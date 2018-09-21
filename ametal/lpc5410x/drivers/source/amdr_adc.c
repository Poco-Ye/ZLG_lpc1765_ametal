/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC驱动实现
 * 
 * \internal
 * \par Modification history
 * - 1.01 15-01-15  hbt, add __adc_global_read.
 * - 1.00 14-12-01  asd, first implementation.
 * \endinternal
 */

#include "amdr_adc.h"
#include "am_int.h"


/*******************************************************************************
* 私有定义
*******************************************************************************/

#define __ADC_HW_DECL(p_hw_adc, p_drv)    \
        amhw_adc_t *p_hw_adc =               \
            ((amdr_adc_dev_t *)p_drv)->p_devinfo->p_hw_adc

#define __ADC_BITS_GET(p_drv)             \
        (((amdr_adc_dev_t *)p_drv)->p_devinfo->bits)

#define __ADC_VREF_GET(p_drv)             \
        (((amdr_adc_dev_t *)p_drv)->p_devinfo->vref)

/*******************************************************************************
* 函数声明
*******************************************************************************/

static int __adc_start (void               *p_drv,
                        int                 channel,
                        uint32_t           *p_val,
                        uint32_t            desired_cnt,
                        void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt),
                        void               *p_arg);

static uint32_t __adc_get_bits(void *p_drv);

static uint32_t __adc_get_vref(void *p_drv);

/**
 * \brief ADC服务函数 
 */
static const struct am_adc_drv_funcs __g_adc_drvfuncs = {
    __adc_start,
    __adc_get_bits, 
    __adc_get_vref
};

/******************************************************************************/

static void __adc_int(void *p_arg)
{
    amdr_adc_dev_t *p_dev = (amdr_adc_dev_t *)p_arg;
    
    __ADC_HW_DECL(p_hw_adc, p_arg);
    
    uint32_t data;

    data = amhw_adc_glo_data_get(p_hw_adc, AMHW_ADC_SEQ_A);
    
    /* 确保数据有效 */
    if ((data & AMHW_ADC_DR_DATAVALID) != 0) {
        
        *(p_dev->p_val) = (data & 0xFFFF) >> (16 - __ADC_BITS_GET(p_arg)); 

        if (p_dev->pfn_convert_cb) {
            p_dev->pfn_convert_cb(p_dev->p_arg,1); /* 每次启动转换仅转换一次 */
        }    
    }
}

/**
 * \brief ADC初始化
 */
am_adc_handle_t amdr_adc_init (amdr_adc_dev_t           *p_dev, 
                               const amdr_adc_devinfo_t *p_devinfo)
{
    amhw_adc_t *p_hw_adc = NULL;

    uint32_t cfg_ctrl;
    uint32_t cfg_seq_a;
    
    if ((p_devinfo == NULL) || (p_dev == NULL)) {
        return NULL;
    }
    
    p_dev->p_devinfo         = p_devinfo;
    p_dev->adc_serve.p_funcs = &__g_adc_drvfuncs;
    p_dev->adc_serve.p_drv   = p_dev; 
    
    p_dev->pfn_convert_cb    = NULL;
    p_dev->chan              = 0;
    
    p_hw_adc                 = p_devinfo->p_hw_adc;
    
    amhw_adc_startup(p_hw_adc);
    
    cfg_ctrl = AMHW_ADC_CTRL_CLK_DIV(p_devinfo->clk_div)    |
               AMHW_ADC_CTRL_MODE_ASYNC                     |
               AMHW_ADC_CTRL_RESOL_NBIT(p_devinfo->bits)    |
               AMHW_ADC_CTRL_SAMPLE_TIME(0)                 |
               AMHW_ADC_CTRL_BYPASS_CALIB;
  
    /* ADC控制寄存器配置 */
    amhw_adc_config(p_hw_adc, cfg_ctrl);
        
    /* ADC 序列A配置 */ 
    cfg_seq_a = AMHW_ADC_SEQ_CTRL_TRIG_SOFT    |  
                AMHW_ADC_SEQ_CTRL_TRIG_POL_POS |  
                AMHW_ADC_SEQ_CTRL_MODE_EOC;
    
    amhw_adc_seq_config(p_hw_adc, AMHW_ADC_SEQ_A, cfg_seq_a);
    
    /* 使能序列A中断 */
    amhw_adc_int_enable(p_hw_adc, AMHW_ADC_INTEN_SEQA_ENABLE); 
    
    /* 序列A使能 */
    amhw_adc_seq_enable(p_hw_adc, AMHW_ADC_SEQ_A);
    
    am_int_connect(p_devinfo->intnums[0], __adc_int, p_dev);
    am_int_enable(p_devinfo->intnums[0]);
    
    return (am_adc_handle_t)(&(p_dev->adc_serve));
}

/**
 * \brief ADC去初始化
 */
void amdr_adc_deinit (amdr_adc_dev_t *p_dev)
{
    int i;
    
    for (i = 0; i < p_dev->p_devinfo->intcnts; i++) {
        am_int_disable(p_dev->p_devinfo->intnums[i]);
    }
    
    amhw_adc_seq_disable(p_dev->p_devinfo->p_hw_adc, AMHW_ADC_SEQ_A);
    
    am_int_disconnect(p_dev->p_devinfo->intnums[0], __adc_int, p_dev);
    am_int_disable(p_dev->p_devinfo->intnums[0]);
}

/**
 * \brief 启动ADC转换
 */
static int __adc_start (void               *p_drv,
                        int                 chan,
                        uint32_t           *p_val,
                        uint32_t            desired_cnt,
                        void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt),
                        void               *p_arg)
{
    __ADC_HW_DECL(p_hw_adc, p_drv);
    amdr_adc_dev_t *p_dev = (amdr_adc_dev_t *)p_drv;

    if (p_val == NULL || desired_cnt == 0) {
        return -AM_EINVAL;
    }

    if (chan >= 12) {
        return -AM_ENXIO;   /* 无效的通道值 */
    }

    p_dev->pfn_convert_cb = pfn_convert_cb;
    p_dev->p_arg          = p_arg;
    p_dev->p_val          = p_val;
    p_dev->chan           = chan;
    
    amhw_adc_seq_chan_set(p_hw_adc, AMHW_ADC_SEQ_A, chan);
    amhw_adc_seq_start(p_hw_adc, AMHW_ADC_SEQ_A);
    
    return AM_OK;
}

/**
 * \brief 获取ADC转换精度。
 */
static uint32_t __adc_get_bits (void *p_drv)
{
    return (uint32_t)__ADC_BITS_GET(p_drv);
}

/**
 * \brief 获取ADC参考电压。
 */
static uint32_t __adc_get_vref (void *p_drv)
{
    return (uint32_t)__ADC_VREF_GET(p_drv);
}

/* end of file */

/*******************************************************************************
*                                Apollo
*                      ----------------------------
*                      innovating embedded platform
*
*Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
*All rights reserved.
*
*Contact information:
*web site:    http://www.zlg.cn/
*e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC驱动，服务ADC标准接口
 *
 * \internal
 * \par Modification History
 * - 1.01 15-01-15  hbt, delete device name in amh_adc_dev.
 * - 1.00 15-01-10  asd, first implementation.
 * \endinternal
 */
 
#ifndef  __AMDR_ADC_H
#define  __AMDR_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_adc.h"
#include "amhw_adc.h"

/**
 * \addtogroup amdr_if_adc
 * \copydoc amdr_adc.h
 * @{
 */


/**
 * \brief ADC 设备信息 
 */
typedef struct amdr_adc_devinfo {
    
    /** \brief 指向ADC寄存器块的指针 */
    amhw_adc_t *p_hw_adc;
    
    /** \brief ADC中断号数组 */
    uint8_t    *intnums;

    /** \brief ADC中断号数量 */
    uint8_t     intcnts;

    /** \brief ADC采样精度 */
    uint8_t     bits;

    /** 
     * \brief ADC参考电压，单位：mV 
     *
     * 对于 LPC5410x, 参考电压 Vref = (Vrefp - Vrefn)  为了在最大采样速率时
     * 稳定运行ADC，确保：VREFP = VDDA Vrefn 典型值为： Vss 或 Vssa 。
     * 
     * \note 该参考电压由具体的电路决定 
     *
     */
    uint32_t    vref;
    
    /** \brief ADC采样时钟分频 */
    uint32_t    clk_div;

} amdr_adc_devinfo_t;

/**
 * \brief ADC设备实例 
 */
typedef struct amdr_adc_dev {
    
    /** \brief ADC标准服务 */
    am_adc_serv_t             adc_serve;

    /** \brief 指向ADC设备信息的指针 */
    const amdr_adc_devinfo_t *p_devinfo;
    
    /** \brief 存放用户启动转换后的回调函数 */
    void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt);
        
    /** \brief 用户启动回调函数的回调函数参数 */
    void                    *p_arg;
    
    /** \brief 当前转换通道的缓冲区          */
    uint32_t                *p_val;
    
    /** \brief 当前转换的通道 */
    uint32_t                 chan;
    
} amdr_adc_dev_t;

/**
 * \brief ADC初始化 
 *
 * 默认初始化序列A 
 *
 * \param[in] p_dev     : 指向ADC设备的指针 
 * \param[in] p_devinfo : 指向ADC设备信息的指针 
 *
 * \return ADC标准服务操作句柄 如果为 NULL，表明初始化失败 
 */
am_adc_handle_t amdr_adc_init(amdr_adc_dev_t           *p_dev, 
                              const amdr_adc_devinfo_t *p_devinfo);

/**
 * \brief ADC去初始化 
 *
 * 默认去初始化序列A 
 *
 * \param[in] p_dev : 指向ADC设备的指针 
 *
 * \return 无 
 */
void amdr_adc_deinit(amdr_adc_dev_t *p_dev);                              
                              
/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMDR_ADC_H  */

/* end of file */

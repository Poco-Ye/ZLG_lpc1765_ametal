/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co.,  Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC例程，转换结果数据通过DMA传输，通过HW层的接口实现
 *
 * - 操作步骤：
 *   1. PIO0_0引脚连接PC串口的TXD；
 *   2. PIO0_1引脚连接PC串口的RXD；
 *   3. PIO0_29(ADC通道0) 连接模拟输入。
 *
 * - 实验现象：
 *   1. ADC转换完成100次，串口打印出100个采样电压值。
 *
 * \par 源代码
 * \snippet demo_hw_adc_dma.c src_hw_adc_dma 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_adc_dma
 * \copydoc demo_hw_adc_dma.c
 */

/** [src_hw_adc_dma] */
#include "ametal.h"
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

/** \brief ADC转换结果缓冲区 */
uint32_t adc_abuf[100];
uint32_t adc_bbuf[100];

/** \brief DMA 重载描述符 */
__align(16) amhw_dma_xfer_desc_t g_desc[2];

/** \brief DMA传输完成标志 */
bool_t  g_trans_adone;
bool_t  g_trans_bdone; 

/** 
 * \brief DMA中断服务程序。
 *
 * \param[in] p_arg : 用户自定义参数，通过 amdr_dma_isr_connect() 函数传递。 
 * \param[in] p_flg : DMA中断标志，由底层驱动传入，该参数的可能取值：
 *                    (#AMDR_DMA_INTA)、(#AMDR_DMA_INTB) 或 (#AMDR_DMA_INTERR)。
 *
 * \return    无。
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;
    
    if (flag == AMDR_DMA_INTA) {  
        
        /* DMA传输完成 */
        g_trans_adone = TRUE;  
        
    } else if (flag == AMDR_DMA_INTB) {
        g_trans_bdone = TRUE;  
        
    } else if (flag == AMDR_DMA_INTERR) {
        // 用户自定义执行代码
    }
}

/**
 * \brief DMA传输：乒乓传输。
 */
void dma_transfer (void)
{
    uint32_t flags1, flags2;
    
    /* DMA通道配置 */
    amdr_dma_chan_setup(DMA_CHAN_0,                     /* DMA通道号                       */
                        AMHW_DMA_CHAN_PERIPH_REQ_OFF |  /* 禁能外设触发                    */
                        AMHW_DMA_CHAN_HWTRIG_LOW     |  /* 低电平触发                      */
                        AMHW_DMA_CHAN_BURST_1        |  /* 突发传输模式                    */
                        AMHW_DMA_CHAN_PRIO_1);          /* 通道优先级：1（0优先级最高）    */
    
    amdr_dma_chan_start(DMA_CHAN_0);                    /* 开始DMA传输                     */
    
    /* DMA传输配置 */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                  /* 当前通道描述符有效              */
             AMHW_DMA_XFER_RELOAD |                     /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                     /* 软件触发                        */
             AMHW_DMA_XFER_CLRTRIG |                    /* 清除触发标志                    */
             AMHW_DMA_XFER_WIDTH_32BIT |                /* 传输数据宽度：32 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* 源端数据地址不递增              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTA;                     /* 使能中断 A                      */

    /* DMA传输配置 */
    flags2 = AMHW_DMA_XFER_CFG_VALID |                  /* 当前通道描述符有效              */
             AMHW_DMA_XFER_RELOAD |                     /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                     /* 软件触发                        */
             AMHW_DMA_XFER_CLRTRIG |                    /* 清除触发标志                    */
             AMHW_DMA_XFER_WIDTH_32BIT |                /* 传输数据宽度：32 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* 源端数据地址不递增              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTB;                     /* 使能中断 B                      */

    /* 建立通道描述符A */
    amdr_dma_xfer_desc_build(&g_desc[0],                    /* A的重载描述符               */
                             (uint32_t)(&AMHW_ADC0->dat0),  /* 源端数据地址                */
                             (uint32_t)&adc_abuf[0],        /* A的目标端缓冲区地址         */
                             4 * 100,                       /* 传输字节数                  */
                             flags1);                       /* 传输配置                    */

    /* 建立通道描述符B */
    amdr_dma_xfer_desc_build(&g_desc[1],                    /* B的重载描述符               */
                             (uint32_t)(&AMHW_ADC0->dat0),  /* 源端数据地址                */
                             (uint32_t)&adc_bbuf[0],        /* B的目标端缓冲区地址         */
                             4 * 100,                       /* 传输字节数                  */
                             flags2);                       /* 传输配置                    */

    /* 连接DMA中断服务函数 */
    amdr_dma_isr_connect(DMA_CHAN_0, dma_isr, (void *)0);
    
    /* 链接重载描述符 */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /* 启动DMA传输，马上开始传输 */
    amdr_dma_chan_xfer_startup(DMA_CHAN_0, &g_desc[0]);
}

/**
 * \brief ADC配置，通过HW层函数接口实现。
 */
void adc_config (void)
{
    uint32_t adc_flags, seq_flags;
    
    /* 配置ADC模拟输入引脚 */
    am_gpio_pin_cfg(PIO0_29, PIO0_29_ADC_IN0 | PIO0_29_INACTIVE); 

    /* ADC时钟配置 */
    amhw_clock_adc_src_set(AMHW_CLOCK_ADC_SRC_MAINCLK);
    amhw_clock_adc_clkdiv_set(0x01);
    
    /* 启动ADC */
    amhw_adc_startup(AMHW_ADC0);

    adc_flags = AMHW_ADC_CTRL_CLK_DIV(0)     |    /* 时钟分频为0（1分频） */ 
                AMHW_ADC_CTRL_MODE_SYNC      |    /* 使能同步模式         */ 
                AMHW_ADC_CTRL_RESOL_12BIT    |    /* 12位采样精度         */ 
                AMHW_ADC_CTRL_SAMPLE_TIME(0) |    /* 采样默认采样时钟     */ 
                AMHW_ADC_CTRL_BYPASS_CALIB;       /* 忽略校验             */ 
    
    /* ADC配置 */
    amhw_adc_config(AMHW_ADC0, adc_flags);

    seq_flags = AMHW_ADC_SEQ_CTRL_MODE_BURST   |  /* 采用突发转换模式      */
                AMHW_ADC_SEQ_CTRL_MODE_EOS     |  /* 序列转换完成后触发DMA */ 
                AMHW_ADC_SEQ_CTRL_ENABLE_CH(0);   /* 使能ADC通道0          */ 

    /* ADC序列A配置 */
    amhw_adc_seq_config(AMHW_ADC0, AMHW_ADC_SEQ_A, seq_flags);
    
    /* 使能序列A中断 */
    amhw_adc_int_enable(AMHW_ADC0, AMHW_ADC_INTEN_SEQA_ENABLE);
    
    /* 使能序列A转换 */
    amhw_adc_seq_enable(AMHW_ADC0, AMHW_ADC_SEQ_A);
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    int i;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amdr_plfm_adc0_init(); 
    amhw_plfm_dma_init();
    
    /* ADC配置 */
    adc_config();

    /* DMA初始化 */
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);

    /* DMA传输 */
    dma_transfer();
    
    while (1) {
        if (g_trans_adone) {
            g_trans_adone = FALSE;
            
            for (i = 0; i < 100; i++) {
                
                /* 串口输出采样电压 */
                am_kprintf("The buffer A conversion %2d: %4d mV \r\n", i,
                            AMHW_ADC_DR_RESULT(adc_abuf[i]) * 3200 / 4095);
            }
            am_mdelay(50);
        }
        
        if (g_trans_bdone) {
            g_trans_bdone = FALSE;
            
            for (i = 0; i < 100; i++) {
                
                /* 串口输出采样电压 */
                am_kprintf("The buffer B conversion %2d: %4d mV \r\n", i,
                            AMHW_ADC_DR_RESULT(adc_bbuf[i]) * 3200 / 4095);
            }
            am_mdelay(50);
        }
    }
}

/** [src_hw_adc_dma] */

/* end of file */

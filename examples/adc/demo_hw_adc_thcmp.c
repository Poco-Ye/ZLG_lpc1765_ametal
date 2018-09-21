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
 * \brief ADC阈值比较的例程，通过HW层的接口实现
 *  
 * - 本例程展示了2种阈值比较：
 *   1. 阈值比较 0: 范围比较；
 *   2. 阈值比较 1: 穿越比较。
 *
 * - 操作步骤：
 *   1. PIO0_0引脚连接PC串口的TXD；
 *   2. PIO0_1引脚连接PC串口的RXD；
 *   3. PIO0_29(ADC通道0) 连接模拟输入1；
 *   3. PIO0_29(ADC通道1) 连接模拟输入2；
 *   4. 将两个通道的模拟输入电压分别从0调到3200 mV。
 *
 * - 实验现象：
 *   1. 模拟输入1的电压低于1100mV或高于2500mV时，串口会输出电压值及比较结果；
 *   1. 模拟输入2的电压变化经过1100mV或2500mV时，串口会输出电压值及比较结果。
 *
 *
 * \par 源代码
 * \snippet demo_hw_adc_thcmp.c src_hw_adc_thcmp
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-20  hbt, modified.
 * - 1.00 14-12-08  asd, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_hw_adc_thcmp
 * \copydoc demo_hw_adc_thcmp.c
 */

/** [src_hw_adc_thcmp] */
#include "ametal.h"  
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"

/** \brief 低比较阈值(mV)  */
#define THRE_LOW            ((1100 * 4095) / 3200)

/** \brief 高比较阈值(mV) */
#define THRE_HIGH           ((2500 * 4095) / 3200)


bool_t g_tc0_flag;  /** \brief 阈值比较0中断标志 */
bool_t g_tc1_flag;  /** \brief 阈值比较1中断标志 */

uint32_t g_val_chan0; /** \brief ADC通道0数据缓冲区 */
uint32_t g_val_chan1; /** \brief ADC通道1数据缓冲区 */

/** 
 * \brief ADC中断服务函数
 */
void adc_isr (void *p_arg)
{
    uint32_t int_flags = 0;
    
    int_flags = amhw_adc_flags_get(AMHW_ADC0);
    
    if (int_flags & AMHW_ADC_FLAGS_THCMP_INT_MASK) {
        if (int_flags & AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_0)) {
            g_tc0_flag  = TRUE;
            g_val_chan0 = amhw_adc_chan_data_get(AMHW_ADC0, AMHW_ADC0_CHAN_0); 
            amhw_adc_flags_clr(AMHW_ADC0, AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_0));
        }
        
        if (int_flags & AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_1)) {
            g_tc1_flag  = TRUE;
            g_val_chan1 = amhw_adc_chan_data_get(AMHW_ADC0, AMHW_ADC0_CHAN_1);
            amhw_adc_flags_clr(AMHW_ADC0, AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_1));
        }
        
        amhw_adc_flags_clr(AMHW_ADC0, AMHW_ADC_FLAGS_THCMP_INT_MASK);
    }
}

/**
 * \brief 配置
 */
void adc_config (void)
{
    uint32_t adc_flags, seq_flags;
    
    /* 配置ADC模拟输入引脚 */
    am_gpio_pin_cfg(PIO0_29, PIO0_29_ADC_IN0 | PIO0_29_INACTIVE);  
    am_gpio_pin_cfg(PIO0_30, PIO0_30_ADC_IN1 | PIO0_30_INACTIVE);

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

    seq_flags = AMHW_ADC_SEQ_CTRL_TRIG_SOFT    |  /* 软件触发               */
                AMHW_ADC_SEQ_CTRL_TRIG_POL_POS |  /* 推荐使用正边沿触发方式 */
                AMHW_ADC_SEQ_CTRL_MODE_EOS     |  /* 通道转换完成触发中断   */
                AMHW_ADC_SEQ_CTRL_ENABLE_CH(1) |  /* 使能ADC通道0           */
                AMHW_ADC_SEQ_CTRL_ENABLE_CH(0);   /* 使能ADC通道1           */

    /* ADC序列A配置 */
    amhw_adc_seq_config(AMHW_ADC0, AMHW_ADC_SEQ_A, seq_flags);
    
    /* 使能中断 */
    amhw_adc_int_enable(AMHW_ADC0, AMHW_ADC_INTEN_CMP_OUTSIDETH(AMHW_ADC0_CHAN_0) |
                                   AMHW_ADC_INTEN_CMP_CROSSTH(AMHW_ADC0_CHAN_1));
    
    /* 为通道选择阈值比较 */
    amdr_adc_thr0_sel(AMHW_ADC0, AMHW_ADC0_CHAN_0);
    amdr_adc_thr1_sel(AMHW_ADC0, AMHW_ADC0_CHAN_1);
     
    /* 设置比较阈值 */
    amhw_adc_thr_low_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_0, THRE_LOW);
    amhw_adc_thr_high_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_0, THRE_HIGH);
    
    amhw_adc_thr_low_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_1, THRE_LOW);
    amhw_adc_thr_high_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_1, THRE_HIGH);
    
    /* 使能序列A */
    amhw_adc_seq_enable(AMHW_ADC0, AMHW_ADC_SEQ_A);
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();
    
    /* 平台初始化 */
    amdr_plfm_adc0_init(); 

    /* 连接ADC中断服务函数，并使能中断 */
    am_int_connect(INUM_ADC0_THCMP, adc_isr, (void *)0);
    am_int_enable(INUM_ADC0_THCMP);
    
    /* ADC配置 */
    adc_config();

    while (1) {
        amhw_adc_seq_start(AMHW_ADC0, AMHW_ADC_SEQ_A);
        
        if (g_tc0_flag == TRUE) {
            g_tc0_flag = FALSE;
            
            am_kprintf("The ADC channel 0 voltage: %4d mV \r\n", 
                        AMHW_ADC_DR_RESULT(g_val_chan0) * 3200 / 4095);
            
            /* 判断通道0阈值比较结果 */
            if (AMHW_ADC_DR_THCMPRANGE(g_val_chan0) == 0x00) {
                am_kprintf("The ADC channel 0 voltage is in range.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPRANGE(g_val_chan0) == 0x01) {
                am_kprintf("The ADC channel 0 voltage is blow range.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPRANGE(g_val_chan0) == 0x02) {
                am_kprintf("The ADC channel 0 voltage is above range.\r\n");
            }
        }
        
        if (g_tc1_flag == TRUE) {
            g_tc1_flag = FALSE;
            
            am_kprintf("The ADC channel 1 voltage: %4d mV \r\n", 
                        AMHW_ADC_DR_RESULT(g_val_chan1) * 3200 / 4095);
            
            /* 判断通道1阈值比较结果 */
            if (AMHW_ADC_DR_THCMPCROSS(g_val_chan1) == 0x00) {
                am_kprintf("The ADC channel 1 voltage no threshold Crossing detected.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPCROSS(g_val_chan1) == 0x02) {
                am_kprintf("The ADC channel 1 voltage downward Threshold Crossing Detected.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPCROSS(g_val_chan1) == 0x03) {
                am_kprintf("The ADC channel 1 voltage upward Threshold Crossing Detected.\r\n");
            }
        }
        am_mdelay(200);
    }
}

/** [src_hw_adc_thcmp] */

/* end of file */

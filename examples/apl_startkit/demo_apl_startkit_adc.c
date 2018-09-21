/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief APL_StartKit ADC演示例程
 *
 * - 操作步骤:
 *   1. 将APL_StartKit配板接到EasyARM-54000M4 demo板；
 *   2. 用跳线帽连接ADC通道3（配板网络标号ADC0）；
 *   3. 将APL_StartKit配板上串口0接口（J3）连接到PC机上。
 *
 * - 实验现象:
 *   1. 通过串口打印出ADC通道3当前的电压值，改变可调电阻，电压值也随之改变。
 *
 * \par 源代码
 * \snippet demo_apl_startkit_adc.c src_apl_startkit_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 14-01-10  asd, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_apl_startkit_adc
 * \copydoc demo_apl_startkit_adc.c
 */

/** [src_apl_startkit_adc] */
#include "ametal.h"  
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

/** \brief ADC数据缓冲区 */
uint32_t g_adc_val;

/** \brief ADC读取完成标志 */
volatile bool_t g_flag = TRUE;

/** \brief ADC标准服务操作句柄 */ 
am_adc_handle_t g_adc0_handle;


/**
 * \brief ADC中断服务函数
 */
void adc_isr (void *p_arg)
{
    /* 
     * 使用中断获取ADC转换结果时，必须从全局数据寄存器读取数据，这样同时可以
     * 清除中断标志。
     */
    g_adc_val = am_adc_global_read(g_adc0_handle);
    
    g_flag = TRUE;
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    uint32_t adc_bits = 0;  
    uint32_t adc_vref = 0;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amdr_plfm_adc0_init(); 
    
    /* 配置ADC模拟输入引脚 */
    am_gpio_pin_cfg(PIO1_0, PIO1_0_ADC_IN3 | PIO1_0_INACTIVE);  

    /* 初始化ADC，并获取ADC标准服务操作句柄 */
    g_adc0_handle = amdr_adc_init(&g_adc0_dev, &g_adc0_devinfo);

    /* 获取ADC转换精度 */
    adc_bits = am_adc_get_bits(g_adc0_handle);
    
    /* 连接ADC中断服务函数，并使能中断 */
    am_int_connect(INUM_ADC0_SEQA, adc_isr, (void *)0); 
    am_int_enable(INUM_ADC0_SEQA);

    /* 获取ADC参考电压，单位：mV */
    adc_vref = am_adc_get_vref(g_adc0_handle);
    
    /* 启动ADC转换 */
    am_adc_start(g_adc0_handle, AMHW_ADC0_CHAN_3); 
    
    while (1) {
        if (g_flag == TRUE) {
            g_flag = FALSE;               /* 清除完成标志 */
            
            /* 串口输出电压采样值 */
            am_kprintf("The ADC voltage value: %d mV \r\n", g_adc_val * adc_vref / 
                                                      ((1UL << adc_bits) - 1));
            am_mdelay(200);
            
            /* 启动下一次AD转换 */
            am_adc_start(g_adc0_handle, AMHW_ADC0_CHAN_3); 
        }
    }
}

/** [src_apl_startkit_adc] */
 
/* end of file */

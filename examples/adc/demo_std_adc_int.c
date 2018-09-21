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
 * \brief ADC例程，利用中断方式获取ADC转换结果，通过标准接口实现
 *
 * - 操作步骤：
 *   1. PIO0_0引脚连接PC串口的TXD；
 *   2. PIO0_1引脚连接PC串口的RXD；
 *   3. PIO0_29(ADC通道0) 连接模拟输入。
 *
 * - 实验现象：
 *   1. 串口输出电压采样值。
 *
 * \par 源代码
 * \snippet demo_std_adc_int.c src_std_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 14-01-10  asd, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_adc_int
 * \copydoc demo_std_adc_int.c
 */

/** [src_std_adc_int] */
#include "ametal.h"  
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

/** \brief ADC数据缓冲区 */
uint32_t g_adc_val;

/** \brief ADC转换完成标志 */
volatile bool_t g_complete_flag = FALSE;

/** \brief ADC标准服务操作句柄 */ 
am_adc_handle_t g_adc0_handle;


/**
 * \brief ADC中断服务函数
 */
void adc_complete (void *p_arg)
{
    g_complete_flag = TRUE;
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    uint32_t adc_bits = 0;  
    uint32_t adc_vref = 0;
    uint32_t adv_val[10];
    int i;
 
    
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amdr_plfm_adc0_init(); 
    
    /* 配置ADC模拟输入引脚 */
    am_gpio_pin_cfg(PIO0_29, PIO0_29_ADC_IN0 | PIO0_29_INACTIVE);  

    /* 初始化ADC，并获取ADC标准服务操作句柄 */
    g_adc0_handle = amdr_adc_init(&g_adc0_dev, &g_adc0_devinfo);

    /* 获取ADC转换精度 */
    adc_bits = am_adc_bits_get(g_adc0_handle);

    /* 获取ADC参考电压，单位：mV */
    adc_vref = am_adc_vref_get(g_adc0_handle);
 
    while (1) {
        
        g_complete_flag = FALSE;          /* 转换完成标志 */
        
        /* 异步读取转换结果 */
        am_adc_async_read(g_adc0_handle, AMHW_ADC0_CHAN_0,adv_val,10, adc_complete,NULL);
        
        while (g_complete_flag == FALSE); /* 等待转换完成 */
        
        am_kprintf("The ADC value channel 0: \r\n");
        
        for (i = 0; i < 10; i++) {
            /* 串口输出采样电压值 */
            am_kprintf("%d mV ", adv_val[i] * adc_vref / ((1UL << adc_bits) - 1));
        }
        
        am_kprintf("\r\n");

        am_mdelay(500);
    }
}

/** [src_std_adc_int] */
 
/* end of file */

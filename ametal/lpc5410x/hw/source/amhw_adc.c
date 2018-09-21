/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC 硬件操作接口实现。
 *
 * - 12位逐次逼近型数模转换器。
 * - 模拟输入引脚多达12个。
 * - 2个独立触发的转换序列。
 * - 可选择高/低阈值比较和“零点穿越”监测。
 * - 电压测量范围从 Vrefn 到 Vrefp (典型值为 3V; 不可超出 VDD 的电压值).
 * - 12位的转换速率高达 4.8 MHz. 可减小转换精度来实现更高的转换速率。
 * - 突发转换模式支持单通道或多通道输入。
 * - 同步或异步操作。在 ADC 的时钟频率内，异步操作可灵活适应。同步模式可减少
 *   潜在的触发干扰、消除不确定触发和因抖动引起的触发响应等。
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-21  hbt, first implementation.
 * \endinternal
 */

#include "amhw_adc.h"

/* 主时钟频率 */
extern uint32_t g_main_clkfreq; 

/******************************************************************************
* Public functions
*******************************************************************************/

/**
 * \brief 启动 ADC
 */
int amhw_adc_startup (amhw_adc_t *p_hw_adc)
{
    int i;
    
    amhw_adc_startup_set(p_hw_adc, AMHW_ADC_STARTUP_ENA);
    
    for (i = 0; i < 0x10; i++) {}

    amhw_adc_startup_set(p_hw_adc, AMHW_ADC_STARTUP_ENA | 
                                   AMHW_ADC_STARTUP_INIT);

    i = 0x7FFFF;
    while ((amhw_adc_startup_get(p_hw_adc) & AMHW_ADC_STARTUP_INIT) && --i );
        
    return i ? AM_OK : -AM_ETIME;
}

/**
 * \brief ADC 校验
 */
void amhw_adc_calibrate (amhw_adc_t *p_hw_adc, uint32_t sysclk_freq)
{
    int i;
    
    /* 
     * 如未曾校验，则进行校验。
     */
    if (amhw_adc_calib_isrun(p_hw_adc)) {
        uint32_t ctrl = amhw_adc_ctrl_get(p_hw_adc) & (0x00007FFF);
        uint32_t tmp  = ctrl;

        /* 设置 ADC 异步模式 */
        tmp &= ~(1 << 8);
        
        /* 为了能顺利完成校验，ADC频率应在 1MHz 到 30MHz 之间 */
        if (sysclk_freq > 1000000UL) {
            tmp |= (((sysclk_freq / 1000000UL) - 1) & 0xFF);
            amhw_adc_config(p_hw_adc, tmp);
        }

        /* 使能校验 */
        amhw_adc_calib_enable(p_hw_adc);
        
        i = 0xF0000;
        while (amhw_adc_calib_get(p_hw_adc) && --i);
        
        amhw_adc_config(p_hw_adc, ctrl);
    }
}

/* end of file */

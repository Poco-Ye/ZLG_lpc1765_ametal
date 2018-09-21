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
 * \brief 时钟频率输出演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. 时钟频率输出通过PIO0_21引脚， 时钟频率等于 main clock / CLKOUT_DIV
 *
 * \par 源代码
 * \snippet demo_hw_clkout.c src_hw_clkout
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_clkout
 * \copydoc demo_hw_clkout.c
 */

/** [src_hw_clkout] */
#include "ametal.h"
#include "am_board.h"



/* 时钟源和时钟分频参数定义 */
#define CLKOUT_SRC  AMHW_CLOCK_CLKOUT_SRC_MAINCLK   /**< \brief 时钟源定义       */
#define CLKOUT_DIV  100                             /**< \brief 时钟分频参数定义 */

/**
 * \brief 主函数
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();

    AM_DBG_INFO("The demo for clock out\r\n");
    
    am_gpio_pin_cfg(PIO0_21, PIO0_21_CLKOUT);
    
    /* 检测到时钟源并使能 */
    if (CLKOUT_SRC == AMHW_CLOCK_CLKOUT_SRC_RTC) {
        
        /* 开启RTC 32K时钟振荡器 */
        amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);
        amhw_clock_rtcosc_enable();
        
    } else if (CLKOUT_SRC == AMHW_CLOCK_CLKOUT_SRC_WDTOSC) {
    
        /* 开启WDT 时钟振荡器 */
        amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);
        
    } else if (CLKOUT_SRC == AMHW_CLOCK_CLKOUT_SRC_CLKIN) {
        
        /* 配置时钟输入引脚 */
        am_gpio_pin_cfg(PIO0_22, PIO0_22_CLKIN);

        if (amhw_clock_clkin_rate_get() == 0) {
            
            AM_DBG_INFO("CLKIN selected for CLKOUT, but CLKIN rate is 0\r\n");
            while (1) {}
        }
    }
    
    /* 配置输出时钟源和时钟分频参数 */
    amhw_clock_clkout_config(CLKOUT_SRC, CLKOUT_DIV);
    
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_hw_clkout] */

/* end of file */

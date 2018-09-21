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
 * \brief PLL例程，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. 输出PLL期望频率、实际输出频率和CLKOUT引脚输出频率；
 *   2. CLKOUT引脚(PIO0_21引脚)输出CLKOUT_DIV分频后的主时钟频率。
 *
 * \par 源代码
 * \snippet demo_hw_pll.c src_hw_pll
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hw_pll
 * \copydoc demo_hw_pll.c
 */

/** [src_hw_pll] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief PLL时钟源，为以下一种：
 * AMHW_PLL_CLKSRC_IRC, AMHW_PLL_CLKSRC_CLKIN,
 * AMHW_PLL_CLKSRC_WDTOSC, AMHW_PLL_CLKSRC_RTC.
 */
#define PLL_CLKSRC          AMHW_PLL_CLKSRC_IRC

/**
 * \brief PLL期望输出频率
 * 最小为1.5MHz，最大为100MHz。
 */
#define PLL_DESIREDRATE     100000000

/** \brief 使能该定义将使用更精确的PLL输出 */
//#define USEPLLPRECISE

/** \brief 选择输出时钟源 */
#define CLKOUT_SRC      AMHW_CLOCK_CLKOUT_SRC_MAINCLK

/** \brief 输出时钟源分频 */
#define CLKOUT_DIV      100


/**
 * \brief 主函数入口
 */
int main (void)
{
    amhw_pll_stat_t stat;

    /* 板级初始化 */
    am_board_init();

    if (PLL_CLKSRC == AMHW_PLL_CLKSRC_RTC) {

        /*
         * 如果使用RTC为PLL时钟源，启动RTC 32K 振荡器。
         */
        amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);
        amhw_clock_rtcosc_enable();
    }
    else if (PLL_CLKSRC == AMHW_PLL_CLKSRC_WDTOSC) {

        /* WDT振荡器上电 */
        amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);
    }
    else if (PLL_CLKSRC == AMHW_PLL_CLKSRC_CLKIN) {

        /* 配置CLKIN引脚 */
        am_gpio_pin_cfg(PIO0_22, PIO0_22_CLKIN);

        if (amhw_clock_clkin_rate_get() == 0) {

            /* 停止！ */
            AM_DBG_INFO("CLKIN selected for CLKOUT, but CLKIN rate is 0\r\n");
            while (1) {}
        }
    }

    /* 配置PLL之前，改变主时钟源为IRC */
    amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);

#ifdef USEPLLPRECISE
    stat = amhw_pll_config(PLL_CLKSRC, PLL_DESIREDRATE, TRUE);
#else
    stat = amhw_pll_config(PLL_CLKSRC, PLL_DESIREDRATE, FALSE);
#endif

    if (stat == AMHW_PLL_SUCCESS) {

        AM_DBG_INFO("PLL configure Success!\r\n");
        AM_DBG_INFO("The Desired rate is %8d Hz\r\n", PLL_DESIREDRATE);
        AM_DBG_INFO("The Actual  rate is %8d Hz\r\n", amhw_pll_out_clkrate_get());

        /* 选择系统时钟分频为1, 故系统时钟 = 主时钟 / 1 */
        amhw_clock_system_clkdiv_set(1);

        /* 设置PLL输出为主时钟源 */
        amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);

    } else {
        AM_DBG_INFO("PLL configure fail! status = %d \r\n", stat);
    }

    /* 如主时钟频率改变，应更新频率 */
    amhw_clock_freq_update();
    am_delay_init();

    AM_DBG_INFO("The CLKOUT  rate is  %8d Hz\r\n", g_main_clkfreq / CLKOUT_DIV);

    /* 配置CLKOUT引脚 */
    am_gpio_pin_cfg(PIO0_21, PIO0_21_CLKOUT);

    /* 配置CLKOUT时钟源和时钟分频 */
    amhw_clock_clkout_config(CLKOUT_SRC, CLKOUT_DIV);

    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_hw_pll] */

/* end of file */

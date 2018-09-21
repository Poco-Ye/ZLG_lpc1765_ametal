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
 * \brief PLL���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. ���PLL����Ƶ�ʡ�ʵ�����Ƶ�ʺ�CLKOUT�������Ƶ�ʣ�
 *   2. CLKOUT����(PIO0_21����)���CLKOUT_DIV��Ƶ�����ʱ��Ƶ�ʡ�
 *
 * \par Դ����
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
 * \brief PLLʱ��Դ��Ϊ����һ�֣�
 * AMHW_PLL_CLKSRC_IRC, AMHW_PLL_CLKSRC_CLKIN,
 * AMHW_PLL_CLKSRC_WDTOSC, AMHW_PLL_CLKSRC_RTC.
 */
#define PLL_CLKSRC          AMHW_PLL_CLKSRC_IRC

/**
 * \brief PLL�������Ƶ��
 * ��СΪ1.5MHz�����Ϊ100MHz��
 */
#define PLL_DESIREDRATE     100000000

/** \brief ʹ�ܸö��彫ʹ�ø���ȷ��PLL��� */
//#define USEPLLPRECISE

/** \brief ѡ�����ʱ��Դ */
#define CLKOUT_SRC      AMHW_CLOCK_CLKOUT_SRC_MAINCLK

/** \brief ���ʱ��Դ��Ƶ */
#define CLKOUT_DIV      100


/**
 * \brief ���������
 */
int main (void)
{
    amhw_pll_stat_t stat;

    /* �弶��ʼ�� */
    am_board_init();

    if (PLL_CLKSRC == AMHW_PLL_CLKSRC_RTC) {

        /*
         * ���ʹ��RTCΪPLLʱ��Դ������RTC 32K ������
         */
        amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);
        amhw_clock_rtcosc_enable();
    }
    else if (PLL_CLKSRC == AMHW_PLL_CLKSRC_WDTOSC) {

        /* WDT�����ϵ� */
        amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);
    }
    else if (PLL_CLKSRC == AMHW_PLL_CLKSRC_CLKIN) {

        /* ����CLKIN���� */
        am_gpio_pin_cfg(PIO0_22, PIO0_22_CLKIN);

        if (amhw_clock_clkin_rate_get() == 0) {

            /* ֹͣ�� */
            AM_DBG_INFO("CLKIN selected for CLKOUT, but CLKIN rate is 0\r\n");
            while (1) {}
        }
    }

    /* ����PLL֮ǰ���ı���ʱ��ԴΪIRC */
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

        /* ѡ��ϵͳʱ�ӷ�ƵΪ1, ��ϵͳʱ�� = ��ʱ�� / 1 */
        amhw_clock_system_clkdiv_set(1);

        /* ����PLL���Ϊ��ʱ��Դ */
        amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);

    } else {
        AM_DBG_INFO("PLL configure fail! status = %d \r\n", stat);
    }

    /* ����ʱ��Ƶ�ʸı䣬Ӧ����Ƶ�� */
    amhw_clock_freq_update();
    am_delay_init();

    AM_DBG_INFO("The CLKOUT  rate is  %8d Hz\r\n", g_main_clkfreq / CLKOUT_DIV);

    /* ����CLKOUT���� */
    am_gpio_pin_cfg(PIO0_21, PIO0_21_CLKOUT);

    /* ����CLKOUTʱ��Դ��ʱ�ӷ�Ƶ */
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

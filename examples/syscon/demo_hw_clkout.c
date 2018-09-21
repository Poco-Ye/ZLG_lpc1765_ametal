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
 * \brief ʱ��Ƶ�������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. ʱ��Ƶ�����ͨ��PIO0_21���ţ� ʱ��Ƶ�ʵ��� main clock / CLKOUT_DIV
 *
 * \par Դ����
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



/* ʱ��Դ��ʱ�ӷ�Ƶ�������� */
#define CLKOUT_SRC  AMHW_CLOCK_CLKOUT_SRC_MAINCLK   /**< \brief ʱ��Դ����       */
#define CLKOUT_DIV  100                             /**< \brief ʱ�ӷ�Ƶ�������� */

/**
 * \brief ������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();

    AM_DBG_INFO("The demo for clock out\r\n");
    
    am_gpio_pin_cfg(PIO0_21, PIO0_21_CLKOUT);
    
    /* ��⵽ʱ��Դ��ʹ�� */
    if (CLKOUT_SRC == AMHW_CLOCK_CLKOUT_SRC_RTC) {
        
        /* ����RTC 32Kʱ������ */
        amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);
        amhw_clock_rtcosc_enable();
        
    } else if (CLKOUT_SRC == AMHW_CLOCK_CLKOUT_SRC_WDTOSC) {
    
        /* ����WDT ʱ������ */
        amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);
        
    } else if (CLKOUT_SRC == AMHW_CLOCK_CLKOUT_SRC_CLKIN) {
        
        /* ����ʱ���������� */
        am_gpio_pin_cfg(PIO0_22, PIO0_22_CLKIN);

        if (amhw_clock_clkin_rate_get() == 0) {
            
            AM_DBG_INFO("CLKIN selected for CLKOUT, but CLKIN rate is 0\r\n");
            while (1) {}
        }
    }
    
    /* �������ʱ��Դ��ʱ�ӷ�Ƶ���� */
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

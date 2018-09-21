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
 * \brief RTC��ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * ��������ʾ��δ���RTC��ʹ��RTC������ͨ��RTC�������ܴ�˯�ߡ����˯�ߡ�����ģʽ����оƬ��
 *
 * - ʵ������:
 *  1. оƬ����˯��ģʽ��RTC���Ѷ�ʱ���Բ�����ʱ��������оƬ������оƬ
 *     �ֽ�����һ��������˯�ߣ�4��֮��RTC��������оƬ��\n
 *     ���Դ����ظ����������Ϣ��
 * \code
 *    Tick number: 0,  1KHZ int:0, alarm int:1
 *    Tick number: 1,  1KHZ int:1, alarm int:0
 *    Tick number: 2,  1KHZ int:1, alarm int:0
 *    Tick number: 3,  1KHZ int:1, alarm int:0
 *    Tick number: 4,  1KHZ int:1, alarm int:0
 *    Tick number: 5,  1KHZ int:1, alarm int:0
 *    Tick number: 6,  1KHZ int:1, alarm int:0
 *    Tick number: 7,  1KHZ int:1, alarm int:0
 *    Tick number: 8,  1KHZ int:1, alarm int:0
 *    Tick number: 9,  1KHZ int:1, alarm int:0
 *    Tick number: 10, 1KHZ int:1, alarm int:0
 *    Setting alarm to wake up in 4s
 * \endcode
 *
 * \par Դ����
 * \snippet demo_hw_rtc.c src_hw_rtc 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_rtc
 * \copydoc demo_hw_rtc.c
 */
 
/** [src_hw_rtc] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief ��Դģʽ��������3��֮һ:
 *         - ˯��ģʽ
 *         - ���˯��ģʽ
 *         - ����ģʽ
 */
#define POWER_MODE    AMHW_POWER_MODE_POWER_DOWN

static  amhw_clock_main_src_t   g_saved_clksrc;   /**< \brief ʱ��Դ�������壬���ڱ���ʱ�� */

static volatile bool_t g_rtc_wake;  /**< \brief RTC 1 kHz ��ʱ�����ѱ�־ */
static volatile bool_t g_rtc_alarm; /**< \brief RTC 1 Hz ��ʱ��������־  */

/** 
 * \brief RTC �жϴ�����
 * \param[in] p_arg : �ж���ں���
 * \return  ��
 */
void rtc_irq_handler (void *p_arg)
{
    uint32_t rtc_status;

    am_led_toggle(0);

    /* ��ȡRTC״̬ */
    rtc_status = amhw_rtc_stat_get(AMHW_RTC);

    /* ����Ƿ�1KHz ��ʱ��ƥ���ж� */
    if (rtc_status & AMHW_RTC_CTRL_WAKE1KHZ) {
        g_rtc_wake  = TRUE;
    }

    /* ����Ƿ�1Hz ��ʱ�������ж� */
    if (rtc_status & AMHW_RTC_CTRL_ALARM1HZ) {
        g_rtc_alarm = TRUE;
    }

    /* ����ж�״̬λ */
    amhw_rtc_stat_clr(AMHW_RTC, 
                     (rtc_status & (AMHW_RTC_CTRL_WAKE1KHZ | AMHW_RTC_CTRL_ALARM1HZ)));
}

/**
 * \brief ������
 */
int main(void)
{
    int state_counter = 0;

    /* �弶��ʼ�� */
    am_board_init();
    
    /* RTCƽ̨��ʼ�� */
    amhw_plfm_rtc_init();
    
    /* ʹ��RTC���� */
    amhw_syscon_wakeup_enable(AMHW_SYSCON_STARTER_RTC);

    /* RTC��λ */
    amhw_rtc_reset(AMHW_RTC);

    /* 
     * ��RTC����ʱ���趨RTC���������� 
     */
    amhw_rtc_disable(AMHW_RTC);
    amhw_rtc_count_set(AMHW_RTC, 0);

    /* �趨�ϳ�����ʱ�䣬��ֹ�жϴ��� */
    amhw_rtc_alarm_set(AMHW_RTC, 1000);

    /* ʹ��RTC */
    amhw_rtc_enable(AMHW_RTC);
    amhw_rtc_enable_1kHz(AMHW_RTC);
    
    /* ���RTC״̬λ */
    amhw_rtc_stat_clr(AMHW_RTC, (AMHW_RTC_CTRL_OFD      |
                                 AMHW_RTC_CTRL_ALARM1HZ | 
                                 AMHW_RTC_CTRL_WAKE1KHZ));

    /* ʹ��RTC�ж� */
    am_int_connect(INUM_RTC, rtc_irq_handler, (void *)0);
    am_int_enable(INUM_RTC);

    /* ���浱ǰ������ʱ��Դ */
    g_saved_clksrc = amhw_clock_main_src_get();

    /* ʹ��RTC�����ж� */
    amhw_rtc_enable_wakeup(AMHW_RTC, (AMHW_RTC_CTRL_ALARMDPD_EN | 
                                      AMHW_RTC_CTRL_WAKEDPD_EN));

    while (1) {
        
        AM_DBG_INFO("Tick number: %d, 1KHZ int:%d, alarm int:%d\r\n",
                    state_counter, g_rtc_wake, g_rtc_alarm);
        
        g_rtc_wake = g_rtc_alarm = FALSE;

        /* ����ʱ����һ�α�һ�γ�100ms,��ֵ300ms */
        if (state_counter < 10) {
            
            /* ����ʱ����300ms��400ms��500ms�� */
            amhw_rtc_setwake(AMHW_RTC, (300 + (state_counter * 100)));
            state_counter++;
        } else {
            AM_DBG_INFO("Setting alarm to wake up in 4s\r\n");
           
           /* ��������ʱ���趨Ϊ4�� */
            amhw_rtc_alarm_set(AMHW_RTC, amhw_rtc_count_get(AMHW_RTC) + 4);
            state_counter = 0;
        }
       
        /* 
         * ����˯�߻��ߵ���ģʽ����ȷ���������ݴ������ 
         */
        while ((amhw_usart_stat_get(AM_CFG_DEBUG_USART) & AMHW_USART_STAT_TXIDLE) == 0);
        
        /* �ڽ���˯��ģʽǰ������PLL */
        if (g_saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);
            amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);
        }

        amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_clock_main_clkrate_get());

        /* 
         * ����˯��ģʽ��ʹ��32Kʱ��Դ
         */
        amhw_power_mode_enter(POWER_MODE, (AMHW_POWER_PD_SRAM0A  |
                                           AMHW_POWER_PD_SRAM0B  |
                                           AMHW_POWER_PD_32K_OSC));

        if (g_saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            amhw_syscon_powerup(AMHW_SYSCON_PD_SYS_PLL);

            /* �ȴ�PLL���� */
            while (!amhw_pll_locked_chk()) {}
                
            amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_pll_out_clkrate_get());

            /* ʹ��PLL��Ϊ��ʱ�� */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);
        }
    }
}

/** [src_hw_rtc] */

/* end of file */

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
 * \brief RTC��ʾ���̣���ϵͳ����ȵ���ģʽ���ѣ�ͨ��HW��Ľӿ�ʵ��
 *
 * ��������ʾ��δ���RTC��ʹ��RTC������ͨ��RTC�������ܴ���ȵ���ģʽ����оƬ��
 *
 * - ʵ������:
 *  1. ���Դ����ظ����������Ϣ�� \n
 *     Reset \n
 *     led toggle \n
 *     Setting alarm to wake up in 1000ms \n
 *
 * \par Դ����
 * \snippet demo_hw_rtc_deep_powerdown.c src_hw_rtc_deep_powerdown 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_rtc_deep_powerdown
 * \copydoc demo_hw_rtc_deep_powerdown.c
 */

/** [src_hw_rtc_deep_powerdown] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief RTC�жϴ�����
 *
 *  һ�����ѣ���ִ���жϺ���
 *
 * \param[in] p_arg : �ж���ڲ���
 * \return  �� 
 */
void rtc_irq_handler (void *p_arg)
{
    uint32_t rtc_status;

    am_led_toggle(0);

    AM_DBG_INFO("led toggle\r\n");
    
    /* ��ȡRTC״̬ */
    rtc_status = amhw_rtc_stat_get(AMHW_RTC);

    /* ���RTC״̬ */
    amhw_rtc_stat_clr(AMHW_RTC, (rtc_status & (AMHW_RTC_CTRL_WAKE1KHZ | 
                                               AMHW_RTC_CTRL_ALARM1HZ)));
}

/**
 * \brief ������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();
    
    /*  RTCƽ̨��ʼ�� */
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
 
    /*
     * RTC�жϹ���λ��λ����ϵͳ����ȵ���ģʽ���Ѻ�ִ��RTC�жϺ�����
     * ������ִ��RTC�жϴ�����������жϹ���λ���ɡ� 
     */
//    amhw_int_clr_pending(INUM_RTC);

    /* ���Ӳ�ʹ��RTC�ж� */
    am_int_connect(INUM_RTC, rtc_irq_handler, (void *)0);
    am_int_enable(INUM_RTC);

    /* ʹ��RTC�����ж� */
    amhw_rtc_enable_wakeup(AMHW_RTC, (AMHW_RTC_CTRL_ALARMDPD_EN | 
                                      AMHW_RTC_CTRL_WAKEDPD_EN));

    AM_DBG_INFO("Reset\r\n");

    /* can do some other things */
    am_mdelay(2000);

    while(1) {
        /*
         * �趨����ʱ��1500ms,���ֵ65535msWakeup
         */
        amhw_rtc_setwake(AMHW_RTC, 1500);
        AM_DBG_INFO("Setting alarm to wake up in 1000ms\r\n");
        
        /*
         * ������ʱ�䳬�����ֵ������10s
         */
    //      amh_rtc_alarm_set(AMHW_RTC, amhw_rtc_count_get(AMHW_RTC) + 10);  
    //      AM_DBG_INFO("Setting alarm to wake up in 10s\r\n");
        /* 
         * ����˯�߻��ߵ���ģʽ����ȷ���������ݴ������ 
         */
        while ((amhw_usart_stat_get(AM_CFG_DEBUG_USART) & AMHW_USART_STAT_TXIDLE) == 0);
        
        /* �������ģʽ��������ʱ��оƬ����*/
        amhw_power_mode_enter(AMHW_POWER_MODE_DEEP_POWER_DOWN, AMHW_SYSCON_PD_32K_OSC);
    }
}

/** [src_hw_rtc_deep_powerdown] */

/* end of file */

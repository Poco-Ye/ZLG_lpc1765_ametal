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
 * \brief ��Ƶ�ʶ�ʱ��(MRT)����,ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED0��10Hz��Ƶ����˸;
 *   2. PIO0_5���ŵ������ƽ״̬��8KHz��Ƶ�ʱ任������4KHz�Ĳ��Ρ�
 *
 * \par Դ����
 * \snippet demo_hw_mrt.c src_hw_mrt
 *
 * \internal
 * \par History
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hw_mrt
 * \copydoc demo_hw_mrt.c
 */

/** [src_hw_mrt] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief ��Ƶ�ʶ�ʱ���жϷ�������
 * \param[in] p_arg : �û��Զ���Ĳ�����ͨ�� am_int_connect()���ݡ�
 * \return ��
  */
void mrt_irq_handler (void *p_arg)
{
    if (amhw_mrt_int_pending_get(AMHW_MRT, AMHW_MRT_CH(0)) == TRUE) {

        /* ��תPIO0_5����״̬ */
        am_gpio_toggle(PIO0_5);

        /* ���жϵȴ���־ */
        amhw_mrt_int_pending_clr(AMHW_MRT, AMHW_MRT_CH(0));
    }

    if (amhw_mrt_int_pending_get(AMHW_MRT, AMHW_MRT_CH(1)) == TRUE) {

        am_led_toggle(LED0);

        /* �����Ҫ�ٴβ����жϣ�one-shotģʽӦ���ٴμ����ж�ֵ */
        amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(1), g_system_clkfreq / 10, TRUE);

        /* ���жϵȴ���־ */
        amhw_mrt_int_pending_clr(AMHW_MRT, AMHW_MRT_CH(1));
    }
}

/**
 * \brief ��������ڡ�
 */
int main (void)
{
    uint32_t ticks;

    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_mrt_init();

    am_gpio_pin_cfg(PIO0_5, PIO0_5_GPIO | PIO0_5_OUTPUT);

    /* ��������ͨ�����ж� */
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(0));
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(1));
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(2));
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(3));

    am_int_connect(INUM_MRT, mrt_irq_handler, (void *)0);
    am_int_enable(INUM_MRT);

    /*
     * ͨ��0ΪAMHW_MRT_MODE_REPEATģʽ���ж�Ƶ��Ϊ8KHz��
     * ����ж�ֵΪ0xFFFFFF��
     * ��100MHz�����ʱ��Ϊ0xFFFFFF / 100 us = 167772 us����СƵ��Ϊ��6 Hz��
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(0), AMHW_MRT_MODE_REPEAT);
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(0), g_system_clkfreq / 8000, TRUE);
    amhw_mrt_int_enable(AMHW_MRT, AMHW_MRT_CH(0));

    /*
     * ͨ��1ΪAMHW_MRT_MODE_ONESHOTģʽ���ж�Ƶ��10Hz��
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(1), AMHW_MRT_MODE_ONESHOT);
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(1), g_system_clkfreq / 10, TRUE);
    amhw_mrt_int_enable(AMHW_MRT, AMHW_MRT_CH(1));


    /*
     * ͨ��2ΪAMHW_MRT_MODE_ONESHOTģʽ����ʱ100us��
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(2), AMHW_MRT_MODE_ONESHOT);

    ticks = 100 * (g_system_clkfreq / 1000000);

    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(2), ticks, TRUE);

    /* �ȴ� */
    while((amhw_mrt_stat_get(AMHW_MRT, AMHW_MRT_CH(2)) & AMHW_MRT_STAT_INTFLAG) == 0);

    /* ���жϱ�־ */
    amhw_mrt_int_flag_clr(AMHW_MRT, AMHW_MRT_CH(2));

    /*
     * ͨ��3ΪAMHW_MRT_MODE_ONESHOT_STALLģʽ��ʱ100ns��
     * one-stallģʽ�����ڷǳ����ݵ���ʱ��������д����ֹͣʱ����Ƶ�ʶ�ʱ������
     * ��ʱ����ʱ��ɺ��ڽ���д����������Ҫ�жϻ��ѯ״̬��־��
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(3), AMHW_MRT_MODE_ONESHOT_STALL);

    /* ��ʱ100��ϵͳʱ�ӣ�����ʱ��ɣ�д����Ҳ��ɡ� */
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(3), 100, TRUE);

    while (1) {
        AM_DBG_INFO("idle channel :%d \r\n", amhw_mrt_idle_channel_get(AMHW_MRT));
        am_mdelay(1000);
    }
}

/** [src_hw_mrt] */

/* end of file */

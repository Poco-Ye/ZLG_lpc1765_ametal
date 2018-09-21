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
 * \brief LPC5410X timer ���ڶ�ʱ�������ļ�
 * \sa amdr_hwconfig_timer_timing.c 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_timer_timing.h"

/**
 * \addtogroup amdr_if_hwconfig_src_timer_timing
 * \copydoc amdr_hwconfig_timer_timing.c 
 * @{
 */

/** \brief ��ʱ��0�豸��Ϣ */
const amdr_timer_timing_devinfo_t  g_timer0_timing_devinfo = {
    AMHW_TIMER0,                /**< \brief ָ��ʱ��0�Ĵ������ָ��  */
    INUM_TIMER0,                /**< \brief ��ʱ��0�жϺ� */
};

/** \brief ��ʱ��0�豸 */
amdr_timer_timing_dev_t  g_timer0_timing_dev;

/** \brief ��ʱ��0ƽ̨��ʼ�� */
void amhw_plfm_timer0_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER0);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
}

/** \brief �����ʱ��0ƽ̨��ʼ�� */
void amhw_plfm_timer0_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER0);
}

/** \brief ��ʱ��1�豸��Ϣ */
const amdr_timer_timing_devinfo_t  g_timer1_timing_devinfo = {
    AMHW_TIMER1,                /**< \brief ָ��ʱ��1�Ĵ������ָ��  */
    INUM_TIMER1,                /**< \brief ��ʱ��1�жϺ� */
};

/** \brief ��ʱ��1�豸 */
amdr_timer_timing_dev_t  g_timer1_timing_dev;

/** \brief ��ʱ��1ƽ̨��ʼ�� */
void amhw_plfm_timer1_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER1);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
}

/** \brief �����ʱ��1ƽ̨��ʼ�� */
void amhw_plfm_timer1_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER1);
}

/** \brief ��ʱ��2�豸��Ϣ */
const amdr_timer_timing_devinfo_t  g_timer2_timing_devinfo = {
    AMHW_TIMER2,                /**< \brief ָ��ʱ��2�Ĵ������ָ��  */
    INUM_TIMER2,                /**< \brief ��ʱ��2�жϺ� */
};

/** \brief ��ʱ��2�豸 */
amdr_timer_timing_dev_t  g_timer2_timing_dev;

/** \brief ��ʱ��2ƽ̨��ʼ�� */
void amhw_plfm_timer2_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER2);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
}

/** \brief �����ʱ��2ƽ̨��ʼ�� */
void amhw_plfm_timer2_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER2);
}

/** \brief ��ʱ��3�豸��Ϣ */
const amdr_timer_timing_devinfo_t  g_timer3_timing_devinfo = {
    AMHW_TIMER3,                /**< \brief ָ��ʱ��3�Ĵ������ָ��  */
    INUM_TIMER3,                /**< \brief ��ʱ��3�жϺ� */
};

/** \brief ��ʱ��3�豸 */
amdr_timer_timing_dev_t  g_timer3_timing_dev;

/** \brief ��ʱ��3ƽ̨��ʼ�� */
void amhw_plfm_timer3_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER3);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
}

/** \brief �����ʱ��3ƽ̨��ʼ�� */
void amhw_plfm_timer3_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER3);
}

/** \brief ��ʱ��4�豸��Ϣ */
const amdr_timer_timing_devinfo_t  g_timer4_timing_devinfo = {
    AMHW_TIMER4,                /**< \brief ָ��ʱ��4�Ĵ������ָ��  */
    INUM_TIMER4,                /**< \brief ��ʱ��4�жϺ� */
};

/** \brief ��ʱ��4�豸 */
amdr_timer_timing_dev_t  g_timer4_timing_dev; 

/** \brief ��ʱ��4ƽ̨��ʼ�� */
void amhw_plfm_timer4_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER4);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER4);
}

/** \brief �����ʱ��4ƽ̨��ʼ�� */
void amhw_plfm_timer4_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER4);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER4);
}

/**
 * @}
 */

/* end of file */

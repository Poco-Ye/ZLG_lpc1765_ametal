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
 * \brief LPC5410X Timer PWM���ܵ��û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_TIMER_PWM_H
#define __AMDR_HWCONFIG_TIMER_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/** \brief Timer0 PWM���ܵ��豸��Ϣ */
extern amdr_timer_pwm_dev_t            g_timer0_pwm_dev;

/** \brief Timer0 PWM�����豸 */
extern const amdr_timer_pwm_devinfo_t  g_timer0_pwm_devinfo;

/**
 * \brief Timer0 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer0_pwm_init(void);

/**
 * \brief ���Timer0 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer0_pwm_deinit(void);


/** \brief Timer1 PWM���ܵ��豸��Ϣ */
extern amdr_timer_pwm_dev_t            g_timer1_pwm_dev;

/** \brief Timer1 PWM�����豸 */
extern const amdr_timer_pwm_devinfo_t  g_timer1_pwm_devinfo;

/**
 * \brief Timer1 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer1_pwm_init(void);

/**
 * \brief ���Timer1 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer1_pwm_deinit(void);


/** \brief Timer2 PWM���ܵ��豸��Ϣ */
extern amdr_timer_pwm_dev_t            g_timer2_pwm_dev;

/** \brief Timer2 PWM�����豸 */
extern const amdr_timer_pwm_devinfo_t  g_timer2_pwm_devinfo;

/**
 * \brief Timer2 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer2_pwm_init(void);

/**
 * \brief ���Timer2 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer2_pwm_deinit(void);

/** \brief Timer3 PWM���ܵ��豸��Ϣ */
extern amdr_timer_pwm_dev_t            g_timer3_pwm_dev;

/** \brief Timer3 PWM�����豸 */
extern const amdr_timer_pwm_devinfo_t  g_timer3_pwm_devinfo;

/**
 * \brief Timer3 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer3_pwm_init(void);

/**
 * \brief ���Timer3 PWM���ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer3_pwm_deinit(void);


/* timer4û���ⲿ�������PWM */

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_TIMER_PWM_H */

/* end of file */

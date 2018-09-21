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
 * \brief LPC5410X timer�������û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_TIMER_CAP_H
#define __AMDR_HWCONFIG_TIMER_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/** \brief Timer0�����ܵ��豸��Ϣ */
extern amdr_timer_cap_dev_t            g_timer0_cap_dev;

/** \brief Timer0�������豸 */
extern const amdr_timer_cap_devinfo_t  g_timer0_cap_devinfo;

/**
 * \brief Timer0�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer0_cap_init(void);

/**
 * \brief ���Timer0�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer0_cap_deinit(void);


/** \brief Timer1�����ܵ��豸��Ϣ */
extern amdr_timer_cap_dev_t            g_timer1_cap_dev;

/** \brief Timer1�������豸 */
extern const amdr_timer_cap_devinfo_t  g_timer1_cap_devinfo;

/**
 * \brief Timer1�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer1_cap_init(void);

/**
 * \brief ���Timer1�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer1_cap_deinit(void);


/** \brief Timer2�����ܵ��豸��Ϣ */
extern amdr_timer_cap_dev_t            g_timer2_cap_dev;

/** \brief Timer2�������豸 */
extern const amdr_timer_cap_devinfo_t  g_timer2_cap_devinfo;

/**
 * \brief Timer2�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer2_cap_init(void);

/**
 * \brief ���Timer2�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer2_cap_deinit(void);


/** \brief Timer3�����ܵ��豸��Ϣ */
extern amdr_timer_cap_dev_t            g_timer3_cap_dev;

/** \brief Timer3�������豸 */
extern const amdr_timer_cap_devinfo_t  g_timer3_cap_devinfo;

/**
 * \brief Timer3�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer3_cap_init(void);

/**
 * \brief ���Timer3�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer3_cap_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_TIMER_TIMING_CONFIG_H */

/* end of file */

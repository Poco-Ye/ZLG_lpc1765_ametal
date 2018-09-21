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
 * \brief LPC5410X Timer��ʱ�����ܵ��û������ļ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_TIMER_TIMING_H
#define __AMDR_HWCONFIG_TIMER_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/** \brief Timer0��ʱ�������豸 */
extern amdr_timer_timing_dev_t           g_timer0_timing_dev;

/** \brief Timer0��ʱ�����ܵ��豸��Ϣ */
extern const amdr_timer_timing_devinfo_t g_timer0_timing_devinfo;

/**
 * \brief Timer0��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer0_timing_init(void);

/**
 * \brief ���Timer0��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer0_timing_deinit(void);

/** \brief Timer1��ʱ�����ܵ��豸��Ϣ */
extern amdr_timer_timing_dev_t           g_timer1_timing_dev;

/** \brief Timer1��ʱ�������豸 */
extern const amdr_timer_timing_devinfo_t g_timer1_timing_devinfo;

/**
 * \brief Timer1��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer1_timing_init(void);

/**
 * \brief ���Timer1��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer1_timing_deinit(void);


/** \brief Timer2��ʱ�����ܵ��豸��Ϣ */
extern amdr_timer_timing_dev_t           g_timer2_timing_dev;

/** \brief Timer2��ʱ�������豸 */
extern const amdr_timer_timing_devinfo_t g_timer2_timing_devinfo;

/**
 * \brief Timer2��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer2_timing_init(void);

/**
 * \brief ���Timer2��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer2_timing_deinit(void);


/** \brief Timer3��ʱ�����ܵ��豸��Ϣ */
extern amdr_timer_timing_dev_t           g_timer3_timing_dev;

/** \brief Timer3��ʱ�������豸 */
extern const amdr_timer_timing_devinfo_t g_timer3_timing_devinfo;

/**
 * \brief Timer3��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer3_timing_init(void);

/**
 * \brief ���Timer3��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer3_timing_deinit(void);


/** \brief Timer4��ʱ�����ܵ��豸��Ϣ */
extern amdr_timer_timing_dev_t           g_timer4_timing_dev;

/** \brief Timer4��ʱ�������豸 */
extern const amdr_timer_timing_devinfo_t g_timer4_timing_devinfo;

/**
 * \brief Timer4��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer4_timing_init(void);

/**
 * \brief ���Timer4��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_timer4_timing_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_TIMER_TIMING_H */

/* end of file */

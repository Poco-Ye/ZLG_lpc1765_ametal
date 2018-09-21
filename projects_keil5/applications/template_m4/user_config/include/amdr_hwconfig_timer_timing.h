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
 * \brief LPC5410X Timer定时器功能的用户配置文件
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

/** \brief Timer0定时器功能设备 */
extern amdr_timer_timing_dev_t           g_timer0_timing_dev;

/** \brief Timer0定时器功能的设备信息 */
extern const amdr_timer_timing_devinfo_t g_timer0_timing_devinfo;

/**
 * \brief Timer0定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer0_timing_init(void);

/**
 * \brief 解除Timer0定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer0_timing_deinit(void);

/** \brief Timer1定时器功能的设备信息 */
extern amdr_timer_timing_dev_t           g_timer1_timing_dev;

/** \brief Timer1定时器功能设备 */
extern const amdr_timer_timing_devinfo_t g_timer1_timing_devinfo;

/**
 * \brief Timer1定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer1_timing_init(void);

/**
 * \brief 解除Timer1定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer1_timing_deinit(void);


/** \brief Timer2定时器功能的设备信息 */
extern amdr_timer_timing_dev_t           g_timer2_timing_dev;

/** \brief Timer2定时器功能设备 */
extern const amdr_timer_timing_devinfo_t g_timer2_timing_devinfo;

/**
 * \brief Timer2定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer2_timing_init(void);

/**
 * \brief 解除Timer2定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer2_timing_deinit(void);


/** \brief Timer3定时器功能的设备信息 */
extern amdr_timer_timing_dev_t           g_timer3_timing_dev;

/** \brief Timer3定时器功能设备 */
extern const amdr_timer_timing_devinfo_t g_timer3_timing_devinfo;

/**
 * \brief Timer3定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer3_timing_init(void);

/**
 * \brief 解除Timer3定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer3_timing_deinit(void);


/** \brief Timer4定时器功能的设备信息 */
extern amdr_timer_timing_dev_t           g_timer4_timing_dev;

/** \brief Timer4定时器功能设备 */
extern const amdr_timer_timing_devinfo_t g_timer4_timing_devinfo;

/**
 * \brief Timer4定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer4_timing_init(void);

/**
 * \brief 解除Timer4定时器功能的平台初始化
 * \return 无
 */
void amhw_plfm_timer4_timing_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_TIMER_TIMING_H */

/* end of file */

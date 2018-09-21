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
 * \brief LPC5410X SCT PWM功能用户配置文件
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_SCT_PWM_H
#define __AMDR_HWCONFIG_SCT_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/** \brief SCT0 PWM功能的设备信息 */
extern amdr_sct_pwm_dev_t            g_sct0_pwm_dev;

/** \brief SCT0 PWM功能设备 */
extern const amdr_sct_pwm_devinfo_t  g_sct0_pwm_devinfo;

/**
 * \brief SCT0 PWM功能的平台初始化
 * \return 无
 */
void amhw_plfm_sct0_pwm_init(void);

/**
 * \brief 解除SCT0 PWM功能的平台初始化
 * \return 无
 */
void amhw_plfm_sct0_pwm_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_SCT_PWM_H */

/* end of file */

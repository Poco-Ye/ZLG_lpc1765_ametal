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
 * \brief LPC5410X UTICK 用户配置文件
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-12  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_UTICK_H
#define __AMDR_HWCONFIG_UTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/** \brief UTICK设备信息 */
extern amdr_utick_dev_t            g_utick_dev;

/** \brief UTICK设备 */
extern const amdr_utick_devinfo_t  g_utick_devinfo;

/**
 * \brief UTICK平台初始化
 * \return 无
 */
void amhw_plfm_utick_init(void);

/**
 * \brief 解除UTICK平台初始化
 * \return 无
 */
void amhw_plfm_utick_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_UTICK_H */

/* end of file */

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
 * \brief LPC5410X MRT 定时器功能用户配置
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_MRT_H
#define __AMDR_HWCONFIG_MRT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \brief MRT平台初始化
 * \return 无
 */
void amhw_plfm_mrt_init(void);

/**
 * \brief 解除MRT平台初始化
 * \return 无
 */
void amhw_plfm_mrt_deinit(void);

/** \brief MRT设备 */
extern amdr_mrt_dev_t           g_mrt_dev;

/** \brief MRT设备信息 */
extern const amdr_mrt_devinfo_t g_mrt_devinfo;

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_MRT_H */

/* end of file */

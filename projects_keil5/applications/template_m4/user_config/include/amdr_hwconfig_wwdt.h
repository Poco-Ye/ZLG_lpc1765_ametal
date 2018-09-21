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
 * \brief LPC5410X WWDT 用户配置头文件
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_WWDT_H
#define __AMDR_HWCONFIG_WWDT_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief WWDT 平台初始化。
 * \return 无.
 */
void amhw_plfm_wwdt_init(void);

/**
 * \brief 解除 WWDT平台初始化
 * \return 无.
 */
void amhw_plfm_wwdt_deinit(void);

/** \brief WWDT 设备信息 */
extern const amdr_wwdt_devinfo_t  g_wwdt_devinfo;

/** \brief WWDT 设备 */
extern amdr_wwdt_dev_t            g_wwdt_dev;

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_WWDT_H */

/* end of file */

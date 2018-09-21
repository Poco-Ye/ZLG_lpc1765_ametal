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
 * \brief LPC5410X 中断用户配置头文件。
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-29  hbt, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_INT_H
#define __AMDR_HWCONFIG_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/** \brief 中断设备信息 */
extern const amdr_int_devinfo_t g_int_devinfo; 

/** \brief 中断设备 */
extern amdr_int_dev_t           g_int_dev;

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_INT_H */

/* end of file */

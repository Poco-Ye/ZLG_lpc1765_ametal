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
 * \brief LPC5410X FIFO用户配置文件
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_FIFO_H
#define __AMDR_HWCONFIG_FIFO_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief FIFO平台初始化
 * \return 无
 */
void amhw_plfm_fifo_init(void);

/**
 * \brief 解除FIFO平台初始化
 * \return 无
 */
void amhw_plfm_fifo_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_FIFO_H */

/* end of file */

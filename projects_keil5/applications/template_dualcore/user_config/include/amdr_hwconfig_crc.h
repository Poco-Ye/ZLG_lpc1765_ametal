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
 * \brief LPC5410X CRC用户配置文件
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_HWCONFIG_CRC_H
#define __AMDR_HWCONFIG_CRC_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief CRC平台初始化
 * \return 无
 */
void amhw_plfm_crc_init(void);

/**
 * \brief 解除CRC平台初始化
 * \return 无
 */
void amhw_plfm_crc_deinit(void);

/** \brief CRC设备信息 */
extern const amdr_crc_devinfo_t  g_crc_devinfo;

/** \brief CRC设备     */
extern amdr_crc_dev_t            g_crc_dev;

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_CRC_H */

/* end of file */

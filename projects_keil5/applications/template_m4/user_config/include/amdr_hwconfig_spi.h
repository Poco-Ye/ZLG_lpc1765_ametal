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
 * \brief LPC5410X SPI用户配置头文件 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  jon, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_SPI_H
#define __AMDR_HWCONFIG_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

extern const struct amdr_spi_devinfo g_spi0_devinfo;      /**< \brief SPI0 设备信息 */
extern amdr_spi_dev_t                g_spi0_dev;          /**< \brief SPI0 设备     */

/**
 * \brief SPI0 平台初始化
 * \return 无
 */
void amhw_plfm_spi0_init(void);

/**
 * \brief 解除SPI0 平台初始化
 * \return 无
 */
void amhw_plfm_spi0_deinit(void);


extern const struct amdr_spi_devinfo g_spi1_devinfo;      /**< \brief SPI1 设备信息 */
extern amdr_spi_dev_t                g_spi1_dev;          /**< \brief SPI1 设备     */

/**
 * \brief SPI1 平台初始化
 * \return 无
 */
void amhw_plfm_spi1_init(void);

/**
 * \brief SPI1 平台初始化
 * \return 无
 */
void amhw_plfm_spi1_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_SPI_H */

/* end of file */

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
 * \brief LPC5410X I2C 用户配置头文件
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  jon, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_I2C_H
#define __AMDR_HWCONFIG_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
    
/**
 * \brief I2C0 平台初始化
 * \return 无
 */
void amhw_plfm_i2c0_init(void);

/**
 * \brief 解除I2C0 平台初始化
 * \return 无
 */
void amhw_plfm_i2c0_deinit(void);

extern const struct amdr_i2c_devinfo g_i2c0_devinfo;    /**< \brief I2C0 设备信息 */
extern amdr_i2c_dev_t                g_i2c0_dev;        /**< \brief I2C0 设备     */


/**
 * \brief I2C1 平台初始化
 * \return 无
 */
void amhw_plfm_i2c1_init(void);

/**
 * \brief 解除I2C1 平台初始化
 * \return 无
 */
void amhw_plfm_i2c1_deinit(void);

extern const struct amdr_i2c_devinfo g_i2c1_devinfo;    /**< \brief I2C1 设备信息 */
extern amdr_i2c_dev_t g_i2c1_dev;                       /**< \brief I2C1 设备     */

/**
 * \brief I2C2 平台初始化
 * \return 无
 */
void amhw_plfm_i2c2_init(void);

/**
 * \brief 解除I2C2 平台初始化
 * \return 无
 */
void amhw_plfm_i2c2_deinit(void);

extern const struct amdr_i2c_devinfo g_i2c2_devinfo;    /**< \brief I2C2 设备信息 */
extern amdr_i2c_dev_t g_i2c2_dev;                       /**< \brief I2C2 设备     */

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_I2C_H */

/* end of file */

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
 * \brief LPC5410X USART用户配置头文件
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  hbt, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_USART_H
#define __AMDR_HWCONFIG_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
    
/**
 * \brief USART0平台初始化。
 * \return 无。
 */
void amhw_plfm_usart0_init(void);

/**
 * \brief 解除USART0平台初始化。
 * \return 无。
 */
void amhw_plfm_usart0_deinit(void);

extern const amdr_usart_devinfo_t g_usart0_devinfo; /**< \brief USART0设备信息 */
extern amdr_usart_dev_t           g_usart0_dev;     /**< \brief USART0设备     */


/**
 * \brief USART1平台初始化
 * \return 无
 */
void amhw_plfm_usart1_init(void);

/**
 * \brief 解除USART1平台初始化
 * \return 无
 */
void amh_platform_usart1_deinit(void);

extern const amdr_usart_devinfo_t g_usart1_devinfo; /**< \brief USART1设备信息 */
extern amdr_usart_dev_t           g_usart1_dev;     /**< \brief USART1设备     */


/**
 * \brief USART2平台初始化
 * \return 无
 */
void amhw_plfm_usart2_init(void);

/**
 * \brief 解除USART2平台初始化
 * \return 无
 */
void amh_platform_usart2_deinit(void);

extern const amdr_usart_devinfo_t g_usart2_devinfo; /**< \brief USART2 设备信息 */
extern amdr_usart_dev_t           g_usart2_dev;     /**< \brief USART2设备      */


/**
 * \brief  USART3平台初始化
 * \return 无
 */
void amhw_plfm_usart3_init(void);

/**
 * \brief  解除USART3平台初始化
 * \return 无
 */
void amh_platform_usart3_deinit(void);

extern const amdr_usart_devinfo_t g_usart3_devinfo; /**< \brief USART3设备信息 */
extern amdr_usart_dev_t           g_usart3_dev;     /**< \brief USART3设备     */

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_USART_H */

/* end of file */

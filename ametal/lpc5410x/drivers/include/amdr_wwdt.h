/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief  WWDT驱动，服务WWDT标准接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-07  fft, first implementation.
 * \endinternal
 */

#ifndef __AMDR_WWDT_H
#define __AMDR_WWDT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_wdt.h"
#include "amhw_wwdt.h"
    
/** 
 * \addtogroup amdr_if_wwdt
 * \copydoc amdr_wwdt.h
 * @{
 */

/**
 * \brief WWDT 设备信息结构体
 */
typedef struct amdr_wwdt_devinfo {
    amhw_wwdt_t *p_hw_wwdt;             /**< \brief 指向WWDT寄存器块的结构体指针 */
} amdr_wwdt_devinfo_t;
    
/**
 * \brief WWDT 设备结构体
 */
typedef struct amdr_wwdt_dev {

    am_wdt_serv_t              wdt_serv;   /**< \brief WWDT标准服务         */
    const amdr_wwdt_devinfo_t *p_devinfo;  /**< \brief 指向WWDT设备信息的指针 */
} amdr_wwdt_dev_t;

/**
 * \brief 初始化WWDT
 *
 * \param[in] p_dev     : 指向WWDT设备
 * \param[in] p_devinfo : 指向WWDT设备信息
 *
 * \return WWDT标准服务操作句柄。如果为 NULL，表明初始化失败。
 */
am_wdt_handle_t amdr_wwdt_init(amdr_wwdt_dev_t           *p_dev,
                               const amdr_wwdt_devinfo_t *p_devinfo);

/**
 * \brief 解除WWDT初始化
 * \param[in] p_dev : 指向WWDT设备
 * \return  无
 */
void amdr_wwdt_deinit(amdr_wwdt_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_WWDT_H */

/* end of file */

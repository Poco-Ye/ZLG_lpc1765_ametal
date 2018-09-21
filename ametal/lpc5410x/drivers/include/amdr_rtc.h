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
 * \brief  RTC驱动，服务RTC标准接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-27  fft, first implementation.
 * \endinternal
 */

#ifndef __AMDR_RTC_H
#define __AMDR_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_rtc.h"
#include "amhw_rtc.h"


/**
 * \addtogroup amdr_if_rtc
 * \copydoc amdr_rtc.h
 * @{
 */

/**
 * \brief RTC 设备信息结构体
 */
typedef struct amdr_rtc_devinfo {
    amhw_rtc_t  *p_hw_rtc;                  /**< \brief 指向RTC寄存器块的结构体指针 */
} amdr_rtc_devinfo_t;
    
/**
 * \brief RTC 设备结构体
 */
typedef struct amdr_rtc_dev {
    am_rtc_serv_t             rtc_serv;     /**< \brief RTC标准服务         */
    const amdr_rtc_devinfo_t *p_devinfo;    /**< \brief 指向RTC设备信息的指针 */
} amdr_rtc_dev_t;

/**
 * \brief 初始化RTC
 *
 * \param[in] p_dev     : 指向RTC设备
 * \param[in] p_devinfo : 指向RTC设备信息
 *
 * \return RTC标准服务操作句柄。如果为 NULL，表明初始化失败。
 */
am_rtc_handle_t amdr_rtc_init(amdr_rtc_dev_t           *p_dev,
                              const amdr_rtc_devinfo_t *p_devinfo);

/**
 * \brief 解除RTC初始化
 * \param[in] p_dev : 指向RTC设备
 * \return  无
 */
void amdr_rtc_deinit(amdr_rtc_dev_t *p_dev);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

/* end of file */

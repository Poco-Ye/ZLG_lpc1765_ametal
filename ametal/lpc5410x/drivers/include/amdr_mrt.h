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
 * \brief MRT驱动，服务Timer标准接口
 *
 * 该驱动实现了MRT的定时功能
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_MRT_H
#define __AMDR_MRT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_mrt.h"

/**
 * \addtogroup amdr_if_mrt
 * \copydoc amdr_mrt.h
 * @{
 */

/**
 * \brief MRT设备信息结构体
 */
typedef struct amdr_mrt_devinfo {
    amhw_mrt_t      *p_hw_mrt;      /**< \brief 指向MRT寄存器块的指针         */
    uint8_t          inum;          /**< \brief MRT中断号                     */
    uint8_t          channel_nums;  /**< \brief 支持的通道数，最大为4         */
} amdr_mrt_devinfo_t;

/**
 * \brief MRT设备
 */
typedef struct amdr_mrt_dev {

    am_timer_serv_t   timer_serv;      /**< \brief 标准定时(Timer)服务        */

    struct {
        void (*pfn_callback)(void *);  /**< \brief 回调函数                   */
        void *p_arg;                   /**< \brief 回调函数的用户参数         */
    } callback_info[AMHW_MRT_CHANNELS_NUM]; /**< \brief 回调函数信息数组      */
        
    /** \brief 指向MRT设备信息常量的指针 */
    const amdr_mrt_devinfo_t  *p_devinfo; 

} amdr_mrt_dev_t;

/**
 * \brief 初始化MRT为定时功能
 *
 * \param[in] p_dev     : 指向MRT设备的指针
 * \param[in] p_devinfo : 指向MRT设备信息常量的指针
 *
 * \return Timer标准服务操作句柄，值为NULL时表明初始化失败
 */
am_timer_handle_t amdr_mrt_init(amdr_mrt_dev_t            *p_dev,
                                const amdr_mrt_devinfo_t  *p_devinfo);

/**
 * \brief 不使用MRT时，解初始化MRT，释放相关资源
 * \param[in] p_dev : 指向MRT设备的指针
 * \return 无
 */
void amdr_mrt_deinit(amdr_mrt_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_MRT_H */

/* end of file */

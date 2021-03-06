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
 * \brief RIT驱动，服务Timer标准接口
 *
 * 该驱动实现了RIT的定时功能
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_RIT_H
#define __AMDR_RIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_rit.h"

/**
 * \addtogroup amdr_if_rit
 * \copydoc amdr_rit.h
 * @{
 */

/**
 * \brief RIT设备信息结构体
 */
typedef struct amdr_rit_devinfo {
    amhw_rit_t      *p_hw_rit;      /**< \brief 指向RIT寄存器块的指针         */
    uint8_t          inum;          /**< \brief RIT中断号                     */
} amdr_rit_devinfo_t;
    
/**
 * \brief RIT设备
 */
typedef struct amdr_rit_dev {

    am_timer_serv_t   timer_serv;      /**< \brief 标准定时(Timer)服务        */

    struct {
        void (*pfn_callback)(void *);  /**< \brief 回调函数                   */
        void *p_arg;                   /**< \brief 回调函数的用户参数         */
    } callback_info[1];    /**< \brief 回调函数信息数组，仅支持一个通道       */
    
    /** \brief 指向RIT设备信息常量的指针 */
    const amdr_rit_devinfo_t  *p_devinfo; 

} amdr_rit_dev_t;

/**
 * \brief 初始化RIT为定时功能
 *
 * \param[in] p_dev     : 指向RIT设备的指针
 * \param[in] p_devinfo : 指向RIT设备信息常量的指针
 *
 * \return Timer标准服务操作句柄，值为NULL时表明初始化失败
 */
am_timer_handle_t amdr_rit_init(amdr_rit_dev_t            *p_dev,
                                const amdr_rit_devinfo_t  *p_devinfo);

/**
 * \brief 不使用RIT时，解初始化RIT，释放相关资源
 * \param[in] p_dev : 指向RIT设备的指针
 * \return 无
 */
void amdr_rit_deinit(amdr_rit_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_RIT_H */

/* end of file */

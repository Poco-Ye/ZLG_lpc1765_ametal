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
 * \brief 定时器（STD Timer）驱动，服务Timer标准接口
 *
 * 1. 定时器支持提供如下三种标准服务，本驱动提供的是服务Timer标准服务的驱动。
 *     - 定时
 *     - PWM输出
 *     - 捕获
 * 2. 在本驱动中，四个匹配寄存器使用如下：
 *     - 匹配寄存器0用于保存定时周期值，产生周期性中断
 *     - 匹配寄存器1未使用
 *     - 匹配寄存器2未使用
 *     - 匹配寄存器3未使用
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_TIMER_TIMING_H
#define __AMDR_TIMER_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_timer.h"

/**
 * \addtogroup amdr_if_timer_timing
 * \copydoc amdr_timer_timing.h
 * @{
 */

/**
 * \brief 定时器定时功能相关的设备信息
 */
typedef struct amdr_timer_timing_devinfo {
    amhw_timer_t    *p_hw_timer; /**< \brief 指向Standard Timer寄存器块的指针  */
    uint8_t          inum;       /**< \brief 定时器中断号                      */
} amdr_timer_timing_devinfo_t;
    
/**
 * \brief 定时器定时功能设备结构体定义
 */
typedef struct amdr_timer_timing_dev {

    am_timer_serv_t   timer_serv;       /**< \brief 标准定时(Timer)服务       */
    
    struct {    
        void (*pfn_callback)(void *);   /**< \brief 回调函数                  */
        void *p_arg;                    /**< \brief 回调函数的用户参数        */
    } callback_info[1];                 /**< \brief 仅支持单通道              */
    
    /** \brief 指向定时器(定时功能)设备信息常量的指针 */
    const amdr_timer_timing_devinfo_t  *p_devinfo; 

} amdr_timer_timing_dev_t;

/**
 * \brief 初始化定时器为定时功能
 *
 * \param[in] p_dev     : 指向定时器(定时功能)设备指针
 * \param[in] p_devinfo : 指向定时器(定时功能)设备信息常量的指针
 *
 * \return Timer标准服务操作句柄，值为NULL时表明初始化失败
 */
am_timer_handle_t amdr_timer_timing_init(amdr_timer_timing_dev_t            *p_dev,
                                         const amdr_timer_timing_devinfo_t  *p_devinfo);

/**
 * \brief 不使用定时器的定时功能时，解初始化定时器的定时功能，释放相关资源
 * \param[in] p_dev : 指向定时器(定时功能)设备指针
 * \return 无
 */
void amdr_timer_timing_deinit(amdr_timer_timing_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_TIMER_TIMING_H */

/* end of file */

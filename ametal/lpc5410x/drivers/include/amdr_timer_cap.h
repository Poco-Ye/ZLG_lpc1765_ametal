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
 * \brief 定时器（STD Timer）驱动，服务CAP标准接口
 *
 * 1. 定时器支持提供如下三种标准服务，本驱动提供的是服务CAP标准服务的驱动。
 *     - 定时
 *     - PWM输出
 *     - 捕获
 * 2. 在本驱动中，四个捕获寄存器使用如下：
 *     - 捕获寄存器0用于捕获输入通道0
 *     - 捕获寄存器1用于捕获输入通道0
 *     - 捕获寄存器2用于捕获输入通道0
 *     - 捕获寄存器3用于捕获输入通道0
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_TIMER_CAP_H
#define __AMDR_TIMER_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "amhw_timer.h"

/**
 * \addtogroup amdr_if_timer_cap
 * \copydoc amdr_timer_cap.h
 * @{
 */

/**
 * \brief 定时器捕获功能相关的GPIO信息
 */
typedef struct amdr_timer_cap_ioinfo {
    uint32_t gpio;           /**< \brief 对应的GPIO管脚                       */
    uint32_t func;           /**< \brief 为捕获功能时的GPIO功能设置           */
    uint32_t dfunc;          /**< \brief 禁能管脚捕获功能时的默认GPIO功能设置 */
} amdr_timer_cap_ioinfo_t;

/**
 * \brief 定时器捕获功能相关的设备信息
 */
typedef struct amdr_timer_cap_devinfo {
    amhw_timer_t            *p_hw_timer;   /**< \brief 指向Standard Timer寄存器块的指针 */
    uint8_t                  inum;         /**< \brief 定时器中断号                     */
    uint8_t                  channels_num; /**< \brief 使用的通道数，最大为4            */
    amdr_timer_cap_ioinfo_t *p_ioinfo;     /**< \brief 指向捕获管脚信息结构体           */
} amdr_timer_cap_devinfo_t;
 
/**
 * \brief 定时器捕获功能设备结构体
 */
typedef struct amdr_timer_cap_dev {
    am_cap_serv_t           cap_serv;       /**< \brief 标准CAP服务           */
    
    struct {   
        am_cap_callback_t   callback_func;  /**< \brief 回调函数              */
        void               *p_arg;          /**< \brief 回调函数的用户参数    */
    }callback_info[4];                      /**< \brief 存储最大4通道的回调函数信息 */
    
    /** \brief 指向定时器捕获功能设备信息常量的指针 */
    const amdr_timer_cap_devinfo_t  *p_devinfo; 

} amdr_timer_cap_dev_t;

/**
 * \brief 初始化定时器为捕获功能
 *
 * \param[in] p_dev     : 指向定时器捕获功能设备的指针
 * \param[in] p_devinfo : 指向定时器捕获功能设备信息常量的指针
 *
 * \return CAP标准服务操作句柄，值为NULL时表明初始化失败
 */
am_cap_handle_t amdr_timer_cap_init(amdr_timer_cap_dev_t           *p_dev,
                                    const amdr_timer_cap_devinfo_t *p_devinfo);

/**
 * \brief 不使用定时器捕获功能时，解初始化定时器捕获功能，释放相关资源
 * \param[in] p_dev : 指向定时器捕获功能设备的指针
 * \return 无
 */
void amdr_timer_cap_deinit(amdr_timer_cap_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_TIMER_CAP_H */

/* end of file */

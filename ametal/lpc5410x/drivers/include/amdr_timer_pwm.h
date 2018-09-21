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
 * \brief 定时器（STD Timer）驱动，服务PWM标准接口
 *
 * 1. 定时器支持提供如下三种标准服务，本驱动提供的是服务PWM标准服务的驱动。
 *     - 定时
 *     - PWM输出
 *     - 捕获
 * 2. 在本驱动中，四个匹配寄存器使用如下：
 *        - 匹配寄存器3用于产生PWM的周期 
 *        - 匹配寄存器0用于产生PWM输出通道0的脉宽 
 *        - 匹配寄存器1用于产生PWM输出通道1的脉宽 
 *        - 匹配寄存器2用于产生PWM输出通道2的脉宽 
 *
 * \note 一个定时器输出的所有PWM共享周期值，也就是说，该定时器输出的所有PWM周期
 *       相同，频率相同
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_TIMER_PWM_H
#define __AMDR_TIMER_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "amhw_timer.h"

/**
 * \addtogroup amdr_if_timer_pwm
 * \copydoc amdr_timer_pwm.h
 * @{
 */

/**
 * \brief 定时器PWM功能相关的GPIO信息
 */
typedef struct amdr_timer_pwm_ioinfo {
    uint32_t gpio;                          /**< \brief 对应的GPIO管脚                      */
    uint32_t func;                          /**< \brief 为PWM功能时的GPIO功能设置           */
    uint32_t dfunc;                         /**< \brief 禁能管脚PWM功能时的默认GPIO功能设置 */
} amdr_timer_pwm_ioinfo_t;

/**
 * \brief 定时器PWM功能相关的设备信息
 */
typedef struct amdr_timer_pwm_devinfo {
    amhw_timer_t            *p_hw_timer;    /**< \brief 指向Standard Timer寄存器块的指针 */
    uint8_t                  channels_num;  /**< \brief 使用的通道数，最大为4            */
    amdr_timer_pwm_ioinfo_t *p_ioinfo;      /**< \brief 指向PWM管脚信息结构体            */
} amdr_timer_pwm_devinfo_t;
 
/**
 * \brief 定时器PWM功能设备结构体
 */
typedef struct amdr_timer_pwm_dev {
    
    /** \brief 标准PWM服务                         */
    am_pwm_serv_t                    pwm_serv; 
    
    /** \brief 指向定时器PWM功能设备信息常量的指针 */
    const amdr_timer_pwm_devinfo_t  *p_devinfo; 

} amdr_timer_pwm_dev_t;

/**
 * \brief 初始化定时器为PWM输出功能
 *
 * \param[in] p_dev     : 指向定时器PWM输出功能设备的指针
 * \param[in] p_devinfo : 指向定时器PWM输出功能设备信息常量的指针
 *
 * \return PWM标准服务操作句柄，值为NULL时表明初始化失败
 */
am_pwm_handle_t amdr_timer_pwm_init(amdr_timer_pwm_dev_t           *p_dev,
                                    const amdr_timer_pwm_devinfo_t *p_devinfo);

/**
 * \brief 不使用定时器的PWM输出功能时，解初始化定时器的PWM输出功能，释放相关资源
 * \param[in] p_dev : 指向定时器PWM输出功能设备的指针
 * \return 无
 */
void amdr_timer_pwm_deinit(amdr_timer_pwm_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_TIMER_PWM_H */

/* end of file */

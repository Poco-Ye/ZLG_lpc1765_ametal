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
 * \brief SCT驱动，服务PWM标准接口
 *
 * 1. SCT支持提供如下三种标准服务，本驱动提供的是服务PWM标准服务的驱动。
 *     - 定时
 *     - PWM输出
 *     - 捕获
 * 2. 在本驱动中，SCT相关资源使用如下：
 *    - 匹配寄存器0用于产生PWM周期，与事件0相关联
 *    - 匹配寄存器1用于产生PWM输出通道0(SCT_OUT0)的脉宽 
 *    - 匹配寄存器2用于产生PWM输出通道1(SCT_OUT1)的脉宽 
 *    - 匹配寄存器3用于产生PWM输出通道2(SCT_OUT2)的脉宽 
 *    - 匹配寄存器4用于产生PWM输出通道3(SCT_OUT3)的脉宽 
 *    - 匹配寄存器5用于产生PWM输出通道4(SCT_OUT4)的脉宽 
 *    - 匹配寄存器6用于产生PWM输出通道5(SCT_OUT5)的脉宽 
 *    - 匹配寄存器7用于产生PWM输出通道6(SCT_OUT6)的脉宽 
 *    - 匹配寄存器8用于产生PWM输出通道7(SCT_OUT7)的脉宽 
 *
 * \note 一个SCT输出的所有PWM共享周期值，也就是说，该SCT输出的所有PWM周期相同，
 *       频率相同
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */


#ifndef __AMDR_SCT_PWM_H
#define __AMDR_SCT_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "amhw_sct.h"

/**
 * \addtogroup amdr_if_sct_pwm
 * \copydoc amdr_sct_pwm.h
 * @{
 */

/**
 * \brief SCT PWM输出功能相关的GPIO信息
 */
typedef struct amdr_sct_pwm_ioinfo {
    uint32_t gpio;              /**< \brief PWM 所用的GPIO                    */
    uint32_t func;              /**< \brief PWM功能的GPIO功能设置值           */
    uint32_t dfunc;             /**< \brief 禁能PWM模式后，默认GPIO功能设置值 */
} amdr_sct_pwm_ioinfo_t;

/**
 * \brief SCT PWM输出功能相关的设备信息
 */
typedef struct amdr_sct_pwm_devinfo {
    amhw_sct_t            *p_hw_sct;     /**< \brief 指向SCT寄存器块的指针    */
    uint8_t                channels_num; /**< \brief 使用的通道数，最大为8    */
    amdr_sct_pwm_ioinfo_t *p_ioinfo;     /**< \brief 指向PWM输出管脚信息结构体*/
} amdr_sct_pwm_devinfo_t;
 
/**
 * \brief SCT PWM输出功能设备结构体
 */
typedef struct amdr_sct_pwm_dev {
    
    am_pwm_serv_t                 pwm_serv; /**< \brief 标准PWM服务           */
    
    /** \brief 指向SCT(PWM输出功能)设备信息常量的指针 */
    const amdr_sct_pwm_devinfo_t  *p_devinfo; 

} amdr_sct_pwm_dev_t;

/**
 * \brief 初始化SCT为PWM输出功能
 *
 * \param[in] p_dev     : 指向SCT(PWM输出功能)设备的指针
 * \param[in] p_devinfo : 指向SCT(PWM输出功能)设备信息常量的指针
 *
 * \return PWM标准服务操作句柄，值为NULL时表明初始化失败
 */
am_pwm_handle_t amdr_sct_pwm_init(amdr_sct_pwm_dev_t           *p_dev,
                                  const amdr_sct_pwm_devinfo_t *p_devinfo);

/**
 * \brief 不使用SCT PWM输出功能时，解初始化SCT PWM输出功能，释放相关资源
 * \param[in] p_dev : 指向SCT(PWM输出功能)设备的指针
 * \return 无
 */
void amhw_sct_pwm_deinit(amdr_sct_pwm_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SCT_PWM_H */

/* end of file */

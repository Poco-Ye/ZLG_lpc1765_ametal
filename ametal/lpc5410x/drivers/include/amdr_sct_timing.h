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
 * \brief SCT驱动，服务Timer标准接口
 *
 * 1. SCT支持提供如下三种标准服务，本驱动提供的是服务Timer标准服务的驱动。
 *     - 定时
 *     - PWM输出
 *     - 捕获
 * 2. 在本驱动中，SCT相关资源使用如下：
 *    - 匹配寄存器0用于保存定时周期值，与事件0相关联，以产生中断。
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-14  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SCT_TIMING_H
#define __AMDR_SCT_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_sct.h"

/**
 * \addtogroup amdr_if_sct_timing
 * \copydoc amdr_sct_timing.h
 * @{
 */

/** \brief SCT运行在1个32位定时器模式, 仅能提供1个定时器通道    */
#define AMDR_SCT_TIMING_1_32BIT      1

/** \brief SCT运行在2个16位定时器模式, 能提供2个定时器通道      */
#define AMDR_SCT_TIMING_2_16BIT      2

/**
 * \brief SCT定时功能相关的设备信息
 */
typedef struct amdr_sct_timing_devinfo {
    amhw_sct_t   *p_hw_sct;    /**< \brief 指向SCT寄存器块的指针              */
    uint8_t       flag;        /**< \brief SCT配置标志(1-32bit 或者 2-16bit)  */
    uint8_t       inum;        /**< \brief SCT中断号                          */
} amdr_sct_timing_devinfo_t;
    
/**
 * \brief SCT定时功能设备
 */
typedef struct amdr_sct_timing_dev {

    am_timer_serv_t   timer_serv;     /**< \brief 标准定时(Timer)服务         */

    struct {
        void (*pfn_callback)(void *); /**< \brief 回调函数                    */
        void *p_arg;                  /**< \brief 回调函数的用户参数          */
    } callback_info[2];               /**< \brief 最大支持2通道(2-16bit定时器)*/
    
    /** \brief 指向SCT(定时功能)设备信息常量的指针 */
    const amdr_sct_timing_devinfo_t  *p_devinfo; 

} amdr_sct_timing_dev_t;

/**
 * \brief 初始化SCT为定时功能
 *
 * \param[in] p_dev     : 指向SCT(定时功能)设备的指针
 * \param[in] p_devinfo : 指向SCT(定时功能)设备信息常量的指针
 *
 * \return Timer标准服务操作句柄，值为NULL时表明初始化失败
 */
am_timer_handle_t amdr_sct_timing_init(amdr_sct_timing_dev_t            *p_dev,
                                       const amdr_sct_timing_devinfo_t  *p_devinfo);

/**
 * \brief 不使用SCT定时功能时，解初始化SCT定时功能，释放相关资源
 * \param[in] p_dev : 指向SCT(定时功能)设备的指针
 * \return 无
 */
void amdr_sct_timing_deinit(amdr_sct_timing_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SCT_TIMING_H */

/* end of file */

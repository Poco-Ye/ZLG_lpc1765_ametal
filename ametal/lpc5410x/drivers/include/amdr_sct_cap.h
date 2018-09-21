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
 * \brief SCT驱动，服务CAP标准接口
 *
 * 1. SCT支持提供如下三种标准服务，本驱动提供的是服务CAP标准服务的驱动。
 *     - 定时
 *     - PWM输出
 *     - 捕获
 * 2. 在本驱动中，SCT相关资源使用如下：
 *    - 捕获通道0用于捕获SCT输入0，与事件0相关联，以产生中断
 *    - 捕获通道1用于捕获SCT输入1，与事件1相关联，以产生中断
 *    - 捕获通道2用于捕获SCT输入2，与事件2相关联，以产生中断
 *    - 捕获通道3用于捕获SCT输入3，与事件3相关联，以产生中断
 *    - 捕获通道4用于捕获SCT输入4，与事件4相关联，以产生中断
 *    - 捕获通道5用于捕获SCT输入5，与事件5相关联，以产生中断
 *    - 捕获通道6用于捕获SCT输入6，与事件6相关联，以产生中断
 *    - 捕获通道7用于捕获SCT输入7，与事件7相关联，以产生中断
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-14  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SCT_CAP_H
#define __AMDR_SCT_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "amhw_sct.h"

/**
 * \addtogroup amdr_if_sct_cap
 * \copydoc amdr_sct_cap.h
 * @{
 */

/**
 * \brief SCT捕获功能相关的GPIO信息，SCT捕获功能共有8个通道，通道6和通道7是内部信息
 *        不需要外部GPIO管脚
 */
typedef struct amdr_sct_cap_ioinfo {
    uint32_t gpio;           /**< \brief 对应的GPIO管脚                       */
    uint32_t func;           /**< \brief 为捕获功能时的GPIO功能设置           */
    uint32_t dfunc;          /**< \brief 禁能管脚捕获功能时的默认GPIO功能设置 */
} amdr_sct_cap_ioinfo_t;

/**
 * \brief SCT捕获功能相关的设备信息
 */
typedef struct amdr_sct_cap_devinfo {
    amhw_sct_t             *p_hw_sct;      /**< \brief 指向SCT寄存器块的指针  */
    uint8_t                 inum;          /**< \brief SCT对应的中断号        */
    uint8_t                 channels_num;  /**< \brief 使用的通道数，最大为8  */
    amdr_sct_cap_ioinfo_t  *p_ioinfo;      /**< \brief 指向捕获管脚信息结构体 */
} amdr_sct_cap_devinfo_t;

/**
 * \brief SCT捕获功能设备
 */
typedef struct amdr_sct_cap_dev {
    am_cap_serv_t          cap_serv;       /**< \brief 标准CAP服务            */

    struct {
        am_cap_callback_t  callback_func;  /**< \brief 回调函数                    */
        void              *p_arg;          /**< \brief 回调函数的用户参数          */
    } callback_info[8];                    /**< \brief 存储最大8通道的回调函数信息 */

    /** \brief 指向SCT(捕获功能)设备信息常量的指针 */
    const amdr_sct_cap_devinfo_t *p_devinfo;

} amdr_sct_cap_dev_t;

/**
 * \brief 初始化SCT为捕获功能
 *
 * \param[in] p_dev     : 指向SCT(捕获功能)设备的指针
 * \param[in] p_devinfo : 指向SCT(捕获功能)设备信息常量的指针
 *
 * \return CAP标准服务操作句柄，值为NULL时表明初始化失败
 */
am_cap_handle_t amdr_sct_cap_init(amdr_sct_cap_dev_t           *p_dev,
                                  const amdr_sct_cap_devinfo_t *p_devinfo);

/**
 * \brief 不使用SCT捕获功能时，解初始化SCT捕获功能，释放相关资源
 * \param[in] p_dev : 指向SCT(捕获功能)设备的指针
 * \return 无
 */
void amdr_sct_cap_deinit(amdr_sct_cap_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SCT_CAP_H */

/* end of file */

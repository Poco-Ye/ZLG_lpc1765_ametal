/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 消息邮件硬件操作接口
 *
 * 1. 提供了一个内核通信方法, 允许多个内核共享资源，并且通过一个简单的方式进行通信；
 * 2. 每个内核提供高达32个可通过用户定义中断，来操作另一个内核；
 * 3. 如果内核有效，可实现共享区域的互斥访问。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-08  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_MBOX_H
#define __AMHW_MBOX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_mbox
 * \copydoc amhw_mbox.h
 * @{
 */

#define AMHW_MBOX_CORE_NUM   2          /**< \brief 内核的数目 */

/**
 * \brief CPU ID定义
 * @{
 */

#define AMHW_MBOX_M0PLUS_ID  0          /**< \brief M0+内核的ID是 0  */
#define AMHW_MBOX_M4_ID      1          /**< \brief M4 内核的ID是 1  */
/** @} */
/**
 * \brief 消息邮箱的IRQ相关结构体
 */
typedef struct amhw_mbox_irq {
    __IO uint32_t  irq;        /**< \brief 消息邮箱数据         */
    __O  uint32_t  irq_set;    /**< \brief 置位消息邮箱数据     */
    __O  uint32_t  irq_clr;    /**< \brief 清除置位消息邮箱数据 */
    __I  uint32_t  reserved;   /**< \brief 保留 */
} amhw_mbox_irq_t;

/**
 * \brief 消息邮箱寄存器块结构体
 */
typedef struct amhw_mailbox {

    /** \brief 消息邮箱,  0 - M0+, 1 - M4 */
    amhw_mbox_irq_t  mbox[AMHW_MBOX_CORE_NUM];

    /** \brief 保留 */
    amhw_mbox_irq_t  reserved1[15 - AMHW_MBOX_CORE_NUM];
    __I  uint32_t    reserved2[2];   /**< \brief 保留         */
    __IO uint32_t    mutex;          /**< \brief 共享互斥变量 */
} amhw_mailbox_t;

/**
 * \brief 设定数值到消息邮箱
 *
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 * \param[in] cpu_id    : 内核ID
 * \param[in] value     : 设定的值
 *
 * \return    无
 */
am_static_inline
void amhw_mbox_val_set (amhw_mailbox_t *p_hw_mbox, uint32_t cpu_id, uint32_t value)
{
    p_hw_mbox->mbox[cpu_id].irq = value;
}

/**
 * \brief 置位消息邮箱数据位为1 
 *
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 * \param[in] cpu_id    : 内核ID
 * \param[in] bits_set  : 需要置1的数据位，对应的数据位置1该位数据有效，反之，无效
 *                        
 * \return    无
 *
 * \note  置位的数据位，通过消息邮箱发送到另一个内核
 */
am_static_inline
void amhw_mbox_val_bits_set (amhw_mailbox_t *p_hw_mbox,
                             uint32_t        cpu_id,
                             uint32_t        bits_set)
{
    p_hw_mbox->mbox[cpu_id].irq_set = bits_set;
}

/**
 * \brief 清除置位的消息邮箱数据位
 *
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 * \param[in] cpu_id    : 内核ID
 * \param[in] bits_clr  : 需要清除的数据位
 *                        
 * \return    无
 *
 * \note  清除的数据位，通过消息邮箱发送到另一个内核
 */
am_static_inline
void amhw_mbox_val_bits_clr (amhw_mailbox_t *p_hw_mbox,
                             uint32_t        cpu_id,
                             uint32_t        bits_clr)
{
    p_hw_mbox->mbox[cpu_id].irq_clr = bits_clr;
}

/**
 * \brief 获取消息邮箱的数据
 *
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 * \param[in] cpu_id    : 内核ID
 *
 * \return 消息邮箱的数据 
 */
am_static_inline
uint32_t amhw_mbox_val_get (amhw_mailbox_t *p_hw_mbox, uint32_t cpu_id)
{
    return p_hw_mbox->mbox[cpu_id].irq;
}

/**
 * \brief 获取MUTEX的状态
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 *
 * \retval  1 获取MUTEX
 * \retval  0 锁定
 */
am_static_inline
uint32_t amhw_mbox_mutex_get (amhw_mailbox_t *p_hw_mbox)
{
    return p_hw_mbox->mutex;
}

/**
 * \brief 置位MUTEX 状态
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 * \return    无
 *
 * \note   若置位MUTEX 状态，允许其他资源获取mutex
 */
am_static_inline
void amhw_mbox_mutex_set (amhw_mailbox_t *p_hw_mbox)
{
    p_hw_mbox->mutex = 1;
}

/**
 * \brief 进入Mutex区域,等待获取到Mutex.
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 * \return  无
 *
 * \note  amhw_mbox_mutex_take() 和 amhw_mbox_mutex_give() 必须成对出现
 */
void amhw_mbox_mutex_take(amhw_mailbox_t *p_hw_mbox);

/**
 * \brief 退出Mutex区域,置位MUTEX状态，允许其他资源获取mutex
 * \param[in] p_hw_mbox : 指向消息邮箱寄存器块的指针
 * \return    无
 *
 * \note  amhw_mbox_mutex_take() 和 amhw_mbox_mutex_give() 必须成对出现
 */
void amhw_mbox_mutex_give(amhw_mailbox_t *p_hw_mbox);

/**
 * @} amhw_if_mbox
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MBOX_H */

/* end of file */

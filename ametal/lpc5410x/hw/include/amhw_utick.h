/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site    http://www.zlg.cn/
* e-mail      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief UTICK(Micro-tick timer)操作接口
 * 
 * 1. 极度简单的定时器；
 * 2. 写值立即启动；
 * 3. 中断模式或软件查询模式。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_UTICK_H
#define __AMHW_UTICK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_utick
 * \copydoc amhw_utick.h
 * @{
 */
 
/**
 * \brief UTICK(Micro-tick timer)寄存器块结构体
 */
typedef struct amhw_utick {
    __IO uint32_t ctrl;        /**< \brief UTICK 控制寄存器  */
    __IO uint32_t status;      /**< \brief UTICK 状态寄存器  */
} amhw_utick_t;
 
/**
 * \name UTICK寄存器操作宏定义
 * @{
 */

/** \brief  UTICK重复定时位                                */
#define AMHW_UTICK_CTRL_REPEAT           ((uint32_t)1UL << 31)

/** \brief  UTICK定时值屏蔽值，31位，最大值为0x7FFFFFFF    */
#define AMHW_UTICK_CTRL_DELAY_MASK       ((uint32_t)0x7FFFFFFF)

/** \brief  UTICK中断状态位            */
#define AMHW_UTICK_STATUS_INTR           ((uint32_t)1 << 0)

/** \brief  UTICK激活位                */
#define AMHW_UTICK_STATUS_ACTIVE         ((uint32_t)1 << 1)

/** \brief  UTICK状态寄存器屏蔽值      */
#define AMHW_UTICK_STATUS_MASK           ((uint32_t)0x03)

/** @} */

/**
 * \brief 设置UTICK的定时tick数
 *
 * 定时值将会是(tick_value + 1)个时钟周期，最小的tick_value值为1，延时两个时钟
 * 周期，tick_value为0将停止定时器。
 *
 * \param[in] p_hw_utick : 指向UTICK寄存器块的指针
 * \param[in] tick_value : Tick 值,最大值为0x7FFFFFFF。
 * \param[in] repeat     : TRUE，重复定时，ticks减到0后自动重装载值
 *                         FALSE，一次定时，ticks减到0后自动停止定时
 * \return 无
 */
void amhw_utick_tick_set(amhw_utick_t *p_hw_utick, 
                         uint32_t      tick_value, 
                         bool_t        repeat);

/**
 * \brief 读取 UTICK 当前Tick值
 * \param[in] p_hw_utick : 指向UTICK寄存器块的指针
 * \return UTICK 当前Tick值
 */
am_static_inline 
uint32_t amhw_utick_tick_get (amhw_utick_t *p_hw_utick)
{
    return (p_hw_utick->ctrl & AMHW_UTICK_CTRL_DELAY_MASK);
}

/**
 * \brief 禁能UTICK定时器
 * \param[in] p_hw_utick : 指向UTICK寄存器块的指针
 * \return 无
 */

am_static_inline 
void amhw_utick_disable (amhw_utick_t *p_hw_utick)
{
    p_hw_utick->ctrl = 0;
}

/**
 * \brief 检测UTICK中断标志是否设置
 * \param[in] p_hw_utick : 指向UTICK寄存器块的指针
 * \retval TRUE  : 中断标志设置
 * \retval FALSE : 中断标志未设置
 */
am_static_inline 
bool_t amhw_utick_int_flag_check (amhw_utick_t *p_hw_utick)
{
    return (bool_t)((p_hw_utick->status & AMHW_UTICK_STATUS_INTR) != 0);
}

/**
 * \brief 清楚UTICK中断标志
 * \param[in] p_hw_utick : 指向UTICK寄存器块的指针
 * \return 无
 */
am_static_inline 
void amhw_utick_int_flag_clr (amhw_utick_t *p_hw_utick)
{
    p_hw_utick->status = AMHW_UTICK_STATUS_INTR;
}
 

/**
 * \brief 检测UTICK 定时器是否激活（通过检测激活标志）
 * \param[in] p_hw_utick : 指向UTICK寄存器块的指针
 * \retval TRUE  : 定时器已激活
 * \retval FALSE : 定时器未激活
 */
am_static_inline 
bool_t amhw_utick_active_flag_check (amhw_utick_t *p_hw_utick)
{
    return (bool_t)((p_hw_utick->status & AMHW_UTICK_STATUS_ACTIVE) != 0);
}
 
/**
 * @} amhw_if_utick
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_UTICK_H */

/* end of file */

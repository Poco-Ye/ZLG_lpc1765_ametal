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
 * \brief RIT(重复中断定时器:Repetitive Interrupt Timer)操作接口
 *
 * 1. 48位定时器，定时器时钟为主时钟（main clock）,定时器可以自由运行，也可以在产
 *    生中断的时候复位；
 * 2. 48位比较值；
 * 3. 48位比较屏蔽值. 当屏蔽后的定时器计数值与屏蔽后的比较值相等时，可以产生中断。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_RIT_H
#define __AMHW_RIT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_rit
 * \copydoc amhw_rit.h
 * @{
 */

/**
 * \brief RIT 寄存器块结构体
 */
typedef struct amhw_rit {
    __IO uint32_t  compval;       /**< \brief 低32位比较值寄存器  */
    __IO uint32_t  mask;          /**< \brief 低32位屏蔽值寄存器  */
    __IO uint32_t  ctrl;          /**< \brief 控制寄存器          */
    __IO uint32_t  counter;       /**< \brief 低32位计数器        */
    __IO uint32_t  compval_h;     /**< \brief 高16位比较值寄存器  */
    __IO uint32_t  mask_h;        /**< \brief 高16位屏蔽值寄存器  */
    __I  uint32_t  reserved;      /**< \brief 保留，不应使用      */
    __IO uint32_t  counter_h;     /**< \brief 高16位计数器        */
} amhw_rit_t;

/**
 * \name 用于RIT寄存器操作的宏定义
 * @{
 */

/** \brief 当定时器计数值与屏蔽后的比较值相等时，该位由硬件置位  */
#define AMHW_RIT_CTRL_INT    ((uint32_t) (1ul << 0))

/**
 * \brief 当定时器计数值与屏蔽后的比较值相等时，定时器当计数值清零
 */
#define AMHW_RIT_CTRL_ENCLR  ((uint32_t) (1ul << 1))

/**
 * \brief 使能定时器的调试模式, 当调试暂停时，定时器也会暂停
 */
#define AMHW_RIT_CTRL_ENBR   ((uint32_t) (1ul << 2))

/** \brief 定时器使能 */
#define AMHW_RIT_CTRL_TEN    ((uint32_t) (1ul << 3))

/** @} */

/**
 * \brief 使能RIT定时器
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_rit_enable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_TEN;
}

/**
 * \brief 禁能RIT定时器
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_rit_disable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl &= ~AMHW_RIT_CTRL_TEN;
}

/**
 * \brief 使能定时器的调试模式, 当调试暂停时，定时器也会暂停
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_rit_debug_enable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_ENBR;
}

/**
 * \brief 禁能定时器的调试模式, 当调试暂停时，定时器不受影响
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_rit_debug_disable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl &= ~AMHW_RIT_CTRL_ENBR;
}

/**
 * \brief 当定时器计数值与屏蔽后的比较值相等时，定时器当计数值清零
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_rit_clear_enable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_ENCLR;
}

/**
 * \brief 当定时器计数值与屏蔽后的比较值相等时，定时器当计数值不清零
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_rit_clear_disable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl &= ~AMHW_RIT_CTRL_ENCLR;
}

/**
 * \brief 检测中断标志位是否置位，当定时器计数值与屏蔽后的比较值相等时，该位由硬件置位
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \retval TRUE  : 中断标志位置位
 * \retval FALSE : 中断标志位未置位
 */
am_static_inline
bool_t amhw_rit_int_flag_check (amhw_rit_t *p_hw_rit)
{
    return (bool_t)((p_hw_rit->ctrl & (AMHW_RIT_CTRL_INT)) != 0);
}

/**
 * \brief 清除中断标志
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_rit_int_flag_clr (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_INT;
}

/**
 * \brief 设置48位比较值（用于产生中断）
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \param[in] val      : 比较值，最大值为0xFFFFFFFFFFFF(48位最大值)
 * \return 无
 */
am_static_inline
void amhw_rit_compval_set (amhw_rit_t *p_hw_rit, uint64_t val)
{
    p_hw_rit->compval   = (uint32_t)(val & 0xFFFFFFFF);
    p_hw_rit->compval_h = (uint32_t)((val >> 32) & 0xFFFF);
}

/**
 * \brief 设置比较屏蔽值 (48位)
 *
 * 屏蔽值为1的位将不参与比较，即屏蔽值为1的位比较结果恒为真
 *
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \param[in] val      : 屏蔽值，最大值为0xFFFFFFFFFFFF(48位最大值)
 *
 * \return 无
 */
am_static_inline
void amhw_rit_mask_set (amhw_rit_t *p_hw_rit, uint64_t val)
{
    p_hw_rit->mask   = (uint32_t)(val & 0xFFFFFFFF);
    p_hw_rit->mask_h = (uint32_t)((val >> 32) & 0xFFFF);
}

/**
 * \brief 得到当前的RIT屏蔽值
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 屏蔽值(低48位有效)
 */
am_static_inline
uint64_t amhw_rit_mask_get (amhw_rit_t *p_hw_rit)
{
    uint64_t mask_value;

    mask_value  = (uint64_t)p_hw_rit->mask;
    mask_value |= (((uint64_t)p_hw_rit->mask_h) << 32);

    return mask_value;
}

/**
 * \brief 得到当前的RIT比较值
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 当前的RIT比较值(低48位有效)
 */
am_static_inline
uint64_t amhw_rit_compval_get (amhw_rit_t *p_hw_rit)
{
    uint64_t compare_value;

    compare_value  = (uint64_t)p_hw_rit->compval;
    compare_value |= (((uint64_t)p_hw_rit->compval_h) << 32);

    return compare_value;
}

/**
 * \brief 得到当前的RIT计数值
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \return 当前的RIT计数值(低48位有效)
 */
am_static_inline
uint64_t amhw_rit_count_get (amhw_rit_t *p_hw_rit)
{
    uint64_t counter_value;

    counter_value  = (uint64_t)p_hw_rit->counter;
    counter_value |= (((uint64_t)p_hw_rit->counter_h) << 32);

    return counter_value;
}

/**
 * \brief 设置当前的RIT计数值
 * \param[in] p_hw_rit : 指向RIT寄存器块的指针
 * \param[in] value    : 设置的RIT计数值，最大值为0xFFFFFFFFFFFF(48位最大值)
 * \return 无
 */
void amhw_rit_count_set(amhw_rit_t *p_hw_rit, uint64_t value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_RIT_H */

/* end of file */

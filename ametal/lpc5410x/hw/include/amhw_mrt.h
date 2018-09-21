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
 * \brief MRT(Multi-Rate Timer)操作接口
 *
 * 1. 24位多频率定时器；
 * 2. 4个独立的向下计数通道，可分别设置独立的值；
 * 3. 支持重复中断模式、一次计时模式和一次计时（总线停滞）模式。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_MRT_H
#define __AMHW_MRT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_mrt
 * \copydoc amhw_mrt.h
 * @{
 */
 
/**
 * \brief MRT通道数配置
 */
#define AMHW_MRT_CHANNELS_NUM      (4)   
    
/** 
 * \brief MRT通道ID,用于操作具体的某个通道，有效范围：0 ~ AMHW_MRT_CHANNELS_NUM - 1 
 */
#define AMHW_MRT_CH(n)             (n)
    
/**
 * \brief MRT 通道寄存器块结构体
 */
typedef struct amhw_mrt_chan {
    __IO uint32_t intval;                /**< \brief 通道定时间隔值设置寄存器 */
    __O  uint32_t timer;                 /**< \brief 当前通道计数值值寄存器   */
    __IO uint32_t ctrl;                  /**< \brief 定时器通道控制寄存器     */
    __IO uint32_t stat;                  /**< \brief 定时器通道状态寄存器     */
} amhw_mrt_chan_t;

/**
 * \brief MRT寄存器块结构体
 */
typedef struct amhw_mrt {
    amhw_mrt_chan_t channel[AMHW_MRT_CHANNELS_NUM]; /**< \brief 通道寄存器组   */
    uint32_t        unused[44];                     /**< \brief 保留，不应使用 */
    __IO uint32_t   modcfg;                         /**< \brief 模式配置寄存器 */
    __O  uint32_t   idle_ch;                        /**< \brief 空闲通道寄存器 */
    __IO uint32_t   irq_flag;                       /**< \brief 中断标志寄存器 */ 
} amhw_mrt_t;

/**
 * \brief MRT 模式定义
 */
typedef enum {
    AMHW_MRT_MODE_REPEAT        = (0 << 1),  /**< \brief 重复定时中断模式     */
    AMHW_MRT_MODE_ONESHOT       = (1 << 1),  /**< \brief 一次计时中断模式     */
    AMHW_MRT_MODE_ONESHOT_STALL = (2 << 1)   /**< \brief 一次计时总线停滞模式 */
} amhw_mrt_mode_t;

/**
 * \name 用于MRT寄存器操作的宏定义
 * @{
 */
 
/** \brief 最大计时值，24位的最大值       */
#define AMHW_MRT_INTVAL_MAX       (0xFFFFFF)  

/** \brief 强制立即写入计时值             */
#define AMHW_MRT_INTVAL_LOAD      (1ul << 31)

/** \brief 中断使能                       */
#define AMHW_MRT_CTRL_INTEN       (1ul << 0)

/** \brief 模式设置屏蔽位                 */
#define AMHW_MRT_CTRL_MODE_MASK   (3ul << 1)
 
/** \brief 中断标志                       */
#define AMHW_MRT_STAT_INTFLAG     (1ul << 0)

/** \brief 通道运行标志                   */
#define AMHW_MRT_STAT_RUNNING     (1ul << 1)

/** \brief 通道使用标志                   */
#define AMHW_MRT_STAT_INUSE       (1ul << 2)

/** @}*/

/**
 * \brief 设置通道的定时值（INTVAL）
 *
 *  该值会被转载进timer（当前通道计数值值寄存器）中，通道将会从 
 *  设置值 - 1 开始递减计数 
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 * \param[in] value    ：定时值（INTVAL，低24位有效）
 * \param[in] forced   : TRUE : INTVAL值被立即转载
 *                       FALSE: NTVAL值下个定时器周期再转载
 *
 * \return 无
 */
am_static_inline
void amhw_mrt_intval_set (amhw_mrt_t *p_hw_mrt,
                          uint8_t     chan,
                          uint32_t    value,
                          bool_t      forced)
{
    value &= AMHW_MRT_INTVAL_MAX; 
    
    /* 值被立即转载入timer计数器 */
    if (forced == TRUE) {
        value |= AMHW_MRT_INTVAL_LOAD;
    }
    
    p_hw_mrt->channel[chan].intval = value;
}

/**
 * \brief 获取定时器的通道定时值（INTVAL）
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 通道定时值（INTVAL）
 */
am_static_inline
uint32_t amhw_mrt_intval_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (p_hw_mrt->channel[chan].intval) & AMHW_MRT_INTVAL_MAX;
}

/**
 * \brief 获取定时器通道当前的向下计数器的值
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 通道当前的向下计数器的值（从intval - 1 开始递减）
 */
am_static_inline 
uint32_t amhw_mrt_chan_count_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (p_hw_mrt->channel[chan].timer);
}


/**
 * \brief 使能定时器通道中断
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 无
 */
am_static_inline  
void amhw_mrt_int_enable (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->channel[chan].ctrl |= AMHW_MRT_CTRL_INTEN;
}

/**
 * \brief 禁能定时器通道中断
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 无
 */
am_static_inline 
void amhw_mrt_int_disable (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->channel[chan].ctrl &= ~AMHW_MRT_CTRL_INTEN;
}

/**
 * \brief 设置定时器通道模式
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 * \param[in] mode     : 定时器通道模式
 *
 * \return 无 
 */
am_static_inline
void amhw_mrt_mode_set (amhw_mrt_t     *p_hw_mrt, 
                        uint8_t         chan,
                        amhw_mrt_mode_t mode)
{
    p_hw_mrt->channel[chan].ctrl = (p_hw_mrt->channel[chan].ctrl 
                                 & (~AMHW_MRT_CTRL_MODE_MASK))
                                 | (uint32_t) mode;
}
/**
 * \brief 获取定时器通道的模式
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 定时器通道的模式
 */
am_static_inline
amhw_mrt_mode_t amhw_mrt_mode_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (amhw_mrt_mode_t)(p_hw_mrt->channel[chan].ctrl 
                                     & AMHW_MRT_CTRL_MODE_MASK);
}


/**
 * \brief 湖片区通道状态
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针.
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 通道状态寄存器值
 */
am_static_inline
uint32_t amhw_mrt_stat_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return p_hw_mrt->channel[chan].stat;
}

/**
 * \brief 清除通道的中断状态标志（操作通道自身的状态寄存器）
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针.
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 无
 */
am_static_inline
void amhw_mrt_int_flag_clr (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->channel[chan].stat |= AMHW_MRT_STAT_INTFLAG;
}


/**
 * \brief 获取当前空闲的通道中，通道号最小的通道
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \return 通道号最小的空闲通道的通道号
 */
am_static_inline
uint8_t amhw_mrt_idle_channel_get (amhw_mrt_t *p_hw_mrt)
{
    return (uint8_t)((p_hw_mrt->idle_ch) >> 4);
}

/**
 * \brief 获取指定通道的中断状态
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
* \retval  TRUE  : 中断发生
* \retval  FALSE : 中断未发生
 */
am_static_inline
bool_t amhw_mrt_int_pending_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (bool_t)((p_hw_mrt->irq_flag & (1 << chan)) != 0);
}

/**
 * \brief 清除通道的中断挂起标志（操作全局中断标志寄存器）
 *
 * \param[in] p_hw_mrt : 指向MRT寄存器块的指针 
 * \param[in] chan     : 通道ID，使用宏#AMHW_MRT_CH(n)
 *
 * \return 无
 */
am_static_inline
void amhw_mrt_int_pending_clr (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->irq_flag = (1 << chan);
}

/**
 * @} amhw_if_mrt
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MRT_H */

/* end of file */

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
 * \brief 标准定时器(Standard counter/timers)操作接口
 *
 * 1. 32位计数器/定时器，每个都具有一个32位可编程预分频器；
 * 2. 计数模式和定时模式；
 * 3. 4个32位捕获通道，可以在指定输入信号的边沿捕获定时器值，捕获事件同时还可以选择
 *   是否产生中断请求；
 * 4. 定时器和预分频器可以配置为被指定的捕获事件清零，该特性可以用作简单的脉宽频率
 *   测量：在指定的边沿清零定时器和预分频器，测量定时器值直到下一个边沿；
 * 5. 4个32位匹配寄存器可以:
 *    - 匹配时产生中断；
 *    - 停止定时器（可选择是否产生中断）；
 *    - 复位定时器（可选择是否产生中断）；
 * 6. 4个外部输入管脚与相应的匹配寄存器可以有如下功能： 
 *    - 匹配时设置输出为低电平；
 *    - 匹配时设置输出为高电平；
 *    - 匹配时翻转输出电平；
 *    - 匹配时管脚状态无变化；
 * 7. 对于每个定时器，最高可达3路单边沿控制的PWM输出。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_TIMER_H
#define __AMHW_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_timer  
 * \copydoc amhw_timer.h
 * @{
 */
    
/**
 * \brief Standard Timer 寄存器块结构体
 */
typedef struct amhw_timer { 
    __IO uint32_t ir;             /**< \brief 中断状态寄存器         */
    __IO uint32_t tcr;            /**< \brief 定时器控制寄存器       */
    __IO uint32_t tc;             /**< \brief 定时器计数寄存器       */
    __IO uint32_t pr;             /**< \brief 预分频寄存器           */
    __IO uint32_t pc;             /**< \brief 预分频计数寄存器       */
    __IO uint32_t mcr;            /**< \brief 匹配控制寄存器         */
    __IO uint32_t mr[4];          /**< \brief 匹配寄存器             */
    __IO uint32_t ccr;            /**< \brief 捕获控制寄存器         */
    __IO uint32_t cr[4];          /**< \brief 捕获寄存器             */
    __IO uint32_t emr;            /**< \brief 外部匹配管脚寄存器     */
    __I  uint32_t reserved0[12];  /**< \brief 保留，不应使用         */
    __IO uint32_t ctcr;           /**< \brief 计数控制寄存器         */
    __IO uint32_t pwmc;           /**< \brief PWM控制寄存器          */
} amhw_timer_t;

/**
 * \brief 检测一个匹配通道是否产生中断
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 待检测的匹配通道，有效值 0 ~ 3
 *
 * \retval  TRUE  : 中断产生
 * \retval  FALSE : 中断未产生
 *
 */
am_static_inline 
bool_t amhw_timer_mat_pending_get (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    return (bool_t)((p_hw_timer->ir & (1 << ch)) != 0);
}

/**
 * \brief 检测一个捕获通道是否产生中断
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 待检测的捕获通道，有效值 0 ~ 3
 *
 * \retval  TRUE  : 中断产生
 * \retval  FALSE : 中断未产生
 */
am_static_inline  
bool_t amhw_timer_cap_pending_get (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    return (bool_t)((p_hw_timer->ir & (1 << (ch + 4))) != 0);
}

/**
 * \brief 清除匹配中断标志
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 待清除中断标志的匹配通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline
void amhw_timer_mat_pending_clr (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ir = (1 << ch);
}

/**
 * \brief 清除捕获中断标志
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 待清除中断标志的捕获通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_cap_pending_clr (amhw_timer_t *p_hw_timer, int8_t ch)
{
    p_hw_timer->ir = (0x10 << ch);
}

/**
 * \brief 使能定时器 (开始计数)
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \return 无
 */
am_static_inline 
void amhw_timer_enable (amhw_timer_t *p_hw_timer)
{
    p_hw_timer->tcr = (p_hw_timer->tcr & 0x03) | (1 << 0);
}

/**
 * \brief 禁能定时器(停止计数)
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \return 无
 */
am_static_inline 
void amhw_timer_disable (amhw_timer_t *p_hw_timer)
{
    p_hw_timer->tcr = (p_hw_timer->tcr & 0x03) & ~(1 << 0);
}

/**
 * \brief 得到当前定时器的计数值
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \return 当前定时器的计数值
 */
am_static_inline 
uint32_t amhw_timer_count_get (amhw_timer_t *p_hw_timer)
{
    return p_hw_timer->tc;
}

/**
 * \brief 设置当前定时器的计数值
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] value      : 设置的定时器的计数值
 * \return 无
 */
am_static_inline 
void amhw_timer_count_set (amhw_timer_t *p_hw_timer, uint32_t value)
{
    p_hw_timer->tc = value;
}

/**
 * \brief 得到预分频设置值
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \return 当前的预分频器设置值
 */
am_static_inline 
uint32_t amhw_timer_prescale_get (amhw_timer_t *p_hw_timer)
{
    return p_hw_timer->pr;
}

/**
 * \brief 设置预分频器的值
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] prescale   : 预分频值
 *
 * \return 无
 */
am_static_inline  
void amhw_timer_prescale_set (amhw_timer_t *p_hw_timer, uint32_t prescale)
{
    p_hw_timer->pr = prescale;
}

/**
 * \brief 得到预分频计数器的当前值
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \return 预分频计数器的当前值
 */
am_static_inline 
uint32_t amhw_timer_prescale_count_get (amhw_timer_t *p_hw_timer)
{
    return p_hw_timer->pc;
}

/**
 * \brief 设置一个匹配通道的匹配值
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 匹配通道，有效值 0 ~ 3
 * \param[in] val        : 匹配值
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_mat_val_set (amhw_timer_t *p_hw_timer, uint8_t ch, uint32_t val)
{
    p_hw_timer->mr[ch] = val;
}

/**
 * \brief 从一个捕获通道获取捕获值
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 捕获通道，有效值 0 ~ 3
 *
 * \return 指定捕获通道的捕获值
 */
am_static_inline  
uint32_t amhw_timer_cap_val_get (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    return p_hw_timer->cr[ch];
}

/**
 * \brief  复位定时器计数值和预分频器计数值为0
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \return 无
 */
void amhw_timer_reset (amhw_timer_t *p_hw_timer);

/**
 * \brief 使能匹配中断（当定时器计数值与匹配通道的值相等时）
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 匹配通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_mat_int_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (1 << (ch * 3));
}

/**
 * \brief 禁能匹配中断
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 匹配通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_mat_int_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) & (~(1 << (ch * 3)));
}

/**
 * \brief 使能匹配事件复位定时器计数值
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 匹配通道，有效值 0 ~ 3
 *
 * \return   无
 */
am_static_inline  
void amhw_timer_mat_reset_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (1 << ((ch * 3) + 1));
}

/**
 * \brief 禁能匹配事件复位定时器计数值
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 匹配通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline  
void amhw_timer_mat_reset_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) & (~(1 << ((ch * 3) + 1)));
}

/**
 * \brief 使能匹配事件停止定时器计数
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 匹配通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_mat_stop_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (1 << (((ch * 3) + 2)));
}

/**
 * \brief 禁能匹配事件停止定时器计数
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 匹配通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_mat_stop_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (~(1 << (((ch * 3) + 2))));
}

/**
 * \brief 使能上升沿触发捕获事件
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 捕获通道，有效值 0 ~ 3
 *
 * \return 无
 *
 * \note 同时使能上升沿捕获和下降沿捕获将会在双边沿均产生捕获事件
 */
am_static_inline 
void amhw_timer_cap_rising_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (1 << (ch * 3));
}

/**
 * \brief 禁能上升沿触发捕获事件
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 捕获通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_cap_rising_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) & (~(1 << (ch * 3)));
}


/**
 * \brief 使能下降沿触发捕获事件
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 捕获通道，有效值 0 ~ 3
 *
 * \return 无
 *
 * \note 同时使能上升沿捕获和下降沿捕获将会在双边沿均产生捕获事件
 */
am_static_inline  
void amhw_timer_cap_falling_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (1 << (ch * 3 + 1));
}

/**
 * \brief 禁能下降沿触发捕获事件
 * 
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 捕获通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline  
void amhw_timer_cap_falling_disable (amhw_timer_t *p_hw_timer, int8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (~(1 << (ch * 3 + 1)));
}

/**
 * \brief 使能捕获中断
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 捕获通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline  
void amhw_timer_cap_int_enable (amhw_timer_t *p_hw_timer, int8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (1 << (ch * 3 + 2));
}

/**
 * \brief 禁能捕获中断
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] ch         : 捕获通道，有效值 0 ~ 3
 *
 * \return 无
 */
am_static_inline  
void amhw_timer_cap_int_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) & (~(1 << (ch * 3 + 2)));
}

/**
 * \brief Standard timer 匹配管脚变化状态定义
 */
typedef enum  amhw_timer_mat_pin_state {
    AMHW_TIMER_MAT_PIN_DO_NOTHING = 0, /**< \brief 匹配时不做任何变化    */
    AMHW_TIMER_MAT_PIN_CLR        = 1, /**< \brief 匹配时输出低电平      */
    AMHW_TIMER_MAT_PIN_SET        = 2, /**< \brief 匹配时输出高电平      */
    AMHW_TIMER_MAT_PIN_TOGGLE     = 3  /**< \brief 匹配时翻转输出电平    */
} amhw_timer_mat_pin_state_t;

/**
 * \brief 配置匹配通道对应的外部管脚
 *
 * \param[in] p_hw_timer    : 指向Standard Timer寄存器块的指针
 * \param[in] ch            : 匹配通道，有效值 0 ~ 3
 * \param[in] initial_state : 外部管脚的初始状态, 1：高电平, 0 ：低电平
 * \param[in] match_state   : 选择该管脚的匹配事件动作状态
 *
 * \return 无
 */
void amhw_timer_mat_pin_ctrl (amhw_timer_t              *p_hw_timer,
                              uint8_t                    ch,
                              uint8_t                    initial_state,
                              amhw_timer_mat_pin_state_t match_state);

/**
 * \brief Standard timer 的计数时钟源和边沿选择
 */
typedef enum amhw_timer_src {
    AMHW_TIMER_SRC_RISING_PCLK  = 0, /**< \brief 默认，PCLK的上升沿     */
    AMHW_TIMER_SRC_RISING_CAP   = 1, /**< \brief 捕获输入的上升沿       */
    AMHW_TIMER_SRC_FALLING_CAP  = 2, /**< \brief 捕获输入的下降沿       */
    AMHW_TIMER_SRC_BOTH_CAP     = 3  /**< \brief 捕获输入的双边沿       */
} amhw_timer_src_t;

/**
 * \brief 设置定时器计数时钟源和时钟边沿
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] timer_src  : 定时器计数时钟源和时钟边沿
 * \param[in] cap_num    : 如果时钟源为捕获输入，则这里指定捕获通道号，有效值0~3
 *
 * \return 无
 */
am_static_inline  
void amhw_timer_src_set (amhw_timer_t     *p_hw_timer, 
                         amhw_timer_src_t  timer_src, 
                         uint8_t           cap_num)
{
    p_hw_timer->ctcr = (p_hw_timer->ctcr &  0xF0ul)  |
                       ((uint32_t)timer_src)         |
                       ((uint32_t)cap_num << 2);
}

/**
 * \brief 选择定时器和预分频器的清零输入源
 */
typedef enum  amhw_timer_cap_clrsrc {
    AMHW_TIMER_CAP_CLRSRC_CH0_RISING  = 0, /**< \brief 捕获通道0上升沿   */
    AMHW_TIMER_CAP_CLRSRC_CH0_FALLING = 1, /**< \brief 捕获通道0下降沿   */
    AMHW_TIMER_CAP_CLRSRC_CH1_RISING  = 2, /**< \brief 捕获通道1上升沿   */
    AMHW_TIMER_CAP_CLRSRC_CH1_FALLING = 3, /**< \brief 捕获通道1下降沿   */
    AMHW_TIMER_CAP_CLRSRC_CH2_RISING  = 4, /**< \brief 捕获通道2上升沿   */
    AMHW_TIMER_CAP_CLRSRC_CH2_FALLING = 5, /**< \brief 捕获通道2下降沿   */ 
} amhw_timer_cap_clrsrc_t;

/**
 * \brief 使能输入捕获时钟源清零定时器和预分频器计数值
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] clr_src    : 用于清零的输入源
 *
 * \return 无
 */
am_static_inline
void amhw_timer_cap_clr_enable (amhw_timer_t            *p_hw_timer,
                                amhw_timer_cap_clrsrc_t  clr_src)
{
    p_hw_timer->ctcr = (p_hw_timer->ctcr & 0x1F) | (clr_src << 5) | (1 <<  4);
}

/**
 * \brief 禁能输入捕获时钟源清零定时器和预分频器计数值
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \return 无
 */
am_static_inline 
void amhw_timer_cap_clr_disable (amhw_timer_t *p_hw_timer)
{
    p_hw_timer->ctcr &= ~((uint32_t)(1 << 4));
}

/**
 * \brief 使能匹配通道的PWM模式
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] mat_num    : 匹配通道：有效值，0 ~ 3
 *
 * \return 无
 * 
 * \note 当使能了匹配通道的PWM模式，则当定时器计数值小于匹配寄存器值时，输出低
 *       电平否则，输出低电平。
 */
am_static_inline 
void amhw_timer_mat_pwm_enable (amhw_timer_t *p_hw_timer, uint8_t mat_num)
{
    p_hw_timer->pwmc |=  (1 << mat_num);
}

/**
 * \brief 禁能匹配通道的PWM模式
 *
 * \param[in] p_hw_timer : 指向Standard Timer寄存器块的指针
 * \param[in] mat_num    : 匹配通道：有效值，0 ~ 3
 *
 * \return 无
 */
am_static_inline 
void amhw_timer_mat_pwm_disable (amhw_timer_t *p_hw_timer, uint8_t mat_num)
{
    p_hw_timer->pwmc &=  ~(1 << mat_num);
}

/**
 * @} amhw_if_timer
 */

#ifdef __cplusplus
}
#endif


#endif /* __AMHW_TIMER_H */

/* end of file */

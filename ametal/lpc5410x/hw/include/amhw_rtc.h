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
 * \brief RTC硬件操作接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-27  fft, first implementation.
 * \endinternal
 */

#ifndef __AMHW_RTC_H
#define __AMHW_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"

/** 
 * \addtogroup amhw_if_rtc
 * \copydoc amhw_rtc.h
 * @{
 */

/**
 * \brief 实时时钟寄存器块的结构体
 */
typedef struct amhw_rtc {                                                                 
    __IO uint32_t ctrl;   /**< \brief RTC 控制寄存器 */
    __IO uint32_t match;  /**< \brief RTC 匹配寄存器 */
    __IO uint32_t count;  /**< \brief RTC 计数寄存器 */
    __IO uint32_t wake;   /**< \brief RTC 唤醒寄存器 */
} amhw_rtc_t;

/** 
 * \brief RTC 控制位定义
 * @{
 */

/** \brief 软件复位控制位 */
#define AMHW_RTC_CTRL_SWRESET      AM_BIT(0)

/** \brief 振荡器检测失败状态  */
#define AMHW_RTC_CTRL_OFD          AM_BIT(1)    

/** \brief RTC 1Hz定时匹配 */
#define AMHW_RTC_CTRL_ALARM1HZ     AM_BIT(2)  

/** \brief RTC 1 kHz 定时唤醒 */
#define AMHW_RTC_CTRL_WAKE1KHZ     AM_BIT(3)   

/** \brief RTC 1 Hz 定时匹配，唤醒从深度掉电模式 */
#define AMHW_RTC_CTRL_ALARMDPD_EN  AM_BIT(4)   

/** \brief RTC 1 kHz 定时唤醒，唤醒从深度掉电模式 */
#define AMHW_RTC_CTRL_WAKEDPD_EN   AM_BIT(5) 

/** \brief 使能RTC 1KHz 定时器 */
#define AMHW_RTC_CTRL_RTC1KHZ_EN   AM_BIT(6)    

/** \brief 使能RTC */
#define AMHW_RTC_CTRL_RTC_EN       AM_BIT(7)

/** \brief RTC 控制位掩码 */
#define AMHW_RTC_CTRL_MASK         ((uint32_t) 0xF1)  

/** @} */


/**
 * \brief RTC 控制位配置函数
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] flags    : AMHW_RTC_CTRL_*的宏值或多个
 *                       AMHW_RTC_CTRL_*宏的或(OR)值(#AMHW_RTC_CTRL_OFD)
 *
 * \return    None
 */
am_static_inline 
void amhw_rtc_control (amhw_rtc_t *p_hw_rtc, uint32_t flags)
{
    p_hw_rtc->ctrl = flags;
}

/**
 * \brief 选择性使能RTC
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] flags    : AMHW_RTC_CTRL_*的宏值或多个
 *                       AMHW_RTC_CTRL_*宏的或(OR)值(#AMHW_RTC_CTRL_ALARMDPD_EN) 
 *
 * \return    无
 * \note 通过将标志位进行或操作，可以同时使能多个RTC选项 例如：
 *       AMHW_RTC_CTRL_ALARMDPD_EN, AMHW_RTC_CTRL_WAKEDPD_EN, AMHW_RTC_CTRL_RTC1KHZ_EN, and
 *       AMHW_RTC_CTRL_RTC_EN 
 */
am_static_inline 
void amhw_rtc_ctl_set (amhw_rtc_t *p_hw_rtc, uint32_t flags)
{
    p_hw_rtc->ctrl = (p_hw_rtc->ctrl & AMHW_RTC_CTRL_MASK) | flags;
}

/**
 * \brief 选择性禁能RTC
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] flags    : AMHW_RTC_CTRL_*的宏值或多个
 *                       AMHW_RTC_CTRL_*宏的或(OR)值(#AMHW_RTC_CTRL_ALARMDPD_EN) 
 *
 * \return    无
 * \note 通过将标志位进行或操作，可以同时禁能多个RTC选项 例如：
 *       AMHW_RTC_CTRL_ALARMDPD_EN, AMHW_RTC_CTRL_WAKEDPD_EN, AMHW_RTC_CTRL_RTC1KHZ_EN, and
 *       AMHW_RTC_CTRL_RTC_EN flags with this function.
 */
am_static_inline 
void amhw_rtc_ctl_clr (amhw_rtc_t *p_hw_rtc, uint32_t flags)
{
    p_hw_rtc->ctrl = (p_hw_rtc->ctrl & AMHW_RTC_CTRL_MASK) & ~flags;
}

/**
 * \brief 使能RTC控制器
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    无
 *
 * \note 可以通过amhw_rtc_ctl_set()函数写入AMHW_RTC_CTRL_RTC_EN标志位使能
 */
am_static_inline 
void amhw_rtc_enable (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_RTC_EN);
}

/**
 * \brief 禁能RTC控制器
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    无
 *
 * \note 可以通过amhw_rtc_ctl_clr()函数写入AMHW_RTC_CTRL_RTC_EN标志位禁能
 */
am_static_inline 
void amhw_rtc_disable (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_clr(p_hw_rtc, AMHW_RTC_CTRL_RTC_EN);
}

/**
 * \brief 复位RTC控制器
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    无
 *
 * \note RTC的状态寄存器将返回默认值
 */
am_static_inline 
void amhw_rtc_reset (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_SWRESET);
    amhw_rtc_ctl_clr(p_hw_rtc, AMHW_RTC_CTRL_SWRESET);
}

/**
 * \brief 检测振荡器是否正常操作
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 *
 * \retval TRUE  : 振荡器检测失败状态
 * \retval FALSE : 振荡器正常运行
 */
am_static_inline 
bool_t amhw_rtc_ofd_check (amhw_rtc_t *p_hw_rtc) 
{
    return (bool_t)((p_hw_rtc->ctrl & AMHW_RTC_CTRL_OFD) != 0);
}

/**
 * \brief 清除振荡器检测失败状态
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return 无
 */
am_static_inline 
void amhw_rtc_ofd_clr (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_OFD);
}

/**
 * \brief 使能RTC 1KHz定时
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    None
 * \note 可以通过amhw_rtc_ctl_set()函数写入AMHW_RTC_CTRL_RTC1KHZ_EN标志位使能        
 */
am_static_inline 
void amhw_rtc_enable_1kHz (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_RTC1KHZ_EN);
}

/**
 * \brief 禁能RTC 1KHz定时
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    None
 * \note 可以通过amhw_rtc_ctl_clr()函数写入AMHW_RTC_CTRL_RTC1KHZ_EN标志位禁能     
 */
am_static_inline
void amhw_rtc_disable_1kHz (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_clr(p_hw_rtc, AMHW_RTC_CTRL_RTC1KHZ_EN);
}

/**
 * \brief 选择性使能RTC中断唤醒
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] ints     : 可唤醒RTC的中断标志位
 *
 * \return    None
 * \note 选择一个或者多个可唤醒RTC中断的标志位，例如AMHW_RTC_CTRL_ALARMDPD_EN
 *       AMHW_RTC_CTRL_WAKEDPD_EN 
 *       可以通过amhw_rtc_ctl_set()函数写入AMHW_RTC_CTRL_ALARMDPD_EN标志位使能   
 */
am_static_inline 
void amhw_rtc_enable_wakeup (amhw_rtc_t *p_hw_rtc, uint32_t ints)
{
    amhw_rtc_ctl_set(p_hw_rtc, ints);
}

/**
 * \brief 选择性禁能RTC中断唤醒
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] ints     : 中断标志位
 *
 * \return    None
 * \note 选择一个或者多个中断的标志位，例如AMHW_RTC_CTRL_ALARMDPD_EN
 *       AMHW_RTC_CTRL_WAKEDPD_EN 
 *       可以通过amhw_rtc_ctl_clr()函数写入AMHW_RTC_CTRL_ALARMDPD_EN标志位禁能   
 */
am_static_inline 
void amhw_rtc_disable_wakeup (amhw_rtc_t *p_hw_rtc, uint32_t ints)
{
    amhw_rtc_ctl_clr(p_hw_rtc, ints);
}

/**
 * \brief 清除RTC状态位
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] sts_mask : 需要清除的状态位
 *
 * \return    无
 * \note 可以用于清除状态位写1可清除的标志。例如：AMHW_RTC_CTRL_OFD, 
 *        AMHW_RTC_CTRL_ALARM1HZ, 和AMHW_RTC_CTRL_WAKE1KHZ。
 */
am_static_inline 
void amhw_rtc_stat_clr (amhw_rtc_t *p_hw_rtc, uint32_t sts_mask)
{
    p_hw_rtc->ctrl = (p_hw_rtc->ctrl & AMHW_RTC_CTRL_MASK) | sts_mask;
}

/**
 * \brief 获取RTC状态寄存器的值 
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return   RTC CTRL寄存器的值 
 */
am_static_inline
uint32_t amhw_rtc_stat_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->ctrl;
}

/**
 * \brief 设定RTC匹配值
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] count    : 设定的值
 *
 * \return    无
 */
am_static_inline 
void amhw_rtc_alarm_set (amhw_rtc_t *p_hw_rtc, uint32_t count)
{
    p_hw_rtc->match = count;
}

/**
 * \brief 获取RTC匹配寄存器的值
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    MATCH寄存器的值
 */
am_static_inline 
uint32_t amhw_rtc_alarm_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->match;
}

/**
 * \brief 设定RTC匹配计数值
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] count    : 初始计数值设定
 *
 * \return    无
 */
am_static_inline 
void amhw_rtc_count_set (amhw_rtc_t *p_hw_rtc, uint32_t count)
{
    p_hw_rtc->count = count;
}

/**
 * \brief 获取RTC计数寄存器值
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    计数寄存器的值
 */
am_static_inline 
uint32_t amhw_rtc_count_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->count;
}

/**
 * \brief 设置RTC唤醒倒计时的值 (单位：ms)
 *
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \param[in] count    : 唤醒时间值
 *
 * \return    无
 * \note 写入数值到唤醒寄存器，进入唤醒定时器
 */
am_static_inline 
void amhw_rtc_setwake (amhw_rtc_t *p_hw_rtc, uint16_t count)
{
    p_hw_rtc->wake = count;
}

/**
 * \brief 获取RTC唤醒寄存器的值
 * \param[in] p_hw_rtc : 指向RTC寄存器块的指针
 * \return    RTC唤醒寄存器的值
 */
am_static_inline 
uint16_t amhw_rtc_getwake (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->wake;
}

/**
 * @} amhw_if_rtc
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_RTC_H */

/* end of file */

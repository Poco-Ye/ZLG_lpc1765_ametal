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
 * \brief  WWDT硬件操作接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-25  fft, first implementation.
 * \endinternal
 */

#ifndef __AMHW_WWDT_H
#define __AMHW_WWDT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "amhw_clock.h"
    
/** 
 * \addtogroup amhw_if_wwdt
 * \copydoc amhw_wwdt.h
 * @{
 */

/**
 * \brief WWDT寄存器块的结构体
 */
typedef struct amhw_wwdt {
    __IO uint32_t  mod;         /**< \brief 看门狗定时器模式寄存器          */
    __IO uint32_t  tc;          /**< \brief 看门狗定时器超时时间设定寄存器  */
    __O  uint32_t  feed;        /**< \brief 看门狗喂狗序列寄存器(0xAA 0x55) */
    __I  uint32_t  tv;          /**< \brief 看门狗定时器值设定寄存器        */
    __I  uint32_t  reserved0;   /**< \brief 保留                   */
    __IO uint32_t  warnint;     /**< \brief 看门狗报警中断比较数值 */
    __IO uint32_t  window;      /**< \brief 看门狗定时器窗口值     */
} amhw_wwdt_t;

/**
* \name WWDT 模式定义
* @{
*/

#define AMHW_WWDT_WDMOD_BITMASK    ((uint32_t)0x3F)  /**< \brief 看门狗模式位掩码 */      
#define AMHW_WWDT_WDMOD_WDEN       AM_BIT(0)         /**< \brief 看门狗使能位  */ 
#define AMHW_WWDT_WDMOD_WDRESET    AM_BIT(1)         /**< \brief 看门狗复位位  */ 
#define AMHW_WWDT_WDMOD_WDTOF      AM_BIT(2)         /**< \brief 看门过超时标志*/    

  
#define AMHW_WWDT_WDMOD_WDINT      AM_BIT(3)         /**< \brief 看门狗报警中断标志 */ 
#define AMHW_WWDT_WDMOD_WDPROTECT  AM_BIT(4)         /**< \brief 看门狗更新模式 */ 
#define AMHW_WWDT_WDMOD_LOCK       AM_BIT(5)         /**< \brief 看门狗锁定位   */

/** @} */
 
 
/**
 * \brief 初始化WWDT
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_wwdt_init (amhw_wwdt_t *p_hw_wwdt)
{
    /* 禁能看门狗 */
    p_hw_wwdt->mod     = 0;
    p_hw_wwdt->tc      = 0xFF;
    p_hw_wwdt->warnint = 0x0;
    p_hw_wwdt->window  = 0xFFFFFF;
}

/**
 * \brief 设置看门狗定时器超时时间，用于喂狗
 *
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \param[in] timeout   : 超时时间, 范围 0xFF - 0xFFFFFF
 *
 * \return    无
 */
am_static_inline 
void amhw_wwdt_timeout_set (amhw_wwdt_t *p_hw_wwdt, uint32_t timeout)
{
    p_hw_wwdt->tc = timeout;
}

/**
 * \brief 看门狗喂狗函数
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \return    无
 * \note 如果该函数未被调用，将产生看门狗报警中断
 */
am_static_inline 
void amhw_wwdt_feed (amhw_wwdt_t *p_hw_wwdt)
{
    p_hw_wwdt->feed = 0xAA;
    p_hw_wwdt->feed = 0x55;
}

/**
 * \brief 设定报警中断的值
 *
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \param[in] timeout   : 看门狗报警中断的比较值
 *
 * \return    无
 *
 * \note  看门狗定时器的值和设定的值匹配，产生一个中断
 */
am_static_inline
void amhw_wwdt_warning_set (amhw_wwdt_t *p_hw_wwdt, uint32_t timeout)
{
    p_hw_wwdt->warnint = timeout;
}

/**
 * \brief 获取报警中断寄存器的值
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针 
 * \return    当前报警中断寄存器的值
 */
am_static_inline 
uint32_t amhw_wwdt_warning_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->warnint;
}

/**
 * \brief 设定看门狗窗口定时器的值
 *
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \param[in] timeout   : 窗口定时器的值
 *
 * \return    无
 */
am_static_inline 
void amhw_wwdt_window_set (amhw_wwdt_t *p_hw_wwdt, uint32_t timeout)
{
    p_hw_wwdt->window = timeout;
}

/**
 * \brief 获取看门狗窗口定时器的值
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \return    看门狗窗口定时器寄存器的值
 */
am_static_inline 
uint32_t amhw_wwdt_window_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->window;
}

/**
 * \brief 使能看门狗定时器选项
 *
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \param[in] options   : 使能的看门狗定时器选项
 *                        例如：AMHW_WWDT_WDMOD_WDEN, AMHW_WWDT_WDMOD_WDRESET, 
 *                              和 AMHW_WWDT_WDMOD_WDPROTECT
 * \return    无
 *
 * \note 使能一个或多个，可将标志位进行或操作(AMHW_WWDT_WDMOD_WDRESET | 
 *                                            AMHW_WWDT_WDMOD_WDPROTECT)
 *       
 */
am_static_inline 
void amhw_wwdt_option_set (amhw_wwdt_t *p_hw_wwdt, uint32_t options)
{
    p_hw_wwdt->mod = (p_hw_wwdt->mod & AMHW_WWDT_WDMOD_BITMASK) | options;
}

/**
 * \brief 使能WWDT
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_wwdt_start (amhw_wwdt_t *p_hw_wwdt)
{
    amhw_wwdt_option_set(p_hw_wwdt, AMHW_WWDT_WDMOD_WDEN);
    amhw_wwdt_feed(p_hw_wwdt);
}

/**
 * \brief 读取WWDT状态标志位
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \return    状态位, WWDT_WDMOD_*的宏值或者多个WWDT_WDMOD_*宏的或（OR）值
 */
am_static_inline 
uint32_t amhw_wwdt_status_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->mod;
}

/**
 * \brief 清除WWDT状态位
 *
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \param[in] flags     : 清除的标志位
 *
 * \return  无
 *
 * \note 可以清除标志位 AMHW_WWDT_WDMOD_WDINT, AMHW_WWDT_WDMOD_WDTOF 
 */
am_static_inline
void amhw_wwdt_status_clr (amhw_wwdt_t *p_hw_wwdt, uint32_t flags)
{
    if (flags & AMHW_WWDT_WDMOD_WDTOF) {
        p_hw_wwdt->mod &= (~AMHW_WWDT_WDMOD_WDTOF) & 0x3F;
    }
    
    /* 写1，清除中断标志位 */
    if (flags & AMHW_WWDT_WDMOD_WDINT) {
        p_hw_wwdt->mod = (p_hw_wwdt->mod & 0x3F) | AMHW_WWDT_WDMOD_WDINT;
    }
}

/**
 * \brief 获取看门狗定时器的值
 * \param[in] p_hw_wwdt : 指向WWDT寄存器块的指针
 * \return    看门狗TV寄存器的值
 */
am_static_inline 
uint32_t amhw_wwdt_currentcount_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->tv;
}

/**
 * @} amhw_if_wwdt
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_WWDT_H */

/* end of file */

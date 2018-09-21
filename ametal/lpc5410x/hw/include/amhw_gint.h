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
* e-mail:      apollo.support\zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GPIO 组中断硬件操作接口
 *
 * 1. 任意配置为输入的数字引脚均可为组中断的贡献一个中断；
 * 2. 组中断中每一个输入源的优先级均可配置为高或低；
 * 3. 各个中断组合可进行逻辑与或操作；
 * 4. 两组中断支持独立的中断模式；
 * 5. 组中断可将部分外设从睡眠模式、深度睡眠模式和掉电模式中唤醒。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  asd, first implementation.
 * \endinternal
 */

#ifndef __AMHW_GINT_H
#define __AMHW_GINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_gint
 * \copydoc amhw_gint.h
 * @{
 */
 
/**
 * \brief GPIO 组中断寄存器块结构体
 */
typedef struct amhw_gint {
    __IO uint32_t  ctrl;                /**< \brief GPIO组中断控制寄存器       */
    __I  uint32_t  reserved0[7];        /**< \brief 保留                       */
    __IO uint32_t  port_pol[8];         /**< \brief GPIO组中断端口优先级寄存器 */
    __IO uint32_t  port_ena[8];         /**< \brief GPIO组中断端口使能寄存器   */
    __I  uint32_t  reserved1[4072];     /**< \brief 保留                       */
} amhw_gint_t;


/**
 * \name 组中断编号
 * \anchor grp_amhw_gint_num
 * @{
 */
 
#define AMHW_GROUP_0                   0            /**< \brief 组中断0 */
#define AMHW_GROUP_1                   1            /**< \brief 组中断1 */

/** @} */


/**
 * \name LPC5410x GPIO控制寄存器位域定义
 * \anchor grp_amhw_gint_ctrl
 * @{
 */
 
#define AMHW_GINT_CTRL_COMB_OR       (0UL << 1)    /**< \brief 组中断或模式       */ 
#define AMHW_GINT_CTRL_COMB_AND      (1UL << 1)    /**< \brief 组中断与模式       */
#define AMHW_GINT_CTRL_TRIG_EDGE     (0UL << 2)    /**< \brief 组中断边沿触发模式 */ 
#define AMHW_GINT_CTRL_TRIG_LEVEL    (1UL << 2)    /**< \brief 组中断电平触发模式 */

/** @} */

/**
 * \brief 设置组中断控制寄存器
 *
 * \param[in] p_hw_gint : 指向GPIO组中断寄存器块的指针。
 * \param[in] group     : GPIO 组中断号，(#AMHW_GROUP_0) 或 (#AMHW_GROUP_1) 
 * \param[in] flags     : 配置参数，参见
 *                        \ref grp_amhw_gint_ctrl
 *
 * \return  无。
 */
am_static_inline
void amhw_gint_ctrl_set (amhw_gint_t *p_hw_gint, uint8_t group, uint32_t flags)
{
    p_hw_gint[group].ctrl = (flags & ~(1UL << 0));
}


/**
 * \brief 清除指定组中断的中断等待状态
 *
 * \param[in] p_hw_gint : 指向GPIO组中断寄存器块的指针
 * \param[in] group     : GPIO 组中断号，(#AMHW_GROUP_0) 或 (#AMHW_GROUP_1) 
 *
 * \return  无。
 */
am_static_inline
void amhw_gint_status_clr (amhw_gint_t *p_hw_gint, uint8_t group)
{
    p_hw_gint[group].ctrl |= (1UL << 0);
}

/**
 * \brief 获取指定组中断的等待中断状态
 *
 * \param[in] p_hw_gint : 指向GPIO组中断寄存器块的指针
 * \param[in] group     : GPIO 组中断号，(#AMHW_GROUP_0) 或 (#AMHW_GROUP_1) 
 *
 * \retval TRUE         : 有中断等待
 * \retval FALSE        : 无中断等待
 */
am_static_inline
bool_t amhw_gint_status_get (amhw_gint_t *p_hw_gint, uint8_t group)
{
    return (bool_t)((p_hw_gint[group].ctrl & (1UL << 0)) != 0);
}

/**
 * \brief 选择指定引脚为指定组中断的低电平触发
 *
 * \param[in] p_hw_gint : 指向GPIO组中断寄存器块的指针
 * \param[in] group     : GPIO 组中断号，(#AMHW_GROUP_0) 或 (#AMHW_GROUP_1) 
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return  无
 */
am_static_inline
void amhw_gint_low_level_sel (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_pol[(uint32_t)(pin >> 5)] &= ~(1UL << (pin & 0xF));
}

/**
 * \brief 选择指定引脚为指定组中断的高电平触发
 *
 * \param[in] p_hw_gint : 指向GPIO组中断寄存器块的指针
 * \param[in] group     : GPIO 组中断号，(#AMHW_GROUP_0) 或 (#AMHW_GROUP_1) 
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return  无
 */
am_static_inline
void amhw_gint_high_level_sel (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_pol[(uint32_t)(pin >> 5)] |= (1UL << (pin & 0xF));
}

/**
 * \brief 组中断中指定引脚中断禁能
 *
 * \param[in] p_hw_gint : 指向GPIO组中断寄存器块的指针
 * \param[in] group     : GPIO 组中断号，(#AMHW_GROUP_0) 或 (#AMHW_GROUP_1) 
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return  无
 *
 * \note   禁能后的引脚不再为组中断贡献中断
 */
am_static_inline
void amhw_gint_disabled (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_ena[(uint32_t)(pin >> 5)] &= ~(1UL << (pin & 0xF));
}

/**
 * \brief 组中断中指定引脚中断使能
 *
 * \param[in] p_hw_gint : 指向GPIO组中断寄存器块的指针
 * \param[in] group     : GPIO 组中断号，(#AMHW_GROUP_0) 或 (#AMHW_GROUP_1) 
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return  无
 *
 * \note    使能后的引脚为组中断贡献中断
 */
am_static_inline
void amhw_gint_enabled (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_ena[(uint32_t)(pin >> 5)] |= (1UL << (pin & 0xF));
}

/** @} amhw_if_gint */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_GINT_H */

/* end of file */

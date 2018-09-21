/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief LPC5410X Timer用于捕获功能的用户配置文件 
 * \sa amdr_hwconfig_timer_cap.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_timer_cap.h"
#include "amdr_timer_cap.h"

/**
 * \addtogroup amdr_if_hwconfig_src_timer_cap
 * \copydoc amdr_hwconfig_timer_cap.c
 * @{
 */

/** \brief 定时器0用于捕获 IO配置信息 */
amdr_timer_cap_ioinfo_t __g_timer0_cap_ioinfo_list[] = {
    {PIO0_23,  PIO0_23_CT0_CAP0, PIO0_23_GPIO | PIO0_23_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO0_24,  PIO0_24_CT0_CAP1, PIO0_24_GPIO | PIO0_24_INPUT}, /**< \brief 通道 1, IO配置信息 */
    {PIO0_25,  PIO0_25_CT0_CAP2, PIO0_25_GPIO | PIO0_25_INPUT}, /**< \brief 通道 2, IO配置信息 */
    {PIO0_26,  PIO0_26_CT0_CAP3, PIO0_26_GPIO | PIO0_26_INPUT}, /**< \brief 通道 3, IO配置信息 */
};

/** \brief 定时器0用于捕获功能的设备信息 */
const amdr_timer_cap_devinfo_t  g_timer0_cap_devinfo = {
    AMHW_TIMER0,               /**< \brief 指向定时器0寄存器块的指针 */
    INUM_TIMER0,               /**< \brief 定时器0 中断编号 */
    4,                         /**< \brief 4个捕获通道      */
    &__g_timer0_cap_ioinfo_list[0],
};

/** \brief 定时器0用于捕获功能的设备定义  */
amdr_timer_cap_dev_t  g_timer0_cap_dev;

/** \brief 定时器0用于捕获功能平台初始化 */
void amhw_plfm_timer0_cap_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER0);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
}

/** \brief 定时器0用于捕获功能平台初始化 */
void amhw_plfm_timer0_cap_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER0);
}

/** \brief 定时器1用于捕获 IO配置信息 */
amdr_timer_cap_ioinfo_t __g_timer1_cap_ioinfo_list[] = {
    {PIO1_5,  PIO1_5_CT1_CAP0,  PIO1_5_GPIO  | PIO1_5_INPUT},  /**< \brief 通道 0, IO配置信息 */
    {PIO0_25, PIO0_25_CT1_CAP1, PIO0_25_GPIO | PIO0_25_INPUT}, /**< \brief 通道 1, IO配置信息 */
    {PIO1_6,  PIO1_6_CT1_CAP2,  PIO1_6_GPIO  | PIO1_6_INPUT},  /**< \brief 通道 2, IO配置信息 */
    {PIO1_8,  PIO1_8_CT1_CAP3,  PIO1_8_GPIO  | PIO1_8_INPUT},  /**< \brief 通道 3, IO配置信息 */
};

/** \brief 定时器1用于捕获功能的设备信息 */
const amdr_timer_cap_devinfo_t  g_timer1_cap_devinfo = {
    AMHW_TIMER1,               /**< \brief 指向定时器1寄存器块的指针 */
    INUM_TIMER1,               /**< \brief 定时器1 中断编号 */
    4,                         /**< \brief 4个捕获通道      */
    &__g_timer1_cap_ioinfo_list[0],
};

/** \brief 定时器1用于捕获功能的设备定义 */
amdr_timer_cap_dev_t  g_timer1_cap_dev;

/** \brief 定时器1用于捕获功能平台初始化 */
void amhw_plfm_timer1_cap_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER1);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
}

/** \brief 解除定时器1用于捕获功能平台初始化 */
void amhw_plfm_timer1_cap_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER1);
}

/** \brief 定时器2用于捕获 IO配置信息 */
amdr_timer_cap_ioinfo_t __g_timer2_cap_ioinfo_list[] = {
    {PIO0_27, PIO0_27_CT2_CAP0, PIO0_27_GPIO | PIO0_27_INPUT}, /**< \brief channel 0, IO information */
    {PIO0_2,  PIO0_2_CT2_CAP1,  PIO0_2_GPIO  | PIO0_2_INPUT},  /**< \brief channel 1, IO information */
    {PIO0_31, PIO0_31_CT2_CAP2, PIO0_31_GPIO | PIO1_6_INPUT},  /**< \brief channel 2, IO information */
};

/** \brief 定时器2用于捕获功能的设备信息 */
const amdr_timer_cap_devinfo_t  g_timer2_cap_devinfo = {
    AMHW_TIMER2,               /**< \brief 指向定时器2寄存器块的指针 */
    INUM_TIMER2,               /**< \brief 定时器2 中断编号 */
    3,                         /**< \brief 3个捕获通道      */
    &__g_timer2_cap_ioinfo_list[0],
};

/** \brief 定时器2用于捕获功能的设备定义 */
amdr_timer_cap_dev_t  g_timer2_cap_dev;

/** \brief 定时器2用于捕获功能平台初始化 */
void amhw_plfm_timer2_cap_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER2);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
}

/** \brief 解除定时器2用于捕获功能平台初始化 */
void amhw_plfm_timer2_cap_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER2);
}

/** \brief 定时器1用于捕获 IO配置信息 */
amdr_timer_cap_ioinfo_t __g_timer3_cap_ioinfo_list[] = {
    {PIO0_9, PIO0_9_CT3_CAP0, PIO0_9_GPIO | PIO0_9_INPUT}, /**< \brief channel 0, IO information */
};

/** \brief 定时器3用于捕获功能的设备信息 */
const amdr_timer_cap_devinfo_t  g_timer3_cap_devinfo = {
    AMHW_TIMER3,               /**< \brief 指向定时器3寄存器块的指针 */
    INUM_TIMER3,               /**< \brief 定时器3 中断编号 */
    1,                         /**< \brief 1个捕获通道      */
    &__g_timer3_cap_ioinfo_list[0],
};

/** \brief 定时器3用于捕获功能的设备定义 */
amdr_timer_cap_dev_t  g_timer3_cap_dev;

/** \brief 定时器3用于捕获功能平台初始化 */
void amhw_plfm_timer3_cap_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER3);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
}

/** \brief 解除定时器3用于捕获功能平台初始化 */
void amhw_plfm_timer3_cap_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER3);
}

/**
 * @}
 */

/* end of file */

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
 * \brief LPC5410X timer 用于定时器配置文件
 * \sa amdr_hwconfig_timer_timing.c 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_timer_timing.h"

/**
 * \addtogroup amdr_if_hwconfig_src_timer_timing
 * \copydoc amdr_hwconfig_timer_timing.c 
 * @{
 */

/** \brief 定时器0设备信息 */
const amdr_timer_timing_devinfo_t  g_timer0_timing_devinfo = {
    AMHW_TIMER0,                /**< \brief 指向定时器0寄存器块的指针  */
    INUM_TIMER0,                /**< \brief 定时器0中断号 */
};

/** \brief 定时器0设备 */
amdr_timer_timing_dev_t  g_timer0_timing_dev;

/** \brief 定时器0平台初始化 */
void amhw_plfm_timer0_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER0);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
}

/** \brief 解除定时器0平台初始化 */
void amhw_plfm_timer0_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER0);
}

/** \brief 定时器1设备信息 */
const amdr_timer_timing_devinfo_t  g_timer1_timing_devinfo = {
    AMHW_TIMER1,                /**< \brief 指向定时器1寄存器块的指针  */
    INUM_TIMER1,                /**< \brief 定时器1中断号 */
};

/** \brief 定时器1设备 */
amdr_timer_timing_dev_t  g_timer1_timing_dev;

/** \brief 定时器1平台初始化 */
void amhw_plfm_timer1_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER1);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
}

/** \brief 解除定时器1平台初始化 */
void amhw_plfm_timer1_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER1);
}

/** \brief 定时器2设备信息 */
const amdr_timer_timing_devinfo_t  g_timer2_timing_devinfo = {
    AMHW_TIMER2,                /**< \brief 指向定时器2寄存器块的指针  */
    INUM_TIMER2,                /**< \brief 定时器2中断号 */
};

/** \brief 定时器2设备 */
amdr_timer_timing_dev_t  g_timer2_timing_dev;

/** \brief 定时器2平台初始化 */
void amhw_plfm_timer2_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER2);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
}

/** \brief 解除定时器2平台初始化 */
void amhw_plfm_timer2_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER2);
}

/** \brief 定时器3设备信息 */
const amdr_timer_timing_devinfo_t  g_timer3_timing_devinfo = {
    AMHW_TIMER3,                /**< \brief 指向定时器3寄存器块的指针  */
    INUM_TIMER3,                /**< \brief 定时器3中断号 */
};

/** \brief 定时器3设备 */
amdr_timer_timing_dev_t  g_timer3_timing_dev;

/** \brief 定时器3平台初始化 */
void amhw_plfm_timer3_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER3);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
}

/** \brief 解除定时器3平台初始化 */
void amhw_plfm_timer3_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER3);
}

/** \brief 定时器4设备信息 */
const amdr_timer_timing_devinfo_t  g_timer4_timing_devinfo = {
    AMHW_TIMER4,                /**< \brief 指向定时器4寄存器块的指针  */
    INUM_TIMER4,                /**< \brief 定时器4中断号 */
};

/** \brief 定时器4设备 */
amdr_timer_timing_dev_t  g_timer4_timing_dev; 

/** \brief 定时器4平台初始化 */
void amhw_plfm_timer4_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER4);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER4);
}

/** \brief 解除定时器4平台初始化 */
void amhw_plfm_timer4_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER4);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER4);
}

/**
 * @}
 */

/* end of file */

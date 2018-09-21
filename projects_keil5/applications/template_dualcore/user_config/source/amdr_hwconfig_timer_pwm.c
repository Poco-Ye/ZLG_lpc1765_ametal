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
 * \brief LPC5410X Timer 用于PWM输出配置文件 
 * \sa amdr_hwconfig_timer_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_timer_pwm.h"

/**
 * \addtogroup amdr_if_hwconfig_src_timer_pwm
 * \copydoc amdr_hwconfig_timer_pwm.c
 * @{
 */

/** \brief 定时器0用于PWM输出 IO配置信息 */
amdr_timer_pwm_ioinfo_t __g_timer0_pwm_ioinfo_list[] = {
    {PIO1_16, PIO1_16_CT0_MAT0, PIO1_16_GPIO | PIO1_16_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO0_29, PIO0_29_CT0_MAT1, PIO0_29_GPIO | PIO0_29_INPUT}, /**< \brief 通道 1, IO配置信息 */
    {PIO0_7,  PIO0_7_CT0_MAT2,  PIO0_7_GPIO  | PIO0_7_INPUT},  /**< \brief 通道 2, IO配置信息 */
};

/** \brief 定时器0用于PWM输出的设备信息 */
const amdr_timer_pwm_devinfo_t  g_timer0_pwm_devinfo = {
    AMHW_TIMER0,               /**< \brief 指向定时器0寄存器块的指针 */
    3,                         /**< \brief 支持3个PWM输出通道        */
    &__g_timer0_pwm_ioinfo_list[0],
};

/** \brief 定时器0用于PWM输出的设备定义  */
amdr_timer_pwm_dev_t  g_timer0_pwm_dev;

/** \brief 定时器0用于PWM输出平台初始化 */
void amhw_plfm_timer0_pwm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER0);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
}

/** \brief 解除定时器0用于PWM输出平台初始化 */
void amhw_plfm_timer0_pwm_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER0);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER0);
}

/** \brief 定时器1用于PWM输出 IO配置信息 */
amdr_timer_pwm_ioinfo_t __g_timer1_pwm_ioinfo_list[] = {
    {PIO1_12, PIO1_12_CT1_MAT0, PIO1_12_GPIO | PIO1_12_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO1_13, PIO1_13_CT1_MAT1, PIO1_13_GPIO | PIO1_13_INPUT}, /**< \brief 通道 1, IO配置信息 */
    {PIO1_6,  PIO1_6_CT1_MAT2,  PIO1_6_GPIO  | PIO1_6_INPUT},  /**< \brief 通道 2, IO配置信息 */
};

/** \brief 定时器1用于PWM输出的设备信息 */
const amdr_timer_pwm_devinfo_t  g_timer1_pwm_devinfo = {
    AMHW_TIMER1,               /**< \brief 指向定时器1寄存器块的指针 */
    3,                         /**< \brief 支持3个PWM输出通道        */
    &__g_timer1_pwm_ioinfo_list[0],
};

/** \brief 定时器1用于PWM输出的设备定义  */
amdr_timer_pwm_dev_t  g_timer1_pwm_dev;

/** \brief 定时器1用于PWM输出平台初始化 */
void amhw_plfm_timer1_pwm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER1);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
}

/** \brief 解除定时器1用于PWM输出平台初始化 */
void amhw_plfm_timer1_pwm_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER1);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER1);
}

/** \brief 定时器2用于PWM输出 IO配置信息 */
amdr_timer_pwm_ioinfo_t __g_timer2_pwm_ioinfo_list[] = {
    {PIO0_13, PIO0_13_CT2_MAT0, PIO0_13_GPIO | PIO0_13_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO0_11, PIO0_11_CT2_MAT1, PIO0_11_GPIO | PIO0_11_INPUT}, /**< \brief 通道 1, IO配置信息 */
    {PIO0_15, PIO0_15_CT2_MAT2, PIO0_15_GPIO | PIO0_15_INPUT}, /**< \brief 通道 2, IO配置信息 */
};

/** \brief 定时器2用于PWM输出的设备信息 */
const amdr_timer_pwm_devinfo_t  g_timer2_pwm_devinfo = {
    AMHW_TIMER2,               /**< \brief 指向定时器2寄存器块的指针 */
    3,                         /**< \brief 支持3个PWM输出通道        */
    &__g_timer2_pwm_ioinfo_list[0],
};

/** \brief 定时器2用于PWM输出的设备定义  */
amdr_timer_pwm_dev_t  g_timer2_pwm_dev;

/** \brief 定时器2用于PWM输出平台初始化 */
void amhw_plfm_timer2_pwm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER2);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
}

/** \brief 解除定时器2用于PWM输出平台初始化 */
void amhw_plfm_timer2_pwm_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER2);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER2);
}

/** \brief 定时器3用于PWM输出 IO配置信息 */
amdr_timer_pwm_ioinfo_t __g_timer3_pwm_ioinfo_list[] = {
    {PIO0_10, PIO0_10_CT3_MAT0, PIO0_10_GPIO | PIO0_10_INPUT}, /**< \brief 通道 0, IO配置信息 */
    {PIO0_16, PIO0_16_CT3_MAT1, PIO0_16_GPIO | PIO0_16_INPUT}, /**< \brief 通道 1, IO配置信息 */
    {PIO0_17, PIO0_17_CT3_MAT2, PIO0_17_GPIO | PIO0_17_INPUT}, /**< \brief 通道 2, IO配置信息 */
};

/** \brief 定时器3用于PWM输出的设备信息 */
const amdr_timer_pwm_devinfo_t  g_timer3_pwm_devinfo = {
    AMHW_TIMER3,               /**< \brief 指向定时器3寄存器块的指针 */
    3,                         /**< \brief 支持3个PWM输出通道        */
    &__g_timer3_pwm_ioinfo_list[0],
};

/** \brief 定时器3用于PWM输出的设备定义  */
amdr_timer_pwm_dev_t  g_timer3_pwm_dev;

/** \brief 定时器3用于PWM输出平台初始化 */
void amhw_plfm_timer3_pwm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_TIMER3);
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
}

/** \brief 定时器3用于PWM输出平台初始化 */
void amhw_plfm_timer3_pwm_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_TIMER3);
    amhw_clock_periph_disable(AMHW_CLOCK_TIMER3);
}

/* 定时器4没有提供PWM输出引脚 */

/**
 * @}
 */

/* end of file */

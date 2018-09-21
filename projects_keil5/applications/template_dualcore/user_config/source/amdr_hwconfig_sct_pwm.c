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
 * \brief LPC5410X SCT0 用于PWM输出 用户配置文件 
 * \sa amdr_hwconfig_sct_pwm.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_sct_pwm.h"

/**
 * \addtogroup amdr_if_hwconfig_src_sct_pwm
 * \copydoc amdr_hwconfig_sct_pwm.c
 * @{
 */

/** \brief SCT0用于PWM功能的引脚配置信息列表 */
amdr_sct_pwm_ioinfo_t __g_sct0_pwm_ioinfo_list[] = {
    {PIO0_7,  PIO0_7_SCT0_OUT0,  PIO0_7_GPIO  | PIO0_7_INPUT},  /**< \brief  通道 0 */
    {PIO0_8,  PIO0_8_SCT0_OUT1,  PIO0_8_GPIO  | PIO0_8_INPUT},  /**< \brief  通道 1 */
    {PIO0_9,  PIO0_9_SCT0_OUT2,  PIO0_9_GPIO  | PIO0_9_INPUT},  /**< \brief  通道 2 */
    {PIO0_10, PIO0_10_SCT0_OUT3, PIO0_10_GPIO | PIO0_10_INPUT}, /**< \brief  通道 3 */
    {PIO0_13, PIO0_13_SCT0_OUT4, PIO0_13_GPIO | PIO0_13_INPUT}, /**< \brief  通道 4 */
    {PIO1_15, PIO1_15_SCT0_OUT5, PIO1_15_GPIO | PIO1_15_INPUT}, /**< \brief  通道 5 */
    {PIO0_5,  PIO0_5_SCT0_OUT6,  PIO0_5_GPIO  | PIO0_5_INPUT},  /**< \brief  通道 6 */
    {PIO1_4,  PIO1_4_SCT0_OUT7,  PIO1_4_GPIO  | PIO1_4_INPUT},  /**< \brief  通道 7 */
};

/** \brief SCT0用于PWM设备信息 */
const amdr_sct_pwm_devinfo_t  g_sct0_pwm_devinfo = {
    AMHW_SCT0,                  /**< \brief 指向SCT寄存器块的指针 */
    8,                          /**< \brief 8个PWM输出通道        */
    &__g_sct0_pwm_ioinfo_list[0],
};

/** \brief SCT0用于PWM设备定义 */
amdr_sct_pwm_dev_t  g_sct0_pwm_dev;

/** \brief SCT0用于PWM输出 平台初始化 */
void amhw_plfm_sct0_pwm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_SCT0);
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
}

/** \brief 解除SCT0平台初始化 */
void amhw_plfm_sct0_pwm_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
    amhw_clock_periph_disable(AMHW_CLOCK_SCT0);
}

/**
 * @}
 */

/* end of file */

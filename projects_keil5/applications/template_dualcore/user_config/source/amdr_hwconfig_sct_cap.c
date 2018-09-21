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
 * \brief LPC5410X SCT0 用于捕获功能的用户配置文件
 * \sa amdr_hwconfig_sct_cap.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_sct_cap.h"

/**
 * \addtogroup amdr_if_hwconfig_src_sct_cap
 * \copydoc amdr_hwconfig_sct_cap.c
 * @{
 */
 
/** \brief SCT0用于捕获功能的引脚配置信息列表 */
amdr_sct_cap_ioinfo_t __g_sct0_cap_ioinfo_list[] = {
    {PIO0_23, PIO0_23_GPIO | PIO0_23_INPUT , PIO0_23_GPIO | PIO0_23_INPUT}, /**< \brief 通道 0 */
    {PIO0_24, PIO0_24_GPIO | PIO0_24_INPUT , PIO0_24_GPIO | PIO0_24_INPUT}, /**< \brief 通道 1 */
    {PIO0_25, PIO0_25_GPIO | PIO0_25_INPUT | PIO0_25_DRIVEDISABLE | 
              PIO0_25_FILTERENABLE, PIO0_25_GPIO | PIO0_25_INPUT},          /**< \brief 通道 2 */
    {PIO0_26, PIO0_26_GPIO | PIO0_26_INPUT , PIO0_26_GPIO | PIO0_26_INPUT}, /**< \brief 通道 3 */
    {PIO0_27, PIO0_27_GPIO | PIO0_27_INPUT , PIO0_27_GPIO | PIO0_27_INPUT}, /**< \brief 通道 4 */
    {PIO0_28, PIO0_28_GPIO | PIO0_28_INPUT , PIO0_28_GPIO | PIO0_28_INPUT}, /**< \brief 通道 5 */
    {0,0,0},/**< \brief 通道6是ADC0阈值中断，可以作为SCT的捕获通道6的信号，无需IO配置 */
    {0,0,0},/**< \brief 通道7是调试停止信号，可以作为SCT的捕获通道7的信号，无需IO配置 */
};

/** \brief SCT0用于捕获功能的设备信息 */
const amdr_sct_cap_devinfo_t  g_sct0_cap_devinfo = {
    AMHW_SCT0,                 /**< \brief 指向SCT0寄存器块的指针 */
    INUM_SCT0,                 /**< \brief SCT0中断编号           */
    8,                         /**< \brief 8个捕获通道            */
    &__g_sct0_cap_ioinfo_list[0],
};

/** \brief SCT0用于捕获功能的设备定义 */
amdr_sct_cap_dev_t  g_sct0_cap_dev;

/** \brief SCT0用于捕获功能的平台初始化 */
void amhw_plfm_sct0_cap_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_SCT0);
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
}

/** \brief  解除SCT0平台初始化 */
void amhw_plfm_sct0_cap_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
    amhw_clock_periph_disable(AMHW_CLOCK_SCT0);
}

/**
 * @}
 */

/* end of file */

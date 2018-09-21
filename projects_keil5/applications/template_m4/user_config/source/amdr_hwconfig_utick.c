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
 * \brief LPC5410X UTICK定时器功能用户配置文件
 * \sa amdr_hwconfig_utick.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-12  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_utick.h"

/**
 * \addtogroup amdr_if_hwconfig_src_utick
 * \copydoc amdr_hwconfig_utick.c
 * @{
 */
 
/** \brief UTICK 设备信息 */
const amdr_utick_devinfo_t  g_utick_devinfo = {
    AMHW_UTICK,                /**< \brief 指向UTICK寄存器块的指针  */
    INUM_UTICK,                /**< \brief UTCIK中断号 */
};

/** \brief UTICK设备 */
amdr_utick_dev_t            g_utick_dev;

/** \brief UTICK 平台初始化 */
void amhw_plfm_utick_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_UTICK);
    amhw_syscon_periph_reset(AMHW_RESET_UTICK);
    
    amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);
    
    amhw_clock_wdt_freq_update();
}

/** \brief 解除 UTICK 平台初始化 */
void amhw_plfm_utick_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_UTICK);
    amhw_clock_periph_disable(AMHW_CLOCK_UTICK);
}

/**
 * @}
 */

/* end of file */

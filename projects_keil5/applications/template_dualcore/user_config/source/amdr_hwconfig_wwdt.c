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
 * \brief LPC5410X WWDT 用户配置文件 
 * \sa amdr_hwconfig_wwdt.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_wwdt.h"

/**
 * \addtogroup amdr_if_hwconfig_src_wwdt
 * \copydoc amdr_hwconfig_wwdt.c
 * @{
 */

/** \brief WWDT 设备信息 */
const amdr_wwdt_devinfo_t  g_wwdt_devinfo = {
    AMHW_WWDT,                 /* 指向WWDT寄存器块的指针 */
};

/** \brief WWDT设备实例  */
amdr_wwdt_dev_t            g_wwdt_dev;

/** \brief WWDT 平台初始化 */
void amhw_plfm_wwdt_init (void)
{
    /* 使能并复位WWDT时钟 */
    amhw_clock_periph_enable(AMHW_CLOCK_WWDT);
    amhw_syscon_periph_reset(AMHW_RESET_WWDT);
    
    /* 切换到WDT时钟源*/
    amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);

    amhw_clock_wdt_freq_update();
}

/** \brief 解除WWDT 平台初始化 */
void amhw_plfm_wwdt_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_WWDT);
    amhw_clock_periph_disable(AMHW_CLOCK_WWDT);
}

/**
 * @}
 */

/* end of file */

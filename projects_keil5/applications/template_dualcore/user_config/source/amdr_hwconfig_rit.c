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
 * \brief LPC5410X RIT 用于定时功能的用户配置文件 
 * \sa amdr_hwconfig_rit.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-12  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_rit.h"

/**
 * \addtogroup amdr_if_hwconfig_src_rit
 * \copydoc amdr_hwconfig_rit.c
 * @{
 */

/** 
 * \brief 由于RIT仅存在于M4内核，故RIT定时服务只能在M4内核中运行 
 */
#ifdef AM_CORTEX_M4

/** \brief RIT设备信息 */
const amdr_rit_devinfo_t  g_rit_devinfo = {
    AMHW_RIT,                  /**< \brief  指向RIT寄存器块的指针 */
    INUM_RIT,                  /**< \brief  RIT中断编号           */
};

/** \brief RIT设备定义 */
amdr_rit_dev_t            g_rit_dev;

/** \brief RIT 平台初始化 */
void amhw_plfm_rit_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_RIT);
    amhw_syscon_periph_reset(AMHW_RESET_RIT);
}

/** \brief 解除RIT 平台初始化 */
void amhw_plfm_rit_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_RIT);
    amhw_clock_periph_disable(AMHW_CLOCK_RIT);
}

#endif

/**
 * @}
 */

/* end of file */

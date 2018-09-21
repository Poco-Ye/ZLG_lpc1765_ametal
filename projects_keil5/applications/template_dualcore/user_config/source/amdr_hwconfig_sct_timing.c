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
 * \brief LPC5410X SCT 定时功能用户配置文件 
 * \sa amdr_hwconfig_sct_timing.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-12  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_sct_timing.h"

/**
 * \addtogroup amdr_if_hwconfig_src_sct_timing
 * \copydoc amdr_hwconfig_sct_timing.c
 * @{
 */

/** \brief SCT 设备信息 */
const amdr_sct_timing_devinfo_t  g_sct0_timing_devinfo = {
    AMHW_SCT0,                  /**< \brief 指向SCT寄存器块的指针  */
    AMDR_SCT_TIMING_2_16BIT,    /**< \brief SCT用于2个16-bit定时器 */
    INUM_SCT0,                  /**< \brief SCT0中断编号           */
};

/** \brief SCT设备定义  */
amdr_sct_timing_dev_t  g_sct0_timing_dev;

/** \brief SCT0 平台初始化 */
void amhw_plfm_sct0_timing_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_SCT0);
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
}

/** \brief 解除SCT0平台初始化 */
void amhw_plfm_sct0_timing_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
    amhw_clock_periph_disable(AMHW_CLOCK_SCT0);
}

/**
 * @}
 */

/* end of file */

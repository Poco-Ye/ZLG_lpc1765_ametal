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
 * \brief LPC5410X MRT用于定时功能的用户配置文件
 * \sa amdr_hwconfig_mrt.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_mrt.h"

/**
 * \addtogroup amdr_if_hwconfig_src_mrt
 * \copydoc amdr_hwconfig_mrt.c
 * @{
 */

/** \brief MRT设备信息 */
const amdr_mrt_devinfo_t  g_mrt_devinfo = {
    AMHW_MRT,                /**< \brief 指向MRT寄存器块的指针 */
    INUM_MRT,                /**< \brief MRT 中断编号          */
    4,                       /**< \brief 支持4个通道           */
};

amdr_mrt_dev_t  g_mrt_dev;   /**< \brief  MRT 设备定义 */

/** \brief MRT平台初始化 */
void amhw_plfm_mrt_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_MRT);
    amhw_syscon_periph_reset(AMHW_RESET_MRT);
}

/** \brief 解除MRT平台初始化 */
void amhw_plfm_mrt_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_MRT);
    amhw_clock_periph_disable(AMHW_CLOCK_MRT);
}

/**
 * @}
 */

/* end of file */

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
 * \brief LPC5410X CRC 用户配置文件 
 * \sa amdr_hwconfig_crc.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_crc.h"

/**
 * \addtogroup amdr_if_hwconfig_src_crc
 * \copydoc amdr_hwconfig_crc.c
 * @{
 */

/** \brief CRC 设备信息 */
const amdr_crc_devinfo_t  g_crc_devinfo = {
    AMHW_CRC,                /** \brief 指向CRC寄存器块的指针 */
};

/** \brief CRC设备定义 */
amdr_crc_dev_t            g_crc_dev;

/** \brief CRC平台初始化 */
void amhw_plfm_crc_init (void)
{
    /* 使能并复位CRC时钟 */
    amhw_clock_periph_enable(AMHW_CLOCK_CRC);
    amhw_syscon_periph_reset(AMHW_RESET_CRC);
 
}

/** \brief 解除CRC平台初始化 */
void amhw_plfm_crc_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_CRC);
    amhw_clock_periph_disable(AMHW_CLOCK_CRC);
}

/**
 * @}
 */

/* end of file */

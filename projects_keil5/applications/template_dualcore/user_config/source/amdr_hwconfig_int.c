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
 * \brief LPC5410X 中断用户配置文件。
 * \sa amdr_hwconfig_int.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-29  hbt, first implementation.
 * \endinternal
 */
 
#include "amdr_hwconfig_int.h"

/**
 * \addtogroup amdr_if_hwconfig_src_int
 * \copydoc amdr_hwconfig_int.c
 * @{
 */


/** \brief ISR 信息数量 */
#define __ISRINFO_COUNT    INUM_INTERNAL_COUNT

/** \brief 支持中断数量 */
struct amdr_int_isr_info __int_isr_infor[__ISRINFO_COUNT];

/** \brief ISR 信息映射 */
uint8_t __int_isr_map[INUM_INTERNAL_COUNT];


/** \brief 中断设备信息 */
const amdr_int_devinfo_t g_int_devinfo =
{
    {
        INUM_INTERNAL_MIN,  /**< \brief 中起始断号 */
        INUM_INTERNAL_MAX   /**< \brief 中末尾断号 */
    },

    AMHW_INT,               /**< \brief 指向中断控制器寄存器块的指针              */
    INUM_INTERNAL_COUNT,    /**< \brief 总中断数量                                */
    __int_isr_map,          /**< \brief ISR 信息映射(大小与 input_cnt 一致)       */
    __ISRINFO_COUNT,        /**< \brief ISR 信息数量                              */
    __int_isr_infor         /**< \brief ISR 信息映射内存(大小与 isrinfo_cnt 一致) */
};

/** \brief 中断设备实例 */
amdr_int_dev_t g_int_dev;


/**
 * @}
 */

/* end of file */

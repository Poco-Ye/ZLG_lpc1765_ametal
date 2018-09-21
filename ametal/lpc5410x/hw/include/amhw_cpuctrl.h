/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief CPU控制硬件操作接口
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-08  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_CPUCTRL_H
#define __AMHW_CPUCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
 
/**
 * \addtogroup amhw_if_cpuctrl
 * \copydoc amhw_cpuctrl.h
 * @{
 */
#define AMHW_CM4_CLK_ENABLE       (1 << 2)    /**< \brief M4核时钟使能  */
#define AMHW_CM0_CLK_ENABLE       (1 << 3)    /**< \brief M0+核时钟使能 */
#define AMHW_CM4_RESET_ENABLE     (1 << 4)    /**< \brief M4核复位使能  */
#define AMHW_CM0_RESET_ENABLE     (1 << 5)    /**< \brief M0+核复位使能 */

/**
 * \brief 是否运行M4内核程序
 * \retval  TRUE  : 运行M4内核程序
 * \retval  FALSE : 运行M0+内核程序
 */
bool_t amhw_cpu_is_m4core(void);

/**
 * \brief 当前的内核作为主机还是从机
 * \retval TRUE  : 主机
 * \retval FALSE : 从机
 */
bool_t amhw_cpu_is_master_core(void);

/**
 * \brief 使用M4内核启动M0+内核
 * \param[in] m0p_entryaddr : M0+内核入口地址
 * \return None
 */
void amhw_cpu_boot_m0p(uint32_t m0p_entryaddr);

/**
 * @} amhw_if_cpuctrl
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_CPUCTRL_H */ 

/* end of file */

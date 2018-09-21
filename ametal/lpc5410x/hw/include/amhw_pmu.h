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
 * \brief 电源管理单元访问接口
 * 
 * - 大多数电源管理通过电源管理库函数实现，在这里主要提供了BOD(Brown-out detector)
 *   相关的操作函数。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-08  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_PMU_H
#define __AMHW_PMU_H

#include "am_types.h"
#include "amhw_lpc5410x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * \addtogroup amhw_if_pmu  
 * \copydoc amhw_pmu.h
 * @{
 */
 
/**
 * \brief 电源管理寄存器块结构体
 */
typedef struct amhw_pmu {
    __I  uint32_t reserved0[4]; /**< \brief 保留,不应使用             */
    __I  uint32_t reserved1[4]; /**< \brief 保留,不应使用             */
    __I  uint32_t reserved2[4]; /**< \brief 保留,不应使用             */
    __I  uint32_t reserved3[4]; /**< \brief 保留,不应使用             */
    __I  uint32_t reserved4;    /**< \brief 保留,不应使用             */
    __IO uint32_t bodctrl;      /**< \brief BOD控制寄存器             */
    __I  uint32_t reserved5;    /**< \brief 保留,不应使用             */
    __I  uint32_t reserved6;    /**< \brief 保留,不应使用             */
    __IO uint32_t dpdwakesrc;   /**< \brief 深度掉电模式的唤醒源      */
} amhw_pmu_t;

/**
 * \brief 掉电检测复位的电源电压等级
 */
typedef enum amhw_pmu_bod_rst_level {
    AMHW_PMU_BODRSTLVL_0,                            /**< \brief 等级0，1.5V  */
    AMHW_PMU_BODRSTLVL_1_50V = AMHW_PMU_BODRSTLVL_0, /**< \brief 等级0，1.5V  */
    AMHW_PMU_BODRSTLVL_1,                            /**< \brief 等级1，1.85V */
    AMHW_PMU_BODRSTLVL_1_85V = AMHW_PMU_BODRSTLVL_1, /**< \brief 等级1，1.85V */
    AMHW_PMU_BODRSTLVL_2,                            /**< \brief 等级2，2.0V  */
    AMHW_PMU_BODRSTLVL_2_00V = AMHW_PMU_BODRSTLVL_2, /**< \brief 等级2，2.0V  */
    AMHW_PMU_BODRSTLVL_3,                            /**< \brief 等级3，2.3V  */
    AMHW_PMU_BODRSTLVL_2_30V = AMHW_PMU_BODRSTLVL_3  /**< \brief 等级3，2.3V  */
} amhw_pmu_bod_rst_level_t;

/**
 * \brief 掉电检测中断的电源电压等级
 */
typedef enum amHW_pmu_bod_int_level {
    AMHW_PMU_BODINTLVL_0,                            /**< \brief 等级0，2.05V */
    AMHW_PMU_BODINTLVL_2_05V = AMHW_PMU_BODINTLVL_0, /**< \brief 等级0，2.05V */
    AMHW_PMU_BODINTLVL_1,                            /**< \brief 等级1，2.45V */
    AMHW_PMU_BODINTLVL_2_45V = AMHW_PMU_BODINTLVL_1, /**< \brief 等级1，2.45V */
    AMHW_PMU_BODINTLVL_2,                            /**< \brief 等级2，2.75V */
    AMHW_PMU_BODINTLVL_2_75V = AMHW_PMU_BODINTLVL_2, /**< \brief 等级2，2.75V */
    AMHW_PMU_BODINTLVL_3,                            /**< \brief 等级3，3.05V */
    AMHW_PMU_BODINTLVL_3_05V = AMHW_PMU_BODINTLVL_3  /**< \brief 等级3，3.05V */
} amhw_pmu_bod_int_level_t;


/**
 * \brief 设置掉电检测中断和掉电检测复位的电源电压等级
 *
 * \param[in] rstlvl : 掉电检测复位电压等级
 * \param[in] intlvl : 掉电检测中断电压等级
 *
 * \return 无
 */
am_static_inline 
void amhw_pmu_bod_level_set (amhw_pmu_bod_rst_level_t rstlvl,
                             amhw_pmu_bod_int_level_t intlvl)
{
    AMHW_PMU->bodctrl = ((uint32_t)rstlvl) | (((uint32_t)intlvl) << 2);
}

/**
 * \brief 使能掉电检测复位
 * \return 无
 */
am_static_inline 
void amhw_pmu_bod_rst_enable (void)
{
    AMHW_PMU->bodctrl |= (1 << 4);
}

/**
 * \brief 禁能掉电检测复位
 * \return 无
 */
am_static_inline 
void amhw_pmu_bod_rst_disable (void)
{
    AMHW_PMU->bodctrl &= ~(1 << 4);
}

/**
 * \brief 使能掉电检测中断
 * \return 无
 */
am_static_inline 
void amhw_pmu_bod_int_enable (void)
{
    AMHW_PMU->bodctrl |= (1 << 5);
}

/**
 * \brief 禁能掉电检测中断
 * \return 无
 */
am_static_inline 
void amhw_pmu_bod_int_disable (void)
{
    AMHW_PMU->bodctrl &= ~(1 << 5);
}

/**
 * \brief 检测BOD复位是否发生
 * \retval TRUE  : BOD复位发生
 * \retval FALSE : BOD复位未发生
 */
am_static_inline 
bool_t amhw_pmu_bod_rst_flag_chk (void)
{
    return (bool_t)((AMHW_PMU->bodctrl & (1 << 6)) != 0);
}

/**
 * \brief 检测BOD中断是否发生
 * \retval TRUE  : BOD中断发生
 * \retval FALSE : BOD中断未发生
 */
am_static_inline 
bool_t amhw_pmu_bod_int_flag_chk (void)
{
    return (bool_t)((AMHW_PMU->bodctrl & (1 << 7)) != 0);
}

/**
 * \name 深度掉电模式复位源
 * @{
 */
 
/** \brief 外部管脚复位              */
#define AMHW_PMU_DPDWU_RESET     (1 << 0)  

/** \brief RTC唤醒复位               */
#define AMHW_PMU_DPDWU_RTC       (1 << 1)  

/** \brief 掉电检测复位              */
#define AMHW_PMU_DPDWU_BODRESET  (1 << 2)  

/** \brief 掉电检测中断唤醒复位      */
#define AMHW_PMU_DPDWU_BODINTR   (1 << 3)  

 /** @} */

/**
 * \brief 获取深度掉电模式的唤醒源
 * \return 深度掉电模式的唤醒源。AMHW_PMU_DPDWU_*如：(#AMHW_PMU_DPDWU_RESET) 
 */
am_static_inline 
uint32_t am_pmu_dpd_wusrc_get (void)
{
    return AMHW_PMU->dpdwakesrc;
}

/**
 * \brief 清除深度掉电模式唤醒源
 * \param[in] mask : AMHW_PMU_DPDWU_*宏值或多个AMHW_PMU_DPDWU_*宏的或值
 *                   如：(#AMHW_PMU_DPDWU_RESET)
 * \return 无
 */
am_static_inline 
void am_pmu_dpd_wusrc_clr (uint32_t mask)
{
    AMHW_PMU->dpdwakesrc = mask;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PMU_H */

/* end of file */

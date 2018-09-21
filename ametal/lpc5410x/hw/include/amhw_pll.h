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
 * \brief  PLL配置接口
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_PLL_H
#define __AMHW_PLL_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"

/**
 * \addtogroup amhw_if_pll
 * \copydoc amhw_pll.h
 * @{
 */

/**
 * \brief PLL输入时钟源
 */
typedef enum amhw_pll_clksrc {
    AMHW_PLL_CLKSRC_IRC = 0,          /**< \brief 内部IRC       */
    AMHW_PLL_CLKSRC_CLKIN,            /**< \brief 外部时钟输入  */
    AMHW_PLL_CLKSRC_WDTOSC,           /**< \brief WDT晶体振荡器 */
    AMHW_PLL_CLKSRC_RTC,              /**< \brief RTC晶体振荡器 */
} amhw_pll_clksrc_t;

/**
 * \brief PLL 频展 (Spread Spectrum) 的调制频率
 */
typedef enum amhw_pll_ss_pmf {
    AMHW_PLL_SS_MF_512 = (0 << 20),  /**< \brief Nss = 512 (fm 3.9 - 7.8 kHz)   */
    AMHW_PLL_SS_MF_384 = (1 << 20),  /**< \brief Nss = 384 (fm 5.2 - 10.4 kHz)  */
    AMHW_PLL_SS_MF_256 = (2 << 20),  /**< \brief Nss = 256 (fm 7.8 - 15.6 kHz)  */
    AMHW_PLL_SS_MF_128 = (3 << 20),  /**< \brief Nss = 128 (fm 15.6 - 31.3 kHz) */
    AMHW_PLL_SS_MF_64  = (4 << 20),  /**< \brief Nss = 64 (fm 32.3 - 64.5 kHz)  */
    AMHW_PLL_SS_MF_32  = (5 << 20),  /**< \brief Nss = 32 (fm 62.5- 125 kHz)    */
    AMHW_PLL_SS_MF_24  = (6 << 20),  /**< \brief Nss = 24 (fm 83.3- 166.6 kHz)  */
    AMHW_PLL_SS_MF_16  = (7 << 20)   /**< \brief Nss = 16 (fm 125- 250 kHz)     */
} amhw_pll_ss_pmf_t;

/**
 * \brief PLL 频展 (Spread Spectrum) 的调制深度
 */
typedef enum amhw_pll_ss_pfmd {
    AMHW_PLL_SS_MR_K0   = (0 << 23),  /**< \brief k = 0 (无频展) */
    AMHW_PLL_SS_MR_K1   = (1 << 23),  /**< \brief k = 1          */
    AMHW_PLL_SS_MR_K1_5 = (2 << 23),  /**< \brief k = 1.5        */
    AMHW_PLL_SS_MR_K2   = (3 << 23),  /**< \brief k = 2          */
    AMHW_PLL_SS_MR_K3   = (4 << 23),  /**< \brief k = 3          */
    AMHW_PLL_SS_MR_K4   = (5 << 23),  /**< \brief k = 4          */
    AMHW_PLL_SS_MR_K6   = (6 << 23),  /**< \brief k = 6          */
    AMHW_PLL_SS_MR_K8   = (7 << 23)   /**< \brief k = 8          */
} amhw_pll_ss_pfmd_t;

/**
 * \brief PLL 频展 (Spread Spectrum) 的调制波形控制
 *
 * 对PLL的低通滤波器进行补偿，以在PLL输出得到一个三角调制波形，从而提供一个平坦的频谱
 */
typedef enum {
    AMHW_PLL_SS_MC_NOC  = (0 << 26),  /**< \brief 无补偿            */
    AMHW_PLL_SS_MC_RECC = (2 << 26),  /**< \brief 建议设置的补偿值  */
    AMHW_PLL_SS_MC_MAXC = (3 << 26),  /**< \brief 最大补偿          */
} amhw_pll_ss_mwctrl_t;

/**
 * \name PLL配置标志（用于PLL配置结构体的flags成员）
 * @{
 */

/**
 * \brief 使用 input_rate 指定PLL输入时钟频率值
 *
 *     如果使用了该标志, 则配置结构体中的 input_rate 成员需要设置为正确的PLL输入
 * 时钟频率。
 *     如果未使用该标志，则 input_rate 设置值将会被忽略，将由驱动自动的根据当前
 * 的PLL时钟源确定PLL输入时钟频率。
 *
 */
#define AMHW_PLL_CONFIG_FLAG_USEINRATE    (1 << 0)

/**
 * \brief 强制不使用PLL的部分功能
 *
 *     如果使用了该标志，则PLL的自动波特率选择(automatic bandwidth selection)、
 * 频展支持(Spread Spectrum (SS) support)、小数M除法器将不会使用。
 *
 */
#define AMHW_PLL_CONFIG_FLAG_FORCENOFRACT (1 << 2)

/** @} */

/**
 * \brief PLL 配置结构体
 */
typedef struct amhw_pll_config {

    /** \brief  PLL 配置标志       */
    uint32_t           flags;

    /** \brief  PLL的期望输出频率  */
    uint32_t           desired_rate;

    /**
     * \brief PLL输入频率（单位：Hz）
     *  仅当 AMHW_PLL_CONFIG_FLAG_USEINRATE 标志被设置时有效。
     */
    uint32_t           input_rate;

    /**
     * \brief PLL 频展 (Spread Spectrum) 的调制频率
     *  仅当 AMHW_PLL_CONFIG_FLAG_FORCENOFRACT 标志未被设置时有效。
     */
    amhw_pll_ss_pmf_t    ss_mf;

    /**
     * \brief PLL 频展 (Spread Spectrum) 的调制深度
     *  仅当 AMHW_PLL_CONFIG_FLAG_FORCENOFRACT 标志未被设置时有效。
     */
    amhw_pll_ss_pfmd_t   ss_mr;

    /**
     * \brief PLL 频展 (Spread Spectrum) 的波形控制
     *  仅当 AMHW_PLL_CONFIG_FLAG_FORCENOFRACT 标志未被设置时有效。
     */
    amhw_pll_ss_mwctrl_t ss_mc;

    /**
     * \brief 调制频率设置
     *  FALSE：固定调制频率，TRUE ：调制频率有一定的抖动
     *  仅当 AMHW_PLL_CONFIG_FLAG_FORCENOFRACT 标志未被设置时有效。
     */
    bool_t             mf_dither;

} amhw_pll_config_t;

/**
 * \name PLL建立标志（用于PLL建立结构体的flags成员）
 * @{
 */

/** \brief PLL建立后需要打开PLL电源                 */
#define AMHW_PLL_SETUP_FLAG_POWERUP   (1 << 0)

/** \brief PLL建立后需要等待PLL锁定                 */
#define AMHW_PLL_SETUP_FLAG_WAITLOCK  (1 << 1)

/** \brief PLL建立后针对新的PLL输出频率优化系统电压  */
#define AMHW_PLL_SETUPFLAG_ADGVOLT    (1 << 2)

/** @} */

/**
 * \brief PLL 建立结构体
 */
typedef struct amhw_pll_setup {
    uint32_t  flags;             /**< \brief  PLL 建立标志         */
    uint32_t  pllctrl;           /**< \brief  PLL 控制寄存器       */
    uint32_t  pllndec;           /**< \brief  PLL NDEC 寄存器      */
    uint32_t  pllpdec;           /**< \brief  PLL PDEC 寄存器      */
    uint32_t  pllssctrl[2];      /**< \brief  PLL SSCTL 寄存器     */
} amhw_pll_setup_t;

/**
 * \brief PLL 状态定义
 */
typedef enum {
    AMHW_PLL_SUCCESS = 0,        /**< \brief PLL 操作成功                */
    AMHW_PLL_OUTPUT_TOO_LOW,     /**< \brief PLL 输出频率太低            */
    AMHW_PLL_OUTPUT_TOO_HIGH,    /**< \brief PLL 输出频率太高            */
    AMHW_PLL_INPUT_TOO_LOW,      /**< \brief PLL 输入频率太低            */
    AMHW_PLL_INPUT_TOO_HIGH,     /**< \brief PLL 输入频率太高            */
    AMHW_PLL_OUTSIDE_INTLIMIT,   /**< \brief 请求的PLL输出频率是不可能的 */
} amhw_pll_stat_t;

/**
 * \brief 设置PLL输入时钟源
 * \param[in] src : PLL输入时钟源
 * \return 无
 * \note 在切换PLL输入时钟时，需要确保PLL电源处于关闭状态
 */
am_static_inline
void amhw_pll_clksrc_set (amhw_pll_clksrc_t src)
{
    AMHW_SYSCON->syspllclksel = (uint32_t) src;
}

/**
 * \brief 得到PLL的输入时钟频率
 * \return PLL的输入时钟频率
 */
uint32_t amhw_pll_in_clkrate_get(void);

/**
 * \brief 得到PLL的输出时钟频率
 * \return PLL的输出时钟频率
 */
uint32_t amhw_pll_out_clkrate_get(void);

/**
 * \brief 使能或禁能PLL的旁路模式
 * \param[in] bypass : TRUE  使能PLL旁路模式 (PLL output = PLL input)
 *                     FALSE 禁能PLL旁路模式
 * \return 无
 */
void amhw_pll_bypass_set(bool_t bypass);

/**
 * \brief 检查PLL是否锁定
 * \retval  TRUE  : PLL已锁定.
 * \retval  FALSE : PLL未锁定.
 */
am_static_inline
bool_t amhw_pll_locked_chk (void)
{
    return (bool_t)((AMHW_SYSCON->syspllstat & 1) != 0);
}

/**
 * \brief 从PLL建立结构体得到PLL的输出频率
 * \param[in] p_setup : 指向PLL建立结构体
 * \return 由PLL建立结构体得到PLL的输出频率
 */
uint32_t amhw_pll_out_clkrate_fromsetup(amhw_pll_setup_t *p_setup);

/**
 * \brief 根据PLL配置结构体数据设置PLL建立结构体数据
 *
 * \param[in] p_configure : 指向填充好数据的PLL配置结构体
 * \param[in] p_setup     : 指向待填充数据的PLL建立结构体
 *
 * \return PLL设置的状态
 *
 * \note 实际设置的频率可能与配置结构体中的期望频率有偏差
 */
amhw_pll_stat_t amhw_pll_setup_plldata(amhw_pll_config_t *p_configure,
                                       amhw_pll_setup_t  *p_setup);

/**
 * \brief 根据PLL建立结构体设置PLL输出频率(高精度模式)
 * \param[in] p_setup : 指向填充好数据的PLL建立结构体
 * \return PLL设置的状态
 *
 * \note 该函数将会在设置之前关闭PLL电源
 */
amhw_pll_stat_t amhw_pll_setup_prec(amhw_pll_setup_t *p_setup);


/**
 * \brief 根据输入频率和倍频系数设置PLL
 *
 * 该函数是一个简单的PLL配置函数，直接将输入频率倍频整数倍
 *
 * \param[in] multiply_by : 倍频系数
 * \param[in] input_freq  : PLL输入时钟频率
 *
 * \return None
 *
 * \note 该函数在设置PLL前，不会关闭PLL电源，因此，必须在调用该函数前关闭PLL电源
 */
void amhw_pll_setup_multiby(uint32_t multiply_by, uint32_t input_freq);


/**
 * \brief 配置PLL，一个通用的函数
 *
 * 通常情况下，调用该函数即可实现PLL基本设置。
 *
 * \param[in] clksrc        : PLL输入时钟源
 * \param[in] desiredrate   : 期望的PLL输出频率
 * \param[in] usepllprecise : 是否使用PLL频展(Spread Spectrum)
 *
 * \return PLL设置的状态
 *
 * \note 当usepllprecise为TRUE时，PLL输入时钟源不能为AMHW_PLL_CLKSRC_RTC
 */

amhw_pll_stat_t amhw_pll_config(amhw_pll_clksrc_t clksrc,
                                uint32_t          desiredrate,
                                bool_t            usepllprecise);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PLL_H */

/* end of file */

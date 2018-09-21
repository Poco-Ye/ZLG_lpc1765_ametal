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
 * \brief  PLL���ýӿ�
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
 * \brief PLL����ʱ��Դ
 */
typedef enum amhw_pll_clksrc {
    AMHW_PLL_CLKSRC_IRC = 0,          /**< \brief �ڲ�IRC       */
    AMHW_PLL_CLKSRC_CLKIN,            /**< \brief �ⲿʱ������  */
    AMHW_PLL_CLKSRC_WDTOSC,           /**< \brief WDT�������� */
    AMHW_PLL_CLKSRC_RTC,              /**< \brief RTC�������� */
} amhw_pll_clksrc_t;

/**
 * \brief PLL Ƶչ (Spread Spectrum) �ĵ���Ƶ��
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
 * \brief PLL Ƶչ (Spread Spectrum) �ĵ������
 */
typedef enum amhw_pll_ss_pfmd {
    AMHW_PLL_SS_MR_K0   = (0 << 23),  /**< \brief k = 0 (��Ƶչ) */
    AMHW_PLL_SS_MR_K1   = (1 << 23),  /**< \brief k = 1          */
    AMHW_PLL_SS_MR_K1_5 = (2 << 23),  /**< \brief k = 1.5        */
    AMHW_PLL_SS_MR_K2   = (3 << 23),  /**< \brief k = 2          */
    AMHW_PLL_SS_MR_K3   = (4 << 23),  /**< \brief k = 3          */
    AMHW_PLL_SS_MR_K4   = (5 << 23),  /**< \brief k = 4          */
    AMHW_PLL_SS_MR_K6   = (6 << 23),  /**< \brief k = 6          */
    AMHW_PLL_SS_MR_K8   = (7 << 23)   /**< \brief k = 8          */
} amhw_pll_ss_pfmd_t;

/**
 * \brief PLL Ƶչ (Spread Spectrum) �ĵ��Ʋ��ο���
 *
 * ��PLL�ĵ�ͨ�˲������в���������PLL����õ�һ�����ǵ��Ʋ��Σ��Ӷ��ṩһ��ƽ̹��Ƶ��
 */
typedef enum {
    AMHW_PLL_SS_MC_NOC  = (0 << 26),  /**< \brief �޲���            */
    AMHW_PLL_SS_MC_RECC = (2 << 26),  /**< \brief �������õĲ���ֵ  */
    AMHW_PLL_SS_MC_MAXC = (3 << 26),  /**< \brief ��󲹳�          */
} amhw_pll_ss_mwctrl_t;

/**
 * \name PLL���ñ�־������PLL���ýṹ���flags��Ա��
 * @{
 */

/**
 * \brief ʹ�� input_rate ָ��PLL����ʱ��Ƶ��ֵ
 *
 *     ���ʹ���˸ñ�־, �����ýṹ���е� input_rate ��Ա��Ҫ����Ϊ��ȷ��PLL����
 * ʱ��Ƶ�ʡ�
 *     ���δʹ�øñ�־���� input_rate ����ֵ���ᱻ���ԣ����������Զ��ĸ��ݵ�ǰ
 * ��PLLʱ��Դȷ��PLL����ʱ��Ƶ�ʡ�
 *
 */
#define AMHW_PLL_CONFIG_FLAG_USEINRATE    (1 << 0)

/**
 * \brief ǿ�Ʋ�ʹ��PLL�Ĳ��ֹ���
 *
 *     ���ʹ���˸ñ�־����PLL���Զ�������ѡ��(automatic bandwidth selection)��
 * Ƶչ֧��(Spread Spectrum (SS) support)��С��M������������ʹ�á�
 *
 */
#define AMHW_PLL_CONFIG_FLAG_FORCENOFRACT (1 << 2)

/** @} */

/**
 * \brief PLL ���ýṹ��
 */
typedef struct amhw_pll_config {

    /** \brief  PLL ���ñ�־       */
    uint32_t           flags;

    /** \brief  PLL���������Ƶ��  */
    uint32_t           desired_rate;

    /**
     * \brief PLL����Ƶ�ʣ���λ��Hz��
     *  ���� AMHW_PLL_CONFIG_FLAG_USEINRATE ��־������ʱ��Ч��
     */
    uint32_t           input_rate;

    /**
     * \brief PLL Ƶչ (Spread Spectrum) �ĵ���Ƶ��
     *  ���� AMHW_PLL_CONFIG_FLAG_FORCENOFRACT ��־δ������ʱ��Ч��
     */
    amhw_pll_ss_pmf_t    ss_mf;

    /**
     * \brief PLL Ƶչ (Spread Spectrum) �ĵ������
     *  ���� AMHW_PLL_CONFIG_FLAG_FORCENOFRACT ��־δ������ʱ��Ч��
     */
    amhw_pll_ss_pfmd_t   ss_mr;

    /**
     * \brief PLL Ƶչ (Spread Spectrum) �Ĳ��ο���
     *  ���� AMHW_PLL_CONFIG_FLAG_FORCENOFRACT ��־δ������ʱ��Ч��
     */
    amhw_pll_ss_mwctrl_t ss_mc;

    /**
     * \brief ����Ƶ������
     *  FALSE���̶�����Ƶ�ʣ�TRUE ������Ƶ����һ���Ķ���
     *  ���� AMHW_PLL_CONFIG_FLAG_FORCENOFRACT ��־δ������ʱ��Ч��
     */
    bool_t             mf_dither;

} amhw_pll_config_t;

/**
 * \name PLL������־������PLL�����ṹ���flags��Ա��
 * @{
 */

/** \brief PLL��������Ҫ��PLL��Դ                 */
#define AMHW_PLL_SETUP_FLAG_POWERUP   (1 << 0)

/** \brief PLL��������Ҫ�ȴ�PLL����                 */
#define AMHW_PLL_SETUP_FLAG_WAITLOCK  (1 << 1)

/** \brief PLL����������µ�PLL���Ƶ���Ż�ϵͳ��ѹ  */
#define AMHW_PLL_SETUPFLAG_ADGVOLT    (1 << 2)

/** @} */

/**
 * \brief PLL �����ṹ��
 */
typedef struct amhw_pll_setup {
    uint32_t  flags;             /**< \brief  PLL ������־         */
    uint32_t  pllctrl;           /**< \brief  PLL ���ƼĴ���       */
    uint32_t  pllndec;           /**< \brief  PLL NDEC �Ĵ���      */
    uint32_t  pllpdec;           /**< \brief  PLL PDEC �Ĵ���      */
    uint32_t  pllssctrl[2];      /**< \brief  PLL SSCTL �Ĵ���     */
} amhw_pll_setup_t;

/**
 * \brief PLL ״̬����
 */
typedef enum {
    AMHW_PLL_SUCCESS = 0,        /**< \brief PLL �����ɹ�                */
    AMHW_PLL_OUTPUT_TOO_LOW,     /**< \brief PLL ���Ƶ��̫��            */
    AMHW_PLL_OUTPUT_TOO_HIGH,    /**< \brief PLL ���Ƶ��̫��            */
    AMHW_PLL_INPUT_TOO_LOW,      /**< \brief PLL ����Ƶ��̫��            */
    AMHW_PLL_INPUT_TOO_HIGH,     /**< \brief PLL ����Ƶ��̫��            */
    AMHW_PLL_OUTSIDE_INTLIMIT,   /**< \brief �����PLL���Ƶ���ǲ����ܵ� */
} amhw_pll_stat_t;

/**
 * \brief ����PLL����ʱ��Դ
 * \param[in] src : PLL����ʱ��Դ
 * \return ��
 * \note ���л�PLL����ʱ��ʱ����Ҫȷ��PLL��Դ���ڹر�״̬
 */
am_static_inline
void amhw_pll_clksrc_set (amhw_pll_clksrc_t src)
{
    AMHW_SYSCON->syspllclksel = (uint32_t) src;
}

/**
 * \brief �õ�PLL������ʱ��Ƶ��
 * \return PLL������ʱ��Ƶ��
 */
uint32_t amhw_pll_in_clkrate_get(void);

/**
 * \brief �õ�PLL�����ʱ��Ƶ��
 * \return PLL�����ʱ��Ƶ��
 */
uint32_t amhw_pll_out_clkrate_get(void);

/**
 * \brief ʹ�ܻ����PLL����·ģʽ
 * \param[in] bypass : TRUE  ʹ��PLL��·ģʽ (PLL output = PLL input)
 *                     FALSE ����PLL��·ģʽ
 * \return ��
 */
void amhw_pll_bypass_set(bool_t bypass);

/**
 * \brief ���PLL�Ƿ�����
 * \retval  TRUE  : PLL������.
 * \retval  FALSE : PLLδ����.
 */
am_static_inline
bool_t amhw_pll_locked_chk (void)
{
    return (bool_t)((AMHW_SYSCON->syspllstat & 1) != 0);
}

/**
 * \brief ��PLL�����ṹ��õ�PLL�����Ƶ��
 * \param[in] p_setup : ָ��PLL�����ṹ��
 * \return ��PLL�����ṹ��õ�PLL�����Ƶ��
 */
uint32_t amhw_pll_out_clkrate_fromsetup(amhw_pll_setup_t *p_setup);

/**
 * \brief ����PLL���ýṹ����������PLL�����ṹ������
 *
 * \param[in] p_configure : ָ���������ݵ�PLL���ýṹ��
 * \param[in] p_setup     : ָ���������ݵ�PLL�����ṹ��
 *
 * \return PLL���õ�״̬
 *
 * \note ʵ�����õ�Ƶ�ʿ��������ýṹ���е�����Ƶ����ƫ��
 */
amhw_pll_stat_t amhw_pll_setup_plldata(amhw_pll_config_t *p_configure,
                                       amhw_pll_setup_t  *p_setup);

/**
 * \brief ����PLL�����ṹ������PLL���Ƶ��(�߾���ģʽ)
 * \param[in] p_setup : ָ���������ݵ�PLL�����ṹ��
 * \return PLL���õ�״̬
 *
 * \note �ú�������������֮ǰ�ر�PLL��Դ
 */
amhw_pll_stat_t amhw_pll_setup_prec(amhw_pll_setup_t *p_setup);


/**
 * \brief ��������Ƶ�ʺͱ�Ƶϵ������PLL
 *
 * �ú�����һ���򵥵�PLL���ú�����ֱ�ӽ�����Ƶ�ʱ�Ƶ������
 *
 * \param[in] multiply_by : ��Ƶϵ��
 * \param[in] input_freq  : PLL����ʱ��Ƶ��
 *
 * \return None
 *
 * \note �ú���������PLLǰ������ر�PLL��Դ����ˣ������ڵ��øú���ǰ�ر�PLL��Դ
 */
void amhw_pll_setup_multiby(uint32_t multiply_by, uint32_t input_freq);


/**
 * \brief ����PLL��һ��ͨ�õĺ���
 *
 * ͨ������£����øú�������ʵ��PLL�������á�
 *
 * \param[in] clksrc        : PLL����ʱ��Դ
 * \param[in] desiredrate   : ������PLL���Ƶ��
 * \param[in] usepllprecise : �Ƿ�ʹ��PLLƵչ(Spread Spectrum)
 *
 * \return PLL���õ�״̬
 *
 * \note ��usepllpreciseΪTRUEʱ��PLL����ʱ��Դ����ΪAMHW_PLL_CLKSRC_RTC
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

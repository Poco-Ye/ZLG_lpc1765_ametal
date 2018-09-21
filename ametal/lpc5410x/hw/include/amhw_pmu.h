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
 * \brief ��Դ����Ԫ���ʽӿ�
 * 
 * - �������Դ����ͨ����Դ����⺯��ʵ�֣���������Ҫ�ṩ��BOD(Brown-out detector)
 *   ��صĲ���������
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
 * \brief ��Դ����Ĵ�����ṹ��
 */
typedef struct amhw_pmu {
    __I  uint32_t reserved0[4]; /**< \brief ����,��Ӧʹ��             */
    __I  uint32_t reserved1[4]; /**< \brief ����,��Ӧʹ��             */
    __I  uint32_t reserved2[4]; /**< \brief ����,��Ӧʹ��             */
    __I  uint32_t reserved3[4]; /**< \brief ����,��Ӧʹ��             */
    __I  uint32_t reserved4;    /**< \brief ����,��Ӧʹ��             */
    __IO uint32_t bodctrl;      /**< \brief BOD���ƼĴ���             */
    __I  uint32_t reserved5;    /**< \brief ����,��Ӧʹ��             */
    __I  uint32_t reserved6;    /**< \brief ����,��Ӧʹ��             */
    __IO uint32_t dpdwakesrc;   /**< \brief ��ȵ���ģʽ�Ļ���Դ      */
} amhw_pmu_t;

/**
 * \brief �����⸴λ�ĵ�Դ��ѹ�ȼ�
 */
typedef enum amhw_pmu_bod_rst_level {
    AMHW_PMU_BODRSTLVL_0,                            /**< \brief �ȼ�0��1.5V  */
    AMHW_PMU_BODRSTLVL_1_50V = AMHW_PMU_BODRSTLVL_0, /**< \brief �ȼ�0��1.5V  */
    AMHW_PMU_BODRSTLVL_1,                            /**< \brief �ȼ�1��1.85V */
    AMHW_PMU_BODRSTLVL_1_85V = AMHW_PMU_BODRSTLVL_1, /**< \brief �ȼ�1��1.85V */
    AMHW_PMU_BODRSTLVL_2,                            /**< \brief �ȼ�2��2.0V  */
    AMHW_PMU_BODRSTLVL_2_00V = AMHW_PMU_BODRSTLVL_2, /**< \brief �ȼ�2��2.0V  */
    AMHW_PMU_BODRSTLVL_3,                            /**< \brief �ȼ�3��2.3V  */
    AMHW_PMU_BODRSTLVL_2_30V = AMHW_PMU_BODRSTLVL_3  /**< \brief �ȼ�3��2.3V  */
} amhw_pmu_bod_rst_level_t;

/**
 * \brief �������жϵĵ�Դ��ѹ�ȼ�
 */
typedef enum amHW_pmu_bod_int_level {
    AMHW_PMU_BODINTLVL_0,                            /**< \brief �ȼ�0��2.05V */
    AMHW_PMU_BODINTLVL_2_05V = AMHW_PMU_BODINTLVL_0, /**< \brief �ȼ�0��2.05V */
    AMHW_PMU_BODINTLVL_1,                            /**< \brief �ȼ�1��2.45V */
    AMHW_PMU_BODINTLVL_2_45V = AMHW_PMU_BODINTLVL_1, /**< \brief �ȼ�1��2.45V */
    AMHW_PMU_BODINTLVL_2,                            /**< \brief �ȼ�2��2.75V */
    AMHW_PMU_BODINTLVL_2_75V = AMHW_PMU_BODINTLVL_2, /**< \brief �ȼ�2��2.75V */
    AMHW_PMU_BODINTLVL_3,                            /**< \brief �ȼ�3��3.05V */
    AMHW_PMU_BODINTLVL_3_05V = AMHW_PMU_BODINTLVL_3  /**< \brief �ȼ�3��3.05V */
} amhw_pmu_bod_int_level_t;


/**
 * \brief ���õ������жϺ͵����⸴λ�ĵ�Դ��ѹ�ȼ�
 *
 * \param[in] rstlvl : �����⸴λ��ѹ�ȼ�
 * \param[in] intlvl : �������жϵ�ѹ�ȼ�
 *
 * \return ��
 */
am_static_inline 
void amhw_pmu_bod_level_set (amhw_pmu_bod_rst_level_t rstlvl,
                             amhw_pmu_bod_int_level_t intlvl)
{
    AMHW_PMU->bodctrl = ((uint32_t)rstlvl) | (((uint32_t)intlvl) << 2);
}

/**
 * \brief ʹ�ܵ����⸴λ
 * \return ��
 */
am_static_inline 
void amhw_pmu_bod_rst_enable (void)
{
    AMHW_PMU->bodctrl |= (1 << 4);
}

/**
 * \brief ���ܵ����⸴λ
 * \return ��
 */
am_static_inline 
void amhw_pmu_bod_rst_disable (void)
{
    AMHW_PMU->bodctrl &= ~(1 << 4);
}

/**
 * \brief ʹ�ܵ������ж�
 * \return ��
 */
am_static_inline 
void amhw_pmu_bod_int_enable (void)
{
    AMHW_PMU->bodctrl |= (1 << 5);
}

/**
 * \brief ���ܵ������ж�
 * \return ��
 */
am_static_inline 
void amhw_pmu_bod_int_disable (void)
{
    AMHW_PMU->bodctrl &= ~(1 << 5);
}

/**
 * \brief ���BOD��λ�Ƿ���
 * \retval TRUE  : BOD��λ����
 * \retval FALSE : BOD��λδ����
 */
am_static_inline 
bool_t amhw_pmu_bod_rst_flag_chk (void)
{
    return (bool_t)((AMHW_PMU->bodctrl & (1 << 6)) != 0);
}

/**
 * \brief ���BOD�ж��Ƿ���
 * \retval TRUE  : BOD�жϷ���
 * \retval FALSE : BOD�ж�δ����
 */
am_static_inline 
bool_t amhw_pmu_bod_int_flag_chk (void)
{
    return (bool_t)((AMHW_PMU->bodctrl & (1 << 7)) != 0);
}

/**
 * \name ��ȵ���ģʽ��λԴ
 * @{
 */
 
/** \brief �ⲿ�ܽŸ�λ              */
#define AMHW_PMU_DPDWU_RESET     (1 << 0)  

/** \brief RTC���Ѹ�λ               */
#define AMHW_PMU_DPDWU_RTC       (1 << 1)  

/** \brief �����⸴λ              */
#define AMHW_PMU_DPDWU_BODRESET  (1 << 2)  

/** \brief �������жϻ��Ѹ�λ      */
#define AMHW_PMU_DPDWU_BODINTR   (1 << 3)  

 /** @} */

/**
 * \brief ��ȡ��ȵ���ģʽ�Ļ���Դ
 * \return ��ȵ���ģʽ�Ļ���Դ��AMHW_PMU_DPDWU_*�磺(#AMHW_PMU_DPDWU_RESET) 
 */
am_static_inline 
uint32_t am_pmu_dpd_wusrc_get (void)
{
    return AMHW_PMU->dpdwakesrc;
}

/**
 * \brief �����ȵ���ģʽ����Դ
 * \param[in] mask : AMHW_PMU_DPDWU_*��ֵ����AMHW_PMU_DPDWU_*��Ļ�ֵ
 *                   �磺(#AMHW_PMU_DPDWU_RESET)
 * \return ��
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

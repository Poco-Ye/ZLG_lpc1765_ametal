/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site    http://www.zlg.cn/
* e-mail      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief RIT(�ظ��ж϶�ʱ��:Repetitive Interrupt Timer)�����ӿ�
 *
 * 1. 48λ��ʱ������ʱ��ʱ��Ϊ��ʱ�ӣ�main clock��,��ʱ�������������У�Ҳ�����ڲ�
 *    ���жϵ�ʱ��λ��
 * 2. 48λ�Ƚ�ֵ��
 * 3. 48λ�Ƚ�����ֵ. �����κ�Ķ�ʱ������ֵ�����κ�ıȽ�ֵ���ʱ�����Բ����жϡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_RIT_H
#define __AMHW_RIT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_rit
 * \copydoc amhw_rit.h
 * @{
 */

/**
 * \brief RIT �Ĵ�����ṹ��
 */
typedef struct amhw_rit {
    __IO uint32_t  compval;       /**< \brief ��32λ�Ƚ�ֵ�Ĵ���  */
    __IO uint32_t  mask;          /**< \brief ��32λ����ֵ�Ĵ���  */
    __IO uint32_t  ctrl;          /**< \brief ���ƼĴ���          */
    __IO uint32_t  counter;       /**< \brief ��32λ������        */
    __IO uint32_t  compval_h;     /**< \brief ��16λ�Ƚ�ֵ�Ĵ���  */
    __IO uint32_t  mask_h;        /**< \brief ��16λ����ֵ�Ĵ���  */
    __I  uint32_t  reserved;      /**< \brief ��������Ӧʹ��      */
    __IO uint32_t  counter_h;     /**< \brief ��16λ������        */
} amhw_rit_t;

/**
 * \name ����RIT�Ĵ��������ĺ궨��
 * @{
 */

/** \brief ����ʱ������ֵ�����κ�ıȽ�ֵ���ʱ����λ��Ӳ����λ  */
#define AMHW_RIT_CTRL_INT    ((uint32_t) (1ul << 0))

/**
 * \brief ����ʱ������ֵ�����κ�ıȽ�ֵ���ʱ����ʱ��������ֵ����
 */
#define AMHW_RIT_CTRL_ENCLR  ((uint32_t) (1ul << 1))

/**
 * \brief ʹ�ܶ�ʱ���ĵ���ģʽ, ��������ͣʱ����ʱ��Ҳ����ͣ
 */
#define AMHW_RIT_CTRL_ENBR   ((uint32_t) (1ul << 2))

/** \brief ��ʱ��ʹ�� */
#define AMHW_RIT_CTRL_TEN    ((uint32_t) (1ul << 3))

/** @} */

/**
 * \brief ʹ��RIT��ʱ��
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_rit_enable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_TEN;
}

/**
 * \brief ����RIT��ʱ��
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_rit_disable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl &= ~AMHW_RIT_CTRL_TEN;
}

/**
 * \brief ʹ�ܶ�ʱ���ĵ���ģʽ, ��������ͣʱ����ʱ��Ҳ����ͣ
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_rit_debug_enable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_ENBR;
}

/**
 * \brief ���ܶ�ʱ���ĵ���ģʽ, ��������ͣʱ����ʱ������Ӱ��
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_rit_debug_disable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl &= ~AMHW_RIT_CTRL_ENBR;
}

/**
 * \brief ����ʱ������ֵ�����κ�ıȽ�ֵ���ʱ����ʱ��������ֵ����
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_rit_clear_enable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_ENCLR;
}

/**
 * \brief ����ʱ������ֵ�����κ�ıȽ�ֵ���ʱ����ʱ��������ֵ������
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_rit_clear_disable (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl &= ~AMHW_RIT_CTRL_ENCLR;
}

/**
 * \brief ����жϱ�־λ�Ƿ���λ������ʱ������ֵ�����κ�ıȽ�ֵ���ʱ����λ��Ӳ����λ
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \retval TRUE  : �жϱ�־λ��λ
 * \retval FALSE : �жϱ�־λδ��λ
 */
am_static_inline
bool_t amhw_rit_int_flag_check (amhw_rit_t *p_hw_rit)
{
    return (bool_t)((p_hw_rit->ctrl & (AMHW_RIT_CTRL_INT)) != 0);
}

/**
 * \brief ����жϱ�־
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��
 */
am_static_inline
void amhw_rit_int_flag_clr (amhw_rit_t *p_hw_rit)
{
    p_hw_rit->ctrl |= AMHW_RIT_CTRL_INT;
}

/**
 * \brief ����48λ�Ƚ�ֵ�����ڲ����жϣ�
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \param[in] val      : �Ƚ�ֵ�����ֵΪ0xFFFFFFFFFFFF(48λ���ֵ)
 * \return ��
 */
am_static_inline
void amhw_rit_compval_set (amhw_rit_t *p_hw_rit, uint64_t val)
{
    p_hw_rit->compval   = (uint32_t)(val & 0xFFFFFFFF);
    p_hw_rit->compval_h = (uint32_t)((val >> 32) & 0xFFFF);
}

/**
 * \brief ���ñȽ�����ֵ (48λ)
 *
 * ����ֵΪ1��λ��������Ƚϣ�������ֵΪ1��λ�ȽϽ����Ϊ��
 *
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \param[in] val      : ����ֵ�����ֵΪ0xFFFFFFFFFFFF(48λ���ֵ)
 *
 * \return ��
 */
am_static_inline
void amhw_rit_mask_set (amhw_rit_t *p_hw_rit, uint64_t val)
{
    p_hw_rit->mask   = (uint32_t)(val & 0xFFFFFFFF);
    p_hw_rit->mask_h = (uint32_t)((val >> 32) & 0xFFFF);
}

/**
 * \brief �õ���ǰ��RIT����ֵ
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ����ֵ(��48λ��Ч)
 */
am_static_inline
uint64_t amhw_rit_mask_get (amhw_rit_t *p_hw_rit)
{
    uint64_t mask_value;

    mask_value  = (uint64_t)p_hw_rit->mask;
    mask_value |= (((uint64_t)p_hw_rit->mask_h) << 32);

    return mask_value;
}

/**
 * \brief �õ���ǰ��RIT�Ƚ�ֵ
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��ǰ��RIT�Ƚ�ֵ(��48λ��Ч)
 */
am_static_inline
uint64_t amhw_rit_compval_get (amhw_rit_t *p_hw_rit)
{
    uint64_t compare_value;

    compare_value  = (uint64_t)p_hw_rit->compval;
    compare_value |= (((uint64_t)p_hw_rit->compval_h) << 32);

    return compare_value;
}

/**
 * \brief �õ���ǰ��RIT����ֵ
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \return ��ǰ��RIT����ֵ(��48λ��Ч)
 */
am_static_inline
uint64_t amhw_rit_count_get (amhw_rit_t *p_hw_rit)
{
    uint64_t counter_value;

    counter_value  = (uint64_t)p_hw_rit->counter;
    counter_value |= (((uint64_t)p_hw_rit->counter_h) << 32);

    return counter_value;
}

/**
 * \brief ���õ�ǰ��RIT����ֵ
 * \param[in] p_hw_rit : ָ��RIT�Ĵ������ָ��
 * \param[in] value    : ���õ�RIT����ֵ�����ֵΪ0xFFFFFFFFFFFF(48λ���ֵ)
 * \return ��
 */
void amhw_rit_count_set(amhw_rit_t *p_hw_rit, uint64_t value);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_RIT_H */

/* end of file */

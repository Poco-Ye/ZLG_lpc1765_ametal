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
* e-mail:      apollo.support\zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GPIO ���ж�Ӳ�������ӿ�
 *
 * 1. ��������Ϊ������������ž���Ϊ���жϵĹ���һ���жϣ�
 * 2. ���ж���ÿһ������Դ�����ȼ���������Ϊ�߻�ͣ�
 * 3. �����ж���Ͽɽ����߼���������
 * 4. �����ж�֧�ֶ������ж�ģʽ��
 * 5. ���жϿɽ����������˯��ģʽ�����˯��ģʽ�͵���ģʽ�л��ѡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  asd, first implementation.
 * \endinternal
 */

#ifndef __AMHW_GINT_H
#define __AMHW_GINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_gint
 * \copydoc amhw_gint.h
 * @{
 */
 
/**
 * \brief GPIO ���жϼĴ�����ṹ��
 */
typedef struct amhw_gint {
    __IO uint32_t  ctrl;                /**< \brief GPIO���жϿ��ƼĴ���       */
    __I  uint32_t  reserved0[7];        /**< \brief ����                       */
    __IO uint32_t  port_pol[8];         /**< \brief GPIO���ж϶˿����ȼ��Ĵ��� */
    __IO uint32_t  port_ena[8];         /**< \brief GPIO���ж϶˿�ʹ�ܼĴ���   */
    __I  uint32_t  reserved1[4072];     /**< \brief ����                       */
} amhw_gint_t;


/**
 * \name ���жϱ��
 * \anchor grp_amhw_gint_num
 * @{
 */
 
#define AMHW_GROUP_0                   0            /**< \brief ���ж�0 */
#define AMHW_GROUP_1                   1            /**< \brief ���ж�1 */

/** @} */


/**
 * \name LPC5410x GPIO���ƼĴ���λ����
 * \anchor grp_amhw_gint_ctrl
 * @{
 */
 
#define AMHW_GINT_CTRL_COMB_OR       (0UL << 1)    /**< \brief ���жϻ�ģʽ       */ 
#define AMHW_GINT_CTRL_COMB_AND      (1UL << 1)    /**< \brief ���ж���ģʽ       */
#define AMHW_GINT_CTRL_TRIG_EDGE     (0UL << 2)    /**< \brief ���жϱ��ش���ģʽ */ 
#define AMHW_GINT_CTRL_TRIG_LEVEL    (1UL << 2)    /**< \brief ���жϵ�ƽ����ģʽ */

/** @} */

/**
 * \brief �������жϿ��ƼĴ���
 *
 * \param[in] p_hw_gint : ָ��GPIO���жϼĴ������ָ�롣
 * \param[in] group     : GPIO ���жϺţ�(#AMHW_GROUP_0) �� (#AMHW_GROUP_1) 
 * \param[in] flags     : ���ò������μ�
 *                        \ref grp_amhw_gint_ctrl
 *
 * \return  �ޡ�
 */
am_static_inline
void amhw_gint_ctrl_set (amhw_gint_t *p_hw_gint, uint8_t group, uint32_t flags)
{
    p_hw_gint[group].ctrl = (flags & ~(1UL << 0));
}


/**
 * \brief ���ָ�����жϵ��жϵȴ�״̬
 *
 * \param[in] p_hw_gint : ָ��GPIO���жϼĴ������ָ��
 * \param[in] group     : GPIO ���жϺţ�(#AMHW_GROUP_0) �� (#AMHW_GROUP_1) 
 *
 * \return  �ޡ�
 */
am_static_inline
void amhw_gint_status_clr (amhw_gint_t *p_hw_gint, uint8_t group)
{
    p_hw_gint[group].ctrl |= (1UL << 0);
}

/**
 * \brief ��ȡָ�����жϵĵȴ��ж�״̬
 *
 * \param[in] p_hw_gint : ָ��GPIO���жϼĴ������ָ��
 * \param[in] group     : GPIO ���жϺţ�(#AMHW_GROUP_0) �� (#AMHW_GROUP_1) 
 *
 * \retval TRUE         : ���жϵȴ�
 * \retval FALSE        : ���жϵȴ�
 */
am_static_inline
bool_t amhw_gint_status_get (amhw_gint_t *p_hw_gint, uint8_t group)
{
    return (bool_t)((p_hw_gint[group].ctrl & (1UL << 0)) != 0);
}

/**
 * \brief ѡ��ָ������Ϊָ�����жϵĵ͵�ƽ����
 *
 * \param[in] p_hw_gint : ָ��GPIO���жϼĴ������ָ��
 * \param[in] group     : GPIO ���жϺţ�(#AMHW_GROUP_0) �� (#AMHW_GROUP_1) 
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return  ��
 */
am_static_inline
void amhw_gint_low_level_sel (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_pol[(uint32_t)(pin >> 5)] &= ~(1UL << (pin & 0xF));
}

/**
 * \brief ѡ��ָ������Ϊָ�����жϵĸߵ�ƽ����
 *
 * \param[in] p_hw_gint : ָ��GPIO���жϼĴ������ָ��
 * \param[in] group     : GPIO ���жϺţ�(#AMHW_GROUP_0) �� (#AMHW_GROUP_1) 
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return  ��
 */
am_static_inline
void amhw_gint_high_level_sel (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_pol[(uint32_t)(pin >> 5)] |= (1UL << (pin & 0xF));
}

/**
 * \brief ���ж���ָ�������жϽ���
 *
 * \param[in] p_hw_gint : ָ��GPIO���жϼĴ������ָ��
 * \param[in] group     : GPIO ���жϺţ�(#AMHW_GROUP_0) �� (#AMHW_GROUP_1) 
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return  ��
 *
 * \note   ���ܺ�����Ų���Ϊ���жϹ����ж�
 */
am_static_inline
void amhw_gint_disabled (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_ena[(uint32_t)(pin >> 5)] &= ~(1UL << (pin & 0xF));
}

/**
 * \brief ���ж���ָ�������ж�ʹ��
 *
 * \param[in] p_hw_gint : ָ��GPIO���жϼĴ������ָ��
 * \param[in] group     : GPIO ���жϺţ�(#AMHW_GROUP_0) �� (#AMHW_GROUP_1) 
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return  ��
 *
 * \note    ʹ�ܺ������Ϊ���жϹ����ж�
 */
am_static_inline
void amhw_gint_enabled (amhw_gint_t *p_hw_gint, uint8_t group, int pin)
{
    p_hw_gint[group].port_ena[(uint32_t)(pin >> 5)] |= (1UL << (pin & 0xF));
}

/** @} amhw_if_gint */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_GINT_H */

/* end of file */

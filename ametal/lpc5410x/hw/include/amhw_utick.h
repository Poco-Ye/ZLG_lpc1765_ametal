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
 * \brief UTICK(Micro-tick timer)�����ӿ�
 * 
 * 1. ���ȼ򵥵Ķ�ʱ����
 * 2. дֵ����������
 * 3. �ж�ģʽ�������ѯģʽ��
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_UTICK_H
#define __AMHW_UTICK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_utick
 * \copydoc amhw_utick.h
 * @{
 */
 
/**
 * \brief UTICK(Micro-tick timer)�Ĵ�����ṹ��
 */
typedef struct amhw_utick {
    __IO uint32_t ctrl;        /**< \brief UTICK ���ƼĴ���  */
    __IO uint32_t status;      /**< \brief UTICK ״̬�Ĵ���  */
} amhw_utick_t;
 
/**
 * \name UTICK�Ĵ��������궨��
 * @{
 */

/** \brief  UTICK�ظ���ʱλ                                */
#define AMHW_UTICK_CTRL_REPEAT           ((uint32_t)1UL << 31)

/** \brief  UTICK��ʱֵ����ֵ��31λ�����ֵΪ0x7FFFFFFF    */
#define AMHW_UTICK_CTRL_DELAY_MASK       ((uint32_t)0x7FFFFFFF)

/** \brief  UTICK�ж�״̬λ            */
#define AMHW_UTICK_STATUS_INTR           ((uint32_t)1 << 0)

/** \brief  UTICK����λ                */
#define AMHW_UTICK_STATUS_ACTIVE         ((uint32_t)1 << 1)

/** \brief  UTICK״̬�Ĵ�������ֵ      */
#define AMHW_UTICK_STATUS_MASK           ((uint32_t)0x03)

/** @} */

/**
 * \brief ����UTICK�Ķ�ʱtick��
 *
 * ��ʱֵ������(tick_value + 1)��ʱ�����ڣ���С��tick_valueֵΪ1����ʱ����ʱ��
 * ���ڣ�tick_valueΪ0��ֹͣ��ʱ����
 *
 * \param[in] p_hw_utick : ָ��UTICK�Ĵ������ָ��
 * \param[in] tick_value : Tick ֵ,���ֵΪ0x7FFFFFFF��
 * \param[in] repeat     : TRUE���ظ���ʱ��ticks����0���Զ���װ��ֵ
 *                         FALSE��һ�ζ�ʱ��ticks����0���Զ�ֹͣ��ʱ
 * \return ��
 */
void amhw_utick_tick_set(amhw_utick_t *p_hw_utick, 
                         uint32_t      tick_value, 
                         bool_t        repeat);

/**
 * \brief ��ȡ UTICK ��ǰTickֵ
 * \param[in] p_hw_utick : ָ��UTICK�Ĵ������ָ��
 * \return UTICK ��ǰTickֵ
 */
am_static_inline 
uint32_t amhw_utick_tick_get (amhw_utick_t *p_hw_utick)
{
    return (p_hw_utick->ctrl & AMHW_UTICK_CTRL_DELAY_MASK);
}

/**
 * \brief ����UTICK��ʱ��
 * \param[in] p_hw_utick : ָ��UTICK�Ĵ������ָ��
 * \return ��
 */

am_static_inline 
void amhw_utick_disable (amhw_utick_t *p_hw_utick)
{
    p_hw_utick->ctrl = 0;
}

/**
 * \brief ���UTICK�жϱ�־�Ƿ�����
 * \param[in] p_hw_utick : ָ��UTICK�Ĵ������ָ��
 * \retval TRUE  : �жϱ�־����
 * \retval FALSE : �жϱ�־δ����
 */
am_static_inline 
bool_t amhw_utick_int_flag_check (amhw_utick_t *p_hw_utick)
{
    return (bool_t)((p_hw_utick->status & AMHW_UTICK_STATUS_INTR) != 0);
}

/**
 * \brief ���UTICK�жϱ�־
 * \param[in] p_hw_utick : ָ��UTICK�Ĵ������ָ��
 * \return ��
 */
am_static_inline 
void amhw_utick_int_flag_clr (amhw_utick_t *p_hw_utick)
{
    p_hw_utick->status = AMHW_UTICK_STATUS_INTR;
}
 

/**
 * \brief ���UTICK ��ʱ���Ƿ񼤻ͨ����⼤���־��
 * \param[in] p_hw_utick : ָ��UTICK�Ĵ������ָ��
 * \retval TRUE  : ��ʱ���Ѽ���
 * \retval FALSE : ��ʱ��δ����
 */
am_static_inline 
bool_t amhw_utick_active_flag_check (amhw_utick_t *p_hw_utick)
{
    return (bool_t)((p_hw_utick->status & AMHW_UTICK_STATUS_ACTIVE) != 0);
}
 
/**
 * @} amhw_if_utick
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_UTICK_H */

/* end of file */

/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ��Ϣ�ʼ�Ӳ�������ӿ�
 *
 * 1. �ṩ��һ���ں�ͨ�ŷ���, �������ں˹�����Դ������ͨ��һ���򵥵ķ�ʽ����ͨ�ţ�
 * 2. ÿ���ں��ṩ�ߴ�32����ͨ���û������жϣ���������һ���ںˣ�
 * 3. ����ں���Ч����ʵ�ֹ�������Ļ�����ʡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-08  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_MBOX_H
#define __AMHW_MBOX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_mbox
 * \copydoc amhw_mbox.h
 * @{
 */

#define AMHW_MBOX_CORE_NUM   2          /**< \brief �ں˵���Ŀ */

/**
 * \brief CPU ID����
 * @{
 */

#define AMHW_MBOX_M0PLUS_ID  0          /**< \brief M0+�ں˵�ID�� 0  */
#define AMHW_MBOX_M4_ID      1          /**< \brief M4 �ں˵�ID�� 1  */
/** @} */
/**
 * \brief ��Ϣ�����IRQ��ؽṹ��
 */
typedef struct amhw_mbox_irq {
    __IO uint32_t  irq;        /**< \brief ��Ϣ��������         */
    __O  uint32_t  irq_set;    /**< \brief ��λ��Ϣ��������     */
    __O  uint32_t  irq_clr;    /**< \brief �����λ��Ϣ�������� */
    __I  uint32_t  reserved;   /**< \brief ���� */
} amhw_mbox_irq_t;

/**
 * \brief ��Ϣ����Ĵ�����ṹ��
 */
typedef struct amhw_mailbox {

    /** \brief ��Ϣ����,  0 - M0+, 1 - M4 */
    amhw_mbox_irq_t  mbox[AMHW_MBOX_CORE_NUM];

    /** \brief ���� */
    amhw_mbox_irq_t  reserved1[15 - AMHW_MBOX_CORE_NUM];
    __I  uint32_t    reserved2[2];   /**< \brief ����         */
    __IO uint32_t    mutex;          /**< \brief ��������� */
} amhw_mailbox_t;

/**
 * \brief �趨��ֵ����Ϣ����
 *
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 * \param[in] cpu_id    : �ں�ID
 * \param[in] value     : �趨��ֵ
 *
 * \return    ��
 */
am_static_inline
void amhw_mbox_val_set (amhw_mailbox_t *p_hw_mbox, uint32_t cpu_id, uint32_t value)
{
    p_hw_mbox->mbox[cpu_id].irq = value;
}

/**
 * \brief ��λ��Ϣ��������λΪ1 
 *
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 * \param[in] cpu_id    : �ں�ID
 * \param[in] bits_set  : ��Ҫ��1������λ����Ӧ������λ��1��λ������Ч����֮����Ч
 *                        
 * \return    ��
 *
 * \note  ��λ������λ��ͨ����Ϣ���䷢�͵���һ���ں�
 */
am_static_inline
void amhw_mbox_val_bits_set (amhw_mailbox_t *p_hw_mbox,
                             uint32_t        cpu_id,
                             uint32_t        bits_set)
{
    p_hw_mbox->mbox[cpu_id].irq_set = bits_set;
}

/**
 * \brief �����λ����Ϣ��������λ
 *
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 * \param[in] cpu_id    : �ں�ID
 * \param[in] bits_clr  : ��Ҫ���������λ
 *                        
 * \return    ��
 *
 * \note  ���������λ��ͨ����Ϣ���䷢�͵���һ���ں�
 */
am_static_inline
void amhw_mbox_val_bits_clr (amhw_mailbox_t *p_hw_mbox,
                             uint32_t        cpu_id,
                             uint32_t        bits_clr)
{
    p_hw_mbox->mbox[cpu_id].irq_clr = bits_clr;
}

/**
 * \brief ��ȡ��Ϣ���������
 *
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 * \param[in] cpu_id    : �ں�ID
 *
 * \return ��Ϣ��������� 
 */
am_static_inline
uint32_t amhw_mbox_val_get (amhw_mailbox_t *p_hw_mbox, uint32_t cpu_id)
{
    return p_hw_mbox->mbox[cpu_id].irq;
}

/**
 * \brief ��ȡMUTEX��״̬
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 *
 * \retval  1 ��ȡMUTEX
 * \retval  0 ����
 */
am_static_inline
uint32_t amhw_mbox_mutex_get (amhw_mailbox_t *p_hw_mbox)
{
    return p_hw_mbox->mutex;
}

/**
 * \brief ��λMUTEX ״̬
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 * \return    ��
 *
 * \note   ����λMUTEX ״̬������������Դ��ȡmutex
 */
am_static_inline
void amhw_mbox_mutex_set (amhw_mailbox_t *p_hw_mbox)
{
    p_hw_mbox->mutex = 1;
}

/**
 * \brief ����Mutex����,�ȴ���ȡ��Mutex.
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 * \return  ��
 *
 * \note  amhw_mbox_mutex_take() �� amhw_mbox_mutex_give() ����ɶԳ���
 */
void amhw_mbox_mutex_take(amhw_mailbox_t *p_hw_mbox);

/**
 * \brief �˳�Mutex����,��λMUTEX״̬������������Դ��ȡmutex
 * \param[in] p_hw_mbox : ָ����Ϣ����Ĵ������ָ��
 * \return    ��
 *
 * \note  amhw_mbox_mutex_take() �� amhw_mbox_mutex_give() ����ɶԳ���
 */
void amhw_mbox_mutex_give(amhw_mailbox_t *p_hw_mbox);

/**
 * @} amhw_if_mbox
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MBOX_H */

/* end of file */

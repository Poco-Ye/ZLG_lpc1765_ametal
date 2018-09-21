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
 * \brief NVIC��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  hbt, first implementation.
 * \endinternal
 */

#ifndef __AM_INT_H
#define __AM_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup am_if_int
 * \copydoc am_int.h
 * @{
 */

/**
 * \brief �ж�����
 * 
 * \param[in] inum    : �жϺ�
 * \param[in] pfn_isr : �жϻص�����ָ��
 * \param[in] p_arg   : �ص���������ڲ���
 * 
 * \retval  AM_OK     : ���ӳɹ�
 * \retval -AM_EINVAL : ��Ч����
 * \retval -AM_EPERM  : ����ʧ��
 */
int am_int_connect(int inum, am_pfnvoid_t pfn_isr, void *p_arg);

/**
 * \brief ɾ���ж�����
 * 
 * \param[in] inum    : �жϺ�
 * \param[in] pfn_isr : �жϻص�����ָ��
 * \param[in] p_arg   : �ص���������ڲ���
 * 
 * \retval  AM_OK     : ɾ�����ӳɹ�
 * \retval -AM_EINVAL : ��Ч����
 * \retval -AM_EPERM  : ����ʧ��
 */
int am_int_disconnect(int inum, am_pfnvoid_t pfn_isr, void *p_arg);

/**
 * \brief ʹ���ж�
 * \param[in] inum  : �жϺ�
 * \retval    AM_OK : �����ɹ�
 */
int am_int_enable(int inum);

/**
 * \brief �����ж�
 * \param[in] inum  : �жϺ�
 * \retval    AM_OK : �����ɹ�
 */
int am_int_disable(int inum);

/**
 * \brief �رձ���CPU�ж�
 *
 * \attention
 * - �رձ���CPU�жϵ�ʱ��һ��Ҫ��
 * - ������ am_int_cpu_unlock() ��������ʹ��
 *
 * \return �жϹر���Ϣ
 *
 * \par ʾ����
 * \code
 * uint32_t key;
 * 
 * key = am_int_cpu_lock();
 * // do something.
 * am_int_cpu_unlock(key);
 * \endcode
 *
 * \par Ƕ��ʹ��ʾ����
 * \code 
 * uint32_t key0, key1;
 *
 * key0 = am_int_cpu_lock();  // �ж����Ϲر�
 * key1 = am_int_cpu_lock();  // �жϱ��ֹر�
 * 
 * am_int_cpu_unlock(key1);   // �жϱ��ֹر�
 * am_int_cpu_unlock(key0);   // �ж����ϴ�
 * \endcode
 */
uint32_t am_int_cpu_lock(void);

/**
 * \brief �򿪱���CPU�ж�
 *
 * \attention
 *  ������ am_int_cpu_lock() ��������ʹ��
 *
 * \param[in] key : �жϹر���Ϣ
 * \return    ��
 */
void am_int_cpu_unlock(uint32_t key);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_INT_H */

/* end of file */

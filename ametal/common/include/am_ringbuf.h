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
 * \brief ���λ�������׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-03  jon, first implementation.
 * \endinternal
 */
#ifndef __AM_RINGBUF_H
#define __AM_RINGBUF_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
    
/**
 * \addtogroup am_if_ringbuf
 * \copydoc am_ringbuf.h
 * @{
 */
 
/**
 * \brief ���λ�������Ϣ�ṹ��
 */
typedef struct am_ringbuf {
    void    *p_data_buf;          /**< \brief ָ�����ݻ����ָ�� */
    uint32_t count;               /**< \brief ���λ������Ĵ�С     */
    uint32_t item_sz;             /**< \brief �������͵ĳ��� */
    uint32_t head;                /**< \brief ���λ�������ͷ */
    uint32_t tail;                /**< \brief ���λ�������β */
} am_ringbuf_t;

/** \brief ��ȡ���λ�������ͷ */
#define AM_RB_VHEAD(rb)    (*(volatile uint32_t *) &(rb)->head) 

/** \brief ��ȡ���λ�������ͷ */
#define AM_RB_VTAIL(rb)    (*(volatile uint32_t *) &(rb)->tail) 

#ifndef AM_MIN

/** \brief ��ȡ��������Сֵ */
#define AM_MIN(a, b)       (((a) < (b)) ? (a) : (b))
#endif

/**
 * \brief ��ʼ�����λ�����
 *
 * \param[in] p_rb       : ָ���λ�������ָ��
 * \param[in] p_data_buf : ָ���λ�������ݻ���ָ��
 * \param[in] item_size  : ���λ��������ݵ�Ԫ�ĳ���
 * \param[in] count      : ���λ������Ĵ�С
 *
 * \retval  AM_OK        : ��ʼ�����
 * \retval -AM_EINVAL    : ��ʼ��ʧ�ܣ�������Ч
 */
int am_ringbuf_init(am_ringbuf_t *p_rb, 
                    void         *p_data_buf, 
                    uint32_t      item_size, 
                    uint32_t      count);

/**
 * \brief ��ջ��ѻ�����
 * \param[in] p_rb : ָ���λ�������ָ��
 * \return  ��
 */
am_static_inline
void am_ringbuf_flush (am_ringbuf_t *p_rb)
{
    p_rb->head = p_rb->tail = 0;
}

/**
 * \brief ��ȡ���λ����������ݻ��泤��
 * \param[in] p_rb : ָ���λ����ָ��
 * \retval    ���λ������Ĵ�С���ֽ�����
 */
am_static_inline 
uint32_t am_ringbuf_size_get (am_ringbuf_t *p_rb)
{
    return (p_rb->count);
}

/**
 * \brief ��ȡ���λ������ĳ���
 * \param[in] p_rb : ָ���λ����ָ��
 * \retval    ���λ���������Ŀ���Զ������������λ��Ԫ��
 */
am_static_inline 
uint32_t am_ringbuf_size_used_get (am_ringbuf_t *p_rb)
{
    return AM_RB_VHEAD(p_rb) - AM_RB_VTAIL(p_rb);
}

/**
 * \brief ��ȡ���λ�����ʣ�����Ŀ
 * \param[in] p_rb : ָ���λ�������ָ��
 * \retval    ���λ�����ʣ��ĵ�Ԫ��Ŀ
 */
am_static_inline 
uint32_t am_ringbuf_size_free_get (am_ringbuf_t *p_rb)
{
    return p_rb->count - am_ringbuf_size_used_get(p_rb);
}

/**
 * \brief ��⻷�λ������Ƿ�Ϊ��
 *
 * \param[in] p_rb : ָ���λ�������ָ��
 *
 * \retval TRUE    : ���λ�����Ϊ��
 * \retval FALSE   : ���λ���������
 */
am_static_inline 
bool_t am_ringbuf_isfull (am_ringbuf_t *p_rb)
{
    return (bool_t)(am_ringbuf_size_used_get(p_rb) >= p_rb->count);
}

/**
 * \brief ��⻽�ѻ������Ƿ�Ϊ��
 *
 * \param[in] p_rb : ָ���λ�������ָ��
 * 
 * \retval TRUE    : ���λ�����Ϊ��
 * \retval FALSE   : ���λ������ǿ�
 */
am_static_inline 
bool_t am_ringbuf_isempty (am_ringbuf_t *p_rb)
{
    return (bool_t)(AM_RB_VHEAD(p_rb) == AM_RB_VTAIL(p_rb));
}

/**
 * \brief �ڻ��λ������в���һ����Ԫ����
 *
 * \param[in] p_rb   : ָ���λ�������ָ��
 * \param[in] p_data : ָ��Ҫ���������
 *
 * \retval  1 : �������ݳɹ�
 * \retval  0 : ���λ�����Ϊ�������벻�ɹ�
 */
uint32_t am_ringbuf_insert(am_ringbuf_t *p_rb, const void *p_data);

/**
 * \brief �ڻ��λ������в���һ������
 *
 * \param[in] p_rb    : ָ���λ�������ָ��
 * \param[in] p_buf   : ָ��Ҫ���������
 * \param[in] length  : �������ݵĳ���
 *
 * \return  �ɹ��������Ŀ
 */
uint32_t am_ringbuf_insert_mult(am_ringbuf_t *p_rb, 
                                const void   *p_buf, 
                                uint32_t      length);

/**
 * \brief �ӻ��λ��������Ƴ�һ��Ԫ����
 *
 * \param[in] p_rb   : ָ���λ�������ָ��
 * \param[in] p_data : ָ��Ҫ�Ƴ������ݵ�Ԫ
 *
 * \retval  1 : �Ƴ����ݳɹ�
 * \retval  0 : ���λ�����Ϊ�գ�����ʧ��
 */
uint32_t am_ringbuf_pop(am_ringbuf_t *p_rb, void *p_data);

/**
 * \brief �ӻ��λ��������Ƴ�һ������
 *
 * \param[in] p_rb   : ָ���λ�������ָ��
 * \param[in] p_buf  : ָ��Ҫ�Ƴ������ݻ���
 * \param[in] length : ���λ�����Ҫ�Ƴ������ݳ���
 *
 * \return   �ɹ��Ƴ���������Ŀ
 */
uint32_t am_ringbuf_pop_mult(am_ringbuf_t *p_rb, 
                             void         *p_buf, 
                             uint32_t      length);


/**
 * @} 
 */

#ifdef __cplusplus
}
#endif
 
#endif /* __AM_RINGBUF_H */

/* end of file */

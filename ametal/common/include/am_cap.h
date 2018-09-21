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
 * \brief ���벶���׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-09  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_CAP_H
#define __AM_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup am_if_cap
 * \copydoc am_cap.h
 * @{
 */

/** \brief �����ش������� */
#define AM_CAP_TRIGGER_RISE          0x01
    
/** \brief �½��ش������� */
#define AM_CAP_TRIGGER_FALL          0x02

/** \brief ˫���ش������� */
#define AM_CAP_TRIGGER_BOTH_EDGES    0x04

/** \brief �����¼��Ļص��������� */
typedef void (*am_cap_callback_t) (void *p_arg, unsigned int count); 
    
/**
 * \brief ���벶�����������ṹ��
 */
struct am_cap_drv_funcs {

    /** \brief ����һ������ͨ��               */
    int (*pfn_cap_config) (void             *p_cookie,
                           int               chan,
                           unsigned int      options,
                           am_cap_callback_t pfn_callback,
                           void             *p_arg);

    /** \brief ʹ�ܲ���ͨ��                   */
    int (*pfn_cap_enable) (void *p_cookie, int chan);

    /** \brief ���ܲ���ͨ��                   */
    int (*pfn_cap_disable) (void *p_cookie, int chan);
                             
    /** \brief ��λһ������ͨ����ʹ����ֵ����         */
    int (*pfn_cap_reset) (void *p_cookie,int chan);
    
    /** \brief ת�����β���ֵΪʱ��ֵ��ʱ�䵥λ��ns�� */
    int (*pfn_cap_count_to_time)(void         *p_cookie,
                                 int           chan,
                                 unsigned int  count1,
                                 unsigned int  count2,
                                 unsigned int *p_time_ns);
};


/** 
 * \brief ���벶�����
 */
typedef struct am_cap_serv {

    /** \brief ���벶�����������ṹ��ָ��    */
    struct am_cap_drv_funcs   *p_funcs;   
    
    /** \brief �������������ĵ�һ������      */
    void                      *p_drv;    
} am_cap_serv_t;

/** \brief ���벶���׼�������������Ͷ���  */
typedef am_cap_serv_t *am_cap_handle_t;


/** 
 * \brief ����һ�����벶��ͨ��
 * 
 * \param[in] handle       : ���벶���׼����������
 * \param[in] chan         : ���벶��ͨ��
 * \param[in] options      : AM_CAP_TRIGGER_*��ֵ (�磺#AM_CAP_TRIGGER_RISE)
 * \param[in] pfn_callback : �ص�����
 * \param[in] p_arg        : �ص��������û�����
 *
 * \retval  AM_OK       : ����CAPͨ���ɹ�
 * \retval -AM_EINVAL   : ����ʧ�ܣ���������
 */
am_static_inline
int am_cap_config (am_cap_handle_t   handle,
                   int               chan,
                   unsigned int      options,
                   am_cap_callback_t pfn_callback,
                   void             *p_arg)
{
    return handle->p_funcs->pfn_cap_config(handle->p_drv,
                                           chan,
                                           options,
                                           pfn_callback,
                                           p_arg);
                      
}

/** 
 * \brief ʹ�ܲ���ͨ��
 * 
 * \param[in] handle  : ���벶���׼����������
 * \param[in] chan    : ���벶��ͨ��
 *
 * \retval  AM_OK     : ʹ�ܲ���ͨ���ɹ�
 * \retval -AM_EINVAL : ʹ�ܲ���ͨ��ʧ�ܣ���������
 */
am_static_inline
int am_cap_enable (am_cap_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_cap_enable(handle->p_drv, chan);
}

/** 
 * \brief ���ܲ���ͨ��
 * 
 * \param[in] handle  : ���벶���׼����������
 * \param[in] chan    : ���벶��ͨ��
 *
 * \retval  AM_OK     : ���ܲ���ͨ���ɹ�
 * \retval -AM_EINVAL : ���ܲ���ͨ��ʧ�ܣ���������
 */
am_static_inline
int am_cap_disable(am_cap_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_cap_disable(handle->p_drv, chan);
}


/** 
 * \brief ��λ����ͨ������ֵΪ0
 *
 * \param[in] handle  : ���벶���׼����������
 * \param[in] chan    : ���벶��ͨ��
 *
 * \retval  AM_OK     : ��λ�ɹ�
 * \retval -AM_EINVAL : ��λʧ��, ��������
 */
am_static_inline
int am_cap_reset(am_cap_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_cap_reset(handle->p_drv, chan);
}

/** 
 * \brief ת�����β���ֵΪʱ��ֵ��ʱ�䵥λ��ns��
 *
 * \param[in]  handle    : ���벶���׼����������
 * \param[in]  chan      : ���벶��ͨ��
 * \param[in]  count1    : ��һ�β���ֵ
 * \param[in]  count2    : �ڶ��β���ֵ
 * \param[out] p_time_ns : ���ڻ�ȡת�����ʱ��ֵ
 *
 * \retval  AM_OK        : ת���ɹ�
 * \retval -AM_EINVAL    : ת��ʧ�ܣ���������
 */
am_static_inline
int am_cap_count_to_time(am_cap_handle_t handle,
                         int             chan,
                         unsigned int    count1,
                         unsigned int    count2,
                         unsigned int   *p_time_ns)
{
    return handle->p_funcs->pfn_cap_count_to_time(handle->p_drv, 
                                                  chan,
                                                  count1,
                                                  count2,
                                                  p_time_ns);
}

/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_CAP_H */

/* end of file */

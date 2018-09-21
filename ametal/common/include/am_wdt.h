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
 * \brief  WDT��׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-07  fft, first implementation.
 * \endinternal
 */

#ifndef __AM_WDT_H
#define __AM_WDT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
    
/** 
 * \addtogroup am_if_wdt
 * \copydoc am_wdt.h
 * @{
 */

/** 
 * \brief WDT��ʱ��Ϣ
 */
typedef struct am_wdt_info {
    uint32_t   min_timeout_ms;  /**< \brief ֧�ֵ����ʱʱ�䣬��λ��ms */
    uint32_t   max_timeout_ms;  /**< \brief ֧�ֵ���С��ʱʱ�䣬��λ��ms */
} am_wdt_info_t;

/** 
 * \brief WDT��������
 */
struct am_wdt_drv_funcs {
    
    /** \brief ��ȡWDT��Ϣ */
    int (*pfn_wdt_info_get)(void *p_drv, am_wdt_info_t *p_info);

    /** \brief ���ó�ʱʱ�䲢ʹ��WDT */
    int (*pfn_wdt_enable)(void *p_drv, uint32_t timeout_ms);
    
    /** \brief ���Ź�ι�� */
    int (*pfn_wdt_feed)(void *p_drv);
};

/** 
 * \brief WDT��׼����
 */
typedef struct am_wdt_serv {

    /** \brief WDT�������� */
    struct am_wdt_drv_funcs  *p_funcs; 
    
    /** \brief ����������һ����ڲ��� */
    void                     *p_drv; 
} am_wdt_serv_t;

/** \brief WDT��׼�������������� */
typedef am_wdt_serv_t *am_wdt_handle_t;


/**
 * \brief ��ȡWDT��Ϣ
 *
 * \param[in] handle  : WDT��׼����������
 * \param[out] p_info : ָ��WDT��Ϣ��ָ��
 *
 * \retval AM_OK      : �����ɹ�
 * \retval -AM_EINVAL : ��Ч����
 */
am_static_inline
int am_wdt_info_get (am_wdt_handle_t handle, am_wdt_info_t *p_info)
{
    return handle->p_funcs->pfn_wdt_info_get(handle->p_drv,p_info);
}

/**
 * \brief ���ó�ʱʱ�䲢ʹ��WDT
 *
 * \param[in] handle     : WDT��׼����������
 * \param[in] timeout_ms : ��ʱʱ��ֵ����λ��ms
 *
 * \retval  AM_OK        : ���ó�ʱʱ��ɹ�
 * \retval -AM_EINVAL    : ������Ч������趨��ʱʱ���Ƿ�������Χ��
 *
 * \note ����趨�ĳ�ʱʱ��ֵ��Ϊ0��WDT��ʹ��
 */
am_static_inline
int am_wdt_enable (am_wdt_handle_t handle, uint32_t timeout_ms)
{
    return handle->p_funcs->pfn_wdt_enable(handle->p_drv,timeout_ms);
}

/**
 * \brief ���Ź�ι��
 * \param[in] handle : WDT��׼����������
 * \retval  AM_OK    : �����ɹ�
 */
am_static_inline
int am_wdt_feed (am_wdt_handle_t handle)
{
    return handle->p_funcs->pfn_wdt_feed(handle->p_drv);
}

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_WDT_H */

/* end of file */

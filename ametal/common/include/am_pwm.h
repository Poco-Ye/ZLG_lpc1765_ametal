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
 * \brief PWM��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_PWM_H
#define __AM_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_pwm
 * \copydoc am_pwm.h
 * @{
 */

/**
 * \brief PWM���������ṹ��
 */
struct am_pwm_drv_funcs {

    /** \brief ����һ��PWMͨ��  */
    int (*pfn_pwm_config) (void          *p_drv,
                           int            chan,
                           unsigned long  duty_ns,
                           unsigned long  period_ns);
    
    /** \brief ʹ��PWM���     */
    int (*pfn_pwm_enable) (void *p_drv, int chan);
    
    /** \brief ����PWM���     */
    int (*pfn_pwm_disable) (void *p_drv,int chan);
};

/** 
 * \brief PWM����
 */
typedef struct am_pwm_serv {

    /** \brief PWM���������ṹ��ָ��   */
    struct am_pwm_drv_funcs   *p_funcs;
    
    /** \brief �������������ĵ�һ������ */
    void                      *p_drv; 
} am_pwm_serv_t;

/** \brief PWM��׼�������������Ͷ��� */
typedef am_pwm_serv_t *am_pwm_handle_t;

/** 
 * \brief ����һ��PWMͨ��
 * 
 * \param[in] handle    : PWM��׼����������
 * \param[in] chan      : PWMͨ��
 * \param[in] duty_ns   : PWM����ʱ�䣨��λ�����룩
 * \param[in] period_ns : PWM����ʱ�䣨��λ�����룩
 *
 * \retval  AM_OK       : ����PWMͨ���ɹ�
 * \retval -AM_EINVAL   : ����ʧ��, ��������
 */
am_static_inline
int am_pwm_config (am_pwm_handle_t handle, 
                   int             chan,
                   unsigned long   duty_ns,
                   unsigned long   period_ns)
{
    return handle->p_funcs->pfn_pwm_config(handle->p_drv,
                                           chan,
                                           duty_ns,
                                           period_ns);
}

/** 
 * \brief ʹ��PWM���
 * 
 * \param[in] handle  : PWM��׼����������
 * \param[in] chan    : PWMͨ��
 *
 * \retval  AM_OK     : ʹ��PWM����ɹ�
 * \retval -AM_EINVAL : ʧ��, ��������
 */
am_static_inline
int am_pwm_enable (am_pwm_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_pwm_enable(handle->p_drv, chan);
}

/** 
 * \brief ����PWM���
 * 
 * \param[in] handle  : PWM��׼����������
 * \param[in] chan    : PWMͨ��
 *
 * \retval  AM_OK     : ����PWM����ɹ�
 * \retval -AM_EINVAL : ʧ��, ��������
 */
am_static_inline
int am_pwm_disable (am_pwm_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_pwm_disable(handle->p_drv, chan);
}

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_PWM_H */

/* end of file */

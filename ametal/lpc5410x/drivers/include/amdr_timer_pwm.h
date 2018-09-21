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
 * \brief ��ʱ����STD Timer������������PWM��׼�ӿ�
 *
 * 1. ��ʱ��֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���PWM��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. �ڱ������У��ĸ�ƥ��Ĵ���ʹ�����£�
 *        - ƥ��Ĵ���3���ڲ���PWM������ 
 *        - ƥ��Ĵ���0���ڲ���PWM���ͨ��0������ 
 *        - ƥ��Ĵ���1���ڲ���PWM���ͨ��1������ 
 *        - ƥ��Ĵ���2���ڲ���PWM���ͨ��2������ 
 *
 * \note һ����ʱ�����������PWM��������ֵ��Ҳ����˵���ö�ʱ�����������PWM����
 *       ��ͬ��Ƶ����ͬ
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_TIMER_PWM_H
#define __AMDR_TIMER_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "amhw_timer.h"

/**
 * \addtogroup amdr_if_timer_pwm
 * \copydoc amdr_timer_pwm.h
 * @{
 */

/**
 * \brief ��ʱ��PWM������ص�GPIO��Ϣ
 */
typedef struct amdr_timer_pwm_ioinfo {
    uint32_t gpio;                          /**< \brief ��Ӧ��GPIO�ܽ�                      */
    uint32_t func;                          /**< \brief ΪPWM����ʱ��GPIO��������           */
    uint32_t dfunc;                         /**< \brief ���ܹܽ�PWM����ʱ��Ĭ��GPIO�������� */
} amdr_timer_pwm_ioinfo_t;

/**
 * \brief ��ʱ��PWM������ص��豸��Ϣ
 */
typedef struct amdr_timer_pwm_devinfo {
    amhw_timer_t            *p_hw_timer;    /**< \brief ָ��Standard Timer�Ĵ������ָ�� */
    uint8_t                  channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ4            */
    amdr_timer_pwm_ioinfo_t *p_ioinfo;      /**< \brief ָ��PWM�ܽ���Ϣ�ṹ��            */
} amdr_timer_pwm_devinfo_t;
 
/**
 * \brief ��ʱ��PWM�����豸�ṹ��
 */
typedef struct amdr_timer_pwm_dev {
    
    /** \brief ��׼PWM����                         */
    am_pwm_serv_t                    pwm_serv; 
    
    /** \brief ָ��ʱ��PWM�����豸��Ϣ������ָ�� */
    const amdr_timer_pwm_devinfo_t  *p_devinfo; 

} amdr_timer_pwm_dev_t;

/**
 * \brief ��ʼ����ʱ��ΪPWM�������
 *
 * \param[in] p_dev     : ָ��ʱ��PWM��������豸��ָ��
 * \param[in] p_devinfo : ָ��ʱ��PWM��������豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t amdr_timer_pwm_init(amdr_timer_pwm_dev_t           *p_dev,
                                    const amdr_timer_pwm_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ�ö�ʱ����PWM�������ʱ�����ʼ����ʱ����PWM������ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��ʱ��PWM��������豸��ָ��
 * \return ��
 */
void amdr_timer_pwm_deinit(amdr_timer_pwm_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_TIMER_PWM_H */

/* end of file */

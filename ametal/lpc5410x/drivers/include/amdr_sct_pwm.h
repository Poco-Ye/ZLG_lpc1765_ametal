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
 * \brief SCT����������PWM��׼�ӿ�
 *
 * 1. SCT֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���PWM��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. �ڱ������У�SCT�����Դʹ�����£�
 *    - ƥ��Ĵ���0���ڲ���PWM���ڣ����¼�0�����
 *    - ƥ��Ĵ���1���ڲ���PWM���ͨ��0(SCT_OUT0)������ 
 *    - ƥ��Ĵ���2���ڲ���PWM���ͨ��1(SCT_OUT1)������ 
 *    - ƥ��Ĵ���3���ڲ���PWM���ͨ��2(SCT_OUT2)������ 
 *    - ƥ��Ĵ���4���ڲ���PWM���ͨ��3(SCT_OUT3)������ 
 *    - ƥ��Ĵ���5���ڲ���PWM���ͨ��4(SCT_OUT4)������ 
 *    - ƥ��Ĵ���6���ڲ���PWM���ͨ��5(SCT_OUT5)������ 
 *    - ƥ��Ĵ���7���ڲ���PWM���ͨ��6(SCT_OUT6)������ 
 *    - ƥ��Ĵ���8���ڲ���PWM���ͨ��7(SCT_OUT7)������ 
 *
 * \note һ��SCT���������PWM��������ֵ��Ҳ����˵����SCT���������PWM������ͬ��
 *       Ƶ����ͬ
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */


#ifndef __AMDR_SCT_PWM_H
#define __AMDR_SCT_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_pwm.h"
#include "amhw_sct.h"

/**
 * \addtogroup amdr_if_sct_pwm
 * \copydoc amdr_sct_pwm.h
 * @{
 */

/**
 * \brief SCT PWM���������ص�GPIO��Ϣ
 */
typedef struct amdr_sct_pwm_ioinfo {
    uint32_t gpio;              /**< \brief PWM ���õ�GPIO                    */
    uint32_t func;              /**< \brief PWM���ܵ�GPIO��������ֵ           */
    uint32_t dfunc;             /**< \brief ����PWMģʽ��Ĭ��GPIO��������ֵ */
} amdr_sct_pwm_ioinfo_t;

/**
 * \brief SCT PWM���������ص��豸��Ϣ
 */
typedef struct amdr_sct_pwm_devinfo {
    amhw_sct_t            *p_hw_sct;     /**< \brief ָ��SCT�Ĵ������ָ��    */
    uint8_t                channels_num; /**< \brief ʹ�õ�ͨ���������Ϊ8    */
    amdr_sct_pwm_ioinfo_t *p_ioinfo;     /**< \brief ָ��PWM����ܽ���Ϣ�ṹ��*/
} amdr_sct_pwm_devinfo_t;
 
/**
 * \brief SCT PWM��������豸�ṹ��
 */
typedef struct amdr_sct_pwm_dev {
    
    am_pwm_serv_t                 pwm_serv; /**< \brief ��׼PWM����           */
    
    /** \brief ָ��SCT(PWM�������)�豸��Ϣ������ָ�� */
    const amdr_sct_pwm_devinfo_t  *p_devinfo; 

} amdr_sct_pwm_dev_t;

/**
 * \brief ��ʼ��SCTΪPWM�������
 *
 * \param[in] p_dev     : ָ��SCT(PWM�������)�豸��ָ��
 * \param[in] p_devinfo : ָ��SCT(PWM�������)�豸��Ϣ������ָ��
 *
 * \return PWM��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_pwm_handle_t amdr_sct_pwm_init(amdr_sct_pwm_dev_t           *p_dev,
                                  const amdr_sct_pwm_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��SCT PWM�������ʱ�����ʼ��SCT PWM������ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��SCT(PWM�������)�豸��ָ��
 * \return ��
 */
void amhw_sct_pwm_deinit(amdr_sct_pwm_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SCT_PWM_H */

/* end of file */

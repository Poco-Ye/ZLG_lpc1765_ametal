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
 * \brief ��ʱ����STD Timer������������CAP��׼�ӿ�
 *
 * 1. ��ʱ��֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���CAP��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. �ڱ������У��ĸ�����Ĵ���ʹ�����£�
 *     - ����Ĵ���0���ڲ�������ͨ��0
 *     - ����Ĵ���1���ڲ�������ͨ��0
 *     - ����Ĵ���2���ڲ�������ͨ��0
 *     - ����Ĵ���3���ڲ�������ͨ��0
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_TIMER_CAP_H
#define __AMDR_TIMER_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "amhw_timer.h"

/**
 * \addtogroup amdr_if_timer_cap
 * \copydoc amdr_timer_cap.h
 * @{
 */

/**
 * \brief ��ʱ����������ص�GPIO��Ϣ
 */
typedef struct amdr_timer_cap_ioinfo {
    uint32_t gpio;           /**< \brief ��Ӧ��GPIO�ܽ�                       */
    uint32_t func;           /**< \brief Ϊ������ʱ��GPIO��������           */
    uint32_t dfunc;          /**< \brief ���ܹܽŲ�����ʱ��Ĭ��GPIO�������� */
} amdr_timer_cap_ioinfo_t;

/**
 * \brief ��ʱ����������ص��豸��Ϣ
 */
typedef struct amdr_timer_cap_devinfo {
    amhw_timer_t            *p_hw_timer;   /**< \brief ָ��Standard Timer�Ĵ������ָ�� */
    uint8_t                  inum;         /**< \brief ��ʱ���жϺ�                     */
    uint8_t                  channels_num; /**< \brief ʹ�õ�ͨ���������Ϊ4            */
    amdr_timer_cap_ioinfo_t *p_ioinfo;     /**< \brief ָ�򲶻�ܽ���Ϣ�ṹ��           */
} amdr_timer_cap_devinfo_t;
 
/**
 * \brief ��ʱ���������豸�ṹ��
 */
typedef struct amdr_timer_cap_dev {
    am_cap_serv_t           cap_serv;       /**< \brief ��׼CAP����           */
    
    struct {   
        am_cap_callback_t   callback_func;  /**< \brief �ص�����              */
        void               *p_arg;          /**< \brief �ص��������û�����    */
    }callback_info[4];                      /**< \brief �洢���4ͨ���Ļص�������Ϣ */
    
    /** \brief ָ��ʱ���������豸��Ϣ������ָ�� */
    const amdr_timer_cap_devinfo_t  *p_devinfo; 

} amdr_timer_cap_dev_t;

/**
 * \brief ��ʼ����ʱ��Ϊ������
 *
 * \param[in] p_dev     : ָ��ʱ���������豸��ָ��
 * \param[in] p_devinfo : ָ��ʱ���������豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t amdr_timer_cap_init(amdr_timer_cap_dev_t           *p_dev,
                                    const amdr_timer_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ�ö�ʱ��������ʱ�����ʼ����ʱ�������ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��ʱ���������豸��ָ��
 * \return ��
 */
void amdr_timer_cap_deinit(amdr_timer_cap_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_TIMER_CAP_H */

/* end of file */

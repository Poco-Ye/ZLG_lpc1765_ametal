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
 * \brief ��ʱ����STD Timer������������Timer��׼�ӿ�
 *
 * 1. ��ʱ��֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���Timer��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. �ڱ������У��ĸ�ƥ��Ĵ���ʹ�����£�
 *     - ƥ��Ĵ���0���ڱ��涨ʱ����ֵ�������������ж�
 *     - ƥ��Ĵ���1δʹ��
 *     - ƥ��Ĵ���2δʹ��
 *     - ƥ��Ĵ���3δʹ��
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_TIMER_TIMING_H
#define __AMDR_TIMER_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_timer.h"

/**
 * \addtogroup amdr_if_timer_timing
 * \copydoc amdr_timer_timing.h
 * @{
 */

/**
 * \brief ��ʱ����ʱ������ص��豸��Ϣ
 */
typedef struct amdr_timer_timing_devinfo {
    amhw_timer_t    *p_hw_timer; /**< \brief ָ��Standard Timer�Ĵ������ָ��  */
    uint8_t          inum;       /**< \brief ��ʱ���жϺ�                      */
} amdr_timer_timing_devinfo_t;
    
/**
 * \brief ��ʱ����ʱ�����豸�ṹ�嶨��
 */
typedef struct amdr_timer_timing_dev {

    am_timer_serv_t   timer_serv;       /**< \brief ��׼��ʱ(Timer)����       */
    
    struct {    
        void (*pfn_callback)(void *);   /**< \brief �ص�����                  */
        void *p_arg;                    /**< \brief �ص��������û�����        */
    } callback_info[1];                 /**< \brief ��֧�ֵ�ͨ��              */
    
    /** \brief ָ��ʱ��(��ʱ����)�豸��Ϣ������ָ�� */
    const amdr_timer_timing_devinfo_t  *p_devinfo; 

} amdr_timer_timing_dev_t;

/**
 * \brief ��ʼ����ʱ��Ϊ��ʱ����
 *
 * \param[in] p_dev     : ָ��ʱ��(��ʱ����)�豸ָ��
 * \param[in] p_devinfo : ָ��ʱ��(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t amdr_timer_timing_init(amdr_timer_timing_dev_t            *p_dev,
                                         const amdr_timer_timing_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ�ö�ʱ���Ķ�ʱ����ʱ�����ʼ����ʱ���Ķ�ʱ���ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��ʱ��(��ʱ����)�豸ָ��
 * \return ��
 */
void amdr_timer_timing_deinit(amdr_timer_timing_dev_t *p_dev);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_TIMER_TIMING_H */

/* end of file */

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
 * \brief SCT����������Timer��׼�ӿ�
 *
 * 1. SCT֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���Timer��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. �ڱ������У�SCT�����Դʹ�����£�
 *    - ƥ��Ĵ���0���ڱ��涨ʱ����ֵ�����¼�0��������Բ����жϡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-14  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SCT_TIMING_H
#define __AMDR_SCT_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_sct.h"

/**
 * \addtogroup amdr_if_sct_timing
 * \copydoc amdr_sct_timing.h
 * @{
 */

/** \brief SCT������1��32λ��ʱ��ģʽ, �����ṩ1����ʱ��ͨ��    */
#define AMDR_SCT_TIMING_1_32BIT      1

/** \brief SCT������2��16λ��ʱ��ģʽ, ���ṩ2����ʱ��ͨ��      */
#define AMDR_SCT_TIMING_2_16BIT      2

/**
 * \brief SCT��ʱ������ص��豸��Ϣ
 */
typedef struct amdr_sct_timing_devinfo {
    amhw_sct_t   *p_hw_sct;    /**< \brief ָ��SCT�Ĵ������ָ��              */
    uint8_t       flag;        /**< \brief SCT���ñ�־(1-32bit ���� 2-16bit)  */
    uint8_t       inum;        /**< \brief SCT�жϺ�                          */
} amdr_sct_timing_devinfo_t;
    
/**
 * \brief SCT��ʱ�����豸
 */
typedef struct amdr_sct_timing_dev {

    am_timer_serv_t   timer_serv;     /**< \brief ��׼��ʱ(Timer)����         */

    struct {
        void (*pfn_callback)(void *); /**< \brief �ص�����                    */
        void *p_arg;                  /**< \brief �ص��������û�����          */
    } callback_info[2];               /**< \brief ���֧��2ͨ��(2-16bit��ʱ��)*/
    
    /** \brief ָ��SCT(��ʱ����)�豸��Ϣ������ָ�� */
    const amdr_sct_timing_devinfo_t  *p_devinfo; 

} amdr_sct_timing_dev_t;

/**
 * \brief ��ʼ��SCTΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��SCT(��ʱ����)�豸��ָ��
 * \param[in] p_devinfo : ָ��SCT(��ʱ����)�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t amdr_sct_timing_init(amdr_sct_timing_dev_t            *p_dev,
                                       const amdr_sct_timing_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��SCT��ʱ����ʱ�����ʼ��SCT��ʱ���ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��SCT(��ʱ����)�豸��ָ��
 * \return ��
 */
void amdr_sct_timing_deinit(amdr_sct_timing_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SCT_TIMING_H */

/* end of file */

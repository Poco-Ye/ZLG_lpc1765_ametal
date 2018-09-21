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
 * \brief MRT����������Timer��׼�ӿ�
 *
 * ������ʵ����MRT�Ķ�ʱ����
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_MRT_H
#define __AMDR_MRT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_mrt.h"

/**
 * \addtogroup amdr_if_mrt
 * \copydoc amdr_mrt.h
 * @{
 */

/**
 * \brief MRT�豸��Ϣ�ṹ��
 */
typedef struct amdr_mrt_devinfo {
    amhw_mrt_t      *p_hw_mrt;      /**< \brief ָ��MRT�Ĵ������ָ��         */
    uint8_t          inum;          /**< \brief MRT�жϺ�                     */
    uint8_t          channel_nums;  /**< \brief ֧�ֵ�ͨ���������Ϊ4         */
} amdr_mrt_devinfo_t;

/**
 * \brief MRT�豸
 */
typedef struct amdr_mrt_dev {

    am_timer_serv_t   timer_serv;      /**< \brief ��׼��ʱ(Timer)����        */

    struct {
        void (*pfn_callback)(void *);  /**< \brief �ص�����                   */
        void *p_arg;                   /**< \brief �ص��������û�����         */
    } callback_info[AMHW_MRT_CHANNELS_NUM]; /**< \brief �ص�������Ϣ����      */
        
    /** \brief ָ��MRT�豸��Ϣ������ָ�� */
    const amdr_mrt_devinfo_t  *p_devinfo; 

} amdr_mrt_dev_t;

/**
 * \brief ��ʼ��MRTΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��MRT�豸��ָ��
 * \param[in] p_devinfo : ָ��MRT�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t amdr_mrt_init(amdr_mrt_dev_t            *p_dev,
                                const amdr_mrt_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��MRTʱ�����ʼ��MRT���ͷ������Դ
 * \param[in] p_dev : ָ��MRT�豸��ָ��
 * \return ��
 */
void amdr_mrt_deinit(amdr_mrt_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_MRT_H */

/* end of file */

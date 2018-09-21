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
 * \brief RIT����������Timer��׼�ӿ�
 *
 * ������ʵ����RIT�Ķ�ʱ����
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_RIT_H
#define __AMDR_RIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_rit.h"

/**
 * \addtogroup amdr_if_rit
 * \copydoc amdr_rit.h
 * @{
 */

/**
 * \brief RIT�豸��Ϣ�ṹ��
 */
typedef struct amdr_rit_devinfo {
    amhw_rit_t      *p_hw_rit;      /**< \brief ָ��RIT�Ĵ������ָ��         */
    uint8_t          inum;          /**< \brief RIT�жϺ�                     */
} amdr_rit_devinfo_t;
    
/**
 * \brief RIT�豸
 */
typedef struct amdr_rit_dev {

    am_timer_serv_t   timer_serv;      /**< \brief ��׼��ʱ(Timer)����        */

    struct {
        void (*pfn_callback)(void *);  /**< \brief �ص�����                   */
        void *p_arg;                   /**< \brief �ص��������û�����         */
    } callback_info[1];    /**< \brief �ص�������Ϣ���飬��֧��һ��ͨ��       */
    
    /** \brief ָ��RIT�豸��Ϣ������ָ�� */
    const amdr_rit_devinfo_t  *p_devinfo; 

} amdr_rit_dev_t;

/**
 * \brief ��ʼ��RITΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��RIT�豸��ָ��
 * \param[in] p_devinfo : ָ��RIT�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t amdr_rit_init(amdr_rit_dev_t            *p_dev,
                                const amdr_rit_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��RITʱ�����ʼ��RIT���ͷ������Դ
 * \param[in] p_dev : ָ��RIT�豸��ָ��
 * \return ��
 */
void amdr_rit_deinit(amdr_rit_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_RIT_H */

/* end of file */

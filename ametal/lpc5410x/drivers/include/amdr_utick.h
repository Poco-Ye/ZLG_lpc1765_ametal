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
 * \brief UTICK����������Timer��׼�ӿ�
 *
 * ������ʵ����UTICK�Ķ�ʱ����
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_UTICK_H
#define __AMDR_UTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_timer.h"
#include "amhw_utick.h"

/**
 * \addtogroup amdr_if_utick
 * \copydoc amdr_utick.h
 * @{
 */

/**
 * \brief UTICK�豸��Ϣ�ṹ��
 */
typedef struct amdr_utick_devinfo {
    amhw_utick_t    *p_hw_utick;    /**< \brief ָ��UTICK�Ĵ������ָ��       */
    uint8_t          inum;          /**< \brief UTICK�жϺ�                   */
} amdr_utick_devinfo_t;
    
/**
 * \brief UTICK�豸
 */
typedef struct amdr_utick_dev {

    am_timer_serv_t   timer_serv;       /**< \brief ��׼��ʱ(Timer)����       */

    struct {
        void (*pfn_callback)(void *);   /**< \brief �ص�����                  */
        void *p_arg;                    /**< \brief �ص��������û�����        */
    } callback_info[1];                 /**< \brief UTICK��֧��1��ͨ��        */
    
    /** \brief ָ��UTICK�豸��Ϣ������ָ�� */
    const amdr_utick_devinfo_t  *p_devinfo; 

} amdr_utick_dev_t;

/**
 * \brief ��ʼ��UTICKΪ��ʱ����
 *
 * \param[in] p_dev     : ָ��UTICK�豸��ָ��
 * \param[in] p_devinfo : ָ��UTICK�豸��Ϣ������ָ��
 *
 * \return Timer��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_timer_handle_t amdr_utick_init(amdr_utick_dev_t            *p_dev,
                                  const amdr_utick_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��UTICKʱ�����ʼ��UTICK���ͷ������Դ
 * \param[in] p_dev : ָ��UTICK�豸��ָ��
 * \return ��
 */
void amdr_utick_deinit(amdr_utick_dev_t *p_dev);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_UTICK_H */

/* end of file */

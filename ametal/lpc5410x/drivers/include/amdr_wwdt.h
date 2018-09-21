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
 * \brief  WWDT����������WWDT��׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-07  fft, first implementation.
 * \endinternal
 */

#ifndef __AMDR_WWDT_H
#define __AMDR_WWDT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_wdt.h"
#include "amhw_wwdt.h"
    
/** 
 * \addtogroup amdr_if_wwdt
 * \copydoc amdr_wwdt.h
 * @{
 */

/**
 * \brief WWDT �豸��Ϣ�ṹ��
 */
typedef struct amdr_wwdt_devinfo {
    amhw_wwdt_t *p_hw_wwdt;             /**< \brief ָ��WWDT�Ĵ�����Ľṹ��ָ�� */
} amdr_wwdt_devinfo_t;
    
/**
 * \brief WWDT �豸�ṹ��
 */
typedef struct amdr_wwdt_dev {

    am_wdt_serv_t              wdt_serv;   /**< \brief WWDT��׼����         */
    const amdr_wwdt_devinfo_t *p_devinfo;  /**< \brief ָ��WWDT�豸��Ϣ��ָ�� */
} amdr_wwdt_dev_t;

/**
 * \brief ��ʼ��WWDT
 *
 * \param[in] p_dev     : ָ��WWDT�豸
 * \param[in] p_devinfo : ָ��WWDT�豸��Ϣ
 *
 * \return WWDT��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_wdt_handle_t amdr_wwdt_init(amdr_wwdt_dev_t           *p_dev,
                               const amdr_wwdt_devinfo_t *p_devinfo);

/**
 * \brief ���WWDT��ʼ��
 * \param[in] p_dev : ָ��WWDT�豸
 * \return  ��
 */
void amdr_wwdt_deinit(amdr_wwdt_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_WWDT_H */

/* end of file */

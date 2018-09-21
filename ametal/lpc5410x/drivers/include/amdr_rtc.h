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
 * \brief  RTC����������RTC��׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-27  fft, first implementation.
 * \endinternal
 */

#ifndef __AMDR_RTC_H
#define __AMDR_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_rtc.h"
#include "amhw_rtc.h"


/**
 * \addtogroup amdr_if_rtc
 * \copydoc amdr_rtc.h
 * @{
 */

/**
 * \brief RTC �豸��Ϣ�ṹ��
 */
typedef struct amdr_rtc_devinfo {
    amhw_rtc_t  *p_hw_rtc;                  /**< \brief ָ��RTC�Ĵ�����Ľṹ��ָ�� */
} amdr_rtc_devinfo_t;
    
/**
 * \brief RTC �豸�ṹ��
 */
typedef struct amdr_rtc_dev {
    am_rtc_serv_t             rtc_serv;     /**< \brief RTC��׼����         */
    const amdr_rtc_devinfo_t *p_devinfo;    /**< \brief ָ��RTC�豸��Ϣ��ָ�� */
} amdr_rtc_dev_t;

/**
 * \brief ��ʼ��RTC
 *
 * \param[in] p_dev     : ָ��RTC�豸
 * \param[in] p_devinfo : ָ��RTC�豸��Ϣ
 *
 * \return RTC��׼���������������Ϊ NULL��������ʼ��ʧ�ܡ�
 */
am_rtc_handle_t amdr_rtc_init(amdr_rtc_dev_t           *p_dev,
                              const amdr_rtc_devinfo_t *p_devinfo);

/**
 * \brief ���RTC��ʼ��
 * \param[in] p_dev : ָ��RTC�豸
 * \return  ��
 */
void amdr_rtc_deinit(amdr_rtc_dev_t *p_dev);


/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif

/* end of file */

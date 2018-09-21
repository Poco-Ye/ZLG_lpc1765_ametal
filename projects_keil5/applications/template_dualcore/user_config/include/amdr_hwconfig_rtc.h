/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief LPC5410X RTC�û�����ͷ�ļ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  hbt, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_RTC_H
#define __AMDR_HWCONFIG_RTC_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief RTC ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_rtc_init(void);

/**
 * \brief ���RTCƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_rtc_deinit(void);

/**\brief RTC �豸��Ϣ */
extern const amdr_rtc_devinfo_t  g_rtc_devinfo;

/**\brief RTC �豸 */
extern amdr_rtc_dev_t            g_rtc_dev;
    
#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_RTC_H */

/* end of file */

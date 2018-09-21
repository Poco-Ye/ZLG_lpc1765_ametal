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
 * \brief LPC5410X ADC �û�����ͷ�ļ���
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  hbt, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_ADC_H
#define __AMDR_HWCONFIG_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \brief ADC0 ƽ̨��ʼ����
 * \return �ޡ� 
 */
void amdr_plfm_adc0_init(void);

/**
 * \brief ���ADC0 ƽ̨��ʼ����
 * \return �ޡ�
 */
void amdr_plfm_adc0_deinit(void);


extern const amdr_adc_devinfo_t g_adc0_devinfo; /**< \brief ADC0 �豸��Ϣ */
extern amdr_adc_dev_t           g_adc0_dev;     /**< \brief ADC0�豸      */

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_ADC_H */

/* end of file */

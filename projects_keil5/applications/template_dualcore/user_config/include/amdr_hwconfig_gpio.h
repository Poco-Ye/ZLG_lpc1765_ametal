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
 * \brief LPC5410X GPIO �û�����ͷ�ļ���
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  hbt, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_GPIO_H
#define __AMDR_HWCONFIG_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
    
/**
 * \brief GPIO ƽ̨��ʼ����
 * \return �ޡ�
 */
void amhw_plfm_gpio_init(void);

/**
 * \brief GPIO ƽ̨ȥ��ʼ����
 * \return �ޡ�
 */
void amhw_plfm_gpio_deinit(void);

extern const amdr_gpio_devinfo_t g_gpio_devinfo; /**< \brief GPIO�豸��Ϣ */
extern amdr_gpio_dev_t           g_gpio_dev;     /**< \brief GPIO�豸     */

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_GPIO_H */

/* end of file */

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
 * \brief LPC5410X WWDT �û�����ͷ�ļ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_WWDT_H
#define __AMDR_HWCONFIG_WWDT_H

#include "ametal.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief WWDT ƽ̨��ʼ����
 * \return ��.
 */
void amhw_plfm_wwdt_init(void);

/**
 * \brief ��� WWDTƽ̨��ʼ��
 * \return ��.
 */
void amhw_plfm_wwdt_deinit(void);

/** \brief WWDT �豸��Ϣ */
extern const amdr_wwdt_devinfo_t  g_wwdt_devinfo;

/** \brief WWDT �豸 */
extern amdr_wwdt_dev_t            g_wwdt_dev;

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_WWDT_H */

/* end of file */

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
 * \brief LPC5410X RIT�û������ļ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_RIT_H
#define __AMDR_HWCONFIG_RIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
#include "amdr_rit.h"

/** \brief RIT�豸��Ϣ */
extern amdr_rit_dev_t            g_rit_dev;
    
/** \brief RIT�豸 */
extern const amdr_rit_devinfo_t  g_rit_devinfo;

/**
 * \brief RITƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_rit_init(void);
    
/**
 * \brief ���RITƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_rit_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_RIT_H */

/* end of file */

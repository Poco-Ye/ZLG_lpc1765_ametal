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
 * \brief LPC5410X SCT0�������û����� 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_SCT_CAP_H
#define __AMDR_HWCONFIG_SCT_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/**
 * \brief SCT0������ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_sct0_cap_init(void);
    
/**
 * \brief ���SCT0������ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_sct0_cap_deinit(void);

/** \brief SCT0�������豸��Ϣ */
extern amdr_sct_cap_dev_t            g_sct0_cap_dev;
    
/** \brief SCT0�������豸The The SCT0 for capture device */
extern const amdr_sct_cap_devinfo_t  g_sct0_cap_devinfo;

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_SCT_CAP_H */

/* end of file */

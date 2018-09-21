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
 * \brief LPC5410X SCT��ʱ�������û������ļ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_SCT_TIMING_H
#define __AMDR_HWCONFIG_SCT_TIMING_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"

/** \brief SCT0��ʱ�����ܵ��豸��Ϣ */
extern amdr_sct_timing_dev_t            g_sct0_timing_dev;
    
/** \brief SCT0��ʱ�������豸 */
extern const amdr_sct_timing_devinfo_t  g_sct0_timing_devinfo;

/**
 * \brief SCT0��ʱ������ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_sct0_timing_init(void);
    
/**
 * \brief ���SCT0��ʱ�����ܵ�ƽ̨��ʼ��
 * \return ��
 */
void amhw_plfm_sct0_timing_deinit(void);

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_SCT_TIMING_H */

/* end of file */

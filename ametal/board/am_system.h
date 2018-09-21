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
 * \brief ϵͳ���ýӿ�
 * 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_SYSTEM_H
#define __AM_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "amhw_clock.h"
#include "amhw_pll.h"

/**
 * \brief ϵͳ��ʼ������Ҫ������ϵͳʱ�ӵĳ�ʼ��
 */   
void am_system_init(void);
 

#ifdef __cplusplus
}
#endif

#endif /* __AM_SYSTEM_H */

/* end of file */

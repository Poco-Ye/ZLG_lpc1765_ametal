/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief Mailbox implementation for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */
#include "amhw_mbox.h"

/** 
 * \brief Enter Mutex region
 */
void amhw_mbox_mutex_take (amhw_mailbox_t *p_hw_mbox)
{
    /* Wait forever until we can get the mutex */
    while (amhw_mbox_mutex_get(p_hw_mbox) == 0) {}
}

/**
 * \brief Exit Mutex region
 */
void amhw_mbox_mutex_give (amhw_mailbox_t *p_hw_mbox)
{
    amhw_mbox_mutex_set(p_hw_mbox);
}

/* end of file */

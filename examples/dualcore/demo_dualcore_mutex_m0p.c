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
 * \brief ˫�ˣ�M0+���֣������ź�����ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. ������� "The Cortex-M0+ operation\r\n" ��
 * 
 * \par Դ����
 * \snippet demo_dualcore_mutex_m0p.c src_dualcore_mutex_m0p 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mutex_m0p
 * \copydoc demo_dualcore_mutex_m0p.c
 */

/** [src_dualcore_mutex_m0p] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief ������
 */
int main (void)
{
    /* The board initialization */
    am_board_init();

    while (1) {
        
        /* 
         * ���ڴ��������� cortex-M4����ģ�
         * Ϊ�˱��������ں�ͬʱ���ʴ��ڣ� ���빲������ʴ���
         */
        amhw_mbox_mutex_take(AMHW_MAILBOX);
        AM_DBG_INFO("The Cortex-M0+ operation\r\n");
        amhw_mbox_mutex_give(AMHW_MAILBOX);
        
        am_mdelay(500);
        
    }
}

/** [src_dualcore_mutex_m0p] */

/* end of file */

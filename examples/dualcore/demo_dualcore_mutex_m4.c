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
 * \brief ˫�ˣ�M4���֣������ź�����ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. ������� "The Cortex-M4 operation\r\n"�� 
 * 
 * \par Դ����
 * \snippet demo_dualcore_mutex_m4.c src_dualcore_mutex_m4 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mutex_m4
 * \copydoc demo_dualcore_mutex_m4.c
 */

/** [src_dualcore_mutex_m4] */
#include "ametal.h"
#include "am_board.h"
#include "..\shared\lpc5410x_config_memory.h"

/** 
 * \brief Mailbox ƽ̨��ʼ��
 */
void amhw_plfm_mbox_init (void)
{
    /* ʹ�ܲ���λ��Ϣ����ʱ�� */
    amhw_clock_periph_enable(AMHW_CLOCK_MAILBOX);
    amhw_syscon_periph_reset(AMHW_RESET_MAILBOX);
    
    /* ��ʼ����������Ļ�����ʣ���λ */
    amhw_mbox_mutex_set(AMHW_MAILBOX);
}

/**
 * \brief Application Main entry point
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    amhw_plfm_mbox_init();

    /* ����M0+�ں� */
    amhw_cpu_boot_m0p(LPC5410X_CFG_MEM_FLASH_CM0_START);
    
    while (1) {
        
        /* 
         * ���ڴ��������� cortex-M0+����ģ�
         * Ϊ�˱��������ں�ͬʱ���ʴ��ڣ� ���빲������ʴ���
         */
        amhw_mbox_mutex_take(AMHW_MAILBOX);
        AM_DBG_INFO("The Cortex-M4 operation\r\n");
        amhw_mbox_mutex_give(AMHW_MAILBOX);
        
        am_mdelay(500);
    }
}

/** [src_dualcore_mutex_m4] */

/* end of file */

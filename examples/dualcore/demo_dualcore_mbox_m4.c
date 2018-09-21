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
 * \brief ˫�ˣ�M4���֣�MailBox��ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. �����������1��������500msʱ�������͵�M0+�ںˣ�
 *   2. �����յ�M0+�ں˵���Ӧ����������ַ���;
 *      "The value to send M0+ be received" ��Ϊ��Ӧ��
 * 
 * \par Դ����
 * \snippet demo_dualcore_mbox_m4.c src_dualcore_mbox_m4 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  jon, add mail box for CPUs communicate.
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mbox_m4
 * \copydoc demo_dualcore_mbox_m4.c
 */
 

/** [src_dualcore_mbox_m4] */
#include "ametal.h"
#include "am_board.h"
#include "..\shared\lpc5410x_config_memory.h"



/** 
 * \brief ��Ϣ�����жϴ�����
 * \param[in] p_arg : �ж���ڲ���
 * \return  ��
 */
void mbox_irq_handler (void *p_arg)
{
    amhw_mailbox_t *p_hw_mbox = (amhw_mailbox_t *)p_arg;
    
    AM_DBG_INFO("The value to send M0+ be received\r\n");
    
    /* ���M4 �ں���Ϣ�������������λ */
    amhw_mbox_val_bits_clr(p_hw_mbox, AMHW_MBOX_M4_ID, 0xFFFFFFFF);
}

/** 
 * \brief ��Ϣ����ƽ̨��ʼ��
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
 * \brief  ������
 */
int main (void)
{
    uint32_t shared_data = 0;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    amhw_plfm_mbox_init();

    /* ���Ӳ�ʹ����Ϣ�����ж� */
    am_int_connect(INUM_MAILBOX, mbox_irq_handler, (void *)AMHW_MAILBOX);
    am_int_enable(INUM_MAILBOX);
    
    /* ����M0+�ں� */
    amhw_cpu_boot_m0p(LPC5410X_CFG_MEM_FLASH_CM0_START);
    
    while (1) {

        /* 
         * ���ڷ��͵�M0+�ں˵������ǹ����ַ�����ݣ�
         * Ϊ�˱��������ں�ͬʱ����, ���빲������ʴ���
         */
        amhw_mbox_mutex_take(AMHW_MAILBOX);
        shared_data++;
        amhw_mbox_mutex_give(AMHW_MAILBOX);
        
        /* �������ݵ�M0+�ں� */
        amhw_mbox_val_set(AMHW_MAILBOX, AMHW_MBOX_M0PLUS_ID, (uint32_t)&shared_data);
        am_mdelay(500);

    }
}

/** [src_dualcore_mbox_m4] */

/* end of files */

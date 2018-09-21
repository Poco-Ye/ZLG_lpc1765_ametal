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
 * \brief ˫�ˣ�M0+���֣�MailBox��ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. �����յ�ż��ʱ��LED����
 *   2. �����յ������ǣ�LED��LED��500msʱ������˸��
 *   3. �����յ���������ʱ, ����1��M4�ں���Ϊ��Ӧ��
 * 
 * \par Դ����
 * \snippet demo_dualcore_mbox_m0p.c src_dualcore_mbox_m0p 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  jon, add mail box for CPUs communicate.
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mbox_m0p
 * \copydoc demo_dualcore_mbox_m0p.c
 */

/** [src_dualcore_mbox_m0p] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief mailbox�жϴ�����
 * \param[in] p_arg : �ж���ڲ���
 * \return  ��
 */
void mbox_irq_handler (void *p_arg)
{
    amhw_mailbox_t *p_hw_mbox = (amhw_mailbox_t *)p_arg;
    
    uint32_t shared_value;
    
    /* 
     * ��ȡM0+�ں���Ϣ���������
     */
    uint32_t *p_shared_vale = (uint32_t *)amhw_mbox_val_get(p_hw_mbox, AMHW_MBOX_M0PLUS_ID);
    
    /* 
     * ���ڵõ��������ǹ����ַ������ 
     * Ϊ�˱��������ں�ͬʱ����, ���빲������ʴ���
     */
    amhw_mbox_mutex_take(p_hw_mbox);
    shared_value = *p_shared_vale;
    amhw_mbox_mutex_give(p_hw_mbox);
    
    if (shared_value % 2 == 0) {
        am_led_on(LED0);
    
    } else {
        am_led_off(LED0);
    }

    /* ���M0+�ں���Ϣ�������������λ */
    amhw_mbox_val_bits_clr(p_hw_mbox, AMHW_MBOX_M0PLUS_ID, 0xFFFFFFFF);
    
    /* д����1��M4�ںˣ��������յ�������� */
    amhw_mbox_val_set(p_hw_mbox, AMHW_MBOX_M4_ID, 1);     
    
}

/**
 * \brief ������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();

    /* ���Ӳ�ʹ����Ϣ�����ж� */
    am_int_connect(INUM_MAILBOX, mbox_irq_handler, (void *)AMHW_MAILBOX);
    am_int_enable(INUM_MAILBOX);
    
    while (1) {
        __WFI();
    }
}

/** [src_dualcore_mbox_m0p] */

/* end of file */

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
 * \brief USART��ѯģʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_0 ��������PC���ڵ�TXD;
 *   2. PIO0_1 ��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. �������"USART polling mode test:"��
 *   2. ����������յ����ַ�����
 *
 * \note ������Դ���ʹ���뱾������ͬ�Ĵ��ڣ���Ӧ�ں�������ʹ�õ�����Ϣ�������
 *      ���磺AM_DBG_INFO()��
 *
 * \par Դ����
 * \snippet demo_std_uart_polling.c src_std_uart_polling 
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_std_uart_polling
 * \copydoc demo_std_uart_polling.c
 */
 
 /** [src_std_uart_polling] */
#include "ametal.h"
#include "am_board.h"



/**
 * \brief ���������
 */
int main (void)
{
    uint8_t          uart0_buf[5];
    am_uart_handle_t handle;
    
    /* �弶��ʼ��  */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_usart0_init();
    amhw_plfm_fifo_init();
    
    /* USART��ʼ��  */
    handle = amdr_usart_init(&g_usart0_dev, &g_usart0_devinfo);

    am_uart_poll_send(handle,"USART polling mode test:\r\n", 
                             sizeof("USART polling mode test:\r\n"));
    
    while (1) {
        
        /* ����һ���ַ� */
        am_uart_poll_receive(handle, uart0_buf, 1);
        
        /* ���͸ոս��յ��ַ� */
        am_uart_poll_send(handle, uart0_buf, 1);
    }
}

 /** [src_std_uart_polling] */
 
/* end of file */


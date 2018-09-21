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
 * \brief UART���ж�ģʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_0 ��������PC���ڵ�TXD;
 *   2. PIO0_1 ��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. �������"UART interrupt mode test:"��
 *   2. ����������յ����ַ�����
 *
 * \note ����û��ʹ�ô��仺����������ջ����������λ���������ֻʹ����Ϊ���պ�
 *       ���Ͷ����õ��û����ݻ����������ÿ�η��ͻ��������Ҫ���ϴη��ͻ������
 *       ����ɺ���ܽ��С�
 *
 * \par Դ����
 * \snippet demo_std_uart_int.c src_std_uart_int
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */


/**
 * \addtogroup demo_if_std_uart_int
 * \copydoc demo_std_uart_int.c
 */

 /** [src_std_uart_int] */
#include "ametal.h"
#include "am_board.h"


 /* ���崮�ڣ��ж�ģʽ���豸�ṹ�壬���ڷ�����ؿռ� */
am_uart_int_dev_t  g_uart0_int_dev;

/**
 * \brief ���������
 */
int main (void)
{
    uint8_t              uart0_buf[5];
    am_uart_handle_t     uart_handle;
    am_uart_int_handle_t handle;

    /* �弶��ʼ��  */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_usart0_init();
    amhw_plfm_fifo_init();

    /* USART��ʼ�� */
    uart_handle = amdr_usart_init(&g_usart0_dev, &g_usart0_devinfo);

    /* USART��ʼ��Ϊ�ж�ģʽ */
    handle      = am_uart_int_init(&g_uart0_int_dev, uart_handle);

    am_uart_int_send(handle,
                     "UART interrupt mode test:\r\n",
                     sizeof("UART interrupt mode test:\r\n"));

    while (1) {

        /* ����һ���ַ� */
        am_uart_int_receive(handle, uart0_buf, 1);

        /* ���͸ոս��յ��ַ� */
        am_uart_int_send(handle, uart0_buf, 1);
    }
}

 /** [src_std_uart_int] */

/* end of file */

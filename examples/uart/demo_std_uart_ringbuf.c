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
 * \brief USART���λ�����ģʽ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_0 ��������PC���ڵ�TXD;
 *   2. PIO0_1 ��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. �������"USART ring buffer test\r\n"��
 *   2. ����������յ����ַ�����
 *
 * \par Դ����
 * \snippet demo_std_uart_ringbuf.c src_std_uart_ringbuf
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_uart_ringbuf
 * \copydoc demo_std_uart_ringbuf.c
 */

/** [src_std_uart_ringbuf] */
#include "ametal.h"
#include "am_board.h"


#define UART0_RX_BUF_SIZE  128  /**< \brief ���ջ��λ�������С��Ӧ��Ϊ2^n  */
#define UART0_TX_BUF_SIZE  128  /**< \brief ���ͻ��λ�������С��Ӧ��Ϊ2^n  */

static char uart0_rxbuf[UART0_RX_BUF_SIZE];
static char uart0_txbuf[UART0_TX_BUF_SIZE];

am_uart_ringbuf_dev_t  g_uart0_ringbuf_dev;

/**
 * \brief ���������
 */
int main (void)
{
    uint8_t                  uart0_buf[5];
    am_uart_handle_t         uart_handle;
    am_uart_ringbuf_handle_t handle;

    /* �弶��ʼ��  */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_usart0_init();
    amhw_plfm_fifo_init();

    /* USART��ʼ��    */
    uart_handle = amdr_usart_init(&g_usart0_dev, &g_usart0_devinfo);

    /* USART��ʼ��Ϊ���λ�����ģʽ */
    handle = am_uart_ringbuf_init(&g_uart0_ringbuf_dev,
                                   uart_handle,
                                   uart0_rxbuf,
                                   UART0_RX_BUF_SIZE,
                                   uart0_txbuf,
                                   UART0_TX_BUF_SIZE);

    am_uart_ringbuf_send(handle,
                         "USART interrupt mode(Add ring buffer) test:\r\n",
                         sizeof("USART interrupt mode(Add ring buffer) test:\r\n"));

    while (1) {

        /* ����һ���ַ� */
        am_uart_ringbuf_receive(handle, uart0_buf, 1);

        /* ���͸ոս��յ��ַ� */
        am_uart_ringbuf_send(handle, uart0_buf, 1);

    }
}

/** [src_std_uart_ringbuf] */

/* end of file */

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
 * \brief USART环形缓冲区模式例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. PIO0_0 引脚连接PC串口的TXD;
 *   2. PIO0_1 引脚连接PC串口的RXD。
 *
 * - 实验现象：
 *   1. 串口输出"USART ring buffer test\r\n"；
 *   2. 串口输出接收到的字符串。
 *
 * \par 源代码
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


#define UART0_RX_BUF_SIZE  128  /**< \brief 接收环形缓冲区大小，应该为2^n  */
#define UART0_TX_BUF_SIZE  128  /**< \brief 发送环形缓冲区大小，应该为2^n  */

static char uart0_rxbuf[UART0_RX_BUF_SIZE];
static char uart0_txbuf[UART0_TX_BUF_SIZE];

am_uart_ringbuf_dev_t  g_uart0_ringbuf_dev;

/**
 * \brief 主函数入口
 */
int main (void)
{
    uint8_t                  uart0_buf[5];
    am_uart_handle_t         uart_handle;
    am_uart_ringbuf_handle_t handle;

    /* 板级初始化  */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_usart0_init();
    amhw_plfm_fifo_init();

    /* USART初始化    */
    uart_handle = amdr_usart_init(&g_usart0_dev, &g_usart0_devinfo);

    /* USART初始化为环形缓冲区模式 */
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

        /* 接收一个字符 */
        am_uart_ringbuf_receive(handle, uart0_buf, 1);

        /* 发送刚刚接收的字符 */
        am_uart_ringbuf_send(handle, uart0_buf, 1);

    }
}

/** [src_std_uart_ringbuf] */

/* end of file */

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
 * \brief UART的中断模式例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. PIO0_0 引脚连接PC串口的TXD;
 *   2. PIO0_1 引脚连接PC串口的RXD。
 *
 * - 实验现象：
 *   1. 串口输出"UART interrupt mode test:"；
 *   2. 串口输出接收到的字符串。
 *
 * \note 例程没有使用传输缓冲区或则接收缓冲区（像环形缓冲区），只使用了为接收和
 *       发送而设置的用户数据缓冲区，因此每次发送或接收数据要等上次发送或接收数
 *       据完成后才能进行。
 *
 * \par 源代码
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


 /* 定义串口（中断模式）设备结构体，用于分配相关空间 */
am_uart_int_dev_t  g_uart0_int_dev;

/**
 * \brief 主函数入口
 */
int main (void)
{
    uint8_t              uart0_buf[5];
    am_uart_handle_t     uart_handle;
    am_uart_int_handle_t handle;

    /* 板级初始化  */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_usart0_init();
    amhw_plfm_fifo_init();

    /* USART初始化 */
    uart_handle = amdr_usart_init(&g_usart0_dev, &g_usart0_devinfo);

    /* USART初始化为中断模式 */
    handle      = am_uart_int_init(&g_uart0_int_dev, uart_handle);

    am_uart_int_send(handle,
                     "UART interrupt mode test:\r\n",
                     sizeof("UART interrupt mode test:\r\n"));

    while (1) {

        /* 接收一个字符 */
        am_uart_int_receive(handle, uart0_buf, 1);

        /* 发送刚刚接收的字符 */
        am_uart_int_send(handle, uart0_buf, 1);
    }
}

 /** [src_std_uart_int] */

/* end of file */

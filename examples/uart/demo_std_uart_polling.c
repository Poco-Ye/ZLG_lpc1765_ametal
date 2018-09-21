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
 * \brief USART查询模式例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. PIO0_0 引脚连接PC串口的TXD;
 *   2. PIO0_1 引脚连接PC串口的RXD。
 *
 * - 实验现象：
 *   1. 串口输出"USART polling mode test:"；
 *   2. 串口输出接收到的字符串。
 *
 * \note 如果调试串口使用与本例程相同的串口，则不应在后续继续使用调试信息输出函数
 *      （如：AM_DBG_INFO()）
 *
 * \par 源代码
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
 * \brief 主函数入口
 */
int main (void)
{
    uint8_t          uart0_buf[5];
    am_uart_handle_t handle;
    
    /* 板级初始化  */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_usart0_init();
    amhw_plfm_fifo_init();
    
    /* USART初始化  */
    handle = amdr_usart_init(&g_usart0_dev, &g_usart0_devinfo);

    am_uart_poll_send(handle,"USART polling mode test:\r\n", 
                             sizeof("USART polling mode test:\r\n"));
    
    while (1) {
        
        /* 接收一个字符 */
        am_uart_poll_receive(handle, uart0_buf, 1);
        
        /* 发送刚刚接收的字符 */
        am_uart_poll_send(handle, uart0_buf, 1);
    }
}

 /** [src_std_uart_polling] */
 
/* end of file */


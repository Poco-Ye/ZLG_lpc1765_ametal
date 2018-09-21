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
 * \brief USART通过DMA方式接收数据，通过HW层的接口实现
 *
 * - 操作步骤：
 *   1. PIO0_0 引脚连接PC串口的TXD;
 *   2. PIO0_1 引脚连接PC串口的RXD;
 *   3. 通过PC一次性向MCU发送16个字符。
 *
 * - 实验现象：
 *   1. 串口打印出接收到的数据；
 *   2. 然后串口打印出“x tansfer done!”, 'x'是'A'或'B'。
 *
 * \note 当使用DMA传输时，USART不能使用FIFO
 *
 * \par 源代码
 * \snippet demo_hw_uart_rx_dma.c src_hw_uart_rx_dma
 *
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-26  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hw_uart_rx_dma
 * \copydoc demo_hw_uart_rx_dma.c
 */

/** [src_hw_uart_rx_dma] */
#include "ametal.h"
#include "am_board.h"
#include "am_delay.h"
#include "am_prj_config.h"



/** \brief USART通道*/
#define USART_CH            AMHW_USART0

/** \brief 波特率，在32kmode时波特率最大为9600 */
#define USART_BAUDRATE     (115200)

/** \brief DMA 重载描述符 */
__align(16) amhw_dma_xfer_desc_t g_desc[2];

uint8_t g_buf_dsta[16];          /**< \brief A目标端数据缓冲区 */
uint8_t g_buf_dstb[16];          /**< \brief B目标端数据缓冲区 */


/**
 * \brief DMA中断服务程序
 *
 * \param[in] p_arg : 用户自定义参数，通过 amdr_dma_isr_connect() 函数传递。
 * \param[in] p_flg : DMA中断标志，由底层驱动传入，该参数的可能取值：
 *                    (#AMDR_DMA_INTA)、(#AMDR_DMA_INTB) 或 (#AMDR_DMA_INTERR)。
 *
 * \return    无。
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;

    if (flag == AMDR_DMA_INTA) {
        amhw_usart_poll_send(USART_CH, g_buf_dsta, 16);
        amhw_usart_poll_send(USART_CH, "\r\n", sizeof("\r\n") - 1);

        amhw_usart_poll_send(USART_CH, "A transfer done!\r\n",
                                sizeof("A transfer done!\r\n") - 1);

    } else if (flag == AMDR_DMA_INTB) {
        amhw_usart_poll_send(USART_CH, g_buf_dstb, 16);
        amhw_usart_poll_send(USART_CH, "\r\n", sizeof("\r\n") - 1);

        amhw_usart_poll_send(USART_CH, "B transfer done!\r\n",
                                sizeof("B transfer done!\r\n") - 1);

    } else if (flag == AMDR_DMA_INTERR) {
        // 用户自定义执行代码。
    }
}

/**
 * \brief DMA传输：乒乓模式。
 */
void dma_tran_test (void)
{
    int i;
    uint32_t flags1, flags2;

    /* DMA通道配置 */
    amdr_dma_chan_setup(DMA_CHAN_USART0_RX_REQ,         /* USART0请求DMA通道            */
                        AMHW_DMA_CHAN_PERIPH_REQ_EN |   /* 使能外设请求                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF    |   /* 禁止硬件触发                 */
                        AMHW_DMA_CHAN_SINGLE_TRANS  |   /* 单次触发模式                 */
                        AMHW_DMA_CHAN_PRIO_5);          /* 通道优先级：5                */

    amdr_dma_chan_start(DMA_CHAN_USART0_RX_REQ);        /* 开始DMA传送                  */

    for (i = 0; i < 16; i++) {
        g_buf_dsta[i] = 0;
        g_buf_dstb[i] = 0;
    }

    /* DMA传输配置 */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                /* 当前配置描述符有效              */
             AMHW_DMA_XFER_RELOAD |                   /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                   /* 软件触发                        */
             AMHW_DMA_XFER_NO_CLRTRIG |               /* 不清除触发标志                  */
             AMHW_DMA_XFER_WIDTH_8BIT |               /* 传输数据宽度：8 bit             */
             AMHW_DMA_XFER_NO_SRCINC |                /* 源端数据地址不增加              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |          /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTA;                   /* 使能中断A                       */

    /* DMA传输配置 */
    flags2 = AMHW_DMA_XFER_CFG_VALID |                /* 当前配置描述符有效              */
             AMHW_DMA_XFER_RELOAD |                   /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                   /* 软件触发                        */
             AMHW_DMA_XFER_NO_CLRTRIG |               /* 不清除触发标志                  */
             AMHW_DMA_XFER_WIDTH_8BIT |               /* 传输数据宽度：8 bit             */
             AMHW_DMA_XFER_NO_SRCINC |                /* 源端数据地址不增加              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |          /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTB;                   /* 使能中断B                       */

    /* 建立通道描述符A */
    amdr_dma_xfer_desc_build(&g_desc[0],                        /* A的重载描述符         */
                             (uint32_t)AMHW_USART0_RXDAT_ADDR,  /* 源端数据缓冲区        */
                             (uint32_t)g_buf_dsta,              /* A的目标端缓冲区地址   */
                              16,                               /* 传输字节数            */
                              flags1);                          /* 传输配置 */

    /* 建立通道描述符B */
    amdr_dma_xfer_desc_build(&g_desc[1],                        /* B的重载描述符         */
                             (uint32_t)AMHW_USART0_RXDAT_ADDR,  /* 源端数据缓冲区        */
                             (uint32_t)g_buf_dstb,              /* B的目标端缓冲区地址   */
                              16,                               /* 传输字节数            */
                              flags2);                          /* 传输配置              */

    /* 连接DMA中断服务函数 */
    amdr_dma_isr_connect(DMA_CHAN_USART0_RX_REQ, dma_isr, (void *)0);

    /* 链接重载描述符 */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /* 启动DMA传输，马上开始传输 */
    amdr_dma_chan_xfer_startup(DMA_CHAN_USART0_RX_REQ, &g_desc[0]);
}

/**
 * \brief USART初始化
 */
void usart_init (void)
{
    /* 使能USART0时钟，并复位USART0 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART0);
    amhw_syscon_periph_reset(AMHW_RESET_USART0);

    /* 将PIO0_0引脚配置为UART0_RXD */
    am_gpio_pin_cfg(PIO0_0, PIO0_0_USART0_RXD | PIO0_0_PULLUP);

    /* 将PIO0_1引脚配置为UART0_TXD */
    am_gpio_pin_cfg(PIO0_1, PIO0_1_USART0_TXD | PIO0_0_PULLUP);

    amhw_clock_usart_baseclkrate_set(11059200);

    amhw_usart_config(USART_CH, AMHW_USART_CFG_8BIT       |
                                AMHW_USART_CFG_PARITY_NO  |
                                AMHW_USART_CFG_STOP_1 );

    amhw_usart_baudrate_set(USART_CH,
                            amhw_clock_usart_baseclkrate_get(),
                            115200);

    amhw_usart_enable(USART_CH);
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_dma_init();

    /* USART初始化 */
    usart_init();

    /* DMA初始化 */
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);

    /* 开始DMA传输 */
    dma_tran_test();

    while (1) {
        ;
    }
}

/** [src_hw_uart_rx_dma] */

/* end of file */

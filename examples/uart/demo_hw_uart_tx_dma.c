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
 * \brief USART通过DMA方式发送数据，通过HW层的接口实现
 *
 * - 操作步骤：
 *   1. PIO0_0 引脚连接PC串口的TXD;
 *   2. PIO0_1 引脚连接PC串口的RXD。
 *    
 * - 实验现象：
 *   1. 串口输出"aAbBcCdD..."；
 *   2. DMA传输完成后LED闪烁。
 *
 * \note 当使用DMA传输时，UART不能使用FIFO
 *
 * \par 源代码
 * \snippet demo_hw_uart_tx_dma.c src_hw_uart_tx_dma 
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-15  hbt, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_hw_uart_tx_dma
 * \copydoc demo_hw_uart_tx_dma.c
 */ 
/** [src_hw_uart_tx_dma] */
#include "ametal.h"
#include "am_board.h"



/** \brief USART通道*/
#define USART_CH            AMHW_USART0

/** \brief 波特率，在32kmode时波特率最大为9600 */
#define USART_BAUDRATE     (115200)

uint8_t g_buf_src[256];          /**< \brief 源端数据缓冲区       */

bool_t  g_trans_done;            /**< \brief 传输完成标志         */

/**
 * \brief 非乒乓传输时，描述符的地址不要求16字节对齐。        
 */
amhw_dma_xfer_desc_t g_desc;


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
        
        /* 停止传送Stop transfer */
        amdr_dma_chan_stop(DMA_CHAN_USART0_TX_REQ);
        
        amhw_usart_poll_send(USART_CH, "\r\n", sizeof("\r\n") - 1);
        amhw_usart_poll_send(USART_CH, "DMA transfer done!\r\n", 
                                sizeof("DMA transfer done!\r\n") - 1);
        
        /* DMA传输完成 */
        g_trans_done = TRUE;
    }
}

/**
 * \brief DMA传输
 */
void dma_tran_test (void)
{
    int      i;
    uint32_t flags;

    /* DMA通道配置 */
    amdr_dma_chan_setup(DMA_CHAN_USART0_TX_REQ,         /* USART0请求DMA通道            */
                        AMHW_DMA_CHAN_PERIPH_REQ_EN  |  /* 使能外设请求                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF     |  /* 禁止硬件触发                 */
                        AMHW_DMA_CHAN_SINGLE_TRANS   |  /* 单次触发模式                 */
                        AMHW_DMA_CHAN_PRIO_5);          /* 通道优先级：5                */

    for (i = 0; i < 256; i += 2) {
        g_buf_src[i]     = i / 2 % 26 + 'a';
        g_buf_src[i + 1] = i / 2 % 26 + 'A';
    }
    
    /* 开始DMA传输 */
    amdr_dma_chan_start(DMA_CHAN_USART0_TX_REQ);        

    /* DMA传输配置*/
    flags = AMHW_DMA_XFER_CFG_VALID       |             /* 当前配置描述符有效              */
            AMHW_DMA_XFER_NO_RELOAD       |             /* 禁止重载通道描述符              */
            AMHW_DMA_XFER_SWTRIG          |             /* 软件触发                        */
            AMHW_DMA_XFER_NO_CLRTRIG      |             /* 不清除触发标志                  */
            AMHW_DMA_XFER_WIDTH_8BIT      |             /* 传输数据宽度：8 bit             */
            AMHW_DMA_XFER_SRCINC_1X_WIDTH |             /* 源端数据地址按1个数据宽度递增   */
            AMHW_DMA_XFER_NO_DSTINC       |             /* 目标端数据地址不增加            */
            AMHW_DMA_XFER_SETINTA;                      /* 使能中断A                       */

    
    /* 建立通道描述符A */
    amdr_dma_xfer_desc_build(&g_desc,                          /* 通道描述符               */
                            (uint32_t)g_buf_src,               /* 源端数据缓冲区           */
                            (uint32_t)AMHW_USART0_TXDAT_ADDR,  /* USART0传输数据寄存器地址 */
                             256,                              /* 传输字节                 */
                             flags);                           /* 传输配置                 */

    amdr_dma_isr_connect(DMA_CHAN_USART0_TX_REQ, dma_isr, (void *)0);
                        
    /* 启动DMA传输，马上开始传输 */
    amdr_dma_chan_xfer_startup(DMA_CHAN_USART0_TX_REQ, &g_desc);
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
    
    /* USART初始化 */
    usart_init();
                                  
    /* 平台初始化 */
    amhw_plfm_dma_init();
    
    /* DMA 初始化 */ 
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);

    amhw_usart_poll_send(USART_CH, "DMA transfer start:\r\n", 
                            sizeof("DMA transfer start:\r\n") - 1);
    
    dma_tran_test();
    
    while (1) {
        if (g_trans_done) {
            am_led_toggle(LED0);
            am_mdelay(200);
        }
    }
}
/** [src_hw_uart_tx_dma] */

/* end of file */

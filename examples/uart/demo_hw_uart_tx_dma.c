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
 * \brief USARTͨ��DMA��ʽ�������ݣ�ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_0 ��������PC���ڵ�TXD;
 *   2. PIO0_1 ��������PC���ڵ�RXD��
 *    
 * - ʵ������
 *   1. �������"aAbBcCdD..."��
 *   2. DMA������ɺ�LED��˸��
 *
 * \note ��ʹ��DMA����ʱ��UART����ʹ��FIFO
 *
 * \par Դ����
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



/** \brief USARTͨ��*/
#define USART_CH            AMHW_USART0

/** \brief �����ʣ���32kmodeʱ���������Ϊ9600 */
#define USART_BAUDRATE     (115200)

uint8_t g_buf_src[256];          /**< \brief Դ�����ݻ�����       */

bool_t  g_trans_done;            /**< \brief ������ɱ�־         */

/**
 * \brief ��ƹ�Ҵ���ʱ���������ĵ�ַ��Ҫ��16�ֽڶ��롣        
 */
amhw_dma_xfer_desc_t g_desc;


/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� amdr_dma_isr_connect() �������ݡ�
 * \param[in] p_flg : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AMDR_DMA_INTA)��(#AMDR_DMA_INTB) �� (#AMDR_DMA_INTERR)��
 *
 * \return    �ޡ�
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;
    
    if (flag == AMDR_DMA_INTA) {
        
        /* ֹͣ����Stop transfer */
        amdr_dma_chan_stop(DMA_CHAN_USART0_TX_REQ);
        
        amhw_usart_poll_send(USART_CH, "\r\n", sizeof("\r\n") - 1);
        amhw_usart_poll_send(USART_CH, "DMA transfer done!\r\n", 
                                sizeof("DMA transfer done!\r\n") - 1);
        
        /* DMA������� */
        g_trans_done = TRUE;
    }
}

/**
 * \brief DMA����
 */
void dma_tran_test (void)
{
    int      i;
    uint32_t flags;

    /* DMAͨ������ */
    amdr_dma_chan_setup(DMA_CHAN_USART0_TX_REQ,         /* USART0����DMAͨ��            */
                        AMHW_DMA_CHAN_PERIPH_REQ_EN  |  /* ʹ����������                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF     |  /* ��ֹӲ������                 */
                        AMHW_DMA_CHAN_SINGLE_TRANS   |  /* ���δ���ģʽ                 */
                        AMHW_DMA_CHAN_PRIO_5);          /* ͨ�����ȼ���5                */

    for (i = 0; i < 256; i += 2) {
        g_buf_src[i]     = i / 2 % 26 + 'a';
        g_buf_src[i + 1] = i / 2 % 26 + 'A';
    }
    
    /* ��ʼDMA���� */
    amdr_dma_chan_start(DMA_CHAN_USART0_TX_REQ);        

    /* DMA��������*/
    flags = AMHW_DMA_XFER_CFG_VALID       |             /* ��ǰ������������Ч              */
            AMHW_DMA_XFER_NO_RELOAD       |             /* ��ֹ����ͨ��������              */
            AMHW_DMA_XFER_SWTRIG          |             /* �������                        */
            AMHW_DMA_XFER_NO_CLRTRIG      |             /* �����������־                  */
            AMHW_DMA_XFER_WIDTH_8BIT      |             /* �������ݿ�ȣ�8 bit             */
            AMHW_DMA_XFER_SRCINC_1X_WIDTH |             /* Դ�����ݵ�ַ��1�����ݿ�ȵ���   */
            AMHW_DMA_XFER_NO_DSTINC       |             /* Ŀ������ݵ�ַ������            */
            AMHW_DMA_XFER_SETINTA;                      /* ʹ���ж�A                       */

    
    /* ����ͨ��������A */
    amdr_dma_xfer_desc_build(&g_desc,                          /* ͨ��������               */
                            (uint32_t)g_buf_src,               /* Դ�����ݻ�����           */
                            (uint32_t)AMHW_USART0_TXDAT_ADDR,  /* USART0�������ݼĴ�����ַ */
                             256,                              /* �����ֽ�                 */
                             flags);                           /* ��������                 */

    amdr_dma_isr_connect(DMA_CHAN_USART0_TX_REQ, dma_isr, (void *)0);
                        
    /* ����DMA���䣬���Ͽ�ʼ���� */
    amdr_dma_chan_xfer_startup(DMA_CHAN_USART0_TX_REQ, &g_desc);
}

/**
 * \brief USART��ʼ��
 */
void usart_init (void)
{
    /* ʹ��USART0ʱ�ӣ�����λUSART0 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART0);
    amhw_syscon_periph_reset(AMHW_RESET_USART0);
    
    /* ��PIO0_0��������ΪUART0_RXD */
    am_gpio_pin_cfg(PIO0_0, PIO0_0_USART0_RXD | PIO0_0_PULLUP);
    
    /* ��PIO0_1��������ΪUART0_TXD */
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
 * \brief ���������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();
    
    /* USART��ʼ�� */
    usart_init();
                                  
    /* ƽ̨��ʼ�� */
    amhw_plfm_dma_init();
    
    /* DMA ��ʼ�� */ 
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

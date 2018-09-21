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
 *   2. PIO0_1 ��������PC���ڵ�RXD;
 *   3. ͨ��PCһ������MCU����16���ַ���
 *
 * - ʵ������
 *   1. ���ڴ�ӡ�����յ������ݣ�
 *   2. Ȼ�󴮿ڴ�ӡ����x tansfer done!��, 'x'��'A'��'B'��
 *
 * \note ��ʹ��DMA����ʱ��USART����ʹ��FIFO
 *
 * \par Դ����
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



/** \brief USARTͨ��*/
#define USART_CH            AMHW_USART0

/** \brief �����ʣ���32kmodeʱ���������Ϊ9600 */
#define USART_BAUDRATE     (115200)

/** \brief DMA ���������� */
__align(16) amhw_dma_xfer_desc_t g_desc[2];

uint8_t g_buf_dsta[16];          /**< \brief AĿ������ݻ����� */
uint8_t g_buf_dstb[16];          /**< \brief BĿ������ݻ����� */


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
        // �û��Զ���ִ�д��롣
    }
}

/**
 * \brief DMA���䣺ƹ��ģʽ��
 */
void dma_tran_test (void)
{
    int i;
    uint32_t flags1, flags2;

    /* DMAͨ������ */
    amdr_dma_chan_setup(DMA_CHAN_USART0_RX_REQ,         /* USART0����DMAͨ��            */
                        AMHW_DMA_CHAN_PERIPH_REQ_EN |   /* ʹ����������                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF    |   /* ��ֹӲ������                 */
                        AMHW_DMA_CHAN_SINGLE_TRANS  |   /* ���δ���ģʽ                 */
                        AMHW_DMA_CHAN_PRIO_5);          /* ͨ�����ȼ���5                */

    amdr_dma_chan_start(DMA_CHAN_USART0_RX_REQ);        /* ��ʼDMA����                  */

    for (i = 0; i < 16; i++) {
        g_buf_dsta[i] = 0;
        g_buf_dstb[i] = 0;
    }

    /* DMA�������� */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                /* ��ǰ������������Ч              */
             AMHW_DMA_XFER_RELOAD |                   /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                   /* �������                        */
             AMHW_DMA_XFER_NO_CLRTRIG |               /* �����������־                  */
             AMHW_DMA_XFER_WIDTH_8BIT |               /* �������ݿ�ȣ�8 bit             */
             AMHW_DMA_XFER_NO_SRCINC |                /* Դ�����ݵ�ַ������              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |          /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTA;                   /* ʹ���ж�A                       */

    /* DMA�������� */
    flags2 = AMHW_DMA_XFER_CFG_VALID |                /* ��ǰ������������Ч              */
             AMHW_DMA_XFER_RELOAD |                   /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                   /* �������                        */
             AMHW_DMA_XFER_NO_CLRTRIG |               /* �����������־                  */
             AMHW_DMA_XFER_WIDTH_8BIT |               /* �������ݿ�ȣ�8 bit             */
             AMHW_DMA_XFER_NO_SRCINC |                /* Դ�����ݵ�ַ������              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |          /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTB;                   /* ʹ���ж�B                       */

    /* ����ͨ��������A */
    amdr_dma_xfer_desc_build(&g_desc[0],                        /* A������������         */
                             (uint32_t)AMHW_USART0_RXDAT_ADDR,  /* Դ�����ݻ�����        */
                             (uint32_t)g_buf_dsta,              /* A��Ŀ��˻�������ַ   */
                              16,                               /* �����ֽ���            */
                              flags1);                          /* �������� */

    /* ����ͨ��������B */
    amdr_dma_xfer_desc_build(&g_desc[1],                        /* B������������         */
                             (uint32_t)AMHW_USART0_RXDAT_ADDR,  /* Դ�����ݻ�����        */
                             (uint32_t)g_buf_dstb,              /* B��Ŀ��˻�������ַ   */
                              16,                               /* �����ֽ���            */
                              flags2);                          /* ��������              */

    /* ����DMA�жϷ����� */
    amdr_dma_isr_connect(DMA_CHAN_USART0_RX_REQ, dma_isr, (void *)0);

    /* �������������� */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /* ����DMA���䣬���Ͽ�ʼ���� */
    amdr_dma_chan_xfer_startup(DMA_CHAN_USART0_RX_REQ, &g_desc[0]);
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

    /* ƽ̨��ʼ�� */
    amhw_plfm_dma_init();

    /* USART��ʼ�� */
    usart_init();

    /* DMA��ʼ�� */
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);

    /* ��ʼDMA���� */
    dma_tran_test();

    while (1) {
        ;
    }
}

/** [src_hw_uart_rx_dma] */

/* end of file */

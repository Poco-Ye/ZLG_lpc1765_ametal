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
 * \brief SPI�ӻ���������ͨ��DMA��������ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӿں�����Դ��Ӧ��SPI�ӿ�����������
 *   2. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. ���յ����ݣ�ͨ�����ڴ�ӡ������
 *
 * \par Դ����
 * \snippet demo_hw_spi_slave_dma.c src_hw_spi_slave_dma
 *
 * \internal
 * \par History
 * - 1.00 15-01-25  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_spi_slave_dma
 * \copydoc demo_hw_spi_slave_dma.c
 */ 
 
/** [src_hw_spi_slave_dma] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"



#define SPI_SLAVE      AMHW_SPI0 /**< \brief SPI�ӻ�������ͨ���� */


/** \brief reload descriptor map */
__align(16)  amhw_dma_xfer_desc_t g_desc[2];

uint16_t g_buf_src[16];           /**< \brief Դ���ݻ�����   */
uint16_t g_buf_dsta[8];           /**< \brief A ������������ */
uint16_t g_buf_dstb[8];           /**< \brief B ������������ */


uint8_t g_a_transfer_done;        /**< \brief A ������ɱ�־ */
uint8_t g_b_transfer_done;        /**< \brief B ������ɱ�־ */

/** 
 * \brief DMA �жϷ�����
 *
 * \param[in] p_arg : �жϷ�������ڲ���
 * \param[in] p_flg : DMA�жϱ�־������A�����жϣ�B�����жϣ������жϵȣ�
 *
 * \return    ��
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;
    
    if (flag == AMDR_DMA_INTA) {
        g_a_transfer_done = 1;
    
    } else if (flag == AMDR_DMA_INTB) {
        g_b_transfer_done = 1;
    
    } else if (flag == AMDR_DMA_INTERR) {
        
    }

    
}


/**
 * \brief DMAƹ��ģʽ������Ժ���.
 */
void dma_ping_pong_test (void)
{
    uint32_t flags1, flags2;
    
    /* 
     * DMAͨ������
     */
    amdr_dma_chan_setup(DMA_CHAN_SPI0_RX_REQ,           /* DMA ͨ��������     */
                        AMHW_DMA_CHAN_PERIPH_REQ_EN |   /* �������败������   */
                        AMHW_DMA_CHAN_HWTRIG_OFF |      /* ����Ӳ������       */
                        AMHW_DMA_CHAN_SINGLE_TRANS |    /* ��һ����           */
                        AMHW_DMA_CHAN_PRIO_6);          /* ����ͨ�����ȼ�Ϊ6  */

    amdr_dma_chan_start(DMA_CHAN_SPI0_RX_REQ);          /* DMA ͨ������  */
    
    /*
     * DMA��������1
     */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                  /* ��ǰͨ����������Ч              */
             AMHW_DMA_XFER_RELOAD |                     /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                     /* �������                        */
             AMHW_DMA_XFER_NO_CLRTRIG |                 /* �����������־                  */
             AMHW_DMA_XFER_WIDTH_16BIT |                /* �������ݿ�ȣ�16 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* Դ�����ݵ�ַ������              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTA;                     /* ʹ���ж� A                      */

    /*                                                  
     * DMA��������2                       
     */                                                 
    flags2 = AMHW_DMA_XFER_CFG_VALID |                  /* ��ǰͨ����������Ч              */
             AMHW_DMA_XFER_RELOAD |                     /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                     /* �������                        */
             AMHW_DMA_XFER_NO_CLRTRIG |                 /* �����������־                  */
             AMHW_DMA_XFER_WIDTH_16BIT |                /* �������ݿ�ȣ�16 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* Դ�����ݵ�ַ������              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTB;                     /* ʹ���ж� B                      */

    /*
     * ����ͨ��������A 
     */
    amdr_dma_xfer_desc_build(&g_desc[0],                     /* A������������               */
                             (uint32_t)AMHW_SPI0_RXDAT_ADDR, /* Դ�����ݵ�ַ                */
                             (uint32_t)g_buf_dsta,           /* A��Ŀ��˻�������ַ         */
                             16,                             /* �����ֽ���                  */
                             flags1);                        /* ��������1                   */

    /*
     * ����ͨ��������B 
     */
    amdr_dma_xfer_desc_build(&g_desc[1],                     /* B������������               */
                             (uint32_t)AMHW_SPI0_RXDAT_ADDR, /* Դ�����ݵ�ַ                */
                             (uint32_t)g_buf_dstb,           /* B��Ŀ��˻�������ַ         */
                             16,                             /* �����ֽ���                  */
                             flags2);                        /* ��������2                   */
    /*
     * ����DMA�жϴ�����
     */
    amdr_dma_isr_connect(DMA_CHAN_SPI0_RX_REQ,
                         dma_isr,
                         (void *)0);
                         


    
    /*
     * �������������� 
     */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /*
     * DMA��������
     */
    amdr_dma_chan_xfer_startup(DMA_CHAN_SPI0_RX_REQ, &g_desc[0]);

}


/**
 * \brief SPI�ӻ�����
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] len      : ����֡���ȣ���Χ1 - 16.
 *
 * \return  ��
 */
void spi_slv_start (amhw_spi_t *p_hw_spi,uint8_t len)
{
    p_hw_spi->txctl = AMHW_SPI_TXDATCTL_FSIZE(len);
}

/**
 * \brief SPI�ӻ���ʼ������
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \retval  AM_OK      : �������
 * \retval  -AM_EINVAL ��������Ч
 */
int spi_slv_init (amhw_spi_t *p_hw_spi)
{
    amhw_spi_disable(p_hw_spi);                /* ����SPI�����ò��� */
    
    /* SPI�ӻ���������  */
    p_hw_spi->cfg |= AMHW_SPI_CFG_SLAVE ; 

    amhw_spi_enable(p_hw_spi);                 /* ������ɣ�ʹ��SPI*/
    return AM_OK;
}


/**
 * \brief ������
 */
int main (void)
{
    uint8_t i ;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* SPI0��DMA���ƽ̨��ʼ�� */
    amhw_plfm_dma_init();
    amhw_plfm_spi0_init();
    /* DMA��������ʼ�� */ 
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);
    
    /* SPI�ӻ���ʼ������ */
    spi_slv_init(SPI_SLAVE);
    
    spi_slv_start(SPI_SLAVE, 16-1);
   
    dma_ping_pong_test();
    
    while (1) {
        
        /* A������ɱ�־λ��λ��ͨ�����ڽ����յ����ݴ�ӡ���� */
        if (g_a_transfer_done) {
            g_a_transfer_done = 0;
            for (i = 0; i < 8; i++){
                AM_DBG_INFO("A_buf %2dst is :%4X\r\n",i,g_buf_dsta[i]);
            }

        }
        
        /* A������ɱ�־λ��λ��ͨ�����ڽ����յ����ݴ�ӡ���� */
        if (g_b_transfer_done) {
            g_b_transfer_done = 0;
            for (i = 0; i < 8; i++){
                AM_DBG_INFO("B_buf %2dst is :%4X\r\n",i,g_buf_dstb[i]);
            }
        }
    }
    
}

/** [src_hw_spi_slave_dma] */

/* end of file */


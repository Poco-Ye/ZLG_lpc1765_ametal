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
 * \brief SPI�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӻ��ӿں������ӿڶ�Ӧ����������
 *   2. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. �ӻ������������ݣ���ͨ�����ڽ����յ������ݴ�ӡ������
 *   2. �ӻ��������ݵ���������ͨ�����ڽ����͵����ݴ�ӡ������
 *   3. �����������֮��LED0��200msʱ������˸��
 *
 * \par Դ����
 * \snippet demo_hw_spi_slave.c src_hw_spi_slave
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_spi_slave
 * \copydoc demo_hw_spi_slave.c
 */
 
/** [src_hw_spi_slave] */ 
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


#define SPI_SLAVE      AMHW_SPI0      /**< \brief SPI�ӻ�������ͨ���� */

#define SPI_M_EOT       0x1000        /**< \brief SPI������ǰtransfer����λ  */
#define SPI_M_CTRL_MASK 0xFF00        /**< \brief SPI����λ����              */
#define SPI_M_8_BPW     0x0007        /**< \brief SPI��������֡��СΪ8bytes  */
#define SPI_M_16_BPW    0x000F        /**< \brief SPI��������֡��СΪ16bytes */
#define SPI_M_BPW_MASK  0x00FF        /**< \brief SPI��������֡��С����      */


/** 
 * \brief SPI����ṹ�嶨��
 */
typedef struct spi_transfer {
    const void *p_txbuf;                  /**< \brief ָ�������ݻ����ָ��  */
    void       *p_rxbuf;                  /**< \brief ָ��������ݻ����ָ��  */
    uint32_t    nbytes;                   /**< \brief ���ݳ���   */
    uint16_t    flags;                    /**< \brief SPI������Ʊ�־λ */
} spi_transfer_t;

spi_transfer_t __g_spi0_transfer;         /* ����һ��SPI����ṹ��ʵ�� */

/**
 * \brief SPI����ṹ���������
 *
 * \param[in] p_trans : ָ��SPI����ṹ��
 * \param[in] p_txbuf : ָ�������ݻ����ָ��
 * \param[in] p_rxbuf : ָ��������ݻ����ָ��
 * \param[in] nbytes  : ��ǰ�������ݳ���   
 * \param[in] flags   : SPI������Ʊ�־λ
 *
 * \retval  AM_OK     : �������
 */
int spi_mktrans (spi_transfer_t *p_trans, 
                 const void     *p_txbuf,
                 void           *p_rxbuf,
                 uint32_t        nbytes,
                 uint16_t        flags)
                    
{
    if (p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->p_txbuf  = p_txbuf;
    p_trans->p_rxbuf  = p_rxbuf;
    p_trans->nbytes   = nbytes;
    p_trans->flags    = flags;

    return AM_OK;
}


/**
 * \brief SPI�ӻ�����
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] p_trans  : ָ��SPI������ṹ��ָ��
 *
 * \return  ��
 */
void spi_slv_start (amhw_spi_t *p_hw_spi, spi_transfer_t *p_trans)
{
    p_hw_spi->txctl = AMHW_SPI_TXDATCTL_FSIZE(p_trans->flags & SPI_M_BPW_MASK);
}
/**
 * \brief SPI�ӻ���������
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] p_trans  : ָ��SPI������ṹ��ָ��
 *
 * \return  AM_OK : SPI������� 
 */
int spi_slv_send (amhw_spi_t      *p_hw_spi, 
                  spi_transfer_t  *p_trans)
{
    uint32_t i = 0;
    
    spi_slv_start(p_hw_spi, p_trans);
    
    for (i = 0; i < p_trans->nbytes; i++) {

        while ( (p_hw_spi->stat & AMHW_SPI_STAT_TXRDY) == 0);

        if ((p_trans->flags & SPI_M_BPW_MASK) <= 8) {
            amhw_spi_txdat_write(p_hw_spi, ((uint8_t *)(p_trans->p_txbuf))[i]);
    
        } else {   
            amhw_spi_txdat_write(p_hw_spi, ((uint16_t *)(p_trans->p_txbuf))[i]);
        }
    }
    return AM_OK; 
}


/**
 * \brief SPI�ӻ���������
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] p_trans  : ָ��SPI������ṹ��ָ��
 *
 * \return  AM_OK : SPI������� 
 */
int spi_slv_recv (amhw_spi_t      *p_hw_spi, 
                  spi_transfer_t  *p_trans)
{
    uint32_t i = 0;
    
    spi_slv_start(p_hw_spi, p_trans);
    
    for (i = 0; i < p_trans->nbytes; i++) {
        while ( (p_hw_spi->stat & AMHW_SPI_STAT_RXRDY) == 0 );

        if ((p_trans->flags & SPI_M_BPW_MASK) <= 8) {
            ((uint8_t *)(p_trans->p_rxbuf))[i] = amhw_spi_rxdata_8bit_read(p_hw_spi); 
        
        } else {   
            ((uint16_t *)(p_trans->p_rxbuf))[i] = amhw_spi_rxdata_16bit_read(p_hw_spi);
        }
    }
    return 0; 
}

/**
 * \brief SPI�ӻ���ʼ������
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \retval  AM_OK      : �������
 * \retval  -AM_EINVAL ��������Ч
 */
int spi_slv_init (amhw_spi_t *p_hw_spi)
{
    amhw_spi_disable(p_hw_spi);                                  /* ����SPI�����ò��� */
    
    /* SPI�ӻ���������  */
    p_hw_spi->cfg |= AMHW_SPI_CFG_SLAVE ; 

    amhw_spi_enable(p_hw_spi);                                   /* ������ɣ�ʹ��SPI*/
    return AM_OK;
}

/**
 * \brief ������
 */
int main (void)
{
    spi_transfer_t *p_trans = &__g_spi0_transfer;
    
    uint8_t spi_slv_txbuf[32] = {0};
    uint8_t spi_slv_rxbuf[32] = {0};
    uint8_t length =16;
    uint8_t i;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* SPI0 ƽ̨��س�ʼ�� */
    amhw_plfm_spi0_init();
  
    /* SPI �ӻ���ʼ�� */
    spi_slv_init(SPI_SLAVE);
    
    for (i = 0; i < length; i++) {
        spi_slv_txbuf[i] = 2*i; 
    }
    
    /* �ӻ������������͵����� */
    spi_mktrans(p_trans,  NULL, (uint8_t *)&spi_slv_rxbuf, length, (SPI_M_EOT | SPI_M_8_BPW));
    spi_slv_recv(SPI_SLAVE, p_trans);               
    printf("\r\n--Slave receive Data:\r\n");
    for (i = 0; i<length; i++) {
        printf("The %2dst data is %2d \r\n", i, spi_slv_rxbuf[i]);
       
    }               
    
    /* �ӻ��������ݵ����� */
    spi_mktrans(p_trans, (uint8_t *)&spi_slv_txbuf, NULL, length, (SPI_M_EOT | SPI_M_8_BPW));
    spi_slv_send(SPI_SLAVE, p_trans);               
    
    printf("\r\n--Slave transmit Data:\r\n");
    for (i = 0; i < length; i++) {
        printf("The %2dst data is %2d \r\n", i, spi_slv_txbuf[i]);
    }
    
    while (1) {
        
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_hw_spi_slave] */ 
  

/* end of file */


/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief SPI Ӳ�������ӿ�
 * 
 * 1. ֧��1-16bitsֱ�Ӵ��䣬�ϴ������֡��ͨ���������֮����д��䣻
 * 2. ֧�������ʹӻ����䣻
 * 3. ���ݿ��Ա����䵽�ӻ�������������������ݡ�������ܿ����ڽ���SPI�ڴ棻 
 * 4. ������Ϣ��ѡ���Եĺ�����һͬд��. �ù���Ӧ�ù㷺, �������ⳤ������֡��
 * 5. �ߴ�4���ӻ�����/���ѡ��˿ڣ��������ü��ԣ��û���������ã�
 * 6. ֧��DMA����: SPI���պͷ������ݿ�ͨ��ϵͳDMA���������д��䡣
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_SPI_H
#define __AMHW_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"

/**
 * \addtogroup amhw_if_spi
 * \copydoc amhw_spi.h
 * @{
 */
 
    
/**
 * \brief SPI�Ĵ�����ṹ��
 */
typedef struct amhw_spi {
    __IO uint32_t  cfg;         /**< \brief SPI ���üĴ���     */
    __IO uint32_t  dly;         /**< \brief SPI ��ʱ�������üĴ��� */
    __IO uint32_t  stat;        /**< \brief SPI ״̬�Ĵ���     */
    __IO uint32_t  intenset;    /**< \brief SPI �ж�ʹ�ܼĴ��� */
    __O  uint32_t  intenclr;    /**< \brief SPI �жϽ��ܼĴ��� */
    __I  uint32_t  rxdat;       /**< \brief SPI �������ݼĴ��� */
    __IO uint32_t  txdatctl;    /**< \brief SPI �������ݺʹ�����ƼĴ��� */
    __IO uint32_t  txdat;       /**< \brief SPI �������ݼĴ��� */
    __IO uint32_t  txctl;       /**< \brief SPI ������ƼĴ��� */
    __IO uint32_t  div;         /**< \brief SPI ʱ�ӷ�Ƶ�Ĵ��� */
    __I  uint32_t  intstat;     /**< \brief SPI �ж�״̬�Ĵ��� */
} amhw_spi_t;

/**
 * \name DMA�ɲ�����SPI���Ƶ������ַ
 * @{
 */

/** \brief SPI0 �������ݵ�ַ */
#define AMHW_SPI0_RXDAT_ADDR  (&(AMHW_SPI0->rxdat)) 

/** \brief SPI0 �������ݵ�ַ */
#define AMHW_SPI0_TXDAT_ADDR  (&(AMHW_SPI0->txdat)) 

/** \brief SPI1 �������ݵ�ַ  */
#define AMHW_SPI1_RXDAT_ADDR  (&(AMHW_SPI1->rxdat)) 

/** \brief SPI1 �������ݵ�ַ */
#define AMHW_SPI1_TXDAT_ADDR  (&(AMHW_SPI1->txdat)) 

/** @} */


/**
 * \name SPI �ж�ʹ��״̬λ����
 * @{
 */
 
/** \brief SPI ���վ����ж�ʹ�� */
#define AMHW_SPI_INTENSET_RXRDY           (1UL << 0)  

/** \brief SPI ���;����ж�ʹ�� */ 
#define AMHW_SPI_INTENSET_TXRDY           (1UL << 1)   

/** \brief SPI ��������ж�ʹ�� */
#define AMHW_SPI_INTENSET_RXOVERRUN       (1UL << 2)   

/** \brief SPI �������磨����Ϊ�գ��ж�ʹ�� */
#define AMHW_SPI_INTENSET_TXUNDERRUN      (1UL << 3) 

/** \brief �ӻ�Ƭѡ��Ч�ж�ʹ�� */
#define AMHW_SPI_INTENSET_SELNASSERT      (1UL << 4) 

/** \brief �ӻ�Ƭѡδ��Ч�ж�ʹ�� */
#define AMHW_SPI_INTENSET_SELNDEASSERT    (1UL << 5)  

/** \brief ���������ж�ʹ�� */ 
#define AMHW_SPI_INTENSET_MSTIDLE         (1UL << 8)   

/** @} */

/**
 * \name SPI �жϽ���״̬λ����
 * @{
 */
 
/** \brief SPI ���վ����жϽ��� */
#define AMHW_SPI_INTENCLR_RXRDY           (1UL << 0) 

/** \brief SPI ���;����жϽ��� */  
#define AMHW_SPI_INTENCLR_TXRDY           (1UL << 1) 

/** \brief SPI ��������жϽ��� */
#define AMHW_SPI_INTENCLR_RXOVERRUN       (1UL << 2)

/** \brief SPI �������磨����Ϊ�գ��жϽ��� */  
#define AMHW_SPI_INTENCLR_TXUNDERRUN      (1UL << 3)   

/** \brief �ӻ�Ƭѡ��Ч�жϽ��� */
#define AMHW_SPI_INTENCLR_SELNASSERT      (1UL << 4)  

/** \brief �ӻ�Ƭѡδ��Ч�жϽ��� */
#define AMHW_SPI_INTENCLR_SELNDEASSERT    (1UL << 5) 

/** \brief ���������жϽ��� */ 
#define AMHW_SPI_INTENCLR_MSTIDLE         (1UL << 8)   

/** @} */

/**
 * \name SPI ״̬λ����
 * @{
 */
 
/** \brief ���վ���״̬ */
#define AMHW_SPI_STAT_RXRDY               (1UL << 0) 
 
/** \brief ���;���״̬ */ 
#define AMHW_SPI_STAT_TXRDY               (1UL << 1)

/** \brief �������״̬ */   
#define AMHW_SPI_STAT_RXOVERRUN           (1UL << 2)   

/** \brief ��������״̬ */
#define AMHW_SPI_STAT_TXUNDERRUN          (1UL << 3)  

/** \brief �ӻ�ѡ����Ч״̬ */ 
#define AMHW_SPI_STAT_SELNASSERT          (1UL << 4) 

/** \brief �ӻ�ѡ����Ч״̬  */  
#define AMHW_SPI_STAT_SELNDEASSERT        (1UL << 5)   
                                          
#define AMHW_SPI_STAT_CLKSTALL            (1UL << 6)   /**< \brief ʧ��״̬ */
#define AMHW_SPI_STAT_EOF                 (1UL << 7)   /**< \brief ��������״̬ */
#define AMHW_SPI_STAT_IDLE                (1UL << 8)   /**< \brief ��������״̬ */

/** @} */


/**
 * \name SPI ģʽ����
 * @{
 */
 
#define AMHW_SPI_CFG_ENABLE               (1UL << 0)   /**< \brief SPI ������ʹ�� */        
#define AMHW_SPI_CFG_MASTER               (1UL << 2)   /**< \brief SPI ����ģʽʹ�� */        
#define AMHW_SPI_CFG_SLAVE                (0UL << 2)   /**< \brief SPI �ӻ�ģʽʹ�� */        
#define AMHW_SPI_CFG_LSBF                 (1UL << 3)   /**< \brief ���ֽ��ȷ���ģʽʹ�� */        
#define AMHW_SPI_CFG_LOOPBACK             (1UL << 7)   /**< \brief ����ģʽʹ�ܣ��������� */   
     
/** @} */

/**
 * \name SPI����λ����
 * @{
 */

#define AMHW_SPI_TXDATCTL_MASK       (0xF7F0000)          /**< \brief ����λ����      */
#define AMHW_SPI_TXDATCTL_SSELN(s)   ((s) << 16)          /**< \brief ѡ��ӻ�����λ   */
#define AMHW_SPI_TXDATCTL_EOT        (1UL << 20)          /**< \brief �����������λ   */
#define AMHW_SPI_TXDATCTL_EOF        (1UL << 21)          /**< \brief ��������֡����λ */
#define AMHW_SPI_TXDATCTL_RX_IGNORE  (1UL << 22)          /**< \brief ���Խ��տ���λ   */
#define AMHW_SPI_TXDATCTL_FSIZE(s)   (((s) & 0xFF) << 24) /**< \brief ����֡���ȿ���λ */ 

/** @} */

/**
 * \brief SPI �ӻ�����/����˿ڶ���
 */
typedef enum amhw_slave {
    AMHW_SPI_SLAVE0 = ((~(1 << 0)) & 0xf),             /**< \brief SSEL0������Ч */
    AMHW_SPI_SLAVE1 = ((~(1 << 1)) & 0xf),             /**< \brief SSEL1������Ч */
    AMHW_SPI_SLAVE2 = ((~(1 << 2)) & 0xf),             /**< \brief SSEL2������Ч */
    AMHW_SPI_SLAVE3 = ((~(1 << 3)) & 0xf)              /**< \brief SSEL3������Ч */
} amhw_slave_t;

/**
 * \name SPI ����ģʽ
 * @{
 */ 

/** \brief SCK ��λ״̬(LOW)  SCK ���ݸı�������(falling)  SCK ���ݲ���������(rising) */
#define AMHW_SPI_MODE_0     ((0 << 4) |(0 << 5))  
 
/** \brief SCK ��λ״̬(LOW)  SCK ���ݸı�������(rising)  SCK ���ݲ���������(falling) */
#define AMHW_SPI_MODE_1     ((1 << 4) |(0 << 5))

/** \brief SCK ��λ״̬(HIGH) SCK ���ݸı�������(rising)  SCK ���ݲ���������(falling) */
#define AMHW_SPI_MODE_2     ((0 << 4) |(1 << 5)) 
     
/** \brief SCK ��λ״̬(HIGH) SCK ���ݸı�������(falling) SCK ���ݲ���������(rising) */
#define AMHW_SPI_MODE_3     ((1 << 4) |(1 << 5))

/**
 * @} 
 */
 
 
/**
 * \name ��ʱʱ�����λ����
 * @{
 */
 
/** \brief ��SPIʱ������SSEL��Ч�ʹ��俪ʼ֮�����ʱ */
#define AMHW_SPI_PREDELAY(d)     ((d) << 0)  

/** \brief ��SPIʱ�����ϴ��������SSEL��Ч֮�����ʱ */
#define AMHW_SPI_POSTDELAY(d)    ((d) << 4)   

/** \brief ��SPIʱ��������������֮֡�����ʱ */
#define AMHW_SPI_FRAMEDELAY(d)   ((d) << 8) 

/** \brief ��SPIʱ��������������֮�����ʱ */
#define AMHW_SPI_INTERDELAY(d)   ((d) << 12) 

/** @}  */


/**
 * \brief SPI ��ʱ�����ṹ��
 */
typedef struct amhw_spi_mst_delay {
    uint8_t predelay;         /**< \brief SSEL��Ч�ʹ��俪ʼ֮�����ʱ */
    uint8_t postdelay;        /**< \brief ���������SSEL��Ч֮�����ʱ */                         
    uint8_t framedelay;       /**< \brief ��������֮֡�����ʱ */                       
    uint8_t transferdelay;    /**< \brief ��������֮�����ʱ */
} amhw_spi_mst_delay_t;

/**
 * \brief SPI ����������
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_spi_disable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->cfg &= ~AMHW_SPI_CFG_ENABLE;
} 

/**
 * \brief SPI ������ʹ��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_spi_enable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->cfg |= AMHW_SPI_CFG_ENABLE;
} 

/**
 * \brief SPI ������ʱ��������
 *
 * \param[in] p_hw_spi    : ָ��SPI�Ĵ������ָ��
 * \param[in] p_spi_delay : ָ��SPI��ʱ�����ṹ��
 *
 * \return    ��
 */
am_static_inline 
void amhw_spi_master_dly (amhw_spi_t           *p_hw_spi,
                          amhw_spi_mst_delay_t *p_spi_delay)
{
    p_hw_spi->dly = (AMHW_SPI_PREDELAY  (p_spi_delay->predelay)   |
                     AMHW_SPI_POSTDELAY (p_spi_delay->postdelay)  |
                     AMHW_SPI_FRAMEDELAY(p_spi_delay->framedelay) |
                     AMHW_SPI_INTERDELAY(p_spi_delay->transferdelay));
} 

/**
 * \brief SPI �ж�ʹ��
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : AM_SPI_INTENSET_* ��ֵ����
 *                       AM_SPI_INTENSET_*��� ��OR��ֵ (#AMHW_SPI_INTENSET_RXRDY)
 *
 * \return  None
 */

am_static_inline 
void amhw_spi_int_enable (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    p_hw_spi->intenset = flags;
}

/**
 * \brief SPI �жϽ���
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : AM_SPI_INTENCLR_* ��ֵ����
 *                       AM_SPI_INTENCLR_*��� ��OR��ֵ (#AMHW_SPI_INTENCLR_RXRDY)
 *
 * \return  ��
 */
am_static_inline 
void amhw_spi_int_disable (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    p_hw_spi->intenclr = flags;
}

/**
 * \brief SPI ����λ�趨 
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : AMHW_SPI_TXDATCTL_* ��ֵ����
 *                       AMHW_SPI_TXDATCTL_*��� ��OR��ֵ(#AMHW_SPI_TXDATCTL_EOT)
 * \return  ��
 */
am_static_inline 
void amhw_spi_txctl_set (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    uint32_t reg;

    reg             = (p_hw_spi->txctl) & AMHW_SPI_TXDATCTL_MASK;
    p_hw_spi->txctl = reg | flags;
}

/**
 * \brief SPI ����λ���
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : AMHW_SPI_TXDATCTL_* ��ֵ����
 *                       AMHW_SPI_TXDATCTL_*��� ��OR��ֵ(#AMHW_SPI_TXDATCTL_EOT)
 * \return  ��
 */
am_static_inline 
void amhw_spi_txctl_clear (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    uint32_t reg;

    reg = (p_hw_spi->txctl) & AMHW_SPI_TXDATCTL_MASK;
    p_hw_spi->txctl = reg & ~flags;
}

/**
 * \brief ����趨��״̬λ
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] flags    : AMHW_SPI_STAT_* ��ֵ����
 *                       AMHW_SPI_STAT_*��� ��OR��ֵ(#AMHW_SPI_STAT_RXRDY)
 * \return  None
 */
am_static_inline 
void amhw_spi_stat_clear (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    p_hw_spi->stat = flags;
}

/**
 * \brief ��ȡSPI��״̬
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  SPI״̬
 */
am_static_inline 
uint32_t amhw_spi_stat_read (amhw_spi_t *p_hw_spi)
{
    return p_hw_spi->stat;
}

/**
 * \brief ��ȡSPI�ж�״̬λ
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return    �ж�״̬�Ĵ�����ֵ
 */
am_static_inline 
uint32_t amhw_spi_intstat_read (amhw_spi_t *p_hw_spi)
{
    return p_hw_spi->intstat;
}

/**
 * \brief ��ȡSPI�������ݼĴ�����ֵ��8-bits��
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return    �������ݼĴ�����ֵ(��8λ)
 */
am_static_inline 
uint8_t amhw_spi_rxdata_8bit_read (amhw_spi_t *p_hw_spi)
{
    return (p_hw_spi->rxdat & 0xFF);
}

/**
 * \brief ��ȡSPI�������ݼĴ�����ֵ (16bits)
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return    �������ݼĴ�����ֵ
 */
am_static_inline 
uint16_t amhw_spi_rxdata_16bit_read (amhw_spi_t *p_hw_spi)
{
    return (p_hw_spi->rxdat & 0xFFFF);
}

/**
 * \brief д���ݵ��������ݼĴ���
 *
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \param[in] data     : Ҫ���͵�����
 *
 * \return  ��
 */
am_static_inline 
void amhw_spi_txdat_write (amhw_spi_t *p_hw_spi, uint16_t data)
{
    p_hw_spi->txdat = (uint32_t)data;
}

/**
 * \brief SPI������Խ�������
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��
 */
am_static_inline 
void amhw_spi_ignore_recv_enable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) | 
                      AMHW_SPI_TXDATCTL_RX_IGNORE;
}

/**
 * \brief SPI���䲻���Խ�������
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��
 */
am_static_inline 
void amhw_spi_ignore_recv_disable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) & 
                      (~(AMHW_SPI_TXDATCTL_RX_IGNORE));
}

/**
 * \brief SPI ��������,SSEL����Ϊ��Ч״̬
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��
 */
am_static_inline 
void amhw_spi_end_trans_enable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) | 
                      AMHW_SPI_TXDATCTL_EOT;
}

/**
 * \brief SPI �������䣬������SSELΪ��Ч״̬
 * \param[in] p_hw_spi : ָ��SPI�Ĵ������ָ��
 * \return  ��
 */
am_static_inline 
void amhw_spi_end_trans_disable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) & 
                      (~(AMHW_SPI_TXDATCTL_EOT));
}

/** 
 * @} amhw_if_spi
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SPI_H */

/*end of file */

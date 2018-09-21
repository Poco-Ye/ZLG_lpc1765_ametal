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
 * \brief ���������FIFOӲ�������ӿ�
 *
 * 1. ���еĴ��ں�SPIִ�з��ͺͽ�����һ���豸��,
 *    ֧���������DMA��ÿ��������н��շ��Ͳ�����
 * 2. FIFO�ṩ�˸��Ӷ�ʱ���ܣ�����������DMAʱ������չ��
 * 3. ÿ�������ṩ�˶����Ļ���ռ䣬�û���ͨ������������з��䣬 
 *    ������16����FIFO��ں�16������FIFO��ڣ�SPI��8������FIFO��ں�8������FIFO��ڣ�
 * 4. �ڽϵ��������ϵͳFIFO����ΪAPB���裬������AHBʱ������������CPU��DMA�������ݣ�
 *    ����ʧ������£��������ʴ�С����������ʱ�Ӷ������У�
 * 5. ÿ������Ľ��պͷ���FIFO��������ͨ�����������ֵ����Χ1��FIFOΪ������ֵ��
 * 6. ÿ������Ľ��պͷ���FIFO�ṩ��FIFO�����������Χ0-FIFO������ֵ��
 * 7. ����������պͷ���������Ч��ϵͳFIFO�ṩ״̬��־�������ڲ����жϻ��߷����źŸ�ϵͳDMA��
 * 8. ���ڵõ�����һ��ʱ���δ�ﵽFIFO����ֵ��ϵͳFIFO�ṩ�˳�ʱ�����ܡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_FIFO_H
#define __AMHW_FIFO_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_fifo
 * \copydoc amhw_fifo.h
 * @{
 */


#define  AMHW_FIFO_USART_MAX     (0x04)          /**< \brief ���ڵ������ */
#define  AMHW_FIFO_SPI_MAX       (0x02)          /**< \brief SPI�������  */

/**
 * \brief FIFO����Ĺ����Ĵ�����ṹ��
 */
typedef struct amhw_fifo_comm {
    __I  uint32_t  reserved[64];       /**< \brief ����                   */
    __IO uint32_t  fifoctlusart;       /**< \brief ����FIFO���ƼĴ���     */
    __O  uint32_t  fifoupdateusart;    /**< \brief ����FIFO��С���¼Ĵ��� */
    __I  uint32_t  reserved1[2];       /**< \brief ����                   */

    /** \brief ����FIFO�����üĴ��� */
    __IO uint32_t  fifocfgusart[AMHW_FIFO_USART_MAX];

    __I  uint32_t  reserved2[56];      /**< \brief ����                     */
    __IO uint32_t  fifoctlspi;         /**< \brief SPI��FIFO���ƼĴ���      */
    __O  uint32_t  fifoupdatespi;      /**< \brief SPI��FIFO��С���¼Ĵ���  */
    __I  uint32_t  reserved3[2];       /**< \brief ����                     */

    /** \brief SPI��FIFO�����üĴ��� */
    __IO uint32_t  fifocfgspi[AMHW_FIFO_SPI_MAX];

    __I  uint32_t  reserved4[890];     /**< \brief ����                     */
}amhw_fifo_comm_t;

/**
 * \brief ������ص�FIFO�Ĵ����ṹ��
 */
typedef struct amhw_fifo_usart {
    __IO uint32_t  cfg;                /**< \brief USART ���üĴ��� */
    __IO uint32_t  stat;               /**< \brief USART ״̬�Ĵ��� */
    __I  uint32_t  intstat;            /**< \brief USART �ж�״̬�Ĵ���         */
    __IO uint32_t  ctlset;             /**< \brief USART ��λ����ж�λ�Ĵ���   */
    __O  uint32_t  ctlclr;             /**< \brief USART �������ж�λ�Ĵ���   */
    __I  uint32_t  rxdat;              /**< \brief USART �������ݼĴ���         */
    __I  uint32_t  rxdatstat;          /**< \brief USART �������ݼ���״̬�Ĵ��� */
    __O  uint32_t  txdat;              /**< \brief USART �������ݼĴ���         */
    __I  uint32_t  reserved5[56];      /**< \brief ����             */
}amhw_fifo_usart_t;

/**
 * \brief SPI��ص�FIFO�Ĵ����ṹ��
 */
typedef struct amhw_fifo_spi {
    __IO uint32_t  cfg;                /**< \brief SPI ���üĴ��� */
    __IO uint32_t  stat;               /**< \brief SPI ״̬�Ĵ��� */
    __I  uint32_t  intstat;            /**< \brief SPI �ж�״̬�Ĵ���         */
    __IO uint32_t  ctlset;             /**< \brief SPI ��λ����ж�λ�Ĵ���   */
    __O  uint32_t  ctlclr;             /**< \brief SPI �������ж�λ�Ĵ���   */
    __I  uint32_t  rxdat;              /**< \brief SPI �������ݼĴ���         */
    __O  uint32_t  txdat;              /**< \brief SPI �������ݼĴ���         */
    __I  uint32_t  reserved9[57];      /**< \brief ����           */
}amhw_fifo_spi_t;

/**
 * \brief FIFO�Ĵ�����ṹ��
 */
typedef struct amhw_fifo {
    
    /** \brief FIFO����Ĺ����Ĵ�����ṹ�� */  
    amhw_fifo_comm_t  common;
    
    /** \brief ������ص�FIFO�Ĵ����ṹ�� */
    amhw_fifo_usart_t usart[AMHW_FIFO_USART_MAX]; 
    
    /** \brief ���� */
    __I  uint32_t     reserved[768];
    
    /** \brief SPI��ص�FIFO�Ĵ����ṹ�� */
    amhw_fifo_spi_t   spi[AMHW_FIFO_SPI_MAX];
} amhw_fifo_t;

/**
 * \name FIFO״̬λ����
 * @{
 */
#define AMHW_FIFO_STAT_RXTH       (1 << 0)   /**< \brief �ﵽ����FIFO��ֵ */
#define AMHW_FIFO_STAT_TXTH       (1 << 1)   /**< \brief �ﵽ����FIFO��ֵ */
#define AMHW_FIFO_STAT_RXTIMEOUT  (1 << 4)   /**< \brief ����FIFO��ʱ     */
#define AMHW_FIFO_STAT_BUSERR     (1 << 7)   /**< \brief ���ߴ���         */
#define AMHW_FIFO_STAT_RXEMPTY    (1 << 8)   /**< \brief ����FIFOΪ�� */
#define AMHW_FIFO_STAT_TXEMPTY    (1 << 9)   /**< \brief ����FIFOΪ�� */

/** @} */

/**
 * \brief ����FIFO�Ŀ���λ���ж϶���
 * @{
 */

#define AMHW_FIFO_INT_RXTH       (1 << 0)  /**< \brief ����FIFO�ﵽ��ֵ�ж� */
#define AMHW_FIFO_INT_TXTH       (1 << 1)  /**< \brief ����FIFO�ﵽ��ֵ�ж� */
#define AMHW_FIFO_INT_RXTIMEOUT  (1 << 4)  /**< \brief ����FIFO��ʱ�ж�     */

#define AMHW_FIFO_CTRL_RXFLUSH   (1 << 8)  /**< \brief ����FIFO��� */
#define AMHW_FIFO_CTRL_TXFLUSH   (1 << 9)  /**< \brief ����FIFO��� */

/** @} */


/**
 * \name FIFO�ж��¼�����
 * @{
 */
#define AMHW_FIFO_EVENT_RX_TH         0x01  /**< \brief ��������FIFO�ﵽ��ֵ�ж��¼�  */
#define AMHW_FIFO_EVENT_RX_EMPTY      0x02  /**< \brief ��������FIFOΪ���¼� */
#define AMHW_FIFO_EVENT_TX_TH         0x04  /**< \brief ��������FIFO�ﵽ��ֵ�ж��¼�  */
#define AMHW_FIFO_EVENT_TX_EMPTY      0x08  /**< \brief ��������FIFOΪ���¼� */
#define AMHW_FIFO_EVENT_BUS_ERROR     0x10  /**< \brief �������ߴ����¼�     */
/** @} */

/**
 * \brief ����FIFO��ͨ���Ŷ���
 */
typedef enum amhw_fifo_usart_ch {
    AMHW_FIFO_USART0 = 0,          /**< \brief ����FIFOͨ��0 */
    AMHW_FIFO_USART1,              /**< \brief ����FIFOͨ��1 */
    AMHW_FIFO_USART2,              /**< \brief ����FIFOͨ��2 */
    AMHW_FIFO_USART3,              /**< \brief ����FIFOͨ��3 */
} amhw_fifo_usart_ch_t;

/**
 * \brief FIFO�������Ͷ���
 */
typedef enum amhw_fifo_periph {
    AMHW_FIFO_PERIPH_USART = 0,               /**< \brief ����FIFO */
    AMHW_FIFO_PERIPH_SPI                      /**< \brief SPI FIFO */
} amhw_fifo_periph_t;

/**
 * \brief FIFO����
 */
typedef enum amhw_fifo_dir {
    AMHW_FIFO_TX = 0,                         /**< \brief FIFO ���� */
    AMHW_FIFO_RX                              /**< \brief FIFO ���� */
} amhw_fifo_dir_t;

/**
 * \brief ����FIFO��С�趨�ṹ��
 */
typedef struct amhw_fifo_size {
    uint16_t fifo_rxsize[4]; /**< \brief ����FIFO��С, 0-3 ��Ӧ����0-3,  0-1 ��ӦSPI(0-1) */
    uint16_t fifo_txsize[4]; /**< \brief ����FIFO��С, 0-3 ��Ӧ����0-3,  0-1 ��ӦSPI(0-1) */
} amhw_fifo_size_t;

/**
 * \brief ��ȡFIFO���µĿռ��С
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] periph_id : ����id����
 * \param[in] dir       : FIFO�����ķ���
 *
 * \return  ��Ӧ�����FIFO���µĿռ�
 */
uint32_t amhw_fifo_space_get(amhw_fifo_t        *p_hw_fifo,
                             amhw_fifo_periph_t  periph_id,
                             amhw_fifo_dir_t     dir);

/**
 * \brief ��ͣһ�������FIFO
 *
 * \param[in] p_hw_fifo : 
 * \param[in] periph_id : 
 * \param[in] dir       : 
 *
 * \return    ��
 */
void amhw_fifo_pause(amhw_fifo_t         *p_hw_fifo,
                     amhw_fifo_periph_t   periph_id,
                     amhw_fifo_dir_t      dir);

/**
 * \brief ��������һ�������FIFO
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] periph_id : ����id����
 * \param[in] dir       : FIFO�����ķ���
 *
 * \return    ��
 */
void amhw_fifo_restart(amhw_fifo_t        *p_hw_fifo,
                       amhw_fifo_periph_t  periph_id,
                       amhw_fifo_dir_t     dir);

/**
 * \brief ��ȡ����FIFO�Ĵ�С 
 *
 * \param[in]  p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in]  periph_id : ����id����
 * \param[out] p_size    : ָ������FIFO��С�趨�ṹ���ָ��
 *
 * \retval  AM_OK   : ��ȡ���
 */
int amhw_fifo_size_read(amhw_fifo_t        *p_hw_fifo,
                        amhw_fifo_periph_t  periph_id,
                        amhw_fifo_size_t   *p_size);

/**
 * \brief ��������FIFO��С
 *
 * \param[in]  p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in]  periph_id : ����id����
 * \param[out] p_size    : ָ������FIFO��С�趨�ṹ���ָ��
 *
 * \retval  AM_OK      : ���óɹ�
 * \retval -AM_EINVAL  : ������Ч
 *
 * \note ����һ�θú�����������һ���������е�FIFO��С,
 *       ����amhw_fifo_restart()֮��ſɵ��øú���
 
*/
int amhw_fifo_size_cfg(amhw_fifo_t        *p_hw_fifo,
                       amhw_fifo_periph_t  periph_id,
                       amhw_fifo_size_t   *p_size);

/**
 * \brief FIFO�������ö���
 * @{
 */

/**
 * \brief ��д�����ݽ��뵽����FIFO����Ӧ�����費��λ������ĳ�ʱ
 */
#define AMHW_FIFO_CFG_TIMEOUTCONTONWRITE   (1 << 4)

/**
 * \brief ������FIFOΪ�գ���Ӧ�����費��λ������ĳ�ʱ
 */
#define AMHW_FIFO_CFG_TIMEOUTCONTONEMPTY   (1 << 5)

/** @} */

/**
 * \brief ����������Ϣ�ṹ��
 */
typedef struct amhw_fifo_cfg {
    uint32_t  flags;         /**< \brief AMHW_FIFO_CFG_*�ĺ�ֵ���߶��
                                   AMHW_FIFO_CFG_*��Ļ�or��ֵ(#AMHW_FIFO_CFG_TIMEOUTCONTONWRITE) */
    uint8_t   timeout_base;  /**< \brief 0 ~ 15,��ʱ�Ļ�ֵ   */
    uint8_t   timeout_value; /**< \brief 2 ~ 15,��ʱ�����ֵ */
    uint32_t  rx_threshold;  /**< \brief ����FIFO��ֵ        */
    uint32_t  tx_threshold;  /**< \brief ����FIFO��ֵ        */
} amhw_fifo_cfg_t;

/**
 * \brief  ����FIFO�����ú���
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] p_cfg     : ָ��������Ϣ�ṹ���ָ��
 *
 * \retval  AM_OK      : �������
 * \retval -AM_EINVAL  : ������Ч
 */
int amhw_fifo_usart_cfg(amhw_fifo_t          *p_hw_fifo,
                        amhw_fifo_usart_ch_t  usart_ch,
                        amhw_fifo_cfg_t      *p_cfg);

/**
 * \brief ��ȡ����FIFO��״̬
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 *
 * \return  AMHW_FIFO_STAT_*�ĺ�ֵ���߶��AMHW_FIFO_STAT_*��Ļ�or��ֵ(#AMHW_FIFO_STAT_RXTH)
 */
am_static_inline
uint32_t amhw_fifo_usart_stat_get (amhw_fifo_t          *p_hw_fifo,
                                   amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].stat);
}

/**
 * \brief ��ȡ���ڽ���FIFO�������
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��   
 * \param[in] usart_ch  : ����ͨ����               
 *
 * \return ���ڿ��Խ���FIFO�������. 0-FIFOΪ��
 */
am_static_inline
uint32_t amhw_fifo_usart_rxcount_get (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].stat >> 16) & 0xFF;
}

/**
 * \brief ��ȡ���ڷ���FIFO����Ч����
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ�� 
 * \param[in] usart_ch  : ����ͨ���� 
 *
 * \return ���ڿ��Է���FIFO�������. 0 = FIFOΪ��.
 */
am_static_inline
uint32_t amhw_fifo_usart_txcount_get (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].stat >> 24) & 0xFF;
}

/**
 * \brief ��ȡ�����ж�״̬
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 *
 * \return  AMHW_FIFO_INT_*�ĺ�ֵ���߶��AMHW_FIFO_INT_*��Ļ�or��ֵ(#AMHW_FIFO_INT_RXTH)
 */
am_static_inline
uint32_t amhw_fifo_usart_intstat_get (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].intstat);
}

/**
 * \brief �������FIFO״̬
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] clr_bits  : AMHW_FIFO_STAT_*�ĺ�ֵ���߶��AMHW_FIFO_STAT_*��Ļ�or��ֵ(#AMHW_FIFO_STAT_RXTH)
 *
 * \return ��
 *
 * \note ֻ��һЩ�ض���״̬λд1�������������AMHW_FIFO_STAT_RXTIMEOUT��AMHW_FIFO_STAT_BUSERR 
 */
am_static_inline
void amhw_fifo_usart_stat_clr (amhw_fifo_t          *p_hw_fifo,
                               amhw_fifo_usart_ch_t  usart_ch,
                               uint32_t              clr_bits)
{
    p_hw_fifo->usart[usart_ch].stat = clr_bits;
}

/**
 * \brief ʹ�ܴ���FIFO�ж�
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] int_flags : AMHW_FIFO_INT_*�ĺ�ֵ���߶��AMHW_FIFO_INT_*��Ļ�or��ֵ(#AMHW_FIFO_INT_RXTH)
 *
 * \return ��
 */
am_static_inline
void amhw_fifo_usart_int_enable (amhw_fifo_t          *p_hw_fifo,
                                 amhw_fifo_usart_ch_t  usart_ch,
                                 uint32_t              int_flags)
{
    p_hw_fifo->usart[usart_ch].ctlset = int_flags;
}

/**
 * \brief ���ܴ���FIFO�ж�
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] int_flags : AMHW_FIFO_INT_*�ĺ�ֵ���߶��AMHW_FIFO_INT_*��Ļ�or��ֵ(#AMHW_FIFO_INT_RXTH)
 *
 * \return ��
 */
am_static_inline
void amhw_fifo_usart_int_disable (amhw_fifo_t          *p_hw_fifo,
                                  amhw_fifo_usart_ch_t  usart_ch,
                                  uint32_t              int_flags)
{
    p_hw_fifo->usart[usart_ch].ctlclr = int_flags;
}

/**
 * \brief ������ڽ���/����FIFO��ʹ���Ϊ��
 *
 * \param[in] p_hw_fifo   : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch    : ����ͨ����
 * \param[in] flush_flags : FIFO�����ʶλ
                            ���磺(#AMHW_FIFO_CTRL_RXFLUSH) and/or (#AMHW_FIFO_CTRL_TXFLUSH)
 * \return ��
 */
am_static_inline
void amhw_fifo_usart_flush (amhw_fifo_t          *p_hw_fifo,
                            amhw_fifo_usart_ch_t  usart_ch,
                            uint32_t              flush_flags)
{
    flush_flags = flush_flags & (AMHW_FIFO_CTRL_RXFLUSH | AMHW_FIFO_CTRL_TXFLUSH);

    p_hw_fifo->usart[usart_ch].ctlset = flush_flags;
    p_hw_fifo->usart[usart_ch].ctlclr = flush_flags;
}

/**
 * \brief д��һ�ֽ����ݵ�����FIFO�������ݼĴ���
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] data      : д�������
 *
 * \return ��
 */
am_static_inline
void amhw_fifo_usart_txdata_write (amhw_fifo_t          *p_hw_fifo,
                                   amhw_fifo_usart_ch_t  usart_ch,
                                   uint8_t               data)
{
    p_hw_fifo->usart[usart_ch].txdat = data;  
}

/**
 * \brief ��ȡһ���ֽ����ݴӴ���FIFO�������ݼĴ���
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 *
 * \return ��ȡ��������
 */
am_static_inline
uint32_t amhw_fifo_usart_rxdata_read (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return p_hw_fifo->usart[usart_ch].rxdat;
}


/**
 * \brief д��һ�����ݵ�����FIFO
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] p_txbuf   : ���͵����ݻ���
 * \param[in] nbytes    : ��������ݳ���
 *
 * \return д�뵽FIFO�����ݳ���
 */
uint32_t amhw_fifo_usart_write_data(amhw_fifo_t          *p_hw_fifo,
                                    amhw_fifo_usart_ch_t  usart_ch,
                                    uint8_t              *p_txbuf,
                                    uint32_t              nbytes);


/**
 * \brief ��ȡ���ݴӴ���FIFO
 *
 * \param[in] p_hw_fifo : ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] p_rxbuf   : �������ݻ���
 * \param[in] nbytes    : ��������ݳ���
 *
 * \return ��FIFO�ж�ȡ�������ݳ���
 */
uint32_t amhw_fifo_usart_read_data(amhw_fifo_t          *p_hw_fifo,
                                   amhw_fifo_usart_ch_t  usart_ch,
                                   uint8_t              *p_rxbuf,
                                   uint32_t              nbytes);

/**
 * \name ����FIFO���ݵ�״̬λ����
 * @{
 */

#define AMHW_FIFO_USART_RXDATA_FRAMHERR   (1 << 13)  /**< \brief ����֡����״̬  */
#define AMHW_FIFO_USART_RXDATA_PARITYERR  (1 << 14)  /**< \brief ���Դ���״̬    */
#define AMHW_FIFO_USART_RXDATA_RXNOISE    (1 << 15)  /**< \brief ���ո���״̬ */

/** @} */

/**
 * \brief �����ݺ�״̬��ϵͳFIFO
 *
 * \param[in] p_hw_fifo : ָ��FIFO�Ĵ������ָ��
 * \param[in] usart_ch  : ����ͨ����
 * \param[in] p_buf     : �������ݻ���
 * \param[in] nbytes    : ��������ݳ���
 *
 * \return ��FIFO�ж�ȡ�������ݳ���   
 */
uint32_t amhw_fifo_usart_read_data_with_stat(amhw_fifo_t          *p_hw_fifo,
                                             amhw_fifo_usart_ch_t  usart_ch,
                                             uint16_t             *p_buf,
                                             uint32_t              nbytes);

                                             
/**
 * @} amhw_if_fifo
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __AMHW_FIFO_H */

/* end of file */

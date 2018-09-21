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
 * \brief FIFO for Serial Peripherals implementation for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */
 
#include "amhw_fifo.h"

/**
 * \brief Get FIFO space size
 */
uint32_t amhw_fifo_space_get (amhw_fifo_t        *p_hw_fifo,
                              amhw_fifo_periph_t  periph_id,
                              amhw_fifo_dir_t     dir)
{
    uint32_t reg;
    
    /* First, get peripheral common control register value */
    if (periph_id == AMHW_FIFO_PERIPH_USART) {
        reg = p_hw_fifo->common.fifoctlusart;
    } else {
        reg = p_hw_fifo->common.fifoctlspi;
    }
    
    /* Next, get available space size */
    if (dir == AMHW_FIFO_RX) {
        reg = reg >> 16;
    } else {
        reg = reg >> 24;
    }
    
    return (reg & 0xFF);
}

/**
 * \brief Pause peripheral FIFO
 */
void amhw_fifo_pause (amhw_fifo_t        *p_hw_fifo,
                      amhw_fifo_periph_t  periph_id,
                      amhw_fifo_dir_t     dir)
{
    if (periph_id == AMHW_FIFO_PERIPH_USART) {
        if (dir == AMHW_FIFO_RX) {
             p_hw_fifo->common.fifoctlusart |= (1 << 0);  /* Pause all UART receive FIFO operations */
        } else {
             p_hw_fifo->common.fifoctlusart |= (1 << 8);  /* Pause all UART send FIFO operations */
        }
    } else {
        if (dir == AMHW_FIFO_RX) {
             p_hw_fifo->common.fifoctlspi |= (1 << 0);    /* Pause all SPIs receive FIFO operations */
       } else {                                
             p_hw_fifo->common.fifoctlspi |= (1 << 8);    /* Pause all SPIs send FIFO operations */
        }
    }
}


/**
 * \brief Restart peripheral FIFO
 */
void amhw_fifo_restart (amhw_fifo_t        *p_hw_fifo,
                        amhw_fifo_periph_t  periph_id,
                        amhw_fifo_dir_t     dir)
{
    if (periph_id == AMHW_FIFO_PERIPH_USART) {
        if (dir == AMHW_FIFO_RX) {
             p_hw_fifo->common.fifoctlusart &= ~(1 << 0);  
        } else {
             p_hw_fifo->common.fifoctlusart &= ~(1 << 8);  
        }
    } else {
        if (dir == AMHW_FIFO_RX) {
             p_hw_fifo->common.fifoctlspi &= ~(1 << 0); 
        } else {                                
             p_hw_fifo->common.fifoctlspi &= ~(1 << 8);
        }
    }
}

/**
 * \brief Read a peripheral FIFO sizes 
 */
int amhw_fifo_size_read (amhw_fifo_t        *p_hw_fifo, 
                         amhw_fifo_periph_t  periph_id,
                         amhw_fifo_size_t   *p_size)
{
    int                max_periphs, i;
    volatile uint32_t *p_hw_fifosizes;
    
    /* 
     * Maximum peripheral FIFO supported 
     */
    if (periph_id == AMHW_FIFO_PERIPH_USART) {
        max_periphs    = AMHW_FIFO_USART_MAX;
        
        /* Save the size configure address */
        p_hw_fifosizes = &(p_hw_fifo->common.fifocfgusart[0]); 
    } else {
        max_periphs    = AMHW_FIFO_SPI_MAX;
        
        /* Save the size configure address */
        p_hw_fifosizes = &(p_hw_fifo->common.fifocfgspi[0]);  
    }
    
    /* 
     * Update FIFO sizes 
     */
    for (i = 0; i < max_periphs; i++) {
        p_size->fifo_rxsize[i] = p_hw_fifosizes[i] & 0xFF;
        p_size->fifo_txsize[i] = (p_hw_fifosizes[i] >> 8) & 0xFF;
    }

    return AM_OK;
}

/**
 * \brief Configure a peripheral FIFO sizes 
 */
int amhw_fifo_size_cfg (amhw_fifo_t        *p_hw_fifo,
                        amhw_fifo_periph_t  periph_id,
                        amhw_fifo_size_t   *p_size)
{
    int                max_periphs, i;
    uint32_t           update_mask;
    volatile uint32_t *update_reg, *p_hw_fifosizes, *p_hw_fifopause;
    
    int max_space_rx = amhw_fifo_space_get(p_hw_fifo, periph_id, AMHW_FIFO_RX);
    int max_space_tx = amhw_fifo_space_get(p_hw_fifo, periph_id, AMHW_FIFO_TX);
    int sum_rx       = 0;
    int sum_tx       = 0;

    /*
     * Pause FIFO 
     */
    amhw_fifo_pause(p_hw_fifo, periph_id, AMHW_FIFO_RX);
    amhw_fifo_pause(p_hw_fifo, periph_id, AMHW_FIFO_TX);

    /* 
     * Maximum peripheral FIFO supported 
     */
    if (periph_id == AMHW_FIFO_PERIPH_USART) {
        max_periphs = AMHW_FIFO_USART_MAX;
        
        update_reg     = &p_hw_fifo->common.fifoupdateusart;
        update_mask    = 0xF | (0xF << 16);
        
        /* Save the size configure address */
        p_hw_fifosizes = &(p_hw_fifo->common.fifocfgusart[0]); 
        p_hw_fifopause = &(p_hw_fifo->common.fifoctlusart);
    } else {
        max_periphs = AMHW_FIFO_SPI_MAX;
        
        update_reg     = &p_hw_fifo->common.fifoupdatespi;
        update_mask    = 0xF | (0xF << 16);
        
        /* Save the size configure address */
        p_hw_fifosizes = &(p_hw_fifo->common.fifocfgspi[0]);  
        p_hw_fifopause = &(p_hw_fifo->common.fifoctlspi);
    }
    
    sum_rx = sum_tx = 0;
    
    for (i = 0; i < max_periphs; i++) {
        sum_rx += p_size->fifo_rxsize[i];
        sum_tx += p_size->fifo_txsize[i];
    }
    
    if ((sum_rx > max_space_rx) || (sum_tx > max_space_tx)) {
        return -AM_EINVAL;
    }
    
    /* Wait for FIFO pause */
    while ((*p_hw_fifopause & ((1 << 0) | (1 << 8))) != ((1 << 0) | (1 << 8)));

    /* Wait for FIFO pause */
    while ((*p_hw_fifopause & ((1 << 1) | (1 << 9))) != ((1 << 1) | (1 << 9)));

    /* Wait for FIFO Empty */
    while ((*p_hw_fifopause & ((1 << 2) | (1 << 10))) != ((1 << 2) | (1 << 10)));

    /* 
     * Update FIFO sizes 
     */
    for (i = 0; i < max_periphs; i++) {
        p_hw_fifosizes[i] = ((uint32_t)(p_size->fifo_rxsize[i]) << 0) |
                            ((uint32_t)(p_size->fifo_txsize[i]) << 8);
    }

    /* update all peripheral FIFO sizes */
    *update_reg = update_mask;
    
    return AM_OK;
}

/**
 * \brief  Configure the UART system FIFO
 */
int amhw_fifo_usart_cfg (amhw_fifo_t          *p_hw_fifo,
                         amhw_fifo_usart_ch_t  usart_ch,
                         amhw_fifo_cfg_t      *p_cfg)
{
    p_cfg->flags &= (AMHW_FIFO_CFG_TIMEOUTCONTONEMPTY | 
                     AMHW_FIFO_CFG_TIMEOUTCONTONWRITE);
    
    p_cfg->timeout_base  &= 0xF;
    p_cfg->timeout_value &= 0xF;
    p_cfg->rx_threshold  &= 0xFF;
    p_cfg->tx_threshold  &= 0xFF;
    
    /* The time-out value is 0 ~ 15 */
    if (p_cfg->timeout_value < 2) {
        return -AM_EINVAL;
    }
    
    p_hw_fifo->usart[usart_ch].cfg =  p_cfg->flags                 |
                                     (p_cfg->timeout_base  << 8)   |
                                     (p_cfg->timeout_value << 12)  |
                                     (p_cfg->rx_threshold  << 16)  |
                                     (p_cfg->tx_threshold  << 24);
    
    return AM_OK;
}


/**
 * \brief write data to a system FIFO (non-blocking) 
 */
uint32_t amhw_fifo_usart_write_data (amhw_fifo_t          *p_hw_fifo,
                                     amhw_fifo_usart_ch_t  usart_ch,
                                     uint8_t              *p_txbuf,
                                     uint32_t              nbytes)
{
    uint32_t write_len;
    uint32_t valid_len;

    valid_len = (p_hw_fifo->usart[usart_ch].stat >> 24) & 0xFF;  /* Get valid length */

    /* Get length of can write in */
    if (valid_len > nbytes) {
        valid_len = nbytes;
    }
    
    write_len = valid_len;
    
    for (; valid_len > 0; valid_len--) {
        p_hw_fifo->usart[usart_ch].txdat = *p_txbuf++;        /* Write from buffer */
    }
    
    return write_len;
}

/**
 * \brief Read data from a system FIFO (non-blocking) 
 */
uint32_t amhw_fifo_usart_read_data (amhw_fifo_t          *p_hw_fifo,
                                    amhw_fifo_usart_ch_t  ch,
                                    uint8_t              *p_rxbuf,
                                    uint32_t              nbytes)
{
    uint32_t read_len;
    uint32_t valid_len;
    
    /* get valid length */
    valid_len = (p_hw_fifo->usart[ch].stat >> 16) & 0xFF;  

    if (valid_len > nbytes) {
        valid_len = nbytes;
    }
    
    read_len = valid_len;
    for (; valid_len > 0; valid_len--) {
        *p_rxbuf++ = p_hw_fifo->usart[ch].rxdat;    /* Read data from buffer */
    }
    
    return read_len;
}


/**
 * \brief Read data from a system FIFO with status (non-blocking) 
 */
uint32_t amhw_fifo_usart_read_data_with_stat (amhw_fifo_t          *p_hw_fifo,
                                              amhw_fifo_usart_ch_t  usart_ch,
                                              uint16_t             *p_buf, 
                                              uint32_t              nbytes)
{
    uint32_t read_len;
    uint32_t valid_len;
    
    /* get valid length */
    valid_len = (p_hw_fifo->usart[usart_ch].stat >> 16) & 0xFF;  

    if (valid_len > nbytes) {
        valid_len = nbytes;
    }
    
    read_len = valid_len;
    for (; valid_len > 0; valid_len--) {
        *p_buf++ = p_hw_fifo->usart[usart_ch].rxdatstat & (0xFFFF);   
    }
    
    return read_len;
}

/* end of file */

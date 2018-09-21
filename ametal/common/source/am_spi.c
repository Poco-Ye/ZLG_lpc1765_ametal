/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#include "am_spi.h"

/**
 * \brief SPI传输完成回调函数
 */


static volatile uint8_t __g_trans_stat = AM_OK;
 
static void __transfer_complete(void *p_arg,int status)
{
    am_wait_t *p_wait = (am_wait_t *)p_arg;
    
    __g_trans_stat = status;
    
    /* 结束等待序列 */
    am_wait_done(p_wait);
}

/**
 * \brief 先写后读
 */
int am_spi_write_then_read (am_spi_handle_t  handle,
                            const uint8_t   *p_txbuf,
                            size_t           n_tx,
                            uint8_t         *p_rxbuf,
                            size_t           n_rx)
{
    am_spi_transfer_t trans;
    am_wait_t         trans_wait;
    
    if (handle == NULL) {
        return -AM_EINVAL;
    }
    
    am_wait_init(&trans_wait);
    
    am_spi_mktrans(&trans,
                   p_txbuf,
                   NULL,
                   n_tx,
                   0,
                   __transfer_complete,
                   (void *)&trans_wait);
    
    am_spi_transfer(handle, &trans);
    am_wait_on(&trans_wait);

    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }
    
    am_spi_mktrans(&trans,
                   NULL,
                   p_rxbuf,
                   n_rx,
                   AM_SPI_TRANS_EOT,
                   __transfer_complete,
                   (void *)&trans_wait);
    
    am_spi_transfer(handle, &trans);
    am_wait_on(&trans_wait);
    
    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }
    
    return AM_OK;
}

/**
 * \brief 执行两次写操作
 */
int am_spi_write_then_write (am_spi_handle_t  handle,
                             const uint8_t   *p_txbuf0,
                             size_t           n_tx0,
                             const uint8_t   *p_txbuf1,
                             size_t           n_tx1)
                                 
{
    am_spi_transfer_t trans;
    am_wait_t         trans_wait;
    
    if (handle == NULL) {
        return -AM_EINVAL;
    }
    
    am_wait_init(&trans_wait);
    
    am_spi_mktrans(&trans,
                   p_txbuf0,
                   NULL,
                   n_tx0,
                   0,
                   __transfer_complete,
                   (void *)&trans_wait);

    am_spi_transfer(handle, &trans);
    am_wait_on(&trans_wait);
    
    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }
    
    am_spi_mktrans(&trans,
                   p_txbuf1,
                   NULL,
                   n_tx1,
                   AM_SPI_TRANS_EOT,
                   __transfer_complete,
                   (void *)&trans_wait);
    
    am_spi_transfer(handle, &trans);
    am_wait_on(&trans_wait);

    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }
    
    return AM_OK;
}

/* end of file */

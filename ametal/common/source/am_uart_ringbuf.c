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
 * \brief UART implementation by ring buffer 
 * 
 * \internal
 * \par Modification history
 * - 1.01 14-12-03  jon, add UART interrupt mode
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
#include "am_uart_ringbuf.h"
#include "am_ringbuf.h"
 
/*******************************************************************************
  Public functions
*******************************************************************************/ 

/** 
 * \brief the function that to get one char to transmit.
 */
int __uart_ringbuf_txchar_get (void *p_arg, char *p_outchar)
{
    am_ringbuf_t *p_rb = (am_ringbuf_t *)p_arg;
    
    /* Success pop one data from ring buffer */
    if (am_ringbuf_pop(p_rb, p_outchar) == 1) {
         return AM_OK;
    }
    
    return -AM_EEMPTY;     /* No data to transmit,return -AM_EEMPTY */ 
}

/** 
 * \brief the function revived one char.
 */
int __uart_ringbuf_rxchar_put (void *p_arg, char inchar)
{
    am_ringbuf_t *p_rb = (am_ringbuf_t *)p_arg;
    
    /* Success Insert one data to ring buffer */
    if (am_ringbuf_insert(p_rb, &inchar) == 1) {
        return AM_OK;
    }
    
    return -AM_EFULL;          /* No data to receive,return -AM_EFULL */  
}

/**
 * \brief UART send data.
 */
int am_uart_ringbuf_send (am_uart_ringbuf_handle_t  ringbuf_handle,
                          const uint8_t            *p_txbuf,
                          uint32_t                  nbytes)
{
    
    am_uart_ringbuf_dev_t *p_dev  = (am_uart_ringbuf_dev_t *)ringbuf_handle;
    am_ringbuf_t          *p_rb   = &p_dev->tx_ringbuf;

    uint32_t rb_ct, write_ct;

    uint32_t len = nbytes;
    
    while (len > 0) {
        if (am_ringbuf_isfull(p_rb) == TRUE) {
            continue;
        }

        rb_ct    = am_ringbuf_size_free_get(p_rb);

        write_ct = (rb_ct > len) ? len : rb_ct;

        am_ringbuf_insert_mult(p_rb, p_txbuf, write_ct);
        
        p_txbuf += write_ct;
        
        len     -= write_ct;
        
        am_uart_tx_startup(p_dev->handle);
    }

    return nbytes;
}

/**
 * \brief UART receive data
 */
int am_uart_ringbuf_receive (am_uart_ringbuf_handle_t   ringbuf_handle,
                             uint8_t                   *p_rxbuf,
                             uint32_t                   nbytes)
{
    
    am_uart_ringbuf_dev_t *p_dev =  (am_uart_ringbuf_dev_t *)ringbuf_handle;
    am_ringbuf_t          *p_rb  = &p_dev->rx_ringbuf;
    
    uint32_t rb_ct, read_ct;
    
    uint32_t len = nbytes;
    
    while (len > 0) {
        if (am_ringbuf_isempty(p_rb) == TRUE) {
            continue;
        }

        rb_ct   = am_ringbuf_size_used_get(p_rb);

        read_ct = (rb_ct > len) ? len : rb_ct;

        am_ringbuf_pop_mult(p_rb, p_rxbuf, read_ct);
        
        p_rxbuf += read_ct;
        
        len     -= read_ct;
    }
    
    return nbytes;
}

am_uart_ringbuf_handle_t am_uart_ringbuf_init (am_uart_ringbuf_dev_t *p_dev,
                                               am_uart_handle_t       handle,
                                               char                  *p_rxbuf,
                                               uint32_t               rxbuf_size,
                                               char                  *p_txbuf,
                                               uint32_t               txbuf_size)
{
    if (handle == NULL) {
        return NULL;
    }
    
    p_dev->handle = handle;
    
    if (txbuf_size == 0 || rxbuf_size == 0) {
        return NULL;
    }
    
    /* The size should be 2^n */
    if ((txbuf_size & (txbuf_size - 1)) != 0) {
        return NULL;
    }
    
    if ((rxbuf_size & (rxbuf_size - 1)) != 0) {
        return NULL;
    }
    
    /* Initialize the ring-buffer */
    am_ringbuf_init(&(p_dev->rx_ringbuf), p_rxbuf, 1, rxbuf_size);
    am_ringbuf_init(&(p_dev->tx_ringbuf), p_txbuf, 1, txbuf_size);
    
    am_uart_ioctl(handle, AM_UART_MODE_SET, (void *)AM_UART_MODE_INT);
    
    am_uart_callback_set(handle,
                         AM_UART_CALLBACK_GET_TX_CHAR,
        (int (*)(void *))__uart_ringbuf_txchar_get,
                         (void *)&(p_dev->tx_ringbuf));

    am_uart_callback_set(handle,
                         AM_UART_CALLBACK_PUT_RCV_CHAR,
        (int (*)(void *))__uart_ringbuf_rxchar_put,
                         (void *)&(p_dev->rx_ringbuf));
                                   
    am_uart_connect(handle);
    
    return (am_uart_ringbuf_handle_t)(p_dev);
    
}

/* end of file */

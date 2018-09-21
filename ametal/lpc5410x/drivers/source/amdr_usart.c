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
 * \brief USART drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.01 14-12-03  jon, add USART interrupt mode
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
#include "amdr_usart.h"
#include "amhw_fifo.h"
#include "amhw_clock.h"
#include "am_int.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

int __usart_mode_set(amdr_usart_dev_t *p_dev, uint32_t new_mode);

int __usart_opt_set(amdr_usart_dev_t *p_dev, uint32_t opts);

/* lpc5410x UART drv functions declaration */
static int __usart_ioctl(void *p_drv, int, void *);

static int __usart_tx_startup(void *p_drv);

static int __usart_callback_set(void  *p_drv,
                                int    callback_type,
                                int  (*pfn_callback)(void *),
                                void  *callback_arg);
                                     
static int __usart_poll_getchar(void *p_drv, char *p_char);

static int __usart_poll_putchar(void *p_drv, char outchar);

static int __usart_connect(void *p_drv);
                                      
/** \brief SIO driver functions */
static const struct am_uart_drv_funcs __g_uart_drv_funcs = {
     __usart_ioctl,
     __usart_tx_startup,
     __usart_callback_set,
     __usart_poll_getchar,
     __usart_poll_putchar,
     __usart_connect,
};

/*******************************************************************************/

/**
 * \brief special device control
 *
 * Includes commands to get/set baud rate, mode (INT,POLL), hardware options
 * (parity, number of data bits), and modem control (RTS/CTS).
 * The ioctl command SIO_HUP is sent by ttyDrv when the last close() function
 * call is made. Likewise SIO_OPEN is sent when the first open() function call
 * is made.
 *
 * \return AM_OK on success, -AM_EIO on device error,
 *         -AM_ENOTSUP on unsupported request
 */
static int __usart_ioctl (void *p_drv, int request, void *p_arg)
{
    amdr_usart_dev_t *p_dev  = (amdr_usart_dev_t *)p_drv;
    int               status = AM_OK;
    amhw_usart_t     *p_hw_usart;
    
    switch (request) {
    case AM_UART_BAUD_SET:
        p_hw_usart = p_dev->p_devinfo->p_hw_usart;
    
        while ((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_STAT_TXIDLE) == 0);
    
        status = amhw_usart_baudrate_set(p_dev->p_devinfo->p_hw_usart,
                                         amhw_clock_usart_baseclkrate_get(),
                                        (uint32_t)p_arg);
    
        if (status > 0) {
            p_dev->baud_rate = status;
            status = AM_OK;
        } else {
            status = -AM_EIO;
        }
        break;

    case AM_UART_BAUD_GET:
        *(int *)p_arg = p_dev->baud_rate;
        break;

    case AM_UART_MODE_SET:
        status = (__usart_mode_set(p_dev, (int)p_arg) == AM_OK)
                 ? AM_OK : -AM_EIO;
        break;

    case AM_UART_MODE_GET:
        *(int *)p_arg = p_dev->channel_mode;
        break;

    case AM_UART_AVAIL_MODES_GET:
        *(int *)p_arg = AM_UART_MODE_INT | AM_UART_MODE_POLL;
        break;

    case AM_UART_OPTS_SET:
        status = (__usart_opt_set(p_dev, (int)p_arg) == AM_OK) ? AM_OK : -AM_EIO;
        break;

    case AM_UART_OPTS_GET:
        *(int *)p_arg = p_dev->options;
        break;
    default:
        status = -AM_EIO;
        break;
    }

    return (status);
}

/** 
 * \brief USART start transfer(only for interrupt mode)
 */
int __usart_tx_startup (void *p_drv)
{
    amdr_usart_dev_t *p_dev   = (amdr_usart_dev_t *)p_drv;
    uint8_t           tx_size = p_dev->p_devinfo->fifo_info.tx_size;

    /* Use the Tx FIFO */
    if (tx_size != 0) {
        amhw_fifo_t          *p_hw_fifo = p_dev->p_devinfo->fifo_info.p_hw_fifo;
        amhw_fifo_usart_ch_t  usart_ch  = p_dev->p_devinfo->fifo_info.usart_ch;
        
        /* enable FIFO TX THRESHOLD interrupt */
        amhw_fifo_usart_int_enable(p_hw_fifo, 
                                   usart_ch, 
                                   AMHW_FIFO_INT_TXTH);
    } else {
        amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
        
        /* Enable the TXRDY interrupt */
        amhw_usart_int_enable(p_hw_usart, AMHW_USART_INT_TXRDY);
    }
    
    return AM_OK;
}

/**
 * \brief install ISR call backs
 *
 * This routine installs the call back functions to get/put chars for the
 * driver.
 *
 * \param p_siochan         pointer to device to control
 * \param callback_type     callback type(Tx or receive)
 * \param pfn_callback    pointer to callback function
 * \param callback_arg      callback function argument
 *
 * \return AM_OK on success, ENOSYS on unsupported call back type
 */
static int __usart_callback_set (void  *p_drv,
                                 int    callback_type,
                                 int  (*pfn_callback)(void *),
                                 void  *callback_arg)
{
    amdr_usart_dev_t *p_dev = (amdr_usart_dev_t *)p_drv;
    
    switch (callback_type) {
    case AM_UART_CALLBACK_GET_TX_CHAR:
        p_dev->pfn_txchar_get = (pfn_uart_txchar_get_t)pfn_callback;
        p_dev->txget_arg      = callback_arg;
        return (AM_OK);
    
    case AM_UART_CALLBACK_PUT_RCV_CHAR:
        p_dev->pfn_rxchar_put = (pfn_uart_rxchar_put_t)pfn_callback;
        p_dev->rxput_arg      = callback_arg;
        return (AM_OK);
    
    case AM_UART_CALLBACK_ERROR:
        p_dev->pfn_err = (pfn_uart_err_t)pfn_callback;
        p_dev->err_arg = callback_arg;
        return (AM_OK);
        
    default:
        return (-AM_ENOTSUP);
    }
}

/**
 * \brief output a character in polled mode
 *
 * This routine transmits a character in polled mode.
 *
 * \return AM_OK if a character sent, -EAGAIN if the output buffer is full
 */
static int __usart_poll_putchar (void *p_drv, char outchar)
{
    amdr_usart_dev_t *p_dev   = (amdr_usart_dev_t *)p_drv;
    uint8_t           tx_size = p_dev->p_devinfo->fifo_info.tx_size;

    if (tx_size != 0) {
        amhw_fifo_t         *p_hw_fifo = p_dev->p_devinfo->fifo_info.p_hw_fifo;
        amhw_fifo_usart_ch_t usart_ch  = p_dev->p_devinfo->fifo_info.usart_ch;
        
        if (amhw_fifo_usart_txcount_get(p_hw_fifo, usart_ch) == 0) {
            return (-AM_EAGAIN); 
        } else {
            amhw_fifo_usart_txdata_write(p_hw_fifo, usart_ch, outchar);
        }
    } else {
        amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
        
        /* TX not ready */
        if ((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_STAT_TXRDY) == 0) {
            return (-AM_EAGAIN); 
        } else {
        
            /* Send one data */
            amhw_usart_txdata_write(p_hw_usart, outchar);
        }
    }
    
    return (AM_OK);
}

/**
 * \brief poll for input
 *
 * This routine polls the device for input.
 *
 * \return AM_OK if a character arrived, -EAGAIN if the input buffer if empty
 */
static int __usart_poll_getchar (void *p_drv, char *p_char)
{
    amdr_usart_dev_t *p_dev   = (amdr_usart_dev_t *)p_drv;
    uint8_t           rx_size = p_dev->p_devinfo->fifo_info.rx_size;
    
    uint8_t *p_inchar = (uint8_t *)p_char;

    if (rx_size != 0) {
        amhw_fifo_t         *p_hw_fifo = p_dev->p_devinfo->fifo_info.p_hw_fifo;
        amhw_fifo_usart_ch_t usart_ch  = p_dev->p_devinfo->fifo_info.usart_ch;
    
        if (amhw_fifo_usart_rxcount_get(p_hw_fifo, usart_ch) == 0) {
            return (-AM_EAGAIN); 
        } else {
            *p_inchar = amhw_fifo_usart_rxdata_read(p_hw_fifo, usart_ch);
        }
    } else {
        amhw_usart_t *p_hw_usart  = p_dev->p_devinfo->p_hw_usart;
        
        /* RX not ready */
        if ((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_STAT_RXRDY) == 0) {
            return (-AM_EAGAIN);
        } else {
            *p_inchar = amhw_usart_rxdata_read(p_hw_usart);
        }
    }

    return (AM_OK);
}

int __usart_mode_set (amdr_usart_dev_t *p_dev, uint32_t new_mode)
{
    uint8_t rx_size = p_dev->p_devinfo->fifo_info.rx_size;

    /* Only support interrupt mode or poll mode */
    if ((new_mode != AM_UART_MODE_POLL) && (new_mode != AM_UART_MODE_INT)) {
        return (AM_ERROR);
    }
    
    if (rx_size != 0) {
        amhw_fifo_t         *p_hw_fifo = p_dev->p_devinfo->fifo_info.p_hw_fifo;
        amhw_fifo_usart_ch_t usart_ch  = p_dev->p_devinfo->fifo_info.usart_ch;
            
        if (new_mode == AM_UART_MODE_INT) {
             amhw_fifo_usart_int_enable(p_hw_fifo, usart_ch, AMHW_FIFO_INT_RXTH    |
                                                             AMHW_FIFO_INT_RXTIMEOUT);
        } else {
             amhw_fifo_usart_int_disable(p_hw_fifo, usart_ch, AMHW_FIFO_INT_RXTH    |
                                                              AMHW_FIFO_INT_TXTH    |
                                                              AMHW_FIFO_INT_RXTIMEOUT);
        }
    } else {
        
        amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;

        if (new_mode == AM_UART_MODE_INT) {
            
            /* Enable the RXRDY interrupt */
            amhw_usart_int_enable(p_hw_usart, AMHW_USART_INT_RXRDY);

        } else {
        
            /* disable all USART interrupts */
            amhw_usart_int_disable(p_hw_usart, AMHW_USART_INT_ALL);
        }
    }
    
    p_dev->channel_mode = new_mode;

    return (AM_OK);
}

/* Support data length, stop bit and parity configure */
int __usart_opt_set (amdr_usart_dev_t *p_dev, uint32_t options)
{
    amhw_usart_t *p_hw_usart;
    uint32_t      cfg_flags;
    
    if (p_dev == NULL) {
        return AM_ERROR;
    }
    
    p_hw_usart = p_dev->p_devinfo->p_hw_usart;
    cfg_flags  = p_hw_usart->cfg;
    
    switch (options & AM_UART_CSIZE) {
    case AM_UART_CS7:
        cfg_flags &= ~(0x03 << 2);
        cfg_flags |= AMHW_USART_CFG_7BIT;
        break;
        
    case AM_UART_CS8:
        cfg_flags &= ~(0x03 << 2);
        cfg_flags |= AMHW_USART_CFG_8BIT;
        break;
        
    default:
        break;
    }

    /* is two stop bits ? */
    if (options & AM_UART_STOPB) {
        cfg_flags &= ~(0x01 << 6);
        cfg_flags |= AMHW_USART_CFG_STOP_2;
    } else {
        cfg_flags &= ~(0x01 << 6);
        cfg_flags |= AMHW_USART_CFG_STOP_1;
    }

    /* if enable parity detection */        
    if (options & AM_UART_PARENB) {
        cfg_flags &= ~(0x03 << 4);

        if (options & AM_UART_PARODD) {   /* odd parity */   
            cfg_flags |= AMHW_USART_CFG_PARITY_ODD;
        } else {                     
            cfg_flags |= AMHW_USART_CFG_PARITY_EVEN;
        }
    } else {
        cfg_flags &= ~(0x03 << 4);
        cfg_flags |= AMHW_USART_CFG_PARITY_NO;
    }

    if ((p_hw_usart->cfg & 0x01) == 1) {
    
        /* wait for idle */
        while((amhw_usart_stat_get(p_hw_usart) & AMHW_USART_STAT_TXIDLE) == 0);
        amhw_usart_disable(p_hw_usart);
    }
    
    p_hw_usart->cfg = cfg_flags;
    amhw_usart_enable(p_hw_usart);
    
    p_dev->options = options;
    
    return (AM_OK);
}

/*******************************************************************************
  USART interrupt request handler
*******************************************************************************/

void __usart_irq_rx_handler (amdr_usart_dev_t *p_dev)
{
    amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
    uint32_t      int_stat   = amhw_usart_intstat_get(p_hw_usart);
    
    char data;
    
    /* Check if is the RX interrupt */
    if ((int_stat & AMHW_USART_INTSTAT_RXRDY) != 0) {
        
        data = amhw_usart_rxdata_read(p_hw_usart);
        
        p_dev->pfn_rxchar_put(p_dev->rxput_arg, data);
    }
}

void __usart_irq_tx_handler (amdr_usart_dev_t *p_dev)
{
    amhw_usart_t *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
    uint32_t      int_stat   = amhw_usart_intstat_get(p_hw_usart);
    
    char data;
    
    /* Check if is the TX interrupt */
    if (((int_stat & AMHW_USART_INTSTAT_TXRDY)  != 0) || 
        ((int_stat & AMHW_USART_INTSTAT_TXIDLE) != 0)) {

        if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
            amhw_usart_txdata_write(p_hw_usart, data);
        } else {                                 /* No data to transmit */
            amhw_usart_int_disable(p_hw_usart, AMHW_USART_INT_TXRDY);
        }
    }
}

void __fifo_irq_rx_handler (amdr_usart_dev_t *p_dev)
{
    amhw_fifo_t         *p_hw_fifo = p_dev->p_devinfo->fifo_info.p_hw_fifo;
    amhw_fifo_usart_ch_t usart_ch  = p_dev->p_devinfo->fifo_info.usart_ch;
    
    uint32_t int_stat = amhw_fifo_usart_intstat_get(p_hw_fifo, usart_ch);
    
    uint32_t data_len, i;
    char data;

    /* Check if is the Receive FIFO Threshold interrupt */
    if ((int_stat & (AMHW_FIFO_STAT_RXTH | AMHW_FIFO_STAT_RXTIMEOUT)) != 0) {

        data_len = amhw_fifo_usart_rxcount_get(p_hw_fifo, usart_ch);
       
        for (i = 0 ; i < data_len; i++) {
            data = amhw_fifo_usart_rxdata_read(p_hw_fifo, usart_ch);
            p_dev->pfn_rxchar_put(p_dev->rxput_arg, data);
        }

        /* Check if is the Receive Time out interrupt */
        if ((int_stat & AMHW_FIFO_STAT_RXTIMEOUT) != 0) {
        
            /* clear status */
            amhw_fifo_usart_stat_clr(p_hw_fifo, usart_ch, AMHW_FIFO_STAT_RXTIMEOUT);
        }
    }
    
    /* FIFO Bus error */
    if ((int_stat & AMHW_FIFO_STAT_BUSERR) != 0 ) {
        
        /* handle bus err */
        amhw_fifo_usart_stat_clr(p_hw_fifo, usart_ch, AMHW_FIFO_STAT_BUSERR);
    }
}

void __fifo_irq_tx_handler (amdr_usart_dev_t *p_dev)
{
    amhw_fifo_t          *p_hw_fifo = p_dev->p_devinfo->fifo_info.p_hw_fifo;
    amhw_fifo_usart_ch_t  usart_ch  = p_dev->p_devinfo->fifo_info.usart_ch;
    
    uint32_t int_stat = amhw_fifo_usart_intstat_get(p_hw_fifo, usart_ch);
    uint32_t data_len, i;
    char     data;

    /* Check if is the Transmit FIFO Threshold interrupt */
    if ((int_stat & AMHW_FIFO_STAT_TXTH) != 0) {
        data_len = amhw_fifo_usart_txcount_get(p_hw_fifo, usart_ch);
       
        for (i = 0 ; i < data_len; i++) {
            if ((p_dev->pfn_txchar_get(p_dev->txget_arg, &data)) == AM_OK) {
                amhw_fifo_usart_txdata_write(p_hw_fifo, usart_ch, data);
                
            } else {                                 /* No data to transmit */
                amhw_fifo_usart_int_disable(p_hw_fifo, usart_ch, AMHW_FIFO_INT_TXTH);
            }
        }
    }
    
    /* FIFO Bus error */
    if ((int_stat & AMHW_FIFO_STAT_BUSERR) != 0 ) {
        
        /* handle bus err */
        amhw_fifo_usart_stat_clr(p_hw_fifo, usart_ch, AMHW_FIFO_STAT_BUSERR);
    }
}

/** 
 * \brief USART IRQ handler
 * \param[in] p_arg : The argument data setting in am_int_connect().
 * \return None
 */
void __usart_irq_handler (void *p_arg)
{
    amdr_usart_dev_t     *p_dev      = (amdr_usart_dev_t *)p_arg;
    amhw_usart_t         *p_hw_usart = p_dev->p_devinfo->p_hw_usart;
    amhw_fifo_t          *p_hw_fifo  = p_dev->p_devinfo->fifo_info.p_hw_fifo;
    amhw_fifo_usart_ch_t  usart_ch   = p_dev->p_devinfo->fifo_info.usart_ch;
    
    uint32_t usart_int_stat = amhw_usart_intstat_get(p_hw_usart);
    uint32_t fifo_int_stat  = amhw_fifo_usart_intstat_get(p_hw_fifo, usart_ch);
    
    if (p_dev->p_devinfo->fifo_info.rx_size == 0) {
        __usart_irq_rx_handler(p_dev);
    } else {
        __fifo_irq_rx_handler(p_dev);
    }
    
    if (p_dev->p_devinfo->fifo_info.tx_size == 0) {
        __usart_irq_tx_handler(p_dev);
    } else {
        __fifo_irq_tx_handler(p_dev);
    }

    /* Some specified interrupt happen */
    if ((p_dev->other_int_enable & usart_int_stat) != 0) {

        usart_int_stat &= p_dev->other_int_enable;
        
        if (p_dev->pfn_err != NULL) {
            p_dev->pfn_err(p_dev->err_arg,
                           AMDR_UART_ERRCODE_USART_OTHER_INT,
                           (void *)usart_int_stat,
                           1);
        }
        
    }
    
    /* FIFO Bus error */
    if ((fifo_int_stat & AMHW_FIFO_STAT_BUSERR) != 0 ) {
        
        if (p_dev->pfn_err != NULL) {
            p_dev->pfn_err(p_dev->err_arg,
                           AMDR_UART_ERRCODE_FIFO_BUSERR,
                           NULL,
                           0);
        }
    }
}

int __usart_connect (void *p_drv)
{
    amdr_usart_dev_t *p_dev = (amdr_usart_dev_t *)p_drv;
    
 
    am_int_connect(p_dev->p_devinfo->inum, __usart_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    
    amhw_usart_int_enable(p_dev->p_devinfo->p_hw_usart, p_dev->other_int_enable);
    
    return AM_OK;
}

/**
 * \brief Initialize FIFO for USART
 * \param[in] p_fifo  : Pointer to the FIFO that to be initialized
 * \retval  AM_OK     : Initialize successful
 * \retval -AM_EINVAL : Invalid parameter
 */
int __usart_fifo_chan_init (const amdr_usart_fifo_info_t *p_fifo_info)
{
    
    amhw_fifo_t          *p_hw_usart = p_fifo_info->p_hw_fifo;
    amhw_fifo_usart_ch_t  chan       = p_fifo_info->usart_ch;
    amhw_fifo_cfg_t       usart_cfg;
    amhw_fifo_size_t      fifo_size;
    
    amhw_fifo_size_read(p_hw_usart, AMHW_FIFO_PERIPH_USART, &fifo_size);
        
    fifo_size.fifo_rxsize[chan] = p_fifo_info->rx_size;
    fifo_size.fifo_txsize[chan] = p_fifo_info->tx_size;
    
    /* Configure the FIFO size */
    if(amhw_fifo_size_cfg(p_hw_usart, AMHW_FIFO_PERIPH_USART, &fifo_size) != AM_OK) {
        return -AM_EINVAL;
    }

    usart_cfg.flags         = 0;
    usart_cfg.timeout_base  = p_fifo_info->timeout_base;
    usart_cfg.timeout_value = p_fifo_info->timeout_value;
    
    /* FIFO TX threshold interrupt on half FIFO level */
    usart_cfg.rx_threshold  = p_fifo_info->rx_size / 2;
    
    /* FIFO RX threshold interrupt on half FIFO level */
    usart_cfg.tx_threshold  = p_fifo_info->tx_size / 2;
    
    if (amhw_fifo_usart_cfg(p_hw_usart, chan, &usart_cfg) != AM_OK) {
        return -AM_EINVAL;
    }

    /* Unpause FIFOs after configuration */
    amhw_fifo_restart(p_hw_usart, AMHW_FIFO_PERIPH_USART, AMHW_FIFO_RX);
    amhw_fifo_restart(p_hw_usart, AMHW_FIFO_PERIPH_USART, AMHW_FIFO_TX);
    
    /* Flush UART FIFOs */
    amhw_fifo_usart_flush(p_hw_usart, chan, (AMHW_FIFO_CTRL_RXFLUSH | 
                                             AMHW_FIFO_CTRL_TXFLUSH));
                                     
    return AM_OK;
}

/**
 * \brief dummy callback routine.
 *
 * \returns AW_ERROR, always
 */
static int __usart_dummy_callback (void *p_arg, char *p_outchar)
{
    return (AM_ERROR);
}

am_uart_handle_t amdr_usart_init (amdr_usart_dev_t           *p_dev,
                                  const amdr_usart_devinfo_t *p_devinfo)
{
    amhw_usart_t           *p_hw_usart;
    amdr_usart_fifo_info_t *p_fifo_info;
    uint32_t                tmp;
    
    if (p_devinfo == NULL || p_devinfo->p_hw_usart == NULL) {
        return NULL;
    }
    
    p_hw_usart               = p_devinfo->p_hw_usart;
    p_fifo_info              = (amdr_usart_fifo_info_t *)&(p_devinfo->fifo_info);
    p_dev->p_devinfo         = p_devinfo;
    p_dev->uart_serv.p_funcs = (struct am_uart_drv_funcs *)&__g_uart_drv_funcs;
    p_dev->uart_serv.p_drv   = p_dev; 
    p_dev->baud_rate         = p_devinfo->baud_rate;
    p_dev->options           = 0;    
    
    p_dev->pfn_txchar_get    = (int (*) (void *, char*))__usart_dummy_callback;
    p_dev->txget_arg         = NULL;
    p_dev->pfn_rxchar_put    = (int (*) (void *, char ))__usart_dummy_callback;
    p_dev->rxput_arg         = NULL;
    p_dev->pfn_err           = (int (*) (void *, int, void*, int))__usart_dummy_callback;
    p_dev->err_arg           = NULL;

    p_dev->other_int_enable = p_devinfo->other_int_enable & 
                             ~(AMHW_USART_INT_TXRDY | AMHW_USART_INT_TXIDLE);
    
    if (p_fifo_info->tx_size != 0 || p_fifo_info->rx_size != 0) {
        
        if( __usart_fifo_chan_init(p_fifo_info) != AM_OK) {
            return NULL;
        }
    }
    
    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 2) & 0x03;
    
    switch (tmp) {
    case 0:
        p_dev->options |= AM_UART_CS7;
        break;
        
    case 1:
        p_dev->options |= AM_UART_CS8;
        break;
        
    default:
        p_dev->options |= AM_UART_CS8;
        break;
    }

    tmp = p_devinfo->cfg_flags;
    tmp = (tmp >> 4) & 0x03;
    
    if (tmp == 2) {
        p_dev->options |= AM_UART_PARENB;
    } else if (tmp == 3) {
        p_dev->options |= (AM_UART_PARENB | AM_UART_PARODD);
    }
    
    if (p_devinfo->cfg_flags & AMHW_USART_CFG_STOP_2) {
        p_dev->options |= AM_UART_STOPB;
    }
    
    amhw_usart_config(p_hw_usart, p_devinfo->cfg_flags);
    amhw_usart_control(p_hw_usart, p_devinfo->ctl_flags);
    
    p_dev->baud_rate = amhw_usart_baudrate_set(p_dev->p_devinfo->p_hw_usart,
                                               amhw_clock_usart_baseclkrate_get(),
                                               p_devinfo->baud_rate);
    
    __usart_mode_set(p_dev, AM_UART_MODE_POLL);  /* The Initialize mode is poll */
    
    amhw_usart_enable(p_hw_usart);               /* Enable USART */
    
    return &(p_dev->uart_serv);
}

void amdr_usart_deinit (amdr_usart_dev_t *p_dev)
{
    amhw_usart_t           *p_hw_usart;
    amdr_usart_fifo_info_t *p_fifo_info = (amdr_usart_fifo_info_t *)&(p_dev->p_devinfo->fifo_info);
    amdr_usart_fifo_info_t  fifo_info;

    p_dev->uart_serv.p_funcs = NULL;
    p_dev->uart_serv.p_drv   = NULL; 

    if (p_fifo_info->tx_size != 0 || 
        p_fifo_info->rx_size != 0) {

        fifo_info.p_hw_fifo     = p_fifo_info->p_hw_fifo;
        fifo_info.usart_ch      = p_fifo_info->usart_ch;
        fifo_info.tx_size       = 0;
        fifo_info.rx_size       = 0;
        fifo_info.timeout_base  = p_fifo_info->timeout_base;
        fifo_info.timeout_value = p_fifo_info->timeout_value;
        
        /* Release the FIFO resource */
        __usart_fifo_chan_init(&fifo_info);
    }
        
    if (p_dev->channel_mode == AM_UART_MODE_INT) {
        __usart_mode_set(p_dev, AM_UART_MODE_POLL);  /* The default mode is poll */
    }

    amhw_usart_disable(p_hw_usart);                  /* Disable USART */
    
    am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */

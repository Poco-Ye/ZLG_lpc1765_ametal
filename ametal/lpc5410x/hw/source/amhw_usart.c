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
 * \brief USART implementation for operating hardware.
 * 
 * - 7, 8, or 9 data bits and 1 or 2 stop bits
 * - Synchronous mode with master or slave operation. Includes data phase 
 *   selection and continuous clock option.
 * - Multiprocessor/multidrop (9-bit) mode with software address compare.
 * - RS-485 transceiver output enable.
 * - Parity generation and checking: odd, even, or none.
 * - Software selectable oversampling from 5 to 16 clocks in asynchronous mode.
 * - One transmit and one receive data buffer.
 * - FIFO support from the System FIFO 
 * - RTS/CTS for hardware signaling for automatic flow control. Software flow 
 *   control can be performed using Delta CTS detect, Transmit Disable control, 
 *    and any GPIO as an RTS output.
 * - Received data and status can optionally be read from a single register.
 * - Break generation and detection.
 * - Receive data is 2 of 3 sample "voting". Status flag set when one sample differs.
 * - Built-in Baud Rate Generator with auto-baud function.
 * - A fractional rate divider is shared among all USARTs.
 * - Interrupts available for Receiver Ready, Transmitter Ready, Receiver Idle, 
 *   change in receiver break detect, Framing error, Parity error, Overrun, 
 *   Underrun, Delta CTS detect, and receiver sample noise detected.
 * - Loopback mode for testing of data and flow control.
 * - USART transmit and receive functions can operated with the system DMA controller.
 * - Special operating mode allows operation at up to 9600 baud using the 32 kHz 
 *   RTC oscillator as the USART clock. This modecan be used while the device is in 
 *   Power-down mode and can wake-up the device when a character is received.
 * - USART transmit and receive functions can be operated with the system DMA controller.
 *
 * \internal
 * \par Modification History
 * - 1.01 14-12-03  jon, add USART interrupt mode.
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
 
#include "amhw_usart.h"
 
/*******************************************************************************
  Public functions
*******************************************************************************/

/**
 * \brief Calculate error difference
 */
static int32_t __err_cal (uint32_t  u_clk, 
                          uint32_t  baudrate, 
                          uint32_t *p_prev_err)
{
    uint32_t err  = u_clk - (u_clk / baudrate) * baudrate;
    
    uint32_t herr = ((u_clk / baudrate) + 1) * baudrate - u_clk;
    
    if (herr < err) {
        err = herr;
    }
    
    /* If the previous error is smaller than now error */
    if (*p_prev_err <= err) {  
        return 0;
    }
    
    *p_prev_err = err;
    
    /*
     * 1: herr != err ( init err < herr)  
     * 2: herr == err ( init err > herr)
     */                           
    return (herr == err) + 1;
}

/**
 * \brief Calculate the base DIV value
 */
static int __usart_div_cal (uint32_t  u_clk,
                            uint32_t *p_baudrate,
                            uint32_t *p_div,
                            uint32_t *p_oversamples)
{
    uint32_t ovr     = 0;
    uint32_t pre_err = ~0UL; /* The previous err. Init with the largest value */
    uint32_t div     = 0;
    
    uint32_t oversamples = *p_oversamples;

    /*
     * Find the best over samples 
     */    
    if (oversamples == 0) {
        for (ovr = 16; ovr > 4; ovr--) {
            int32_t tmp = __err_cal(u_clk, *p_baudrate * ovr, &pre_err);

            /*
             * Continue when no improvement seen in err value 
             */
            if (!tmp) {
                continue;
            }

            div         = tmp - 1;
            oversamples = ovr;
        }
    }
    
    /* over samples is not valid. return error */
    if (!oversamples) {             
        return -AM_EINVAL;
    }

    div += u_clk / (*p_baudrate * oversamples);
    
    /* Divider is not valid. Return error */
    if (!div) {                         
        return -AM_EINVAL;
    }
    
    *p_div         = div;
    *p_baudrate    = u_clk / (div * oversamples);         /* Actual baud rate */
    *p_oversamples = oversamples;
    
    return AM_OK;
}

/**
 * \brief Set USART baudrate
 */
int amhw_usart_baudrate_set (amhw_usart_t *p_hw_usart,
                             uint32_t      u_clk, 
                             uint32_t      baudrate)
{
    uint32_t div         = 0;
    uint32_t oversamples = 0;   /* automatic find best over samples */
    
    uint32_t err, herr;
 
    if ((p_hw_usart->cfg & AMHW_USART_CFG_MODE32K) != 0) {
        u_clk = 32768;
    }
    
    if (u_clk == 32768) {       /* The USART use the 32K Mode                 */
        if (baudrate > 9600) {  /* In this mode,The maximum baud rate is 9600 */
            return -AM_EINVAL;
        } else {
            div  = 9600 / baudrate;
            
            err  = 9600 - baudrate * div;
            herr = (div + 1) * baudrate - 9600;

            if (err > herr) {
               div = div + 1;
            }
            p_hw_usart->brg = div - 1;
            
            /* The actual buad rate */
            return (9600 / (div - 1));                 
        }
    } else {
        if (__usart_div_cal(u_clk, &baudrate, &div, &oversamples) == -1) {
            return -AM_EINVAL;
        }
    }

    p_hw_usart->osr = (oversamples - 1) & 0x0F;
    p_hw_usart->brg = (div - 1) & 0xFFFF;

    return baudrate;
}

/**
 * \brief USART send data(poll mode)
 *
 * \param[in] handle  : The UART handle
 * \param[in] p_txbuf : The transmit buffer
 * \param[in] nbytes  : The number bytes to transmit
 * 
 * \return The number bytes transmit successful
 */
int amhw_usart_poll_send (amhw_usart_t  *p_hw_usart,
                          const uint8_t *p_txbuf,
                          uint32_t       nbytes)
{
    uint32_t len = nbytes;
    
    while (len--) {
        while ((p_hw_usart->stat & AMHW_USART_STAT_TXRDY) == 0);
        amhw_usart_txdata_write(p_hw_usart, (uint32_t)(*p_txbuf++));
    }
    
    return nbytes;
}
                            

/**
 * \brief USART receive data(poll mode)
 *
 * \param[in] handle  : The UART handle
 * \param[in] p_rxbuf : The receive buffer
 * \param[in] nbytes  : The number bytes to receive
 * 
 * \return The number bytes received successful
 */
int amhw_usart_poll_receive (amhw_usart_t *p_hw_usart,
                             uint8_t      *p_rxbuf,
                             uint32_t      nbytes)
{
    uint32_t len = nbytes;
    
    while (len--) {
        while((p_hw_usart->stat & AMHW_USART_STAT_RXRDY) == 0);
        *p_rxbuf++ = amhw_usart_rxdata_read(p_hw_usart);
    }
    
    return nbytes;
}

/* end of file */

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
 * \brief UART(使用ring buffer的中断模式)标准接口
 *
 * 该文件函数接口的实现基于UART标准接口，为方便用户使用设计，可作为UART接口函数
 * 的使用范例。
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_UART_RINGBUF_H
#define __AM_UART_RINGBUF_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "am_ringbuf.h"

/**
 * \addtogroup am_if_uart_ringbuf
 * \copydoc am_uart_ringbuf.h
 * @{
 */

/**
 * \brief UART（带ring buffer的中断模式）设备结构体
 */
typedef struct am_uart_ringbuf_dev {

    /** \brief UART标准服务操作句柄 */
    am_uart_handle_t  handle;

    /** \brief 接收数据环形缓冲区   */
    am_ringbuf_t      rx_ringbuf;

    /** \brief 发送数据环形缓冲区   */
    am_ringbuf_t      tx_ringbuf;
} am_uart_ringbuf_dev_t;

/** \brief UART（带ring buffer的中断模式）标准服务操作句柄类型定义 */
typedef struct am_uart_ringbuf_dev * am_uart_ringbuf_handle_t;


/**
 * \brief 初始化UART为带ring buffer的中断模式
 *
 * \param[in] p_dev      : UART（带ring buffer的中断模式）设备结构体指针
 * \param[in] handle     : UART标准服务操作句柄
 * \param[in] p_rxbuf    : 指向接收缓冲区的指针，用于实现接收环形缓冲区
 * \param[in] rxbuf_size : 接收缓冲区的大小
 * \param[in] p_txbuf    : 指向发送缓冲区的指针，用于实现发送环形缓冲区
 * \param[in] txbuf_size : 发送缓冲区的大小
 *
 * \return UART（带ring buffer的中断模式）标准服务操作句柄，如果值为NULL，表明初
 *         始化失败
 */
am_uart_ringbuf_handle_t am_uart_ringbuf_init(am_uart_ringbuf_dev_t *p_dev,
                                              am_uart_handle_t       handle,
                                              char                  *p_rxbuf,
                                              uint32_t               rxbuf_size,
                                              char                  *p_txbuf,
                                              uint32_t               txbuf_size);

/**
 * \brief UART数据发送（带ring buffer的中断模式）
 *
 * \param[in] handle  : UART（带ring buffer的中断模式）标准服务操作句柄
 * \param[in] p_txbuf : 发送数据缓冲区
 * \param[in] nbytes  : 待发送数据的个数
 * 
 * \return 成功发送数据的个数
 */
int am_uart_ringbuf_send(am_uart_ringbuf_handle_t  handle,
                         const uint8_t            *p_txbuf,
                         uint32_t                  nbytes);

/**
 * \brief UART数据接收（带ring buffer的中断模式）
 *
 * \param[in] handle  : UART（带ring buffer的中断模式）标准服务操作句柄
 * \param[in] p_rxbuf : 接收数据缓冲区
 * \param[in] nbytes  : 待接收数据的个数
 *
 * \return 成功接收数据的个数
 */
int am_uart_ringbuf_receive(am_uart_ringbuf_handle_t  handle,
                            uint8_t                  *p_rxbuf,
                            uint32_t                  nbytes);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_UART_RINGBUF_H */

/* end of file */

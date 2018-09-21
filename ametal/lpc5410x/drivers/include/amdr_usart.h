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
 * \brief USART驱动，服务UART标准接口
 *
 * \internal
 * \par Modification History
 * - 1.01 14-12-03  jon, add USART interrupt mode.
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_USART_H
#define __AMDR_USART_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "amhw_usart.h"
#include "amhw_fifo.h"

/**
 * \addtogroup amdr_if_usart
 * \copydoc amdr_usart.h
 * @{
 */

/**
 * \name 错误编码号，错误回调函数的code参数，由驱动传递给用户，指明当前的错误类型
 *
 *  错误回调函数的参数原型：\n
 *  int uart_err(void *p_arg, int code, void *p_data, int size);
 *  p_arg是用户注册的用户参数。p_data和size不同的错误类型包含的信息有所不同。
 *  可以使用am_uart_callback_set() 函数设置串口错误回调函数。
 * @{
 */

/** \brief 串口FIFO总线错误，p_data不包含信息，为NULL,size的值为0 */
#define AMDR_UART_ERRCODE_FIFO_BUSERR      1

/**
 * \brief 用户指定的其它中断发生,p_data的类型为uint32_t，值为串口的中断状态，方
 *        便用户判断具体的中断源，size为1。
 */
#define AMDR_UART_ERRCODE_USART_OTHER_INT  2

/** @} */

/**
 * \brief 串口FIFO信息结构体
 */
typedef struct amdr_usart_fifo_info {

    amhw_fifo_t          *p_hw_fifo;   /**< \brief 指向系统FIFO寄存器块的指针 */
    amhw_fifo_usart_ch_t  usart_ch;    /**< \brief FIFO中串口对应使用的通道号 */

    /**
     * \brief 用于串口接收的FIFO大小，所有的串口使用的FIFO接收大小之和不能超过16。
     *        该值为0表明不使用串口接收FIFO。
     */
    uint8_t   rx_size;

    /**
     * \brief 用于串口发送的FIFO大小，所有的串口使用的FIFO发送大小之和不能超过16。
     *        该值为0表明不使用串口发送FIFO。
     */
    uint8_t   tx_size;

    /**
     * \brief FIFO接收超时设置，超时时钟个数为：2 ^ timeout_base * timeout_value
     *        有效值为 0 ~ 15
     */
    uint8_t   timeout_base;

    /**
     * \brief FIFO接收超时设置，超时时钟个数为：2 ^ timeout_base * timeout_value
     *        有效值为 2 ~ 15
     */
    uint8_t   timeout_value;

} amdr_usart_fifo_info_t;

/**
 * \brief 串口设备信息结构体，该设备信息用于串口初始化
 */
typedef struct amdr_usart_devinfo {

    amhw_usart_t *p_hw_usart;       /**< \brief 指向USART寄存器块的指针       */

    uint8_t      inum;              /**< \brief 串口中断号                    */

    /**
     * \brief 串口配置标志，AMHW_USART_CFG_*宏或多个AMHW_USART_CFG_*宏的或值
     *        (如：#AMHW_USART_CFG_8BIT)
     */
    uint32_t     cfg_flags;

    /**
     * \brief 串口控制标志，AMHW_USART_CTL_*宏或多个AMHW_USART_CTL_*宏的或值
     *        (如：#AMHW_USART_CTL_ADDRDET)
     */
    uint32_t     ctl_flags;
    uint32_t     baud_rate;           /**< \brief 初始化波特率                */

    /**
     * \brief 指定使能的其它中断,AMHW_USART_INT_*宏值或多个AMHW_USART_INT_*宏的
     *        或值，除了(#AMHW_USART_INT_RXRDY),(#AMHW_USART_INT_TXRDY) and
     *        (#AMHW_USART_INT_TXIDLE)这三个中断。
     */
    uint32_t other_int_enable;

    amdr_usart_fifo_info_t fifo_info; /**< \brief 串口使用的FIFO信息          */

} amdr_usart_devinfo_t;

/**
 * \brief 串口设备结构体定义
 */
typedef struct amdr_usart_dev {

    am_uart_serv_t  uart_serv;                /**< \brief 标准UART服务        */

    int (*pfn_txchar_get)(void *, char *);    /**< \brief 指向用户注册的txchar_get函数 */
    int (*pfn_rxchar_put)(void *, char);      /**< \brief 指向用户注册的rxchar_put函数 */
    int (*pfn_err)(void *, int, void *, int); /**< \brief 指向用户注册的错误回调函数   */

    void     *txget_arg;                      /**< \brief txchar_get函数参数     */
    void     *rxput_arg;                      /**< \brief rxchar_put函数参数     */
    void     *err_arg;                        /**< \brief 错误回调函数用户参数   */

    uint8_t   channel_mode;                   /**< \brief 串口模式 中断/查询     */
    uint32_t  baud_rate;                      /**< \brief 串口波特率             */
    uint16_t  options;                        /**< \brief 硬件设置选项           */

    uint32_t  other_int_enable;               /**< \brief 指定使能的其它中断     */

    const amdr_usart_devinfo_t *p_devinfo;    /**< \brief 指向设备信息常量的指针 */

} amdr_usart_dev_t;

/**
 * \brief 初始化USART，返回UART标准服务操作句柄
 *
 * \param[in] p_dev     : 指向串口设备的指针
 * \param[in] p_devinfo : 指向串口设备信息常量的指针
 *
 * \return UART标准服务操作句柄，值为NULL时表明初始化失败
 */
am_uart_handle_t amdr_usart_init(amdr_usart_dev_t           *p_dev,
                                 const amdr_usart_devinfo_t *p_devinfo);

/**
 * \brief 不使用USART时，解初始化USART，释放相关资源
 * \param[in] p_dev : 指向串口设备的指针
 * \return 无
 */
void amdr_usart_deinit(amdr_usart_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_USART_H */

/* end of file */

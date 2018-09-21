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
 * \brief 串行外设的FIFO硬件操作接口
 *
 * 1. 所有的串口和SPI执行发送和接收在一个设备上,
 *    支持软件或者DMA对每个外设进行接收发送操作；
 * 2. FIFO提供了附加定时功能，可以在连接DMA时用于扩展；
 * 3. 每个外设提供了独立的缓存空间，用户可通过软件设置自行分配， 
 *    串口有16发送FIFO入口和16个接收FIFO入口，SPI有8个发送FIFO入口和8个接收FIFO入口；
 * 4. 在较低速情况下系统FIFO可作为APB外设，并且在AHB时钟速率下允许CPU或DMA处理数据，
 *    对于失速情况下，无论速率大小，外设总线时钟都在运行；
 * 5. 每个外设的接收和发送FIFO，都可以通过软件设置阈值，范围1至FIFO为满的数值；
 * 6. 每个外设的接收和发送FIFO提供了FIFO入口数量，范围0-FIFO入口最大值；
 * 7. 对于外设接收和发送数据有效，系统FIFO提供状态标志，可用于产生中断或者发送信号给系统DMA；
 * 8. 对于得到数据一段时间后还未达到FIFO的阈值，系统FIFO提供了超时处理功能。
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


#define  AMHW_FIFO_USART_MAX     (0x04)          /**< \brief 串口的最大编号 */
#define  AMHW_FIFO_SPI_MAX       (0x02)          /**< \brief SPI的最大编号  */

/**
 * \brief FIFO外设的公共寄存器块结构体
 */
typedef struct amhw_fifo_comm {
    __I  uint32_t  reserved[64];       /**< \brief 保留                   */
    __IO uint32_t  fifoctlusart;       /**< \brief 串口FIFO控制寄存器     */
    __O  uint32_t  fifoupdateusart;    /**< \brief 串口FIFO大小更新寄存器 */
    __I  uint32_t  reserved1[2];       /**< \brief 保留                   */

    /** \brief 串口FIFO的配置寄存器 */
    __IO uint32_t  fifocfgusart[AMHW_FIFO_USART_MAX];

    __I  uint32_t  reserved2[56];      /**< \brief 保留                     */
    __IO uint32_t  fifoctlspi;         /**< \brief SPI的FIFO控制寄存器      */
    __O  uint32_t  fifoupdatespi;      /**< \brief SPI的FIFO大小更新寄存器  */
    __I  uint32_t  reserved3[2];       /**< \brief 保留                     */

    /** \brief SPI的FIFO的配置寄存器 */
    __IO uint32_t  fifocfgspi[AMHW_FIFO_SPI_MAX];

    __I  uint32_t  reserved4[890];     /**< \brief 保留                     */
}amhw_fifo_comm_t;

/**
 * \brief 串口相关的FIFO寄存器结构体
 */
typedef struct amhw_fifo_usart {
    __IO uint32_t  cfg;                /**< \brief USART 配置寄存器 */
    __IO uint32_t  stat;               /**< \brief USART 状态寄存器 */
    __I  uint32_t  intstat;            /**< \brief USART 中断状态寄存器         */
    __IO uint32_t  ctlset;             /**< \brief USART 置位相关中断位寄存器   */
    __O  uint32_t  ctlclr;             /**< \brief USART 清除相关中断位寄存器   */
    __I  uint32_t  rxdat;              /**< \brief USART 接收数据寄存器         */
    __I  uint32_t  rxdatstat;          /**< \brief USART 接收数据及其状态寄存器 */
    __O  uint32_t  txdat;              /**< \brief USART 发送数据寄存器         */
    __I  uint32_t  reserved5[56];      /**< \brief 保留             */
}amhw_fifo_usart_t;

/**
 * \brief SPI相关的FIFO寄存器结构体
 */
typedef struct amhw_fifo_spi {
    __IO uint32_t  cfg;                /**< \brief SPI 配置寄存器 */
    __IO uint32_t  stat;               /**< \brief SPI 状态寄存器 */
    __I  uint32_t  intstat;            /**< \brief SPI 中断状态寄存器         */
    __IO uint32_t  ctlset;             /**< \brief SPI 置位相关中断位寄存器   */
    __O  uint32_t  ctlclr;             /**< \brief SPI 清除相关中断位寄存器   */
    __I  uint32_t  rxdat;              /**< \brief SPI 接收数据寄存器         */
    __O  uint32_t  txdat;              /**< \brief SPI 发送数据寄存器         */
    __I  uint32_t  reserved9[57];      /**< \brief 保留           */
}amhw_fifo_spi_t;

/**
 * \brief FIFO寄存器块结构体
 */
typedef struct amhw_fifo {
    
    /** \brief FIFO外设的公共寄存器块结构体 */  
    amhw_fifo_comm_t  common;
    
    /** \brief 串口相关的FIFO寄存器结构体 */
    amhw_fifo_usart_t usart[AMHW_FIFO_USART_MAX]; 
    
    /** \brief 保留 */
    __I  uint32_t     reserved[768];
    
    /** \brief SPI相关的FIFO寄存器结构体 */
    amhw_fifo_spi_t   spi[AMHW_FIFO_SPI_MAX];
} amhw_fifo_t;

/**
 * \name FIFO状态位定义
 * @{
 */
#define AMHW_FIFO_STAT_RXTH       (1 << 0)   /**< \brief 达到接收FIFO阈值 */
#define AMHW_FIFO_STAT_TXTH       (1 << 1)   /**< \brief 达到发送FIFO阈值 */
#define AMHW_FIFO_STAT_RXTIMEOUT  (1 << 4)   /**< \brief 接收FIFO超时     */
#define AMHW_FIFO_STAT_BUSERR     (1 << 7)   /**< \brief 总线错误         */
#define AMHW_FIFO_STAT_RXEMPTY    (1 << 8)   /**< \brief 接收FIFO为空 */
#define AMHW_FIFO_STAT_TXEMPTY    (1 << 9)   /**< \brief 发送FIFO为空 */

/** @} */

/**
 * \brief 串口FIFO的控制位及中断定义
 * @{
 */

#define AMHW_FIFO_INT_RXTH       (1 << 0)  /**< \brief 接收FIFO达到阈值中断 */
#define AMHW_FIFO_INT_TXTH       (1 << 1)  /**< \brief 发送FIFO达到阈值中断 */
#define AMHW_FIFO_INT_RXTIMEOUT  (1 << 4)  /**< \brief 接收FIFO超时中断     */

#define AMHW_FIFO_CTRL_RXFLUSH   (1 << 8)  /**< \brief 接收FIFO清除 */
#define AMHW_FIFO_CTRL_TXFLUSH   (1 << 9)  /**< \brief 发送FIFO清除 */

/** @} */


/**
 * \name FIFO中断事件定义
 * @{
 */
#define AMHW_FIFO_EVENT_RX_TH         0x01  /**< \brief 发生接收FIFO达到阈值中断事件  */
#define AMHW_FIFO_EVENT_RX_EMPTY      0x02  /**< \brief 发生接收FIFO为空事件 */
#define AMHW_FIFO_EVENT_TX_TH         0x04  /**< \brief 发生发送FIFO达到阈值中断事件  */
#define AMHW_FIFO_EVENT_TX_EMPTY      0x08  /**< \brief 发生发送FIFO为空事件 */
#define AMHW_FIFO_EVENT_BUS_ERROR     0x10  /**< \brief 发生总线错误事件     */
/** @} */

/**
 * \brief 串口FIFO的通道号定义
 */
typedef enum amhw_fifo_usart_ch {
    AMHW_FIFO_USART0 = 0,          /**< \brief 串口FIFO通道0 */
    AMHW_FIFO_USART1,              /**< \brief 串口FIFO通道1 */
    AMHW_FIFO_USART2,              /**< \brief 串口FIFO通道2 */
    AMHW_FIFO_USART3,              /**< \brief 串口FIFO通道3 */
} amhw_fifo_usart_ch_t;

/**
 * \brief FIFO外设类型定义
 */
typedef enum amhw_fifo_periph {
    AMHW_FIFO_PERIPH_USART = 0,               /**< \brief 串口FIFO */
    AMHW_FIFO_PERIPH_SPI                      /**< \brief SPI FIFO */
} amhw_fifo_periph_t;

/**
 * \brief FIFO方向
 */
typedef enum amhw_fifo_dir {
    AMHW_FIFO_TX = 0,                         /**< \brief FIFO 发送 */
    AMHW_FIFO_RX                              /**< \brief FIFO 接收 */
} amhw_fifo_dir_t;

/**
 * \brief 外设FIFO大小设定结构体
 */
typedef struct amhw_fifo_size {
    uint16_t fifo_rxsize[4]; /**< \brief 接收FIFO大小, 0-3 对应串口0-3,  0-1 对应SPI(0-1) */
    uint16_t fifo_txsize[4]; /**< \brief 发送FIFO大小, 0-3 对应串口0-3,  0-1 对应SPI(0-1) */
} amhw_fifo_size_t;

/**
 * \brief 获取FIFO余下的空间大小
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] periph_id : 外设id定义
 * \param[in] dir       : FIFO操作的方向
 *
 * \return  对应外设的FIFO余下的空间
 */
uint32_t amhw_fifo_space_get(amhw_fifo_t        *p_hw_fifo,
                             amhw_fifo_periph_t  periph_id,
                             amhw_fifo_dir_t     dir);

/**
 * \brief 暂停一个外设的FIFO
 *
 * \param[in] p_hw_fifo : 
 * \param[in] periph_id : 
 * \param[in] dir       : 
 *
 * \return    无
 */
void amhw_fifo_pause(amhw_fifo_t         *p_hw_fifo,
                     amhw_fifo_periph_t   periph_id,
                     amhw_fifo_dir_t      dir);

/**
 * \brief 重新启动一个外设的FIFO
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] periph_id : 外设id定义
 * \param[in] dir       : FIFO操作的方向
 *
 * \return    无
 */
void amhw_fifo_restart(amhw_fifo_t        *p_hw_fifo,
                       amhw_fifo_periph_t  periph_id,
                       amhw_fifo_dir_t     dir);

/**
 * \brief 读取外设FIFO的大小 
 *
 * \param[in]  p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in]  periph_id : 外设id定义
 * \param[out] p_size    : 指向外设FIFO大小设定结构体的指针
 *
 * \retval  AM_OK   : 读取完成
 */
int amhw_fifo_size_read(amhw_fifo_t        *p_hw_fifo,
                        amhw_fifo_periph_t  periph_id,
                        amhw_fifo_size_t   *p_size);

/**
 * \brief 配置外设FIFO大小
 *
 * \param[in]  p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in]  periph_id : 外设id定义
 * \param[out] p_size    : 指向外设FIFO大小设定结构体的指针
 *
 * \retval  AM_OK      : 配置成功
 * \retval -AM_EINVAL  : 参数无效
 *
 * \note 调用一次该函数，可配置一个外设所有的FIFO大小,
 *       调用amhw_fifo_restart()之后才可调用该函数
 
*/
int amhw_fifo_size_cfg(amhw_fifo_t        *p_hw_fifo,
                       amhw_fifo_periph_t  periph_id,
                       amhw_fifo_size_t   *p_size);

/**
 * \brief FIFO外设配置定义
 * @{
 */

/**
 * \brief 当写入数据进入到接收FIFO，相应的外设不复位而引起的超时
 */
#define AMHW_FIFO_CFG_TIMEOUTCONTONWRITE   (1 << 4)

/**
 * \brief 当接收FIFO为空，相应的外设不复位而引起的超时
 */
#define AMHW_FIFO_CFG_TIMEOUTCONTONEMPTY   (1 << 5)

/** @} */

/**
 * \brief 外设配置信息结构体
 */
typedef struct amhw_fifo_cfg {
    uint32_t  flags;         /**< \brief AMHW_FIFO_CFG_*的宏值或者多个
                                   AMHW_FIFO_CFG_*宏的或（or）值(#AMHW_FIFO_CFG_TIMEOUTCONTONWRITE) */
    uint8_t   timeout_base;  /**< \brief 0 ~ 15,超时的基值   */
    uint8_t   timeout_value; /**< \brief 2 ~ 15,超时的最大值 */
    uint32_t  rx_threshold;  /**< \brief 接收FIFO阈值        */
    uint32_t  tx_threshold;  /**< \brief 发送FIFO阈值        */
} amhw_fifo_cfg_t;

/**
 * \brief  串口FIFO的配置函数
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 * \param[in] p_cfg     : 指向配置信息结构体的指针
 *
 * \retval  AM_OK      : 配置完成
 * \retval -AM_EINVAL  : 参数无效
 */
int amhw_fifo_usart_cfg(amhw_fifo_t          *p_hw_fifo,
                        amhw_fifo_usart_ch_t  usart_ch,
                        amhw_fifo_cfg_t      *p_cfg);

/**
 * \brief 获取串口FIFO的状态
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 *
 * \return  AMHW_FIFO_STAT_*的宏值或者多个AMHW_FIFO_STAT_*宏的或（or）值(#AMHW_FIFO_STAT_RXTH)
 */
am_static_inline
uint32_t amhw_fifo_usart_stat_get (amhw_fifo_t          *p_hw_fifo,
                                   amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].stat);
}

/**
 * \brief 获取串口接收FIFO入口数量
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针   
 * \param[in] usart_ch  : 串口通道号               
 *
 * \return 串口可以接收FIFO的入口数. 0-FIFO为空
 */
am_static_inline
uint32_t amhw_fifo_usart_rxcount_get (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].stat >> 16) & 0xFF;
}

/**
 * \brief 获取串口发送FIFO的有效数量
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针 
 * \param[in] usart_ch  : 串口通道号 
 *
 * \return 串口可以发送FIFO的入口数. 0 = FIFO为满.
 */
am_static_inline
uint32_t amhw_fifo_usart_txcount_get (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].stat >> 24) & 0xFF;
}

/**
 * \brief 获取串口中断状态
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 *
 * \return  AMHW_FIFO_INT_*的宏值或者多个AMHW_FIFO_INT_*宏的或（or）值(#AMHW_FIFO_INT_RXTH)
 */
am_static_inline
uint32_t amhw_fifo_usart_intstat_get (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return (p_hw_fifo->usart[usart_ch].intstat);
}

/**
 * \brief 清除串口FIFO状态
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 * \param[in] clr_bits  : AMHW_FIFO_STAT_*的宏值或者多个AMHW_FIFO_STAT_*宏的或（or）值(#AMHW_FIFO_STAT_RXTH)
 *
 * \return 无
 *
 * \note 只有一些特定的状态位写1才能清除，例如AMHW_FIFO_STAT_RXTIMEOUT和AMHW_FIFO_STAT_BUSERR 
 */
am_static_inline
void amhw_fifo_usart_stat_clr (amhw_fifo_t          *p_hw_fifo,
                               amhw_fifo_usart_ch_t  usart_ch,
                               uint32_t              clr_bits)
{
    p_hw_fifo->usart[usart_ch].stat = clr_bits;
}

/**
 * \brief 使能串口FIFO中断
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 * \param[in] int_flags : AMHW_FIFO_INT_*的宏值或者多个AMHW_FIFO_INT_*宏的或（or）值(#AMHW_FIFO_INT_RXTH)
 *
 * \return 无
 */
am_static_inline
void amhw_fifo_usart_int_enable (amhw_fifo_t          *p_hw_fifo,
                                 amhw_fifo_usart_ch_t  usart_ch,
                                 uint32_t              int_flags)
{
    p_hw_fifo->usart[usart_ch].ctlset = int_flags;
}

/**
 * \brief 禁能串口FIFO中断
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 * \param[in] int_flags : AMHW_FIFO_INT_*的宏值或者多个AMHW_FIFO_INT_*宏的或（or）值(#AMHW_FIFO_INT_RXTH)
 *
 * \return 无
 */
am_static_inline
void amhw_fifo_usart_int_disable (amhw_fifo_t          *p_hw_fifo,
                                  amhw_fifo_usart_ch_t  usart_ch,
                                  uint32_t              int_flags)
{
    p_hw_fifo->usart[usart_ch].ctlclr = int_flags;
}

/**
 * \brief 清除串口接收/发送FIFO，使其变为空
 *
 * \param[in] p_hw_fifo   : 指向FIFO寄存器块的指针
 * \param[in] usart_ch    : 串口通道号
 * \param[in] flush_flags : FIFO清除标识位
                            例如：(#AMHW_FIFO_CTRL_RXFLUSH) and/or (#AMHW_FIFO_CTRL_TXFLUSH)
 * \return 无
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
 * \brief 写入一字节数据到串口FIFO发送数据寄存器
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 * \param[in] data      : 写入的数据
 *
 * \return 无
 */
am_static_inline
void amhw_fifo_usart_txdata_write (amhw_fifo_t          *p_hw_fifo,
                                   amhw_fifo_usart_ch_t  usart_ch,
                                   uint8_t               data)
{
    p_hw_fifo->usart[usart_ch].txdat = data;  
}

/**
 * \brief 读取一个字节数据从串口FIFO接收数据寄存器
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 *
 * \return 读取到的数据
 */
am_static_inline
uint32_t amhw_fifo_usart_rxdata_read (amhw_fifo_t          *p_hw_fifo,
                                      amhw_fifo_usart_ch_t  usart_ch)
{
    return p_hw_fifo->usart[usart_ch].rxdat;
}


/**
 * \brief 写入一组数据到串口FIFO
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 * \param[in] p_txbuf   : 发送的数据缓存
 * \param[in] nbytes    : 缓存的数据长度
 *
 * \return 写入到FIFO的数据长度
 */
uint32_t amhw_fifo_usart_write_data(amhw_fifo_t          *p_hw_fifo,
                                    amhw_fifo_usart_ch_t  usart_ch,
                                    uint8_t              *p_txbuf,
                                    uint32_t              nbytes);


/**
 * \brief 读取数据从串口FIFO
 *
 * \param[in] p_hw_fifo : 指向
 * \param[in] usart_ch  : 串口通道号
 * \param[in] p_rxbuf   : 接收数据缓存
 * \param[in] nbytes    : 缓存的数据长度
 *
 * \return 从FIFO中读取到的数据长度
 */
uint32_t amhw_fifo_usart_read_data(amhw_fifo_t          *p_hw_fifo,
                                   amhw_fifo_usart_ch_t  usart_ch,
                                   uint8_t              *p_rxbuf,
                                   uint32_t              nbytes);

/**
 * \name 接收FIFO数据的状态位定义
 * @{
 */

#define AMHW_FIFO_USART_RXDATA_FRAMHERR   (1 << 13)  /**< \brief 数据帧错误状态  */
#define AMHW_FIFO_USART_RXDATA_PARITYERR  (1 << 14)  /**< \brief 极性错误状态    */
#define AMHW_FIFO_USART_RXDATA_RXNOISE    (1 << 15)  /**< \brief 接收干扰状态 */

/** @} */

/**
 * \brief 读数据和状态从系统FIFO
 *
 * \param[in] p_hw_fifo : 指向FIFO寄存器块的指针
 * \param[in] usart_ch  : 串口通道号
 * \param[in] p_buf     : 接收数据缓存
 * \param[in] nbytes    : 缓存的数据长度
 *
 * \return 从FIFO中读取到的数据长度   
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

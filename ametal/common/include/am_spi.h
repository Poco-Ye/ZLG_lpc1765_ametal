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
 * \brief SPI标准接口
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_SPI_H
#define __AM_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    

#include "am_common.h"


/**
 * \addtogroup am_if_spi
 * \copydoc am_spi.h
 * @{
 */

/**
 * \name SPI配置标志，用于am_spi_config()的配置信息中的 cfg_flags参数
 * @{
 */

#define AM_SPI_CFG_CPHA         0x01  /**< \brief 时钟相位可设置            */
#define AM_SPI_CFG_CPOL         0x02  /**< \brief 时钟极性可设置            */
#define AM_SPI_CFG_LSB_FIRST    0x08  /**< \brief 按低位先出的方式发送数据帧 */
#define AM_SPI_CFG_3WIRE        0x10  /**< \brief 3线模式，SI/SO 信号线共享 */
#define AM_SPI_CFG_LOOP         0x20  /**< \brief 回环模式                  */
#define AM_SPI_CFG_READY        0x80  /**< \brief READY信号,从机拉低此信号暂停传输 */

/** \brief SPI模式0    */
#define AM_SPI_CFG_MODE_0   (0 | 0)

/** \brief SPI模式1 */
#define AM_SPI_CFG_MODE_1   (0 | AM_SPI_CFG_CPHA)

/** \brief SPI模式2 */
#define AM_SPI_CFG_MODE_2   (AM_SPI_CFG_CPOL | 0)

/** \brief SPI模式3 */
#define AM_SPI_CFG_MODE_3   (AM_SPI_CFG_CPOL | AM_SPI_CFG_CPHA)

/** \brief SPI在读取过程中MOSI引脚输出高电平（默认为低电平）*/
#define AM_SPI_CFG_READ_MOSI_HIGH    0x01

/** @} */
    
/**
 * \name 特殊控制标识,用于 am_spi_mktrans() 的 flags参数
 * @{
 */
 
/**
 * \brief 当该传输是一系列传输的最后一个传输（置SSEL信号为无效状态前的传输）
 *        应该设置该标志位
 */
#define AM_SPI_TRANS_EOT       0x1000

/** @} */

/**
 * \brief SPI 传输
 *
 * - SPI 传输写的个数总是等于读的个数。协议驱动应该总是提供 \a rx_buf 和/或
 * \a tx_buf 。在某些情况下，它们同样可能想提供数据传输的DMA地址，这样的话，底
 * 层驱动可以使用DMA，以降低数据传输的代价。
 *
 * - 如果传输缓冲区\a tx_buf 为NULL，则在填充\a rx_buf 时，0将会被移出到总线上。
 * 如果接收缓冲区 \a rx_buf 为NULL，则从总线上移入的数据将会被丢弃。只有 \a len
 * 个字节会被移出或移入。尝试移出部分字是错误的操作，例如，移出3个字节而字大小
 * 是 16 或 20 bit，前者每个字使用2个字节，而后者使用4个字节。
 *
 * - 在内存中，数据总是按CPU的的本地字节顺序存放，以线字节顺序传输 (即大端，除非
 * 设备模式或传输标志中被设置了 AW_SPI_CFG_LSB_FIRST)。例如，当\a bits_per_word 为
 * 16，缓冲区为 2N 字节长 (\a len = 2N) 并且以CPU字节顺便保存N个16-bit字。
 *
 * - 当 SPI 传输的字大小不是2的幂次倍8-bit时，这些内存中的字将包含额外的bit。在
 * 内中，字总是向右对齐的，因此，未定义 (rx) 或未使用 (tx) 的位总是最高有效位。
 *
 * - 所有SPI传输开始时，片选变得有效，通常它一直保持有效，如果是一系列传输中的最后一个
 *   传输，最后一个传输应该设置传输标志位：#AM_SPI_TRANS_EOT
 *
 */
typedef struct am_spi_transfer {
    const void *p_txbuf;                   /**< \brief 指向发送数据缓存的指针 */
    void       *p_rxbuf;                   /**< \brief 指向接收数据缓存的指针 */
    uint32_t    nbytes;                    /**< \brief 数据长度(字节数)      */
    uint32_t    flags;                     /**< \brief 传输控制标志          */
    void      (*pfn_callback)(void *,int); /**< \brief SPI传输完成回调函数    */
    void       *p_arg;                     /**< \brief 回调函数的入口参数     */
} am_spi_transfer_t;


/**
 * \brief SPI控制配置参数信息
 */
typedef struct am_spi_cfg_info {
    
    uint8_t     bpw;         /**< \brief bit_per_word,字大小                       */
    uint32_t    speed;       /**< \brief SPI速度                                   */
    uint32_t    cfg_flags;   /**< \brief 模式标识,可以是SPI模式标识的宏或多个宏的或值 */
   
} am_spi_cfg_info_t;

/**
 * \brief SPI驱动函数结构体
 */
struct am_spi_drv_funcs {
    
    /** \brief 指向SPI参数配置函数 */
    int (*pfn_spi_config)(void              *p_drv,
                          am_spi_cfg_info_t *p_info);

    /** \brief 指向SPI传输函数 */
    int (*pfn_spi_transfer)(void              *p_drv, 
                            am_spi_transfer_t *p_trans);
    
    /** \brief 指向SPI中断连接函数 */
    int (*pfn_spi_connect)(void *p_drv);
    
};

/**
 * \brief SPI 标准服务结构体
 */
typedef struct am_spi_serv {
    struct am_spi_drv_funcs   *p_drv_funcs;    /**< \brief SPI  SPI驱动函数     */
    void                      *p_drv;          /**< \brief SPI  SPI驱动函数参数 */
} am_spi_serv_t;

/** \brief SPI 标准服务操作句柄定义 */
typedef am_spi_serv_t *am_spi_handle_t;

/**
 * \brief SPI中断连接函数
 * \param[in] handle : SPI标准服务操作句柄
 * \retval  AM_OK    : 连接成功
 */
am_static_inline
int am_spi_connect (am_spi_handle_t handle)
{
    return handle->p_drv_funcs->pfn_spi_connect(handle->p_drv);
}

/**
 * \brief SPI参数配置函数，配置速率、位宽、模式等
 *
 * \param[in] handle     : SPI标准服务操作句柄
 * \param[in] p_info     : 需要配置的参数信息
 *
 * \retval   AM_OK           : 配置成功
 * \retval  -AM_EHIGH        : 配置失败，频率太高，支持的最高频率将存放在 p_info->speed 中。
 * \retval  -AM_ELOW         : 配置失败，频率太低，支持的最小频率将存放在 p_info->speed 中。
 * \retval  -AM_ENOTSUP      : 配置失败，不支持的位宽、模式
 *
 * \note 配置完成后，p_info中存放了实际的配置结果，速率可能存在一定偏差。  
 */
am_static_inline
int am_spi_config (am_spi_handle_t handle, am_spi_cfg_info_t *p_info)
{
    return handle->p_drv_funcs->pfn_spi_config(handle->p_drv, p_info);
}

/**
 * \brief SPI传输结构体参数设置
 *
 * \param[in] p_trans      : 指向SPI传输结构体的指针
 * \param[in] p_txbuf      : 指向发送数据缓存的指针,仅接收时应该置为NULL
 * \param[in] p_rxbuf      : 指向接收数据缓存的指针,仅发送时应该置为NULL
 * \param[in] nbytes       : 当前传输数据长度，字节数（16位数据时，字节数应该是2 * N（数据个数））
 * \param[in] flags        : SPI传输控制标志位，AM_SPI_TRANS_*的宏值或者多AM_SPI_TRANS_*宏的 或（OR）值
 * \param[in] pfn_callback : 回调函数
 * \param[in] p_arg        : 回调函数的入口参数
 *
 * \retval  AM_OK     : 传输结构体参数设置完成
 *
 * \note 如果发送和接收数据缓冲区都有效，务必确保它们的数据长度是一致的。
 *       关于缓冲区的类型和数据传输字节数：
 *        - 1  ~ 8 位宽时，uint8_t 类型，nbytes = 数据传输的个数
 *        - 9  ~ 16位宽时，uint16_t类型，nbytes = 2 * 数据传输的个数
 *        - 17 ~ 31位宽时，uint32_t类型，nbytes = 4 * 数据传输的个数
 */
am_static_inline
int am_spi_mktrans (am_spi_transfer_t *p_trans,
                    const void        *p_txbuf,
                    void              *p_rxbuf,
                    uint32_t           nbytes,
                    uint32_t           flags,
                    void             (*pfn_callback)(void *,int),
                    void              *p_arg)
{
    if(p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->p_txbuf      = p_txbuf;
    p_trans->p_rxbuf      = p_rxbuf;
    p_trans->nbytes       = nbytes;
    p_trans->flags        = flags;
    p_trans->pfn_callback = pfn_callback; 
    p_trans->p_arg        = p_arg;
    
    return AM_OK;
}

/**
 * \brief SPI传输函数
 *
 * \param[in] handle  : SPI标准服务操作句柄
 * \param[in] p_trans : 指向SPI传输结构体的指针
 *
 * \retval   AM_OK     : 传输正常进行处理
 * \retval -AM_EINVAL : 输入参数错误
 *  传输过程以及结果状态，通过传输回调函数获取状态位
 *    \li  AW_OK  : 传输完成
 *    \li -AM_EIO : 传输错误
 */
am_static_inline
int am_spi_transfer (am_spi_handle_t handle, am_spi_transfer_t *p_trans)
{
    return handle->p_drv_funcs->pfn_spi_transfer(handle->p_drv, p_trans);
}


/**
 * \brief 先写后读
 *
 * 本函数先进行SPI写操作，再进行读操作。
 * 在实际应用中，写缓冲区可以为地址，读缓冲区为要从该地址读取的数据。
 *
 * \param[in]   handle  SPI标准服务操作句柄
 * \param[in]   p_txbuf 数据发送缓冲区
 * \param[in]   n_tx    要发送的数据字节个数
 * \param[out]  p_rxbuf 数据接收缓冲区
 * \param[in]   n_rx    要接收的数据字节个数
 *
 * \retval AM_OK        消息处理成功
 * \retval -AM_EINVAL   参数错误
 * \retval -AM_EIO      传输出错
 */
int am_spi_write_then_read (am_spi_handle_t  handle,
                            const uint8_t   *p_txbuf,
                            size_t           n_tx,
                            uint8_t         *p_rxbuf,
                            size_t           n_rx);

/**
 * \brief 执行两次写操作
 *
 * 本函数连续执行两次写操作，依次发送数据缓冲区0和缓冲区1中的数据。
 * 在实际应用中，缓冲区0可以为地址，缓冲区1为要写入该地址的数据。
 *
 * \param[in]   handle  SPI标准服务操作句柄
 * \param[in]   p_txbuf0 数据发送缓冲区0
 * \param[in]   n_tx0    缓冲区0数据个数
 * \param[in]   p_txbuf1 数据发送缓冲区1
 * \param[in]   n_tx1    缓冲区1数据个数
 *
 * \retval AM_OK        消息处理成功
 * \retval -AM_EINVAL   参数错误
 * \retval -AM_EIO      传输出错
 */
int am_spi_write_then_write (am_spi_handle_t  handle,
                             const uint8_t   *p_txbuf0,
                             size_t           n_tx0,
                             const uint8_t   *p_txbuf1,
                             size_t           n_tx1);
/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SPI_H */

/*end of file */

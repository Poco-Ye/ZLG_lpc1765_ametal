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
 * \brief I2C标准接口
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_I2C_H
#define __AM_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * @addtogroup am_if_i2c
 * @copydoc am_i2c.h
 * @{
 */

/**
 * \name I2C 传输控制标识，用于am_i2c_transfer的flags成员
 * @{ 
 */

#define AM_I2C_M_7BIT          0x0000u    /**< \brief 7-bits 设备地址  */
#define AM_I2C_M_10BIT         0x0001u    /**< \brief 10-bits 设备地址 */
#define AM_I2C_M_WR            0x0000u    /**< \brief 写操作           */
#define AM_I2C_M_RD            0x0002u    /**< \brief 读操作           */
#define AM_I2C_M_NOSTART       0x0004u    /**< \brief 无需重新启动     */
#define AM_I2C_M_REV_DIR_ADDR  0x0008u    /**< \brief 读写标志位反转   */
#define AM_I2C_M_RECV_LEN      0x0010u    /**< \brief 暂不支持        */

/** \brief 忽略所有无应答错误 (包括从机地址无应答和数据无应答) */
#define AM_I2C_M_IGNORE_NAK    0x0020u

/** \brief 在读操作中接收数据时不发送应答    */
#define AM_I2C_M_NO_RD_ACK     0x0040u

/** \brief 本次传输完成产生I2C停止信号      */
#define AM_I2C_M_STOP          0x0080u

/** \brief I2C传输控制标志掩码 */
#define AM_I2C_M_MASK          0x00FFu

/** @} */


/**
 * \name I2C 从机设备标志，用于 am_i2c_device 的 dev_flags 成员
 * @{ 
 */
/** \brief 7位地址模式(默认模式) */
#define AM_I2C_ADDR_7BIT         AM_I2C_M_7BIT

/** \brief 10位地址模式 */
#define AM_I2C_ADDR_10BIT        AM_I2C_M_10BIT

/** \brief 忽略设备的无应答 */
#define AM_I2C_IGNORE_NAK        AM_I2C_M_IGNORE_NAK

/** \brief 器件内子地址高位字节先传输(默认)*/
#define AM_I2C_SUBADDR_MSB_FIRST 0x0000u

/** \brief 器件内子地址低位字节先传输 */
#define AM_I2C_SUBADDR_LSB_FIRST 0x0100u

#define AM_I2C_SUBADDR_NONE      0x0000u  /**< \brief 无子地址(默认)  */
#define AM_I2C_SUBADDR_1BYTE     0x1000u  /**< \brief 子地址宽度1字节 */
#define AM_I2C_SUBADDR_2BYTE     0x2000u  /**< \brief 子地址宽度2字节 */

/** \brief 从标志控制字中取得子地址宽度 */
#define AM_I2C_SUBADDR_LEN_GET(flags)  (((flags) & 0xF000) >> 12)

/** @} */

/**
 * \brief I2C从机设备相关信息结构体
 */
typedef struct am_i2c_device {
    uint16_t  dev_addr;                 /**< \brief I2C 从机设备地址 */ 
    uint16_t  dev_flags;                /**< \brief I2C 从机设备特性 */
} am_i2c_device_t;

/**
 * \brief I2C 传输结构体
 */ 
typedef struct am_i2c_transfer {
    uint16_t   addr;                      /**< \brief I2C设备地址          */
    uint16_t   flags;                     /**< \brief I2C 传输标志         */
    void      *p_buf;                     /**< \brief I2C 传输数据缓存指针  */
    uint16_t   length;                    /**< \brief I2C 数据缓存长度      */
    void     (*pfn_callback)(void *,int); /**< \brief I2C 传输完成回调函数  */
    void      *p_arg;                     /**< \brief 回调函数入口参数      */
} am_i2c_transfer_t;


/**
 * \brief I2C驱动函数结构体
 */
struct am_i2c_drv_funcs {
    
    /** \brief 指向I2C数据/地址传输函数 */
    int (*pfunc_i2c_transfer) (void *p_drv, am_i2c_transfer_t *p_trans);
    
    /** \brief 指向I2C中断连接函数 */
    int (*pfunc_i2c_connect) (void *p_drv);
    
};

/**
 * \brief I2C标准服务结构体 
 */
typedef struct am_i2c_serv {
    struct am_i2c_drv_funcs   *p_drv_funcs;   /**< \brief I2C驱动函数 */
    void                      *p_drv;         /**< \brief I2C驱动函数入口函数 */
} am_i2c_serv_t;

/** \brief I2C标准服务操作句柄定义 */
typedef am_i2c_serv_t *am_i2c_handle_t;

/**
 * \brief I2C中断连接函数
 * \param[in] handle : I2C标准服务操作句柄
 * \retval  AM_OK    : 连接成功
 */
static int am_i2c_connect (am_i2c_handle_t handle)
{
    return handle->p_drv_funcs->pfunc_i2c_connect(handle->p_drv);
}


/**
 * \brief I2C从机设备相关信息结构体参数设置
 *
 * \param[in] p_device     : 指向从机设备信息的结构体的指针
 * \param[in] dev_addr     : 从机设备地址
 * \param[in] dev_flags    : 从机设备特性
 *
 * \retval  AM_OK     : 设备信息设置完成
 * \retval -AM_EINVAL : 参数错误
 */
am_static_inline
int am_i2c_mkdevice(am_i2c_device_t *p_device, 
                    uint16_t         dev_addr,
                    uint16_t         dev_flags)

{
    if(p_device == NULL) {
        return -AM_EINVAL;
    }
    
    p_device->dev_addr   = dev_addr;
    p_device->dev_flags  = dev_flags;

    return AM_OK;
}

/**
 * \brief I2C传输结构体信息参数设置
 *
 * \param[in] p_trans : 指向传输结构体的指针
 * \param[in] addr    : 操作的从机设备地址
 * \param[in] flags   : 传输过程中的控制标识位
 *                      AM_I2C_M_*的宏值或者多个AM_I2C_M_*宏的 或（OR）值 (#AM_I2C_M_RD) 
 * \param[in] p_buf   : 指向发送或者接收数据缓存
 * \param[in] length  : 当前传输的数据/地址长度
 * \param[in] pfn_callback   : 传输完成回调函数
 * \param[in] p_arg   : 回调函数入口参数
 *
 * \retval  AM_OK     : 传输结构体参数设置完成
 * \retval -AM_EINVAL : 参数错误
 */
am_static_inline
int am_i2c_mktrans (am_i2c_transfer_t *p_trans, 
                    uint16_t           addr,  
                    uint16_t           flags, 
                    void              *p_buf, 
                    uint16_t           length,
                    void             (*pfn_callback)(void *,int),
                    void              *p_arg)
{
    if (p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->addr   = addr;
    p_trans->flags  = flags;
    p_trans->p_buf  = p_buf; 
    p_trans->length = length;
    p_trans->pfn_callback = pfn_callback; 
    p_trans->p_arg  = p_arg;
    
    return AM_OK;
}

/**
 * \brief I2C传输数据/地址函数
 *
 * \param[in] handle  : I2C标准服务操作句柄
 * \param[in] p_trans : 指向传输结构体的指针
 *
 * \retval  AM_OK     : 传输正常进行
 * \retval -AM_EINVAL : 输入参数错误 
 *  传输过程以及结果状态返回，通过传输回调状态位获取
 *    \li  AW_OK  传输完成
 *    \li -AM_EIO 总线错误或者总线仲裁错误等
 */
static int am_i2c_transfer (am_i2c_handle_t handle, am_i2c_transfer_t *p_trans)
{
    return handle->p_drv_funcs->pfunc_i2c_transfer(handle->p_drv, p_trans);
}

/**
 * \brief I2C写数据
 *
 * \param[in] handle   : I2C标准服务操作句柄
 * \param[in] p_device : 指向从机设备信息的结构体的指针
 * \param[in] sub_addr : 从机设备子地址
 * \param[in] p_buf    : 指向发送/接收数据缓存
 * \param[in] nbytes   : 数据缓存长度
 *
 * \return  AM_OK : 写数据完成
 */
int am_i2c_write(am_i2c_handle_t  handle,
                 am_i2c_device_t *p_device,
                 uint32_t         sub_addr,
                 uint8_t         *p_buf, 
                 uint32_t         nbytes);
/**
 * \brief I2C读数据
 *
 * \param[in] handle   : I2C标准服务操作句柄
 * \param[in] p_device : 指向从机设备信息的结构体的指针
 * \param[in] sub_addr : 从机设备子地址
 * \param[in] p_buf    : 指向发送/接收数据缓存
 * \param[in] length   : 数据缓存长度
 *
 * \return  AM_OK : 读数据完成 
 */
int am_i2c_read (am_i2c_handle_t  handle,
                 am_i2c_device_t *p_device,
                 uint32_t         sub_addr,
                 void            *p_buf, 
                 uint16_t         length);
/** 
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_I2C_H */

/* end of file */

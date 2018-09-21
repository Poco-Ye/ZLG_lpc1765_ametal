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
 * \brief SPI驱动，服务SPI标准接口
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-15  jon, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SPI_H
#define __AMDR_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"    
#include "am_spi.h"
#include "amhw_spi.h"
#include "am_int.h"

/**
 * \addtogroup amdr_if_spi
 * \copydoc amdr_spi.h
 * @{
 */
 
/**
 * \brief SPI 设备基本参数结构体 
 */
typedef struct amdr_spi_mst_param {
    uint8_t      bits_per_word;                     /**< \brief 数据帧的位数            */
    uint16_t     scl_mode;                          /**< \brief SPI SCL的模式           */
    uint16_t     lsb_first;                         /**< \brief SPI LSB优先发送与否定义 */
    amhw_slave_t slave;                             /**< \brief SPI 从机片选引脚选择    */
} amdr_spi_mst_param_t;


/**
 * \brief SPI 设备信息结构体
 */
typedef struct amdr_spi_devinfo {
    
    uint8_t           bits_per_word;       /**< \brief 数据帧的位数          */
    uint32_t          flags;               /**< \brief SPI 配置标识          */
    uint32_t          speed;               /**< \brief 初始化速率            */
    struct amhw_spi  *p_hw_spi;            /**< \brief 指向SPI寄存器块的指针  */
    uint16_t          inum;                /**< \brief SPI 中断编号          */

} amdr_spi_devinfo_t;

/** \brief SPI 设备信息重定义 */
typedef amdr_spi_devinfo_t am_spi_devinfo_hw_t;


/**
 * \brief SPI 设备
 */
typedef struct amdr_spi_dev {
    
     /** \brief SPI标准服务操作句柄 */
    am_spi_serv_t             spi_serve;
    
    /** \brief 指向SPI传输结构体的指针 */
    am_spi_transfer_t        *p_trans;
    
    /** \brief 指向I2C设备信息的指针 */
    const amdr_spi_devinfo_t *p_devinfo;
    
    /** \brief 控制器状态机状态  */
    int         state;  
    
    uint32_t    cur_speed;      /**< \brief 控制器当前速度   */
    uint8_t     cur_bpw;        /**< \brief 控制器当前帧大小 */
    uint8_t     cur_flags;      /**< \brief 控制器当前模式   */
    uint16_t    cur_dly;        /**< \brief 当前传输间延时   */
    
    uint32_t    nbytes_to_recv; /**< \brief 待接收的字节数   */
    uint32_t    data_ptr;       /**< \brief 数据传输记数     */
    
} amdr_spi_dev_t;

/** \brief SPI 设备重定义 */
typedef amdr_spi_dev_t am_spi_dev_hw_t;

/**
 * \brief SPI 初始化
 *
 * \param[in] p_dev     : 指向SPI设备结构体的指针
 * \param[in] p_devinfo : 指向SPI设备信息结构体的指针
 *
 * \return  SPI标准服务操作句柄 
 */
am_spi_handle_t amdr_spi_init(amdr_spi_dev_t           *p_dev,
                              const amdr_spi_devinfo_t *p_devinfo);

/**
 * \brief 解除SPI初始化
 * \param[in] p_dev : 指向SPI设备结构体的指针
 * \return 无
 */
void amdr_spi_deinit(amdr_spi_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SPI_H */

/*end of file */

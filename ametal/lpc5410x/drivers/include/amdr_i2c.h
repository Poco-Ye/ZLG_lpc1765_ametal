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
 * \brief I2C驱动，服务I2C标准接口
 *
 * \internal
 * \par Modification History
 * - 1.01 15-04-16  tee, modified some interface,add the function to support am_i2c_speed_set()
 * - 1.00 15-01-10  jon, first implementation.
 * \endinternal
 */

#ifndef __AMDR_I2C_H
#define __AMDR_I2C_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_int.h"
#include "am_i2c.h"
#include "amhw_i2c.h"

/**
 * \addtogroup amdr_if_i2c
 * \copydoc amdr_i2c.h
 * @{
 */

/**
 * \brief I2C 设备信息参数结构体
 */
typedef struct amdr_i2c_devinfo {
    
    uint32_t         bus_speed;      /**< \brief I2C初始化总线速度,am_i2c_speed_set() 标准接口可以改变速率 */
 
    struct amhw_i2c *p_hw_i2c;       /**< \brief 指向I2C寄存器块的指针  */
    uint16_t         inum;           /**< \brief I2C 控制器的中断号     */
} amdr_i2c_devinfo_t;

/**
 * \brief I2C 设备结构体
 */
typedef struct amdr_i2c_dev {
   
     /** \brief 标准I2C服务           */
    am_i2c_serv_t             i2c_serv;

    /** \brief 指向I2C传输结构体的指针,同一时间只能处理一个传输 */
    am_i2c_transfer_t        *p_trans;
    
    /** \brief 用于数据接收/发送计数   */
    uint32_t                  data_ptr; 
    
    /** \brief 忙标识                 */
    bool_t                    busy;
    
    /** \brief 状态                   */
    uint8_t                   state;    
    
    /** \brief 指向I2C设备信息的指针   */
    const amdr_i2c_devinfo_t *p_devinfo;
    
} amdr_i2c_dev_t;


/**
 * \brief I2C 初始化
 *
 * \param[in] p_dev     : 指向I2C设备结构体的指针
 * \param[in] p_devinfo : 指向I2C设备信息结构体的指针
 *
 * \return  I2C标准服务操作句柄 
 */
am_i2c_handle_t amdr_i2c_init(amdr_i2c_dev_t           *p_dev,
                              const amdr_i2c_devinfo_t *p_devinfo);

/**
 * \brief 解除I2C初始化
 * \param[in] p_dev : 指向I2C设备结构体的指针
 * \return 无
 */
void amdr_i2c_deinit(amdr_i2c_dev_t *p_dev);



/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_I2C_H */

/* end of file */

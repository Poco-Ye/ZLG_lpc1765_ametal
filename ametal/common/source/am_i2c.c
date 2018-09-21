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
 * \brief I2C implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#include "am_i2c.h"

/** \brief 传输状态标志  */
volatile static int __g_trans_stat = AM_OK;

void __i2c_callback(void *p_arg, int status)
{
    am_wait_t *p_wait = (am_wait_t *)p_arg;
    
    __g_trans_stat = status;
    
    /* 结束等待序列 */
    am_wait_done(p_wait);
}

/**
 * \brief I2C write operate
 */
int am_i2c_write (am_i2c_handle_t  handle,
                  am_i2c_device_t *p_device,
                  uint32_t         sub_addr,
                  uint8_t         *p_buf, 
                  uint32_t         nbytes)
{

    uint16_t subaddr_len = AM_I2C_SUBADDR_LEN_GET(p_device->dev_flags);
    
    am_i2c_transfer_t trans;
    am_wait_t         trans_wait;
    
    am_wait_init(&trans_wait);
    
    /* if no sub address just send the data */
    if (subaddr_len == 0) {
        
        am_i2c_mktrans(&trans,
                       p_device->dev_addr,
                       (p_device->dev_flags | AM_I2C_M_WR),
                       p_buf, 
                       nbytes,
                        __i2c_callback,
                       (void *)&trans_wait);
        
        am_i2c_transfer(handle, &trans);
        am_wait_on(&trans_wait);
                       
        /* 传输出现错误，返回错误信息 */
        if (__g_trans_stat != AM_OK) {
            return __g_trans_stat;
        }
        return AM_OK;
    }
    
    am_i2c_mktrans(&trans,
                   p_device->dev_addr,
                   (p_device->dev_flags | AM_I2C_M_WR),
                   (uint8_t *)&sub_addr, 
                    subaddr_len,
                    __i2c_callback,
                   (void *)&trans_wait);
                   
    am_i2c_transfer(handle, &trans);
    am_wait_on(&trans_wait);
                   
    /* 传输出现错误，返回错误信息 */
    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }
    
    am_i2c_mktrans(&trans,
                   p_device->dev_addr,
                   (p_device->dev_flags | AM_I2C_M_NOSTART | AM_I2C_M_WR | AM_I2C_M_STOP),  /* 不需要启动信号，需要停止信号 */
                   (uint8_t *)p_buf, 
                   nbytes,
                    __i2c_callback,
                   (void *)&trans_wait);

    am_i2c_transfer(handle, &trans);
    am_wait_on(&trans_wait);
    
    /* 传输出现错误，返回错误信息 */
    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }
    
    return AM_OK;
}


/**
 * \brief I2C write operate
 */
int am_i2c_read (am_i2c_handle_t  handle,
                 am_i2c_device_t *p_device,
                 uint32_t         sub_addr,
                 void            *p_buf, 
                 uint16_t         length)
{
    uint16_t subaddr_len = AM_I2C_SUBADDR_LEN_GET(p_device->dev_flags);
    
    am_i2c_transfer_t trans;
    am_wait_t         trans_wait;
    
    am_wait_init(&trans_wait);
    
    /* if no sub address just send the data */
    if (subaddr_len == 0) {
        
        am_i2c_mktrans(&trans,
                       p_device->dev_addr,
                       (p_device->dev_flags | AM_I2C_M_RD),
                       p_buf, 
                       length,
                       __i2c_callback,
                       (void *)&trans_wait);
        
        am_i2c_transfer(handle, &trans);
        
        /* 等待，直到传输结束 */
        am_wait_on(&trans_wait);
        
        /* 传输出现错误，返回错误信息 */
        if (__g_trans_stat != AM_OK) {
            return __g_trans_stat;
        }
                       
        return AM_OK;
        
    }
    
    am_i2c_mktrans(&trans,
                   p_device->dev_addr,
                   (p_device->dev_flags | AM_I2C_M_WR),
                   (uint8_t *)&sub_addr, 
                   subaddr_len, 
                   __i2c_callback, 
                   (void *)&trans_wait);
                   
    am_i2c_transfer(handle, &trans);
    am_wait_on(&trans_wait);

    /* 传输出现错误，返回错误信息 */
    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }

    am_i2c_mktrans(&trans,
                   p_device->dev_addr,
                   (p_device->dev_flags | AM_I2C_M_RD | AM_I2C_M_STOP),
                   (uint8_t *)p_buf, 
                   length,
                   __i2c_callback,
                   (void *)&trans_wait);

    am_i2c_transfer(handle, &trans);
    am_wait_on(&trans_wait);
                   
    /* 传输出现错误，返回错误信息 */
    if (__g_trans_stat != AM_OK) {
        return __g_trans_stat;
    }

    return AM_OK;
}

/* end of file */

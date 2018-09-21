/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief 在I2C轮询模式下操作EEPROM，通过HW层的接口实现
 *
 * - 操作步骤:
 *   1. 将I2C接口和EEPROM接口对应引脚连接；
 *   2. 将程序下载到demo板上，并重新上电或复位。
 *
 * - 实验现象:
 *   1. 读取EEPROM中的数据通过串口打印出来；
 *   2. 若写入数据和读取的数据一致，校验通过，LED以200ms间隔闪烁。
 *
 * \par 源代码
 * \snippet demo_hw_i2c_polling_eeprom.c src_hw_i2c_polling_eeprom 
 * 
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_i2c_polling_eeprom
 * \copydoc demo_hw_i2c_polling_eeprom.c
 */
 
/** [src_hw_i2c_polling_eeprom] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"

#define I2C_M_7BIT      0x0000u    /**< \brief 7-bits 设备地址  */
#define I2C_M_10BIT     0x0001u    /**< \brief 10-bit 设备地址  */
#define I2C_M_WR        0x0000u    /**< \brief 写操作           */
#define I2C_M_RD        0x0002u    /**< \brief 读操作           */
#define I2C_M_NOSTART   0x0010u    /**< \brief 无需重新启动标识 */


#define I2C_MASTER      AMHW_I2C0  /**< \brief I2C主机控制器通道号定义   */
#define I2C_SPEED       400000     /**< \brief I2C控制器速度参数定义     */
#define I2C_CLKDIV      6          /**< \brief I2C控制器时钟分频参数定义 */
#define EEPROM_ADDR     0x50       /**< \brief EEPROM设备地址定义        */
#define TEST_LEN        0x10       /**< \brief 操作EEPROM的页大小        */

/**
 * \brief I2C传输结构体定义，主要用于I2C轮询模式下。
 */ 
typedef struct i2c_transfer {
    volatile uint16_t   addr;      /**< \brief I2C设备地址          */ 
    volatile uint16_t   flags;     /**< \brief I2C 设备特性以及transfer需要的特殊标识 */
    volatile void      *p_buf;     /**< \brief I2C 传输数据缓存指针 */
    volatile uint16_t   length;    /**< \brief I2C 数据缓存长度     */
} i2c_transfer_t;

i2c_transfer_t __g_i2c0_transfer;

/**
 * \brief I2C传输结构体参数设置函数
 *
 * \param[in] p_trans : 指向I2C传输结构体的指针
 * \param[in] addr    : 设备地址参数
 * \param[in] flags   : 传输控制标识位参数 
 * \param[in] p_buf   : 指向发送或者接收数据缓存的指针
 * \param[in] length  : 缓存的字节长度参数
 *
 * \retval  AM_OK     : 传输结构体设置完成
 */
int i2c_mktrans (i2c_transfer_t    *p_trans, 
                 uint16_t           addr,  
                 uint16_t           flags, 
                 void              *p_buf, 
                 uint16_t           length)
{
    if(p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->addr   = addr;
    p_trans->flags  = flags;
    p_trans->p_buf  = p_buf; 
    p_trans->length = length;
    
    return AM_OK;
}

/**
 * \brief I2C主机启动函数
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] p_trans  : 指向I2C传输结构体的指针
 *
 * return   无
 */
void i2c_mst_start (amhw_i2c_t     *p_hw_i2c, 
                    i2c_transfer_t *p_trans)
{
    uint16_t dev_addr = (p_trans->addr) << 1;
    
    if(!(p_trans->flags & I2C_M_NOSTART)) {
        
        if (p_trans->flags & I2C_M_RD) {
            dev_addr |= 0x1;            /* 设置bit0为1，表明当前为读操作 */
        } else {
            dev_addr |= 0x0;            /* 设置bit0为0，表明当前为写操作 */
        }
   
    /* 发送设备地址 */
    amhw_i2c_mstdat_write(p_hw_i2c, dev_addr);
    amhw_i2c_mst_start(p_hw_i2c);       /* I2C 控制器发送启动信号 */
    }
}

/**
 * \brief I2C主机发送地址/数据
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] p_trans  : 指向I2C传输结构体的指针
 *
 * \retval  AM_OK  : 发送完成 
 */
int i2c_mst_send (amhw_i2c_t     *p_hw_i2c, 
                  i2c_transfer_t *p_trans)
                      
{
    uint8_t i;

    for (i = 0;i < p_trans->length; i++) {

        while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)) ; 
        while ((p_hw_i2c->stat & AMHW_I2C_MASTER_STATE_MASK) != AMHW_I2C_STAT_MSTTX);
        
        amhw_i2c_mstdat_write(p_hw_i2c, ((uint8_t *)(p_trans->p_buf))[i]);
        amhw_i2c_mst_continue(p_hw_i2c);
    }
    while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)); 
    while ((p_hw_i2c->stat & AMHW_I2C_MASTER_STATE_MASK) != AMHW_I2C_STAT_MSTTX);

    return AM_OK;
}

/**
 * \brief  I2C主机接收地址/数据
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] p_trans  : 指向I2C传输结构体的指针
 *
 * \retval  AM_OK  : 接收完成 
 */
int i2c_mst_recv (amhw_i2c_t     *p_hw_i2c, 
                  i2c_transfer_t *p_trans)
{
    uint8_t i;

    for (i = 0; i < p_trans->length; i++) {
        while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)) ; 

        while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)) ; 
        while ((p_hw_i2c->stat & AMHW_I2C_MASTER_STATE_MASK) != AMHW_I2C_STAT_MSTRX); 
        
        /* receive data */
        ((uint8_t *)(p_trans->p_buf))[i] = amhw_i2c_mstdat_read(p_hw_i2c);

        if (i != (p_trans->length - 1)) {
            amhw_i2c_mst_continue(p_hw_i2c);
        }
    }
    return AM_OK;    
}

/**
 * \brief I2C主机速率设置
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] speed    : 主机速度参数
 *
 * \retval  AM_OK  : 设置完成
 */
int i2c_speed_set (amhw_i2c_t *p_hw_i2c, uint32_t speed)
{

    uint32_t    scl;
    uint32_t    scl_h, scl_l;
    
    scl = amhw_clock_periph_freq_get(p_hw_i2c) / 
          ((amhw_i2c_clkdiv_get(p_hw_i2c)+1) * speed);

    scl_h = scl >> 1;
    scl_l = (scl - scl_h);
    if (scl_h < 2) {
        scl_h = 2;
    
    } else if (scl_h > 9) {
        scl_h = 9;
    }
    
    if (scl_l < 2) {
        scl_l = 2;
   
   } else if (scl_l > 9) {
        scl_l = 9;
    }
    amhw_i2c_msttime_set(p_hw_i2c, ((scl_l-2) << 0) | ((scl_h-2) << 4));
    
    return AM_OK;
}

/**
 * \brief I2C主机初始化配置 
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] speed    : 主机速度参数
 * \param[in] clkdiv   : I2C 主机时钟分频参数
 *
 * \retval  AM_OK      : 配置完成
 * \retval  -AM_EINVAL : 参数无效
 */
int i2c_mst_init (amhw_i2c_t *p_hw_i2c, uint32_t speed, uint32_t clkdiv)
{

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }
    
    /* 关闭I2C控制器，配置参数 */
    amhw_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);

    /* 设置时钟分频参数 */
    amhw_i2c_clkdiv_set(p_hw_i2c, clkdiv);
    
    /* 设置速率 */
    i2c_speed_set(p_hw_i2c, speed);

    /* 参数配置完成，启动I2C控制器 */
    amhw_i2c_mode_enable(p_hw_i2c, AM_I2C_MASTER_MODE);

    return AM_OK;
}

/**
 * \brief 主函数
 */
int main (void)
{
    i2c_transfer_t   *p_trans = &__g_i2c0_transfer;
    uint8_t           eeprom_buf[16] = {0};
    uint8_t           test_addr[2]   = {0x90};
    uint8_t           i;
                     
    
    am_board_init();                                 /* 板级初始化          */
    amhw_plfm_i2c0_init();                           /* I2C0 平台相关初始化 */
    
    AM_DBG_INFO("I2C operate EEPROM demo in polling mode .\r\n");
    
    
    i2c_mst_init(I2C_MASTER, I2C_SPEED, I2C_CLKDIV); /* I2C主机初始化配置 */

     /* 设置transfer结构体参数，写入地址 */
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_WR), 
                (uint8_t *)test_addr, 
                1);
                
    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_send (I2C_MASTER, p_trans);
    
    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = i + 0xA;
    }

     /* 设置transfer结构体参数，写入数据 */
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_NOSTART | I2C_M_WR), 
                (uint8_t *)eeprom_buf, 
                TEST_LEN);

    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_send(I2C_MASTER, p_trans);
    
    /* 结束当前传输 */
    amhw_i2c_mst_stop(I2C_MASTER);

    am_mdelay(10);
    
    /* 设置transfer结构体参数，写入地址 */
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_WR), 
                (uint8_t *)test_addr, 
                1);

    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_send (I2C_MASTER, p_trans);

    
   /* 设置transfer结构体参数，读取数据 */
    for (i = 0; i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_RD), 
                (uint8_t *)eeprom_buf, 
                TEST_LEN);

    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_recv(I2C_MASTER, p_trans);
    
    /* 结束当前传输 */
    amhw_i2c_mst_stop(I2C_MASTER);
    
    am_mdelay(10);
    
    /* 校验写入和读取的数据是否一致 */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is  : 0x%2X\r\n", i, eeprom_buf[i]);
        
        /* 校验失败 */
        if(eeprom_buf[i] != (i + 0xA)) {
            while(1);
        }
    }
    
    /* 校验成功，LED以200ms时间间隔闪烁 */
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_hw_i2c_polling_eeprom] */

/* end of file */

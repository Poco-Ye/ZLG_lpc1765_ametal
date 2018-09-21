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
 * \brief I2C主机演示例程，通过标准接口实现
 *
 * - 操作步骤::
 *   1. 将主机I2C接口和从机I2C接口对应引脚连接；
 *   2. 将程序下载到demo板上，并重新上电或复位。
 *
 * - 实验现象:
 *   1. 主机写地址和数据到从机，并通过串口打印出来；
 *   2. 主机接收从机数据，并通过串口打印处理；
 *   3. 主机写入的数据和接收到的从机从机数据一致，校验通过，LED以200ms时间间隔闪烁。
 *
 * \note 该演示例程和 demo_std_i2c_int_eeprom 演示例程所用的接口函数不同，但功能相同
 *
 * \par 源代码
 * \snippet demo_std_i2c_master.c src_std_i2c_master 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_std_i2c_master
 * \copydoc demo_std_i2c_master.c
 */
 
/** [src_std_i2c_master] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


#define EEPROM_ADDR             0x50            /**< \brief EEPROM设备的地址 */
#define TEST_LEN                0x10            /**< \brief 操作EEPROM的页大小 */


bool_t g_trans_flag;                            /**< \brief 传输标志位定义 */
/**
 * \brief I2C 传输完成回调函数
 * \param[in] p_arg  : 回调函数入口参数
 * \param[in] status : 传输状态位
 * \return  无
 */
void  i2c_transfer_complete(void *p_arg, int status)
{
    if(status == AM_OK) {
        g_trans_flag = TRUE;
    } else {
//        AM_DBG_INFO("I2C transfer error, status is %d",status);
    }
    
}



/**
 * \brief 主函数
 */
int main (void)
{
    am_i2c_handle_t    i2c_handle;
    am_i2c_transfer_t  trans;
    uint8_t            eeprom_buf[16] = {0};        /* 数据缓存定义               */
    uint8_t            test_addr[2]   = {0x10};     /* I2C 操作从机设备子地址定义 */
    uint8_t            i;
    
    am_board_init();                                /* 板级初始化 */

    amhw_plfm_i2c0_init();                          /* I2C0 硬件平台初始化 */
    
    AM_DBG_INFO("I2C master test demo.\r\n");
    
    /* I2C 初始化 */
    i2c_handle = amdr_i2c_init(&g_i2c0_dev, &g_i2c0_devinfo);
    am_i2c_connect(i2c_handle);                     /* I2C 中断连接 */
 
    /* 设置transfer结构体参数，写入地址 */
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_WR,
                   (uint8_t *)test_addr, 
                   1,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));

    /* 启动transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* 等待transfer完成 */
    while (!g_trans_flag);
    g_trans_flag = FALSE;

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = (i + 6);
    }
    
    /* 设置transfer结构体参数，写入数据 */
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_NOSTART | AM_I2C_M_WR | AM_I2C_M_STOP, 
                   (uint8_t *)eeprom_buf, 
                   TEST_LEN,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));

    /* 启动transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* 等待transfer完成 */
    while (!g_trans_flag);   
    g_trans_flag = FALSE;

    am_mdelay(10);
    
    /* 设置transfer结构体参数，写入地址 */
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE  | AM_I2C_M_WR, 
                   (uint8_t *)test_addr, 
                   1,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));
    
    /* 启动transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* 等待transfer完成 */
    while (!g_trans_flag);
    g_trans_flag = FALSE;
                   
    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    
    /* 设置transfer结构体参数，读取数据模式*/
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_RD | AM_I2C_M_STOP,
                   (uint8_t *)eeprom_buf, 
                   TEST_LEN,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));
    
    /* 启动transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* 等待transfer完成 */
    while (!g_trans_flag);  
    g_trans_flag = FALSE;


    /* 校验写入和读取的数据是否一致 */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is %2X\r\n", i ,eeprom_buf[i]);
        
        /* 校验失败 */
        if(eeprom_buf[i] != (i + 6)) {
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

/** [src_std_i2c_master] */

/* end of file */

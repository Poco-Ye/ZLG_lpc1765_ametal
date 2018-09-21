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
 * \brief 在I2C中断模式下操作EEPROM演示例程，通过标准接口实现
 *
 * - 操作步骤:
 *   1. 将I2C接口和EEPROM接口对应引脚连接；
 *   2. 将程序下载到demo板上，并重新上电或复位。
 *
 * - 实验现象:
 *   1. 读取EEPROM中的数据通过串口打印出来；
 *   2. 若写入数据和读取的数据一致，校验通过，LED以200ms间隔闪烁。
 *
 * \note 该演示例程和 demo_std_i2c_master 演示例程，实现的所用的接口函数不同，但功能相同
 *
 * \par 源代码
 * \snippet demo_std_i2c_int_eeprom.c src_std_i2c_int_eeprom 
 * 
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_std_i2c_int_eeprom
 * \copydoc demo_std_i2c_int_eeprom.c
 */

/** [src_std_i2c_int_eeprom] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"

#define EEPROM_ADDR             0x50            /**< \brief EEPROM设备的地址 */
#define TEST_LEN                0x10            /**< \brief 操作EEPROM的页大小 */


/**
 * \brief 主函数
 */
int main (void)
{
    am_i2c_handle_t    i2c_handle;
    am_i2c_device_t    eeprom;                      /* I2C 操作设备定义           */
    uint8_t            eeprom_buf[16] = {0};        /* 数据缓存定义               */
    uint8_t            test_addr      =  0x90 ;     /* I2C 操作从机设备子地址定义 */
    uint8_t            i;
    int                ret;
    
    am_board_init();                                /* 板级初始化 */

    amhw_plfm_i2c0_init();                          /* I2C0 硬件平台初始化 */
    
    AM_DBG_INFO("I2C operate EEPROM demo.\r\n");
    
    /* I2C 初始化 */
    i2c_handle = amdr_i2c_init(&g_i2c0_dev, &g_i2c0_devinfo);
    am_i2c_connect(i2c_handle);                     /* I2C 中断连接 */
    
    am_i2c_mkdevice(&eeprom,
                    EEPROM_ADDR,
                    AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = (i + 5);
    }
    
    /* 写入数据到指定的EEPROM地址 */
    ret = am_i2c_write(i2c_handle,
                       &eeprom,
                        test_addr,
                       (uint8_t *)eeprom_buf, 
                       TEST_LEN);
    
    if (ret != AM_OK) {
        AM_DBG_INFO("写数据：I2C传输出现错误,错误代码：%d\r\n",ret);
    }

    am_mdelay(10);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    
    /* 读取数据到指定的EEPROM地址 */
    ret = am_i2c_read(i2c_handle,
                      &eeprom,
                      test_addr,
                      (uint8_t *)eeprom_buf, 
                      TEST_LEN);

    if (ret != AM_OK) {
        AM_DBG_INFO("读数据：I2C传输出现错误,错误代码：%d\r\n",ret);
        while(1);
    }
    
    am_mdelay(10);

    /* 校验写入和读取的数据是否一致 */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is %2X\r\n", i ,eeprom_buf[i]);
        
        /* 校验失败 */
        if(eeprom_buf[i] != (i + 5)) {
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

/** [src_std_i2c_int_eeprom] */

/* end of file */

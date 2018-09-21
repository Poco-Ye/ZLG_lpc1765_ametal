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
 * \brief APL_StartKit EEPROM演示例程
 *
 * - 操作步骤:
 *   1. 将APL_StartKit配板接到EasyARM-54000M4 demo板；
 *   2. 将APL_StartKit配板上串口0接口（J3）连接到PC机上。
 *
 * - 实验现象:
 *   1. 读取EEPROM中的数据通过串口打印出来；
 *   2. 若写入数据和读取的数据一致，校验通过，LED_RUN(绿)以200ms间隔闪烁,
 *      反之，RUN_LED(红)亮。
 *
 * \par 源代码
 * \snippet demo_apl_startkit_eeprom.c src_apl_startkit_eeprom 
 * 
 * \internal
 * \par History
 * - 1.00 15-03-17  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_apl_startkit_eeprom
 * \copydoc demo_apl_startkit_eeprom.c
 */

/** [src_apl_startkit_eeprom] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"

/**
 * \name EEPROM 设备参数定义
 * @{ 
 */
#define EEPROM_ADDR             0x50            /**< \brief EEPROM设备的地址   */

/** \brief EEPROM设备子地址，CAT240C02子地址范围0x00-0xFF */
#define TEST_ADDR               0x10            
#define TEST_LEN                0x10            /**< \brief 操作EEPROM的页大小 */
/** @} */

/**
 * \name APL_StartKit 配板IO定义
 * @{ 
 */
#define RUN_LED                 PIO1_5          /**< \brief RUN指示灯IO端口定义 */
#define ERR_LED                 PIO0_9          /**< \brief ERR指示灯IO端口定义 */
/** @} */

/**
 * \brief APL_StartKit 配板相关初始化
 */
void apl_startkit_init(void)
{
    am_gpio_pin_cfg(RUN_LED, AM_GPIO_OUTPUT);        /* 配置PIO1_4 RUN_LED   */
    am_gpio_set(RUN_LED, 1);                         /* RUN_LED 初始状态熄灭 */
    am_gpio_pin_cfg(ERR_LED, AM_GPIO_OUTPUT);        /* 配置PIO1_5 ERR_LED   */
    am_gpio_set(ERR_LED, 1);                         /* RUN_LED 初始状态熄灭 */
}

/**
 * \brief 主函数
 */
int main (void)
{
    am_i2c_handle_t    i2c_handle;
    am_i2c_device_t    eeprom;                      /* I2C 操作设备定义           */
    uint8_t            eeprom_buf[16] = {0};        /* 数据缓存定义               */
    uint8_t            i;
    bool_t             verify_ok_flag = TRUE;       /* 校验成功与否标志，
                                                        TRUE-校验成功 
                                                        FALSE-校验失败 */
    
    am_board_init();                                /* 板级初始化 */
    
    apl_startkit_init();                            /* APL_StartKit 初始化 */
    
    amhw_plfm_i2c0_init();                          /* I2C0 硬件平台初始化 */
    
    AM_DBG_INFO("I2C operate APL_StartKit’s EEPROM .\r\n");
    
    /* I2C 初始化 */
    i2c_handle = amdr_i2c_init(&g_i2c0_dev, &g_i2c0_devinfo);
    am_i2c_connect(i2c_handle);                     /* I2C 中断连接 */
    
    am_i2c_mkdevice(&eeprom,
                    EEPROM_ADDR,
                    AM_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE,
                    0x01);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = (i + 5);
    }
    
    /* 写入数据到指定的EEPROM地址 */
    am_i2c_write(i2c_handle,
                 &eeprom,
                 TEST_ADDR,
                 (uint8_t *)eeprom_buf, 
                 TEST_LEN);

    am_mdelay(10);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    
    /* 读取数据到指定的EEPROM地址 */
    am_i2c_read(i2c_handle,
                &eeprom,
                TEST_ADDR,
                (uint8_t *)eeprom_buf, 
                TEST_LEN);

    am_mdelay(10);

    /* 校验写入和读取的数据是否一致 */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is %2X\r\n", i ,eeprom_buf[i]);
        
        /* 校验失败 */
        if(eeprom_buf[i] != (i + 5)) {
            AM_DBG_INFO(" Verify failed!\r\n");
            verify_ok_flag = FALSE;
        }
    }
    
    
    while (1) {
        
        /* 校验成功，RUN_LED(绿灯)以200ms时间间隔闪烁 */
        if(verify_ok_flag) {
            am_gpio_set(RUN_LED, 0); 
            am_mdelay(200);
        
            am_gpio_set(RUN_LED, 1); 
            am_mdelay(200);
            
        /* 校验失败，ERR_LED(红灯)常亮 */
        } else {
            am_gpio_set(ERR_LED, 0); 
        }
    }
}


/** [src_apl_startkit_eeprom] */

/* end of file */

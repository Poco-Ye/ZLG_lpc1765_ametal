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
 * \brief APL_StartKit SPI FLASH演示例程
 *
 * - 操作步骤:
 *   1. 将APL_StartKit配板接到EasyARM-54000M4 demo板；
 *   2. 用跳线帽连接SPI接口(MISO、MOSI、SCK、CS)，使SPI_FLASH连接到SPI0；
 *   3. 将APL_StartKit配板上串口0接口（J3）连接到PC机上。
 *
 * - 实验现象:
 *   1. 从SPI_FLASH中读取到的数据，通过串口打印出来；
 *   2. 写入数据和读取的数据相同，SPI_FLASH读写测试成功，LED_RUN(绿)以200ms间隔闪烁,
 *      反之，RUN_LED(红)亮。
 *
 * \par 源代码
 * \snippet demo_apl_startkit_spiflash.c src_apl_startkit_spiflash
 *
 * \internal
 * \par History
 * - 1.00 15-03-19  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_apl_startkit_spiflash
 * \copydoc demo_apl_startkit_spiflash.c
 */
 
/** [src_apl_startkit_spiflash] */
#include "ametal.h"
#include "am_board.h"
#include "am_spi_flash.h"
#include "am_prj_config.h"




#define TEST_ADDR          0x0900                  /**< \brief SPI_FLASH 测试页地址   */
#define TEST_LEN           256                     /**< \brief 测试字节长度           */

uint8_t g_tx_buf[TEST_LEN]={0};                    /**< \brief SPI_FLASH 写数据缓存 */
uint8_t g_rx_buf[TEST_LEN]={0};                    /**< \brief SPI_FLASH 读数据缓存 */


bool_t g_verify_flag = TRUE;                       /**< \brief 校验成功与否标志，
                                                               TRUE-校验成功 
                                                               FALSE-校验失败 */

/* APL_StartKit definitions */
#define  RUN_LED        PIO1_5
#define  ERR_LED        PIO0_9


/**
 * \brief SPI_FLASH测试demo
 *         1. 擦除将要操作地址中的数据， 
 *         2. 写入数据到设定的地址， 
 *         3. 从该地址中读取数据， 
 *         4. 数据校验。
 *
 * \param[in] spi_handle : SPI标准服务操作句柄
 * \param[in] addr       : 将要操作的SPI_FLASH页地址
 * \param[in] length     : 数据长度
 *
 * \return  无
 */
void spi_flash_test (am_spi_handle_t spi_handle, 
                     uint32_t        addr, 
                     uint32_t        length) 
{
    uint32_t i;

    /* 擦除当前地址中数据 */
    am_spi_flash_erase(spi_handle, addr);

    for (i = 0; i < length; i++) {
        g_tx_buf[i] = i ;
    }
    
    /* 写入数据到设定SPI_FLASH地址 */
    am_spi_flash_write(spi_handle, addr, (uint8_t *)g_tx_buf, length);
    am_mdelay(10);

    for (i = 0; i < length; i++) {
        g_tx_buf[i] = 0;
    }
    
    /* 从设定的SPI_FLASH地址中读取数据 */
    am_spi_flash_read(spi_handle, addr, (uint8_t *)g_tx_buf,length);
    am_mdelay(10);
    
    /* 数据校验 */
    for (i = 0; i < length; i++) {
        
        /* 将读取到的数据通过串口打印出来 */
        AM_DBG_INFO(" read FLASH %2dst data is : 0x%2x \r\n", i, g_tx_buf[i]);
        if(g_tx_buf[i] != (i & 0xFF)) {
            g_verify_flag = FALSE;
            AM_DBG_INFO("verify failed!\r\n");
        }
    }
}

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
    am_spi_handle_t     spi_handle;
    
    /* 板级初始化 */
    am_board_init();
    
    /* APL_StartKit 配板LED IO 初始化 */
    apl_startkit_init();
   
    /* SPI0 平台相关初始化 */
    amhw_plfm_spi0_init();

    /* SPI初始化配置 */
    spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);

    /* SPI中断函数连接 */
    am_spi_connect(spi_handle);

    spi_flash_test(spi_handle, TEST_ADDR, TEST_LEN);
    
    /* SPI_FLASH读写数据校验成功后，LED0 以200ms时间间隔闪烁 */
    while (1) {
        /* 校验成功，RUN_LED(绿灯)以200ms时间间隔闪烁 */
        if(g_verify_flag) {        
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

/** [src_apl_startkit_spiflash] */

/* end of file */

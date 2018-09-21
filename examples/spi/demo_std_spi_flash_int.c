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
 * \brief 在SPI中断模式下操作SPI_FLASH演示例程，通过标准接口实现
 *
 * - 操作步骤:
 *   1. 将SPI接口和SPI_FLASH对应的接口连接起来；
 *   2. 将程序下载到demo板，重新上电或者复位。
 *
 * - 实验现象:
 *   1. 从SPI_FLASH中读取到的数据，通过串口打印出来；
 *   2. 写入数据和读取的数据相同，SPI_FLASH读写测试成功，LED0以200ms间隔闪烁。
 *
 * \note
 *   1. 可见，大多数情况下，直接使用 am_spi_write_then_read() 和 am_spi_write_then_write() 函数即可。
 *
 * \par 源代码
 * \snippet demo_std_spi_flash_int.c src_std_spi_flash_int
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_std_spi_flash_int
 * \copydoc demo_std_spi_flash_int.c
 */
 
/** [src_std_spi_flash_int] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


/**
 * \brief SPI flash defines
 */
#define WREN            0x06                       /**< \brief SPI_FLASH 写使能命令   */
#define WRDI            0x04                       /**< \brief SPI_FLASH 读取ID命令   */
#define RDSR            0x05                       /**< \brief SPI_FLASH 读取状态命令 */
#define WRSR            0x01                       /**< \brief SPI_FLASH 写状态命令   */
#define READ            0x03                       /**< \brief SPI_FLASH 读操作命令   */
#define WRITE           0x02                       /**< \brief SPI_FLASH 写操作命令   */
#define SE              0x20                       /**< \brief SPI_FLASH 擦除操作命令 */
#define CHIP_ERASE      0x60                       /**< \brief SPI_FLASH 整片擦除命令 */

#define FLASH_PAGE_SIZE    256                     /**< \brief SPI_FLASH 页大小定义   */

#define TEST_ADDR          0x0900                  /**< \brief SPI_FLASH 测试页地址   */
#define TEST_LEN           FLASH_PAGE_SIZE         /**< \brief 测试字节长度           */

uint8_t g_tx_buf[TEST_LEN]={0x9F};                /**< \brief SPI_FLASH 写数据缓存 */
uint8_t g_rx_buf[TEST_LEN]={0};                   /**< \brief SPI_FLASH 读数据缓存 */

volatile bool_t g_trans_flag;                               /**< \brief SPI 传输标志 */

/**
 * \brief SPI传输完成回调函数
 */
void spi_transfer_complete(void *p_arg,int status)
{
    if(status == AM_OK) {
        g_trans_flag = TRUE;
    } else {
        AM_DBG_INFO("SPI transfer error, status is %d", status);
    }
}

/**
 * \brief 判断SPI_FLASH 是否处于忙状态
 * \param[in] spi_handle : SPI标准服务操作句柄
 * \retval TURE  : 忙状态
 * \retval FALSE : 空闲状态
 */
bool_t flash_isbusy_chk (am_spi_handle_t spi_handle) 
{
    uint8_t           cmd_data = RDSR;
    uint8_t           status_data;

    am_spi_write_then_read(spi_handle,
                           &cmd_data,
                           1,
                           &status_data,
                           1);

    return (status_data & 0x01) ? TRUE : FALSE;
}

/* FLASH 写使能 */
void flash_wren (am_spi_handle_t spi_handle) 
{
    am_spi_transfer_t trans;
    
    uint8_t  tx_cmd = WREN;       /* 发送的指令 */
 
    /* 设置transfer参数， 发送写使能命令 */ 
    am_spi_mktrans( &trans, 
                    &tx_cmd,
                    NULL,
                    1,
                    AM_SPI_TRANS_EOT,
                    spi_transfer_complete,
                    NULL);
                   
    am_spi_transfer(spi_handle, &trans);
    while (!g_trans_flag);
    g_trans_flag = FALSE;
}


/**
 * \brief SPI_FLASH擦除函数
 *
 * \param[in] spi_handle : SPI标准服务操作句柄
 * \param[in] addr       : SPI_FLASH擦出的页地址
 *
 * \return  无
 */
void spi_flash_erase (am_spi_handle_t spi_handle, 
                      uint32_t        addr)
{
    am_spi_transfer_t trans;
    
    uint8_t  tx_cmd[4];  /* 发送的指令 */
    uint8_t  cmd_len;    /* 指令长度   */

    flash_wren(spi_handle);

    tx_cmd[0] = SE;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;
    
    cmd_len   = 4;
    
    /* 设置transfer参数， 发送擦除命令以及擦除地址 */
    am_spi_mktrans(&trans, 
                   tx_cmd, 
                   NULL, 
                   cmd_len, 
                   AM_SPI_TRANS_EOT,
                   spi_transfer_complete,
                   (void *)(spi_handle));
                   
    am_spi_transfer(spi_handle, &trans);
    while (!g_trans_flag);
    g_trans_flag = FALSE;
                   
    /* 等待SPI_FLASH处于空闲状态 */
    while (flash_isbusy_chk(spi_handle) == TRUE) {
        am_mdelay(1);
    }
}

/**
 * \brief SPI_FLASH 写数据
 *
 * \param[in] spi_handle : SPI标准服务操作句柄
 * \param[in] addr       : 要写入数据的地址
 * \param[in] length     : 数据缓存的长度
 *
 * \return  无
 */
 void spi_flash_write (am_spi_handle_t spi_handle, 
                         uint32_t        addr, 
                         uint32_t        length)
{
    uint8_t  tx_cmd[4];       /* 发送的指令 */

    flash_wren(spi_handle);

    /* 写入写指令和24位地址 */
    tx_cmd[0] = WRITE;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;
 
    am_spi_write_then_write(spi_handle,
                            tx_cmd,
                            4,
                            g_tx_buf,
                            length);

    /* 等待SPI_FLASH处于空闲状态 */
    while (flash_isbusy_chk(spi_handle) == TRUE);
}

/**
 * \brief SPI_FLASH读数据
 *
 * \param[in] spi_handle : SPI标准服务操作句柄
 * \param[in] addr       : 要读取数据的地址
 * \param[in] length     : 数据缓存的长度
 *
 * \return  无
 */
void spi_flash_read (am_spi_handle_t spi_handle, 
                     uint32_t        addr, 
                     uint32_t        length)
{
    uint8_t  tx_cmd[4];       /* 发送的指令 */

    /* 写入读指令和24位地址 */
    tx_cmd[0] = READ;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;
    
    am_spi_write_then_read(spi_handle,
                           tx_cmd,
                           4,
                           g_rx_buf,
                           length);
 
    /* 等待SPI_FLASH处于空闲状态 */
    while (flash_isbusy_chk(spi_handle) == TRUE);
}

/**
 * \brief SPI_FLASH读数据
 *
 * \param[in] spi_handle : SPI标准服务操作句柄
 * \param[in] addr       : 要读取数据的地址
 * \param[in] length     : 数据缓存的长度
 *
 * \return  无
 */
void flash_id_chk (am_spi_handle_t spi_handle)
{

    uint8_t  tx_cmd = 0x9F;       /* 发送的指令 */
    uint8_t  rd_id[3];
    
    am_spi_write_then_read(spi_handle,
                           &tx_cmd,
                           1,
                           rd_id,
                           3);
 
    /* 等待SPI_FLASH处于空闲状态 */
    while (flash_isbusy_chk(spi_handle) == TRUE);
    
    
    am_kprintf("The ID is %x, %x ,%x\r\n",rd_id[0], rd_id[1], rd_id[2]);
}

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
void spi_flash_test_demo (am_spi_handle_t spi_handle, 
                          uint32_t        addr, 
                          uint32_t        length) 
{
    uint32_t           i;
    am_spi_cfg_info_t  cfg_info;
    
    /**
     * 由于片选引脚为PIO0_14（具有SSEL功能），可以实现SPI硬件自动控制，在这里
     * 只需要将其引脚配置为SPI0的SSEL功能即可。
     * 如果不是SPI的SSEL功能，则可以手动控制，调用gpio标准接口。
     */
    am_gpio_pin_cfg(PIO0_14, PIO0_14_SPI0_SSELN0 | PIO0_14_PULLUP);

    /* 设定配置参数 */
    cfg_info.speed       = 2000000;             /* SPI速率设置为4MHz  */
    cfg_info.cfg_flags   = AM_SPI_CFG_MODE_0;   /* 使用SPI模式0       */
    cfg_info.bpw         = 8;                   /* 位宽为8位          */
    
    /* 配置SPI控制器 */
    am_spi_config(spi_handle, &cfg_info);
    
    /* 检查芯片ID */
    flash_id_chk(spi_handle);
    
    /* 擦除当前地址中数据 */
    spi_flash_erase(spi_handle, addr);
 
    am_kprintf("FLASH擦除完成\r\n");
    
    for (i = 0; i < length; i++) {
        g_tx_buf[i] = i + 7;
    }
    
    /* 写入数据到设定SPI_FLASH地址 */
    spi_flash_write(spi_handle, addr, length);
    am_mdelay(10);

    am_kprintf("FLASH数据写入完成\r\n");
    
    for (i = 0; i < length; i++) {
        g_rx_buf[i] = 0;
    }
    
    /* 从设定的SPI_FLASH地址中读取数据 */
    spi_flash_read(spi_handle, addr, length);
    am_mdelay(10);
 
    /* 数据校验 */
    for (i = 0; i < length; i++) {
        
        /* 将读取到的数据通过串口打印出来 */
        AM_DBG_INFO(" read %2dst data is : 0x%2x \r\n", i, g_rx_buf[i]);
        if(g_rx_buf[i] != ((7 + i) & 0xFF)) {
            AM_DBG_INFO("verify failed!\r\n");
            while(1);
        }
    }
}
/**
 * \brief 主函数
 */
int main (void)
{
    am_spi_handle_t     spi_handle;
    
    /* 板级初始化 */
    am_board_init();

    /* SPI0 平台相关初始化 */
    amhw_plfm_spi0_init();

    /* SPI初始化配置 */
    spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);

    /* SPI中断函数连接 */
    am_spi_connect(spi_handle);

    spi_flash_test_demo(spi_handle, TEST_ADDR, TEST_LEN);
    
    /* SPI_FLASH读写数据校验成功后，LED0 以200ms时间间隔闪烁 */
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_std_spi_flash_int] */

/* end of file */

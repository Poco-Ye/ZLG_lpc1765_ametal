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
 * \brief SPI从机演示例程，通过HW层的接口实现
 *
 * - 操作步骤:
 *   1. 将SPI从机接口和主机接口对应连接起来；
 *   2. 将程序下载到demo板，重新上电或者复位。
 *
 * - 实验现象:
 *   1. 从机接收主机数据，并通过串口将接收到的数据打印出来；
 *   2. 从机发送数据到主机，并通过串口将发送的数据打印出来；
 *   3. 上述操作完成之后，LED0以200ms时间间隔闪烁。
 *
 * \par 源代码
 * \snippet demo_hw_spi_slave.c src_hw_spi_slave
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_spi_slave
 * \copydoc demo_hw_spi_slave.c
 */
 
/** [src_hw_spi_slave] */ 
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


#define SPI_SLAVE      AMHW_SPI0      /**< \brief SPI从机控制器通道号 */

#define SPI_M_EOT       0x1000        /**< \brief SPI结束当前transfer控制位  */
#define SPI_M_CTRL_MASK 0xFF00        /**< \brief SPI控制位掩码              */
#define SPI_M_8_BPW     0x0007        /**< \brief SPI传输数据帧大小为8bytes  */
#define SPI_M_16_BPW    0x000F        /**< \brief SPI传输数据帧大小为16bytes */
#define SPI_M_BPW_MASK  0x00FF        /**< \brief SPI传输数据帧大小掩码      */


/** 
 * \brief SPI传输结构体定义
 */
typedef struct spi_transfer {
    const void *p_txbuf;                  /**< \brief 指向发送数据缓存的指针  */
    void       *p_rxbuf;                  /**< \brief 指向接收数据缓存的指针  */
    uint32_t    nbytes;                   /**< \brief 数据长度   */
    uint16_t    flags;                    /**< \brief SPI传输控制标志位 */
} spi_transfer_t;

spi_transfer_t __g_spi0_transfer;         /* 定义一个SPI传输结构体实例 */

/**
 * \brief SPI传输结构体参数设置
 *
 * \param[in] p_trans : 指向SPI传输结构体
 * \param[in] p_txbuf : 指向发送数据缓存的指针
 * \param[in] p_rxbuf : 指向接收数据缓存的指针
 * \param[in] nbytes  : 当前传输数据长度   
 * \param[in] flags   : SPI传输控制标志位
 *
 * \retval  AM_OK     : 设置完成
 */
int spi_mktrans (spi_transfer_t *p_trans, 
                 const void     *p_txbuf,
                 void           *p_rxbuf,
                 uint32_t        nbytes,
                 uint16_t        flags)
                    
{
    if (p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->p_txbuf  = p_txbuf;
    p_trans->p_rxbuf  = p_rxbuf;
    p_trans->nbytes   = nbytes;
    p_trans->flags    = flags;

    return AM_OK;
}


/**
 * \brief SPI从机启动
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] p_trans  : 指向SPI传输体结构体指针
 *
 * \return  无
 */
void spi_slv_start (amhw_spi_t *p_hw_spi, spi_transfer_t *p_trans)
{
    p_hw_spi->txctl = AMHW_SPI_TXDATCTL_FSIZE(p_trans->flags & SPI_M_BPW_MASK);
}
/**
 * \brief SPI从机发送数据
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] p_trans  : 指向SPI传输体结构体指针
 *
 * \return  AM_OK : SPI发送完成 
 */
int spi_slv_send (amhw_spi_t      *p_hw_spi, 
                  spi_transfer_t  *p_trans)
{
    uint32_t i = 0;
    
    spi_slv_start(p_hw_spi, p_trans);
    
    for (i = 0; i < p_trans->nbytes; i++) {

        while ( (p_hw_spi->stat & AMHW_SPI_STAT_TXRDY) == 0);

        if ((p_trans->flags & SPI_M_BPW_MASK) <= 8) {
            amhw_spi_txdat_write(p_hw_spi, ((uint8_t *)(p_trans->p_txbuf))[i]);
    
        } else {   
            amhw_spi_txdat_write(p_hw_spi, ((uint16_t *)(p_trans->p_txbuf))[i]);
        }
    }
    return AM_OK; 
}


/**
 * \brief SPI从机接收数据
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] p_trans  : 指向SPI传输体结构体指针
 *
 * \return  AM_OK : SPI接收完成 
 */
int spi_slv_recv (amhw_spi_t      *p_hw_spi, 
                  spi_transfer_t  *p_trans)
{
    uint32_t i = 0;
    
    spi_slv_start(p_hw_spi, p_trans);
    
    for (i = 0; i < p_trans->nbytes; i++) {
        while ( (p_hw_spi->stat & AMHW_SPI_STAT_RXRDY) == 0 );

        if ((p_trans->flags & SPI_M_BPW_MASK) <= 8) {
            ((uint8_t *)(p_trans->p_rxbuf))[i] = amhw_spi_rxdata_8bit_read(p_hw_spi); 
        
        } else {   
            ((uint16_t *)(p_trans->p_rxbuf))[i] = amhw_spi_rxdata_16bit_read(p_hw_spi);
        }
    }
    return 0; 
}

/**
 * \brief SPI从机初始化配置
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \retval  AM_OK      : 配置完成
 * \retval  -AM_EINVAL ：参数无效
 */
int spi_slv_init (amhw_spi_t *p_hw_spi)
{
    amhw_spi_disable(p_hw_spi);                                  /* 禁能SPI，配置参数 */
    
    /* SPI从机参数配置  */
    p_hw_spi->cfg |= AMHW_SPI_CFG_SLAVE ; 

    amhw_spi_enable(p_hw_spi);                                   /* 配置完成，使能SPI*/
    return AM_OK;
}

/**
 * \brief 主函数
 */
int main (void)
{
    spi_transfer_t *p_trans = &__g_spi0_transfer;
    
    uint8_t spi_slv_txbuf[32] = {0};
    uint8_t spi_slv_rxbuf[32] = {0};
    uint8_t length =16;
    uint8_t i;
    
    /* 板级初始化 */
    am_board_init();
    
    /* SPI0 平台相关初始化 */
    amhw_plfm_spi0_init();
  
    /* SPI 从机初始化 */
    spi_slv_init(SPI_SLAVE);
    
    for (i = 0; i < length; i++) {
        spi_slv_txbuf[i] = 2*i; 
    }
    
    /* 从机接收主机发送的数据 */
    spi_mktrans(p_trans,  NULL, (uint8_t *)&spi_slv_rxbuf, length, (SPI_M_EOT | SPI_M_8_BPW));
    spi_slv_recv(SPI_SLAVE, p_trans);               
    printf("\r\n--Slave receive Data:\r\n");
    for (i = 0; i<length; i++) {
        printf("The %2dst data is %2d \r\n", i, spi_slv_rxbuf[i]);
       
    }               
    
    /* 从机发送数据到主机 */
    spi_mktrans(p_trans, (uint8_t *)&spi_slv_txbuf, NULL, length, (SPI_M_EOT | SPI_M_8_BPW));
    spi_slv_send(SPI_SLAVE, p_trans);               
    
    printf("\r\n--Slave transmit Data:\r\n");
    for (i = 0; i < length; i++) {
        printf("The %2dst data is %2d \r\n", i, spi_slv_txbuf[i]);
    }
    
    while (1) {
        
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_hw_spi_slave] */ 
  

/* end of file */


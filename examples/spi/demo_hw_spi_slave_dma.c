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
 * \brief SPI从机接收数据通过DMA控制器，通过HW层的接口实现
 *
 * - 操作步骤:
 *   1. 将SPI接口和数据源对应的SPI接口连接起来；
 *   2. 将程序下载到demo板，重新上电或者复位。
 *
 * - 实验现象:
 *   1. 接收到数据，通过串口打印出来。
 *
 * \par 源代码
 * \snippet demo_hw_spi_slave_dma.c src_hw_spi_slave_dma
 *
 * \internal
 * \par History
 * - 1.00 15-01-25  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_spi_slave_dma
 * \copydoc demo_hw_spi_slave_dma.c
 */ 
 
/** [src_hw_spi_slave_dma] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"



#define SPI_SLAVE      AMHW_SPI0 /**< \brief SPI从机控制器通道号 */


/** \brief reload descriptor map */
__align(16)  amhw_dma_xfer_desc_t g_desc[2];

uint16_t g_buf_src[16];           /**< \brief 源数据缓存区   */
uint16_t g_buf_dsta[8];           /**< \brief A 描述符缓存区 */
uint16_t g_buf_dstb[8];           /**< \brief B 描述符缓存区 */


uint8_t g_a_transfer_done;        /**< \brief A 传输完成标志 */
uint8_t g_b_transfer_done;        /**< \brief B 传输完成标志 */

/** 
 * \brief DMA 中断服务函数
 *
 * \param[in] p_arg : 中断服务函数入口参数
 * \param[in] p_flg : DMA中断标志（例如A传输中断，B传输中断，错误中断等）
 *
 * \return    无
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;
    
    if (flag == AMDR_DMA_INTA) {
        g_a_transfer_done = 1;
    
    } else if (flag == AMDR_DMA_INTB) {
        g_b_transfer_done = 1;
    
    } else if (flag == AMDR_DMA_INTERR) {
        
    }

    
}


/**
 * \brief DMA乒乓模式传输测试函数.
 */
void dma_ping_pong_test (void)
{
    uint32_t flags1, flags2;
    
    /* 
     * DMA通道配置
     */
    amdr_dma_chan_setup(DMA_CHAN_SPI0_RX_REQ,           /* DMA 通道号设置     */
                        AMHW_DMA_CHAN_PERIPH_REQ_EN |   /* 禁能外设触发请求   */
                        AMHW_DMA_CHAN_HWTRIG_OFF |      /* 禁能硬件触发       */
                        AMHW_DMA_CHAN_SINGLE_TRANS |    /* 单一传输           */
                        AMHW_DMA_CHAN_PRIO_6);          /* 设置通道优先级为6  */

    amdr_dma_chan_start(DMA_CHAN_SPI0_RX_REQ);          /* DMA 通道启动  */
    
    /*
     * DMA传输配置1
     */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                  /* 当前通道描述符有效              */
             AMHW_DMA_XFER_RELOAD |                     /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                     /* 软件触发                        */
             AMHW_DMA_XFER_NO_CLRTRIG |                 /* 不清除触发标志                  */
             AMHW_DMA_XFER_WIDTH_16BIT |                /* 传输数据宽度：16 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* 源端数据地址不递增              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTA;                     /* 使能中断 A                      */

    /*                                                  
     * DMA传输配置2                       
     */                                                 
    flags2 = AMHW_DMA_XFER_CFG_VALID |                  /* 当前通道描述符有效              */
             AMHW_DMA_XFER_RELOAD |                     /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                     /* 软件触发                        */
             AMHW_DMA_XFER_NO_CLRTRIG |                 /* 不清除触发标志                  */
             AMHW_DMA_XFER_WIDTH_16BIT |                /* 传输数据宽度：16 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* 源端数据地址不递增              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTB;                     /* 使能中断 B                      */

    /*
     * 建立通道描述符A 
     */
    amdr_dma_xfer_desc_build(&g_desc[0],                     /* A的重载描述符               */
                             (uint32_t)AMHW_SPI0_RXDAT_ADDR, /* 源端数据地址                */
                             (uint32_t)g_buf_dsta,           /* A的目标端缓冲区地址         */
                             16,                             /* 传输字节数                  */
                             flags1);                        /* 传输配置1                   */

    /*
     * 建立通道描述符B 
     */
    amdr_dma_xfer_desc_build(&g_desc[1],                     /* B的重载描述符               */
                             (uint32_t)AMHW_SPI0_RXDAT_ADDR, /* 源端数据地址                */
                             (uint32_t)g_buf_dstb,           /* B的目标端缓冲区地址         */
                             16,                             /* 传输字节数                  */
                             flags2);                        /* 传输配置2                   */
    /*
     * 连接DMA中断处理函数
     */
    amdr_dma_isr_connect(DMA_CHAN_SPI0_RX_REQ,
                         dma_isr,
                         (void *)0);
                         


    
    /*
     * 链接重载描述符 
     */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /*
     * DMA传输启动
     */
    amdr_dma_chan_xfer_startup(DMA_CHAN_SPI0_RX_REQ, &g_desc[0]);

}


/**
 * \brief SPI从机启动
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] len      : 数据帧长度，范围1 - 16.
 *
 * \return  无
 */
void spi_slv_start (amhw_spi_t *p_hw_spi,uint8_t len)
{
    p_hw_spi->txctl = AMHW_SPI_TXDATCTL_FSIZE(len);
}

/**
 * \brief SPI从机初始化配置
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \retval  AM_OK      : 配置完成
 * \retval  -AM_EINVAL ：参数无效
 */
int spi_slv_init (amhw_spi_t *p_hw_spi)
{
    amhw_spi_disable(p_hw_spi);                /* 禁能SPI，配置参数 */
    
    /* SPI从机参数配置  */
    p_hw_spi->cfg |= AMHW_SPI_CFG_SLAVE ; 

    amhw_spi_enable(p_hw_spi);                 /* 配置完成，使能SPI*/
    return AM_OK;
}


/**
 * \brief 主函数
 */
int main (void)
{
    uint8_t i ;
    
    /* 板级初始化 */
    am_board_init();
    
    /* SPI0与DMA相关平台初始化 */
    amhw_plfm_dma_init();
    amhw_plfm_spi0_init();
    /* DMA控制器初始化 */ 
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);
    
    /* SPI从机初始化配置 */
    spi_slv_init(SPI_SLAVE);
    
    spi_slv_start(SPI_SLAVE, 16-1);
   
    dma_ping_pong_test();
    
    while (1) {
        
        /* A传输完成标志位置位，通过串口将接收到数据打印出来 */
        if (g_a_transfer_done) {
            g_a_transfer_done = 0;
            for (i = 0; i < 8; i++){
                AM_DBG_INFO("A_buf %2dst is :%4X\r\n",i,g_buf_dsta[i]);
            }

        }
        
        /* A传输完成标志位置位，通过串口将接收到数据打印出来 */
        if (g_b_transfer_done) {
            g_b_transfer_done = 0;
            for (i = 0; i < 8; i++){
                AM_DBG_INFO("B_buf %2dst is :%4X\r\n",i,g_buf_dstb[i]);
            }
        }
    }
    
}

/** [src_hw_spi_slave_dma] */

/* end of file */


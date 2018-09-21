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
 * \brief SPI 硬件操作接口
 * 
 * 1. 支持1-16bits直接传输，较大的数据帧可通过软件处理之后进行传输；
 * 2. 支持主机和从机传输；
 * 3. 数据可以被传输到从机，无需读传进来的数据。这个功能可用于建立SPI内存； 
 * 4. 控制信息可选择性的和数据一同写入. 该功能应用广泛, 包含任意长度数据帧；
 * 5. 高达4个从机输入/输出选择端口，并可配置极性，用户可灵活配置；
 * 6. 支持DMA传输: SPI接收和发送数据可通过系统DMA控制器进行传输。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_SPI_H
#define __AMHW_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"

/**
 * \addtogroup amhw_if_spi
 * \copydoc amhw_spi.h
 * @{
 */
 
    
/**
 * \brief SPI寄存器块结构体
 */
typedef struct amhw_spi {
    __IO uint32_t  cfg;         /**< \brief SPI 配置寄存器     */
    __IO uint32_t  dly;         /**< \brief SPI 延时参数配置寄存器 */
    __IO uint32_t  stat;        /**< \brief SPI 状态寄存器     */
    __IO uint32_t  intenset;    /**< \brief SPI 中断使能寄存器 */
    __O  uint32_t  intenclr;    /**< \brief SPI 中断禁能寄存器 */
    __I  uint32_t  rxdat;       /**< \brief SPI 接收数据寄存器 */
    __IO uint32_t  txdatctl;    /**< \brief SPI 发送数据和传输控制寄存器 */
    __IO uint32_t  txdat;       /**< \brief SPI 发送数据寄存器 */
    __IO uint32_t  txctl;       /**< \brief SPI 传输控制寄存器 */
    __IO uint32_t  div;         /**< \brief SPI 时钟分频寄存器 */
    __I  uint32_t  intstat;     /**< \brief SPI 中断状态寄存器 */
} amhw_spi_t;

/**
 * \name DMA可操作的SPI控制的物理地址
 * @{
 */

/** \brief SPI0 接收数据地址 */
#define AMHW_SPI0_RXDAT_ADDR  (&(AMHW_SPI0->rxdat)) 

/** \brief SPI0 发送数据地址 */
#define AMHW_SPI0_TXDAT_ADDR  (&(AMHW_SPI0->txdat)) 

/** \brief SPI1 接收数据地址  */
#define AMHW_SPI1_RXDAT_ADDR  (&(AMHW_SPI1->rxdat)) 

/** \brief SPI1 发送数据地址 */
#define AMHW_SPI1_TXDAT_ADDR  (&(AMHW_SPI1->txdat)) 

/** @} */


/**
 * \name SPI 中断使能状态位定义
 * @{
 */
 
/** \brief SPI 接收就绪中断使能 */
#define AMHW_SPI_INTENSET_RXRDY           (1UL << 0)  

/** \brief SPI 发送就绪中断使能 */ 
#define AMHW_SPI_INTENSET_TXRDY           (1UL << 1)   

/** \brief SPI 接收溢出中断使能 */
#define AMHW_SPI_INTENSET_RXOVERRUN       (1UL << 2)   

/** \brief SPI 发送下溢（数据为空）中断使能 */
#define AMHW_SPI_INTENSET_TXUNDERRUN      (1UL << 3) 

/** \brief 从机片选有效中断使能 */
#define AMHW_SPI_INTENSET_SELNASSERT      (1UL << 4) 

/** \brief 从机片选未生效中断使能 */
#define AMHW_SPI_INTENSET_SELNDEASSERT    (1UL << 5)  

/** \brief 主机空闲中断使能 */ 
#define AMHW_SPI_INTENSET_MSTIDLE         (1UL << 8)   

/** @} */

/**
 * \name SPI 中断禁能状态位定义
 * @{
 */
 
/** \brief SPI 接收就绪中断禁能 */
#define AMHW_SPI_INTENCLR_RXRDY           (1UL << 0) 

/** \brief SPI 发送就绪中断禁能 */  
#define AMHW_SPI_INTENCLR_TXRDY           (1UL << 1) 

/** \brief SPI 接收溢出中断禁能 */
#define AMHW_SPI_INTENCLR_RXOVERRUN       (1UL << 2)

/** \brief SPI 发送下溢（数据为空）中断禁能 */  
#define AMHW_SPI_INTENCLR_TXUNDERRUN      (1UL << 3)   

/** \brief 从机片选有效中断禁能 */
#define AMHW_SPI_INTENCLR_SELNASSERT      (1UL << 4)  

/** \brief 从机片选未生效中断禁能 */
#define AMHW_SPI_INTENCLR_SELNDEASSERT    (1UL << 5) 

/** \brief 主机空闲中断禁能 */ 
#define AMHW_SPI_INTENCLR_MSTIDLE         (1UL << 8)   

/** @} */

/**
 * \name SPI 状态位定义
 * @{
 */
 
/** \brief 接收就绪状态 */
#define AMHW_SPI_STAT_RXRDY               (1UL << 0) 
 
/** \brief 发送就绪状态 */ 
#define AMHW_SPI_STAT_TXRDY               (1UL << 1)

/** \brief 接收溢出状态 */   
#define AMHW_SPI_STAT_RXOVERRUN           (1UL << 2)   

/** \brief 发送下溢状态 */
#define AMHW_SPI_STAT_TXUNDERRUN          (1UL << 3)  

/** \brief 从机选择有效状态 */ 
#define AMHW_SPI_STAT_SELNASSERT          (1UL << 4) 

/** \brief 从机选择无效状态  */  
#define AMHW_SPI_STAT_SELNDEASSERT        (1UL << 5)   
                                          
#define AMHW_SPI_STAT_CLKSTALL            (1UL << 6)   /**< \brief 失速状态 */
#define AMHW_SPI_STAT_EOF                 (1UL << 7)   /**< \brief 结束传输状态 */
#define AMHW_SPI_STAT_IDLE                (1UL << 8)   /**< \brief 主机空闲状态 */

/** @} */


/**
 * \name SPI 模式定义
 * @{
 */
 
#define AMHW_SPI_CFG_ENABLE               (1UL << 0)   /**< \brief SPI 控制器使能 */        
#define AMHW_SPI_CFG_MASTER               (1UL << 2)   /**< \brief SPI 主机模式使能 */        
#define AMHW_SPI_CFG_SLAVE                (0UL << 2)   /**< \brief SPI 从机模式使能 */        
#define AMHW_SPI_CFG_LSBF                 (1UL << 3)   /**< \brief 低字节先发送模式使能 */        
#define AMHW_SPI_CFG_LOOPBACK             (1UL << 7)   /**< \brief 环形模式使能（仅主机） */   
     
/** @} */

/**
 * \name SPI控制位定义
 * @{
 */

#define AMHW_SPI_TXDATCTL_MASK       (0xF7F0000)          /**< \brief 控制位掩码      */
#define AMHW_SPI_TXDATCTL_SSELN(s)   ((s) << 16)          /**< \brief 选择从机控制位   */
#define AMHW_SPI_TXDATCTL_EOT        (1UL << 20)          /**< \brief 结束传输控制位   */
#define AMHW_SPI_TXDATCTL_EOF        (1UL << 21)          /**< \brief 结束数据帧控制位 */
#define AMHW_SPI_TXDATCTL_RX_IGNORE  (1UL << 22)          /**< \brief 忽略接收控制位   */
#define AMHW_SPI_TXDATCTL_FSIZE(s)   (((s) & 0xFF) << 24) /**< \brief 数据帧长度控制位 */ 

/** @} */

/**
 * \brief SPI 从机输入/输出端口定义
 */
typedef enum amhw_slave {
    AMHW_SPI_SLAVE0 = ((~(1 << 0)) & 0xf),             /**< \brief SSEL0引脚有效 */
    AMHW_SPI_SLAVE1 = ((~(1 << 1)) & 0xf),             /**< \brief SSEL1引脚有效 */
    AMHW_SPI_SLAVE2 = ((~(1 << 2)) & 0xf),             /**< \brief SSEL2引脚有效 */
    AMHW_SPI_SLAVE3 = ((~(1 << 3)) & 0xf)              /**< \brief SSEL3引脚有效 */
} amhw_slave_t;

/**
 * \name SPI 工作模式
 * @{
 */ 

/** \brief SCK 复位状态(LOW)  SCK 数据改变跳边沿(falling)  SCK 数据采样跳边沿(rising) */
#define AMHW_SPI_MODE_0     ((0 << 4) |(0 << 5))  
 
/** \brief SCK 复位状态(LOW)  SCK 数据改变跳边沿(rising)  SCK 数据采样跳边沿(falling) */
#define AMHW_SPI_MODE_1     ((1 << 4) |(0 << 5))

/** \brief SCK 复位状态(HIGH) SCK 数据改变跳边沿(rising)  SCK 数据采样跳边沿(falling) */
#define AMHW_SPI_MODE_2     ((0 << 4) |(1 << 5)) 
     
/** \brief SCK 复位状态(HIGH) SCK 数据改变跳边沿(falling) SCK 数据采样跳边沿(rising) */
#define AMHW_SPI_MODE_3     ((1 << 4) |(1 << 5))

/**
 * @} 
 */
 
 
/**
 * \name 延时时间控制位定义
 * @{
 */
 
/** \brief 在SPI时钟线上SSEL有效和传输开始之间的延时 */
#define AMHW_SPI_PREDELAY(d)     ((d) << 0)  

/** \brief 在SPI时钟线上传输结束和SSEL无效之间的延时 */
#define AMHW_SPI_POSTDELAY(d)    ((d) << 4)   

/** \brief 在SPI时钟线上两个数据帧之间的延时 */
#define AMHW_SPI_FRAMEDELAY(d)   ((d) << 8) 

/** \brief 在SPI时钟线上两个传输之间的延时 */
#define AMHW_SPI_INTERDELAY(d)   ((d) << 12) 

/** @}  */


/**
 * \brief SPI 延时参数结构体
 */
typedef struct amhw_spi_mst_delay {
    uint8_t predelay;         /**< \brief SSEL有效和传输开始之间的延时 */
    uint8_t postdelay;        /**< \brief 传输结束和SSEL无效之间的延时 */                         
    uint8_t framedelay;       /**< \brief 两个数据帧之间的延时 */                       
    uint8_t transferdelay;    /**< \brief 两个传输之间的延时 */
} amhw_spi_mst_delay_t;

/**
 * \brief SPI 控制器禁能
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_spi_disable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->cfg &= ~AMHW_SPI_CFG_ENABLE;
} 

/**
 * \brief SPI 控制器使能
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_spi_enable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->cfg |= AMHW_SPI_CFG_ENABLE;
} 

/**
 * \brief SPI 主机延时参数配置
 *
 * \param[in] p_hw_spi    : 指向SPI寄存器块的指针
 * \param[in] p_spi_delay : 指向SPI延时参数结构体
 *
 * \return    无
 */
am_static_inline 
void amhw_spi_master_dly (amhw_spi_t           *p_hw_spi,
                          amhw_spi_mst_delay_t *p_spi_delay)
{
    p_hw_spi->dly = (AMHW_SPI_PREDELAY  (p_spi_delay->predelay)   |
                     AMHW_SPI_POSTDELAY (p_spi_delay->postdelay)  |
                     AMHW_SPI_FRAMEDELAY(p_spi_delay->framedelay) |
                     AMHW_SPI_INTERDELAY(p_spi_delay->transferdelay));
} 

/**
 * \brief SPI 中断使能
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] flags    : AM_SPI_INTENSET_* 宏值或多个
 *                       AM_SPI_INTENSET_*宏的 或（OR）值 (#AMHW_SPI_INTENSET_RXRDY)
 *
 * \return  None
 */

am_static_inline 
void amhw_spi_int_enable (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    p_hw_spi->intenset = flags;
}

/**
 * \brief SPI 中断禁能
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] flags    : AM_SPI_INTENCLR_* 宏值或多个
 *                       AM_SPI_INTENCLR_*宏的 或（OR）值 (#AMHW_SPI_INTENCLR_RXRDY)
 *
 * \return  无
 */
am_static_inline 
void amhw_spi_int_disable (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    p_hw_spi->intenclr = flags;
}

/**
 * \brief SPI 控制位设定 
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] flags    : AMHW_SPI_TXDATCTL_* 宏值或多个
 *                       AMHW_SPI_TXDATCTL_*宏的 或（OR）值(#AMHW_SPI_TXDATCTL_EOT)
 * \return  无
 */
am_static_inline 
void amhw_spi_txctl_set (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    uint32_t reg;

    reg             = (p_hw_spi->txctl) & AMHW_SPI_TXDATCTL_MASK;
    p_hw_spi->txctl = reg | flags;
}

/**
 * \brief SPI 控制位清除
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] flags    : AMHW_SPI_TXDATCTL_* 宏值或多个
 *                       AMHW_SPI_TXDATCTL_*宏的 或（OR）值(#AMHW_SPI_TXDATCTL_EOT)
 * \return  无
 */
am_static_inline 
void amhw_spi_txctl_clear (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    uint32_t reg;

    reg = (p_hw_spi->txctl) & AMHW_SPI_TXDATCTL_MASK;
    p_hw_spi->txctl = reg & ~flags;
}

/**
 * \brief 清除设定的状态位
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] flags    : AMHW_SPI_STAT_* 宏值或多个
 *                       AMHW_SPI_STAT_*宏的 或（OR）值(#AMHW_SPI_STAT_RXRDY)
 * \return  None
 */
am_static_inline 
void amhw_spi_stat_clear (amhw_spi_t *p_hw_spi, uint32_t flags)
{
    p_hw_spi->stat = flags;
}

/**
 * \brief 获取SPI的状态
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return  SPI状态
 */
am_static_inline 
uint32_t amhw_spi_stat_read (amhw_spi_t *p_hw_spi)
{
    return p_hw_spi->stat;
}

/**
 * \brief 获取SPI中断状态位
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return    中断状态寄存器的值
 */
am_static_inline 
uint32_t amhw_spi_intstat_read (amhw_spi_t *p_hw_spi)
{
    return p_hw_spi->intstat;
}

/**
 * \brief 获取SPI接收数据寄存器的值（8-bits）
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return    接收数据寄存器的值(低8位)
 */
am_static_inline 
uint8_t amhw_spi_rxdata_8bit_read (amhw_spi_t *p_hw_spi)
{
    return (p_hw_spi->rxdat & 0xFF);
}

/**
 * \brief 获取SPI接收数据寄存器的值 (16bits)
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return    接收数据寄存器的值
 */
am_static_inline 
uint16_t amhw_spi_rxdata_16bit_read (amhw_spi_t *p_hw_spi)
{
    return (p_hw_spi->rxdat & 0xFFFF);
}

/**
 * \brief 写数据到发送数据寄存器
 *
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \param[in] data     : 要发送的数据
 *
 * \return  无
 */
am_static_inline 
void amhw_spi_txdat_write (amhw_spi_t *p_hw_spi, uint16_t data)
{
    p_hw_spi->txdat = (uint32_t)data;
}

/**
 * \brief SPI传输忽略接收数据
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return  无
 */
am_static_inline 
void amhw_spi_ignore_recv_enable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) | 
                      AMHW_SPI_TXDATCTL_RX_IGNORE;
}

/**
 * \brief SPI传输不忽略接收数据
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return  无
 */
am_static_inline 
void amhw_spi_ignore_recv_disable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) & 
                      (~(AMHW_SPI_TXDATCTL_RX_IGNORE));
}

/**
 * \brief SPI 结束传输,SSEL将置为无效状态
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return  无
 */
am_static_inline 
void amhw_spi_end_trans_enable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) | 
                      AMHW_SPI_TXDATCTL_EOT;
}

/**
 * \brief SPI 正常传输，不会置SSEL为无效状态
 * \param[in] p_hw_spi : 指向SPI寄存器块的指针
 * \return  无
 */
am_static_inline 
void amhw_spi_end_trans_disable (amhw_spi_t *p_hw_spi)
{
    p_hw_spi->txctl = (p_hw_spi->txctl & AMHW_SPI_TXDATCTL_MASK) & 
                      (~(AMHW_SPI_TXDATCTL_EOT));
}

/** 
 * @} amhw_if_spi
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SPI_H */

/*end of file */

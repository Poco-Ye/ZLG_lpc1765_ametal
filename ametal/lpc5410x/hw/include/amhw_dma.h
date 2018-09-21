/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief DMA 硬件操作接口。
 *
 * 1. 22 个通道, 其中21个通道可连接外设通道请求。这些外设分别是USART、SPI和I2C等。
 *    剩下的1个通道不能连接到外设请求，但能够用于内存到内存的数据搬运；
 * 2. 片内或片外事件均能触发DMA运行.每个DMA通道均可选择20个输入触发源.触发源有
 *    ADC中断、定时器中断、引脚中断和SCT DMA请求列；
 * 3. 每个通道均可设定优先级（高达8个优先级设置）；
 * 4. 持续的优先级仲裁；
 * 5. 4个入口的cache地址（每个入口是地址的一部分）；
 * 6. 能有效使用与数据总线；
 * 7. 单次传输最多可传1024字；
 * 8. 地址增量可选择封装和/或不封装数据。
 *
 * \internal
 * \par Modification History
 * - 1.10 14-12-01  zen, refine the implementation.
 * - 1.00 14-11-24  hbt, first implementation.
 * \endinternal
 */

#ifndef __AMHW_DMA_H
#define __AMHW_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 
#include "am_common.h"

/**
 * \addtogroup amhw_if_dma
 * \copydoc amhw_dma.h
 * @{
 */

/** \brief DMA 通道数量 */
#define AMHW_DMA_CHAN_CNT           22

/**
 * \brief DMA 通道寄存器结构体
 */
typedef struct amhw_dma_chan {
    __IO  uint32_t  cfg;            /**< \brief DMA 通道配置寄存器       */
    __IO  uint32_t  ctlstat;        /**< \brief DMA 通道控制和状态寄存器 */
    __IO  uint32_t  xfercfg;        /**< \brief DMA 传输配置寄存器       */
    __IO  uint32_t  reserved;       /**< \brief 保留                     */
} amhw_dma_chan_t;

/**
 * \brief DMA 控制器寄存器块结构体 
 */
typedef struct amhw_dma {
    __IO  uint32_t    ctrl;          /**< \brief DMA 控制寄存器                */
    __IO  uint32_t    intstat;       /**< \brief DMA 中断状态寄存器            */
    __IO  uint32_t    srambase;      /**< \brief DMA 通道配置列表的SRAM地址    */
    __IO  uint32_t    reserved0[5];  /**< \brief 保留                          */
    __IO  uint32_t    enableset0;    /**< \brief 读和设置DMA通道使能寄存器     */
    __IO  uint32_t    reserved1;     /**< \brief 保留                          */
    __IO  uint32_t    enableclr0;    /**< \brief 清除DMA通道使能寄存器         */
    __IO  uint32_t    reserved2;     /**< \brief 保留                          */
    __IO  uint32_t    active0;       /**< \brief DMA通道有效状态寄存器         */
    __IO  uint32_t    reserved3;     /**< \brief 保留                          */
    __IO  uint32_t    busy0;         /**< \brief DMA通道busy状态寄存器         */
    __IO  uint32_t    reserved4;     /**< \brief 保留                          */
    __IO  uint32_t    errint0;       /**< \brief DMA 通道错误中断状态寄存器    */
    __IO  uint32_t    reserved5;     /**< \brief 保留                          */
    __IO  uint32_t    intenset0;     /**< \brief 读和设置DMA通道中断使能寄存器 */
    __IO  uint32_t    reserved6;     /**< \brief 保留                          */
    __IO  uint32_t    intenclr0;     /**< \brief 清除DMA通道中断使能寄存器     */
    __IO  uint32_t    reserved7;     /**< \brief 保留                          */
    __IO  uint32_t    inta0;         /**< \brief DMA A中断标志寄存器           */
    __IO  uint32_t    reserved8;     /**< \brief 保留                          */
    __IO  uint32_t    intb0;         /**< \brief DMA B中断标志寄存器           */
    __IO  uint32_t    reserved9;     /**< \brief 保留                          */
    __IO  uint32_t    setvalid0;     /**< \brief DMA通道有效等待控制位寄存器   */
    __IO  uint32_t    reserved10;    /**< \brief 保留                          */
    __IO  uint32_t    settrig0;      /**< \brief DMA通道触发控制位寄存器       */
    __IO  uint32_t    reserved11;    /**< \brief 保留                          */
    __IO  uint32_t    abort0;        /**< \brief DMA通道冻结控制位寄存器       */
    __IO  uint32_t    reserved12[225]; /**< \brief 保留                        */
    
    amhw_dma_chan_t chan[AMHW_DMA_CHAN_CNT];   /**< \brief DMA通道寄存器       */
    
} amhw_dma_t;

/**
 * \brief DMA 重载描述符
 * \attention 重载描述符的地址必须是16字节对齐
 */
typedef struct amhw_dma_xfer_desc {
    volatile uint32_t xfercfg;            /**< \brief 传输配置         */
    volatile uint32_t src_end_addr;       /**< \brief 源数据末地址     */
    volatile uint32_t dst_end_addr;       /**< \brief 目标数据末地址   */
    volatile uint32_t link;               /**< \brief 指向下一个描述符 */
} amhw_dma_xfer_desc_t;


/**
 * \brief 使能DMA控制器
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dma_enable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->ctrl = 1UL;
}

/**
 * \brief 禁能DMA控制器
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    无
 */
am_static_inline
void amhw_dma_disable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->ctrl = 0;
}

/**
 * \brief 获取DMA中断状态
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return    中断状态。
 */
am_static_inline
uint32_t amhw_dma_int_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat;
}

/**
 * \brief 是否有中断（除错误中断外）在等待处理
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 *
 * \retval  non-0      : 至少有一个中断在等待处理
 * \retval  0          : 无中断在等待处理
 */
am_static_inline
uint32_t amhw_dma_int_pending (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat & 0x02UL;
}

/**
 * \brief 是否有错误中断在等待处理
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 *
 * \retval  non-0      : 至少有一个错误中断在等待处理
 * \retval  0          : 无错误中断在等待处理
 */
am_static_inline
uint32_t amhw_dma_errint_pending (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat & 0x04UL;
}

/**
 * \brief 配置SRAM基地址
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] addr     : 通道描述符列表的起始地址，该地址必须是512字节对齐
 *
 * \return    无
 */
am_static_inline
void amhw_dma_sram_addr_set (amhw_dma_t *p_hw_dma, uint32_t addr)
{
    p_hw_dma->srambase = addr;
}

/**
 * \brief 获取SRAM基地址
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \return  通道描述符列表的起始地址，该地址必须是512字节对齐
 */
am_static_inline
uint32_t amhw_dma_sram_addr_get (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->srambase;
}

/**
 * \brief 获取通道描述符地址
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return  通道描述符地址
 */
am_static_inline
uint32_t amhw_dma_chan_desc_addr_get (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return (amhw_dma_sram_addr_get(p_hw_dma) + (chan << 4));
}

/**
 * \brief 使能DMA通道
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_enable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->enableset0 = (1UL << chan);
}

/**
 * \brief 禁能DMA通道
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_disable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->enableclr0 = (1UL << chan);
}

/**
 * \brief 指定通道是否有效
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 * 
 * \retval  non-0      : 通道有效
 * \retval  0          : 通道无效
 */
am_static_inline
uint32_t amhw_dma_chan_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->active0;
}

/**
 * \brief 指定通道是否busy
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 * 
 * \retval  non-0      : 通道busy
 * \retval  0          : 通道 unbusy
 */
am_static_inline
uint32_t amhw_dma_chan_busy (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->busy0 & (1UL << chan);
}

/**
 * \brief 指定通道的错误中断是否有效
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针。
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : 通道的错误中断有效
 * \retval  0          : 通道的错误中断无效
 */
am_static_inline
uint32_t amhw_dma_chan_errint_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->errint0 & (1UL << chan);
}

/**
 * \brief 清指定通道的错误中断
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_errint_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->errint0 = (1UL << chan);
}

/**
 * \brief 使能DMA通道中断
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_int_enable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->intenset0 = (1UL << chan);
}

/**
 * \brief 禁能DMA通道中断
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_int_disable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->intenclr0 = (1UL << chan);
}

/**
 * \brief 获取错误中断标志
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 *
 * \return    错误中断标志, bit[21:0] 是错误标志位域，Bit n 对应通道 n
 */
am_static_inline
uint32_t amhw_dma_errint_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->errint0;
}

/**
 * \brief 通过掩码清除错误中断标志
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] mask     : bit[21:0] 对应DMA通道 n， 该清除位必须与 ERRINT 相对应.
 *
 * \return    无
 */
am_static_inline
void amhw_dma_errint_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->errint0 = mask;
}

/**
 * \brief 获取A中断状态。
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 *
 * \return    A中断标志，bit[21:0] 是DMA通道 n 的A中断标志，Bit n 对应DMA通道 n 
 */
am_static_inline
uint32_t amhw_dma_inta_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->inta0;
}

/**
 * \brief 通过掩码清除A中断标志
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] mask     : bit[21:0] 对应DMA通道 n, 该被清除为必须与 NTA 相对应。
 *
 * \return    无
 */
am_static_inline
void amhw_dma_inta_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->inta0 = mask;
}

/**
 * \brief 指定通道的A中断是否有效
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : 通道的A中断有效
 * \retval  0          : 通道的A中断无效
 */
am_static_inline
uint32_t amhw_dma_chan_inta_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->inta0 & (1UL << chan);
}

/**
 * \brief 清除指定通道的A中断标志
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_inta_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->inta0 = (1UL << chan);
}

/**
 * \brief 获取B中断状态
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 *
 * \return    B中断标志，bit[21:0] 是DMA通道 n 的B中断标志，Bit n 对应DMA通道 n 。
 */
am_static_inline
uint32_t amhw_dma_intb_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intb0;
}

/**
 * \brief 通过掩码清除B中断标志
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] mask     : bit[21:0] 对应DMA通道 n, 该被清除为必须与 NTB 相对应。
 *
 * \return    无
 */
am_static_inline
void amhw_dma_intb_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->intb0 = mask;
}

/**
 * \brief 指定通道的B中断是否有效
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : 通道的B中断有效
 * \retval  0          : 通道的B中断无效
 */
am_static_inline
uint32_t amhw_dma_chan_intb_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->intb0 & (1UL << chan);
}

/**
 * \brief 清除指定通道的B中断标志
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_intb_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->intb0 = (1UL << chan);
}

/**
 * \brief 指定通道有效
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_set_valid (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->setvalid0 |= (1UL << chan);
}

/**
 * \brief 设置DMA通道触发位
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_set_trig (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->settrig0 |= (1UL << chan);
}

/**
 * \brief 冻结DMA通道
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_abort (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->abort0 |= (1UL << chan);
}


/**
 * \name 定义通道配置参数
 * \anchor grp_amhw_dma_chan_cfg_flags
 * @{
 */

#define AMHW_DMA_CHAN_PERIPH_REQ_OFF     0            /**< \brief 禁能外设DMA请求。 */
#define AMHW_DMA_CHAN_PERIPH_REQ_EN      AM_BIT(0)    /**< \brief 使能外设DMA请求。 */

#define AMHW_DMA_CHAN_HWTRIG_OFF         0                                   /**< \brief 禁止硬件触发。             */
#define AMHW_DMA_CHAN_HWTRIG_FALL        AM_BIT(1)                           /**< \brief DMA 硬件触发：下降沿敏感。 */
#define AMHW_DMA_CHAN_HWTRIG_RISE       (AM_BIT(1) | AM_BIT(4))              /**< \brief DMA 硬件触发：上升沿敏感。 */
#define AMHW_DMA_CHAN_HWTRIG_LOW        (AM_BIT(1) | AM_BIT(5))              /**< \brief DMA 硬件触发：低电平敏感。 */
#define AMHW_DMA_CHAN_HWTRIG_HIGH       (AM_BIT(1) | AM_BIT(4) | AM_BIT(5))  /**< \brief DMA 硬件触发：高电平敏感。 */

#define AMHW_DMA_CHAN_SINGLE_TRANS       0                           /**< \brief 硬件触发引起单次传输。                  */
#define AMHW_DMA_CHAN_BURST_1           (AM_BIT(6) | AM_SBF(0,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 1    */
#define AMHW_DMA_CHAN_BURST_2           (AM_BIT(6) | AM_SBF(1,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 2    */
#define AMHW_DMA_CHAN_BURST_4           (AM_BIT(6) | AM_SBF(2,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 4    */
#define AMHW_DMA_CHAN_BURST_8           (AM_BIT(6) | AM_SBF(3,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 8    */
#define AMHW_DMA_CHAN_BURST_16          (AM_BIT(6) | AM_SBF(4,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 16   */
#define AMHW_DMA_CHAN_BURST_32          (AM_BIT(6) | AM_SBF(5,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 32   */
#define AMHW_DMA_CHAN_BURST_64          (AM_BIT(6) | AM_SBF(6,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 64   */
#define AMHW_DMA_CHAN_BURST_128         (AM_BIT(6) | AM_SBF(7,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 128  */
#define AMHW_DMA_CHAN_BURST_256         (AM_BIT(6) | AM_SBF(8,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 256  */
#define AMHW_DMA_CHAN_BURST_512         (AM_BIT(6) | AM_SBF(9,  8))  /**< \brief 硬件触发引起突发传输，Burst size = 512  */
#define AMHW_DMA_CHAN_BURST_1024        (AM_BIT(6) | AM_SBF(10, 8))  /**< \brief 硬件触发引起突发传输，Burst size = 1024 */

#define AMHW_DMA_CHAN_SRC_BURST_NO_WRAP  0              /**< \brief 源端突发不环绕。    */
#define AMHW_DMA_CHAN_DST_BURST_NO_WRAP  0              /**< \brief 目标端突发不环绕。  */
#define AMHW_DMA_CHAN_SRC_BURST_WRAP     AM_BIT(14)     /**< \brief 源端突发环绕。      */
#define AMHW_DMA_CHAN_DST_BURST_WRAP     AM_BIT(15)     /**< \brief 目标端突发环绕。    */

#define AMHW_DMA_CHAN_PRIO_0             AM_SBF(0, 16)  /**< \brief 通道优先级 0 (0 为最高优先级) */
#define AMHW_DMA_CHAN_PRIO_1             AM_SBF(1, 16)  /**< \brief 通道优先级 1 (0 为最高优先级) */
#define AMHW_DMA_CHAN_PRIO_2             AM_SBF(2, 16)  /**< \brief 通道优先级 2 (0 为最高优先级) */
#define AMHW_DMA_CHAN_PRIO_3             AM_SBF(3, 16)  /**< \brief 通道优先级 3 (0 为最高优先级) */
#define AMHW_DMA_CHAN_PRIO_4             AM_SBF(4, 16)  /**< \brief 通道优先级 4 (0 为最高优先级) */
#define AMHW_DMA_CHAN_PRIO_5             AM_SBF(5, 16)  /**< \brief 通道优先级 5 (0 为最高优先级) */
#define AMHW_DMA_CHAN_PRIO_6             AM_SBF(6, 16)  /**< \brief 通道优先级 6 (0 为最高优先级) */
#define AMHW_DMA_CHAN_PRIO_7             AM_SBF(7, 16)  /**< \brief 通道优先级 7 (0 为最高优先级) */

/** @} */


/**
 * \brief DMA 通道配置
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] flags    : 配置参数，参见
 *                       \ref grp_amhw_dma_chan_cfg_flags "Channel Configuration Flags"
 * \return    无
 */
am_static_inline
void amhw_dma_chan_cfg_set (amhw_dma_t *p_hw_dma, unsigned int chan, uint32_t flags)
{
    p_hw_dma->chan[chan].cfg = flags;
}

/**
 * \brief 指定通道是否有效等待
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : 有效等待。
 * \retval  0          : 无有效DMA操作。
 */
am_static_inline
uint32_t amhw_dma_chan_valid_pending (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->chan[chan].ctlstat & (1UL << 0);
}

/**
 * \brief 当前通道触发是否被置位
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : 当前通道触发被置位，DMA传输被执行
 * \retval  0          : 当前通道触发未被置位，DMA传输不被执行
 */
am_static_inline
uint32_t amhw_dma_chan_triggered (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->chan[chan].ctlstat & (1UL << 2);
}


/**
 * \name 定义传输配置参数
 * \anchor grp_amhw_dma_chan_xfercfg_flags
 * @{
 */

#define AMHW_DMA_XFER_CFG_INVALID      0              /**< \brief 除非对应的 SETVALID0 被置位， 要不然当前通道描述符一直无效。 */
#define AMHW_DMA_XFER_CFG_VALID        AM_BIT(0)      /**< \brief 当前通道描述符有效。                                         */

#define AMHW_DMA_XFER_NO_RELOAD        0              /**< \brief 当前描述符传输完成时，不重载新的通道描述符。 */
#define AMHW_DMA_XFER_RELOAD           AM_BIT(1)      /**< \brief 当前描述符传输完成时，重载新的通道描述符。   */

#define AMHW_DMA_XFER_NO_SWTRIG        0              /**< \brief 当前通道不使用软件触发。             */
#define AMHW_DMA_XFER_SWTRIG           AM_BIT(2)      /**< \brief 当前通道使用软件触发，马上进行传输。 */

#define AMHW_DMA_XFER_NO_CLRTRIG       0              /**< \brief 当前描述符传输完成时，触发信号不被清除。 */
#define AMHW_DMA_XFER_CLRTRIG          AM_BIT(3)      /**< \brief 当前描述符传输完成时，触发信号被清除。   */

#define AMHW_DMA_XFER_SETINTA          AM_BIT(4)      /**< \brief 当前描述符传输完成时，该通道的A中断标志置位。 */
#define AMHW_DMA_XFER_SETINTB          AM_BIT(5)      /**< \brief 当前描述符传输完成时，该通道的B中断标志置位。 */

#define AMHW_DMA_XFER_WIDTH_8BIT       AM_SBF(0, 8)   /**< \brief 执行 8-bit 传输 (源数据读和目标数据写均为 8-bit)。   */
#define AMHW_DMA_XFER_WIDTH_16BIT      AM_SBF(1, 8)   /**< \brief 执行 16-bit 传输 (源数据读和目标数据写均为 16-bit)。 */
#define AMHW_DMA_XFER_WIDTH_32BIT      AM_SBF(2, 8)   /**< \brief 执行 32-bit 传输 (源数据读和目标数据写均为 32-bit)。 */
#define AMHW_DMA_XFER_WIDTH_MASK       AM_SBF(0x3, 8) /**< \brief 传输位宽掩码。                                       */

#define AMHW_DMA_XFER_NO_SRCINC        AM_SBF(0, 12)  /**< \brief 每次传输源地址不增加。              */
#define AMHW_DMA_XFER_SRCINC_1X_WIDTH  AM_SBF(1, 12)  /**< \brief 每次传输源地址增加1个指定数据宽度。 */
#define AMHW_DMA_XFER_SRCINC_2X_WIDTH  AM_SBF(2, 12)  /**< \brief 每次传输源地址增加2个指定数据宽度。 */
#define AMHW_DMA_XFER_SRCINC_4X_WIDTH  AM_SBF(3, 12)  /**< \brief 每次传输源地址增加4个指定数据宽度。 */

#define AMHW_DMA_XFER_NO_DSTINC        AM_SBF(0, 14)  /**< \brief 每次传输目标地址不增加。              */ 
#define AMHW_DMA_XFER_DSTINC_1X_WIDTH  AM_SBF(1, 14)  /**< \brief 每次传输目标地址增加1个指定数据宽度。 */ 
#define AMHW_DMA_XFER_DSTINC_2X_WIDTH  AM_SBF(2, 14)  /**< \brief 每次传输目标地址增加2个指定数据宽度。 */
#define AMHW_DMA_XFER_DSTINC_4X_WIDTH  AM_SBF(3, 14)  /**< \brief 每次传输目标地址增加4个指定数据宽度。 */

#define AMHW_DMA_XFERCOUNT(n)          AM_SBF(n, 16)  /**< \brief 传输总次数，最少为1次。  */

/** @} */

/**
 * \brief 设置DMA通道的配置参数
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] flags    : 配置参数，参见
 *                       \ref grp_amhw_dma_chan_xfercfg_flags "Transfer Configuration Flags"
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_xfercfg_set (amhw_dma_t   *p_hw_dma, 
                                unsigned int  chan, 
                                uint32_t      flags)
{
    p_hw_dma->chan[chan].xfercfg = flags;
}

/**
 * \brief 指定通道使能A中断
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_inta_set (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg |= AM_BIT(4);
}

/**
 * \brief 指定通道使能B中断
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_intb_set (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg |= AM_BIT(5);
}

/**
 * \brief 清除指定通道的A中断配置
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_inta_clr (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg &= ~AM_BIT(4);
}

/**
 * \brief 清除指定通道的B中断配置
 *
 * \param[in] p_hw_dma : 指向DMA控制器寄存器块的指针
 * \param[in] chan     : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    无
 */
am_static_inline
void amhw_dma_chan_intb_clr (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg &= ~AM_BIT(5);
}

/**
 * @} amhw_if_dma
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_DMA_H */

/* end of file */

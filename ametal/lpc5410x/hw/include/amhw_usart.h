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
 * \brief 串口（USART）操作接口
 *
 * 1. 支持7、8、9三种数据宽度，支持1位、2位停止位；
 * 2. 主机模式和从机模式均支持同步模式传输，包括数据相位选择和持续时钟设置；
 * 3. 多主机模式(9位数据位)支持软件地址匹配；
 * 4. 支持RS-485 收发器输出使能；
 * 5. 奇偶校验的产生和检查：支持奇校验、偶校验和无校验；
 * 6. 在异步模式下，软件可编程过采样时钟数，支持5 ~ 16时钟采样；
 * 7. 一个发送和一个接收数据缓冲区；
 * 8. 系统FIFO支持；
 * 9. RTS/CTS 硬件信号用于自动流控制. 软件流控制可以使用Delta CTS 检测，发送禁能
 *   控制和一个任意的IO口（用于产生RTS信号）实现；
 * 10. 接收数据和状态可以从一个寄存器中一次性读出；
 * 11. 中断(Break)产生和发现；
 * 12. 接收数据采用多次采样，超过2/3的电平值为最终采样值；
 * 13. 内建波特率产生器，支持自动波特率特性；
 * 14. 一个小数分频器用于所有的串口。用于产生更高精度的波特率；
 * 15. 中断(Interrupt)支持: 接收准备就绪， 发送准备就绪，接收空闲，接收break检测到变化，
 *     帧错误，奇偶校验错误，溢出，Delta CTS 检测，接收采样噪声检测；
 * 16. 回路模式，用于测试数据和流控制；
 * 17. 特殊运行模式，使用32kHz的RTC晶体振荡器作为时钟源，允许运行在最高9600波特率
 *     下，该模式可以在掉电模式(Power-down mode)下使用串口，并可以在接收到一个字符
 *     时唤醒设备；
 * 18. USART 发送和接收可以使用DMA控制器。
 *
 * \internal
 * \par Modification History
 * - 1.01 14-12-03  jon, add USART interrupt mode.
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_USART_H
#define __AMHW_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_if_usart
 * \copydoc amhw_usart.h
 * @{
 */

/**
 * \brief USART 寄存器块结构体
 */
typedef struct amhw_usart {
    __IO uint32_t cfg;         /**< \brief USART 配置寄存器             */
    __IO uint32_t ctl;         /**< \brief USART 控制寄存器             */
    __IO uint32_t stat;        /**< \brief USART 状态寄存器             */
    __IO uint32_t int_enset;   /**< \brief 中断使能寄存器               */
    __O  uint32_t int_enclr;   /**< \brief 中断使能寄存器位清除寄存器   */
    __I  uint32_t rxdat;       /**< \brief 接收数据寄存器.              */
    __I  uint32_t rxdatstat;   /**< \brief 接收数据和接收状态寄存器     */
    __IO uint32_t txdat;       /**< \brief 发送数据寄存器               */
    __IO uint32_t brg;         /**< \brief 波特率产生寄存器             */
    __I  uint32_t intstat;     /**< \brief 中断状态寄存器               */
    __IO uint32_t osr;         /**< \brief 过采样选择寄存器             */
    __IO uint32_t addr;        /**< \brief 地址寄存器                   */
} amhw_usart_t;


/**
 * \name 串口数据寄存器地址定义，(可能由DMA用到)
 * @{
 */

/** \brief USART0 接收数据寄存器地址  */
#define AMHW_USART0_RXDAT_ADDR  (&(AMHW_USART0->rxdat))

/** \brief USART0 发送数据寄存器地址  */
#define AMHW_USART0_TXDAT_ADDR  (&(AMHW_USART0->txdat))

/** \brief USART1 接收数据寄存器地址  */
#define AMHW_USART1_RXDAT_ADDR  (&(AMHW_USART1->rxdat))

/** \brief USART1 发送数据寄存器地址  */
#define AMHW_USART1_TXDAT_ADDR  (&(AMHW_USART1->txdat))

/** \brief USART2 接收数据寄存器地址  */
#define AMHW_USART2_RXDAT_ADDR  (&(AMHW_USART2->rxdat))

/** \brief USART2 发送数据寄存器地址  */
#define AMHW_USART2_TXDAT_ADDR  (&(AMHW_USART2->txdat))

/** \brief USART3 接收数据寄存器地址  */
#define AMHW_USART3_RXDAT_ADDR  (&(AMHW_USART3->rxdat))

/** \brief USART3 发送数据寄存器地址  */
#define AMHW_USART3_TXDAT_ADDR  (&(AMHW_USART3->txdat))

/** @} */


/**
 * \name 数据长度定义
 * @{
 */

#define AMHW_USART_CFG_7BIT         0       /**< \brief 7位数据长度      */
#define AMHW_USART_CFG_8BIT        (1 << 2) /**< \brief 8位数据长度      */
#define AMHW_USART_CFG_9BIT        (1 << 3) /**< \brief 9位数据长度      */

/** @} */

/**
 * \name 奇偶校验定义
 * @{
 */

#define AMHW_USART_CFG_PARITY_NO     0        /**< \brief 不使用奇偶校验      */
#define AMHW_USART_CFG_PARITY_EVEN  (2 << 5)  /**< \brief 偶校验              */
#define AMHW_USART_CFG_PARITY_ODD   (3 << 4)  /**< \brief 奇校验              */

/** @} */

/**
 * \brief 停止位长度
 * @{
 */

#define AMHW_USART_CFG_STOP_1     0        /**< \brief 1位停止位    */
#define AMHW_USART_CFG_STOP_2    (1 << 6)  /**< \brief 2位停止位    */

/** @} */


/** \brief USART时钟使用 32KHz RTC 晶体振荡器时钟  */
#define AMHW_USART_CFG_MODE32K   (1 << 7)

/** \brief Break 检测和产生，用于 LIN 总线模式     */
#define AMHW_USART_CFG_LINMODE   (1 << 8)

/** \brief 使能硬件流控制                          */
#define AMHW_USART_CFG_HWFLOW    (1 << 9)
 
/** \brief 使能同步模式                            */
#define AMHW_USART_CFG_SYNMODE   (1 << 11)

/**
 * \brief 用于同步模式，数据采样在SCLK的下降沿 
 *        (必须与#AMHW_USART_CFG_SYNMODE宏一起使用，不可单独使用)
 */
#define AMHW_USART_CFG_FALLING    0

/**
 * \brief 用于同步模式，数据采样在SCLK的上升沿 
 *        (必须与#AMHW_USART_CFG_SYNMODE宏一起使用，不可单独使用)
 */
#define AMHW_USART_CFG_RISING    (1 << 12)

/**
 * \brief 用于同步模式，串口工作在主机模式
 *        (必须与#AMHW_USART_CFG_SYNMODE宏一起使用，不可单独使用)
 */
#define AMHW_USART_CFG_MASTER    (1 << 14)

/** \brief 串口将工作在回路模式(LoopBack mode) */
#define AMHW_USART_CFG_LOOPBACK  (1 << 15)

/** \brief 串口工作在 IrDA 模式               */
#define AMHW_USART_CFG_IRDAMHODE (1 << 16)

/**
 * \brief 用于RS-485模式: RTS 用于控制RS-485收发器的输出使能
 */
#define AMHW_USART_CFG_OESEL     (1 << 20)

/**
 * \brief 用于RS-485模式: 输出使能失效(De-assertion)信号将会在延迟一个字符时间
 *        需要与 #AMHW_USART_CFG_OESEL 宏一起使用
 */
#define AMHW_USART_CFG_OETA      (1 << 18)

/**
 * \brief 自动地址匹配使能，当地址匹配模式被使能后（#AMHW_USART_CTL_ADDRDET）。
 *        地址匹配通过硬件完成，使用地址寄存器中的值完成地址匹配
 */
#define AMHW_USART_CFG_AUTOADDR  (1 << 19)

/**
 * \brief 用于RS-485模式: 输出使能信号高电平有效，否则，默认情况下是低电平有效
 */
#define AMHW_USART_CFG_OEPOLHIGH (1 << 21)

/**
 * \brief 颠倒接收数据管脚的电平极性
 */
#define AMHW_USART_CFG_RXPOL     (1 << 22)

/**
 * \brief 颠倒发送数据管脚的点平极性
 */
#define AMHW_USART_CFG_TXPOL     (1 << 23)

/**
 * \name USART控制标志，这些标志用于函数 amhw_usart_control().
 * @{
 */

#define AMHW_USART_CTL_TXBRKEN   (1 << 1)  /**< \brief 持续break模式          */
#define AMHW_USART_CTL_ADDRDET   (1 << 2)  /**< \brief 使能地址匹配模式       */
#define AMHW_USART_CTL_TXDIS     (1 << 6)  /**< \brief 发送禁能               */
#define AMHW_USART_CTL_CC        (1 << 8)  /**< \brief 持续时钟产生           */
#define AMHW_USART_CTL_CLRCCONRX (1 << 9)  /**< \brief 接收到一个字符时清除CC位 */
#define AMHW_USART_CTL_AUTOBAUD  (1 << 16) /**< \brief 自动波特率使能         */

/** @} */

/**
 * \name USART状态标志
 * @{
 */

#define AMHW_USART_STAT_RXRDY    (1 << 0)   /**< \brief 接收准备就绪          */
#define AMHW_USART_STAT_RXIDLE   (1 << 1)   /**< \brief 接收空闲              */
#define AMHW_USART_STAT_TXRDY    (1 << 2)   /**< \brief 发送准备就绪          */
#define AMHW_USART_STAT_TXIDLE   (1 << 3)   /**< \brief 发送空闲              */

/** \brief 该位实时反映当前的CTS信号状态  */
#define AMHW_USART_STAT_CTS      (1 << 4)

/**
 * \brief 表明检测到CTS信号发生变化，该标志由软件清除
 */
#define AMHW_USART_STAT_DELTACTS (1 << 5)

#define AMHW_USART_STAT_TXDIS    (1 << 6)   /**< \brief 发送禁能状态标志      */
#define AMHW_USART_STAT_OVR      (1 << 8)   /**< \brief 溢出错误标志          */
#define AMHW_USART_STAT_BREAK    (1 << 10)  /**< \brief 接收中断标志          */

/**
 * \brief 表明检测到接收break状态变化，该标志由软件清除
 */
#define AMHW_USART_STAT_DELTARXBRK    (1 << 11)

/**
 * 表明接收器检测到起始（START）信号
 */
#define AMHW_USART_STAT_START       (1 << 12)

#define AMHW_USART_STAT_FRMERR      (1 << 13)  /**< \brief 帧错误标志         */
#define AMHW_USART_STAT_PARERR      (1 << 14)  /**< \brief 奇偶校验错误标志   */
#define AMHW_USART_STAT_RXNOISE     (1 << 15)  /**< \brief 接收噪声标志       */
#define AMHW_USART_STAT_ABAUDERR    (1 << 16)  /**< \brief 自动波特率错误标志 */

/** @} */

/**
 * \name USART串口中断状态标志，可以通过函数am_uart_intstat_get()获取中断状态
 * @{
 */

#define AMHW_USART_INTSTAT_RXRDY      (1 << 0) /**< \brief 接收准备就绪       */
#define AMHW_USART_INTSTAT_TXRDY      (1 << 2) /**< \brief 发送准备就绪       */
#define AMHW_USART_INTSTAT_TXIDLE     (1 << 3) /**< \brief 发送空闲           */

/**
 * \brief 表明检测到CTS信号发生变化。
 */
#define AMHW_USART_INTSTAT_DELTACTS   (1 << 5)

#define AMHW_USART_INTSTAT_TXDIS      (1 << 6) /**< \brief 发送禁能中断标志   */
#define AMHW_USART_INTSTAT_OVR        (1 << 8) /**< \brief 溢出中断标志       */


/**
 * \brief 表明检测到接收break状态变化
 */
#define AMHW_USART_INTSTAT_DELTARXBRK (1 << 11)

/**
 * \brief 接收器检测到起始（START）信号
 */
#define AMHW_USART_INTSTAT_START     (1 << 12)

#define AMHW_USART_INTSTAT_FRMERR    (1 << 13) /**< \brief 帧错误中断         */
#define AMHW_USART_INTSTAT_PARERR    (1 << 14) /**< \brief 奇偶校验错误中断   */
#define AMHW_USART_INTSTAT_RXNOISE   (1 << 15) /**< \brief 接收噪声中断       */
#define AMHW_USART_INTSTAT_ABAUDERR  (1 << 16) /**< \brief 自动波特率错误中断 */

/** @} interrupt state */

/**
 * \name 串口中断源定义
 * @{
 */

#define AMHW_USART_INT_RXRDY      (1 << 0) /**< \brief 接收准备就绪           */
#define AMHW_USART_INT_TXRDY      (1 << 2) /**< \brief 发送准备就绪           */
#define AMHW_USART_INT_TXIDLE     (1 << 3) /**< \brief 发送空闲               */
#define AMHW_USART_INT_DELTACTS   (1 << 5) /**< \brief 检测到CTS信号发生变化  */
#define AMHW_USART_INT_TXDIS      (1 << 6) /**< \brief 发送器禁止中断         */
#define AMHW_USART_INT_OVR        (1 << 8) /**< \brief 溢出中断               */

/** \brief 检测到接收break状态变化       */
#define AMHW_USART_INT_DELTARXBRK     (1 << 11)

/** \brief 接收器检测到起始（START）信号 */
#define AMHW_USART_INT_START          (1 << 12)

#define AMHW_USART_INT_FRMERR      (1 << 13) /**< \brief 帧错误中断           */
#define AMHW_USART_INT_PARERR      (1 << 14) /**< \brief 奇偶校验错误中断     */
#define AMHW_USART_INT_RXNOISE     (1 << 15) /**< \brief 接收噪声中断         */
#define AMHW_USART_INT_ABAUDERR    (1 << 16) /**< \brief 自动波特率错误中断   */

#define AMHW_USART_INT_ALL         (0x1F96D) /**< \brief 所有中断             */

/** @} */

/**
 * \brief 配置串口
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] cfg_flags  : AMHW_USART_CFG_*宏值或多个AMHW_USART_CFG_*宏的或值
 *                         (#AMHW_USART_CFG_8BIT)
 *
 * \return 无
 *
 * \note 如果串口的时钟源是RTC晶体振荡器输出时钟，则其频率为32.768KHz，则必须
 *       使用#AMHW_USART_CFG_MODE32K 标志。配置前，确保串口处于禁能状态。
 *       通过调用函数 amhw_usart_disable()。
 */
am_static_inline
void amhw_usart_config (amhw_usart_t *p_hw_usart, uint32_t cfg_flags)
{
    p_hw_usart->cfg = cfg_flags;
}

/**
 * \brief 设置串口控制寄存器值
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] ctl_flags  :  AMHW_USART_CTL_*宏值或多个AMHW_USART_CTL_*宏的或值
 *                         (#AMHW_USART_CTL_ADDRDET)
 * \return 无
 */
am_static_inline
void amhw_usart_control (amhw_usart_t *p_hw_usart, uint32_t ctl_flags)
{
    p_hw_usart->ctl = ctl_flags;
}

/**
 * \brief 设置控制寄存器的相应位为1
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] flags      : AMHW_USART_CTL_*宏值或多个AMHW_USART_CTL_*宏的或值
 *                         (#AMHW_USART_CTL_ADDRDET)。未设置的位不受影响。
 *
 * \return 无
 */
am_static_inline
void amhw_usart_ctl_set (amhw_usart_t *p_hw_usart, uint32_t flags)
{
    p_hw_usart->ctl |= flags;
}

/**
 * \brief 清零控制寄存器
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] flags      : AMHW_USART_CTL_*宏值或多个AMHW_USART_CTL_*宏的或值
 *                         (#AMHW_USART_CTL_ADDRDET)。未设置的位不受影响。
 *
 * \return 无
 */
am_static_inline
void amhw_usart_ctl_clr (amhw_usart_t *p_hw_usart, uint32_t flags)
{
    p_hw_usart->ctl &= ~flags;
}

/**
 * \brief 使能串口
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_usart_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->cfg |= 0x01;
}

/**
 * \brief 禁能串口
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_usart_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->cfg &= ~(0x01);
}

/**
 * \brief 获取串口状态
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \return 串口状态，AMHW_USART_STAT_*宏值或多个AMHW_USART_STAT_*宏的或值
 *         （#AMHW_USART_STAT_OVR）
 */
am_static_inline
uint32_t amhw_usart_stat_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->stat;
}

/**
 * \brief 等待串口发送空闲
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \return 无
 */
am_static_inline
void amhw_usart_wait_idle (amhw_usart_t *p_hw_usart)
{
    while ((p_hw_usart->stat & AMHW_USART_STAT_TXIDLE) == 0);
}

/**
 * \brief 清除串口状态标志
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] clr_flags  : AMHW_USART_STAT_*宏值或多个AMHW_USART_STAT_*宏的或值
 *                         (#AMHW_USART_STAT_START)
 *
 * \return 无
 *
 * \note 大多数标志是自动清除.少部分标志才需要软件清除:
 *       #AMHW_USART_STAT_DELTACTS, #AMHW_USART_STAT_OVR, #AMHW_USART_STAT_DELTARXBRK,
 *       #AMHW_USART_STAT_START, #AMHW_USART_STAT_FRMERR, #AMHW_USART_STAT_PARERR
 *       #AMHW_USART_STAT_RXNOISE, #AMHW_USART_STAT_ABAUDERR
 */
am_static_inline
void amhw_usart_stat_clr (amhw_usart_t *p_hw_usart, uint32_t clr_flags)
{
    p_hw_usart->stat = clr_flags;
}

/**
 * \brief 得到串口中断状态
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \return AMHW_USART_INTSTAT_*宏值或多个AMHW_USART_INTSTAT_*宏的或值
 *         (#AMHW_USART_INTSTAT_RXRDY)
 */
am_static_inline
uint32_t amhw_usart_intstat_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->intstat;
}

/**
 * \brief 使能指定的串口中断
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] int_enable : AMHW_USART_INT_* 宏值或多个AMHW_USART_INT_*宏的或值
 *                         (#AMHW_USART_INT_RXRDY)
 *
 * \return 无
 */
am_static_inline
void amhw_usart_int_enable (amhw_usart_t *p_hw_usart, uint32_t int_enable)
{
     p_hw_usart->int_enset |= int_enable;
}

/**
 * \brief 禁能指定的串口中断
 *
 * \param[in] p_hw_usart  : 指向串口寄存器块的指针
 * \param[in] int_disable : AMHW_USART_INT_* 宏值或多个AMHW_USART_INT_*宏的或值
 *                          (#AMHW_USART_INT_RXRDY)
 *
 * \return 无
 */
am_static_inline
void amhw_usart_int_disable (amhw_usart_t *p_hw_usart, uint32_t int_disable)
{
     p_hw_usart->int_enclr = int_disable;
}

/**
 * \brief 写串口发送寄存器值（发送一个数据）
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] data       : 发送的数据
 *
 * \return 无
 */
am_static_inline
void amhw_usart_txdata_write (amhw_usart_t *p_hw_usart, uint32_t data)
{
     p_hw_usart->txdat = data;
}

/**
 * \brief 读取串口接收数据
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \return 串口接收到的数据
 */
am_static_inline
uint32_t amhw_usart_rxdata_read (amhw_usart_t *p_hw_usart)
{
     return p_hw_usart->rxdat;
}

/**
 * \brief 读取串口接收数据，同时包含接收相关状态
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \return 读取到的值
 *          - bit0 ~ bit8 : 接收到的数据
 *          - bit13       : 帧错误状态
 *          - bit14       : 奇偶校验错误状态
 *          - bit15       : 接收噪声
 */
am_static_inline
uint32_t amhw_usart_rxdata_stat_read (amhw_usart_t *p_hw_usart)
{
     return p_hw_usart->rxdatstat;
}

/**
 * \brief 设置串口波特率产生寄存器值
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] brg_val    : 设置值，串口时钟将被(brg_val + 1)分频
 *
 * \return 无
 *
 * \note 串口波特率产生器是一个简单的16位整数分频器。在32k RTC作为时钟源时，该分
 *       频器仍然有效，如果要得到9600的波特率，该值就必须设置为0.
 *       在设置值前，确保串口没有正在进行发送和接收。
 */
am_static_inline
void amhw_usart_brg_set (amhw_usart_t *p_hw_usart, uint16_t brg_val)
{
    p_hw_usart->brg = brg_val;
}

/**
 * \brief 设置过采样值
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] osr_val    : 发送和接收每位使用(osr_val + 1)个时钟进行采样，有效值
 *                         为 4 ~ 15.
 *
 * \return 无
 *
 * \note OSR寄存器允许设置异步模式下的过采样值，默认采样值是16。
 */
am_static_inline
void amhw_usart_osr_set (amhw_usart_t *p_hw_usart, uint8_t osr_val)
{
    if (osr_val >= 4 && osr_val <= 15) {
        p_hw_usart->osr = osr_val;
    }
}

/**
 * \brief 设置地址寄存器的值
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] addr_val   : 8位的地址值
 *
 * \return 无
 *
 * \note 在地址匹配模式中，如果使能了地址自动匹配模式，则该地址寄存器保存着的地
 *       址值用于硬件地址匹配。
 */
am_static_inline
void amhw_usart_addr_set (amhw_usart_t *p_hw_usart, uint8_t addr_val)
{
    p_hw_usart->addr = addr_val;
}

/**
 * \brief 串口波特率设置
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] u_clk      : 串口的输入时钟频率
 * \param[in] baudrate   : 期望设置的串口波特率
 *
 * \return 大于0表示实际的波特率，小于0表明设置失败。
 */
int amhw_usart_baudrate_set (amhw_usart_t *p_hw_usart,
                             uint32_t      u_clk,
                             uint32_t      baudrate);

/**
 * \brief USART数据发送(查询模式)
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] p_txbuf    : 发送数据缓冲区
 * \param[in] nbytes     : 发送数据个数
 *
 * \return 成功发送的数据个数
 */
int amhw_usart_poll_send(amhw_usart_t  *p_hw_usart,
                         const uint8_t *p_txbuf,
                         uint32_t       nbytes);

/**
 * \brief USART数据接收(查询模式)
 *
 * \param[in] p_hw_usart : 指向串口寄存器块的指针
 * \param[in] p_rxbuf    : 接收数据缓冲区
 * \param[in] nbytes     : 接收数据个数
 *
 * \return 成功接收的数据个数
 */
int amhw_usart_poll_receive(amhw_usart_t *p_hw_usart,
                            uint8_t      *p_rxbuf,
                            uint32_t      nbytes);

/**
 * @} amhw_if_usart
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_USART_H */

/* end of file */

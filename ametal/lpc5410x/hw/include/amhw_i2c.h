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
 * \brief I2C 硬件操作接口
 * 
 * 1. 具有独立主机、从机和监控等功能；
 * 2. 总线速度:
 *    - 标准模式下, 可高达100k bits/s；
 *    - 快速模式下, 可高达400k bits/s；
 *    - 快速模式plus下, 可高达1M bits/s；
 *    - 高速模式下, 在从机模式可高达3.4M bits/s；
 * 3. 支持多个主机和具有从机的多主机；
 * 4. 在硬件上支持多个从机地址；
 * 5. 通过软件配置，可支持10bits地址的设备；
 * 6. 支持系统管理总线；
 * 7. 为了接收数据DMA可独立请求I2C的主机、从机和监控；
 * 8. 在无片上时钟请求时接收数据和从机地址匹配，可以将设备从掉电模式中唤醒； 
 * 9. 在主机、从机模式下支持快速模式plus (FM+, 总线速率可高达 1 MHz) 
 *    高速模式仅设备为从机时支持（总线速率可高达 3.4 MHz）。
 *   
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_I2C_H
#define __AMHW_I2C_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
/**
 * @addtogroup amhw_if_i2c
 * @copydoc amhw_i2c.h
 * @{
 */
    
/**
 * \brief I2C 寄存器块结构体
 */
typedef struct amhw_i2c {
    __IO uint32_t  cfg;           /**< \brief I2C 配置寄存器              */
    __IO uint32_t  stat;          /**< \brief I2C 状态寄存器              */
    __IO uint32_t  intenset;      /**< \brief I2C 中断位使能或读取寄存器  */
    __O  uint32_t  intenclr;      /**< \brief I2C 中断位禁能寄存器        */
    __IO uint32_t  timeout;       /**< \brief I2C 超时时间设定寄存器      */
    __IO uint32_t  clkdiv;        /**< \brief I2C 时钟分频数值设定寄存器  */
    __I  uint32_t  intstat;       /**< \brief I2C 中断状态                */
    __I  uint32_t  reserved;      /**< \brief 保留位                      */
    __IO uint32_t  mstctl;        /**< \brief I2C 主机控制寄存器          */
    __IO uint32_t  msttime;       /**< \brief I2C 主机SCL高电平和低电平时间设定寄存器 */
    __IO uint32_t  mstdat;        /**< \brief I2C 主机数据寄存器          */
    __I  uint32_t  reserved1[5];  /**< \brief 保留位                      */
    __IO uint32_t  slvctl;        /**< \brief I2C 从机控制寄存器          */
    __IO uint32_t  slvdat;        /**< \brief I2C 从机数据寄存器          */
    __IO uint32_t  slvadr0;       /**< \brief 从机地址0                   */
    __IO uint32_t  slvadr1;       /**< \brief 从机地址1                   */
    __IO uint32_t  slvadr2;       /**< \brief 从机地址2                   */
    __IO uint32_t  slvadr3;       /**< \brief 从机地址3                   */
    __IO uint32_t  slvqual0;      /**< \brief 从机地址限定寄存器          */
    __I  uint32_t  reserved2[9];  /**< \brief 保留位                      */
    __I  uint32_t  monrxdat;      /**< \brief 监控模式数据寄存器          */
} amhw_i2c_t;



/**
 * \name I2C 状态寄存器各个位详细定义
 * @{
 */

#define AMHW_I2C_STAT_MSTPEND          (0x1 << 0)  /**< \brief I2C 主机挂起状态 */
#define AMHW_I2C_MASTER_STATE_MASK     (0x7 << 1)  /**< \brief I2C 主机状态掩码 */
#define AMHW_I2C_STAT_MSTIDLE          (0x0 << 1)  /**< \brief I2C 主机空闲状态 */
#define AMHW_I2C_STAT_MSTRX            (0x1 << 1)  /**< \brief I2C 主机接收就绪状态  */
#define AMHW_I2C_STAT_MSTTX            (0x2 << 1)  /**< \brief I2C 主机发送就绪状态  */
#define AMHW_I2C_STAT_MSTNACKADDR      (0x3 << 1)  /**< \brief I2C 主机地址无响应    */
#define AMHW_I2C_STAT_MSTNACKTX        (0x4 << 1)  /**< \brief I2C 主机发送无响应    */
#define AMHW_I2C_STAT_MSTARBLOSS       (0x1 << 4)  /**< \brief I2C 主机仲裁失败      */
#define AMHW_I2C_STAT_MSTSSERR         (0x1 << 6)  /**< \brief I2C 主机启动/停止错误 */
                                       
#define AMHW_I2C_STAT_SLVPEND          (0x1 << 8)  /**< \brief I2C 从机挂起状态 */
#define AMHW_I2C_SLAVE_STATE_MASK      (0x3 << 9)  /**< \brief I2C 从机状态掩码 */
#define AMHW_I2C_STAT_SLVADDR          (0x0 << 9)  /**< \brief I2C 从机地址     */
#define AMHW_I2C_STAT_SLVRX            (0x1 << 9)  /**< \brief I2C 从机接收就绪状态 */
#define AMHW_I2C_STAT_SLVTX            (0x2 << 9)  /**< \brief I2C 从机发送就绪状态 */
#define AMHW_I2C_STAT_SLVNOTSTR        (0x1 << 11) /**< \brief I2C 从机不依靠I2C总线时钟 */
#define AMHW_I2C_STAT_SLVSEL           (0x1 << 14) /**< \brief I2C 从机选择     */
#define AMHW_I2C_STAT_SLVDESEL         (0x1 << 15) /**< \brief I2C 从机不选择   */
                                       
#define AMHW_I2C_STAT_EVTIMEOUT        (0x1 << 24) /**< \brief I2C 事件超时    */
#define AMHW_I2C_STAT_SCLTIMEOUT       (0x1 << 25) /**< \brief I2C 时钟超时    */

/** @} */


/**
 * \name I2C 中断使能寄存器各个位详细定义
 * @{
 */

#define AMHW_I2C_INTENSET_MSTPEND      (0x1 << 0)  /**< \brief I2C 主机挂起中断使能          */
#define AMHW_I2C_INTENSET_MSTARBLOSS   (0x1 << 4)  /**< \brief I2C 主机仲裁失败中断使能      */
#define AMHW_I2C_INTENSET_MSTSSERR     (0x1 << 6)  /**< \brief I2C 主机启动/停止错误中断使能 */
                                       
#define AMHW_I2C_INTENSET_SLVPEND      (0x1 << 8)  /**< \brief I2C 从机挂起中断使能       */
#define AMHW_I2C_INTENSET_SLVNOTSTR    (0x1 << 11) /**< \brief I2C 从机不依靠总线时钟使能 */
#define AMHW_I2C_INTENSET_SLVDESEL     (0x1 << 15) /**< \brief I2C 从机不选择中断使能     */
                                       
#define AMHW_I2C_INTENSET_MONRX        (0x1 << 8)  /**< \brief I2C 监控模式接收就绪中断使能 */
#define AMHW_I2C_INTENSET_MONOVEN      (0x1 << 11) /**< \brief I2C 监控超限中断使能         */
#define AMHW_I2C_INTENSET_MONIDLE      (0x1 << 15) /**< \brief I2C 监控模式空闲中断使能     */
                                       
#define AMHW_I2C_INTENSET_EVTIMEOUT    (0x1 << 24) /**< \brief I2C 事件超时中断使能 */
#define AMHW_I2C_INTENSET_SCLTIMEOUT   (0x1 << 25) /**< \brief I2C 时钟超时中断使能 */

/** @} */


/**
 * \name I2C 中断禁能寄存器各个位详细定义
 * @{
 */

#define AMHW_I2C_INTENCLR_MSTPEND      (0x1 << 0)  /**< \brief I2C 主机挂起中断禁能          */
#define AMHW_I2C_INTENCLR_MSTARBLOSS   (0x1 << 4)  /**< \brief I2C 主机仲裁失败中断禁能      */
#define AMHW_I2C_INTENCLR_MSTSSERR     (0x1 << 6)  /**< \brief I2C 主机启动/停止错误中断禁能 */
                                                   
#define AMHW_I2C_INTENCLR_SLVPEND      (0x1 << 8)  /**< \brief I2C 从机挂起中断禁能       */
#define AMHW_I2C_INTENCLR_SLVNOTSTR    (0x1 << 11) /**< \brief I2C 从机不依靠总线时钟禁能 */
#define AMHW_I2C_INTENCLR_SLVDESEL     (0x1 << 15) /**< \brief I2C 从机不选择中断禁能     */
                                                   
#define AMHW_I2C_INTENCLR_MONRX        (0x1 << 8)  /**< \brief I2C 监控模式接收就绪中断禁能 */
#define AMHW_I2C_INTENCLR_MONOVEN      (0x1 << 11) /**< \brief I2C 监控超限中断禁能         */
#define AMHW_I2C_INTENCLR_MONIDLE      (0x1 << 15) /**< \brief I2C 监控模式空闲中断禁能     */
                                                   
#define AMHW_I2C_INTENCLR_EVTIMEOUT    (0x1 << 24) /**< \brief I2C 事件超时中断禁能 */
#define AMHW_I2C_INTENCLR_SCLTIMEOUT   (0x1 << 25) /**< \brief I2C 时钟超时中断禁能 */

/** @} */


/**
 * \name I2C 主机控制寄存器位定义
 * @{
 */
 
#define AMHW_I2C_CTL_MSTCONTINUE       (1 << 0)  /**< \brief I2C 主机继续（响应）控制位 */ 
#define AMHW_I2C_CTL_MSTSTART          (1 << 1)  /**< \brief I2C 主机启动控制位 */
#define AMHW_I2C_CTL_MSTSTOP           (1 << 2)  /**< \brief I2C 主机停止控制位 */
#define AMHW_I2C_CTL_MSTDMA            (1 << 3)  /**< \brief I2C 主机DMA控制位  */

/** @} */


/**
 * \name I2C 从机控制寄存器位定义
 * @{
 */ 

#define AMHW_I2C_CTL_SLVCONTINUE       (1 << 0)  /**< \brief I2C 从机继续（响应）控制位 */
#define AMHW_I2C_CTL_SLVNACK           (1 << 1)  /**< \brief I2C 从机无响应控制位 */
#define AMHW_I2C_CTL_SLVDMA            (1 << 3)  /**< \brief I2C 从机DMA控制位    */

/** @} */

/**
 * \anchor I2C_mode
 * \brief I2C模式定义（参考I2C CFG寄存器） 
 */
typedef enum amhw_i2c_mode {
    AM_I2C_MASTER_MODE    = (1 << 0),  /**< \brief 主机模式使能  */
    AM_I2C_SLAVE_MODE     = (1 << 1),  /**< \brief 从机模式使能 */
    AM_I2C_MONITOR_MODE   = (1 << 2),  /**< \brief 监控模式使能 */
    AM_I2C_TIMEOUT_MODE   = (1 << 3),  /**< \brief 超时使能 */
    AM_I2C_MONCLKSTR_MODE = (1 << 4),  /**< \brief 监控模式时钟延伸使能 */
} amhw_i2c_mode_t;

/**
 * \brief I2C 写数据到主机数据寄存器
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] value    : 写入主机数据寄存器的数据
 *
 * \return  无
 */
am_static_inline 
void amhw_i2c_mstdat_write (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->mstdat = value;  
}

/**
 * \brief I2C 读取数据从主机数据寄存器
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  主机数据寄存器的值
 */
am_static_inline 
uint32_t amhw_i2c_mstdat_read (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->mstdat);  
}

/**
 * \brief 写数据到从机数据寄存器
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] value    : 写入从机数据寄存器的数据
 *
 * \return  无
 */
am_static_inline 
void amhw_i2c_slvdat_write (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->slvdat =  value;  
}

/**
 * \brief I2C 读取数据从从机数据寄存器
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  从机数据寄存器的值
 */
am_static_inline 
uint32_t amhw_i2c_slvdat_read (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->slvdat);  
}

/**
 * \brief 获取时钟分频寄存器
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  时钟分频寄存器的值
 */
am_static_inline 
uint32_t amhw_i2c_clkdiv_get (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->clkdiv);
}

/**
 * \brief 设定时钟分频函数
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] div      : 时钟分频参数
 *
 * \return  无
 */
am_static_inline 
void amhw_i2c_clkdiv_set (amhw_i2c_t *p_hw_i2c, uint32_t div)
{
    uint32_t clkdiv;
    
    if((div >= 1) && (div <= 65535)) {
        clkdiv = div - 1;
    } else {
        clkdiv = 0;
    }
    
    p_hw_i2c->clkdiv = clkdiv;
}


/**
 * \brief 设定MSTTIME（SCL高电平和SCL的电平时间）
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] value    : 设定时间参数
 *
 * \return  无
 */
am_static_inline 
void amhw_i2c_msttime_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->msttime = value;
}

/**
 * \brief 获取当前中断状态的函数
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  中断状态寄存器的值 
 */
am_static_inline 
uint32_t amhw_i2c_intstat_get (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->intstat);
}

/**
 * \brief 获取当前I2C状态的函数
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  状态寄存器的值
 */
am_static_inline 
uint32_t amhw_i2c_stat_get (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->stat);
}
/**
 * \brief 设定I2C状态的函数
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] value    : 设定的状态位AMHW_I2C_STAT_* 宏值或多个 
 *                       AMHW_I2C_STAT_*宏的 或（OR）值(#AMHW_I2C_STAT_MSTPEND)
 *
 * \return  无
 */
am_static_inline 
void amhw_i2c_stat_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->stat = value;
}
/**
 * \brief I2C 中断使能
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] flags    : AMHW_I2C_INTENSET_* 宏值或多个 
 *                       AMHW_I2C_INTENSET_*宏的 或（OR）值(#AMHW_I2C_INTENSET_MSTPEND) 
 *
 * \return  None
 */
am_static_inline 
void amhw_i2c_int_enable (amhw_i2c_t *p_hw_i2c, uint32_t flags)
{
    p_hw_i2c->intenset = flags;
}

/**
 * \brief I2C 中断禁能
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] flags    : AMHW_I2C_INTENCLR_*宏值或多个 
 *                       AMHW_I2C_INTENCLR_*宏的 或（OR）值(#AMHW_I2C_INTENCLR_MSTPEND) 
 *
 * \return  None
 */
am_static_inline 
void amhw_i2c_int_disable (amhw_i2c_t *p_hw_i2c, uint32_t flags)
{
    p_hw_i2c->intenclr = flags;
}
/**
 * \brief I2C 主机启动控制函数
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  无
 */
am_static_inline 
void amhw_i2c_mst_start (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->mstctl = AMHW_I2C_CTL_MSTSTART;  
}

/**
 * \brief I2C 主机继续操作函数（响应ACK）
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_i2c_mst_continue (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->mstctl = AMHW_I2C_CTL_MSTCONTINUE;  
}
/**
 * \brief  I2C 主机停止控制函数
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  无
 */
am_static_inline 
void amhw_i2c_mst_stop (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->mstctl = AMHW_I2C_CTL_MSTSTOP;
}

/**
 * \brief I2C 从机继续操作（响应ACK）
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \return  无
 */
am_static_inline 
void amhw_i2c_slv_continue (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->slvctl = AMHW_I2C_CTL_SLVCONTINUE;
}

/**
 * \brief  使能设定的I2C模式
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] mode     : 需要使能的I2C 模式,参考 \ref I2C_mode "I2C 模式定义"
 *
 * \return    无
 */
am_static_inline 
void amhw_i2c_mode_enable (amhw_i2c_t *p_hw_i2c, uint32_t mode)
{
    p_hw_i2c->cfg |= mode;
}


/**
 * \brief  禁能设定的I2C模式
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] mode     : 需要禁能的I2C 模式,参考 \ref I2C_mode "I2C 模式定义"
 *
 * \return    无
 */
am_static_inline 
void amhw_i2c_mode_disable (amhw_i2c_t *p_hw_i2c, uint32_t mode)
{
    p_hw_i2c->cfg &= ~mode;
}


/**
 * \brief 设定从机地址0
 *
 * \param[in] p_hw_i2c : 指向I2C寄存器块的指针
 * \param[in] sla_addr : 从机地址
 *
 * \return    无
 */
am_static_inline 
void amhw_i2c_slvadr0_set (amhw_i2c_t *p_hw_i2c, uint32_t sla_addr)
{
    p_hw_i2c->slvadr0 = sla_addr;
}


/** 
 * @} amhw_if_i2c 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_I2C_H */


/* end of file */

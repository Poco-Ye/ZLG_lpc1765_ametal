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
 * \brief 系统控制接口
 *
 * 1. 系统和总线配置；
 * 2. 复位控制；
 * 3. 唤醒控制；
 * 4. BOD（掉电检测）配置；
 * 5. 高精度时钟频率测量单元；
 * 6. 设备 ID 寄存器。
 *
 * \internal
 * \par History
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_SYSCON_H
#define __AMHW_SYSCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc5410x.h"

/**
 * \addtogroup amhw_if_syscon
 * \copydoc amhw_syscon.h
 * @{
 */

/**
  * \brief 系统控制寄存器块结构体
  */
typedef struct amhw_syscon {
    __IO uint32_t  sysmemremap;     /**< \brief 系统内存重定向寄存器          */
    __IO uint32_t  ahbmatprio;      /**< \brief AHB总线矩阵优先级设置寄存器   */
    __I  uint32_t  reserved[3];     /**< \brief 保留，不能使用                */
    __IO uint32_t  systckcal;       /**< \brief Systick校准寄存器             */
    __I  uint32_t  reserved1;       /**< \brief 保留，不能使用                */
    __IO uint32_t  nmisrc;          /**< \brief 不可屏蔽中断(NMI)中断源选择   */
    __IO uint32_t  asyncapbctrl;    /**< \brief 异步APB控制寄存器             */
    __I  uint32_t  reserved2[7];    /**< \brief 保留，不能使用                */
    __IO uint32_t  sysrststat;      /**< \brief 系统复位状态寄存器            */
    __IO uint32_t  presetctrl0;     /**< \brief 外设复位控制寄存器0           */
    __IO uint32_t  presetctrl1;     /**< \brief 外设复位控制寄存器1           */
    __O  uint32_t  presetctrlset0;  /**< \brief 置位外设复位控制寄存器0相应位 */
    __O  uint32_t  presetctrlset1;  /**< \brief 置位外设复位控制寄存器1相应位 */
    __O  uint32_t  presetctrlclr0;  /**< \brief 清零外设复位控制寄存器0相应位 */
    __O  uint32_t  presetctrlclr1;  /**< \brief 清零外设复位控制寄存器1相应位 */
    __I  uint32_t  pioporcap[2];    /**< \brief 上电复位捕获的PIO状态         */
    __I  uint32_t  reserved3;       /**< \brief 保留，不能使用                */
    __I  uint32_t  piorescap[2];    /**< \brief 复位捕获的PIO状态             */
    __I  uint32_t  reserved4[4];    /**< \brief 保留，不能使用                */
    __IO uint32_t  mainclksela;     /**< \brief Main A 时钟源选择寄存器       */
    __IO uint32_t  mainclkselb;     /**< \brief Main B 时钟源选择寄存器       */
    __I  uint32_t  reserved5;       /**< \brief 保留，不能使用                */
    __IO uint32_t  adcclksel;       /**< \brief ADC 时钟源选择寄存器          */
    __I  uint32_t  reserved6;       /**< \brief 保留，不能使用                */
    __IO uint32_t  clkoutsela;      /**< \brief CLKOUT A时钟源选择            */
    __IO uint32_t  clkoutselb;      /**< \brief CLKOUT B时钟源选择            */
    __I  uint32_t  reserved7;       /**< \brief 保留，不能使用                */
    __IO uint32_t  syspllclksel;    /**< \brief PLL 时钟源选择寄存器          */
    __I  uint32_t  reserved8[7];    /**< \brief 保留，不能使用                */
    __IO uint32_t  ahbclkctrl0;     /**< \brief AHB时钟控制寄存器0            */
    __IO uint32_t  ahbclkctrl1;     /**< \brief AHB时钟控制寄存器1            */
    __O  uint32_t  ahbclkctrlset0;  /**< \brief 置位AHB时钟控制寄存器0相应位  */
    __O  uint32_t  ahbclkctrlset1;  /**< \brief 置位AHB时钟控制寄存器1相应位  */
    __O  uint32_t  ahbclkctrlclr0;  /**< \brief 清零AHB时钟控制寄存器0相应位  */
    __O  uint32_t  ahbclkctrlclr1;  /**< \brief 清零AHB时钟控制寄存器1相应位  */
    __I  uint32_t  reserved9[2];    /**< \brief 保留，不能使用                */
    __IO uint32_t  systickclkdiv;   /**< \brief SYSTICK 时钟分频寄存器        */
    __I  uint32_t  reserved10[7];   /**< \brief 保留，不能使用                */
    __IO uint32_t  ahbclkdiv;       /**< \brief 系统时钟分频寄存器            */
    __I  uint32_t  reserved11;      /**< \brief 保留，不能使用                */
    __IO uint32_t  adcclkdiv;       /**< \brief ADC时钟分频寄存器             */
    __IO uint32_t  clkoutdiv;       /**< \brief CLKOUT时钟分频寄存器          */
    __I  uint32_t  reserved12[4];   /**< \brief 保留，不能使用                */
    __IO uint32_t  freqmectrl;      /**< \brief 频率测量单元控制寄存器        */
    __IO uint32_t  flashcfg;        /**< \brief Flash等待状态配置寄存器       */
    __I  uint32_t  reserved13[8];   /**< \brief 保留，不能使用                */
    __IO uint32_t  fifoctrl;        /**< \brief 串行设备的FIFO使能寄存器      */
    __I  uint32_t  reserved14[14];  /**< \brief 保留，不能使用                */
    __IO uint32_t  ircctrl;         /**< \brief IRC振荡器控制寄存器           */
    __I  uint32_t  reserved15[2];   /**< \brief 保留，不能使用                */
    __IO uint32_t  rtcoscctrl;      /**< \brief RTC晶体振荡器输出控制寄存器   */
    __I  uint32_t  reserved16[7];   /**< \brief 保留，不能使用                */
    __IO uint32_t  syspllctrl;      /**< \brief PLL控制寄存器                 */
    __I  uint32_t  syspllstat;      /**< \brief PLL状态寄存器                 */
    __IO uint32_t  syspllndec;      /**< \brief PLL N 译码器                  */
    __IO uint32_t  syspllpdec;      /**< \brief PLL P 译码器                  */
    __IO uint32_t  syspllssctrl0;   /**< \brief PLL频展控制寄存器0            */
    __IO uint32_t  syspllssctrl1;   /**< \brief PLL频展控制寄存器1            */
    __I  uint32_t  reserved17[18];  /**< \brief 保留，不能使用                */
    __IO uint32_t  pdruncfg;        /**< \brief 电源控制寄存器                */
    __O  uint32_t  pdruncfgset;     /**< \brief 置位电源控制寄存器的相应位    */
    __O  uint32_t  pdruncfgclr;     /**< \brief 清零电源控制寄存器的相应位    */
    __I  uint32_t  reserved18[9];   /**< \brief 保留，不能使用                */
    __IO uint32_t  starterp0;       /**< \brief 使能唤醒寄存器0               */
    __IO uint32_t  starterp1;       /**< \brief 使能唤醒寄存器1               */
    __O  uint32_t  starterpset0;    /**< \brief 置位唤醒寄存器0的相应位       */
    __O  uint32_t  starterpset1;    /**< \brief 置位唤醒寄存器1的相应位       */
    __O  uint32_t  starterpclr0;    /**< \brief 清零唤醒寄存器0的相应位       */
    __O  uint32_t  starterpclr1;    /**< \brief 清零唤醒寄存器1的相应位       */
    __I  uint32_t  reserved19[42];  /**< \brief 保留，不能使用                */
    __IO uint32_t  cpuctrl;         /**< \brief CPU控制寄存器                 */
    __IO uint32_t  cpboot;          /**< \brief 协处理器启动地址              */
    __IO uint32_t  cpstack;         /**< \brief 协处理器堆栈地址              */
    __I  uint32_t  reserved20[58];  /**< \brief 保留，不能使用                */
    __I  uint32_t  jtagidcode;      /**< \brief JTAG ID 寄存器                */
    __I  uint32_t  device_id0;      /**< \brief Part ID 寄存器                */
    __I  uint32_t  device_id1;      /**< \brief Boot ROM 版本号寄存器         */
} amhw_syscon_t;

/**
  * \brief 异步系统配置寄存器块结构体
  */
typedef struct amhw_asyncsyscon {
    __IO uint32_t  asyncpresetctrl;    /**< \brief 异步外设复位控制寄存器     */
    __O  uint32_t  asyncpresetctrlset; /**< \brief 置位异步外设复位控制寄存器 */
    __O  uint32_t  asyncpresetctrlclr; /**< \brief 清零异步外设复位控制寄存器 */
    __I  uint32_t  reserved;           /**< \brief 保留，不能使用             */
    __IO uint32_t  asyncapbclkctrl;    /**< \brief 异步外设时钟控制寄存器     */
    __O  uint32_t  asyncapbclkctrlset; /**< \brief 置位异步外设时钟控制寄存器 */
    __O  uint32_t  asyncapbclkctrlclr; /**< \brief 清零异步外设时钟控制寄存器 */
    __I  uint32_t  reserved1;          /**< \brief 保留，不能使用             */
    __IO uint32_t  asyncapbclksela;    /**< \brief 异步APB时钟源选择寄存器A   */
    __IO uint32_t  asyncapbclkselb;    /**< \brief 异步APB时钟源选择寄存器B   */
    __IO uint32_t  asyncclkdiv;        /**< \brief 异步APB时钟分频寄存器      */
    __I  uint32_t  reserved2;          /**< \brief 保留，不能使用             */
    __IO uint32_t  frgctrl;            /**< \brief 串口小数分频器控制寄存器   */
    __I  uint32_t  reserved3[4];       /**< \brief 保留，不能使用             */
} amhw_asyncsyscon_t;

/**
 * \brief 系统内存重映射，用于重映射中断向量表
 */
typedef enum amhw_syscon_bootmode_remap {

    /** \brief 中断向量表重映射至启动ROM中  */
    AM_SYSYCON_REMAP_BOOTROM_MODE = 0,

    /** \brief 中断向量表重映射至SRAM中     */
    AM_SYSYCON_REMAP_SRAM_MODE,

    /** \brief 中断向量表重映射至FLASH中    */
    AM_SYSYCON_REMAP_FLASH_MODE,
} amhw_syscon_bootmode_remap_t;

/**
 * \brief 总线类型，用于设置AHB总线的优先级
 */
typedef enum am_ahb_bus_type {
    AM_AHB_BUS_ICODE = 0,    /**< \brief I-Code 总线      */
    AM_AHB_BUS_DCODE = 2,    /**< \brief D-Code 总线      */
    AM_AHB_BUS_SYS   = 4,    /**< \brief 系统 总线        */
    AM_AHB_BUS_DMA   = 8,    /**< \brief DMA控制器 总线   */
    AM_AHB_BUS_FIFO  = 14,   /**< \brief FIFO 总线        */
    AM_AHB_BUS_M0    = 16    /**< \brief Cortex-M0+ 总线  */
} am_ahb_bus_type_t;

/**
 * \brief 重映射中断向量表
 * \param[in] remap : 选择重映射至何种内存中
 * \return 无
 */
am_static_inline
void amhw_syscon_remap_set (amhw_syscon_bootmode_remap_t remap)
{
    AMHW_SYSCON->sysmemremap = (uint32_t)remap;
}

/**
 * \brief 获取中断向量表的重映射值
 * \return 中断向量表的重映射值
 */
am_static_inline
amhw_syscon_bootmode_remap_t amhw_syscon_remap_get (void)
{
    return (amhw_syscon_bootmode_remap_t)AMHW_SYSCON->sysmemremap;
}

/**
 * \brief 设置总线在AHB总线矩阵中的优先级
 *
 * \param[in] bus_type : 待设置优先级的总线类型
 * \param[in] priority : 优先级值，有效范围是0 ~ 3(最高优先级)
 *
 * \return 无
 *
 * \note 当优先级值相同时，具有较低 master num 值的总线具有更高的优先级。一种典
 *       型的设置是将 Cortex-M4 D-code 总线设置为最高优先级，紧接着是I-Code总线。
 *       其它所有的总线共享一个低优先级。
 *             bus_type     |    master num
 *       ------------------ | ----------------
 *        AM_AHB_BUS_ICODE  |        0
 *        AM_AHB_BUS_DCODE  |        1
 *        AM_AHB_BUS_SYS    |        2
 *        AM_AHB_BUS_DMA    |        5
 *        AM_AHB_BUS_FIFO   |        9
 *        AM_AHB_BUS_M0     |        10
 *
 */
void amhw_syscon_ahb_priority_set(am_ahb_bus_type_t bus_type, uint8_t priority);

/**
 * \brief 设置Systick的校准值
 * \param[in] systickcal_val : Systick的校准值
 * \return 无
 */
am_static_inline
void amhw_syscon_systickcal_set (uint32_t systickcal_val)
{
    AMHW_SYSCON->systckcal = systickcal_val;
}

/**
 * \name 用于使能相应核的不可屏蔽中断（NMI）
 * @{
 */

/** \brief Enable the Non-Maskable Interrupt M0 (NMI) source */
#define AMHW_SYSCON_NMISRC_M0_ENABLE   ((uint32_t) 1 << 30)

/** \brief Enable the Non-Maskable Interrupt M4 (NMI) source */
#define AMHW_SYSCON_NMISRC_M4_ENABLE   ((uint32_t) 1 << 31)

/** @} */

/**
 * \brief 设置不可屏蔽中断源
 * \param[in] intsrc : 用于NMI的中断号（IRQ number）
 * \return 无
 * \note NMI中断源此时还是处于禁止状态的，可以使用amhw_syscon_nmisrc_enable()函数
 *       使能用于NMI中断源的中断。
 */
void amhw_syscon_nmisrc_set(uint32_t intsrc);

/**
 * \brief 使能NMI中断源的中断
 * \return 无
 */
void amhw_syscon_nmisrc_enable(void);

/**
 * \brief 禁能NMI中断源的中断
 * \return 无
 */
void amhw_syscon_nmisrc_disable(void);

/**
 * \brief 使能异步APB和异步APB子系统
 * \return 无
 * \note  访问任何异步外设之前，必须确保该函数已被调用
 */
am_static_inline
void amhw_syscon_async_enable (void)
{
    AMHW_SYSCON->asyncapbctrl = 0x01;
}

/**
 * \brief 禁能异步APB和异步APB子系统
 * \return 无
 */
am_static_inline
void amhw_syscon_async_disable (void)
{
    AMHW_SYSCON->asyncapbctrl = 0x00;
}

/**
 * \brief 设置串口小数分频器的值
 *
 * \param[in] fmul : 小数分频器的倍乘数
 * \param[in] fdiv : 小数分频器的除数 (必须是0xFF)
 *
 * \return 无
 */
am_static_inline
void amhw_syscon_usart_frgctrl_set (uint8_t fmul, uint8_t fdiv)
{
    AMHW_ASYNCSYSCON->frgctrl = ((uint32_t) fmul << 8) | fdiv;
}

/**
 * \name 系统复位状态值
 * @{
 */

#define AMHW_SYSCON_RSTSTAT_POR    (1 << 0)   /**< \brief 上电复位            */
#define AMHW_SYSCON_RSTSTAT_EXTRST (1 << 1)   /**< \brief 外部管脚复位        */
#define AMHW_SYSCON_RSTSTAT_WDT    (1 << 2)   /**< \brief 看门狗复位          */
#define AMHW_SYSCON_RSTSTAT_BOD    (1 << 3)   /**< \brief 掉电检测复位        */
#define AMHW_SYSCON_RSTSTAT_SYSRST (1 << 4)   /**< \brief 软件复位            */

/** @} */

/**
 * \brief 获取系统复位状态
 * \return AMHW_SYSCON_RSTSTAT_* 宏值或多个AMHW_SYSCON_RSTSTAT_*宏的或（OR）值
 *         (#AMHW_SYSCON_RSTSTAT_POR)
 */
am_static_inline
uint32_t amhw_syscon_rst_stat_get (void)
{
    return AMHW_SYSCON->sysrststat;
}

/**
 * \brief 清除系统复位状态
 * \param[in] reset : AMHW_SYSCON_RSTSTAT_* 宏值或多个AMHW_SYSCON_RSTSTAT_*宏的
                      或（OR）值(#AMHW_SYSCON_RSTSTAT_POR)
 * \return 无
 */
am_static_inline
void amhw_syscon_rst_stat_clr (uint32_t reset)
{
    AMHW_SYSCON->sysrststat = reset;
}

/**
 * \brief 用于外设复位的枚举值
 */
typedef enum amhw_syscon_periph_reset {
    AMHW_RESET_FLASH = 7,          /**< \brief FLASH控制器                 */
    AMHW_RESET_FMC,                /**< \brief FLASH加速器                 */
    AMHW_RESET_INMUX = 11,         /**< \brief 输入复用(INPUT MUX)         */
    AMHW_RESET_IOCON = 13,         /**< \brief IO控制器(IOCON)             */
    AMHW_RESET_GPIO0,              /**< \brief GPIO 端口 0(GPIO0)          */
    AMHW_RESET_GPIO1,              /**< \brief GPIO 端口 1(GPIO1)          */
    AMHW_RESET_PINT = 18,          /**< \brief 管脚中断                    */
    AMHW_RESET_GINT,               /**< \brief 引脚组中断 (GINT)           */
    AMHW_RESET_DMA,                /**< \brief DMA                         */
    AMHW_RESET_CRC,                /**< \brief 循环冗余校验(CRC)           */
    AMHW_RESET_WWDT,               /**< \brief 看门狗                      */
    AMHW_RESET_RTC,                /**< \brief 实时时钟                    */
    AMHW_RESET_MAILBOX = 26,       /**< \brief 双核通信邮箱                */
    AMHW_RESET_ADC0,               /**< \brief ADC0                        */

    AMHW_RESET_MRT = 32 + 0,       /**< \brief 多频率定时器(MRT)           */
    AMHW_RESET_RIT,                /**< \brief 可重复中断定时器（RIT）     */
    AMHW_RESET_SCT0,               /**< \brief 状态可编程定时器0           */
    AMHW_RESET_FIFO = 32 + 9,      /**< \brief 系统 FIFO                   */
    AMHW_RESET_UTICK,              /**< \brief Micro-tick Timer            */
    AMHW_RESET_TIMER2 = 32 + 22,   /**< \brief 定时器2                     */
    AMHW_RESET_TIMER3 = 32 + 26,   /**< \brief 定时器3                     */
    AMHW_RESET_TIMER4,             /**< \brief 定时器4                     */
 
    AMHW_RESET_USART0 = 128 + 1,   /**< \brief 串口0                       */
    AMHW_RESET_USART1,             /**< \brief 串口1                       */
    AMHW_RESET_USART2,             /**< \brief 串口2                       */
    AMHW_RESET_USART3,             /**< \brief 串口3                       */
    AMHW_RESET_I2C0,               /**< \brief I2C0                        */
    AMHW_RESET_I2C1,               /**< \brief I2C1                        */
    AMHW_RESET_I2C2,               /**< \brief I2C2                        */
    AMHW_RESET_SPI0 = 128 + 9,     /**< \brief SPI0                        */
    AMHW_RESET_SPI1,               /**< \brief SPI1                        */
    AMHW_RESET_TIMER0 = 128 + 13,  /**< \brief 定时器0                     */
    AMHW_RESET_TIMER1,             /**< \brief 定时器1                     */
    AMHW_RESET_FRG0                /**< \brief 串口小数分频控制器          */
} amhw_syscon_periph_reset_t;

/**
 * \brief 复位一个外设
 * \param[in] periph : 需要复位的外设
 * \return 无
 */
void amhw_syscon_periph_reset(amhw_syscon_periph_reset_t periph);

/**
 * \brief 读取上电复位捕获到的IO状态
 * \param[in] port : IO端口号，0-GPIO0,1-GPIO1
 * \return 上电复位捕获到的IO状态
 */
am_static_inline
uint32_t amhw_syscon_porcap_stat_get (uint8_t port)
{
    return AMHW_SYSCON->pioporcap[port];
}

/**
 * \brief 读取复位捕获到的IO状态
 * \param[in] port : IO端口号，0-GPIO0,1-GPIO1
 * \return 复位捕获到的IO状态s
 * \note 当复位不是上电复位时使用
 */
am_static_inline
uint32_t amhw_syscon_rstcap_stat_get (uint8_t port)
{
    return AMHW_SYSCON->piorescap[port];
}

/**
 * \brief 开始频率测量
 * \return 无
 * \note 该函数常常用于 amhw_inmux_freqmsr_refclk_set() 和 amhw_inmux_freqmsr_targclk_set()
 *       函数设置好参考时钟和目标时钟之后.
 */
am_static_inline
void amhw_syscon_freqmeas_start (void)
{
    AMHW_SYSCON->freqmectrl = 0;
    AMHW_SYSCON->freqmectrl = (1UL << 31);
}

/**
 * \brief 检测频率测量是否完成
 * \retval  TRUE  : 本次频率测量完成
 * \retval  FALSE : 本次频率测量未完成
 */
am_static_inline
bool_t amhw_syscon_freqmsr_complete_chk (void)
{
    return (bool_t) ((AMHW_SYSCON->freqmectrl & (1UL << 31)) == 0);
}

/**
 * \brief 得到频率测量单元捕获值
 * \return  频率测量单元捕获值(并不是频率，需要转换)
 */
am_static_inline
uint32_t amhw_syscon_freqmeas_capval_get (void)
{
    return AMHW_SYSCON->freqmectrl & 0x3FFF;
}

/**
 * \brief 得到频率测量单元目标时钟的频率
 * \param[in] ref_clkrate : 频率测量单元参考时钟的频率
 * \return 频率测量单元目标时钟的频率
 * \note 调用该函数前确保频率测量已经完成
 */
uint32_t amhw_syscon_freqmeas_targfreq_get(uint32_t ref_clkrate);

/**
 * \brief FLASH访问时间定义
 */
typedef enum amhw_syscon_flashtim {
    AMHW_SYSCON_FLASH_1CYCLE = 0, /**< \brief Flash 访问使用1个CPU时钟   */
    AMHW_FLASHTIM_20MHZ_CPU  = 0, /**< \brief Flash 访问使用1个CPU时钟   */
    AMHW_SYSCON_FLASH_2CYCLE,     /**< \brief Flash 访问使用2个CPU时钟   */
    AMHW_SYSCON_FLASH_3CYCLE,     /**< \brief Flash 访问使用3个CPU时钟   */
    AMHW_SYSCON_FLASH_4CYCLE,     /**< \brief Flash 访问使用4个CPU时钟   */
    AMHW_SYSCON_FLASH_5CYCLE,     /**< \brief Flash 访问使用5个CPU时钟   */
    AMHW_SYSCON_FLASH_6CYCLE,     /**< \brief Flash 访问使用6个CPU时钟   */
    AMHW_SYSCON_FLASH_7CYCLE,     /**< \brief Flash 访问使用7个CPU时钟   */
    AMHW_SYSCON_FLASH_8CYCLE      /**< \brief Flash 访问使用8个CPU时钟   */
} amhw_syscon_flashtim_t;

/**
 * \brief 设置FLASH访问时间
 * \param[in] clks : FLASH访问时间
 * \return 无
 */
am_static_inline
void amhw_syscon_flashaccess_set (amhw_syscon_flashtim_t clks)
{
    uint32_t tmp;

    tmp = AMHW_SYSCON->flashcfg & ~(0xF << 12);

    AMHW_SYSCON->flashcfg = tmp | ((uint32_t) clks << 12);
}

/**
 * \brief 根据系统时钟频率设置FLASH访问时间
 * \param[in] freq : 系统时钟的频率
 * \return 无
 */
void amhw_syscon_setupflashclocks(uint32_t freq);

/**
 * \name 系统外设 FIFO 使能位定义
 * @{
 */

#define AMHW_SYSCON_FIFO_U0TXFIFOEN      (1 << 0)  /**< \brief 串口0发送 FIFO */
#define AMHW_SYSCON_FIFO_U1TXFIFOEN      (1 << 1)  /**< \brief 串口1发送 FIFO */
#define AMHW_SYSCON_FIFO_U2TXFIFOEN      (1 << 2)  /**< \brief 串口2发送 FIFO */
#define AMHW_SYSCON_FIFO_U3TXFIFOEN      (1 << 3)  /**< \brief 串口3发送 FIFO */
#define AMHW_SYSCON_FIFO_SPI0TXFIFOEN    (1 << 4)  /**< \brief SPI0 发送 FIFO */
#define AMHW_SYSCON_FIFO_SPI1TXFIFOEN    (1 << 5)  /**< \brief SPI1 发送 FIFO */
#define AMHW_SYSCON_FIFO_U0RXFIFOEN      (1 << 8)  /**< \brief 串口0接收 FIFO */
#define AMHW_SYSCON_FIFO_U1RXFIFOEN      (1 << 9)  /**< \brief 串口1接收 FIFO */
#define AMHW_SYSCON_FIFO_U2RXFIFOEN      (1 << 10) /**< \brief 串口2接收 FIFO */
#define AMHW_SYSCON_FIFO_U3RXFIFOEN      (1 << 11) /**< \brief 串口3接收 FIFO */
#define AMHW_SYSCON_FIFO_SPI0RXFIFOEN    (1 << 12) /**< \brief SPI0 接收 FIFO */
#define AMHW_SYSCON_FIFO_SPI1RXFIFOEN    (1 << 13) /**< \brief SPI1 接收 FIFO */

/** @} */

/**
 * \brief 使能指定外设的系统FIFO
 * \param[in] en_mask : AMHW_SYSCON_FIFO_* 宏值或多个 AMHW_SYSCON_FIFO_*宏的 或
                       （OR）值  (#AMHW_SYSCON_FIFO_U0TXFIFOEN)
 * \return 无
 */
am_static_inline
void amhw_syscon_fifo_enable (uint32_t en_mask)
{
    AMHW_SYSCON->fifoctrl |= en_mask;
}

/**
 * \brief 禁能指定外设的系统FIFO
 * \param[in] dis_mask : AMHW_SYSCON_FIFO_* 宏值或多个 AMHW_SYSCON_FIFO_*宏的 或
                       （OR）值  (#AMHW_SYSCON_FIFO_U0TXFIFOEN)
 * \return 无
 */
am_static_inline
void amhw_syscon_fifo_disable (uint32_t dis_mask)
{
    AMHW_SYSCON->fifoctrl &= ~dis_mask;
}

/**
 * \name 电源控制位定义(0 = powered, 1 = powered down)
 * @{
 */

#define AMHW_SYSCON_PD_IRC_OSC    (1 << 3)     /**< \brief IRC 振荡器输出     */
#define AMHW_SYSCON_PD_IRC        (1 << 4)     /**< \brief IRC 振荡器         */
#define AMHW_SYSCON_PD_FLASH      (1 << 5)     /**< \brief Flash              */
#define AMHW_SYSCON_PD_BOD_RST    (1 << 7)     /**< \brief 掉电检测复位单元   */
#define AMHW_SYSCON_PD_BOD_INTR   (1 << 8)     /**< \brief 掉电检测中断单元   */
#define AMHW_SYSCON_PD_ADC0       (1 << 10)    /**< \brief ADC0               */
#define AMHW_SYSCON_PD_SRAM0A     (1 << 13)    /**< \brief SRAM0起始的8KB内存 */
#define AMHW_SYSCON_PD_SRAM0B     (1 << 14)    /**< \brief SRAM0起始8KB之后的内存 */
#define AMHW_SYSCON_PD_SRAM1      (1 << 15)    /**< \brief SRAM1              */
#define AMHW_SYSCON_PD_SRAM2      (1 << 16)    /**< \brief SRAM2              */
#define AMHW_SYSCON_PD_ROM        (1 << 17)    /**< \brief ROM                */
#define AMHW_SYSCON_PD_VDDA_ENA   (1 << 19)    /**< \brief ADC的VDDA供电      */
#define AMHW_SYSCON_PD_WDT_OSC    (1 << 20)    /**< \brief 看门狗振荡器电源   */
#define AMHW_SYSCON_PD_SYS_PLL    (1 << 22)    /**< \brief PLL0               */
#define AMHW_SYSCON_PD_VREFP      (1 << 23)    /**< \brief ADC的VREFP供电     */
#define AMHW_SYSCON_PD_32K_OSC    (1 << 24)    /**< \brief 32 kHz RTC 振荡器  */

/** @} */

/**
 * \brief 得到当前的电源控制寄存器状态
 * \return  AMHW_SYSCON_PD_* 宏值或多个 AMHW_SYSCON_PD_*宏的 或（OR）值
            (#AMHW_SYSCON_PD_IRC)
 * \note  相应位为高电平表明该外设未供电，低电平表明供电
 */
am_static_inline
uint32_t amhw_syscon_powerstat_get (void)
{
    return AMHW_SYSCON->pdruncfg;
}

/**
 * \brief 关闭外设电源
 * \param[in] powerdownmask ：AMHW_SYSCON_PD_* 宏值或多个 AMHW_SYSCON_PD_*宏的
                              或（OR）值(#AMHW_SYSCON_PD_IRC)
 * \return 无
 */
am_static_inline
void amhw_syscon_powerdown (uint32_t powerdownmask)
{
    AMHW_SYSCON->pdruncfgset = powerdownmask;
}

/**
 * \brief 打开外设电源
 * \param[in] powerupmask ：AMHW_SYSCON_PD_* 宏值或多个 AMHW_SYSCON_PD_*宏的
                            或（OR）值(#AMHW_SYSCON_PD_IRC)
 * \return 无
 */
void amhw_syscon_powerup(uint32_t powerupmask);

/**
 * \brief 检测指定外设是否上电
 * \param[in] powermask : AMHW_SYSCON_PD_* 宏值
 * \retval    TRUE      : 外设已上电
 * \retval    FALSE     : 外设未上电
 */
am_static_inline
bool_t amhw_syscon_power_check (uint32_t powermask)
{
    return (bool_t)((AMHW_SYSCON->pdruncfg & powermask) == 0);
}

/**
 * \brief 枚举值，用于使能或者禁能外设中断的唤醒逻辑
 * 
 *  如果使能了某外设的唤醒逻辑，则该中断能够将芯片从深度睡眠模式和掉电模式唤醒
 */
typedef enum amhw_syscon_wakeup {
    AMHW_SYSCON_STARTER_WWDT = 0,        /**< \brief 看门狗(WWDT)             */
    AMHW_SYSCON_STARTER_BOD,             /**< \brief 掉电检测(BOD)            */
    AMHW_SYSCON_STARTER_DMA = 3,         /**< \brief DMA                      */
    AMHW_SYSCON_STARTER_GINT0,           /**< \brief GINT0                    */
    AMHW_SYSCON_STARTER_PINT0,           /**< \brief PINT0                    */
    AMHW_SYSCON_STARTER_PINT1,           /**< \brief PINT1                    */
    AMHW_SYSCON_STARTER_PINT2,           /**< \brief PINT2                    */
    AMHW_SYSCON_STARTER_PINT3,           /**< \brief PINT3                    */
    AMHW_SYSCON_STARTER_UTICK,           /**< \brief UTICK(Micro-tick timer)  */
    AMHW_SYSCON_STARTER_MRT,             /**< \brief MRT                      */
    AMHW_SYSCON_STARTER_TIMER0,          /**< \brief 定时器0                  */
    AMHW_SYSCON_STARTER_TIMER1,          /**< \brief 定时器1                  */
    AMHW_SYSCON_STARTER_TIMER2,          /**< \brief 定时器2                  */
    AMHW_SYSCON_STARTER_TIMER3,          /**< \brief 定时器3                  */
    AMHW_SYSCON_STARTER_TIMER4,          /**< \brief 定时器4                  */
    AMHW_SYSCON_STARTER_SCT0,            /**< \brief SCT0                     */
    AMHW_SYSCON_STARTER_USART0,          /**< \brief 串口0                    */
    AMHW_SYSCON_STARTER_USART1,          /**< \brief 串口1                    */
    AMHW_SYSCON_STARTER_USART2,          /**< \brief 串口2                    */
    AMHW_SYSCON_STARTER_USART3,          /**< \brief 串口3                    */
    AMHW_SYSCON_STARTER_I2C0,            /**< \brief I2C0                     */
    AMHW_SYSCON_STARTER_I2C1,            /**< \brief I2C1                     */
    AMHW_SYSCON_STARTER_I2C2,            /**< \brief I2C2                     */
    AMHW_SYSCON_STARTER_SPI0,            /**< \brief SPI0                     */
    AMHW_SYSCON_STARTER_SPI1,            /**< \brief SPI1                     */
    AMHW_SYSCON_STARTER_ADC0_SEQA,       /**< \brief ADC0_SEQA                */
    AMHW_SYSCON_STARTER_ADC0_SEQB,       /**< \brief ADC0_SEQB                */
    AMHW_SYSCON_STARTER_ADC0_THCMP,      /**< \brief ADC0_THCMP               */
    AMHW_SYSCON_STARTER_RTC,             /**< \brief 实时时钟(RTC)            */
    AMHW_SYSCON_STARTER_MAILBOX = 31,    /**< \brief 双核通信邮箱             */
    /* 仅仅在M4核内有效 */
    AMHW_SYSCON_STARTER_GINT1 = 32,      /**< \brief GINT1                    */
    AMHW_SYSCON_STARTER_PINT4,           /**< \brief PINT4                    */
    AMHW_SYSCON_STARTER_PINT5,           /**< \brief PINT5                    */
    AMHW_SYSCON_STARTER_PINT6,           /**< \brief PINT6                    */
    AMHW_SYSCON_STARTER_PINT7,           /**< \brief PINT7                    */
    AMHW_SYSCON_STARTER_RIT = 32 + 8,    /**< \brief RIT                      */
} amhw_syscon_wakeup_t;

/**
 * \brief 使能外设的唤醒逻辑
 * \param[in] periph_id :  AMHW_SYSCON_STARTER_* 宏值(#AMHW_SYSCON_STARTER_WWDT)
 * \return 无
 */
am_static_inline
void amhw_syscon_wakeup_enable (amhw_syscon_wakeup_t periph_id)
{
    uint32_t pid = (uint32_t)periph_id;

    if (pid < 32) {
        AMHW_SYSCON->starterpset0 = (1 << pid);
    } else {
        AMHW_SYSCON->starterpset1 = (1 << (pid - 32));
    }
}

/**
 * \brief 禁能外设的唤醒逻辑
 * \param[in] periph_id :  AMHW_SYSCON_STARTER_* 宏值(#AMHW_SYSCON_STARTER_WWDT)
 * \return 无
 */
am_static_inline
void amhw_syscon_wakeup_disable (amhw_syscon_wakeup_t periph_id)
{
    uint32_t pid = (uint32_t) periph_id;

    if (pid < 32) {
        AMHW_SYSCON->starterpclr0 = (1 << pid);
    }
    else {
        AMHW_SYSCON->starterpclr1 = (1 << (pid - 32));
    }
}

/**
 * \brief 获取设备ID 0
 * \return 设备ID 0
 */
am_static_inline
uint32_t amhw_syscon_deviceid0_get (void)
{
    return AMHW_SYSCON->device_id0;
}

/**
 * \brief 获取设备ID 1
 * \return 设备ID 1
 */
am_static_inline
uint32_t amhw_syscon_deviceid1_get (void)
{
    return AMHW_SYSCON->device_id1;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SYSCON_H */

/* end of file */

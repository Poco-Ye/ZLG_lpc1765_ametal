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
 * \brief 外设内存映射地址宏定义和外设定义
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-11-28  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LPC5410X_H
#define __AMHW_LPC5410X_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 中断号定义，为 core_cm4.h and core_cm0plus.h文件保留
 */
typedef enum {
 
#ifdef AM_CORTEX_M4
    /* ----------------------  Cortex-M4核异常号  ------------------- */
    
    /** \brief  1  复位向量                                           */
    Reset_IRQn               = -15,   
    
    /** \brief  2  不可屏蔽中断, 不能被停止或抢占                     */
    NonMaskableInt_IRQn      = -14,   
    
    /** \brief  3  硬件错误中断                                       */
    HardFault_IRQn           = -13,   
    
    /** \brief 4   内存管理中断                                       */
    MemoryManagement_IRQn    = -12,  
    
    /** \brief 5 总线错误,预取指,内存访问错误,其他内存、地址相关错误  */
    BusFault_IRQn            = -11,   
    
    /** \brief  6 用法错误, 如：未定义指令, 非法状态转换              */
    UsageFault_IRQn          = -10,   
    
    /** \brief 11  系统服务调用通过SVC指令                            */
    SVCall_IRQn              =  -5,   
    
    /** \brief 12  调试监控                                           */
    DebugMonitor_IRQn        =  -4,   
    
    /** \brief 14  系统的挂起请求                                     */
    PendSV_IRQn              =  -2,   
    
    /** \brief 15  系统滴答定时器                                     */
    SysTick_IRQn             =  -1,   
   
    /* ---------------  LPC5410x M4 核外设中断 ----------------- */
    WDT_IRQn                 =   0,   /**< \brief   0  WDT       */
    BOD_IRQn                 =   1,   /**< \brief   1  BOD       */
    DMA_IRQn                 =   3,   /**< \brief   3  DMA       */
    GINT0_IRQn               =   4,   /**< \brief   4  GINT0     */
    PIN_INT0_IRQn            =   5,   /**< \brief   5  PIN_INT0  */
    PIN_INT1_IRQn            =   6,   /**< \brief   6  PIN_INT1  */
    PIN_INT2_IRQn            =   7,   /**< \brief   7  PIN_INT2  */
    PIN_INT3_IRQn            =   8,   /**< \brief   8  PIN_INT3  */
    UTICK_IRQn               =   9,   /**< \brief   9  UTICK     */
    MRT_IRQn                 =  10,   /**< \brief  10  MRT       */
    CT32B0_IRQn              =  11,   /**< \brief  11  CT32B0    */
    CT32B1_IRQn              =  12,   /**< \brief  12  CT32B1    */
    CT32B2_IRQn              =  13,   /**< \brief  13  CT32B2    */
    CT32B3_IRQn              =  14,   /**< \brief  14  CT32B3    */
    CT32B4_IRQn              =  15,   /**< \brief  15  CT32B4    */
    SCT0_IRQn                =  16,   /**< \brief  16  SCT0      */
    UART0_IRQn               =  17,   /**< \brief  17  UART0     */
    UART1_IRQn               =  18,   /**< \brief  18  UART1     */
    UART2_IRQn               =  19,   /**< \brief  19  UART2     */
    UART3_IRQn               =  20,   /**< \brief  20  UART3     */
    I2C0_IRQn                =  21,   /**< \brief  21  I2C0      */
    I2C1_IRQn                =  22,   /**< \brief  22  I2C1      */
    I2C2_IRQn                =  23,   /**< \brief  23  I2C2      */
    SPI0_IRQn                =  24,   /**< \brief  24  SPI0      */
    SPI1_IRQn                =  25,   /**< \brief  25  SPI1      */
    ADC_SEQA_IRQn            =  26,   /**< \brief  26  ADC_SEQA  */
    ADC_SEQB_IRQn            =  27,   /**< \brief  27  ADC_SEQB  */
    ADC_THCMP_IRQn           =  28,   /**< \brief  28  ADC_THCMP */
    RTC_IRQn                 =  29,   /**< \brief  29  RTC       */
    MAILBOX_IRQn             =  31,   /**< \brief  31  MAILBOX   */
    GINT1_IRQn               =  32,   /**< \brief  32  GINT1     */
    PIN_INT4_IRQn            =  33,   /**< \brief  33  PIN_INT4  */
    PIN_INT5_IRQn            =  34,   /**< \brief  34  PIN_INT5  */
    PIN_INT6_IRQn            =  35,   /**< \brief  35  PIN_INT6  */
    PIN_INT7_IRQn            =  36,   /**< \brief  36  PIN_INT7  */
    RIT_IRQn                 =  40    /**< \brief  40  RIT       */
   
#else
   
    /* -------------------  Cortex-M0+ 核异常号  ------------------ */
    
    /** \brief  1  复位向量                                         */
    Reset_IRQn               = -15,  

    /** \brief  2  不可屏蔽中断, 不能被停止或抢占                   */
    NonMaskableInt_IRQn      = -14,    

    /** \brief 3  硬件错误中断                                     */
    HardFault_IRQn           = -13,            
   
   /** \brief  11   系统服务调用通过SVC指令                        */
    SVCall_IRQn              =  -5,            
                    
    /** \brief  14  系统的挂起请求                                 */                     
    PendSV_IRQn              =  -2,           
    
    /** \brief  15  系统滴答定时器                                 */
    SysTick_IRQn             =  -1,    
    
    /* -----------------  LPC54xxx M0+ 核外设中断 --------------- */
    WDT_IRQn                 =   0,   /**< \brief   0  WDT        */         
    BOD_IRQn                 =   1,   /**< \brief   1  BOD        */         
    DMA_IRQn                 =   3,   /**< \brief   3  DMA        */         
    GINT0_IRQn               =   4,   /**< \brief   4  GINT0      */         
    PIN_INT0_IRQn            =   5,   /**< \brief   5  PIN_INT0   */         
    PIN_INT1_IRQn            =   6,   /**< \brief   6  PIN_INT1   */         
    PIN_INT2_IRQn            =   7,   /**< \brief   7  PIN_INT2   */         
    PIN_INT3_IRQn            =   8,   /**< \brief   8  PIN_INT3   */         
    UTICK_IRQn               =   9,   /**< \brief   9  UTICK      */         
    MRT_IRQn                 =  10,   /**< \brief  10  MRT        */         
    CT32B0_IRQn              =  11,   /**< \brief  11  CT32B0     */         
    CT32B1_IRQn              =  12,   /**< \brief  12  CT32B1     */         
    CT32B2_IRQn              =  13,   /**< \brief  13  CT32B2     */         
    CT32B3_IRQn              =  14,   /**< \brief  14  CT32B3     */         
    CT32B4_IRQn              =  15,   /**< \brief  15  CT32B4     */         
    SCT0_IRQn                =  16,   /**< \brief  16  SCT0       */         
    UART0_IRQn               =  17,   /**< \brief  17  UART0      */         
    UART1_IRQn               =  18,   /**< \brief  18  UART1      */         
    UART2_IRQn               =  19,   /**< \brief  19  UART2      */         
    UART3_IRQn               =  20,   /**< \brief  20  UART3      */         
    I2C0_IRQn                =  21,   /**< \brief  21  I2C0       */         
    I2C1_IRQn                =  22,   /**< \brief  22  I2C1       */         
    I2C2_IRQn                =  23,   /**< \brief  23  I2C2       */         
    SPI0_IRQn                =  24,   /**< \brief  24  SPI0       */         
    SPI1_IRQn                =  25,   /**< \brief  25  SPI1       */         
    ADC_SEQA_IRQn            =  26,   /**< \brief  26  ADC_SEQA   */         
    ADC_SEQB_IRQn            =  27,   /**< \brief  27  ADC_SEQB   */         
    ADC_THCMP_IRQn           =  28,   /**< \brief  28  ADC_THCMP  */         
    RTC_IRQn                 =  29,   /**< \brief  29  RTC        */         
    MAILBOX_IRQn             =  31,   /**< \brief  31  MAILBOX    */         
#endif

} IRQn_Type;

/** 
 * \addtogroup amhw_if_lpc5410x
 * \copydoc amhw_lpc5410x.h
 * @{
 */

/**
 * \name Cortex-M4核 和 Cortex-M0+ 核处理器和外设配置
 * @{
 */
#if defined AM_CORTEX_M4

#define __CM4_REV              1 /**< \brief Cortex-M4 核版本号                    */
#define __MPU_PRESENT          1 /**< \brief M4核有MPU，M0+核无MPU                 */
#define __NVIC_PRIO_BITS       3 /**< \brief M4核用于中断优先级的位数为3，M0+核为2 */
#define __Vendor_SysTickConfig 0 /**< \brief M4核和M0+核没有用到不同的SYSTICK      */
#define __FPU_PRESENT          1 /**< \brief M4核有FPU                             */

#include "core_cm4.h"

#endif

#if defined AM_CORTEX_M0

#define __CM0PLUS_REV           1  /**< \brief Cortex-M0+ 核版本号                   */
#define __MPU_PRESENT           0  /**< \brief M4核有MPU，M0+核无MPU                 */
#define __VTOR_PRESENT          1  /**< \brief M0+核有中断向量表                     */
#define __NVIC_PRIO_BITS        2  /**< \brief M4核用于中断优先级的位数为3，M0+核为2 */
#define __Vendor_SysTickConfig  0  /**< \brief M4核和M0+核没有用到不同的SYSTICK      */

#include "core_cm0plus.h"

#endif
/** @} */

/**
 * \name 外设内存映射地址定义
 * @{
 */

#define AMHW_GPIO_BASE        0x1C000000UL /**< \brief GPIO的基地址           */
#define AMHW_DMA_BASE         0x1C004000UL /**< \brief DMA的基地址            */
#define AMHW_CRC_BASE         0x1C010000UL /**< \brief CRC的基地址            */
#define AMHW_SCT0_BASE        0x1C018000UL /**< \brief SCT0的基地址           */
#define AMHW_MAILBOX_BASE     0x1C02C000UL /**< \brief MailBox的基地址        */
#define AMHW_ADC0_BASE        0x1C034000UL /**< \brief ADC0的基地址           */
#define AMHW_FIFO_BASE        0x1C038000UL /**< \brief FIFO的基地址           */
#define AMHW_SYSCON_BASE      0x40000000UL /**< \brief SYSCON的基地址         */
#define AMHW_TIMER2_BASE      0x40004000UL /**< \brief Timer2的基地址         */
#define AMHW_TIMER3_BASE      0x40008000UL /**< \brief Timer3的基地址         */
#define AMHW_TIMER4_BASE      0x4000C000UL /**< \brief Timer4的基地址         */
#define AMHW_GINT0_BASE       0x40010000UL /**< \brief GINT0的基地址          */
#define AMHW_GINT1_BASE       0x40014000UL /**< \brief GINT1的基地址          */
#define AMHW_PINT_BASE        0x40018000UL /**< \brief PINT的基地址           */
#define AMHW_IOCON_BASE       0x4001C000UL /**< \brief IOCON的基地址          */
#define AMHW_UTICK_BASE       0x40020000UL /**< \brief UTICK的基地址          */
#define AMHW_ADVSYSCON_BASE   0x4002C000UL /**< \brief ADVSYSCON的基地址      */
#define AMHW_WWDT_BASE        0x40038000UL /**< \brief WWDT的基地址           */
#define AMHW_RTC_BASE         0x4003C000UL /**< \brief RTC的基地址            */
#define AMHW_INMUX_BASE       0x40050000UL /**< \brief INMUX的基地址          */
#define AMHW_RIT_BASE         0x40070000UL /**< \brief RIT的基地址            */
#define AMHW_MRT_BASE         0x40074000UL /**< \brief MRT的基地址            */
#define AMHW_ASYNCSYSCON_BASE 0x40080000UL /**< \brief ASYNCSYSCON的基地址    */
#define AMHW_USART0_BASE      0x40084000UL /**< \brief USART0的基地址         */
#define AMHW_USART1_BASE      0x40088000UL /**< \brief USART1的基地址         */
#define AMHW_USART2_BASE      0x4008C000UL /**< \brief USART2的基地址         */
#define AMHW_USART3_BASE      0x40090000UL /**< \brief USART3的基地址         */
#define AMHW_I2C0_BASE        0x40094000UL /**< \brief I2C0的基地址           */
#define AMHW_I2C1_BASE        0x40098000UL /**< \brief I2C1的基地址           */
#define AMHW_I2C2_BASE        0x4009C000UL /**< \brief I2C2的基地址           */
#define AMHW_SPI0_BASE        0x400A4000UL /**< \brief SPI0的基地址           */
#define AMHW_SPI1_BASE        0x400A8000UL /**< \brief SPI1的基地址           */
#define AMHW_TIMER0_BASE      0x400B4000UL /**< \brief TIMER0的基地址         */
#define AMHW_TIMER1_BASE      0x400B8000UL /**< \brief TIMER1的基地址         */
#define AMHW_PMU_BASE         0x4002C000UL /**< \brief 的基地址PMU            */
#define AMHW_NVIC_BASE        (0xE000E000UL + 0x100UL) /**< \brief NVIC的基地址    */
#define AMHW_SYSTICK_BASE     (0xE000E000UL + 0x010UL) /**< \brief SYSTICK的基地址 */
#define AMHW_IAP_ENTRY_LOCATION   0x03000205UL /**< \brief ROM中IAP函数入口地址    */

/** @} */

/**
 * \name 外设定义         
 * @{
 */

#define AMHW_GPIO        ((amhw_gpio_t        *)AMHW_GPIO_BASE)    /**< \brief GPIO     */
#define AMHW_DMA         ((amhw_dma_t         *)AMHW_DMA_BASE)     /**< \brief DMA      */
#define AMHW_CRC         ((amhw_crc_t         *)AMHW_CRC_BASE)     /**< \brief CRC      */
#define AMHW_SCT0        ((amhw_sct_t         *)AMHW_SCT0_BASE)    /**< \brief SCT0     */
#define AMHW_MAILBOX     ((amhw_mailbox_t     *)AMHW_MAILBOX_BASE) /**< \brief MailBox  */
#define AMHW_ADC0        ((amhw_adc_t         *)AMHW_ADC0_BASE)    /**< \brief ADC0     */
#define AMHW_FIFO        ((amhw_fifo_t        *)AMHW_FIFO_BASE)    /**< \brief FIFO     */
#define AMHW_SYSCON      ((amhw_syscon_t      *)AMHW_SYSCON_BASE)  /**< \brief SYSCON   */
#define AMHW_TIMER2      ((amhw_timer_t       *)AMHW_TIMER2_BASE)  /**< \brief Timer2   */
#define AMHW_TIMER3      ((amhw_timer_t       *)AMHW_TIMER3_BASE)  /**< \brief Timer3   */
#define AMHW_TIMER4      ((amhw_timer_t       *)AMHW_TIMER4_BASE)  /**< \brief Timer4   */
#define AMHW_GINT        ((amhw_gint_t        *)AMHW_GINT0_BASE)   /**< \brief GINT     */
#define AMHW_PINT        ((amhw_pint_t        *)AMHW_PINT_BASE)    /**< \brief PINT     */
#define AMHW_IOCON       ((amhw_iocon_t       *)AMHW_IOCON_BASE)   /**< \brief IOCON    */
#define AMHW_UTICK       ((amhw_utick_t       *)AMHW_UTICK_BASE)   /**< \brief UTICK    */
#define AMHW_ADVSYSCON   ((amhw_advsyscon_t   *)AMHW_ADVSYSCON_BASE) /**< \brief ADVSYSCON  */
#define AMHW_WWDT        ((amhw_wwdt_t        *)AMHW_WWDT_BASE)    /**< \brief wwdt     */
#define AMHW_RTC         ((amhw_rtc_t         *)AMHW_RTC_BASE)     /**< \brief RTC      */
#define AMHW_INMUX       ((amhw_inmux_t       *)AMHW_INMUX_BASE)   /**< \brief Input mux  */
#define AMHW_RIT         ((amhw_rit_t         *)AMHW_RIT_BASE)     /**< \brief RIT      */
#define AMHW_MRT         ((amhw_mrt_t         *)AMHW_MRT_BASE)     /**< \brief MRT      */
#define AMHW_ASYNCSYSCON ((amhw_asyncsyscon_t *)AMHW_ASYNCSYSCON_BASE) /**< \brief  ASYNC SYSCON  */
#define AMHW_USART0      ((amhw_usart_t       *)AMHW_USART0_BASE)  /**< \brief USART0   */
#define AMHW_USART1      ((amhw_usart_t       *)AMHW_USART1_BASE)  /**< \brief USART1   */
#define AMHW_USART2      ((amhw_usart_t       *)AMHW_USART2_BASE)  /**< \brief USART2   */
#define AMHW_USART3      ((amhw_usart_t       *)AMHW_USART3_BASE)  /**< \brief USART3   */
#define AMHW_I2C0        ((amhw_i2c_t         *)AMHW_I2C0_BASE)    /**< \brief I2C0     */
#define AMHW_I2C1        ((amhw_i2c_t         *)AMHW_I2C1_BASE)    /**< \brief I2C1     */
#define AMHW_I2C2        ((amhw_i2c_t         *)AMHW_I2C2_BASE)    /**< \brief I2C2     */
#define AMHW_SPI0        ((amhw_spi_t         *)AMHW_SPI0_BASE)    /**< \brief SPI0     */
#define AMHW_SPI1        ((amhw_spi_t         *)AMHW_SPI1_BASE)    /**< \brief SPI1     */
#define AMHW_TIMER0      ((amhw_timer_t       *)AMHW_TIMER0_BASE)  /**< \brief Timer0   */
#define AMHW_TIMER1      ((amhw_timer_t       *)AMHW_TIMER1_BASE)  /**< \brief Timer1   */
#define AMHW_PMU         ((amhw_pmu_t         *)AMHW_PMU_BASE)     /**< \brief PMU      */
                         
#define AMHW_INT         ((amhw_int_t         *)AMHW_NVIC_BASE)    /**< \brief  NVIC     */
#define AMHW_SYSTICK     ((amhw_systick_t     *)AMHW_SYSTICK_BASE) /**< \brief  SYSTICK  */

/** @} */


/**
 * @} amhw_if_lpc5410x
 */

#ifdef __cplusplus
}
#endif


#endif  /* __AMHW_LPC5410X_H */

/* end of file */

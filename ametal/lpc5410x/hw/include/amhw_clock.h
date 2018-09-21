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
 * \brief 时钟选择和控制接口
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_CLOCK_H
#define __AMHW_CLOCK_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_syscon.h"
#include "amhw_pll.h"

/**
 * \addtogroup amhw_if_clock
 * \copydoc amhw_clock.h
 * @{
 */

extern uint32_t g_main_clkfreq;   /**< \brief 主时钟的频率（单位:Hz）         */
extern uint32_t g_system_clkfreq; /**< \brief 系统时钟的频率 （单位:Hz）      */
extern uint32_t g_async_clkfreq;  /**< \brief 异步时钟频率（单位:Hz）         */
extern uint32_t g_wdtosc_clkfreq; /**< \brief 看门狗振荡器频率（单位:Hz）     */

/**
 * \name 频率值定义
 *
 * 如果使用了外部管脚（PIO0_22）作为时钟输入管脚，则需要将 AMHW_CLOCK_FREQ_CLKIN
 * 设置为正确的频率值.
 *
 * @{
 */

#define AMHW_CLOCK_FREQ_RTC      32768UL      /**< \brief RTC振荡器频率       */
#define AMHW_CLOCK_FREQ_IRC      12000000UL   /**< \brief 内部IRC频率         */
#define AMHW_CLOCK_FREQ_CLKIN    0UL          /**< \brief 外部管脚的输入频率  */
#define AMHW_CLOCK_FREQ_WDTOSC   500000UL     /**< \brief WDT振荡器频率       */

/** @} */

/**
 * \brief 系统或外设时钟定义
 */
typedef enum amhw_clock_periph {

    AMHW_CLOCK_ROM = 1,           /**< \brief ROM 时钟                        */
    AMHW_CLOCK_SRAM1 = 3,         /**< \brief SRAM1 时钟                      */
    AMHW_CLOCK_SRAM2,             /**< \brief SRAM2 时钟                      */
    AMHW_CLOCK_FLASH = 7,         /**< \brief FLASH 控制器时钟                */
    AMHW_CLOCK_FMC,               /**< \brief FMC 时钟                        */
    AMHW_CLOCK_INMUX = 11,        /**< \brief 输入复用时钟                    */
    AMHW_CLOCK_IOCON = 13,        /**< \brief IOCON 时钟                      */
    AMHW_CLOCK_GPIO0,             /**< \brief GPIO0 时钟                      */
    AMHW_CLOCK_GPIO1,             /**< \brief GPIO1 时钟                      */
    AMHW_CLOCK_PINT = 18,         /**< \brief PININT 时钟                     */
    AMHW_CLOCK_GINT,              /**< \brief grouped pin interrupt 时钟      */
    AMHW_CLOCK_DMA,               /**< \brief DMA 时钟                        */
    AMHW_CLOCK_CRC,               /**< \brief CRC 时钟                        */
    AMHW_CLOCK_WWDT,              /**< \brief WDT 时钟                        */
    AMHW_CLOCK_RTC,               /**< \brief RTC 时钟                        */
    AMHW_CLOCK_MAILBOX = 26,      /**< \brief Mailbox 时钟                    */
    AMHW_CLOCK_ADC0,              /**< \brief ADC0 时钟                       */

    AMHW_CLOCK_MRT = 32,          /**< \brief multi-rate timer 时钟           */
    AMHW_CLOCK_RIT,               /**< \brief Repetitive interval timer 时钟  */
    AMHW_CLOCK_SCT0,              /**< \brief SCT0 时钟                       */
    AMHW_CLOCK_FIFO = 32 + 9,     /**< \brief System FIFO 时钟                */
    AMHW_CLOCK_UTICK,             /**< \brief UTICK 时钟                      */
    AMHW_CLOCK_TIMER2 = 32 + 22,  /**< \brief Standard timer 2 时钟           */
    AMHW_CLOCK_TIMER3 = 32 + 26,  /**< \brief Standard timer 3 时钟           */
    AMHW_CLOCK_TIMER4,            /**< \brief Standard timer 4 时钟           */

    AMHW_CLOCK_USART0 = 128 + 1,   /**< \brief USART0 时钟                    */
    AMHW_CLOCK_USART1,             /**< \brief USART1 时钟                    */
    AMHW_CLOCK_USART2,             /**< \brief USART2 时钟                    */
    AMHW_CLOCK_USART3,             /**< \brief USART3 时钟                    */
    AMHW_CLOCK_I2C0,               /**< \brief I2C0  时钟                     */
    AMHW_CLOCK_I2C1,               /**< \brief I2C1  时钟                     */
    AMHW_CLOCK_I2C2,               /**< \brief I2C2  时钟                     */
    AMHW_CLOCK_SPI0 = 128 + 9,     /**< \brief SPI0  时钟                     */
    AMHW_CLOCK_SPI1,               /**< \brief SPI1  时钟                     */
    AMHW_CLOCK_TIMER0 = 128 + 13,  /**< \brief Standard timer 0 时钟          */
    AMHW_CLOCK_TIMER1,             /**< \brief Standard timer 1 时钟          */
    AMHW_CLOCK_FRG                 /**< \brief FRG 时钟                       */
} amhw_clock_periph_t;


/**
 * \brief main A 时钟源
 */
typedef enum amhw_clock_main_a_src {
    AMHW_CLOCK_MAIN_A_SRC_IRC = 0,   /**< \brief 内部IRC            */
    AMHW_CLOCK_MAIN_A_SRC_CLKIN,     /**< \brief 外部管脚输入时钟   */
    AMHW_CLOCK_MAIN_A_SRC_WDTOSC,    /**< \brief 看门狗振荡器       */
} amhw_clock_main_a_src_t;

/**
 * \brief main B 时钟源
 */
typedef enum amhw_clock_main_b_src {
    AMHW_CLOCK_MAIN_B_SRC_MAINCLKSELA = 0, /**< \brief main A 时钟       */
    AMHW_CLOCK_MAIN_B_SRC_PLLIN,           /**< \brief PLL输入时钟       */
    AMHW_CLOCK_MAIN_B_SRC_PLLOUT,          /**< \brief PLL输出           */
    AMHW_CLOCK_MAIN_B_SRC_RTC,             /**< \brief RTC晶体振荡器     */
} amhw_clock_main_b_src_t;

/**
 * \brief main 时钟源
 */
typedef enum amhw_clock_main_src {
    AMHW_CLOCK_MAIN_SRC_IRC = 0,          /**< \brief 内部IRC            */
    AMHW_CLOCK_MAIN_SRC_CLKIN,            /**< \brief 外部管脚输入时钟   */
    AMHW_CLOCK_MAIN_SRC_WDTOSC,           /**< \brief 看门狗振荡器       */
    AMHW_CLOCK_MAIN_SRC_PLLIN = 5,        /**< \brief PLL输入时钟        */
    AMHW_CLOCK_MAIN_SRC_PLLOUT,           /**< \brief PLL输出            */
    AMHW_CLOCK_MAIN_SRC_RTC,              /**< \brief RTC晶体振荡器      */
} amhw_clock_main_src_t;

/**
 * \brief CLKOUT Pin 时钟源
 */
typedef enum amhw_clock_clkout_src {
    AMHW_CLOCK_CLKOUT_SRC_MAINCLK = 0,    /**< \brief Main 时钟            */
    AMHW_CLOCK_CLKOUT_SRC_CLKIN,          /**< \brief 外部管脚输入时钟     */
    AMHW_CLOCK_CLKOUT_SRC_WDTOSC,         /**< \brief 看门狗振荡器         */
    AMHW_CLOCK_CLKOUT_SRC_IRC,            /**< \brief 内部IRC              */
    AMHW_CLOCK_CLKOUT_SRC_RTC             /**< \brief RTC晶体振荡器        */
} amhw_clock_clkout_src_t;

/**
 * \brief ADC时钟源
 */
typedef enum amhw_clock_adc_src {
    AMHW_CLOCK_ADC_SRC_MAINCLK = 0,       /**< \brief Main 时钟           */
    AMHW_CLOCK_ADC_SRC_SYSPLLOUT,         /**< \brief PLL输出             */
    AMHW_CLOCK_ADC_SRC_IRC                /**< \brief 内部IRC             */
} amhw_clock_adc_src_t;

/**
 * \brief 异步时钟源
 */
typedef enum amhw_clock_async_src {
    AMHW_CLOCK_ASYNC_SRC_IRC = 0,         /**< \brief 内部IRC             */
    AMHW_CLOCK_ASYNC_SRC_WDTOSC,          /**< \brief 看门狗振荡器        */
    AMHW_CLOCK_ASYNC_SRC_MAINCLK = 4,     /**< \brief Main 时钟           */
    AMHW_CLOCK_ASYNC_SRC_CLKIN,           /**< \brief 外部管脚输入时钟    */
    AMHW_CLOCK_ASYNC_SRC_PLLOUT           /**< \brief PLL输出             */
} amhw_clock_async_src_t;


/**
 * \brief 得到内部IRC时钟频率
 * \return 内部IRC时钟频率（单位：Hz）
 */
am_static_inline
uint32_t amhw_clock_irc_rate_get (void)
{
    return AMHW_CLOCK_FREQ_IRC;
}

/**
 * \brief 得到外部管脚输入时钟频率
 * \return 外部管脚输入时钟频率（单位：Hz）
 */
am_static_inline
uint32_t amhw_clock_clkin_rate_get (void)
{
    return AMHW_CLOCK_FREQ_CLKIN;
}

/**
 * \brief 得到RTC晶体振荡器的时钟频率
 * \return  RTC晶体振荡器的时钟频率（单位：Hz）
 */
am_static_inline
uint32_t amhw_clock_rtc_rate_get (void)
{
    return AMHW_CLOCK_FREQ_RTC;
}

/**
 * \brief 得到WDT振荡器的时钟频率
 *
 *     如果全局变量 g_wdtosc_clkfreq 不为0.表明WDT振荡器的频率已经通过频率测
 * 量单元校准。
 *
 * \return  WDT振荡器的时钟频率（单位：Hz）
 * \note This rate is accurate to plus or minus 40%.
 */
am_static_inline
uint32_t amhw_clock_wdt_rate_get (void)
{
    if (g_wdtosc_clkfreq == 0) {
        return AMHW_CLOCK_FREQ_WDTOSC;
    }
    return g_wdtosc_clkfreq;
}


/**
 * \brief 设置 main A 时钟源
 * \param[in] src : main A 时钟源
 * \return 无
 */
am_static_inline
void amhw_clock_main_a_src_set (amhw_clock_main_a_src_t src)
{
    AMHW_SYSCON->mainclksela = (uint32_t)src;
}

/**
 * \brief 得到 main A 时钟源
 * \return main A 时钟源
 */
am_static_inline
amhw_clock_main_a_src_t amhw_clock_main_a_src_get (void)
{
    return (amhw_clock_main_a_src_t)(AMHW_SYSCON->mainclksela);
}

/**
 * \brief 得到 main A 时钟频率
 * \return  main A 时钟频率（单位:Hz）
 */
uint32_t amhw_clock_main_a_clkrate_get(void);

/**
 * \brief 设置 main B 时钟源
 * \param[in] src : main B 时钟源
 * \return 无
 */
am_static_inline
void amhw_clock_main_b_src_set (amhw_clock_main_b_src_t src)
{
    AMHW_SYSCON->mainclkselb = (uint32_t)src;
}

/**
 * \brief 得到 main B 时钟源
 * \return main B 时钟源
 */
am_static_inline
amhw_clock_main_b_src_t amhw_clock_main_b_src_get (void)
{
    return (amhw_clock_main_b_src_t)(AMHW_SYSCON->mainclkselb);
}

/**
 * \brief 得到 main B 时钟频率
 * \return  main B 时钟频率（单位:Hz）
 */
uint32_t amhw_clock_main_b_clkrate_get(void);


/**
 * \brief 设置 main 时钟源
 * \param[in] src : main 时钟源
 * \return 无
 * \note 如果需要的话，该函数会打开相应时钟源的电源。使用该函数直接设置主时钟源
 *       用户无需分别设置main A 和 main B时钟源。
 */
void amhw_clock_main_src_set(amhw_clock_main_src_t src);

/**
 * \brief 得到 main 时钟源
 * \return main 时钟源
 */
amhw_clock_main_src_t amhw_clock_main_src_get(void);

/**
 * \brief 得到 main 时钟频率
 * \return  main 时钟频率（单位:Hz）
 */
uint32_t amhw_clock_main_clkrate_get(void);

/**
 * \brief 设置 CLKOUT 时钟源和分频值
 *
 * \param[in] src : CLKOUT的时钟源
 * \param[in] div : 对CLKOUT时钟源的分频
 *
 * \return 无
 *
 * \note 分频值为0时将禁能CLKOUT的输出，其它有效值为1~255. 最终CLKOUT管脚输出的
 *       时钟频率为，CLKOUT时钟源的频率除以分频系数。  
 */
void amhw_clock_clkout_config(amhw_clock_clkout_src_t src, uint32_t div);

/**
 * \brief 禁能指定的系统或外设时钟
 * \param[in] clk : 指定的待禁能的系统或外设时钟
 * \return 无
 */
void amhw_clock_periph_disable(amhw_clock_periph_t clk);

/**
 * \brief 使能指定的系统或外设时钟
 * \param[in] clk : 指定的待使能的系统或外设时钟
 * \return 无
 */
void amhw_clock_periph_enable(amhw_clock_periph_t clk);

/**
 * \brief 检查指定的系统或外设时钟是否使能
 * \param[in] clk   : 指定的待检测的系统或外设时钟
 * \retval    TRUE  : 指定的系统或外设时钟已使能.
 * \retval    FALSE : 指定的系统或外设时钟未使能.
 */
bool_t amhw_clock_periph_check(amhw_clock_periph_t clk);

/**
 * \brief 更新时钟频率
 *
 *   该函数会更新全局变量： g_main_clkfreq, g_system_clkfreq 和 g_async_clkfreq.
 *
 * \return 无
 *
 * \note 仅当时钟变化时，才调用该函数更新全局变量值
 */
void amhw_clock_freq_update(void);

/**
 * \brief 更新 WDT 振荡器时钟频率.
 *
 *  该函数将会使用系统控制中的时钟频率测量单元测量 WDT 振荡器时钟频率.
 *  同时更新全局变量 g_wdtosc_clkfreq 的值。 
 *
 * \return  无
 */
void amhw_clock_wdt_freq_update(void);

/**
 * \brief 设置Systick时钟分频值(仅当 CLKIN 作为SYSTICK时钟时有效)
 * \param[in] div : systick 时钟分频值
 * \return 无
 * \note 分频值为0时将禁能Systick时钟，其它有效值为1~255. 当 CLKIN 作为SYSTICK
 *       时钟时(通过清除Systick的CSR寄存器的bit2),Systick的时钟频率为
 *       外部管脚输入时钟频率（CLKIN rate）除以该处设置的时钟分频值。
 *       值得注意的是，内核时钟频率至少在Systick时钟频率的2.5倍以上.
 */
am_static_inline
void amhw_clock_systick_clkdiv_set (uint32_t div)
{
    AMHW_SYSCON->systickclkdiv = div;
}

/**
 * \brief 得到Systick时钟分频值
 * \return Systick时钟分频值
 */
am_static_inline
uint32_t amhw_clock_systick_clkdiv_get (void)
{
    return AMHW_SYSCON->systickclkdiv;
}

/**
 * \brief 得到Systick时钟频率（仅当Systick时钟使用到Systick时钟分频器时有效）
 * \return Systick时钟频率
 */
uint32_t amhw_clock_systick_clkrate_get(void);

/**
 * \brief 设置系统时钟分频值
 * \param[in] div : 系统时钟分频值
 * \return 无
 * \note 分频值为0时将禁能系统时钟，其它有效值为1~255.系统时钟频率为主时钟频率除
 *       以该处设置的系统时钟分频值。
 */
am_static_inline
void amhw_clock_system_clkdiv_set (uint32_t div)
{
    AMHW_SYSCON->ahbclkdiv = div;
}

/**
 * \brief 得到系统时钟分频值
 * \return 系统时钟分频值
 */
am_static_inline
uint32_t amhw_clock_system_clkdiv_get (void)
{
    return AMHW_SYSCON->ahbclkdiv;
}

/**
 * \brief 设置ADC时钟分频值
 * \param[in] div : ADC时钟分频值
 * \return 无
 * \note 分频值为0时将禁能ADC时钟，其它有效值为1~255.
 */
am_static_inline
void amhw_clock_adc_clkdiv_set (uint32_t div)
{
    AMHW_SYSCON->adcclkdiv = div;
}

/**
 * \brief 得到ADC时钟分频值
 * \return ADC时钟分频值, 0表明时钟被禁止
 */
am_static_inline
uint32_t amhw_clock_adc_clkdiv_get (void)
{
    return AMHW_SYSCON->adcclkdiv;
}

/**
 * \brief 设置ADC时钟源
 * \param[in] src : ADC时钟源
 * \return 无
 */
am_static_inline
void amhw_clock_adc_src_set (amhw_clock_adc_src_t src)
{
    AMHW_SYSCON->adcclksel = (uint32_t) src;
}

/**
 * \brief 得到ADC时钟源
 * \return ADC时钟源
 */
am_static_inline
amhw_clock_adc_src_t amhw_clock_adc_src_get (void)
{
    return (amhw_clock_adc_src_t)(AMHW_SYSCON->adcclksel);
}

/**
 * \brief 得到ADC时钟频率
 * \return ADC时钟频率
 */
uint32_t amhw_clock_adc_clkrate_get (void);

/**
 * \brief 使能RTC晶体振荡器波形输出
 * \return 无
 */
am_static_inline
void amhw_clock_rtcosc_enable (void)
{
    AMHW_SYSCON->rtcoscctrl = 1;
}

/**
 * \brief 禁能RTC晶体振荡器波形输出
 * \return 无
 */
am_static_inline
void amhw_clock_rtcosc_disable (void)
{
    AMHW_SYSCON->rtcoscctrl = 0;
}

/**
 * \brief 设置异步时钟源
 * \param[in] src : 异步时钟源
 * \return 无
 */
void amhw_clock_async_src_set(amhw_clock_async_src_t src);

/**
 * \brief 得到异步时钟源
 * \return 异步时钟源
 */
amhw_clock_async_src_t amhw_clock_async_src_get(void);

/**
 * \brief 得到异步时钟频率
 * \return 异步时钟频率
 */
uint32_t amhw_clock_async_clkrate_get(void);

/**
 * \brief 设置异步时钟分频值
 * \param[in] div : 异步时钟分频值
 * \return 无
 * \note 分频值为0时将禁能异步时钟，其它有效值为1~255.
 */
am_static_inline
void amhw_clock_async_clkdiv_set (uint32_t div)
{
    AMHW_ASYNCSYSCON->asyncclkdiv = div;
}

/**
 * \brief 得到异步时钟分频值
 * \return 异步时钟分频值
 */
am_static_inline
uint32_t amhw_clock_async_clkdiv_get (uint32_t div)
{
    return (AMHW_ASYNCSYSCON->asyncclkdiv);
}

/**
 * \brief 得到系统时钟频率
 * \return 系统时钟频率
 */
uint32_t amhw_clock_system_clkrate_get(void);

/**
 * \brief 得到串口基本输入频率（通过FRG）
 * \return 串口基本输入频率
 */
uint32_t amhw_clock_usart_baseclkrate_get(void);

/**
 * \brief 设置串口基本输入频率（通过FRG）
 *
 * 为了获取高精度的波特率，需要利用小数分频器（FRG）将串口的基本输入频率设置为
 * 期望波特率的整数倍。\n
 * 串口基本输入频率的范围是：g_async_clkfreq / (1 + 255/256) ~ g_async_clkfreq \n
 * 例如：\n
 * g_async_clkfreq = 12MHz \n
 * 串口基本输入频率的范围即为： 6,011,741Hz ~ 12MHz \n
 * 为了设置波特率为115200,故设置串口基本输入频率为：
 * 11,059,200Hz(11059200 = 115200 * 96).\n
 * 实际上，串口基本输入频率设置为11.0592MHz，可满足大多数波特率的设置 
 *
 * \param[in] rate : 期望的串口基本输入频率设置值
 * \return 实际的串口基本输入频率值，可能与期望值存在偏差
 */
uint32_t amhw_clock_usart_baseclkrate_set(uint32_t rate);


/**
 * \brief 得到外设的输入频率
 * \param[in] p_periph : 指向外设的寄存器块
 * \return 外设的输入频率
 * \note 调用该函数前，确保使用 amhw_clock_freq_update()
 *        和 amhw_clock_wdt_freq_update()函数更新了相应时钟全局变量的值。
 */
uint32_t amhw_clock_periph_freq_get(void *p_periph);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_CLOCK_H */

/* end of file */

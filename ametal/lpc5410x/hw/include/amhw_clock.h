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
 * \brief ʱ��ѡ��Ϳ��ƽӿ�
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

extern uint32_t g_main_clkfreq;   /**< \brief ��ʱ�ӵ�Ƶ�ʣ���λ:Hz��         */
extern uint32_t g_system_clkfreq; /**< \brief ϵͳʱ�ӵ�Ƶ�� ����λ:Hz��      */
extern uint32_t g_async_clkfreq;  /**< \brief �첽ʱ��Ƶ�ʣ���λ:Hz��         */
extern uint32_t g_wdtosc_clkfreq; /**< \brief ���Ź�����Ƶ�ʣ���λ:Hz��     */

/**
 * \name Ƶ��ֵ����
 *
 * ���ʹ�����ⲿ�ܽţ�PIO0_22����Ϊʱ������ܽţ�����Ҫ�� AMHW_CLOCK_FREQ_CLKIN
 * ����Ϊ��ȷ��Ƶ��ֵ.
 *
 * @{
 */

#define AMHW_CLOCK_FREQ_RTC      32768UL      /**< \brief RTC����Ƶ��       */
#define AMHW_CLOCK_FREQ_IRC      12000000UL   /**< \brief �ڲ�IRCƵ��         */
#define AMHW_CLOCK_FREQ_CLKIN    0UL          /**< \brief �ⲿ�ܽŵ�����Ƶ��  */
#define AMHW_CLOCK_FREQ_WDTOSC   500000UL     /**< \brief WDT����Ƶ��       */

/** @} */

/**
 * \brief ϵͳ������ʱ�Ӷ���
 */
typedef enum amhw_clock_periph {

    AMHW_CLOCK_ROM = 1,           /**< \brief ROM ʱ��                        */
    AMHW_CLOCK_SRAM1 = 3,         /**< \brief SRAM1 ʱ��                      */
    AMHW_CLOCK_SRAM2,             /**< \brief SRAM2 ʱ��                      */
    AMHW_CLOCK_FLASH = 7,         /**< \brief FLASH ������ʱ��                */
    AMHW_CLOCK_FMC,               /**< \brief FMC ʱ��                        */
    AMHW_CLOCK_INMUX = 11,        /**< \brief ���븴��ʱ��                    */
    AMHW_CLOCK_IOCON = 13,        /**< \brief IOCON ʱ��                      */
    AMHW_CLOCK_GPIO0,             /**< \brief GPIO0 ʱ��                      */
    AMHW_CLOCK_GPIO1,             /**< \brief GPIO1 ʱ��                      */
    AMHW_CLOCK_PINT = 18,         /**< \brief PININT ʱ��                     */
    AMHW_CLOCK_GINT,              /**< \brief grouped pin interrupt ʱ��      */
    AMHW_CLOCK_DMA,               /**< \brief DMA ʱ��                        */
    AMHW_CLOCK_CRC,               /**< \brief CRC ʱ��                        */
    AMHW_CLOCK_WWDT,              /**< \brief WDT ʱ��                        */
    AMHW_CLOCK_RTC,               /**< \brief RTC ʱ��                        */
    AMHW_CLOCK_MAILBOX = 26,      /**< \brief Mailbox ʱ��                    */
    AMHW_CLOCK_ADC0,              /**< \brief ADC0 ʱ��                       */

    AMHW_CLOCK_MRT = 32,          /**< \brief multi-rate timer ʱ��           */
    AMHW_CLOCK_RIT,               /**< \brief Repetitive interval timer ʱ��  */
    AMHW_CLOCK_SCT0,              /**< \brief SCT0 ʱ��                       */
    AMHW_CLOCK_FIFO = 32 + 9,     /**< \brief System FIFO ʱ��                */
    AMHW_CLOCK_UTICK,             /**< \brief UTICK ʱ��                      */
    AMHW_CLOCK_TIMER2 = 32 + 22,  /**< \brief Standard timer 2 ʱ��           */
    AMHW_CLOCK_TIMER3 = 32 + 26,  /**< \brief Standard timer 3 ʱ��           */
    AMHW_CLOCK_TIMER4,            /**< \brief Standard timer 4 ʱ��           */

    AMHW_CLOCK_USART0 = 128 + 1,   /**< \brief USART0 ʱ��                    */
    AMHW_CLOCK_USART1,             /**< \brief USART1 ʱ��                    */
    AMHW_CLOCK_USART2,             /**< \brief USART2 ʱ��                    */
    AMHW_CLOCK_USART3,             /**< \brief USART3 ʱ��                    */
    AMHW_CLOCK_I2C0,               /**< \brief I2C0  ʱ��                     */
    AMHW_CLOCK_I2C1,               /**< \brief I2C1  ʱ��                     */
    AMHW_CLOCK_I2C2,               /**< \brief I2C2  ʱ��                     */
    AMHW_CLOCK_SPI0 = 128 + 9,     /**< \brief SPI0  ʱ��                     */
    AMHW_CLOCK_SPI1,               /**< \brief SPI1  ʱ��                     */
    AMHW_CLOCK_TIMER0 = 128 + 13,  /**< \brief Standard timer 0 ʱ��          */
    AMHW_CLOCK_TIMER1,             /**< \brief Standard timer 1 ʱ��          */
    AMHW_CLOCK_FRG                 /**< \brief FRG ʱ��                       */
} amhw_clock_periph_t;


/**
 * \brief main A ʱ��Դ
 */
typedef enum amhw_clock_main_a_src {
    AMHW_CLOCK_MAIN_A_SRC_IRC = 0,   /**< \brief �ڲ�IRC            */
    AMHW_CLOCK_MAIN_A_SRC_CLKIN,     /**< \brief �ⲿ�ܽ�����ʱ��   */
    AMHW_CLOCK_MAIN_A_SRC_WDTOSC,    /**< \brief ���Ź�����       */
} amhw_clock_main_a_src_t;

/**
 * \brief main B ʱ��Դ
 */
typedef enum amhw_clock_main_b_src {
    AMHW_CLOCK_MAIN_B_SRC_MAINCLKSELA = 0, /**< \brief main A ʱ��       */
    AMHW_CLOCK_MAIN_B_SRC_PLLIN,           /**< \brief PLL����ʱ��       */
    AMHW_CLOCK_MAIN_B_SRC_PLLOUT,          /**< \brief PLL���           */
    AMHW_CLOCK_MAIN_B_SRC_RTC,             /**< \brief RTC��������     */
} amhw_clock_main_b_src_t;

/**
 * \brief main ʱ��Դ
 */
typedef enum amhw_clock_main_src {
    AMHW_CLOCK_MAIN_SRC_IRC = 0,          /**< \brief �ڲ�IRC            */
    AMHW_CLOCK_MAIN_SRC_CLKIN,            /**< \brief �ⲿ�ܽ�����ʱ��   */
    AMHW_CLOCK_MAIN_SRC_WDTOSC,           /**< \brief ���Ź�����       */
    AMHW_CLOCK_MAIN_SRC_PLLIN = 5,        /**< \brief PLL����ʱ��        */
    AMHW_CLOCK_MAIN_SRC_PLLOUT,           /**< \brief PLL���            */
    AMHW_CLOCK_MAIN_SRC_RTC,              /**< \brief RTC��������      */
} amhw_clock_main_src_t;

/**
 * \brief CLKOUT Pin ʱ��Դ
 */
typedef enum amhw_clock_clkout_src {
    AMHW_CLOCK_CLKOUT_SRC_MAINCLK = 0,    /**< \brief Main ʱ��            */
    AMHW_CLOCK_CLKOUT_SRC_CLKIN,          /**< \brief �ⲿ�ܽ�����ʱ��     */
    AMHW_CLOCK_CLKOUT_SRC_WDTOSC,         /**< \brief ���Ź�����         */
    AMHW_CLOCK_CLKOUT_SRC_IRC,            /**< \brief �ڲ�IRC              */
    AMHW_CLOCK_CLKOUT_SRC_RTC             /**< \brief RTC��������        */
} amhw_clock_clkout_src_t;

/**
 * \brief ADCʱ��Դ
 */
typedef enum amhw_clock_adc_src {
    AMHW_CLOCK_ADC_SRC_MAINCLK = 0,       /**< \brief Main ʱ��           */
    AMHW_CLOCK_ADC_SRC_SYSPLLOUT,         /**< \brief PLL���             */
    AMHW_CLOCK_ADC_SRC_IRC                /**< \brief �ڲ�IRC             */
} amhw_clock_adc_src_t;

/**
 * \brief �첽ʱ��Դ
 */
typedef enum amhw_clock_async_src {
    AMHW_CLOCK_ASYNC_SRC_IRC = 0,         /**< \brief �ڲ�IRC             */
    AMHW_CLOCK_ASYNC_SRC_WDTOSC,          /**< \brief ���Ź�����        */
    AMHW_CLOCK_ASYNC_SRC_MAINCLK = 4,     /**< \brief Main ʱ��           */
    AMHW_CLOCK_ASYNC_SRC_CLKIN,           /**< \brief �ⲿ�ܽ�����ʱ��    */
    AMHW_CLOCK_ASYNC_SRC_PLLOUT           /**< \brief PLL���             */
} amhw_clock_async_src_t;


/**
 * \brief �õ��ڲ�IRCʱ��Ƶ��
 * \return �ڲ�IRCʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_clock_irc_rate_get (void)
{
    return AMHW_CLOCK_FREQ_IRC;
}

/**
 * \brief �õ��ⲿ�ܽ�����ʱ��Ƶ��
 * \return �ⲿ�ܽ�����ʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_clock_clkin_rate_get (void)
{
    return AMHW_CLOCK_FREQ_CLKIN;
}

/**
 * \brief �õ�RTC����������ʱ��Ƶ��
 * \return  RTC����������ʱ��Ƶ�ʣ���λ��Hz��
 */
am_static_inline
uint32_t amhw_clock_rtc_rate_get (void)
{
    return AMHW_CLOCK_FREQ_RTC;
}

/**
 * \brief �õ�WDT������ʱ��Ƶ��
 *
 *     ���ȫ�ֱ��� g_wdtosc_clkfreq ��Ϊ0.����WDT������Ƶ���Ѿ�ͨ��Ƶ�ʲ�
 * ����ԪУ׼��
 *
 * \return  WDT������ʱ��Ƶ�ʣ���λ��Hz��
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
 * \brief ���� main A ʱ��Դ
 * \param[in] src : main A ʱ��Դ
 * \return ��
 */
am_static_inline
void amhw_clock_main_a_src_set (amhw_clock_main_a_src_t src)
{
    AMHW_SYSCON->mainclksela = (uint32_t)src;
}

/**
 * \brief �õ� main A ʱ��Դ
 * \return main A ʱ��Դ
 */
am_static_inline
amhw_clock_main_a_src_t amhw_clock_main_a_src_get (void)
{
    return (amhw_clock_main_a_src_t)(AMHW_SYSCON->mainclksela);
}

/**
 * \brief �õ� main A ʱ��Ƶ��
 * \return  main A ʱ��Ƶ�ʣ���λ:Hz��
 */
uint32_t amhw_clock_main_a_clkrate_get(void);

/**
 * \brief ���� main B ʱ��Դ
 * \param[in] src : main B ʱ��Դ
 * \return ��
 */
am_static_inline
void amhw_clock_main_b_src_set (amhw_clock_main_b_src_t src)
{
    AMHW_SYSCON->mainclkselb = (uint32_t)src;
}

/**
 * \brief �õ� main B ʱ��Դ
 * \return main B ʱ��Դ
 */
am_static_inline
amhw_clock_main_b_src_t amhw_clock_main_b_src_get (void)
{
    return (amhw_clock_main_b_src_t)(AMHW_SYSCON->mainclkselb);
}

/**
 * \brief �õ� main B ʱ��Ƶ��
 * \return  main B ʱ��Ƶ�ʣ���λ:Hz��
 */
uint32_t amhw_clock_main_b_clkrate_get(void);


/**
 * \brief ���� main ʱ��Դ
 * \param[in] src : main ʱ��Դ
 * \return ��
 * \note �����Ҫ�Ļ����ú��������Ӧʱ��Դ�ĵ�Դ��ʹ�øú���ֱ��������ʱ��Դ
 *       �û�����ֱ�����main A �� main Bʱ��Դ��
 */
void amhw_clock_main_src_set(amhw_clock_main_src_t src);

/**
 * \brief �õ� main ʱ��Դ
 * \return main ʱ��Դ
 */
amhw_clock_main_src_t amhw_clock_main_src_get(void);

/**
 * \brief �õ� main ʱ��Ƶ��
 * \return  main ʱ��Ƶ�ʣ���λ:Hz��
 */
uint32_t amhw_clock_main_clkrate_get(void);

/**
 * \brief ���� CLKOUT ʱ��Դ�ͷ�Ƶֵ
 *
 * \param[in] src : CLKOUT��ʱ��Դ
 * \param[in] div : ��CLKOUTʱ��Դ�ķ�Ƶ
 *
 * \return ��
 *
 * \note ��ƵֵΪ0ʱ������CLKOUT�������������ЧֵΪ1~255. ����CLKOUT�ܽ������
 *       ʱ��Ƶ��Ϊ��CLKOUTʱ��Դ��Ƶ�ʳ��Է�Ƶϵ����  
 */
void amhw_clock_clkout_config(amhw_clock_clkout_src_t src, uint32_t div);

/**
 * \brief ����ָ����ϵͳ������ʱ��
 * \param[in] clk : ָ���Ĵ����ܵ�ϵͳ������ʱ��
 * \return ��
 */
void amhw_clock_periph_disable(amhw_clock_periph_t clk);

/**
 * \brief ʹ��ָ����ϵͳ������ʱ��
 * \param[in] clk : ָ���Ĵ�ʹ�ܵ�ϵͳ������ʱ��
 * \return ��
 */
void amhw_clock_periph_enable(amhw_clock_periph_t clk);

/**
 * \brief ���ָ����ϵͳ������ʱ���Ƿ�ʹ��
 * \param[in] clk   : ָ���Ĵ�����ϵͳ������ʱ��
 * \retval    TRUE  : ָ����ϵͳ������ʱ����ʹ��.
 * \retval    FALSE : ָ����ϵͳ������ʱ��δʹ��.
 */
bool_t amhw_clock_periph_check(amhw_clock_periph_t clk);

/**
 * \brief ����ʱ��Ƶ��
 *
 *   �ú��������ȫ�ֱ����� g_main_clkfreq, g_system_clkfreq �� g_async_clkfreq.
 *
 * \return ��
 *
 * \note ����ʱ�ӱ仯ʱ���ŵ��øú�������ȫ�ֱ���ֵ
 */
void amhw_clock_freq_update(void);

/**
 * \brief ���� WDT ����ʱ��Ƶ��.
 *
 *  �ú�������ʹ��ϵͳ�����е�ʱ��Ƶ�ʲ�����Ԫ���� WDT ����ʱ��Ƶ��.
 *  ͬʱ����ȫ�ֱ��� g_wdtosc_clkfreq ��ֵ�� 
 *
 * \return  ��
 */
void amhw_clock_wdt_freq_update(void);

/**
 * \brief ����Systickʱ�ӷ�Ƶֵ(���� CLKIN ��ΪSYSTICKʱ��ʱ��Ч)
 * \param[in] div : systick ʱ�ӷ�Ƶֵ
 * \return ��
 * \note ��ƵֵΪ0ʱ������Systickʱ�ӣ�������ЧֵΪ1~255. �� CLKIN ��ΪSYSTICK
 *       ʱ��ʱ(ͨ�����Systick��CSR�Ĵ�����bit2),Systick��ʱ��Ƶ��Ϊ
 *       �ⲿ�ܽ�����ʱ��Ƶ�ʣ�CLKIN rate�����Ըô����õ�ʱ�ӷ�Ƶֵ��
 *       ֵ��ע����ǣ��ں�ʱ��Ƶ��������Systickʱ��Ƶ�ʵ�2.5������.
 */
am_static_inline
void amhw_clock_systick_clkdiv_set (uint32_t div)
{
    AMHW_SYSCON->systickclkdiv = div;
}

/**
 * \brief �õ�Systickʱ�ӷ�Ƶֵ
 * \return Systickʱ�ӷ�Ƶֵ
 */
am_static_inline
uint32_t amhw_clock_systick_clkdiv_get (void)
{
    return AMHW_SYSCON->systickclkdiv;
}

/**
 * \brief �õ�Systickʱ��Ƶ�ʣ�����Systickʱ��ʹ�õ�Systickʱ�ӷ�Ƶ��ʱ��Ч��
 * \return Systickʱ��Ƶ��
 */
uint32_t amhw_clock_systick_clkrate_get(void);

/**
 * \brief ����ϵͳʱ�ӷ�Ƶֵ
 * \param[in] div : ϵͳʱ�ӷ�Ƶֵ
 * \return ��
 * \note ��ƵֵΪ0ʱ������ϵͳʱ�ӣ�������ЧֵΪ1~255.ϵͳʱ��Ƶ��Ϊ��ʱ��Ƶ�ʳ�
 *       �Ըô����õ�ϵͳʱ�ӷ�Ƶֵ��
 */
am_static_inline
void amhw_clock_system_clkdiv_set (uint32_t div)
{
    AMHW_SYSCON->ahbclkdiv = div;
}

/**
 * \brief �õ�ϵͳʱ�ӷ�Ƶֵ
 * \return ϵͳʱ�ӷ�Ƶֵ
 */
am_static_inline
uint32_t amhw_clock_system_clkdiv_get (void)
{
    return AMHW_SYSCON->ahbclkdiv;
}

/**
 * \brief ����ADCʱ�ӷ�Ƶֵ
 * \param[in] div : ADCʱ�ӷ�Ƶֵ
 * \return ��
 * \note ��ƵֵΪ0ʱ������ADCʱ�ӣ�������ЧֵΪ1~255.
 */
am_static_inline
void amhw_clock_adc_clkdiv_set (uint32_t div)
{
    AMHW_SYSCON->adcclkdiv = div;
}

/**
 * \brief �õ�ADCʱ�ӷ�Ƶֵ
 * \return ADCʱ�ӷ�Ƶֵ, 0����ʱ�ӱ���ֹ
 */
am_static_inline
uint32_t amhw_clock_adc_clkdiv_get (void)
{
    return AMHW_SYSCON->adcclkdiv;
}

/**
 * \brief ����ADCʱ��Դ
 * \param[in] src : ADCʱ��Դ
 * \return ��
 */
am_static_inline
void amhw_clock_adc_src_set (amhw_clock_adc_src_t src)
{
    AMHW_SYSCON->adcclksel = (uint32_t) src;
}

/**
 * \brief �õ�ADCʱ��Դ
 * \return ADCʱ��Դ
 */
am_static_inline
amhw_clock_adc_src_t amhw_clock_adc_src_get (void)
{
    return (amhw_clock_adc_src_t)(AMHW_SYSCON->adcclksel);
}

/**
 * \brief �õ�ADCʱ��Ƶ��
 * \return ADCʱ��Ƶ��
 */
uint32_t amhw_clock_adc_clkrate_get (void);

/**
 * \brief ʹ��RTC���������������
 * \return ��
 */
am_static_inline
void amhw_clock_rtcosc_enable (void)
{
    AMHW_SYSCON->rtcoscctrl = 1;
}

/**
 * \brief ����RTC���������������
 * \return ��
 */
am_static_inline
void amhw_clock_rtcosc_disable (void)
{
    AMHW_SYSCON->rtcoscctrl = 0;
}

/**
 * \brief �����첽ʱ��Դ
 * \param[in] src : �첽ʱ��Դ
 * \return ��
 */
void amhw_clock_async_src_set(amhw_clock_async_src_t src);

/**
 * \brief �õ��첽ʱ��Դ
 * \return �첽ʱ��Դ
 */
amhw_clock_async_src_t amhw_clock_async_src_get(void);

/**
 * \brief �õ��첽ʱ��Ƶ��
 * \return �첽ʱ��Ƶ��
 */
uint32_t amhw_clock_async_clkrate_get(void);

/**
 * \brief �����첽ʱ�ӷ�Ƶֵ
 * \param[in] div : �첽ʱ�ӷ�Ƶֵ
 * \return ��
 * \note ��ƵֵΪ0ʱ�������첽ʱ�ӣ�������ЧֵΪ1~255.
 */
am_static_inline
void amhw_clock_async_clkdiv_set (uint32_t div)
{
    AMHW_ASYNCSYSCON->asyncclkdiv = div;
}

/**
 * \brief �õ��첽ʱ�ӷ�Ƶֵ
 * \return �첽ʱ�ӷ�Ƶֵ
 */
am_static_inline
uint32_t amhw_clock_async_clkdiv_get (uint32_t div)
{
    return (AMHW_ASYNCSYSCON->asyncclkdiv);
}

/**
 * \brief �õ�ϵͳʱ��Ƶ��
 * \return ϵͳʱ��Ƶ��
 */
uint32_t amhw_clock_system_clkrate_get(void);

/**
 * \brief �õ����ڻ�������Ƶ�ʣ�ͨ��FRG��
 * \return ���ڻ�������Ƶ��
 */
uint32_t amhw_clock_usart_baseclkrate_get(void);

/**
 * \brief ���ô��ڻ�������Ƶ�ʣ�ͨ��FRG��
 *
 * Ϊ�˻�ȡ�߾��ȵĲ����ʣ���Ҫ����С����Ƶ����FRG�������ڵĻ�������Ƶ������Ϊ
 * ���������ʵ���������\n
 * ���ڻ�������Ƶ�ʵķ�Χ�ǣ�g_async_clkfreq / (1 + 255/256) ~ g_async_clkfreq \n
 * ���磺\n
 * g_async_clkfreq = 12MHz \n
 * ���ڻ�������Ƶ�ʵķ�Χ��Ϊ�� 6,011,741Hz ~ 12MHz \n
 * Ϊ�����ò�����Ϊ115200,�����ô��ڻ�������Ƶ��Ϊ��
 * 11,059,200Hz(11059200 = 115200 * 96).\n
 * ʵ���ϣ����ڻ�������Ƶ������Ϊ11.0592MHz�����������������ʵ����� 
 *
 * \param[in] rate : �����Ĵ��ڻ�������Ƶ������ֵ
 * \return ʵ�ʵĴ��ڻ�������Ƶ��ֵ������������ֵ����ƫ��
 */
uint32_t amhw_clock_usart_baseclkrate_set(uint32_t rate);


/**
 * \brief �õ����������Ƶ��
 * \param[in] p_periph : ָ������ļĴ�����
 * \return ���������Ƶ��
 * \note ���øú���ǰ��ȷ��ʹ�� amhw_clock_freq_update()
 *        �� amhw_clock_wdt_freq_update()������������Ӧʱ��ȫ�ֱ�����ֵ��
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

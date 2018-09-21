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
 * \brief Clock select and control implementation for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
 
#include "amhw_clock.h"
#include "amhw_pll.h"
#include "amhw_inmux.h"

uint32_t g_main_clkfreq;   /* the main clock frequency                      */ 
uint32_t g_system_clkfreq; /* system clock frequency,divIde from main clock */
uint32_t g_async_clkfreq;  /* asynchronous clock frequency                  */
uint32_t g_wdtosc_clkfreq; /* WDTOSC frequency                              */

/*******************************************************************************
  Local functions
*******************************************************************************/

/**
 * \brief Return asynchronous APB clock rate (no regard for divider)
 */
static uint32_t __clock_async_clkrate_nodiv_get (void)
{
    amhw_clock_async_src_t src;
    uint32_t             clkrate;

    src = amhw_clock_async_src_get();
    
    switch (src) {
    case AMHW_CLOCK_ASYNC_SRC_IRC:
        clkrate = amhw_clock_irc_rate_get();
        break;

    case AMHW_CLOCK_ASYNC_SRC_WDTOSC:
        clkrate = amhw_clock_wdt_rate_get();
        break;

    case AMHW_CLOCK_ASYNC_SRC_MAINCLK:
        clkrate = amhw_clock_main_clkrate_get();
        break;

    case AMHW_CLOCK_ASYNC_SRC_CLKIN:
        clkrate = amhw_clock_clkin_rate_get();
        break;

    case AMHW_CLOCK_ASYNC_SRC_PLLOUT:
        clkrate = amhw_pll_out_clkrate_get();
        break;

    default:
        clkrate = 0;
        break;
    }

    return clkrate;
}

/*******************************************************************************
  Public functions
*******************************************************************************/

/**
 * \brief Peripheral clock enable.
 */
void amhw_clock_periph_enable (amhw_clock_periph_t clk)
{
    uint32_t clk_enable = (uint32_t) clk;

    /* asynchronous peripheral */
    if (clk_enable >= 128) {
        clk_enable = clk_enable - 128;
        AMHW_ASYNCSYSCON->asyncapbclkctrlset = (1 << clk_enable);
    } else if (clk_enable >= 32) {
        AMHW_SYSCON->ahbclkctrlset1 = (1 << (clk_enable - 32));
    } else {
        AMHW_SYSCON->ahbclkctrlset0 = (1 << clk_enable);
    }
}

/**
 * \brief Peripheral clock disable.
 */
void amhw_clock_periph_disable (amhw_clock_periph_t clk)
{
    uint32_t clk_disable = (uint32_t)clk;

    /* asynchronous peripheral */
    if (clk_disable >= 128) {
        clk_disable = clk_disable - 128;
        AMHW_ASYNCSYSCON->asyncapbclkctrlclr = (1 << clk_disable);
    } else if (clk_disable >= 32) {
        AMHW_SYSCON->ahbclkctrlclr1 = (1 << (clk_disable - 32));
    } else {
        AMHW_SYSCON->ahbclkctrlclr0 = (1 << clk_disable);
    }    
}

/**
 * \brief check the peripheral clock whether enabled or not.
 */
bool_t amhw_clock_periph_check (amhw_clock_periph_t clk)
{
    uint32_t clk_check = (uint32_t)clk;

    /* asynchronous peripheral */
    if (clk_check >= 128) {
        clk_check = clk_check - 128;
        return (bool_t) (((AMHW_ASYNCSYSCON->asyncapbclkctrl) & (1 << clk_check)) != 0);
    } else if (clk_check >= 32) {
        clk_check = clk_check - 32;
        
        return (bool_t)(((AMHW_SYSCON->ahbclkctrl1) & (1 << clk_check)) != 0);
    } else {
        return (bool_t)(((AMHW_SYSCON->ahbclkctrl0) & (1 << clk_check)) != 0);
    }    
}

/**
 * \brief Return main A clock rate .
 */
uint32_t amhw_clock_main_a_clkrate_get (void)
{
    uint32_t clkrate = 0;

    switch (amhw_clock_main_a_src_get()) {
    case AMHW_CLOCK_MAIN_A_SRC_IRC:
        clkrate = AMHW_CLOCK_FREQ_IRC;
        break;

    case AMHW_CLOCK_MAIN_A_SRC_CLKIN:
        clkrate = AMHW_CLOCK_FREQ_CLKIN;
        break;

    case AMHW_CLOCK_MAIN_A_SRC_WDTOSC:
        clkrate = AMHW_CLOCK_FREQ_WDTOSC;
        break;

    default:
        clkrate = 0;
        break;
    }

    return clkrate;
}

/**
 * \brief Return main B clock rate.
 */
uint32_t amhw_clock_main_b_clkrate_get (void)
{
    uint32_t clkrate = 0;

    switch (amhw_clock_main_b_src_get()) {
    case AMHW_CLOCK_MAIN_B_SRC_MAINCLKSELA:
        clkrate = amhw_clock_main_a_clkrate_get();
        break;

    case AMHW_CLOCK_MAIN_B_SRC_PLLIN:
        clkrate = amhw_pll_in_clkrate_get();
        break;

    case AMHW_CLOCK_MAIN_B_SRC_PLLOUT:
        clkrate = amhw_pll_out_clkrate_get();
        break;

    case AMHW_CLOCK_MAIN_B_SRC_RTC:
        clkrate = AMHW_CLOCK_FREQ_RTC;
        break;
    }

    return clkrate;
}

/**
 * \brief Update g_system_clkfreq variable
 *
 * Updates the g_system_clkfreq with current core Clock 
 * retrieved from CPU registers.
 */
void amhw_clock_freq_update (void)
{
    uint32_t clkrate;
    
    if (amhw_clock_main_b_src_get() == AMHW_CLOCK_MAIN_B_SRC_MAINCLKSELA) {
        clkrate = amhw_clock_main_a_clkrate_get();
    } else {
        clkrate = amhw_clock_main_b_clkrate_get();
    }
    
    g_main_clkfreq = clkrate;
      
    /* Update the s_system_clkfreq */
    g_system_clkfreq = (clkrate / (AMHW_SYSCON->ahbclkdiv & 0xFFul));
    
    /* Update the g_async_clkfreq   */
    g_async_clkfreq = amhw_clock_async_clkrate_get();
}

/**
 * \brief Update the WDT oscillator freq.
 */
void amhw_clock_wdt_freq_update (void)
{
    
    bool_t wdtosc_ispowerup;
    bool_t inputmux_isclocked;
    
    wdtosc_ispowerup   = amhw_syscon_power_check(AMHW_SYSCON_PD_WDT_OSC);
    inputmux_isclocked = amhw_clock_periph_check(AMHW_CLOCK_INMUX);
    
    /* 
     * The WDT OSC freq is 500kHz. but It not accurate. the error can reach 40% 
     * for use the WDT OSC in accurately. use the freq measure to get the actual
     * frequency.
     */
     
    if (wdtosc_ispowerup == FALSE) {
        amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);   /* power up the WDT OSC */
    }
    
    /* Use the input multiplexing, should enable clock */ 
    if (inputmux_isclocked == FALSE) {
        amhw_clock_periph_enable(AMHW_CLOCK_INMUX);
    }

    /* Use the main clock as ref clock,the WDT OSC clock as target clock */
    
    amhw_inmux_freqmsr_refclk_set(AMHW_INMUX, AMHW_INMUX_FREQMSR_SRC_MAINCLK);
    amhw_inmux_freqmsr_targclk_set(AMHW_INMUX, AMHW_INMUX_FREQMSR_SRC_WDTOSC);
    
    /* Start freq measure */
    amhw_syscon_freqmeas_start();
    
    /* Wait for measured complete */
    while (amhw_syscon_freqmsr_complete_chk() == FALSE);
    
    /* calculate the freq by giving the main clock freq */
    g_wdtosc_clkfreq = amhw_syscon_freqmeas_targfreq_get(g_main_clkfreq);
    
    if (g_wdtosc_clkfreq == 0) {     /* measured failed          */
        g_wdtosc_clkfreq = 500;      /* giving the default value */
    }     
}

/**
 * \brief Get the main clock rate  
 */
uint32_t amhw_clock_main_clkrate_get (void)
{
    uint32_t clkrate;
    
    if (amhw_clock_main_b_src_get() == AMHW_CLOCK_MAIN_B_SRC_MAINCLKSELA) {
        clkrate = amhw_clock_main_a_clkrate_get();
    } else {
        clkrate = amhw_clock_main_b_clkrate_get();
    }    
    
    return clkrate;
}

/**
 * \brief Set main clock source The function will power up the main clock source if need.
 */
void amhw_clock_main_src_set (amhw_clock_main_src_t mainclk_src)
{
    /* IRC power default up */
    if (mainclk_src <= AMHW_CLOCK_MAIN_SRC_CLKIN) {   
        AMHW_SYSCON->mainclksela = (uint32_t)mainclk_src;
        AMHW_SYSCON->mainclkselb = (uint32_t)0;        
        
    } else if (mainclk_src == AMHW_CLOCK_MAIN_SRC_WDTOSC) {      
             
        /* Enable the power to the WDT Oscillator */
        amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);
        
        AMHW_SYSCON->mainclksela = (uint32_t)mainclk_src;
        AMHW_SYSCON->mainclkselb = (uint32_t)0;
        
    } else if (mainclk_src == AMHW_CLOCK_MAIN_SRC_RTC){      
        
        /* 
         * Turn on the RTC 32K Oscillator if it needs to be used as a source
         * for the PLL. 
         */
        amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);
        amhw_clock_rtcosc_enable();
               
        AMHW_SYSCON->mainclkselb = AMHW_CLOCK_MAIN_SRC_RTC - AMHW_CLOCK_MAIN_SRC_PLLIN + 1;        
        
    } else {
        AMHW_SYSCON->mainclkselb = mainclk_src - AMHW_CLOCK_MAIN_SRC_PLLIN + 1;  
    }
}

/**
 * \brief Returns the main clock source.
 */
amhw_clock_main_src_t amhw_clock_main_src_get (void)
{
    amhw_clock_main_b_src_t src_b;
    uint32_t clksrc;

    /* Get main B clock source */
    src_b = amhw_clock_main_b_src_get();
    if (src_b == AMHW_CLOCK_MAIN_B_SRC_MAINCLKSELA) {
        
        /* Using source A, so return source A */
        clksrc = (uint32_t)amhw_clock_main_a_src_get();
    } else {
        
        /* Using source B */
        clksrc = AMHW_CLOCK_MAIN_SRC_PLLIN - 1 + (uint32_t)src_b;
    }

    return (amhw_clock_main_src_t) clksrc;
}

/**
 * \brief Set CLKOUT clock source and divider.
 */
void amhw_clock_clkout_config (amhw_clock_clkout_src_t src, uint32_t div)
{
    uint32_t clk_src = (uint32_t)src;

    /* Use a clock A source? */
    if (src >= AMHW_CLOCK_CLKOUT_SRC_RTC) {
        
        /* Not using a CLKOUT A source */
        AMHW_SYSCON->clkoutselb = clk_src - AMHW_CLOCK_CLKOUT_SRC_RTC + 3;
    } else {
        
        /* Using a clock A source, select A and then switch B to A */
        AMHW_SYSCON->clkoutsela = clk_src;
        AMHW_SYSCON->clkoutselb = 0;
    }

    AMHW_SYSCON->clkoutdiv = div;
}

/**
 * \brief Get system clock rate
 */
uint32_t amhw_clock_system_clkrate_get (void)
{
    /* No point in checking for divide by 0 */
    return amhw_clock_main_clkrate_get() / AMHW_SYSCON->ahbclkdiv;
}

/**
 * \brief Returns the system tick rate as used with the system tick divider.
 */
uint32_t amhw_clock_systick_clkrate_get (void)
{
    uint32_t sysrate, div;

    div = AMHW_SYSCON->systickclkdiv;

    /* If divider is 0, the system tick clock is disabled */
    if (div == 0) {
        sysrate = 0;
    } else {
        sysrate = amhw_clock_system_clkrate_get() / AMHW_SYSCON->systickclkdiv;
    }

    return sysrate;
}

/**
 * \brief Return ADC clock rate.
 */
uint32_t amhw_clock_adc_clkrate_get (void)
{
    uint32_t div, clkrate = 0;

    div = amhw_clock_adc_clkdiv_get();

    /* ADC clock only enabled if div > 0 */
    if (div > 0) {
        switch (amhw_clock_adc_src_get()) {
        case AMHW_CLOCK_ADC_SRC_MAINCLK:
            clkrate = amhw_clock_main_clkrate_get();
            break;

        case AMHW_CLOCK_ADC_SRC_SYSPLLOUT:
            clkrate = amhw_pll_out_clkrate_get();
            break;

        case AMHW_CLOCK_ADC_SRC_IRC:
            clkrate = amhw_clock_irc_rate_get();
            break;
        
        default:
            break;
        }

        clkrate = clkrate / div;
    }

    return clkrate;
}


/**
 * \brief Set asynchronous APB clock source
 */
void amhw_clock_async_src_set (amhw_clock_async_src_t src)
{
    uint32_t clksrc = (uint32_t)src;

    if (src >= AMHW_CLOCK_ASYNC_SRC_MAINCLK) {
        AMHW_ASYNCSYSCON->asyncapbclkselb = (clksrc - AMHW_CLOCK_ASYNC_SRC_MAINCLK);
    } else {
        AMHW_ASYNCSYSCON->asyncapbclksela = clksrc;
        AMHW_ASYNCSYSCON->asyncapbclkselb = 3;
    }    
}

/**
 * \brief Get asynchronous APB clock source
 */
amhw_clock_async_src_t amhw_clock_async_src_get (void)
{
    uint32_t clksrc;

    if (AMHW_ASYNCSYSCON->asyncapbclkselb == 3) {
        clksrc = AMHW_ASYNCSYSCON->asyncapbclksela;
    } else {
        clksrc = AMHW_CLOCK_ASYNC_SRC_MAINCLK + AMHW_ASYNCSYSCON->asyncapbclkselb;
    }

    return (amhw_clock_async_src_t)clksrc;    
}

/**
 * \brief Return asynchronous APB clock rate
 */
uint32_t amhw_clock_async_clkrate_get (void)
{
    uint32_t clkrate, div;

    clkrate = __clock_async_clkrate_nodiv_get();
    div     = AMHW_ASYNCSYSCON->asyncclkdiv;
    
    if (div == 0) {
        
        /* Clock is disabled */
        return 0;
    }

    return clkrate / div;    
}

/**
 * \brief Get UART base rate.
 */
uint32_t amhw_clock_usart_baseclkrate_get (void)
{
    uint64_t inclk;

    /* Get clock rate into FRG */
    inclk = (uint64_t)amhw_clock_async_clkrate_get();

    if (inclk != 0) {
        uint32_t mult, divmult;
        
        divmult = AMHW_ASYNCSYSCON->frgctrl & 0xFFFF;
        if ((divmult & 0xFF) == 0xFF) {
            
            /* Fractional part is enabled, get multiplier */
            mult = (divmult >> 8) & 0xFF;

            /* Get fractional error */
            inclk = (uint64_t)(inclk * 256) / (uint64_t)(256 + mult);
        }
    }

    return (uint32_t)inclk;
}

/**
 * \brief Set UART base rate.
 */
uint32_t amhw_clock_usart_baseclkrate_set (uint32_t rate)
{
    uint32_t div, inclk, err;
    uint32_t derr, dherr;
    uint64_t frag_mul;

    /* Input clock into FRG block is the main asynchronous clock */
    inclk = amhw_clock_async_clkrate_get();

    /* Get integer divider for coarse rate */
    div = inclk / rate;
    if (div == 0) {
        div = 1;
    }

    /* Enable FRG clock */
    amhw_clock_periph_enable(AMHW_CLOCK_FRG);

    /* Desired the err of in-clock and rate */
    err = inclk - (rate * div);
    
    frag_mul = (((uint64_t) err) * 256) / (uint64_t) (rate * div);

    /* when frag_mul,the err of Desired err and Actual err */
    derr  = err - (rate * div) * frag_mul / 256;
    
    /* when frag_mul + 1,the err of Desired err and Actual err */
    dherr = (rate * div) * (frag_mul + 1) / 256 - err;

    if (dherr < derr) {
        frag_mul += 1;
    }
    
    /* Enable fractional divider and set multiplier */
    AMHW_ASYNCSYSCON->frgctrl = 0xFF | (frag_mul << 8);

    return amhw_clock_usart_baseclkrate_get();
}

/**
 * \brief Get peripheral input clock rate
 * \param[in] p_periph : Pointer to the peripheral register block
 * \retval  The peripheral input clock rate
 * \note before calling this function,Ensure that the clock rate have been updata
 *       by the function amhw_clock_freq_update() and amhw_clock_wdt_freq_update().
 *
 */
uint32_t amhw_clock_periph_freq_get (void *p_periph)
{
    uint32_t base_addr = (uint32_t)(p_periph);
    
    if ( (base_addr == AMHW_USART0_BASE) ||
         (base_addr == AMHW_USART1_BASE) ||
         (base_addr == AMHW_USART2_BASE) ||
         (base_addr == AMHW_USART3_BASE) ||
         (base_addr == AMHW_I2C0_BASE)   ||
         (base_addr == AMHW_I2C1_BASE)   ||
         (base_addr == AMHW_I2C2_BASE)   ||
         (base_addr == AMHW_SPI0_BASE)   ||
         (base_addr == AMHW_SPI1_BASE)   ||
         (base_addr == AMHW_TIMER0_BASE) ||
         (base_addr == AMHW_TIMER1_BASE) ) {

        return amhw_clock_async_clkrate_get();

    } else if (base_addr == AMHW_UTICK_BASE || base_addr == AMHW_WWDT_BASE) {
        
        return amhw_clock_wdt_rate_get();
        
    } else if (base_addr == AMHW_RTC_BASE) {
        
        return amhw_clock_rtc_rate_get();
    } else {
        
        return amhw_clock_system_clkrate_get();
    }
}

/**
 * \brief Enable a system or peripheral clock.
 */
void Chip_Clock_EnablePeriphClock (amhw_clock_periph_t clk)
{
    uint32_t clk_enable = (uint32_t)clk;

    if (clk_enable >= 128) {
        clk_enable = clk_enable - 128;
        AMHW_ASYNCSYSCON->asyncapbclkctrlset = (1 << clk_enable);
    } else if (clk_enable >= 32) {
        AMHW_SYSCON->ahbclkctrlset1 = (1 << (clk_enable - 32));
    } else {
        AMHW_SYSCON->ahbclkctrlset0 = (1 << clk_enable);
    }
}

/**
 * \brief Disable a system or peripheral clock.
 */
void Chip_Clock_DisablePeriphClock (amhw_clock_periph_t clk)
{
    uint32_t clk_disable = (uint32_t)clk;

    if (clk_disable >= 128) {
        clk_disable = clk_disable - 128;
        AMHW_ASYNCSYSCON->asyncapbclkctrlclr = (1 << clk_disable);
    } else if (clk_disable >= 32) {
        AMHW_SYSCON->ahbclkctrlclr1 = (1 << (clk_disable - 32));
    } else {
        AMHW_SYSCON->ahbclkctrlclr0 = (1 << clk_disable);
    }
}

/* end of file */

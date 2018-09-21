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
 * \brief 频率测量演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. 串口输出WDT和RTC时钟源频率
 *
 * \par 源代码
 * \snippet demo_hw_freqmeasure.c src_hw_freqmeasure
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_hw_freqmeasure
 * \copydoc demo_hw_freqmeasure.c
 */
 
/** [src_hw_freqmeasure] */
#include "ametal.h"
#include "am_board.h"



/**
 * \brief 频率测量函数
 *
 * \param[in] ref_clksrc  : 参考时钟源The reference clock source for freq measure 
 * \param[in] targ_clksrc : 目标时钟源The target clock source for freq measure 
 * \param[in] ref_clkfreq : 参考时钟频率The reference clock frequency
 *
 * \return  目标时钟源的频率
 *
 * \note 参考频率要求大于目标频率
 */
uint32_t freq_measure(amhw_inmux_freqmsr_src_t  ref_clksrc, 
                      amhw_inmux_freqmsr_src_t  targ_clksrc, 
                      uint32_t                  ref_clkfreq)
{
    

    amhw_inmux_freqmsr_refclk_set(AMHW_INMUX, ref_clksrc);
    amhw_inmux_freqmsr_targclk_set(AMHW_INMUX, targ_clksrc); 
    
    /* 启动频率测量 */
    amhw_syscon_freqmeas_start();
    
    /* 等待测量完成 */
    while (amhw_syscon_freqmsr_complete_chk() == FALSE);
    
    return amhw_syscon_freqmeas_targfreq_get(ref_clkfreq);
    
}

/** 
 * \brief 平台初始化
 *
 * 使能并复位外设外设时钟，以及其他相关的平台初始化
 *
 * \return  None
 */
void amhw_plfm_init (void)
{
    /* 使能并复位外设外设时钟 */
    amhw_clock_periph_enable(AMHW_CLOCK_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
    
    amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);   /* 打开WDT时钟 */
    amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);   /* 打开WDT时钟 */
}

/**
 * \brief 主函数
 */
int main (void)
{
    uint32_t wdtosc_freq;
    uint32_t rtcosc_freq;
    
    /* 板级初始化 */
    am_board_init();
    
    AM_DBG_INFO("The demo for frequency measure\r\n");
    
    /* 平台相关初始化 */
    amhw_plfm_init();
    
    /* 主时钟作为参考时钟，WDT时钟作为目标时钟 */
    wdtosc_freq = freq_measure(AMHW_INMUX_FREQMSR_SRC_MAINCLK, 
                               AMHW_INMUX_FREQMSR_SRC_WDTOSC, 
                               g_main_clkfreq);
    

    AM_DBG_INFO("The watch dog OSC clock rate is %d Hz\r\n", wdtosc_freq);
 
    /* IRC时钟作为参考时钟，RTC作为目标时钟 */
    rtcosc_freq = freq_measure(AMHW_INMUX_FREQMSR_SRC_IRC, 
                               AMHW_INMUX_FREQMSR_SRC_32KHZOSC, 
                               amhw_clock_irc_rate_get());
  
    AM_DBG_INFO("The RTC OSC clock rate is %d Hz\r\n", rtcosc_freq); 
 
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_hw_freqmeasure] */

/* end of file */



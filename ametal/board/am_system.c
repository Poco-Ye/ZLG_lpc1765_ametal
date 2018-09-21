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
 * \brief 系统初始化设置
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
 
#include "am_system.h"
#include "am_prj_config.h"

extern uint32_t gc_vectors[];    /* 在 am_startup_armcc_lpc5410x.s 文件中定义 */

/**
 * \brief 该函数在复位后调用，在复位函数调用。
 *
 * 复位函数在 am_startup_armcc_lpc5410x.s 文件中定义
 *
 */
void SystemInit (void) 
{

/* 在M4核上，存在FPU，使用前，操作CPACR寄存器使能FPU */
#if (__FPU_PRESENT == 1)
    SCB->CPACR |= ((3UL << 10*2) |                 /* 设置 CP10 完全访问    */
                   (3UL << 11*2));                 /* 设置 CP11 完全访问    */
#endif

    /* 设置中断向量表地址*/
    SCB->VTOR = ((uint32_t)(&gc_vectors[0])) & SCB_VTOR_TBLOFF_Msk;
}

#ifdef AM_CORTEX_M4

/** 
 * \brief 系统初始化函数
 *
 * 使用PLL得到更高的时钟频率 
 */
void am_system_init (void)
{
    amhw_pll_stat_t stat;
    
    /* IRC振荡器和IRC单元上电 */
    amhw_syscon_powerup(AMHW_SYSCON_PD_IRC_OSC | AMHW_SYSCON_PD_IRC);
    
    if (AM_CFG_MAIN_CLK_SRC  == AMHW_CLOCK_MAIN_SRC_PLLOUT ||
        AM_CFG_ASYNC_CLK_SRC == AMHW_CLOCK_ASYNC_SRC_PLLOUT) {
            
        /* 在配置PLL之前，切换主时钟源为IRC */
        amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);

#if (AM_CFG_PLL_USEPRECISE == 0)
            
        stat = amhw_pll_config(AM_CFG_PLL_CLK_SRC, 
                               AM_CFG_PLLOUT_FREQ, 
                               FALSE);
#else 
        stat = amhw_pll_config(AM_CFG_PLL_CLK_SRC, 
                               AM_CFG_PLLOUT_FREQ, 
                               TRUE);
#endif
    }

    amhw_clock_system_clkdiv_set(AM_CFG_SYSTEM_CLK_DIV);
    
    if (AM_CFG_MAIN_CLK_SRC  == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
        
        if (stat == AMHW_PLL_SUCCESS) {
        
            /* 设置主时钟源为PLL输出 */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);
        } else {
        
            /* PLL配置失败, 设置主时钟源为IRC */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);
        }
        
    } else {
         amhw_clock_main_src_set(AM_CFG_MAIN_CLK_SRC);
    }
    
    /* 使能异步系统 */
    amhw_syscon_async_enable();
    
    /* 设置异步时钟分频值 */
    amhw_clock_async_clkdiv_set(AM_CFG_ASYNC_CLK_DIV);    
    
    if (AM_CFG_ASYNC_CLK_SRC == AMHW_CLOCK_ASYNC_SRC_PLLOUT) {
        if (stat == AMHW_PLL_SUCCESS) {
        
            /* 设置异步时钟源为PLL输出 */
            amhw_clock_async_src_set(AMHW_CLOCK_ASYNC_SRC_PLLOUT);
        } else {
        
            /* PLL配置失败, 设置异步时钟源为IRC */
            amhw_clock_async_src_set(AMHW_CLOCK_ASYNC_SRC_IRC);
        }
    } else {
        amhw_clock_async_src_set(AM_CFG_ASYNC_CLK_SRC);
    }

    /* 
     * 更新时钟频率值
     * 包含： g_main_clkfreq, g_system_clkfreq 和 g_async_clkfreq
     */
    amhw_clock_freq_update();  

    /* 更新表示WDT振荡器的输出频率全局变量g_wdtosc_clkfreq的值 */
    amhw_clock_wdt_freq_update();
}

#else 

void am_system_init (void)
{    
    /* 
     * 更新时钟频率值
     * 包含： g_main_clkfreq, g_system_clkfreq 和 g_async_clkfreq
     */
    amhw_clock_freq_update();  

    /* 更新表示WDT振荡器的输出频率全局变量g_wdtosc_clkfreq的值 */
    amhw_clock_wdt_freq_update();
}

#endif /* AM_CORTEX_M4 */

/* end of file */

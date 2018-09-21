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
 * \brief 唤醒演示例程，从睡眠模式中唤醒系统，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. LED0以1s时间间隔闪烁。
 *
 * \par 源代码
 * \snippet demo_hw_wakeup.c src_hw_wakeup 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_wakeup
 * \copydoc demo_hw_wakeup.c
 */
/** [src_hw_wakeup] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief  MRT 中断处理函数
 * \param[in] p_arg : 中断入口参数 
 * \return  None
 */
void mrt_irq_handler (void *p_arg)
{
    amhw_mrt_int_pending_clr(AMHW_MRT, AMHW_MRT_CH(0));
}

/**
 * \brief 主函数
 */
int main (void)
{
    amhw_clock_main_src_t saved_clksrc;  /* 定义该变量，为了保存时钟 */

    /* 板级初始化 */
    am_board_init();

    /* MRT 平台初始化 */
    amhw_plfm_mrt_init();
 
    /* 输出ROM版本号 */
    AM_DBG_INFO("ROM version = %04x\r\n", amhw_power_rom_ver_get());

    /* 切换主时钟位IRC，且关闭PLL电源 */
    saved_clksrc = amhw_clock_main_src_get();
    if (saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
        
        /* 设置PLL输出作为主时钟 */
        amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);  
        amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);
        
        amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_clock_main_clkrate_get());
    }

    /*
     * 在一次计时中断模式下操作通道0，1s后中断
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(0), AMHW_MRT_MODE_ONESHOT);
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(0), amhw_clock_irc_rate_get(), TRUE);
    amhw_mrt_int_enable(AMHW_MRT, AMHW_MRT_CH(0)); 

    am_int_connect(INUM_MRT, mrt_irq_handler, (void *)0);
    am_int_enable(INUM_MRT);

    /* 使能MRT唤醒 */
    amhw_syscon_wakeup_enable(AMHW_SYSCON_STARTER_MRT);

    AM_DBG_INFO("enter power down mode !");

    while (1) {
    
       /* 
        * 进入睡眠模式
        */
        amhw_power_mode_enter(AMHW_POWER_MODE_SLEEP, 0);
        
        /* 等待被唤醒 */
        AM_DBG_INFO("wake up !\r\n");
        
        /* 切换（改变）时钟源位PLL输出 */
        if (saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            
            /* 打开PLL电源 */
            amhw_syscon_powerup(AMHW_SYSCON_PD_SYS_PLL);
            
            /* 等待PLL 时钟 */
            while (amhw_pll_locked_chk() == FALSE) {}
                
            amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_pll_out_clkrate_get());
                
            /* 设置PLL输出位主时钟 */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);
                
            /* 
             * 更新时钟频率
             * 包含 g_main_clkfreq, g_system_clkfreq 和 g_async_clkfreq
             */
            amhw_clock_freq_update();  
                
            AM_DBG_INFO("The main clock freq is %d Hz\r\n", g_main_clkfreq);
        }
        
        // 主任务
        
        /* 主任务完成，关闭PLL电源 */
        if (saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            
            /* 设置IRC为主时钟  */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);  
            amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);
            
            amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_clock_main_clkrate_get());
        }

        amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(0), amhw_clock_main_clkrate_get(), TRUE);
        am_led_toggle(LED0);
    }
}

/** [src_hw_wakeup] */

/* end of file */

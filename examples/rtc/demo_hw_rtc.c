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
 * \brief RTC演示例程，通过HW层的接口实现
 *
 * 该例程演示如何创建RTC、使用RTC、并且通过RTC警报功能从睡眠、深度睡眠、掉电模式唤醒芯片。
 *
 * - 实验现象:
 *  1. 芯片进入睡眠模式，RTC唤醒定时器以不定的时间间隔唤醒芯片，接着芯片
 *     又进入了一个更长的睡眠，4秒之后，RTC警报唤醒芯片。\n
 *     调试串口重复输出下列消息：
 * \code
 *    Tick number: 0,  1KHZ int:0, alarm int:1
 *    Tick number: 1,  1KHZ int:1, alarm int:0
 *    Tick number: 2,  1KHZ int:1, alarm int:0
 *    Tick number: 3,  1KHZ int:1, alarm int:0
 *    Tick number: 4,  1KHZ int:1, alarm int:0
 *    Tick number: 5,  1KHZ int:1, alarm int:0
 *    Tick number: 6,  1KHZ int:1, alarm int:0
 *    Tick number: 7,  1KHZ int:1, alarm int:0
 *    Tick number: 8,  1KHZ int:1, alarm int:0
 *    Tick number: 9,  1KHZ int:1, alarm int:0
 *    Tick number: 10, 1KHZ int:1, alarm int:0
 *    Setting alarm to wake up in 4s
 * \endcode
 *
 * \par 源代码
 * \snippet demo_hw_rtc.c src_hw_rtc 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_rtc
 * \copydoc demo_hw_rtc.c
 */
 
/** [src_hw_rtc] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief 电源模式可能下列3种之一:
 *         - 睡眠模式
 *         - 深度睡眠模式
 *         - 掉电模式
 */
#define POWER_MODE    AMHW_POWER_MODE_POWER_DOWN

static  amhw_clock_main_src_t   g_saved_clksrc;   /**< \brief 时钟源变量定义，用于保存时钟 */

static volatile bool_t g_rtc_wake;  /**< \brief RTC 1 kHz 定时器唤醒标志 */
static volatile bool_t g_rtc_alarm; /**< \brief RTC 1 Hz 定时器警报标志  */

/** 
 * \brief RTC 中断处理函数
 * \param[in] p_arg : 中断入口函数
 * \return  无
 */
void rtc_irq_handler (void *p_arg)
{
    uint32_t rtc_status;

    am_led_toggle(0);

    /* 获取RTC状态 */
    rtc_status = amhw_rtc_stat_get(AMHW_RTC);

    /* 检测是否1KHz 定时器匹配中断 */
    if (rtc_status & AMHW_RTC_CTRL_WAKE1KHZ) {
        g_rtc_wake  = TRUE;
    }

    /* 检测是否1Hz 定时器警报中断 */
    if (rtc_status & AMHW_RTC_CTRL_ALARM1HZ) {
        g_rtc_alarm = TRUE;
    }

    /* 清除中断状态位 */
    amhw_rtc_stat_clr(AMHW_RTC, 
                     (rtc_status & (AMHW_RTC_CTRL_WAKE1KHZ | AMHW_RTC_CTRL_ALARM1HZ)));
}

/**
 * \brief 主函数
 */
int main(void)
{
    int state_counter = 0;

    /* 板级初始化 */
    am_board_init();
    
    /* RTC平台初始化 */
    amhw_plfm_rtc_init();
    
    /* 使能RTC唤醒 */
    amhw_syscon_wakeup_enable(AMHW_SYSCON_STARTER_RTC);

    /* RTC复位 */
    amhw_rtc_reset(AMHW_RTC);

    /* 
     * 在RTC禁能时，设定RTC计数器参数 
     */
    amhw_rtc_disable(AMHW_RTC);
    amhw_rtc_count_set(AMHW_RTC, 0);

    /* 设定较长警报时间，防止中断触发 */
    amhw_rtc_alarm_set(AMHW_RTC, 1000);

    /* 使能RTC */
    amhw_rtc_enable(AMHW_RTC);
    amhw_rtc_enable_1kHz(AMHW_RTC);
    
    /* 清除RTC状态位 */
    amhw_rtc_stat_clr(AMHW_RTC, (AMHW_RTC_CTRL_OFD      |
                                 AMHW_RTC_CTRL_ALARM1HZ | 
                                 AMHW_RTC_CTRL_WAKE1KHZ));

    /* 使能RTC中断 */
    am_int_connect(INUM_RTC, rtc_irq_handler, (void *)0);
    am_int_enable(INUM_RTC);

    /* 保存当前工作的时钟源 */
    g_saved_clksrc = amhw_clock_main_src_get();

    /* 使能RTC唤醒中断 */
    amhw_rtc_enable_wakeup(AMHW_RTC, (AMHW_RTC_CTRL_ALARMDPD_EN | 
                                      AMHW_RTC_CTRL_WAKEDPD_EN));

    while (1) {
        
        AM_DBG_INFO("Tick number: %d, 1KHZ int:%d, alarm int:%d\r\n",
                    state_counter, g_rtc_wake, g_rtc_alarm);
        
        g_rtc_wake = g_rtc_alarm = FALSE;

        /* 唤醒时间间隔一次比一次长100ms,基值300ms */
        if (state_counter < 10) {
            
            /* 唤醒时间间隔300ms、400ms、500ms等 */
            amhw_rtc_setwake(AMHW_RTC, (300 + (state_counter * 100)));
            state_counter++;
        } else {
            AM_DBG_INFO("Setting alarm to wake up in 4s\r\n");
           
           /* 警报唤醒时间设定为4秒 */
            amhw_rtc_alarm_set(AMHW_RTC, amhw_rtc_count_get(AMHW_RTC) + 4);
            state_counter = 0;
        }
       
        /* 
         * 进入睡眠或者掉电模式，需确保串口数据传输完成 
         */
        while ((amhw_usart_stat_get(AM_CFG_DEBUG_USART) & AMHW_USART_STAT_TXIDLE) == 0);
        
        /* 在进入睡眠模式前，禁能PLL */
        if (g_saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);
            amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);
        }

        amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_clock_main_clkrate_get());

        /* 
         * 进入睡眠模式，使用32K时钟源
         */
        amhw_power_mode_enter(POWER_MODE, (AMHW_POWER_PD_SRAM0A  |
                                           AMHW_POWER_PD_SRAM0B  |
                                           AMHW_POWER_PD_32K_OSC));

        if (g_saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            amhw_syscon_powerup(AMHW_SYSCON_PD_SYS_PLL);

            /* 等待PLL锁定 */
            while (!amhw_pll_locked_chk()) {}
                
            amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_pll_out_clkrate_get());

            /* 使用PLL作为主时钟 */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);
        }
    }
}

/** [src_hw_rtc] */

/* end of file */

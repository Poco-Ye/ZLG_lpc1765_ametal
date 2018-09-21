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
 * \brief RTC演示例程，将系统从深度掉电模式唤醒，通过HW层的接口实现
 *
 * 该例程演示如何创建RTC、使用RTC、并且通过RTC警报功能从深度掉电模式唤醒芯片；
 *
 * - 实验现象:
 *  1. 调试串口重复输出下列消息： \n
 *     Reset \n
 *     led toggle \n
 *     Setting alarm to wake up in 1000ms \n
 *
 * \par 源代码
 * \snippet demo_hw_rtc_deep_powerdown.c src_hw_rtc_deep_powerdown 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_rtc_deep_powerdown
 * \copydoc demo_hw_rtc_deep_powerdown.c
 */

/** [src_hw_rtc_deep_powerdown] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief RTC中断处理函数
 *
 *  一旦唤醒，将执行中断函数
 *
 * \param[in] p_arg : 中断入口参数
 * \return  无 
 */
void rtc_irq_handler (void *p_arg)
{
    uint32_t rtc_status;

    am_led_toggle(0);

    AM_DBG_INFO("led toggle\r\n");
    
    /* 获取RTC状态 */
    rtc_status = amhw_rtc_stat_get(AMHW_RTC);

    /* 清除RTC状态 */
    amhw_rtc_stat_clr(AMHW_RTC, (rtc_status & (AMHW_RTC_CTRL_WAKE1KHZ | 
                                               AMHW_RTC_CTRL_ALARM1HZ)));
}

/**
 * \brief 主函数
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();
    
    /*  RTC平台初始化 */
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
 
    /*
     * RTC中断挂起位置位，当系统从深度掉电模式唤醒后，执行RTC中断函数；
     * 若无需执行RTC中断处理函数，清除中断挂起位即可。 
     */
//    amhw_int_clr_pending(INUM_RTC);

    /* 连接并使能RTC中断 */
    am_int_connect(INUM_RTC, rtc_irq_handler, (void *)0);
    am_int_enable(INUM_RTC);

    /* 使能RTC唤醒中断 */
    amhw_rtc_enable_wakeup(AMHW_RTC, (AMHW_RTC_CTRL_ALARMDPD_EN | 
                                      AMHW_RTC_CTRL_WAKEDPD_EN));

    AM_DBG_INFO("Reset\r\n");

    /* can do some other things */
    am_mdelay(2000);

    while(1) {
        /*
         * 设定唤醒时间1500ms,最大值65535msWakeup
         */
        amhw_rtc_setwake(AMHW_RTC, 1500);
        AM_DBG_INFO("Setting alarm to wake up in 1000ms\r\n");
        
        /*
         * 若唤醒时间超过最大值，例如10s
         */
    //      amh_rtc_alarm_set(AMHW_RTC, amhw_rtc_count_get(AMHW_RTC) + 10);  
    //      AM_DBG_INFO("Setting alarm to wake up in 10s\r\n");
        /* 
         * 进入睡眠或者掉电模式，需确保串口数据传输完成 
         */
        while ((amhw_usart_stat_get(AM_CFG_DEBUG_USART) & AMHW_USART_STAT_TXIDLE) == 0);
        
        /* 进入掉电模式，当唤醒时，芯片重启*/
        amhw_power_mode_enter(AMHW_POWER_MODE_DEEP_POWER_DOWN, AMHW_SYSCON_PD_32K_OSC);
    }
}

/** [src_hw_rtc_deep_powerdown] */

/* end of file */

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
 * \brief WWDT看门狗演示例程，通过HW层的接口实现
 * 
 * - 实验现象:
 *   1. 在超时前5次报警中断发生，执行喂狗程序；
 *   2. 然后2秒后发生超时, LED0点亮，并且串口输出"Watchdog reset occurred"。
 *
 * \par 源代码
 * \snippet demo_hw_wwdt.c src_hw_wwdt 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  fft, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_wwdt
 * \copydoc demo_hw_wwdt.c
 */

/** [src_hw_wwdt] */
#include "ametal.h"
#include "am_board.h"
 
static volatile uint8_t wdt_update_count;

/** 
 * \brief 看门狗定时器，中断处理函数
 * \param[in] p_arg : 入口参数
 * \return  无
 */
void wdt_irq_handler (void *p_arg)
{
    uint32_t wdt_status = amhw_wwdt_status_get(AMHW_WWDT);
    
    /* 看门狗定时器出现超时状态 */
    if (wdt_status & AMHW_WWDT_WDMOD_WDTOF) {

        amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDTOF);
    }

    /*  */
    if (wdt_status & AMHW_WWDT_WDMOD_WDINT) {

        amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDINT);
        
        if (wdt_update_count < 5) {      /* 在超时前5次报警中断发生，
                                            执行喂狗程序，然后允许看门狗复位 */
            amhw_wwdt_feed(AMHW_WWDT);
            wdt_update_count++;
            AM_DBG_INFO("The %d times feed\r\n", wdt_update_count);
        }
    }
}

/**
 * \brief 主函数
 */
int main (void)
{
    uint32_t wdt_freq;

    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_wwdt_init();

    AM_DBG_INFO("The wdt osc freq is %d\r\n", g_wdtosc_clkfreq);
    
    /* 看门狗定时器频率为输入时钟频率4分频 */
    wdt_freq = g_wdtosc_clkfreq / 4;
    
    /* 检测看门狗是否复位 */
    if (amhw_wwdt_status_get(AMHW_WWDT) & AMHW_WWDT_WDMOD_WDTOF) {
        am_led_set(0, TRUE);
        AM_DBG_INFO("Watchdog reset occurred\r\n");
        amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDTOF);
    }

    /* WWDT初始化 */
    amhw_wwdt_init(AMHW_WWDT);

    /* 
     * 设置为够时间持续大约2s
     * 设置看门狗报警时间为512 ticks
     * 设置看门狗窗口定时器时间为1s
     */
    amhw_wwdt_timeout_set(AMHW_WWDT, wdt_freq * 2);
    amhw_wwdt_warning_set(AMHW_WWDT, 1023);
    
    /* 
     * 当WWDT计数值大于窗口值，不允许进行喂狗操作
     */
    amhw_wwdt_window_set(AMHW_WWDT, wdt_freq * 1);

    /* 配置在超时后复位 */
    amhw_wwdt_option_set(AMHW_WWDT, AMHW_WWDT_WDMOD_WDRESET);

    /* 清除报警和超时中断 */
    amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDTOF | AMHW_WWDT_WDMOD_WDINT);

    am_int_connect(INUM_WWDT, wdt_irq_handler, (void *)0);
    am_int_enable(INUM_WWDT);

    /* 启动看门狗定时器 */
    amhw_wwdt_start(AMHW_WWDT);

    while (1) {
        __WFI();
    }
}

/** [src_hw_wwdt] */

/* end of file */

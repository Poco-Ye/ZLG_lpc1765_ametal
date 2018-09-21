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
 * \brief utick演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. LED0闪烁频率10Hz；
 *   2. 串口输出WDT时钟源频率。
 *
 * \par 源代码
 * \snippet demo_hw_utick.c src_hw_utick 
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_hw_utick
 * \copydoc demo_hw_utick.c
 */
 
/** [src_hw_utick] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief UTICK 中断处理函数
 * \param[in]  p_arg  : 中断入口参数
 * \return 无 
 */
void utick_irq_handler (void *p_arg)
{
    if (amhw_utick_int_flag_check(AMHW_UTICK) == TRUE) {
        
        am_led_toggle(LED0);
        amhw_utick_int_flag_clr(AMHW_UTICK);
    }
}

/**
 * \brief  主函数
 */
int main (void)
{   
    uint32_t ticks;
    
    /* 
     * 板级初始化
     */
    am_board_init();

    AM_DBG_INFO("The demo for UTICK\r\n");
    
    /* utick平台初始化 */
    amhw_plfm_utick_init();
 
    /* 
     * 延时 100ms 
     * 最大值是0x7FFFFFFF，延时 0x80000000 个滴答时钟。
     * 若g_wdtosc_clkfreq = 500kHz, 最大延时时间 :
     *    0x80000000 / 500000 = 4294s
     * 
     * 最小值是 1，延时 个滴答时钟， 
     * 若 g_wdtosc_clkfreq = 500kHz, 最小延时时间 :
     *    2 / 500000 = 4us
     */
    ticks = 100 * g_wdtosc_clkfreq / 1000;
         
    /* 设置tick, FALSE表明该延时只能执行一次 */
    amhw_utick_tick_set(AMHW_UTICK, ticks, FALSE);
     
    /* 等待延时完成 */
    while(amhw_utick_int_flag_check(AMHW_UTICK) == FALSE);
      
    amhw_utick_int_flag_clr(AMHW_UTICK);
    
    /* 设置tick, TRUE表明该延时重复执行 */
    amhw_utick_tick_set(AMHW_UTICK, ticks, TRUE);    
    
    am_int_connect(INUM_UTICK, utick_irq_handler, (void *)0);     
    
    /* 使能UTICK中断 */
    am_int_enable(INUM_UTICK);     

    AM_DBG_INFO("The WDT OSC freq is %d Hz \r\n", g_wdtosc_clkfreq);
 
    while (1) {
        __WFI();
    }
}

/** [src_hw_utick] */

/* end of file */

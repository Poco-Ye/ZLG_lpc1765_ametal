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
 * \brief 定时器演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. LED闪烁频率10Hz。
 *
 * \par 源代码
 * \snippet demo_hw_timer_timing.c src_hw_timer_timing 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_timer_timing
 * \copydoc demo_hw_timer_timing.c
 */ 
 
/** [src_hw_timer_timing] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief  定时器0中断处理函数
 * \param[in] p_arg : 中断入口参数
 * \return  无
 */
void timer0_irq_handler (void *p_arg)
{
    /* 是否匹配通道0 中断 */
    if (amhw_timer_mat_pending_get(AMHW_TIMER0, 0) == TRUE) {  
        am_led_toggle(LED0);

        /* 清除中断标志 */
        amhw_timer_mat_pending_clr(AMHW_TIMER0, 0);           
    }
}

/**
 * \brief 初始化定时器0，中断频率为freq_hz参数
 *
 * \param[in] p_hw_timer : 指向定时器寄存器块的指针
 * \param[in] chan       : 匹配通道号，可设置范围0 ~ 3
 * \param[in] freq_hz    : 中断频率参数，单位Hz
 *
 * \return  无
 */
void timer_init (amhw_timer_t *p_hw_timer, uint32_t chan, uint32_t freq_hz)
{
    uint32_t clkfreq;
        
    /* 复位定时器计数值和预分频计数值为0 */
    amhw_timer_reset(p_hw_timer);
    
    /* 设置定时器预分频为0 */
    amhw_timer_prescale_set(p_hw_timer, 0);
    
     /* 清除匹配中断 */
    amhw_timer_mat_pending_clr(p_hw_timer, chan);
    
    /* 使能匹配事件复位定时计数值 */
    amhw_timer_mat_reset_enable(p_hw_timer, chan);
    
    /* 使能匹配中断 */
    amhw_timer_mat_int_enable(p_hw_timer, chan);          
    
    clkfreq = amhw_clock_periph_freq_get(p_hw_timer);

    amhw_timer_mat_val_set(p_hw_timer, chan, clkfreq / freq_hz);
}

 

/**
 * \brief 主函数
 */
int main (void)
{
    /* 班级初始化 */
    am_board_init();

    AM_DBG_INFO("The demo for simple timing function\r\n");
    
    /* 平台相关初始化 */
    amhw_plfm_timer0_timing_init();

    /* 初始化定时器0，中断频率为10Hz */
    timer_init(AMHW_TIMER0, 0, 10); 
    
    am_int_connect(INUM_TIMER0, timer0_irq_handler, (void *)0);

    /* 使能定时器0中断 */
    am_int_enable(INUM_TIMER0);
    
    /* 启动定时器，开始计数 */
    amhw_timer_enable(AMHW_TIMER0);
    
    while (1) {
         __WFI();
    }
}

/** [src_hw_timer_timing] */

/* end of file */

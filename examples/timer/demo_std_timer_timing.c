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
 * \brief 定时器演示例程，通过标准接口实现
 *
 * - 实验现象:
 *   1. LED闪烁频率10Hz.
 *
 * \par 源代码
 * \snippet demo_std_timer_timing.c src_std_timer_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_std_timer_timing
 * \copydoc demo_std_timer_timing.c
 */
 
/** [src_std_timer_timing] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief  定时器0回调函数
 * \param[in] p_arg : 回调函数入口参数
 * \return  无
 */
void timer0_callback (void *p_arg)
{
    am_led_toggle(LED0);
}

/**
 * \brief 主函数
 */
int main (void)
{
    am_timer_handle_t  timer0_handle;
    am_timer_info_t    timer0_info;
    
    /* 板级初始化 */
    am_board_init();
    
    /* 平台相关初始化 */
    amhw_plfm_timer0_timing_init();
    
    AM_DBG_INFO("The Timer demo for standard timing service\r\n");
    
    /* 初始化定时器0为定时功能 */
    timer0_handle = amdr_timer_timing_init(&g_timer0_timing_dev, 
                                           &g_timer0_timing_devinfo); 

    am_timer_connect(timer0_handle);
    
    am_timer_info_get(timer0_handle, &timer0_info);
    
    /* STD定时器只支持一个通道，故通道号一直为0 */
    am_timer_callback_set(timer0_handle, 0, timer0_callback, NULL);
    
    while (1) {
        /* 使能定时器中断频率10Hz */
        am_timer_enable(timer0_handle, 0, timer0_info.clk_frequency / 10);
        am_mdelay(3000);
        am_timer_disable(timer0_handle, 0);
        am_mdelay(3000);
    }
}

/** [src_std_timer_timing] */

/* end of file */

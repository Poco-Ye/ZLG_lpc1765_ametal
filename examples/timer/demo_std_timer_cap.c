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
 * \brief 标准定时器用于捕获功能，通过标准接口实现
 *
 * - 实现现象:
 *   1. 串口输出捕获得到的PWM频率
 *
 * - 备注:
 *   1. 定时器0作为PWM功能输出，引脚PIO0_29；
 *   2. 定时器1作为捕获工作，引脚PIO1_5；
 *   3. 将PIO0_29和PIO1_5连接起来，用于捕获PWM频率。
 *
 * \par 源代码
 * \snippet demo_std_timer_cap.c src_std_timer_cap 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_std_timer_cap
 * \copydoc demo_std_timer_cap.c
 */

/** [src_std_timer_cap] */
#include "ametal.h"
#include "am_board.h"

bool_t   g_flag    = FALSE;   /**< \brief 捕获标志，当捕获到数据是置位 */
uint32_t g_time_ns = 0;       /**< \brief 捕获的数据 */

/** 
 * \brief 捕获回调函数
 *
 * \param[in] p_arg   : 入口参数
 * \param[in] cap_val : 捕获的数值
 *
 * \return    无
 */
void cap_callback (void *p_arg, uint32_t cap_val)
{
    static uint32_t count1;
    static bool_t   first      = TRUE;
    am_cap_handle_t cap_handle = (am_cap_handle_t)p_arg;
    
    if (first == TRUE) {
        first = FALSE;
   
   } else {
        am_cap_count_to_time(cap_handle, 0, count1, cap_val, &g_time_ns);
        
        /* 置位捕获标志，表明捕获到数据 */
        g_flag = TRUE;
    }

    count1 = cap_val;
}

/**
 * \brief 主函数
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    am_cap_handle_t  timer1_cap_handle;
    uint32_t         freq;

    /* 班级初始化 */
    am_board_init();

    /* 平台相关初始化 */
    amhw_plfm_timer0_pwm_init();
    amhw_plfm_timer1_cap_init();
    
    AM_DBG_INFO("The Timer demo for standard CAP service\r\n");
    
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer0_pwm_dev, 
                                            &g_timer0_pwm_devinfo);
    
    timer1_cap_handle = amdr_timer_cap_init(&g_timer1_cap_dev, 
                                            &g_timer1_cap_devinfo);
    
    /* PWM通道1，对应的引脚是PIO0_29，该配置在amdr_hwconfig_timer_cap.c完成 */
    am_pwm_config(timer0_pwm_handle, 1, 250000, 500000); /* 频率位2KHz */
    am_pwm_enable(timer0_pwm_handle, 1);
    
    /* 捕获功能通道0，对应的引脚是PIO1_5，该配置在amdr_hwconfig_timer_cap.c完成 */
    am_cap_config(timer1_cap_handle, 
                  0, 
                  AM_CAP_TRIGGER_RISE, 
                  cap_callback, 
                  timer1_cap_handle);
                   
    am_cap_enable(timer1_cap_handle, 0);
    
    while (1) {
        if (g_flag == TRUE) {
            
            freq = 1000000000 / g_time_ns;
            AM_DBG_INFO("freq = %d Hz\r\n", freq);
            g_flag = FALSE;   
        }
        
        am_mdelay(200);
    }
}
 
/** [src_std_timer_cap] */

/* end of file */

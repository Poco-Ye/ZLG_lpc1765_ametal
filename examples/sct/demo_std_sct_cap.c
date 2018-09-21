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
 * \brief SCT实现捕获功能，通过标准接口实现
 *
 * - 实验现象：
 *   1. 输出利用捕获功能得到的PWM信号的周期和频率。
 *
 * - 注意：
 *   1. 定时器0通过PIO0_29引脚输出PWM；
 *   2. SCT捕获输入通道2使用PIO0_25引脚；
 *   3. 关联PIO0_29引脚和PIO0_25引脚，使用捕获测量PWM频率。
 *
 * \par 源代码
 * \snippet demo_std_sct_cap.c src_std_sct_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-14  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_std_sct_cap
 * \copydoc demo_std_sct_cap.c
 */
 
/** [src_std_sct_cap] */
#include "ametal.h"
#include "am_board.h"

volatile bool_t   g_flag    = FALSE;   /**< \brief 捕获标志   */
volatile uint32_t g_time_ns = 0;       /**< \brief 捕获计数值 */

void cap_callback (void *p_arg, uint32_t cap_val)
{
    static uint32_t count1;
    static bool_t   first      = TRUE;
    am_cap_handle_t cap_handle = (am_cap_handle_t)p_arg;
    
    if (g_flag == FALSE) {
    
        if (first == TRUE) {
            count1 = cap_val;
            first  = FALSE;
        } else {
            am_cap_count_to_time(cap_handle, 0, count1, cap_val, (uint32_t *)&g_time_ns);
            first = TRUE;
            
            /* 置标志为真，表明捕获完成 */
            g_flag = TRUE;
        }
    }
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    am_cap_handle_t  sct0_cap_handle;
    uint32_t         freq;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_timer0_pwm_init();

    amhw_plfm_sct0_cap_init();
    
    AM_DBG_INFO("The SCT demo for standard CAP service\r\n");
    
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer0_pwm_dev, 
                                            &g_timer0_pwm_devinfo);
    
    sct0_cap_handle   = amdr_sct_cap_init(&g_sct0_cap_dev, 
                                          &g_sct0_cap_devinfo);

    /* 通道1使用PIO0_29，在 amhw_timer_cap_config.c 中配置 */
    am_pwm_config(timer0_pwm_handle, 1, 5000000 / 2, 5000000); /* T频率为2KHz */
    am_pwm_enable(timer0_pwm_handle, 1);
    
    /* 通道0使用PIO0_25，在 amhw_timer_cap_config.c 中配置 */
    am_cap_config(sct0_cap_handle, 
                  2, 
                  AM_CAP_TRIGGER_RISE, 
                  cap_callback, 
                  sct0_cap_handle);   /* 回调函数参数 */
    
    am_cap_enable(sct0_cap_handle, 2);

    while (1) {
        if (g_flag == TRUE) {
            
            freq = 1000000000 / g_time_ns;
            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n", g_time_ns, freq);
            g_flag = FALSE;   
        }
        
        am_mdelay(200);
    }
}
 
/** [src_std_sct_cap] */

/* end of file */

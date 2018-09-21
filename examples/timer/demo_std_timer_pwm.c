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
 * \brief 标准定时器用于PWM输出的演示例程，通过标准接口实现
 *
 * - 实现现象:
 *   1. LED0从亮逐渐变暗，接着从暗逐渐变亮；
 *   2. PIO0_29 输出PWM，频率5KHz，占空比50%。
 *
 * \note 一个定时器输出的所有PWM公用一个周期参数，故一个定时器输出的所有PWM频率相同
 *
 * \par 源代码
 * \snippet demo_std_timer_pwm.c src_std_timer_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_std_timer_pwm
 * \copydoc demo_std_timer_pwm.c
 */

/** [src_std_timer_pwm] */
#include "ametal.h"
#include "am_board.h"


/**
 * \brief 主函数
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    uint32_t duty_ns   = 0;
    uint32_t period_ns = 200000;
    
    bool_t  up = TRUE;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台相关初始化 */
    amhw_plfm_timer0_pwm_init();
    
    AM_DBG_INFO("The Timer demo for standard PWM service\r\n");
    
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer2_pwm_dev, 
                                            &g_timer0_pwm_devinfo);

    /* PWM通道0引脚配置为PIO1_16，在amh_timer_pwm_config.c文件中完成 */
    am_pwm_config(timer0_pwm_handle, 0, duty_ns, period_ns);
    am_pwm_enable(timer0_pwm_handle, 0);
    
    /* PWM通道1引脚配置为PIO0_29，在amh_timer_pwm_config.c文件中完成 */
    am_pwm_config(timer0_pwm_handle, 1, period_ns / 2, period_ns);
    am_pwm_enable(timer0_pwm_handle, 1);
    
    /* 
     * LED0低电平亮，故占空比越大，LED越暗
     */
    while (1) {
        if (up == TRUE) {          /* LED从亮逐渐变暗 */
            duty_ns += 2000;
            am_pwm_config(timer0_pwm_handle, 0, duty_ns, 200000);
            if (duty_ns == 200000) {
                up = FALSE; 
            }
        } else {                  /* LED从暗逐渐变亮 */
            duty_ns -= 2000;
            am_pwm_config(timer0_pwm_handle, 0, duty_ns, 200000);
            if (duty_ns == 0) {
                up = TRUE; 
            }            
        }
        am_mdelay(20);
    }
}
  
/** [src_std_timer_pwm] */

/* end of file */

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
 * \brief 标准定时器用于PWM输出的演示例程，通过HW层的接口实现
 *
 * - 实现现象:
 *   1. LED0从亮逐渐变暗，接着从暗逐渐变亮；
 *   2. PIO0_29 输出PWM，频率5KHz，占空比50%。
 *
 * \note 一个定时器输出的所有PWM公用一个周期参数，故一个定时器输出的所有PWM频率相同
 *
 * \par 源代码
 * \snippet demo_hw_timer_pwm.c src_hw_timer_pwm 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_timer_pwm
 * \copydoc demo_hw_timer_pwm.c
 */

/** [src_hw_timer_pwm] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief 配置定时器为PWM
 *
 * \param[in] p_hw_timer : 指向定时器寄存器块的指针
 * \param[in] chan       : PWM使用的通道号，不应使用通道3作为PWM周期定义
 * \param[in] duty_ns    : 占空比参数（单位ns）
 * \param[in] period_ns  : 周期参数（单位ns）
 *
 * \return  无
 *
 * \note PWM通道用于匹配寄存器，所有PWM周期使用相同的周期参数
 */
void timer_pwm_chan_config (amhw_timer_t *p_hw_timer, 
                            uint32_t    chan, 
                            uint32_t    duty_ns, 
                            uint32_t    period_ns)
{
    uint32_t clkfreq;
    uint32_t period_c, low_c;
    
    clkfreq = amhw_clock_periph_freq_get(p_hw_timer);

    period_c = (uint64_t)(period_ns) * (clkfreq) / (uint64_t)1000000000;     
    low_c    = (uint64_t)(duty_ns)   * (clkfreq) / (uint64_t)1000000000; 

    /* 低电平时间 */
    low_c = period_c - low_c;
    
    /* 设置通道3的匹配值 */
    amhw_timer_mat_val_set(p_hw_timer, 3, period_c - 1);  
     
    /* 设置匹配通的匹配值 */
    amhw_timer_mat_val_set(p_hw_timer, chan, low_c);
     
    amhw_timer_mat_pwm_enable(p_hw_timer, chan);
}

/**
 * \brief 定时器作为PWM输出的初始化函数
 * \param[in] p_hw_timer : 指向定时器寄存器块的指针
 * \return 无
 *
 * \note 匹配通道3作为周期 
 */
void timer_pwm_init (amhw_timer_t *p_hw_timer)
{
    /* 复位定时器计数值和预分频计数值为0 */
    amhw_timer_reset(p_hw_timer);
    
    /* 设置定时器预分频为0 */
    amhw_timer_prescale_set(p_hw_timer, 0);
    
     /* 清除匹配中断 */
    amhw_timer_mat_pending_clr(p_hw_timer, 3);
    
    /* 使能匹配事件复位定时计数值 */
    amhw_timer_mat_reset_enable(p_hw_timer, 3);
}

/**
 * \brief 主函数
 */
int main (void)
{
    uint32_t duty_ns   = 0;
    uint32_t period_ns = 200000;
    
    bool_t  up = TRUE;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台相关初始化 */
    amhw_plfm_timer0_pwm_init();
    
    am_gpio_pin_cfg(PIO1_16, PIO1_16_CT0_MAT0);
    am_gpio_pin_cfg(PIO0_29, PIO0_29_CT0_MAT1);

    /* 初始化定时器0作为PWM输出，匹配通道3用于PWM周期设定 */    
    timer_pwm_init(AMHW_TIMER0);
    
    /* PIO1_16输出PWM,占空比 0，周期 200000ns，频率为5KHz */
    timer_pwm_chan_config(AMHW_TIMER0, 0, duty_ns, period_ns);
    
    /* PIO0_29输出PWM,占空比 100000，周期 200000ns，频率为5KHz */
    timer_pwm_chan_config(AMHW_TIMER0, 1, 100000, period_ns);
    
    /* 使能定时器0，用于PWM输出 */
    amhw_timer_enable(AMHW_TIMER0);
    
    /* 
     * LED0低电平亮，故占空比越大，LED越暗
     */
    while (1) {
        if (up == TRUE) {          /* LED从亮逐渐变暗 */
            duty_ns += 2000;
            timer_pwm_chan_config(AMHW_TIMER0, 0, duty_ns, 200000);
            if (duty_ns == 200000) {
                up = FALSE; 
            }
        } else {                  /* LED从暗逐渐变亮 */
            duty_ns -= 2000;
            timer_pwm_chan_config(AMHW_TIMER0, 0, duty_ns, 200000);
            if (duty_ns == 0) {
                up = TRUE; 
            }            
        }
        am_mdelay(20);
    }
}

/** [src_hw_timer_pwm] */

/* end of file */

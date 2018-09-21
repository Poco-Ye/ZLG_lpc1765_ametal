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
 * \brief 标准定时器捕获功能演示例程，通过HW层的接口实现
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
 * \snippet demo_hw_timer_cap.c src_hw_timer_cap 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_timer_cap
 * \copydoc demo_hw_timer_cap.c
 */

/** [src_hw_timer_cap] */
#include "ametal.h"
#include "am_board.h"


bool_t   g_flag    = FALSE;   /**< \brief 捕获标志，当捕获到数据是置位 */
uint32_t g_time_ns = 0;       /**< \brief 捕获的数据 */

/** 
 * \brief 定时器1中断处理函数
 * \param[in] p_arg : 中断入口参数
 * \return    无
 */
void timer1_irq_handler(void *p_arg)
{   
    static uint32_t count1;
    static bool_t   first      = TRUE;
    uint32_t        cap_val;
    
    if (amhw_timer_cap_pending_get(AMHW_TIMER1, 0) == TRUE) {
        
        /* 获取捕获计数 */
        cap_val  = amhw_timer_cap_val_get(AMHW_TIMER1, 0);
 
        if (first == TRUE) {
            first = FALSE;
        } else {
            
            /* 定时器1使用同步时钟，频率是g_system_clkfreq */
            g_time_ns = (uint64_t)(cap_val - count1)  * (uint64_t)1000000000  \
                        / g_async_clkfreq;
            
            /* 置位捕获标志，表明捕获到数据 */
            g_flag = TRUE;
        }

        count1 = cap_val;

        amhw_timer_cap_pending_clr(AMHW_TIMER1, 0);
    }       
}

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
 * \brief 定时器用于捕获功能的初始化函数
 *
 * \param[in] p_hw_timer : 指向定时器寄存器块的指针
 * \param[in] chan       : 捕获通道
 * 
 * \return  None
 */
void timer_cap_init (amhw_timer_t *p_hw_timer, uint8_t chan)
{
    /* 复位定时器计数值和预分频计数值为0 */
    amhw_timer_reset(p_hw_timer);
    
    amhw_timer_prescale_set(p_hw_timer, 0);
    
    amhw_timer_cap_pending_clr(p_hw_timer, 0);
    
    /* 
     * 若需要双边沿捕获，需调用
     * amhw_timer_cap_falling_enable() 和 amhw_timer_cap_rising_enable()两个函数
     * 
     */
    amhw_timer_cap_falling_enable(p_hw_timer, chan);  
    
    /* 使能捕获中断 */
    amhw_timer_cap_int_enable(p_hw_timer, chan); 
    
    am_int_connect(INUM_TIMER1, timer1_irq_handler, (void *)0);

    /* 使能定时器1中断 */
    am_int_enable(INUM_TIMER1);

}

/**
 * \brief 主函数
 */
int main (void)
{
    volatile uint32_t freq;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台相关初始化 */
    amhw_plfm_timer0_pwm_init();
    amhw_plfm_timer1_cap_init();
    
    am_gpio_pin_cfg(PIO0_29, PIO0_29_CT0_MAT1);
    am_gpio_pin_cfg(PIO1_5, PIO1_5_CT1_CAP0);
    
   /* 初始化定时器0作为PWM输出，匹配通道3用于PWM周期设定 */
    timer_pwm_init(AMHW_TIMER0);
    
    /* 
     * PIO0_29输出PWM,占空比 100000，周期 200000ns
     * 频率为5KHz
     */
    timer_pwm_chan_config(AMHW_TIMER0, 1, 100000, 200000);
    
    /* 初始化定时器1用于捕获 */
    timer_cap_init(AMHW_TIMER1, 0);
    
    /* 使能定时器0，用于PWM输出 */
    amhw_timer_enable(AMHW_TIMER0);

    /* 使能定时器1用于捕获 */
    amhw_timer_enable(AMHW_TIMER1);

    AM_DBG_INFO("Timer cap test:\r\n");
    AM_DBG_INFO("Please Connect the PIO0_29 to PIO1_5\r\n");
    
    while (1) {
        if (g_flag == TRUE) {
            
            freq = 1000000000 / g_time_ns;
            AM_DBG_INFO("freq = %d Hz\r\n", freq);
            g_flag = FALSE;   
        }
        
        am_mdelay(200);
    }
}

/** [src_hw_timer_cap] */

/* end of file */

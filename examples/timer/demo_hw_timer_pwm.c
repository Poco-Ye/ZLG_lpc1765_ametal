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
 * \brief ��׼��ʱ������PWM�������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED0�����𽥱䰵�����ŴӰ��𽥱�����
 *   2. PIO0_29 ���PWM��Ƶ��5KHz��ռ�ձ�50%��
 *
 * \note һ����ʱ�����������PWM����һ�����ڲ�������һ����ʱ�����������PWMƵ����ͬ
 *
 * \par Դ����
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
 * \brief ���ö�ʱ��ΪPWM
 *
 * \param[in] p_hw_timer : ָ��ʱ���Ĵ������ָ��
 * \param[in] chan       : PWMʹ�õ�ͨ���ţ���Ӧʹ��ͨ��3��ΪPWM���ڶ���
 * \param[in] duty_ns    : ռ�ձȲ�������λns��
 * \param[in] period_ns  : ���ڲ�������λns��
 *
 * \return  ��
 *
 * \note PWMͨ������ƥ��Ĵ���������PWM����ʹ����ͬ�����ڲ���
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

    /* �͵�ƽʱ�� */
    low_c = period_c - low_c;
    
    /* ����ͨ��3��ƥ��ֵ */
    amhw_timer_mat_val_set(p_hw_timer, 3, period_c - 1);  
     
    /* ����ƥ��ͨ��ƥ��ֵ */
    amhw_timer_mat_val_set(p_hw_timer, chan, low_c);
     
    amhw_timer_mat_pwm_enable(p_hw_timer, chan);
}

/**
 * \brief ��ʱ����ΪPWM����ĳ�ʼ������
 * \param[in] p_hw_timer : ָ��ʱ���Ĵ������ָ��
 * \return ��
 *
 * \note ƥ��ͨ��3��Ϊ���� 
 */
void timer_pwm_init (amhw_timer_t *p_hw_timer)
{
    /* ��λ��ʱ������ֵ��Ԥ��Ƶ����ֵΪ0 */
    amhw_timer_reset(p_hw_timer);
    
    /* ���ö�ʱ��Ԥ��ƵΪ0 */
    amhw_timer_prescale_set(p_hw_timer, 0);
    
     /* ���ƥ���ж� */
    amhw_timer_mat_pending_clr(p_hw_timer, 3);
    
    /* ʹ��ƥ���¼���λ��ʱ����ֵ */
    amhw_timer_mat_reset_enable(p_hw_timer, 3);
}

/**
 * \brief ������
 */
int main (void)
{
    uint32_t duty_ns   = 0;
    uint32_t period_ns = 200000;
    
    bool_t  up = TRUE;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��س�ʼ�� */
    amhw_plfm_timer0_pwm_init();
    
    am_gpio_pin_cfg(PIO1_16, PIO1_16_CT0_MAT0);
    am_gpio_pin_cfg(PIO0_29, PIO0_29_CT0_MAT1);

    /* ��ʼ����ʱ��0��ΪPWM�����ƥ��ͨ��3����PWM�����趨 */    
    timer_pwm_init(AMHW_TIMER0);
    
    /* PIO1_16���PWM,ռ�ձ� 0������ 200000ns��Ƶ��Ϊ5KHz */
    timer_pwm_chan_config(AMHW_TIMER0, 0, duty_ns, period_ns);
    
    /* PIO0_29���PWM,ռ�ձ� 100000������ 200000ns��Ƶ��Ϊ5KHz */
    timer_pwm_chan_config(AMHW_TIMER0, 1, 100000, period_ns);
    
    /* ʹ�ܶ�ʱ��0������PWM��� */
    amhw_timer_enable(AMHW_TIMER0);
    
    /* 
     * LED0�͵�ƽ������ռ�ձ�Խ��LEDԽ��
     */
    while (1) {
        if (up == TRUE) {          /* LED�����𽥱䰵 */
            duty_ns += 2000;
            timer_pwm_chan_config(AMHW_TIMER0, 0, duty_ns, 200000);
            if (duty_ns == 200000) {
                up = FALSE; 
            }
        } else {                  /* LED�Ӱ��𽥱��� */
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

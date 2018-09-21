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
 * \brief ��׼��ʱ����������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. �����������õ���PWMƵ��
 *
 * - ��ע:
 *   1. ��ʱ��0��ΪPWM�������������PIO0_29��
 *   2. ��ʱ��1��Ϊ������������PIO1_5��
 *   3. ��PIO0_29��PIO1_5�������������ڲ���PWMƵ�ʡ�
 *
 * \par Դ����
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


bool_t   g_flag    = FALSE;   /**< \brief �����־����������������λ */
uint32_t g_time_ns = 0;       /**< \brief ��������� */

/** 
 * \brief ��ʱ��1�жϴ�����
 * \param[in] p_arg : �ж���ڲ���
 * \return    ��
 */
void timer1_irq_handler(void *p_arg)
{   
    static uint32_t count1;
    static bool_t   first      = TRUE;
    uint32_t        cap_val;
    
    if (amhw_timer_cap_pending_get(AMHW_TIMER1, 0) == TRUE) {
        
        /* ��ȡ������� */
        cap_val  = amhw_timer_cap_val_get(AMHW_TIMER1, 0);
 
        if (first == TRUE) {
            first = FALSE;
        } else {
            
            /* ��ʱ��1ʹ��ͬ��ʱ�ӣ�Ƶ����g_system_clkfreq */
            g_time_ns = (uint64_t)(cap_val - count1)  * (uint64_t)1000000000  \
                        / g_async_clkfreq;
            
            /* ��λ�����־�������������� */
            g_flag = TRUE;
        }

        count1 = cap_val;

        amhw_timer_cap_pending_clr(AMHW_TIMER1, 0);
    }       
}

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
 * \brief ��ʱ�����ڲ����ܵĳ�ʼ������
 *
 * \param[in] p_hw_timer : ָ��ʱ���Ĵ������ָ��
 * \param[in] chan       : ����ͨ��
 * 
 * \return  None
 */
void timer_cap_init (amhw_timer_t *p_hw_timer, uint8_t chan)
{
    /* ��λ��ʱ������ֵ��Ԥ��Ƶ����ֵΪ0 */
    amhw_timer_reset(p_hw_timer);
    
    amhw_timer_prescale_set(p_hw_timer, 0);
    
    amhw_timer_cap_pending_clr(p_hw_timer, 0);
    
    /* 
     * ����Ҫ˫���ز��������
     * amhw_timer_cap_falling_enable() �� amhw_timer_cap_rising_enable()��������
     * 
     */
    amhw_timer_cap_falling_enable(p_hw_timer, chan);  
    
    /* ʹ�ܲ����ж� */
    amhw_timer_cap_int_enable(p_hw_timer, chan); 
    
    am_int_connect(INUM_TIMER1, timer1_irq_handler, (void *)0);

    /* ʹ�ܶ�ʱ��1�ж� */
    am_int_enable(INUM_TIMER1);

}

/**
 * \brief ������
 */
int main (void)
{
    volatile uint32_t freq;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��س�ʼ�� */
    amhw_plfm_timer0_pwm_init();
    amhw_plfm_timer1_cap_init();
    
    am_gpio_pin_cfg(PIO0_29, PIO0_29_CT0_MAT1);
    am_gpio_pin_cfg(PIO1_5, PIO1_5_CT1_CAP0);
    
   /* ��ʼ����ʱ��0��ΪPWM�����ƥ��ͨ��3����PWM�����趨 */
    timer_pwm_init(AMHW_TIMER0);
    
    /* 
     * PIO0_29���PWM,ռ�ձ� 100000������ 200000ns
     * Ƶ��Ϊ5KHz
     */
    timer_pwm_chan_config(AMHW_TIMER0, 1, 100000, 200000);
    
    /* ��ʼ����ʱ��1���ڲ��� */
    timer_cap_init(AMHW_TIMER1, 0);
    
    /* ʹ�ܶ�ʱ��0������PWM��� */
    amhw_timer_enable(AMHW_TIMER0);

    /* ʹ�ܶ�ʱ��1���ڲ��� */
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

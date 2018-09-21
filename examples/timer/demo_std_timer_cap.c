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
 * \brief ��׼��ʱ�����ڲ����ܣ�ͨ����׼�ӿ�ʵ��
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

bool_t   g_flag    = FALSE;   /**< \brief �����־����������������λ */
uint32_t g_time_ns = 0;       /**< \brief ��������� */

/** 
 * \brief ����ص�����
 *
 * \param[in] p_arg   : ��ڲ���
 * \param[in] cap_val : �������ֵ
 *
 * \return    ��
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
        
        /* ��λ�����־�������������� */
        g_flag = TRUE;
    }

    count1 = cap_val;
}

/**
 * \brief ������
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    am_cap_handle_t  timer1_cap_handle;
    uint32_t         freq;

    /* �༶��ʼ�� */
    am_board_init();

    /* ƽ̨��س�ʼ�� */
    amhw_plfm_timer0_pwm_init();
    amhw_plfm_timer1_cap_init();
    
    AM_DBG_INFO("The Timer demo for standard CAP service\r\n");
    
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer0_pwm_dev, 
                                            &g_timer0_pwm_devinfo);
    
    timer1_cap_handle = amdr_timer_cap_init(&g_timer1_cap_dev, 
                                            &g_timer1_cap_devinfo);
    
    /* PWMͨ��1����Ӧ��������PIO0_29����������amdr_hwconfig_timer_cap.c��� */
    am_pwm_config(timer0_pwm_handle, 1, 250000, 500000); /* Ƶ��λ2KHz */
    am_pwm_enable(timer0_pwm_handle, 1);
    
    /* ������ͨ��0����Ӧ��������PIO1_5����������amdr_hwconfig_timer_cap.c��� */
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

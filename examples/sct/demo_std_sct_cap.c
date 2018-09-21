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
 * \brief SCTʵ�ֲ����ܣ�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ������ò����ܵõ���PWM�źŵ����ں�Ƶ�ʡ�
 *
 * - ע�⣺
 *   1. ��ʱ��0ͨ��PIO0_29�������PWM��
 *   2. SCT��������ͨ��2ʹ��PIO0_25���ţ�
 *   3. ����PIO0_29���ź�PIO0_25���ţ�ʹ�ò������PWMƵ�ʡ�
 *
 * \par Դ����
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

volatile bool_t   g_flag    = FALSE;   /**< \brief �����־   */
volatile uint32_t g_time_ns = 0;       /**< \brief �������ֵ */

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
            
            /* �ñ�־Ϊ�棬����������� */
            g_flag = TRUE;
        }
    }
}

/**
 * \brief ���������
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    am_cap_handle_t  sct0_cap_handle;
    uint32_t         freq;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_timer0_pwm_init();

    amhw_plfm_sct0_cap_init();
    
    AM_DBG_INFO("The SCT demo for standard CAP service\r\n");
    
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer0_pwm_dev, 
                                            &g_timer0_pwm_devinfo);
    
    sct0_cap_handle   = amdr_sct_cap_init(&g_sct0_cap_dev, 
                                          &g_sct0_cap_devinfo);

    /* ͨ��1ʹ��PIO0_29���� amhw_timer_cap_config.c ������ */
    am_pwm_config(timer0_pwm_handle, 1, 5000000 / 2, 5000000); /* TƵ��Ϊ2KHz */
    am_pwm_enable(timer0_pwm_handle, 1);
    
    /* ͨ��0ʹ��PIO0_25���� amhw_timer_cap_config.c ������ */
    am_cap_config(sct0_cap_handle, 
                  2, 
                  AM_CAP_TRIGGER_RISE, 
                  cap_callback, 
                  sct0_cap_handle);   /* �ص��������� */
    
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

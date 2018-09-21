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
 * \brief ��׼��ʱ������PWM�������ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED0�����𽥱䰵�����ŴӰ��𽥱�����
 *   2. PIO0_29 ���PWM��Ƶ��5KHz��ռ�ձ�50%��
 *
 * \note һ����ʱ�����������PWM����һ�����ڲ�������һ����ʱ�����������PWMƵ����ͬ
 *
 * \par Դ����
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
 * \brief ������
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    uint32_t duty_ns   = 0;
    uint32_t period_ns = 200000;
    
    bool_t  up = TRUE;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��س�ʼ�� */
    amhw_plfm_timer0_pwm_init();
    
    AM_DBG_INFO("The Timer demo for standard PWM service\r\n");
    
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer2_pwm_dev, 
                                            &g_timer0_pwm_devinfo);

    /* PWMͨ��0��������ΪPIO1_16����amh_timer_pwm_config.c�ļ������ */
    am_pwm_config(timer0_pwm_handle, 0, duty_ns, period_ns);
    am_pwm_enable(timer0_pwm_handle, 0);
    
    /* PWMͨ��1��������ΪPIO0_29����amh_timer_pwm_config.c�ļ������ */
    am_pwm_config(timer0_pwm_handle, 1, period_ns / 2, period_ns);
    am_pwm_enable(timer0_pwm_handle, 1);
    
    /* 
     * LED0�͵�ƽ������ռ�ձ�Խ��LEDԽ��
     */
    while (1) {
        if (up == TRUE) {          /* LED�����𽥱䰵 */
            duty_ns += 2000;
            am_pwm_config(timer0_pwm_handle, 0, duty_ns, 200000);
            if (duty_ns == 200000) {
                up = FALSE; 
            }
        } else {                  /* LED�Ӱ��𽥱��� */
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

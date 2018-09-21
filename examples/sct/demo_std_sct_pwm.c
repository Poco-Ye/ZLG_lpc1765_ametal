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
 * \brief SCTʵ��PWM��׼�ӿ����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_8(SCT_OUT1)���4kHz��PWM��ռ�ձ�Ϊ50%��
 *   2. PIO0_5(SCT_OUT6)���4kHz��PWM��ռ�ձ�Ϊ25%��
 *
 * \par Դ����
 * \snippet demo_std_sct_pwm.c src_std_sct_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_sct_pwm
 * \copydoc demo_std_sct_pwm.c
 */
 
/** [src_std_sct_pwm] */
#include "ametal.h"
#include "am_board.h"


/**
 * \brief ���������
 */
int main (void)
{
    am_pwm_handle_t sct0_pwm_handle;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    amhw_plfm_sct0_pwm_init();
    
    AM_DBG_INFO("The SCT demo for standard pwm service\r\n");
    AM_DBG_INFO("The PIO0_8(SCT_OUT1) PWM: freq is 4kHz, The duty ratio is 50% \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) PWM: freq is 4kHz, The duty ratio is 25% \r\n");
    
    /* ��ʼ����ʱ��0ΪPWM���� */
    sct0_pwm_handle = amdr_sct_pwm_init(&g_sct0_pwm_dev, 
                                        &g_sct0_pwm_devinfo);

    /* ͨ��1ʹ��PIO0_8���� amdr_hwconfig_sct_pwm.c ������ */
    am_pwm_config(sct0_pwm_handle, 1, 125000, 250000);
    am_pwm_enable(sct0_pwm_handle, 1);

    /* ͨ��6ʹ��PIO0_5���� amdr_hwconfig_sct_pwm.c ������ */
    am_pwm_config(sct0_pwm_handle, 6, 62500, 250000);
    am_pwm_enable(sct0_pwm_handle, 6);
    
    while (1) {
        
        am_led_toggle(0);
        am_mdelay(200);
    }
}

/** [src_std_sct_pwm] */

/* end of file */

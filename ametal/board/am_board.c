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
 * \brief EasyARM-54000M4 ���İ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */

#include "am_common.h"
#include "am_system.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_buzzer_pwm.h"
#include "am_prj_config.h"

/*******************************************************************************
  ����LED�����Ϣ
*******************************************************************************/

#if (AM_CFG_LED_ENABLE == 1)

#include "am_led.h"

/** \brief ����LED��GPIO�ܽź��Ƿ�͵�ƽ���� */
const am_led_info_t g_led_info[] = {
     {PIO1_16, TRUE},
};

/** \brief ����LED���� */
const uint32_t g_led_num = sizeof(g_led_info) / sizeof(g_led_info[0]);

#endif


/*******************************************************************************
  ������Դ�����������Ϣ
*******************************************************************************/

#if (AM_CFG_BUZZER_ENABLE == 1)

#include "amdr_sct_pwm.h"

#define __BUZZER_PWM_PERIOD_NS \
            (1000000000 / AM_CFG_BUZZER_PWM_FREQ)

#define __BUZZER_PWM_DUTY_NS   \
            (10000000 * AM_CFG_BUZZER_PWM_DUTY / AM_CFG_BUZZER_PWM_FREQ)
#endif   

/*******************************************************************************
  ��������
*******************************************************************************/

/**
 * \brief �弶��ʼ��
 */
void am_board_init (void)
{
    /* ϵͳ��ʼ�� */
    am_system_init();

#ifdef AM_CORTEX_M4
    /* GPIOƽ̨��ʼ����������M4�˳�ʼ��1�μ��� */
    amhw_plfm_gpio_init();
    
#endif
    
    amdr_gpio_init(&g_gpio_dev, &g_gpio_devinfo);

#if (AM_CFG_INT_ENABLE == 1)

    /* �жϳ�ʼ�� */
    amdr_int_init(&g_int_dev, &g_int_devinfo);
#endif

#if (AM_CFG_DELAY_ENABLE == 1)
    am_delay_init();
#endif

#if (AM_CFG_LED_ENABLE == 1)
    am_led_init(g_led_info,g_led_num);
#endif

#if (AM_CFG_BUZZER_ENABLE == 1)
    
    amhw_plfm_sct0_pwm_init();
    
    am_buzzer_init(amdr_sct_pwm_init(&g_sct0_pwm_dev,&g_sct0_pwm_devinfo),
                   5,                    /* ʹ��ͨ��5, SCT_OUT5,PIO0_14 */
                   __BUZZER_PWM_DUTY_NS,
                   __BUZZER_PWM_PERIOD_NS);
#endif

#if (AM_CFG_DEBUG_ENABLE == 1)

    /* ���Գ�ʼ�� */
    am_debug_init();
#endif

}

/* end of file */

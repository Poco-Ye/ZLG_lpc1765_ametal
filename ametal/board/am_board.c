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
 * \brief EasyARM-54000M4 核心板
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
  板上LED相关信息
*******************************************************************************/

#if (AM_CFG_LED_ENABLE == 1)

#include "am_led.h"

/** \brief 板上LED的GPIO管脚和是否低电平点亮 */
const am_led_info_t g_led_info[] = {
     {PIO1_16, TRUE},
};

/** \brief 板上LED数量 */
const uint32_t g_led_num = sizeof(g_led_info) / sizeof(g_led_info[0]);

#endif


/*******************************************************************************
  板上无源蜂鸣器相关信息
*******************************************************************************/

#if (AM_CFG_BUZZER_ENABLE == 1)

#include "amdr_sct_pwm.h"

#define __BUZZER_PWM_PERIOD_NS \
            (1000000000 / AM_CFG_BUZZER_PWM_FREQ)

#define __BUZZER_PWM_DUTY_NS   \
            (10000000 * AM_CFG_BUZZER_PWM_DUTY / AM_CFG_BUZZER_PWM_FREQ)
#endif   

/*******************************************************************************
  公共函数
*******************************************************************************/

/**
 * \brief 板级初始化
 */
void am_board_init (void)
{
    /* 系统初始化 */
    am_system_init();

#ifdef AM_CORTEX_M4
    /* GPIO平台初始化，仅需在M4核初始化1次即可 */
    amhw_plfm_gpio_init();
    
#endif
    
    amdr_gpio_init(&g_gpio_dev, &g_gpio_devinfo);

#if (AM_CFG_INT_ENABLE == 1)

    /* 中断初始化 */
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
                   5,                    /* 使用通道5, SCT_OUT5,PIO0_14 */
                   __BUZZER_PWM_DUTY_NS,
                   __BUZZER_PWM_PERIOD_NS);
#endif

#if (AM_CFG_DEBUG_ENABLE == 1)

    /* 调试初始化 */
    am_debug_init();
#endif

}

/* end of file */

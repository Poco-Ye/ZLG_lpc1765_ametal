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
 * \brief SCT实现PWM标准接口例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. PIO0_8(SCT_OUT1)输出4kHz的PWM，占空比为50%；
 *   2. PIO0_5(SCT_OUT6)输出4kHz的PWM，占空比为25%。
 *
 * \par 源代码
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
 * \brief 主函数入口
 */
int main (void)
{
    am_pwm_handle_t sct0_pwm_handle;
    
    /* 板级初始化 */
    am_board_init();
    
    /* 平台初始化 */
    amhw_plfm_sct0_pwm_init();
    
    AM_DBG_INFO("The SCT demo for standard pwm service\r\n");
    AM_DBG_INFO("The PIO0_8(SCT_OUT1) PWM: freq is 4kHz, The duty ratio is 50% \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) PWM: freq is 4kHz, The duty ratio is 25% \r\n");
    
    /* 初始化定时器0为PWM功能 */
    sct0_pwm_handle = amdr_sct_pwm_init(&g_sct0_pwm_dev, 
                                        &g_sct0_pwm_devinfo);

    /* 通道1使用PIO0_8，在 amdr_hwconfig_sct_pwm.c 中配置 */
    am_pwm_config(sct0_pwm_handle, 1, 125000, 250000);
    am_pwm_enable(sct0_pwm_handle, 1);

    /* 通道6使用PIO0_5，在 amdr_hwconfig_sct_pwm.c 中配置 */
    am_pwm_config(sct0_pwm_handle, 6, 62500, 250000);
    am_pwm_enable(sct0_pwm_handle, 6);
    
    while (1) {
        
        am_led_toggle(0);
        am_mdelay(200);
    }
}

/** [src_std_sct_pwm] */

/* end of file */

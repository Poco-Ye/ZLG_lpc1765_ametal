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
 * \brief GPIO引脚中断例程，通过标准接口实现
 *
 * - 操作步骤：
 *   1. PIO0_14引脚连接到按键。
 *   
 * - 实验现象：
 *   1. 按下按键，LED状态改变。
 * 
 * \par 源代码
 * \snippet demo_std_gpio_trigger.c src_std_gpio_trigger 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_gpio_trigger
 * \copydoc demo_std_gpio_trigger.c
 */

/** [src_std_gpio_trigger] */
#include "ametal.h" 
#include "am_board.h"


/**
 * \brief 引脚中断服务函数
 */
void gpio_isr (void *p_arg)
{
    am_led_toggle(0);
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();

    /* 连接中断服务函数 */
    am_gpio_trigger_connect(PIO0_14, gpio_isr, (void *)0);

    /* 配置触发引脚和触发模式 */
    am_gpio_trigger_cfg(PIO0_14, AM_GPIO_TRIGGER_FALL);

    /* 使能引脚触发中断 */
    am_gpio_trigger_on(PIO0_14);

    while (1) {
        __WFI();
    }
}

/** [src_std_gpio_trigger] */

/* end of file */

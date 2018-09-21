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
 * \brief APL_StartKit 按键演示例程
 *
 * - 操作步骤：
 *   1. 使用跳线帽连接（KEY1、KEY2、KEY3、KEY4、KEY5）；
 *   2. 使用跳线帽连接（LED1、LED2、LED3、LED4）；
 *   3. 将APL_StartKit配板上串口0接口（J3）连接到PC机上。
 *
 * - 实验现象：
 *   1. 按下按键KEY1，LED1状态翻转，通过串口输出“Press Down Key!”；
 *   2. 按下按键KEY2，LED2状态翻转，通过串口输出“Press Right Key!”；
 *   3. 按下按键KEY3，LED1、LED2、LED3、LED4状态全部翻转，通过串口输出“Press Ok Key!”；
 *   4. 按下按键KEY4，LED3状态翻转，通过串口输出“Press Left Key!”；
 *   5. 按下按键KEY5，LED4状态翻转，通过串口输出“Press Up Key!”。
 * 
 * \par 源代码
 * \snippet demo_apl_startkit_key.c src_apl_startkit_key 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_apl_startkit_key
 * \copydoc demo_apl_startkit_key.c
 */

/** [src_apl_startkit_key] */
#include "ametal.h" 
#include "am_board.h"


/* APL_StartKit defines */
#define  LED1           PIO1_6
#define  LED2           PIO1_7
#define  LED3           PIO1_8
#define  LED4           PIO1_9

#define  KEY1           PIO1_10
#define  KEY2           PIO1_11
#define  KEY3           PIO1_12
#define  KEY4           PIO1_13
#define  KEY5           PIO0_8
/**
 * \brief KEY1(down)中断服务函数
 */
void key_down_isr (void *p_arg)
{
    am_gpio_toggle(LED1);
    AM_DBG_INFO("Press Down Key!\r\n");
}

/**
 * \brief KEY2(right)中断服务函数
 */
void key_right_isr (void *p_arg)
{
    am_gpio_toggle(LED2);
    AM_DBG_INFO("Press Right Key!\r\n");
}

/**
 * \brief KEY3(OK)中断服务函数
 */
void key_ok_isr (void *p_arg)
{
    am_gpio_toggle(LED1);
    am_gpio_toggle(LED2);
    am_gpio_toggle(LED3);
    am_gpio_toggle(LED4);
    AM_DBG_INFO("Press Ok Key!\r\n");
}

/**
 * \brief KEY4(left)中断服务函数
 */
void key_left_isr (void *p_arg)
{
    am_gpio_toggle(LED3);
    AM_DBG_INFO("Press Left Key!\r\n");
}

/**
 * \brief KEY5(up)中断服务函数
 */
void key_up_isr (void *p_arg)
{
    am_gpio_toggle(LED4);
    AM_DBG_INFO("Press Up Key!\r\n");
}

void apl_startkit_gpio_init(void)
{
    am_gpio_pin_cfg(LED1, AM_GPIO_OUTPUT);        /* 配置 LED1 输出模式 */
    am_gpio_set(LED1, 1);                         /* LED1 初始状态熄灭  */
    am_gpio_pin_cfg(LED2, AM_GPIO_OUTPUT);        /* 配置 LED2 输出模式 */
    am_gpio_set(LED2, 1);                         /* LED2 初始状态熄灭  */
    am_gpio_pin_cfg(LED3, AM_GPIO_OUTPUT);        /* 配置 LED3 输出模式 */
    am_gpio_set(LED3, 1);                         /* LED3 初始状态熄灭  */
    am_gpio_pin_cfg(LED4, AM_GPIO_OUTPUT);        /* 配置 LED4 输出模式 */
    am_gpio_set(LED4, 1);                         /* LED4 初始状态熄灭  */
}
/**
 * \brief 主函数入口
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();

    apl_startkit_gpio_init();
    
    am_gpio_trigger_connect(KEY1, key_down_isr, (void *)0);  /* KEY1连接中断服务函数       */
    am_gpio_trigger_cfg(KEY1, AM_GPIO_TRIGGER_FALL);         /* 配置KEY1触发引脚和触发模式 */
    am_gpio_trigger_on(KEY1);                                /* 使能KEY1引脚触发中断       */
    
    am_gpio_trigger_connect(KEY2, key_right_isr, (void *)0); /* KEY2连接中断服务函数       */
    am_gpio_trigger_cfg(KEY2, AM_GPIO_TRIGGER_FALL);         /* 配置KEY2触发引脚和触发模式 */
    am_gpio_trigger_on(KEY2);                                /* 使能KEY2引脚触发中断       */
    
    am_gpio_trigger_connect(KEY3, key_ok_isr, (void *)0);    /* KEY3连接中断服务函数       */
    am_gpio_trigger_cfg(KEY3, AM_GPIO_TRIGGER_FALL);         /* 配置KEY3触发引脚和触发模式 */
    am_gpio_trigger_on(KEY3);                                /* 使能KEY3引脚触发中断       */
   
    am_gpio_trigger_connect(KEY4, key_left_isr, (void *)0);  /* KEY4连接中断服务函数       */
    am_gpio_trigger_cfg(KEY4, AM_GPIO_TRIGGER_FALL);         /* 配置KEY4触发引脚和触发模式 */    
    am_gpio_trigger_on(KEY4);                                /* 使能KEY4引脚触发中断       */
    
    am_gpio_trigger_connect(KEY5, key_up_isr, (void *)0);    /* KEY5连接中断服务函数       */
    am_gpio_trigger_cfg(KEY5, AM_GPIO_TRIGGER_FALL);         /* 配置KEY5触发引脚和触发模式 */
    am_gpio_trigger_on(KEY5);                                /* 使能KEY5引脚触发中断       */
    
    while (1) {
        __WFI();
    }
}

/** [src_apl_startkit_key] */

/* end of file */

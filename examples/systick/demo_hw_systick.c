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
 * \brief SYSTICK演示例程，通过HW层的接口实现
 *
 *   由于延时函数是使用SYSTICK实现，故此文件中不可使用延时函数
 *
 * - 实验现象:
 *   1. LED0闪烁频率10Hz
 *
 * \par 源代码
 * \snippet demo_hw_systick.c src_hw_systick
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_systick
 * \copydoc demo_hw_systick.c
 */
 
/** [src_hw_systick] */
#include "ametal.h"
#include "am_board.h"



/**
 * \brief SYSTICK 中断处理函数
 * \return 无
 * \note SYSTICK中断处理属于内核中断，故无需调用
 *       am_int_connect() 和 am_int_enable() 函数。
 */
void SysTick_Handler(void)
{
    am_led_toggle(LED0);
}

/**
 * \brief 主函数
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();

    AM_DBG_INFO("The demo for SYSTICK\r\n");
    
    /* 使用系统时钟作为SYSTICK时钟源 */
    am_systick_config(AMHW_SYSTICK, AMHW_SYSTICK_CONFIG_CLKSRC_SYSTEM);
    
    /* 设置重载值，最大值为0xFFFFFF */
    am_systick_reload_val_set(AMHW_SYSTICK, g_system_clkfreq / 10);    
    
    /* 设置当前的值为0 */
    am_systick_val_set(AMHW_SYSTICK, 0);
    
    /* 使能SYSTICK中断 */
    am_systick_int_enable(AMHW_SYSTICK);
    
    /* 使能SYSTICK，开始向下计数 */
    am_systick_enable(AMHW_SYSTICK);
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_systick] */

/* end of file */

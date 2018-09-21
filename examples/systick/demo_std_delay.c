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
 * \brief 延时例程，通过标准接口实现
 *
 * - 实验现象:
 *   1. LED0闪烁频率10Hz
 *
 * \par 源代码
 * \snippet demo_std_delay.c src_std_delay
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_std_delay
 * \copydoc demo_std_delay.c
 */
 
/** [src_std_delay] */
#include "ametal.h"
#include "am_board.h"



/**
 * \brief 主函数
 */
int main (void)
{
    /*
     * 板级初始化
     */
    am_board_init();

    AM_DBG_INFO("The demo for delay, The delay is implement through SYSTICK\r\n");
    
    am_delay_init();
    
    /* 延时 1000us */
    am_udelay(1000);
    
    while (1) {
        
        am_led_toggle(LED0);
        
        /* 延时100ms  */
        am_mdelay(100);
    }
}

/** [src_std_delay] */

/* end of file */

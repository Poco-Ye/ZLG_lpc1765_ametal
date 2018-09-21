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
 * \brief Cortex-M4模板工程
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-16  tee, first implementation.
 * \endinternal
 */ 

#include "ametal.h"
#include "am_board.h"

/**
 * \brief 主函数入口
 */
int main (void)
{   
    /* 板级初始化  */
    am_board_init();

    AM_DBG_INFO("Start up successful!\r\n");

    am_buzzer_beep(500);
    
    while (1) {
        
        am_led_on(LED0);
        am_mdelay(100);
        am_led_off(LED0);
        am_mdelay(100);
    }
}

/* end of file */

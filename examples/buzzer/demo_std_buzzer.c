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
 * \brief 蜂鸣器例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. 蜂鸣器以0.5s的时间间隔鸣叫。
 *
 * \warning 蜂鸣器占用了SCT_OUT5的PIO1_15引脚，如果用了使该蜂鸣器，就不能将SCT配置
 *          为其他非PWM功能。如需要在应用程序中使用SCT，就不能调用蜂鸣器的API。
 *       
 *
 * \par 源代码
 * \snippet demo_std_buzzer.c src_std_buzzer 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_buzzer
 * \copydoc demo_std_buzzer.c
 */
 
/** [src_std_buzzer] */
#include "ametal.h"
#include "am_board.h"


/**
 * \brief 主函数入口
 */
int main (void)
{  
    /* 板级初始化 */
    am_board_init();
    
    am_buzzer_on();
    am_mdelay(500);
    am_buzzer_off();
    am_mdelay(500);
    
    while (1) {
        
        am_buzzer_beep(500);  /* 蜂鸣器鸣叫0.5s */
        am_mdelay(500);      
    }
}

/** [src_std_buzzer] */

/* end of file */

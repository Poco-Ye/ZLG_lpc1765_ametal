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
 * \brief GPIO例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. 间隔0.5s，LED闪烁5次；
 *   2. 之后，LED以0.2s的间隔一直闪烁。
 * 
 * \par 源代码
 * \snippet demo_std_gpio.c src_std_gpio 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-08  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_gpio
 * \copydoc demo_std_gpio.c
 */
 
/** [src_std_gpio] */
#include "ametal.h"  
#include "am_board.h"
#include "am_delay.h"
#include "am_prj_config.h"

/**
 * \brief 主函数入口
 */
int main (void)
{
    uint8_t i;
    
    /* 板级初始化 */
    am_board_init();
    
    /* 配置GPIO引脚功能 */
    am_gpio_pin_cfg(PIO1_16, AM_GPIO_OUTPUT);
    
    /* 间隔0.5s，LED闪烁5次 */
    for (i = 0; i < 5; i++) {
        am_gpio_set(PIO1_16, 0); 
        am_mdelay(500);
        
        am_gpio_set(PIO1_16, 1); 
        am_mdelay(500);
    }
    
    while (1) {
        
        /* LED以0.2s的间隔一直闪烁 */
        am_gpio_toggle(PIO1_16);
        am_mdelay(200);
    }
}

/** [src_std_gpio] */

/* end of file */

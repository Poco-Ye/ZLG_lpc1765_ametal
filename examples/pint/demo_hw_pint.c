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
 * \brief GPIO引脚中断（PINT）例程，通过HW层的接口实现
 *
 * - 操作步骤：
 *    1. PIO0_14引脚连接到按键。
 *
 * - 实验现象：
 *    1. 按下按键，LED的状态变化。
 *
 * \par 源代码
 * \snippet demo_hw_pint.c src_hw_pint 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-08  asd, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_pint
 * \copydoc demo_hw_pint.c
 */

/** [src_hw_pint] */
#include "ametal.h"   
#include "am_board.h"


/**
 * \brief GPIO引脚配置。
 */
void pint_config (void)
{
    /* 配置引脚功能 */
    am_gpio_pin_cfg(PIO0_14, AM_GPIO_INPUT);
    
    /* 选择引脚中断通道 */
    amhw_inmux_pint_sel(AMHW_INMUX, AMHW_INMUX_CHAN_0, PIO0_14);
    
    /* 配置为下降沿触发 */
    amhw_pint_trigger_select(AMHW_PINT, AMHW_PINT_CHAN_0, AMHW_PINT_TRIGGER_FALL);
}

/** 
 * \brief 平台初始化。
 */
void plfm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_PINT);
    amhw_syscon_periph_reset(AMHW_RESET_PINT);

    amhw_clock_periph_enable(AMHW_CLOCK_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
}

/** 
 * \brief 引脚中断服务函数。
 */
void pint_isr (void *p_arg)
{
    /* 清除中断标志 */
    amhw_pint_status_clr(AMHW_PINT, AMHW_PINT_CHAN_0);
    
    am_led_toggle(0); 
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();
    
    /* 平台初始化，因在板级初始化中已经初始化该部分，故不再执行。 */
//    plfm_init();

    /* 引脚中断配置 */
    pint_config();
    
    /* 连接中断服务函数 */
    am_int_connect(INUM_PIN_INT0, pint_isr, (void *)0);
    
    /* 使能引脚中断 */
    am_int_enable(INUM_PIN_INT0);
    
    while (1) {
       __WFI();
    }
}

/** [src_hw_pint] */

/* end of file */

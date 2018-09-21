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
 * \brief 组中断(GINT)例程，通过HW层的接口实现
 *
 * - 操作步骤
 *    1. PIO0_13引脚连接至按键1； 
 *    2. PIO0_14引脚连接至按键2； 
 *    3. PIO1_9引脚连接至按键3； 
 *    4. PIO1_10引脚连接至按键4。
 *
 * - 实验现象
 *    1. 按下按键1或按键2时，LED翻转；
 *    2. 同时按下按键3和按键4，LED闪烁5次。
 *
 * \warning 只有Cortex-M4内核才能使用GINT1
 *
 * \par 源代码
 * \snippet demo_hw_gint.c src_hw_gint 
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-01-22  hbt, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_gint
 * \copydoc demo_hw_gint.c
 */
 
/** [src_hw_gint] */
#include "ametal.h" 
#include "am_board.h"



/** \brief 中断标志 */
bool_t g_gint0_flag;

#if AM_CORTEX_M4 
bool_t g_gint1_flag;
#endif

/**
 * \brief 组中断配置。
 */
void gint_config (void)
{
    /* Group0: GPIO引脚配置 */
    am_gpio_pin_cfg(PIO0_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_14, AM_GPIO_INPUT);

#if AM_CORTEX_M4
    
    /* Group1: GPIO引脚配置 */
    am_gpio_pin_cfg(PIO1_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO1_10, AM_GPIO_INPUT); 
#endif
    
    /* 配置组中断功能 */
    amhw_gint_ctrl_set(AMHW_GINT, AMHW_GROUP_0, AMHW_GINT_CTRL_COMB_OR | 
                                                AMHW_GINT_CTRL_TRIG_EDGE); 

#if AM_CORTEX_M4 
    amhw_gint_ctrl_set(AMHW_GINT, AMHW_GROUP_1, AMHW_GINT_CTRL_COMB_AND |
                                                AMHW_GINT_CTRL_TRIG_LEVEL);    
#endif

    /* Group0: 选择引脚到指定组中断的低电平触发 */
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_0, PIO0_13);
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_0, PIO0_14);

#if AM_CORTEX_M4 

    /* Group1: 选择引脚到指定组中断的低电平触发 */
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_1, PIO1_9);
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_1, PIO1_10);     
#endif
    
    /* 使能组中断0的引脚中断 */
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_0, PIO0_13);    
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_0, PIO0_14);

#if AM_CORTEX_M4 

    /* 使能组中断1的引脚中断 */
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_1, PIO1_9);
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_1, PIO1_10);     
#endif
}

/** 
 * \brief 平台初始化
 */
void plfm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_GINT);
    amhw_syscon_periph_reset(AMHW_RESET_GINT);
}

/** 
 * \brief 组中断0服务函数
 */
void gint0_isr (void *p_arg)
{
    amhw_gint_status_clr(AMHW_GINT, AMHW_GROUP_0);
    
    g_gint0_flag = TRUE;
}

#if AM_CORTEX_M4 
/** 
 * \brief 组中断1服务函数
 */
void gint1_isr (void *p_arg)
{
    amhw_gint_status_clr(AMHW_GINT, AMHW_GROUP_1);
    
    g_gint1_flag = TRUE;
}
#endif

/**
 * \brief 主函数入口
 */
int main (void)
{
    int i;
    
    /* 板级初始化 */
    am_board_init();
    
    /* 平台初始化 */
    plfm_init();
    
    /* 组中断配置 */
    gint_config();
    
    /* 连接中断服务函数 */
    am_int_connect(INUM_GINT0, gint0_isr, (void *)0); 
    
#if AM_CORTEX_M4 
    am_int_connect(INUM_GINT1, gint1_isr, (void *)0);   
#endif
    
    /* 使能中断 */
    am_int_enable(INUM_GINT0);
    
#if AM_CORTEX_M4 
    am_int_enable(INUM_GINT1);      
#endif
    
    while (1) {
        
        /* 组中断0产生中断：LED翻转 */
        if (g_gint0_flag == TRUE) {
            g_gint0_flag = FALSE;
            am_led_toggle(0);
        }

#if AM_CORTEX_M4 

         /* 组中断1产生中断：闪烁5次 */
        if (g_gint1_flag == TRUE) {
            g_gint1_flag = FALSE;
            for (i = 0; i < 5; i++) {
                am_led_toggle(0);
                am_mdelay(200);
            }
        }
#endif
    }
}

/** [src_hw_gint] */

/* end of file */

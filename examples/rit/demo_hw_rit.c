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
 * \brief 重复中断定时器(RIT)例程，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. LED以10Hz的频率闪烁。
 * 
 * \par 源代码
 * \snippet demo_hw_rit.c src_hw_rit 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_hw_rit
 * \copydoc demo_hw_rit.c
 */

/** [src_hw_rit] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief 重复中断定时器中断服务函数
 * \param[in]  p_arg : 用户自定义参数，通过 am_int_connect() 函数传递。
 * \return 无
 */
void rit_irq_handler (void *p_arg)
{
    if (amhw_rit_int_flag_check(AMHW_RIT) == TRUE) {
        
        am_led_toggle(LED0);
        
        amhw_rit_int_flag_clr(AMHW_RIT);
    }
}

/**
 * \brief 主函数入口
 */
int main (void)
{      
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_rit_init();
    
    amhw_rit_count_set(AMHW_RIT, 0);     /* 设置计数器为 0  */
    
    /* 设置比较值以产生10Hz的中断 */
    amhw_rit_compval_set(AMHW_RIT, (uint64_t)(g_main_clkfreq / 10)); 
    
    am_int_connect(INUM_RIT, rit_irq_handler, (void *)0);
    
    /* 使能RIT中断 */
    am_int_enable(INUM_RIT);
   
    amhw_rit_clear_enable(AMHW_RIT);  /* 清除匹配计数器 */
    
    amhw_rit_enable(AMHW_RIT);
         
    while (1) {
 
        __WFI();
    }
}

/** [src_hw_rit] */

/* end of file */

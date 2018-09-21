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
 * \brief SCT 32位定时器实现定时功能的例程，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. LED以10Hz的频率闪烁。
 *
 * \par 源代码
 * \snippet demo_hw_sct_1_32bit_timing.c src_hw_sct_1_32bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */
 
 
/**
 * \addtogroup demo_if_hw_sct_1_32bit_timing
 * \copydoc demo_hw_sct_1_32bit_timing.c
 */
 
/** [src_hw_sct_1_32bit_timing] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief  SCT0中断服务函数
 * \param[in]  p_arg : 用户自定义参数，由 am_int_connect() 函数传递。
 * \return  无
 */
void sct0_irq_handler(void *p_arg)
{
    /* 事件0产生中断 */
    if (amhw_sct_event_flag_chk(AMHW_SCT0, AMHW_SCT_EVT(0)) == TRUE ) {
        
        am_led_toggle(LED0);
        
        /* 清除标志 */
        amhw_sct_event_flag_clr(AMHW_SCT0, AMHW_SCT_EVT(0));  
    }
}

/** 
 * \brief 初始化SCT为定时器功能。
 *
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \param[in] freq  : 中断频率。
 *
 * \return 无
 */
void sct_timer_init (amhw_sct_t *p_hw_sct, uint32_t freq)
{

    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  | /* 使用32位定时器 */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* 使用系统时钟   */
    
    /* 将匹配捕捉寄存器配置为匹配功能 */
    amhw_sct_regmode_config(p_hw_sct, 
                            AMHW_SCT_MODE_UNIFY,    /* SCT模式为UNIFY(1 32-bit 计数器) */
                            0,                      /* 匹配/捕获0                      */
                            AMHW_SCT_MATCAP_MATCH); /* 操作匹配寄存器                  */
    
    /* 设置匹配0和重载匹配值 */
    amhw_sct_mat_val_set(p_hw_sct, 
                         AMHW_SCT_MODE_UNIFY, 
                         AMHW_SCT_MAT(0), 
                         g_system_clkfreq / freq - 1);
    
    amhw_sct_mat_reload_val_set(p_hw_sct, 
                                AMHW_SCT_MODE_UNIFY, 
                                AMHW_SCT_MAT(0), 
                                g_system_clkfreq / freq - 1);
    
    /* 设置事件0控制寄存器 */
    amhw_sct_event_ctrl(p_hw_sct, 
                        AMHW_SCT_EVT(0),                  /* 事件0                    */
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* 事件关联到匹配0          */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* 只能使用指定的匹配寄存器 */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV 值加上 STATE     */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* 加 0，STATE没有改变      */
                   
    /* 设置当前状态值为0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
    
    /* 使能状态0中事件0产生 */
    amhw_sct_event_state_enable(p_hw_sct, AMHW_SCT_EVT(0), AMHW_SCT_STATE(0));
    
    /* 使能事件0作限定计数器 */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_EVT(0));
    
    /* 使能事件0产生中断 */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
    
    /* 连接SCT0的中断服务函数 */
    am_int_connect(INUM_SCT0, sct0_irq_handler, (void *)0);
    
    /* 使能SCT0中断 */
    am_int_enable(INUM_SCT0);
    
    /* 置CLRCTR位以清计数器为0 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* 预分频为0，使用系统时钟。 */
    amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
}


/** 
 * \brief 使能SCT为定时器(开始计数)
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \return 无
 */
void sct_timer_enable (amhw_sct_t *p_hw_sct)
{
    /* 清停止位，SCT开始运行 */
    amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
}

/** 
 * \brief  禁止SCT为定时器(停止计数)
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \return  无
 */
void sct_timer_disable (amhw_sct_t *p_hw_sct)
{
    /* 置停止位，SCT停止运行 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
}

/**
 * \brief 主函数入口
 */
int main (void)
{  
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_sct0_timing_init();

    AM_DBG_INFO("The demo for SCT timing:\r\n");
    AM_DBG_INFO("The led toggle in 10Hz \r\n");

    /* 使用SCT实现定时功能，中断频率为10Hz */
    sct_timer_init(AMHW_SCT0, 10);
    
    /* 使能SCT为定时器 */
    sct_timer_enable(AMHW_SCT0);
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_1_32bit_timing] */

/* end of file */

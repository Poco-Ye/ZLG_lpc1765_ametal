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
 * \brief SCT操作多态例程，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. PIO0_5(SCT_OUT6)引脚输出波形。
 *
 * \code
 *  |---         状态0        ---|--- 状态1 ---|--- 状态0      ......
 *             _____     _____     ___         __            ___
 *            |     |   |     |   |   |       |  |          |     ......
 *  __________|     |___|     |___|   |_______|  |__________|
 *
 *  0         10    15  18    23  26  3      10  12         10     (ms)
 *                              (状态1, 0)     (状态0, 0)
 *          事件 0  1   2      3   4   5      6  7
 * \endcode
 *
 * \note 连接PIO0_5(SCT_OUT6)引脚到逻辑分析仪，将会看到该波形，前10ms为低电平。
 *
 * \par 源代码
 * \snippet demo_hw_sct_multi_states.c src_hw_sct_multi_states
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_hw_sct_multi_states
 * \copydoc demo_hw_sct_multi_states.c
 */
 
/** [src_hw_sct_multi_states] */
#include "ametal.h"
#include "am_board.h"

#define   OUT_NUM       AMHW_SCT_OUT(6)       /**< \brief 使用SCT_OUT6 */

/**
 * \brief 初始化匹配寄存器
 *
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \param[in] num   : 匹配
 * \param[in] ms    : 匹配时间，单位：ms
 *
 * \return 无
 */
void sct_match_init (amhw_sct_t *p_hw_sct, uint32_t num, uint32_t ms)
{
    uint32_t ms_ticks = g_system_clkfreq / 1000;
    
    /* 将匹配捕捉寄存器配置为匹配功能 */
    amhw_sct_regmode_config(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(num), AMHW_SCT_MATCAP_MATCH);
    
    /* 设置匹配0和重载匹配值 */
    amhw_sct_mat_val_set(p_hw_sct, 
                         AMHW_SCT_MODE_UNIFY, 
                         num, 
                         ms_ticks * ms - 1); 
    
    amhw_sct_mat_reload_val_set(p_hw_sct, 
                                AMHW_SCT_MODE_UNIFY, 
                                num, 
                                ms_ticks * ms - 1);   
}

/**
 * \brief 初始化一个事件
 *
 * \param[in] p_sct     : 指向SCT寄存器块的指针。
 * \param[in] evt_num   : 事件。
 * \param[in] match_num : 匹配。
 * \param[in] state_num : 状态。
 * \param[in] state_ld  : 0, state_ev 加上状态；
 *                        1, the state_ev 加载为状态
 * \param[in] state_ev  : 该值改变状态。
 *
 * \return 无
 */
void sct_event_init(amhw_sct_t *p_hw_sct, 
                    uint32_t  evt_num, 
                    uint32_t  match_num, 
                    uint32_t  state_num, 
                    uint32_t  state_ld, 
                    uint32_t  state_ev)
{
    
    if(state_ld == 0) {
        state_ld = AMHW_SCT_EV_CTRL_STATELD_ADD;
    } else {
        state_ld = AMHW_SCT_EV_CTRL_STATELD_LOAD;
    }
    
    /* 设置事件0控制 */
    amhw_sct_event_ctrl(p_hw_sct, 
                        evt_num, 
                        AMHW_SCT_EV_CTRL_MATCHSEL(match_num)  | /* 事件关联匹配 */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH       | /* 使用指定匹配 */
                        state_ld                            | 
                        AMHW_SCT_EV_CTRL_STATEV(state_ev));      

    /* 使能事件产生 */
    amhw_sct_event_state_enable(p_hw_sct, evt_num, state_num);      
}

/**
 * \brief 使用SCT输出复杂波形。
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \return 无
 */
void sct_init (amhw_sct_t *p_hw_sct)
{

    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  | /* 作32位定时器      */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* 系统时钟做SCT时钟 */
    
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(0), 10);  /* 设置匹配0值为10ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(1), 15);  /* 设置匹配1值为15ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(2), 18);  /* 设置匹配2值为18ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(3), 23);  /* 设置匹配3值为23ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(4), 26);  /* 设置匹配4值为26ms */ 
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(5), 3);   /* 设置匹配5值为 3ms */ 
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(6), 12);  /* 设置匹配6值为12ms */ 
    
    amhw_sct_output_state_clr(p_hw_sct, OUT_NUM);   /* 清除输出 */ 
    
    /* 
     * 状态0事件控制
     */

    /* 事件0，关联匹配0，不改变状态值，输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(0), AMHW_SCT_MAT(0), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(0));  
   
    /* 事件1，关联匹配1，不改变状态值，清除输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(1), AMHW_SCT_MAT(1), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(1));  

    /* 事件2，关联匹配2，不改变状态值，输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(2), AMHW_SCT_MAT(2), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(2));      

    /* 事件3，关联匹配3，不改变状态值，清除输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(3), AMHW_SCT_MAT(3), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(3));  

    /* 事件4，关联匹配4，改变状态值为1，清除输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(4), AMHW_SCT_MAT(4), AMHW_SCT_STATE(0), 0, 1);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(4));

    /* 在状态0 中，事件4作为限制事件 */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_EVT(4));
    
    /*
     * 状态1事件控制
     */     
     
    /* 事件5，关联匹配5(3ms)，不改变状态值，清除输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(5), AMHW_SCT_MAT(5), AMHW_SCT_STATE(1), 0, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(5));  

    /* 事件6，关联匹配0(10ms)，不改变状态值，输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(6), AMHW_SCT_MAT(0), AMHW_SCT_STATE(1), 0, 0);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(6));  

    /* 事件7，关联匹配6(12ms)，改变状态值为0，清除输出 */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(7), AMHW_SCT_MAT(6), AMHW_SCT_STATE(1), AMHW_SCT_EV_CTRL_STATELD_LOAD, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(7));     
  
    /* 使能事件7限制计数器值 */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_EVT(7));     
  
    /* 设置当前状态值为0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_STATE(0));
    
    /* 使能事件0产生中断 */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
    
    /* 置CLRCTR位以清计数器为0 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* 预分频为0，使用系统时钟。 */
    amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
    
}

/**
 * \brief 使能SCT输出复杂波形
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \return 无
 */
void sct_enable (amhw_sct_t *p_hw_sct)
{
    /* 清停止位，SCT开始运行 */
    amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
}

/**
 * \brief 禁止SCT输出复杂波形
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \return 无
 */
void sct_disable (amhw_sct_t *p_hw_sct)
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
    
    AM_DBG_INFO("The demo for SCT in multi states \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) output waveform\r\n");
    
    am_gpio_pin_cfg(PIO0_5, PIO0_5_SCT0_OUT6);
    
    /* SCT实现定时器功能 */
    sct_init(AMHW_SCT0);
 
    sct_enable(AMHW_SCT0);
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_multi_states] */

/* end of file */

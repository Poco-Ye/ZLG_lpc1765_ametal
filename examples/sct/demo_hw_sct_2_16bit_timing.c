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
 * \brief SCT做2个16位定时器，实现定时功能，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. LED以10Hz的频率闪烁;
 *   2. PIO0_5引脚状态以8KHz的频率翻转，输出波形为4KHz。
 *
 * \par 源代码
 * \snippet demo_hw_sct_2_16bit_timing.c src_hw_sct_2_16bit_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_hw_sct_2_16bit_timing
 * \copydoc demo_hw_sct_2_16bit_timing.c
 */
 
/** [src_hw_sct_2_16bit_timing] */
#include "ametal.h"
#include "am_board.h"



#define   SCT_HANDLE_H        1            /**< \brief 用于操作高组定时器 */
#define   SCT_HANDLE_L        0            /**< \brief 用于操作高组定时器 */

/** 
 * \brief 计算16位定时器指定计时计数值的时，最佳的预分频值和匹配寄存器值。
 *
 * \param[in]  count   : 计数值。
 * \param[out] p_match : 指向定时器匹配值的指针。
 *
 * \return 计算出的8bits预分频值。
 */
uint32_t prescale_and_match_calculate (uint32_t count, uint32_t *p_match)
{
    uint32_t   match, min_remainder, prescale;
    uint32_t   result_quot, result_rem;
 
    min_remainder = count;
    prescale      = 1;
   *p_match       = 65536;

    /* 
     * 计数值最小为65536，
     * 预分频为1，匹配值等于计数值。
     */
    if (count <= 65536) {        
        prescale = 1;
        *p_match = count;  
        return prescale;        
    }    
    
    /* 检查匹配值，直到找到最好的 */
    for (match = 65536; match > 0; match--) {
        
        result_quot = count / match;
        result_rem  = count % match;
        
        /* 
         * 由于预分频宽度为8bits，result_quot的最大值为256，如果超过256，计数值
         * 将无法达到。
         */
        if (result_quot <= 256) {       
            if (result_rem == 0) {
            
                /* 发现最合适的预分频和匹配值 */
                prescale = result_quot;
                *p_match = match;
                break;
                
            } else if (result_rem < min_remainder) {
            
                /* 发现最合适的预分频和匹配值 */
                min_remainder = result_rem;
                prescale      = result_quot;
                *p_match      = match;
            }
        }
    }

    return prescale;
}

/** 
 * \brief  SCT0中断服务函数
 * \param[in] p_arg : 用户自定义参数，由 am_int_connect() 函数传递。
 * \return  无
 */
void sct0_irq_handler (void *p_arg)
{
    /* 事件0中断 */
    if (amhw_sct_event_flag_chk(AMHW_SCT0, AMHW_SCT_EVT(0)) == TRUE) {
        
        am_led_toggle(LED0);
        amhw_sct_event_flag_clr(AMHW_SCT0, AMHW_SCT_EVT(0));  /* 清标志 */
    }
    
    /* 事件1中断 */
    if (amhw_sct_event_flag_chk(AMHW_SCT0, AMHW_SCT_EVT(1)) == TRUE) {
        
        /* 翻转GPIO0_5引脚 */
        am_gpio_toggle(PIO0_5);
        
        amhw_sct_event_flag_clr(AMHW_SCT0, AMHW_SCT_EVT(1));  /* 清标志 */
    } 
}


/** 
 * \brief  使能定时器。
 *
 * \param[in] p_sct  : 指向SCT寄存器块的指针。
 * \param[in] handle : 高组定时器：#SCT_HANDLE_H，低组定时器：#SCT_HANDLE_L
 *
 * \return  无
 */
void sct_2_16bit_timer_enable (amhw_sct_t *p_hw_sct, uint8_t handle)
{
    if (handle == SCT_HANDLE_H) {
    
        /* 清停止位，SCT高组计数器开始运行 */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_H | AMHW_SCT_CTRL_HALT_H);  
      
    } else {
        
        /* 清停止位，SCT低组计数器开始运行 */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
    }        
}

/** 
 * \brief  禁能定时器
 *
 * \param[in] p_sct  : 指向SCT寄存器块的指针。
 * \param[in] handle : 高组定时器：#SCT_HANDLE_H，低组定时器：#SCT_HANDLE_L 。
 *
 * \return  无
 */
void sct_2_16bit_timer_disable (amhw_sct_t *p_hw_sct, uint8_t handle)
{
    if (handle == SCT_HANDLE_H) {
        
        /* 置停止位，SCT高组计数器停止运行 */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_H | AMHW_SCT_CTRL_HALT_H);  
      
    } else {
        
        /* 置停止位，SCT低组计数器停止运行 */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
    }   
}

/**
 * \brief 初始化定时器。
 *
 * \param[in] p_sct  : 指向SCT寄存器块的指针。
 * \param[in] handle : 高组定时器：#SCT_HANDLE_H，低组定时器：#SCT_HANDLE_L 。
 * \param[in] freq   : 定时器中断频率。
 *
 * \return 无
 *
 * \note 低组定时器使用事件0，高组定时器使用事件1.
 */
void sct_2_16bit_timer_init(amhw_sct_t *p_hw_sct, uint8_t handle, uint32_t freq)
{
    uint32_t counters;
    uint32_t prescale, match;
    
    amhw_sct_mode_t  sct_mode;
    uint32_t       event_num;
    uint32_t       event_ctl;
    
    if (handle == SCT_HANDLE_H) {
        
        sct_mode  = AMHW_SCT_MODE_SEPARATE_H;
        event_num = AMHW_SCT_EVT(1);           /* 高组定时器使用事件1 */
        
        /* 事件关联到匹配高16bits */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_H; 
        
    } else {
        sct_mode = AMHW_SCT_MODE_SEPARATE_L;
        event_num = AMHW_SCT_EVT(0);          /* 低组定时器使用事件0 */
        
        /* 事件关联到匹配低16bits */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_L;
    }
    
    /* 配置匹配/捕获寄存器0为16bits匹配寄存器*/
    amhw_sct_regmode_config(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), AMHW_SCT_MATCAP_MATCH);   

    /*
     * 计算16位定时器预分频和匹配值。例如，要产生10Hz的中断，系统时钟频率为
     * 100MHz，定时器计数值为：100 000 000 / 10 = 10 000 000，
     * 计数器为16bits，最大值为65536，故使用预分频：10 000 000 = 200 * 50000；
     * 匹配值为：50000；
     * 预分频值为：200。
     */
    counters = g_system_clkfreq / freq;
    
    prescale = prescale_and_match_calculate(counters, &match);
    
    prescale -= 1;
    match    -= 1;

    /* 如要改变预分频，应先停止SCT */
    if (prescale != amhw_sct_prescale_get(p_hw_sct, sct_mode)) {
        
        if (amhw_sct_halt_check(p_hw_sct, sct_mode) == TRUE ) {
            amhw_sct_prescale_set(p_hw_sct, sct_mode, prescale);
        } else {
            sct_2_16bit_timer_disable(p_hw_sct, handle);
            amhw_sct_prescale_set(p_hw_sct, sct_mode, prescale);
            sct_2_16bit_timer_enable(p_hw_sct, handle);
        }                        
    }
    
    if (amhw_sct_halt_check(p_hw_sct, sct_mode) == TRUE ) {      
        amhw_sct_mat_val_set(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), match);
    }
    amhw_sct_mat_reload_val_set(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), match);

    /* 高组定时器使用事件1，配置事件1 */
    amhw_sct_event_ctrl(p_hw_sct, 
                        event_num, 
                        event_ctl                     |  
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* 事件关联到匹配0     */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* 只能使用指定匹配    */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /* STATEV 值加上 STATE */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* 加 0，STATE没有改变 */

    /* 设置当前状态值为0 */
    amhw_sct_state_set(p_hw_sct, sct_mode, AMHW_SCT_STATE(0));

    /* 使能状态0中产生事件 */
    amhw_sct_event_state_enable(p_hw_sct, event_num, AMHW_SCT_STATE(0));

    /* 使能事件做计数器限定 */
    amhw_sct_event_limit_enable(p_hw_sct, sct_mode, event_num);
    
    /* 使能事件产生中断 */
    amhw_sct_event_int_enable(p_hw_sct, event_num);
    
    if (handle == SCT_HANDLE_H) {
    
        /* 设置CLRCTR位以清高组计数器为0 */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_H);
    } else {
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    }
}

/** 
 * \brief SCT实现定时功能。
 * \param[in] p_sct : 指向SCT寄存器块的指针。
 * \return 无
 */
void sct_2_16bit_init (amhw_sct_t *p_hw_sct)
{
    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_16BIT_COUNTER  | /* 定时器实现2个16bits定时器 */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* SCT时钟使用系统时钟       */    

    /* 使能低组定时器中断，中断频率为10Hz */
    sct_2_16bit_timer_init(p_hw_sct, SCT_HANDLE_L, 10);
    
    /* 使能高组定时器中断，中断频率为8KHz */
    sct_2_16bit_timer_init(p_hw_sct, SCT_HANDLE_H, 8000);
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
 
    AM_DBG_INFO("The demo for SCT operate as 2-16bit timer \r\n");
    AM_DBG_INFO("The LED0 blinking in 10Hz\r\n");
    AM_DBG_INFO("The PIO0_5 toggle in 8KHz, The output waveform is 4KHz\r\n");
    
    am_gpio_pin_cfg(PIO0_5, PIO0_5_GPIO | PIO0_5_OUTPUT);
    
    /* 使用SCT实现定时功能 */
    sct_2_16bit_init(AMHW_SCT0);

    am_int_connect(INUM_SCT0, sct0_irq_handler, (void *)0);
    
    /* 使能SCT0中断 */
    am_int_enable(INUM_SCT0);
    
    sct_2_16bit_timer_enable(AMHW_SCT0, SCT_HANDLE_L);   /* 使能低组定时器 */
    sct_2_16bit_timer_enable(AMHW_SCT0, SCT_HANDLE_H);   /* 使能高组定时器 */
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_2_16bit_timing] */

/* end of file */

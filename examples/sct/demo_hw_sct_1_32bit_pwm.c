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
 * \brief SCT1做32bits定时器输出PWM，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. PIO0_8(SCT_OUT1)输出4kHz的PWM，占空比为50%.
 *   2. PIO0_5(SCT_OUT6)输出4kHz的PWM，占空比为25%.
 *
 * - 注意：
 *   1. SCT使用32位计数器，只能产生一组独立的PWM，所有PWM输出使用同一频率。
 *      计数器和最大匹配值为：0xFFFFFFFF。
 *   2. SCT使用16位计数器，可以产生2组独立的PWM，每一组PWM的输出使用同一频率。
 *      计数器和最大匹配值为：0xFFFF。
 *
 * \par 源代码
 * \snippet demo_hw_sct_1_32bit_pwm.c src_hw_sct_1_32bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */

 
/**
 * \addtogroup demo_if_hw_sct_1_32bit_pwm
 * \copydoc demo_hw_sct_1_32bit_pwm.c
 */
 
/** [src_hw_sct_1_32bit_pwm] */
#include "ametal.h"
#include "am_board.h"


 
#define PWM0_MATCH_NUM   AMHW_SCT_MAT(1)   /**< \brief PWM0，使用匹配1 */
#define PWM0_OUTPUT_NUM     (1)            /**< \brief PWM0, SCT_OUT1  */

#define PWM1_MATCH_NUM   AMHW_SCT_MAT(2)   /**< \brief PWM1，使用匹配2 */
#define PWM1_OUTPUT_NUM     (6)            /**< \brief PWM1, SCT_OUT6  */

/** 
  * \brief 初始化SCT以输出PWM
  *
  *  初始化SCT为32bit定时器，使能MATCH0。
  *  
 * \param[in] p_sct : 指向SCT寄存器块的指针
  * \return 无
  */
void sct_pwm_init (amhw_sct_t *p_sct)
{
 
    /* 初始化匹配0为自动限定，以确定PWM的周期 */
    amhw_sct_config(p_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  | /* 使用32-bit定时器    */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK | /* SCT时钟使用系统时钟 */          
                    AMHW_SCT_CONFIG_AUTOLIMIT_L );   /* 匹配0为自动限定     */
   
    /* 将匹配捕捉寄存器配置为匹配功能 */
    amhw_sct_regmode_config(p_sct, 
                            AMHW_SCT_MODE_UNIFY,   
                            PWM1_MATCH_NUM,        
                            AMHW_SCT_MATCAP_MATCH);     
    
    amhw_sct_mat_val_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), 0);
    
    /* 设置事件0为PWM0 */
    amhw_sct_event_ctrl(p_sct, 
                        AMHW_SCT_EVT(0),                  /* 事件0                    */
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* 事件关联到匹配0          */   
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* 只能使用指定的匹配寄存器 */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV 值加上 STATE     */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* 加 0，STATE没有改变      */

    /* 使能状态0中事件0产生 */
    amhw_sct_event_state_enable(p_sct, AMHW_SCT_EVT(0), AMHW_SCT_STATE(0));    

    /* 置CLRCTR位，以清计数器为0 */
    amhw_sct_ctrl_set(p_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* 置当前状态值为0 */
    amhw_sct_state_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_STATE(0));
    
    /* 预分频为0，使用系统时钟。 */
    amhw_sct_prescale_set(p_sct, AMHW_SCT_MODE_UNIFY, 0);
}

/** 
 * \brief 初始化一路PWM
 *
 * \param[in] p_sct      : 指向SCT寄存器块的指针
 * \param[in] match_num  : 匹配编号。
 * \param[in] output_num : 输出通道0~7.
 *
 * \note 匹配0用于确定PWM周期，故match_num不能为AMHW_SCT_MAT(0)。
 */
void sct_pwm_out_init(amhw_sct_t *p_sct, uint32_t match_num, uint8_t output_num)
{
    uint8_t idx = (uint8_t)match_num;
    
    if (match_num == AMHW_SCT_MAT(0)) {
        return;
    }
    
    /* 将匹配捕捉寄存器配置为匹配功能 */
    amhw_sct_regmode_config(p_sct, 
                            AMHW_SCT_MODE_UNIFY,    /* SCT模式为UNIFY(1 32-bit 计数器) */
                            match_num,        
                            AMHW_SCT_MATCAP_MATCH); /* 操作匹配寄存器 */  
    
    /* 使用事件号同于匹配号 */
    amhw_sct_event_ctrl(p_sct, 
                        idx,                   
                        AMHW_SCT_EV_CTRL_MATCHSEL(idx)  |     
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* 只能使用指定的匹配寄存器 */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV 值加上 STATE     */  
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* 加 0，STATE没有改变      */   
    
    /* 使能状态0中事件0产生 */
    amhw_sct_event_state_enable(p_sct, idx, AMHW_SCT_STATE(0));
    
    /* 事件0输出PWM0 */
    amhw_sct_out_set_enable(p_sct, output_num, AMHW_SCT_EVT(0));
    
    /* 清PWM0输出 */
    amhw_sct_out_clr_enable(p_sct, output_num, idx);    
    
    /* 
     * 当有效时间等于周期将会产生冲突。在该种情况下，占空比为100%，
     * 故此时要置位输出。
     */
    amhw_sct_conflict_res_config(p_sct, output_num, AMHW_SCT_RES_SET_OUTPUT);   

    /* 置位和清零不依赖于方向 */
    amhw_sct_output_dir_ctrl(p_sct, output_num, AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT);
}

/**
 * \brief 配置PWM占空比时间
 *
 * \param[in] p_sct   : 指向SCT寄存器块的指针
 * \param[in] num     : 匹配号。
 * \param[in] duty_ns : 有效时间，单位：ns。
 *
 * \return 无
 *
 * \note 如果想让该配置马上生效，应在调用该函数前禁止SCT的PWM(sct_pwm_disable())，
 *       调用该函数后，再使能(sct_pwm_able())。如果SCT没有停止，该值将会写入
 *       重载匹配值，并在下一周期生效。
 */
void sct_pwm_duty_config(amhw_sct_t *p_sct, uint32_t num, uint32_t duty_ns)
{
    /* 将时间转换为占空有效时间 */
    uint32_t duty_c = (uint64_t)(duty_ns) * (g_system_clkfreq) / (uint64_t)1000000000; 
      
    /* 占空有效时间至少为1 */
    if (duty_c == 0) {
        duty_c = 1;
    }
    
    if (amhw_sct_halt_check(p_sct, AMHW_SCT_MODE_UNIFY) == TRUE ) {      
        amhw_sct_mat_val_set(p_sct, AMHW_SCT_MODE_UNIFY, num, duty_c - 1);
    }
    
    /* 设置重载匹配值 */
    amhw_sct_mat_reload_val_set(p_sct, AMHW_SCT_MODE_UNIFY, num, duty_c - 1); 
         
}

/** 
 * \brief 使能SCT的PWM，PWM输出。
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \return 无
 */
void sct_pwm_enable(amhw_sct_t *p_sct)
{
    /* 清除停止位，SCT开始运行 */
    amhw_sct_ctrl_clr(p_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);    
}

/** 
 * \brief 禁能SCT的PWM，PWM停止输出。
 * \param[in] p_sct : 指向SCT寄存器块的指针
 * \return 无
 */
void sct_pwm_disable(amhw_sct_t *p_sct)
{
    /* 置停止位，SCT停止运行 */
    amhw_sct_ctrl_set(p_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
}

/**
 * \brief 配置PWM周期。
 *
 * \param[in] p_sct     : 指向SCT寄存器块的指针
 * \param[in] period_ns : 周期，单位：ns
 *
 * \return 无
 *
 * \note 如果想让该配置马上生效，应在调用该函数前禁止SCT的PWM(sct_pwm_disable())，
 *       调用该函数后，再使能(sct_pwm_able())。
 */
void sct_pwm_period_config(amhw_sct_t *p_sct, uint32_t period_ns)
{
    /* 将时间转变为周期 */
    uint32_t period_c = (uint64_t)(period_ns) * (g_system_clkfreq) / (uint64_t)1000000000; 
    
    /* 周期至少为1 */
    if (period_c == 0) {
        period_c = 1;
    }
    
    if (amhw_sct_halt_check(p_sct, AMHW_SCT_MODE_UNIFY) == TRUE ) {      
        amhw_sct_mat_val_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), period_c - 1);
    }
    amhw_sct_mat_reload_val_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), period_c - 1);
}

/**
 * \brief 主函数入口。
 */
int main (void)
{  
    /* 板级初始化 */
    am_board_init();
    
    /* 平台初始化 */
    amhw_plfm_sct0_pwm_init();

    AM_DBG_INFO("The demo for SCT output PWM:\r\n");
    AM_DBG_INFO("The PIO0_8(SCT_OUT1) PWM: freq is 4kHz, The duty ratio is 50% \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) PWM: freq is 4kHz, The duty ratio is 25% \r\n");
    
    am_gpio_pin_cfg(PIO0_8, PIO0_8_SCT0_OUT1);    
    am_gpio_pin_cfg(PIO0_5, PIO0_5_SCT0_OUT6);

    sct_pwm_init(AMHW_SCT0);
    
    /* PWM0初始化 */
    sct_pwm_out_init(AMHW_SCT0, PWM0_MATCH_NUM, PWM0_OUTPUT_NUM );  
    
    /* PWM1初始化 */
    sct_pwm_out_init(AMHW_SCT0, PWM1_MATCH_NUM, PWM1_OUTPUT_NUM );
    
    /* 设置周期为 250000ns(4KHz) */
    sct_pwm_period_config(AMHW_SCT0, 250000);
    
    /* 设置PWM0占空比 */
    sct_pwm_duty_config(AMHW_SCT0, PWM0_MATCH_NUM, 125000);          
    
    /* 设置PWM1占空比 */
    sct_pwm_duty_config(AMHW_SCT0, PWM1_MATCH_NUM, 62500);
    
    /* 使能SCT0，输出PWM */
    sct_pwm_enable(AMHW_SCT0);  
 
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_1_32bit_pwm] */

/* end of file */

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
 * \brief SCT 2个16bits定时器输出PWM，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. PIO0_13(SCT_OUT4)输出4kHz的PWM，占空比为50%；
 *   2. PIO0_14(SCT_OUT5)输出1kHz的PWM，占空比为25%。
 *
 * - 注意：
 *   1. SCT使用16位计数器，可以产生2组独立的PWM，每一组PWM的输出使用同一频率。
 *      计数器和最大匹配值为：0xFFFF。
 *   2. SCT使用32位计数器，只能产生一组独立的PWM，所有PWM输出使用同一频率。
 *      计数器和最大匹配值为：0xFFFFFFFF。
 *
 * \par 源代码
 * \snippet demo_hw_sct_2_16bit_pwm.c src_hw_sct_2_16bit_pwm
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_hw_sct_2_16bit_pwm
 * \copydoc demo_hw_sct_2_16bit_pwm.c
 */

/** [src_hw_sct_2_16bit_pwm] */
#include "ametal.h"
#include "am_board.h"


#define   SCT_HANDLE_H        1              /**< \brief 用于操作高组 */
#define   SCT_HANDLE_L        0              /**< \brief 用于操作低组 */

/**
 * \name 定义低组PWM
 * @{
 */
 
#define PWM_L_0_MATCH_NUM    AMHW_SCT_MAT(1) /**< \brief 低组PWM0使用匹配1低位 */
#define PWM_L_0_EVENT_NUM    AMHW_SCT_EVT(1) /**< \brief 低组PWM0使用事件1     */
#define PWM_L_0_OUTPUT_NUM   AMHW_SCT_OUT(1) /**< \brief 低组PWM0，SCT_OUT1    */

/** @} */

/**
 * \name 定义高组PWM
 * @{
 */

#define PWM_H_0_MATCH_NUM    AMHW_SCT_MAT(1) /**< \brief 高组PWM0使用匹配1高位 */
#define PWM_H_0_EVENT_NUM    AMHW_SCT_EVT(2) /**< \brief 高组PWM0使用事件2     */
#define PWM_H_0_OUTPUT_NUM   AMHW_SCT_OUT(6) /**< \brief 高组PWM0, SCT_OUT6    */

/** @} */

/**
 * \brief 计算16位定时器指定计时计数值的时，最佳的预分频值和匹配寄存器值。
 *
 * \param[in]  count   : 计数值
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
        prescale      = 1;
        *p_match      = count;  
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
 * \brief 初始化SCT产生PWM。
 *
 * \param[in] p_sct  : 指向SCT寄存器块的指针。
 * \param[in] handle : 高组：#SCT_HANDLE_H，低组：#SCT_HANDLE_L。
 *
 * \return 无
 *
 * \note 高组使用事件12，匹配0的高16位 bits设置周期。
 *       高组使用事件0，匹配0的低16位 bits设置周期。
 */
void sct_2_16bit_pwm_init (amhw_sct_t *p_hw_sct, uint8_t handle)
{
    amhw_sct_mode_t  sct_mode;
    uint32_t         event_num;
    uint32_t         event_ctl;
    
    if (handle == SCT_HANDLE_H) {
        
        sct_mode  = AMHW_SCT_MODE_SEPARATE_H;
        event_num = AMHW_SCT_EVT(12);        /* 高组使用事件12 */
        
        /* 事件关联匹配高16位 */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_H; 
        
    } else {
        sct_mode = AMHW_SCT_MODE_SEPARATE_L;
        event_num = AMHW_SCT_EVT(0);         /* 低组使用事件0 */
        
        /* 事件关联匹配低16位 */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_L;
    }
    
    /* 配置匹配/捕获寄存器为匹配寄存器 */
    amhw_sct_regmode_config(p_hw_sct, 
                            sct_mode,  
                            AMHW_SCT_MAT(0), 
                            AMHW_SCT_MATCAP_MATCH);

    amhw_sct_mat_val_set(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), 0);
    
 
    /* 配置事件0 */
    amhw_sct_event_ctrl(p_hw_sct, 
                        event_num, 
                        event_ctl                       | /* 选择低状态和匹配寄存器 */
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* 事件关联匹配0          */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* 只能使用指定匹配       */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV 值加上 STATE   */
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* 加 0，STATE没有改变    */       
   
    /* 使能状态0产生事件 */
    amhw_sct_event_state_enable(p_hw_sct, event_num, AMHW_SCT_STATE(0));

    /* 设置当前状态值为0 */
    amhw_sct_state_set(p_hw_sct, sct_mode, AMHW_SCT_STATE(0));
    
    if (handle == SCT_HANDLE_H) {
    
    /* 置CLRCTR位以清高组计数器为0 */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_H);
    } else {
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    }
}

/** 
 * \brief 初始化SCT为2组PWM输出
 * \param[in] p_sct : 指向SCT寄存器块的指针。
 * \return 无
 */
void sct_pwm_init (amhw_sct_t *p_hw_sct)
{
    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_16BIT_COUNTER  | /* 定时器分为2个16位定时器 */
                    AMHW_SCT_CONFIG_AUTOLIMIT_L    | /* 低组匹配0自动限制       */
                    AMHW_SCT_CONFIG_AUTOLIMIT_H    | /* 高组匹配0自动限制       */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* SCT时钟使用系统时钟     */    

    sct_2_16bit_pwm_init(p_hw_sct, SCT_HANDLE_L);
    sct_2_16bit_pwm_init(p_hw_sct, SCT_HANDLE_H);
}

/** 
 * \brief 使能SCT输出PWM
 *
 * \param[in] p_sct  : 指向SCT寄存器块的指针。
 * \param[in] handle : 高组：#SCT_HANDLE_H，低组：#SCT_HANDLE_L。
 *
 * \return  无
 */
void sct_2_16bit_pwm_enable (amhw_sct_t *p_hw_sct, uint8_t handle)
{
    if (handle == SCT_HANDLE_H) {
        
        amhw_sct_ctrl_halt_to_stop(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H); 
         
        /* 清除停止位，SCT高组计数器开始运行 */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_H);
               
        if (amhw_sct_halt_check(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L) == TRUE) {
            
            /* 低组不可休息，建议改为停止，否则高组不能输出PWM */
            amhw_sct_ctrl_halt_to_stop(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L);
        }
      
    } else {
        
        /* 清除停止位，SCT低组计数器开始运行 */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
    }        
}

/** 
 * \brief 禁止SCT输出PWM。
 *
 * \param[in] p_sct  : 指向SCT寄存器块的指针。
 * \param[in] handle : 高组：#SCT_HANDLE_H，低组：#SCT_HANDLE_L。
 *
 * \return  无
 */
void sct_2_16bit_pwm_disable(amhw_sct_t *p_hw_sct, uint8_t handle)
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
 * \brief 初始化输出一路PWM。
 *
 * \param[in] p_sct      : 指向SCT寄存器块的指针。
 * \param[in] handle     : 高组：#SCT_HANDLE_H，低组：#SCT_HANDLE_L。
 * \param[in] match_num  : 匹配编号。
 * \param[in] event_num  : 事件编号。
 * \param[in] output_num : 输出通道，为0~7之间。
 *
 * \note 匹配0用于确定周期，match_num不可使用AMHW_SCT_MAT(0)。
 *
 */
void sct_pwm_out_init(amhw_sct_t *p_hw_sct, 
                      uint8_t   handle, 
                      uint32_t  match_num, 
                      uint32_t  event_num, 
                      uint8_t   output_num)
{
    amhw_sct_mode_t sct_mode;
    uint32_t hevent_mode;
    
    /* 匹配0使用自动限制 */
    if (match_num == AMHW_SCT_MAT(0)) {
        return;
    }
    
    /* 事件0和事件12用于设置输出 */
    if ((event_num == AMHW_SCT_EVT(0)) || (event_num == AMHW_SCT_EVT(0))) {
        return;
    }
    
    if (handle == SCT_HANDLE_H) {
        sct_mode    = AMHW_SCT_MODE_SEPARATE_H;
        hevent_mode = AMHW_SCT_EV_CTRL_HEVENT_H;
    } else {
        sct_mode    = AMHW_SCT_MODE_SEPARATE_L;
        hevent_mode = AMHW_SCT_EV_CTRL_HEVENT_L;
    }
    
    /* 将匹配捕捉寄存器配置为匹配功能 */
    amhw_sct_regmode_config(p_hw_sct, sct_mode, match_num, AMHW_SCT_MATCAP_MATCH);       
                  
    /* 配置事件 */
    amhw_sct_event_ctrl(p_hw_sct, 
                        event_num, 
                        hevent_mode                         |  
                        AMHW_SCT_EV_CTRL_MATCHSEL(match_num)  |     
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH       |  
                        AMHW_SCT_EV_CTRL_STATELD_ADD          |  
                        AMHW_SCT_EV_CTRL_STATEV(0));             
    
    /* 使能状态0中产生事件 */
    amhw_sct_event_state_enable(p_hw_sct, event_num, AMHW_SCT_STATE(0));
    
    if (sct_mode == AMHW_SCT_MODE_SEPARATE_H) {
    
        /* 设置事件12为PWM输出 */
        amhw_sct_out_set_enable(p_hw_sct, output_num, AMHW_SCT_EVT(12));        
    } else {
    
        /* 设置事件0为PWM输出 */
        amhw_sct_out_set_enable(p_hw_sct, output_num, AMHW_SCT_EVT(0));            
    }

    /* 事件清除PWM输出 */
    amhw_sct_out_clr_enable(p_hw_sct, output_num, event_num);    
    
    /* 
     * 当有效时间等于周期将会产生冲突。在该种情况下，占空比为100%，
     * 故此时要置位输出。
     */
    amhw_sct_conflict_res_config(p_hw_sct, output_num, AMHW_SCT_RES_SET_OUTPUT);   

    /* 置位和清零不依赖于方向 */
    amhw_sct_output_dir_ctrl(p_hw_sct, output_num, AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT);
}

/**
 * \brief 配置PWM周期
 *
 * \param[in] p_sct     : 指向SCT寄存器块的指针。
 * \param[in] handle    : 高组：#SCT_HANDLE_H，低组：#SCT_HANDLE_L。
 * \param[in] period_ns : 周期，单位为：ns。
 *
 * \return 无
 *
 * \note 如果想让该配置马上生效，应在调用该函数前禁止SCT的PWM，
 *       调用该函数后，再使能。
 */
void sct_pwm_period_config(amhw_sct_t *p_hw_sct, uint8_t handle, uint32_t period_ns)
{
    /* 转换时间为周期 */
    uint32_t period_c = (uint64_t)(period_ns) * (g_system_clkfreq) / (uint64_t)1000000000; 
    uint32_t prescale = 0;
    uint32_t match    = 0;
    
    amhw_sct_mode_t sct_mode;
    
    if (handle == SCT_HANDLE_H) {
        sct_mode = AMHW_SCT_MODE_SEPARATE_H;
    } else {
        sct_mode = AMHW_SCT_MODE_SEPARATE_L;
    }
    
    /* 周期至少为1 */
    if (period_c == 0) {
        period_c = 1;
    }    

    /* 
     * 计数器最大计数为：65536 * 256(预分频), 最大时间为：
     * 65536 / (g_system_clkfreq / 256) = 65536 * 256 / g_system_clkfreq.
     *
     * 在100MHz时，最大时间为：256 * 65536 / 100 us =  167772 us
     * 在12MHz时，最大时间为：256 * 65536 /  12 us = 1398101 us   
     */
    if (period_c >= 256 * 65536) {
        period_c = 256 * 65536;     /* 最大周期为256 * 65536 */
    }
    
    /* 计算预分频和匹配值 */
    prescale = prescale_and_match_calculate(period_c, &match);    
    
    prescale -= 1;
    
    if (prescale != amhw_sct_prescale_get(p_hw_sct, sct_mode)) {
        
        if (amhw_sct_halt_check(p_hw_sct, sct_mode) == TRUE ) {
            amhw_sct_prescale_set(p_hw_sct, sct_mode, prescale);
        
        } else {
            sct_2_16bit_pwm_disable(p_hw_sct, handle);
            amhw_sct_prescale_set(p_hw_sct, sct_mode, prescale);
            sct_2_16bit_pwm_enable(p_hw_sct, handle);
        }                        
    }
    
    if (amhw_sct_halt_check(p_hw_sct, sct_mode) == TRUE ) {      
        amhw_sct_mat_val_set(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), match - 1);
    }
    amhw_sct_mat_reload_val_set(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), match - 1);
}

/**
 * \brief 配置PWM有效时间（占空比）
 *
 * \param[in] p_sct   : 指向SCT寄存器块的指针。
 * \param[in] handle  : 高组：#SCT_HANDLE_H，低组：#SCT_HANDLE_L。
 * \param[in] num     : 匹配编号。
 * \param[in] duty_ns : 有效时间，单位：ns。
 *
 * \return 无
 *
 * \note 如果想让该配置马上生效，应在调用该函数前禁止SCT的PWM(sct_pwm_disable())，
 *       调用该函数后，再使能(sct_pwm_able())。如果SCT没有停止，该值将会写入
 *       重载匹配值，并在下一周期生效。
 */
void sct_pwm_duty_config (amhw_sct_t *p_hw_sct, uint8_t handle, uint32_t num, uint32_t duty_ns)
{
    uint32_t clkfreq;   
    uint32_t duty_c;
    
    amhw_sct_mode_t sct_mode;
    
    if (handle == SCT_HANDLE_H) {
        sct_mode = AMHW_SCT_MODE_SEPARATE_H;
    
    } else {
        sct_mode = AMHW_SCT_MODE_SEPARATE_L;
    }
    
    /* 将时间转换为周期 */
    clkfreq = g_system_clkfreq / (amhw_sct_prescale_get(p_hw_sct, sct_mode) + 1);
    
    duty_c = (uint64_t)(duty_ns) * (clkfreq) / (uint64_t)1000000000; 
 
    /* 占空有效时间最小为1 */
    if (duty_c == 0) {
        duty_c = 1;
    }
       
    if (duty_c > 65536) {
        duty_c = 65536;
    }
    
    if (amhw_sct_halt_check(p_hw_sct, AMHW_SCT_MODE_UNIFY) == TRUE ) {      
        amhw_sct_mat_val_set(p_hw_sct, sct_mode, num, duty_c - 1);
    }
    
    /* 设置重载匹配值 */
    amhw_sct_mat_reload_val_set(p_hw_sct, sct_mode, num, duty_c - 1);  
}


/**
 * \brief 主函数入口
 */
int main (void)
{  
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_sct0_pwm_init();
    
    AM_DBG_INFO("The demo for SCT output PWM:\r\n");
    AM_DBG_INFO("The PIO0_8(SCT_OUT1) PWM: freq is 4kHz, The duty ratio is 50% \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) PWM: freq is 1kHz, The duty ratio is 25% \r\n");
    
    am_gpio_pin_cfg(PIO0_8, PIO0_8_SCT0_OUT1);
    am_gpio_pin_cfg(PIO0_5, PIO0_5_SCT0_OUT6);
    
    /* 初始化SCT为2组PWM输出 */
    sct_pwm_init(AMHW_SCT0);
    
    /* SCT_OUT5，低组 */
    sct_pwm_out_init(AMHW_SCT0, 
                     SCT_HANDLE_L,         /* 低组   */
                     PWM_L_0_MATCH_NUM,    /* 匹配号 */
                     PWM_L_0_EVENT_NUM,    /* 事件号 */
                     PWM_L_0_OUTPUT_NUM);  /* 输出号 */

    /* SCT_OUT7，高组 */
    sct_pwm_out_init(AMHW_SCT0, 
                     SCT_HANDLE_H, 
                     PWM_H_0_MATCH_NUM, 
                     PWM_H_0_EVENT_NUM, 
                     PWM_H_0_OUTPUT_NUM);
    
    /* 
     * 低组周期为250 000ns(4KHz)，
     * 在100MHz，最大周期为：256 * 65536 / 100 us =  167772 us
     */
    sct_pwm_period_config(AMHW_SCT0, SCT_HANDLE_L, 250000);
    
    /* 高组周期为1000 000ns(1KHz) */
    sct_pwm_period_config(AMHW_SCT0, SCT_HANDLE_H, 1000000);
    
    /* 低组PWM0有效时间 */
    sct_pwm_duty_config(AMHW_SCT0, SCT_HANDLE_L, PWM_L_0_MATCH_NUM, 125000);
    
    /* 高组PWM0有效时间 */
    sct_pwm_duty_config(AMHW_SCT0, SCT_HANDLE_H, PWM_H_0_MATCH_NUM, 250000);

    sct_2_16bit_pwm_enable(AMHW_SCT0, SCT_HANDLE_L);       /* 使能低组PWM */        
    sct_2_16bit_pwm_enable(AMHW_SCT0, SCT_HANDLE_H);       /* 使能高组PWM */  
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_2_16bit_pwm] */

/* end of file */

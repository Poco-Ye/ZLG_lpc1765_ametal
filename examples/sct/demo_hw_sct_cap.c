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
 * \brief SCT做32位定时器实现捕获功能的例程，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. 输出利用捕获功能得到的PWM信号的周期和频率。
 *
 * - 注意：
 *   1. PIO0_29引脚用于定时器0输出PWM(PIO0_29)；
 *   2. PIO0_25 引脚是SCT输入通道2做输入捕获；
 *   3. 连接PIO0_29引脚和PIO0_25引脚，利用输出捕获功能实现PWM频率的测量。
 *
 * \par 源代码
 * \snippet demo_hw_sct_cap.c src_hw_sct_cap
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_hw_sct_cap
 * \copydoc demo_hw_sct_cap.c
 */
 
/** [src_hw_sct_cap] */
#include "ametal.h"
#include "am_board.h"


 
/** \brief 上升沿捕获 */
#define SCT_CAP_TRIGGER_RISE  1

/** \brief 下降沿捕获 */
#define SCT_CAP_TRIGGER_FALL  2

/** 
 * \brief 初始化SCT以输出PWM。
 *
 *  初始化SCT实现32位定时器功能，使能MATCH0为自动限制。
 *  
 * \param[in] p_sct : 指向SCT寄存器块的指针。
 * \return 无
 */
void sct_cap_init (amhw_sct_t *p_hw_sct)
{
    /* 置停止位，SCT停止运行 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
    
    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  |
                    AMHW_SCT_CONFIG_INSYNC_ALL     |
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK ); 
  
    /* 置CLRCTR位以清计数器为0 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* 设置当前状态值为0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_STATE(0));
    
    /* 预分频为0，使用系统时钟。 */
    amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
}

/** 
 * \brief 初始化一路PWM输出。
 *
 * \param[in] p_sct    : 指向SCT寄存器块的指针。
 * \param[in] cap_num  : 捕获编号。
 * \param[in] cap_edge : 捕获边沿选择 (#SCT_CAP_TRIGGER_RISE) 或 (#SCT_CAP_TRIGGER_FALL)
 * 
 * \return  无
 */
void sct_cap_chan_config (amhw_sct_t *p_hw_sct, uint32_t cap_num, uint8_t cap_edge)
{
    uint32_t  iocond;
    
    if (cap_edge == SCT_CAP_TRIGGER_RISE) {
        iocond = AMHW_SCT_EV_CTRL_IOCOND_RISE;
    } else {
        iocond = AMHW_SCT_EV_CTRL_IOCOND_FALL;
    }

    /* 将匹配捕捉寄存器配置为捕获功能 */
    amhw_sct_regmode_config(p_hw_sct, 
                            AMHW_SCT_MODE_UNIFY, 
                            AMHW_SCT_MAT(cap_num), 
                            AMHW_SCT_MATCAP_CAPTURE);
    
    /* 使能事件原因 CAPn _L (UNIFY = 0) 寄存器重加载 */
    amhw_sct_cap_ctrl(p_hw_sct, 
                      AMHW_SCT_MODE_UNIFY, 
                      AMHW_SCT_CAP(cap_num), 
                      AMHW_SCT_EVT(cap_num), 
                      TRUE);
    
    /* 使用事件编号同于通道号。事件只能是IO条件，不能用匹配寄存器。*/
    amhw_sct_event_ctrl(p_hw_sct, 
                        AMHW_SCT_EVT(cap_num), 
                        AMHW_SCT_EV_CTRL_OUTSEL_INPUT    |
                        AMHW_SCT_EV_CTRL_IOSEL(cap_num)  |
                        iocond                           |
                        AMHW_SCT_EV_CTRL_COMBMODE_IO     | /* 使用指定IO           */
                        AMHW_SCT_EV_CTRL_STATELD_ADD     | /*  STATEV 值加上 STATE */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));       /* 加 0，STATE没有改变  */

}

/**
 * \brief 配置PWM有效时间（占空比）。
 *
 * \param[in] p_sct   : 指向SCT寄存器块的指针。
 * \param[in] num     : 配置PWM的匹配编号。
 * \param[in] duty_ns : 有效时间，单位：ns。
 *
 * \return 无
 *
 * \note 如果想让该配置马上生效，应在调用该函数前禁止SCT的PWM(sct_pwm_disable())，
 *       调用该函数后，再使能(sct_pwm_able())。如果SCT没有停止，该值将会写入
 *       重载匹配值，并在下一周期生效。
 */
static int sct_cap_chan_enable (amhw_sct_t *p_hw_sct, uint32_t cap_num)
{
    /* 使能状态0中事件0产生 */
    amhw_sct_event_state_enable(p_hw_sct, AMHW_SCT_EVT(cap_num), AMHW_SCT_STATE(0));

    /* 清除事件标志 */
    amhw_sct_event_flag_clr(p_hw_sct, AMHW_SCT_EVT(cap_num));
        
    /* 使能事件0产生中断 */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(cap_num));
    
    amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
    
    return AM_OK;
}


volatile bool_t   g_flag    = FALSE;   /**< \brief 捕获标志 */
volatile uint32_t g_time_ns = 0;       /**< \brief 捕获计数 */

/** 
 * \brief SCT捕获中断服务函数。
 * \param[in] p_arg : 用户自定义参数，由 am_int_connect() 函数传递。
 * \return  无
 */
void sct_cap_isr (void *p_arg)
{
    static uint32_t count1;
    static bool_t   first    = TRUE;
    amhw_sct_t     *p_hw_sct = (amhw_sct_t *)p_arg;
    uint32_t        cap_val;
    
    /* 捕获通道2使用事件2 */
    if (amhw_sct_event_flag_chk(p_hw_sct, AMHW_SCT_EVT(2)) == TRUE ) {
        
        cap_val = amhw_sct_cap_val_get(p_hw_sct, AMHW_SCT_MODE_UNIFY, 2);
        
        if (g_flag == FALSE) {
        
            if (first == TRUE) {
                count1 = cap_val;
                first  = FALSE;
            } else {
                
                /* 转换计数值为时间  */
                g_time_ns = 1000000000 / g_system_clkfreq * (cap_val - count1);
               
                first = TRUE;
                
                /* 标志为TRUE，表明捕获计数完成 */
                g_flag = TRUE;
            }
        }
        
        /* 清事件标志 */
        amhw_sct_event_flag_clr(p_hw_sct, AMHW_SCT_EVT(2));
    }
}

/**
 * \brief 主函数入口。
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    uint32_t         freq;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_timer0_pwm_init();
    amhw_plfm_sct0_cap_init();
    
    AM_DBG_INFO("The SCT demo for CAP service\r\n");
    
    /* 使用定时器0输出一路PWM */
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer0_pwm_dev, 
                                            &g_timer0_pwm_devinfo);
    
    /* 通道1使用PIO0_29，在 amdr_hwconfig_sct_pwm.c 中配置 */
    am_pwm_config(timer0_pwm_handle, 1, 5000000 / 2, 5000000); /* 频率为2KHz */
    am_pwm_enable(timer0_pwm_handle, 1);
    
    am_int_connect(INUM_SCT0, sct_cap_isr, (void *)AMHW_SCT0);
    am_int_enable(INUM_SCT0);

    sct_cap_init(AMHW_SCT0);
    sct_cap_chan_config(AMHW_SCT0, 2, SCT_CAP_TRIGGER_RISE);
    sct_cap_chan_enable(AMHW_SCT0, 2);
    
    
    while (1) {
        if (g_flag == TRUE) {
            
            freq = 1000000000 / g_time_ns;
            AM_DBG_INFO("The period is %d ns, The freq is %d Hz \r\n", g_time_ns, freq);
            g_flag = FALSE;   
        }
        
        am_mdelay(200);
    }
}

/** [src_hw_sct_cap] */

/* end of file */

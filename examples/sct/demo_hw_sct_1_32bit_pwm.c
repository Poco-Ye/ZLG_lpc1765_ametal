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
 * \brief SCT1��32bits��ʱ�����PWM��ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_8(SCT_OUT1)���4kHz��PWM��ռ�ձ�Ϊ50%.
 *   2. PIO0_5(SCT_OUT6)���4kHz��PWM��ռ�ձ�Ϊ25%.
 *
 * - ע�⣺
 *   1. SCTʹ��32λ��������ֻ�ܲ���һ�������PWM������PWM���ʹ��ͬһƵ�ʡ�
 *      �����������ƥ��ֵΪ��0xFFFFFFFF��
 *   2. SCTʹ��16λ�����������Բ���2�������PWM��ÿһ��PWM�����ʹ��ͬһƵ�ʡ�
 *      �����������ƥ��ֵΪ��0xFFFF��
 *
 * \par Դ����
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


 
#define PWM0_MATCH_NUM   AMHW_SCT_MAT(1)   /**< \brief PWM0��ʹ��ƥ��1 */
#define PWM0_OUTPUT_NUM     (1)            /**< \brief PWM0, SCT_OUT1  */

#define PWM1_MATCH_NUM   AMHW_SCT_MAT(2)   /**< \brief PWM1��ʹ��ƥ��2 */
#define PWM1_OUTPUT_NUM     (6)            /**< \brief PWM1, SCT_OUT6  */

/** 
  * \brief ��ʼ��SCT�����PWM
  *
  *  ��ʼ��SCTΪ32bit��ʱ����ʹ��MATCH0��
  *  
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
  * \return ��
  */
void sct_pwm_init (amhw_sct_t *p_sct)
{
 
    /* ��ʼ��ƥ��0Ϊ�Զ��޶�����ȷ��PWM������ */
    amhw_sct_config(p_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  | /* ʹ��32-bit��ʱ��    */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK | /* SCTʱ��ʹ��ϵͳʱ�� */          
                    AMHW_SCT_CONFIG_AUTOLIMIT_L );   /* ƥ��0Ϊ�Զ��޶�     */
   
    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_sct_regmode_config(p_sct, 
                            AMHW_SCT_MODE_UNIFY,   
                            PWM1_MATCH_NUM,        
                            AMHW_SCT_MATCAP_MATCH);     
    
    amhw_sct_mat_val_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), 0);
    
    /* �����¼�0ΪPWM0 */
    amhw_sct_event_ctrl(p_sct, 
                        AMHW_SCT_EVT(0),                  /* �¼�0                    */
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* �¼�������ƥ��0          */   
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* ֻ��ʹ��ָ����ƥ��Ĵ��� */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV ֵ���� STATE     */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* �� 0��STATEû�иı�      */

    /* ʹ��״̬0���¼�0���� */
    amhw_sct_event_state_enable(p_sct, AMHW_SCT_EVT(0), AMHW_SCT_STATE(0));    

    /* ��CLRCTRλ�����������Ϊ0 */
    amhw_sct_ctrl_set(p_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* �õ�ǰ״ֵ̬Ϊ0 */
    amhw_sct_state_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_STATE(0));
    
    /* Ԥ��ƵΪ0��ʹ��ϵͳʱ�ӡ� */
    amhw_sct_prescale_set(p_sct, AMHW_SCT_MODE_UNIFY, 0);
}

/** 
 * \brief ��ʼ��һ·PWM
 *
 * \param[in] p_sct      : ָ��SCT�Ĵ������ָ��
 * \param[in] match_num  : ƥ���š�
 * \param[in] output_num : ���ͨ��0~7.
 *
 * \note ƥ��0����ȷ��PWM���ڣ���match_num����ΪAMHW_SCT_MAT(0)��
 */
void sct_pwm_out_init(amhw_sct_t *p_sct, uint32_t match_num, uint8_t output_num)
{
    uint8_t idx = (uint8_t)match_num;
    
    if (match_num == AMHW_SCT_MAT(0)) {
        return;
    }
    
    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_sct_regmode_config(p_sct, 
                            AMHW_SCT_MODE_UNIFY,    /* SCTģʽΪUNIFY(1 32-bit ������) */
                            match_num,        
                            AMHW_SCT_MATCAP_MATCH); /* ����ƥ��Ĵ��� */  
    
    /* ʹ���¼���ͬ��ƥ��� */
    amhw_sct_event_ctrl(p_sct, 
                        idx,                   
                        AMHW_SCT_EV_CTRL_MATCHSEL(idx)  |     
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* ֻ��ʹ��ָ����ƥ��Ĵ��� */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV ֵ���� STATE     */  
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* �� 0��STATEû�иı�      */   
    
    /* ʹ��״̬0���¼�0���� */
    amhw_sct_event_state_enable(p_sct, idx, AMHW_SCT_STATE(0));
    
    /* �¼�0���PWM0 */
    amhw_sct_out_set_enable(p_sct, output_num, AMHW_SCT_EVT(0));
    
    /* ��PWM0��� */
    amhw_sct_out_clr_enable(p_sct, output_num, idx);    
    
    /* 
     * ����Чʱ��������ڽ��������ͻ���ڸ�������£�ռ�ձ�Ϊ100%��
     * �ʴ�ʱҪ��λ�����
     */
    amhw_sct_conflict_res_config(p_sct, output_num, AMHW_SCT_RES_SET_OUTPUT);   

    /* ��λ�����㲻�����ڷ��� */
    amhw_sct_output_dir_ctrl(p_sct, output_num, AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT);
}

/**
 * \brief ����PWMռ�ձ�ʱ��
 *
 * \param[in] p_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] num     : ƥ��š�
 * \param[in] duty_ns : ��Чʱ�䣬��λ��ns��
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹSCT��PWM(sct_pwm_disable())��
 *       ���øú�������ʹ��(sct_pwm_able())�����SCTû��ֹͣ����ֵ����д��
 *       ����ƥ��ֵ��������һ������Ч��
 */
void sct_pwm_duty_config(amhw_sct_t *p_sct, uint32_t num, uint32_t duty_ns)
{
    /* ��ʱ��ת��Ϊռ����Чʱ�� */
    uint32_t duty_c = (uint64_t)(duty_ns) * (g_system_clkfreq) / (uint64_t)1000000000; 
      
    /* ռ����Чʱ������Ϊ1 */
    if (duty_c == 0) {
        duty_c = 1;
    }
    
    if (amhw_sct_halt_check(p_sct, AMHW_SCT_MODE_UNIFY) == TRUE ) {      
        amhw_sct_mat_val_set(p_sct, AMHW_SCT_MODE_UNIFY, num, duty_c - 1);
    }
    
    /* ��������ƥ��ֵ */
    amhw_sct_mat_reload_val_set(p_sct, AMHW_SCT_MODE_UNIFY, num, duty_c - 1); 
         
}

/** 
 * \brief ʹ��SCT��PWM��PWM�����
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \return ��
 */
void sct_pwm_enable(amhw_sct_t *p_sct)
{
    /* ���ֹͣλ��SCT��ʼ���� */
    amhw_sct_ctrl_clr(p_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);    
}

/** 
 * \brief ����SCT��PWM��PWMֹͣ�����
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \return ��
 */
void sct_pwm_disable(amhw_sct_t *p_sct)
{
    /* ��ֹͣλ��SCTֹͣ���� */
    amhw_sct_ctrl_set(p_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
}

/**
 * \brief ����PWM���ڡ�
 *
 * \param[in] p_sct     : ָ��SCT�Ĵ������ָ��
 * \param[in] period_ns : ���ڣ���λ��ns
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹSCT��PWM(sct_pwm_disable())��
 *       ���øú�������ʹ��(sct_pwm_able())��
 */
void sct_pwm_period_config(amhw_sct_t *p_sct, uint32_t period_ns)
{
    /* ��ʱ��ת��Ϊ���� */
    uint32_t period_c = (uint64_t)(period_ns) * (g_system_clkfreq) / (uint64_t)1000000000; 
    
    /* ��������Ϊ1 */
    if (period_c == 0) {
        period_c = 1;
    }
    
    if (amhw_sct_halt_check(p_sct, AMHW_SCT_MODE_UNIFY) == TRUE ) {      
        amhw_sct_mat_val_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), period_c - 1);
    }
    amhw_sct_mat_reload_val_set(p_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), period_c - 1);
}

/**
 * \brief ��������ڡ�
 */
int main (void)
{  
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    amhw_plfm_sct0_pwm_init();

    AM_DBG_INFO("The demo for SCT output PWM:\r\n");
    AM_DBG_INFO("The PIO0_8(SCT_OUT1) PWM: freq is 4kHz, The duty ratio is 50% \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) PWM: freq is 4kHz, The duty ratio is 25% \r\n");
    
    am_gpio_pin_cfg(PIO0_8, PIO0_8_SCT0_OUT1);    
    am_gpio_pin_cfg(PIO0_5, PIO0_5_SCT0_OUT6);

    sct_pwm_init(AMHW_SCT0);
    
    /* PWM0��ʼ�� */
    sct_pwm_out_init(AMHW_SCT0, PWM0_MATCH_NUM, PWM0_OUTPUT_NUM );  
    
    /* PWM1��ʼ�� */
    sct_pwm_out_init(AMHW_SCT0, PWM1_MATCH_NUM, PWM1_OUTPUT_NUM );
    
    /* ��������Ϊ 250000ns(4KHz) */
    sct_pwm_period_config(AMHW_SCT0, 250000);
    
    /* ����PWM0ռ�ձ� */
    sct_pwm_duty_config(AMHW_SCT0, PWM0_MATCH_NUM, 125000);          
    
    /* ����PWM1ռ�ձ� */
    sct_pwm_duty_config(AMHW_SCT0, PWM1_MATCH_NUM, 62500);
    
    /* ʹ��SCT0�����PWM */
    sct_pwm_enable(AMHW_SCT0);  
 
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_1_32bit_pwm] */

/* end of file */

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
 * \brief SCT 2��16bits��ʱ�����PWM��ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_13(SCT_OUT4)���4kHz��PWM��ռ�ձ�Ϊ50%��
 *   2. PIO0_14(SCT_OUT5)���1kHz��PWM��ռ�ձ�Ϊ25%��
 *
 * - ע�⣺
 *   1. SCTʹ��16λ�����������Բ���2�������PWM��ÿһ��PWM�����ʹ��ͬһƵ�ʡ�
 *      �����������ƥ��ֵΪ��0xFFFF��
 *   2. SCTʹ��32λ��������ֻ�ܲ���һ�������PWM������PWM���ʹ��ͬһƵ�ʡ�
 *      �����������ƥ��ֵΪ��0xFFFFFFFF��
 *
 * \par Դ����
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


#define   SCT_HANDLE_H        1              /**< \brief ���ڲ������� */
#define   SCT_HANDLE_L        0              /**< \brief ���ڲ������� */

/**
 * \name �������PWM
 * @{
 */
 
#define PWM_L_0_MATCH_NUM    AMHW_SCT_MAT(1) /**< \brief ����PWM0ʹ��ƥ��1��λ */
#define PWM_L_0_EVENT_NUM    AMHW_SCT_EVT(1) /**< \brief ����PWM0ʹ���¼�1     */
#define PWM_L_0_OUTPUT_NUM   AMHW_SCT_OUT(1) /**< \brief ����PWM0��SCT_OUT1    */

/** @} */

/**
 * \name �������PWM
 * @{
 */

#define PWM_H_0_MATCH_NUM    AMHW_SCT_MAT(1) /**< \brief ����PWM0ʹ��ƥ��1��λ */
#define PWM_H_0_EVENT_NUM    AMHW_SCT_EVT(2) /**< \brief ����PWM0ʹ���¼�2     */
#define PWM_H_0_OUTPUT_NUM   AMHW_SCT_OUT(6) /**< \brief ����PWM0, SCT_OUT6    */

/** @} */

/**
 * \brief ����16λ��ʱ��ָ����ʱ����ֵ��ʱ����ѵ�Ԥ��Ƶֵ��ƥ��Ĵ���ֵ��
 *
 * \param[in]  count   : ����ֵ
 * \param[out] p_match : ָ��ʱ��ƥ��ֵ��ָ�롣
 *
 * \return �������8bitsԤ��Ƶֵ��
 */
uint32_t prescale_and_match_calculate (uint32_t count, uint32_t *p_match)
{
    uint32_t   match, min_remainder, prescale;
    uint32_t   result_quot, result_rem;
 
    min_remainder = count;
    prescale      = 1;
   *p_match       = 65536;

    /* 
     * ����ֵ��СΪ65536��
     * Ԥ��ƵΪ1��ƥ��ֵ���ڼ���ֵ��
     */
    if (count <= 65536) {        
        prescale      = 1;
        *p_match      = count;  
        return prescale;        
    }    
    
    /* ���ƥ��ֵ��ֱ���ҵ���õ� */
    for (match = 65536; match > 0; match--) {
        
        result_quot = count / match;
        result_rem  = count % match;
        
        /* 
         * ����Ԥ��Ƶ���Ϊ8bits��result_quot�����ֵΪ256���������256������ֵ
         * ���޷��ﵽ��
         */
        if (result_quot <= 256) {       
            if (result_rem == 0) {   
            
                /* ��������ʵ�Ԥ��Ƶ��ƥ��ֵ */
                prescale = result_quot;
                *p_match = match;
                break;
                
            } else if (result_rem < min_remainder) {
            
                /* ��������ʵ�Ԥ��Ƶ��ƥ��ֵ */
                min_remainder = result_rem;
                prescale      = result_quot;
                *p_match      = match;
            }
        }
    }

    return prescale;
}

/**
 * \brief ��ʼ��SCT����PWM��
 *
 * \param[in] p_sct  : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle : ���飺#SCT_HANDLE_H�����飺#SCT_HANDLE_L��
 *
 * \return ��
 *
 * \note ����ʹ���¼�12��ƥ��0�ĸ�16λ bits�������ڡ�
 *       ����ʹ���¼�0��ƥ��0�ĵ�16λ bits�������ڡ�
 */
void sct_2_16bit_pwm_init (amhw_sct_t *p_hw_sct, uint8_t handle)
{
    amhw_sct_mode_t  sct_mode;
    uint32_t         event_num;
    uint32_t         event_ctl;
    
    if (handle == SCT_HANDLE_H) {
        
        sct_mode  = AMHW_SCT_MODE_SEPARATE_H;
        event_num = AMHW_SCT_EVT(12);        /* ����ʹ���¼�12 */
        
        /* �¼�����ƥ���16λ */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_H; 
        
    } else {
        sct_mode = AMHW_SCT_MODE_SEPARATE_L;
        event_num = AMHW_SCT_EVT(0);         /* ����ʹ���¼�0 */
        
        /* �¼�����ƥ���16λ */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_L;
    }
    
    /* ����ƥ��/����Ĵ���Ϊƥ��Ĵ��� */
    amhw_sct_regmode_config(p_hw_sct, 
                            sct_mode,  
                            AMHW_SCT_MAT(0), 
                            AMHW_SCT_MATCAP_MATCH);

    amhw_sct_mat_val_set(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), 0);
    
 
    /* �����¼�0 */
    amhw_sct_event_ctrl(p_hw_sct, 
                        event_num, 
                        event_ctl                       | /* ѡ���״̬��ƥ��Ĵ��� */
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* �¼�����ƥ��0          */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* ֻ��ʹ��ָ��ƥ��       */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV ֵ���� STATE   */
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* �� 0��STATEû�иı�    */       
   
    /* ʹ��״̬0�����¼� */
    amhw_sct_event_state_enable(p_hw_sct, event_num, AMHW_SCT_STATE(0));

    /* ���õ�ǰ״ֵ̬Ϊ0 */
    amhw_sct_state_set(p_hw_sct, sct_mode, AMHW_SCT_STATE(0));
    
    if (handle == SCT_HANDLE_H) {
    
    /* ��CLRCTRλ������������Ϊ0 */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_H);
    } else {
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    }
}

/** 
 * \brief ��ʼ��SCTΪ2��PWM���
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ�롣
 * \return ��
 */
void sct_pwm_init (amhw_sct_t *p_hw_sct)
{
    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_16BIT_COUNTER  | /* ��ʱ����Ϊ2��16λ��ʱ�� */
                    AMHW_SCT_CONFIG_AUTOLIMIT_L    | /* ����ƥ��0�Զ�����       */
                    AMHW_SCT_CONFIG_AUTOLIMIT_H    | /* ����ƥ��0�Զ�����       */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* SCTʱ��ʹ��ϵͳʱ��     */    

    sct_2_16bit_pwm_init(p_hw_sct, SCT_HANDLE_L);
    sct_2_16bit_pwm_init(p_hw_sct, SCT_HANDLE_H);
}

/** 
 * \brief ʹ��SCT���PWM
 *
 * \param[in] p_sct  : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle : ���飺#SCT_HANDLE_H�����飺#SCT_HANDLE_L��
 *
 * \return  ��
 */
void sct_2_16bit_pwm_enable (amhw_sct_t *p_hw_sct, uint8_t handle)
{
    if (handle == SCT_HANDLE_H) {
        
        amhw_sct_ctrl_halt_to_stop(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H); 
         
        /* ���ֹͣλ��SCT�����������ʼ���� */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_H);
               
        if (amhw_sct_halt_check(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L) == TRUE) {
            
            /* ���鲻����Ϣ�������Ϊֹͣ��������鲻�����PWM */
            amhw_sct_ctrl_halt_to_stop(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L);
        }
      
    } else {
        
        /* ���ֹͣλ��SCT�����������ʼ���� */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
    }        
}

/** 
 * \brief ��ֹSCT���PWM��
 *
 * \param[in] p_sct  : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle : ���飺#SCT_HANDLE_H�����飺#SCT_HANDLE_L��
 *
 * \return  ��
 */
void sct_2_16bit_pwm_disable(amhw_sct_t *p_hw_sct, uint8_t handle)
{
    if (handle == SCT_HANDLE_H) {
        
        /* ��ֹͣλ��SCT���������ֹͣ���� */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_H | AMHW_SCT_CTRL_HALT_H);  
      
    } else {
        
        /* ��ֹͣλ��SCT���������ֹͣ���� */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
    }   
}

/** 
 * \brief ��ʼ�����һ·PWM��
 *
 * \param[in] p_sct      : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle     : ���飺#SCT_HANDLE_H�����飺#SCT_HANDLE_L��
 * \param[in] match_num  : ƥ���š�
 * \param[in] event_num  : �¼���š�
 * \param[in] output_num : ���ͨ����Ϊ0~7֮�䡣
 *
 * \note ƥ��0����ȷ�����ڣ�match_num����ʹ��AMHW_SCT_MAT(0)��
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
    
    /* ƥ��0ʹ���Զ����� */
    if (match_num == AMHW_SCT_MAT(0)) {
        return;
    }
    
    /* �¼�0���¼�12����������� */
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
    
    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_sct_regmode_config(p_hw_sct, sct_mode, match_num, AMHW_SCT_MATCAP_MATCH);       
                  
    /* �����¼� */
    amhw_sct_event_ctrl(p_hw_sct, 
                        event_num, 
                        hevent_mode                         |  
                        AMHW_SCT_EV_CTRL_MATCHSEL(match_num)  |     
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH       |  
                        AMHW_SCT_EV_CTRL_STATELD_ADD          |  
                        AMHW_SCT_EV_CTRL_STATEV(0));             
    
    /* ʹ��״̬0�в����¼� */
    amhw_sct_event_state_enable(p_hw_sct, event_num, AMHW_SCT_STATE(0));
    
    if (sct_mode == AMHW_SCT_MODE_SEPARATE_H) {
    
        /* �����¼�12ΪPWM��� */
        amhw_sct_out_set_enable(p_hw_sct, output_num, AMHW_SCT_EVT(12));        
    } else {
    
        /* �����¼�0ΪPWM��� */
        amhw_sct_out_set_enable(p_hw_sct, output_num, AMHW_SCT_EVT(0));            
    }

    /* �¼����PWM��� */
    amhw_sct_out_clr_enable(p_hw_sct, output_num, event_num);    
    
    /* 
     * ����Чʱ��������ڽ��������ͻ���ڸ�������£�ռ�ձ�Ϊ100%��
     * �ʴ�ʱҪ��λ�����
     */
    amhw_sct_conflict_res_config(p_hw_sct, output_num, AMHW_SCT_RES_SET_OUTPUT);   

    /* ��λ�����㲻�����ڷ��� */
    amhw_sct_output_dir_ctrl(p_hw_sct, output_num, AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT);
}

/**
 * \brief ����PWM����
 *
 * \param[in] p_sct     : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle    : ���飺#SCT_HANDLE_H�����飺#SCT_HANDLE_L��
 * \param[in] period_ns : ���ڣ���λΪ��ns��
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹSCT��PWM��
 *       ���øú�������ʹ�ܡ�
 */
void sct_pwm_period_config(amhw_sct_t *p_hw_sct, uint8_t handle, uint32_t period_ns)
{
    /* ת��ʱ��Ϊ���� */
    uint32_t period_c = (uint64_t)(period_ns) * (g_system_clkfreq) / (uint64_t)1000000000; 
    uint32_t prescale = 0;
    uint32_t match    = 0;
    
    amhw_sct_mode_t sct_mode;
    
    if (handle == SCT_HANDLE_H) {
        sct_mode = AMHW_SCT_MODE_SEPARATE_H;
    } else {
        sct_mode = AMHW_SCT_MODE_SEPARATE_L;
    }
    
    /* ��������Ϊ1 */
    if (period_c == 0) {
        period_c = 1;
    }    

    /* 
     * ������������Ϊ��65536 * 256(Ԥ��Ƶ), ���ʱ��Ϊ��
     * 65536 / (g_system_clkfreq / 256) = 65536 * 256 / g_system_clkfreq.
     *
     * ��100MHzʱ�����ʱ��Ϊ��256 * 65536 / 100 us =  167772 us
     * ��12MHzʱ�����ʱ��Ϊ��256 * 65536 /  12 us = 1398101 us   
     */
    if (period_c >= 256 * 65536) {
        period_c = 256 * 65536;     /* �������Ϊ256 * 65536 */
    }
    
    /* ����Ԥ��Ƶ��ƥ��ֵ */
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
 * \brief ����PWM��Чʱ�䣨ռ�ձȣ�
 *
 * \param[in] p_sct   : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle  : ���飺#SCT_HANDLE_H�����飺#SCT_HANDLE_L��
 * \param[in] num     : ƥ���š�
 * \param[in] duty_ns : ��Чʱ�䣬��λ��ns��
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹSCT��PWM(sct_pwm_disable())��
 *       ���øú�������ʹ��(sct_pwm_able())�����SCTû��ֹͣ����ֵ����д��
 *       ����ƥ��ֵ��������һ������Ч��
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
    
    /* ��ʱ��ת��Ϊ���� */
    clkfreq = g_system_clkfreq / (amhw_sct_prescale_get(p_hw_sct, sct_mode) + 1);
    
    duty_c = (uint64_t)(duty_ns) * (clkfreq) / (uint64_t)1000000000; 
 
    /* ռ����Чʱ����СΪ1 */
    if (duty_c == 0) {
        duty_c = 1;
    }
       
    if (duty_c > 65536) {
        duty_c = 65536;
    }
    
    if (amhw_sct_halt_check(p_hw_sct, AMHW_SCT_MODE_UNIFY) == TRUE ) {      
        amhw_sct_mat_val_set(p_hw_sct, sct_mode, num, duty_c - 1);
    }
    
    /* ��������ƥ��ֵ */
    amhw_sct_mat_reload_val_set(p_hw_sct, sct_mode, num, duty_c - 1);  
}


/**
 * \brief ���������
 */
int main (void)
{  
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_sct0_pwm_init();
    
    AM_DBG_INFO("The demo for SCT output PWM:\r\n");
    AM_DBG_INFO("The PIO0_8(SCT_OUT1) PWM: freq is 4kHz, The duty ratio is 50% \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) PWM: freq is 1kHz, The duty ratio is 25% \r\n");
    
    am_gpio_pin_cfg(PIO0_8, PIO0_8_SCT0_OUT1);
    am_gpio_pin_cfg(PIO0_5, PIO0_5_SCT0_OUT6);
    
    /* ��ʼ��SCTΪ2��PWM��� */
    sct_pwm_init(AMHW_SCT0);
    
    /* SCT_OUT5������ */
    sct_pwm_out_init(AMHW_SCT0, 
                     SCT_HANDLE_L,         /* ����   */
                     PWM_L_0_MATCH_NUM,    /* ƥ��� */
                     PWM_L_0_EVENT_NUM,    /* �¼��� */
                     PWM_L_0_OUTPUT_NUM);  /* ����� */

    /* SCT_OUT7������ */
    sct_pwm_out_init(AMHW_SCT0, 
                     SCT_HANDLE_H, 
                     PWM_H_0_MATCH_NUM, 
                     PWM_H_0_EVENT_NUM, 
                     PWM_H_0_OUTPUT_NUM);
    
    /* 
     * ��������Ϊ250 000ns(4KHz)��
     * ��100MHz���������Ϊ��256 * 65536 / 100 us =  167772 us
     */
    sct_pwm_period_config(AMHW_SCT0, SCT_HANDLE_L, 250000);
    
    /* ��������Ϊ1000 000ns(1KHz) */
    sct_pwm_period_config(AMHW_SCT0, SCT_HANDLE_H, 1000000);
    
    /* ����PWM0��Чʱ�� */
    sct_pwm_duty_config(AMHW_SCT0, SCT_HANDLE_L, PWM_L_0_MATCH_NUM, 125000);
    
    /* ����PWM0��Чʱ�� */
    sct_pwm_duty_config(AMHW_SCT0, SCT_HANDLE_H, PWM_H_0_MATCH_NUM, 250000);

    sct_2_16bit_pwm_enable(AMHW_SCT0, SCT_HANDLE_L);       /* ʹ�ܵ���PWM */        
    sct_2_16bit_pwm_enable(AMHW_SCT0, SCT_HANDLE_H);       /* ʹ�ܸ���PWM */  
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_2_16bit_pwm] */

/* end of file */

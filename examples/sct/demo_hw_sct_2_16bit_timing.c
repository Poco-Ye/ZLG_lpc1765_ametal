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
 * \brief SCT��2��16λ��ʱ����ʵ�ֶ�ʱ���ܣ�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸;
 *   2. PIO0_5����״̬��8KHz��Ƶ�ʷ�ת���������Ϊ4KHz��
 *
 * \par Դ����
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



#define   SCT_HANDLE_H        1            /**< \brief ���ڲ������鶨ʱ�� */
#define   SCT_HANDLE_L        0            /**< \brief ���ڲ������鶨ʱ�� */

/** 
 * \brief ����16λ��ʱ��ָ����ʱ����ֵ��ʱ����ѵ�Ԥ��Ƶֵ��ƥ��Ĵ���ֵ��
 *
 * \param[in]  count   : ����ֵ��
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
        prescale = 1;
        *p_match = count;  
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
 * \brief  SCT0�жϷ�����
 * \param[in] p_arg : �û��Զ���������� am_int_connect() �������ݡ�
 * \return  ��
 */
void sct0_irq_handler (void *p_arg)
{
    /* �¼�0�ж� */
    if (amhw_sct_event_flag_chk(AMHW_SCT0, AMHW_SCT_EVT(0)) == TRUE) {
        
        am_led_toggle(LED0);
        amhw_sct_event_flag_clr(AMHW_SCT0, AMHW_SCT_EVT(0));  /* ���־ */
    }
    
    /* �¼�1�ж� */
    if (amhw_sct_event_flag_chk(AMHW_SCT0, AMHW_SCT_EVT(1)) == TRUE) {
        
        /* ��תGPIO0_5���� */
        am_gpio_toggle(PIO0_5);
        
        amhw_sct_event_flag_clr(AMHW_SCT0, AMHW_SCT_EVT(1));  /* ���־ */
    } 
}


/** 
 * \brief  ʹ�ܶ�ʱ����
 *
 * \param[in] p_sct  : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle : ���鶨ʱ����#SCT_HANDLE_H�����鶨ʱ����#SCT_HANDLE_L
 *
 * \return  ��
 */
void sct_2_16bit_timer_enable (amhw_sct_t *p_hw_sct, uint8_t handle)
{
    if (handle == SCT_HANDLE_H) {
    
        /* ��ֹͣλ��SCT�����������ʼ���� */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_H | AMHW_SCT_CTRL_HALT_H);  
      
    } else {
        
        /* ��ֹͣλ��SCT�����������ʼ���� */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
    }        
}

/** 
 * \brief  ���ܶ�ʱ��
 *
 * \param[in] p_sct  : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle : ���鶨ʱ����#SCT_HANDLE_H�����鶨ʱ����#SCT_HANDLE_L ��
 *
 * \return  ��
 */
void sct_2_16bit_timer_disable (amhw_sct_t *p_hw_sct, uint8_t handle)
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
 * \brief ��ʼ����ʱ����
 *
 * \param[in] p_sct  : ָ��SCT�Ĵ������ָ�롣
 * \param[in] handle : ���鶨ʱ����#SCT_HANDLE_H�����鶨ʱ����#SCT_HANDLE_L ��
 * \param[in] freq   : ��ʱ���ж�Ƶ�ʡ�
 *
 * \return ��
 *
 * \note ���鶨ʱ��ʹ���¼�0�����鶨ʱ��ʹ���¼�1.
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
        event_num = AMHW_SCT_EVT(1);           /* ���鶨ʱ��ʹ���¼�1 */
        
        /* �¼�������ƥ���16bits */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_H; 
        
    } else {
        sct_mode = AMHW_SCT_MODE_SEPARATE_L;
        event_num = AMHW_SCT_EVT(0);          /* ���鶨ʱ��ʹ���¼�0 */
        
        /* �¼�������ƥ���16bits */
        event_ctl = AMHW_SCT_EV_CTRL_HEVENT_L;
    }
    
    /* ����ƥ��/����Ĵ���0Ϊ16bitsƥ��Ĵ���*/
    amhw_sct_regmode_config(p_hw_sct, sct_mode, AMHW_SCT_MAT(0), AMHW_SCT_MATCAP_MATCH);   

    /*
     * ����16λ��ʱ��Ԥ��Ƶ��ƥ��ֵ�����磬Ҫ����10Hz���жϣ�ϵͳʱ��Ƶ��Ϊ
     * 100MHz����ʱ������ֵΪ��100 000 000 / 10 = 10 000 000��
     * ������Ϊ16bits�����ֵΪ65536����ʹ��Ԥ��Ƶ��10 000 000 = 200 * 50000��
     * ƥ��ֵΪ��50000��
     * Ԥ��ƵֵΪ��200��
     */
    counters = g_system_clkfreq / freq;
    
    prescale = prescale_and_match_calculate(counters, &match);
    
    prescale -= 1;
    match    -= 1;

    /* ��Ҫ�ı�Ԥ��Ƶ��Ӧ��ֹͣSCT */
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

    /* ���鶨ʱ��ʹ���¼�1�������¼�1 */
    amhw_sct_event_ctrl(p_hw_sct, 
                        event_num, 
                        event_ctl                     |  
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* �¼�������ƥ��0     */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* ֻ��ʹ��ָ��ƥ��    */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /* STATEV ֵ���� STATE */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* �� 0��STATEû�иı� */

    /* ���õ�ǰ״ֵ̬Ϊ0 */
    amhw_sct_state_set(p_hw_sct, sct_mode, AMHW_SCT_STATE(0));

    /* ʹ��״̬0�в����¼� */
    amhw_sct_event_state_enable(p_hw_sct, event_num, AMHW_SCT_STATE(0));

    /* ʹ���¼����������޶� */
    amhw_sct_event_limit_enable(p_hw_sct, sct_mode, event_num);
    
    /* ʹ���¼������ж� */
    amhw_sct_event_int_enable(p_hw_sct, event_num);
    
    if (handle == SCT_HANDLE_H) {
    
        /* ����CLRCTRλ������������Ϊ0 */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_H);
    } else {
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    }
}

/** 
 * \brief SCTʵ�ֶ�ʱ���ܡ�
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ�롣
 * \return ��
 */
void sct_2_16bit_init (amhw_sct_t *p_hw_sct)
{
    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_16BIT_COUNTER  | /* ��ʱ��ʵ��2��16bits��ʱ�� */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* SCTʱ��ʹ��ϵͳʱ��       */    

    /* ʹ�ܵ��鶨ʱ���жϣ��ж�Ƶ��Ϊ10Hz */
    sct_2_16bit_timer_init(p_hw_sct, SCT_HANDLE_L, 10);
    
    /* ʹ�ܸ��鶨ʱ���жϣ��ж�Ƶ��Ϊ8KHz */
    sct_2_16bit_timer_init(p_hw_sct, SCT_HANDLE_H, 8000);
}

/**
 * \brief ���������
 */
int main (void)
{  
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    amhw_plfm_sct0_timing_init();
 
    AM_DBG_INFO("The demo for SCT operate as 2-16bit timer \r\n");
    AM_DBG_INFO("The LED0 blinking in 10Hz\r\n");
    AM_DBG_INFO("The PIO0_5 toggle in 8KHz, The output waveform is 4KHz\r\n");
    
    am_gpio_pin_cfg(PIO0_5, PIO0_5_GPIO | PIO0_5_OUTPUT);
    
    /* ʹ��SCTʵ�ֶ�ʱ���� */
    sct_2_16bit_init(AMHW_SCT0);

    am_int_connect(INUM_SCT0, sct0_irq_handler, (void *)0);
    
    /* ʹ��SCT0�ж� */
    am_int_enable(INUM_SCT0);
    
    sct_2_16bit_timer_enable(AMHW_SCT0, SCT_HANDLE_L);   /* ʹ�ܵ��鶨ʱ�� */
    sct_2_16bit_timer_enable(AMHW_SCT0, SCT_HANDLE_H);   /* ʹ�ܸ��鶨ʱ�� */
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_2_16bit_timing] */

/* end of file */

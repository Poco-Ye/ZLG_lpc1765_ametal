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
 * \brief SCT������̬���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. PIO0_5(SCT_OUT6)����������Ρ�
 *
 * \code
 *  |---         ״̬0        ---|--- ״̬1 ---|--- ״̬0      ......
 *             _____     _____     ___         __            ___
 *            |     |   |     |   |   |       |  |          |     ......
 *  __________|     |___|     |___|   |_______|  |__________|
 *
 *  0         10    15  18    23  26  3      10  12         10     (ms)
 *                              (״̬1, 0)     (״̬0, 0)
 *          �¼� 0  1   2      3   4   5      6  7
 * \endcode
 *
 * \note ����PIO0_5(SCT_OUT6)���ŵ��߼������ǣ����ῴ���ò��Σ�ǰ10msΪ�͵�ƽ��
 *
 * \par Դ����
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

#define   OUT_NUM       AMHW_SCT_OUT(6)       /**< \brief ʹ��SCT_OUT6 */

/**
 * \brief ��ʼ��ƥ��Ĵ���
 *
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] num   : ƥ��
 * \param[in] ms    : ƥ��ʱ�䣬��λ��ms
 *
 * \return ��
 */
void sct_match_init (amhw_sct_t *p_hw_sct, uint32_t num, uint32_t ms)
{
    uint32_t ms_ticks = g_system_clkfreq / 1000;
    
    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_sct_regmode_config(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(num), AMHW_SCT_MATCAP_MATCH);
    
    /* ����ƥ��0������ƥ��ֵ */
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
 * \brief ��ʼ��һ���¼�
 *
 * \param[in] p_sct     : ָ��SCT�Ĵ������ָ�롣
 * \param[in] evt_num   : �¼���
 * \param[in] match_num : ƥ�䡣
 * \param[in] state_num : ״̬��
 * \param[in] state_ld  : 0, state_ev ����״̬��
 *                        1, the state_ev ����Ϊ״̬
 * \param[in] state_ev  : ��ֵ�ı�״̬��
 *
 * \return ��
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
    
    /* �����¼�0���� */
    amhw_sct_event_ctrl(p_hw_sct, 
                        evt_num, 
                        AMHW_SCT_EV_CTRL_MATCHSEL(match_num)  | /* �¼�����ƥ�� */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH       | /* ʹ��ָ��ƥ�� */
                        state_ld                            | 
                        AMHW_SCT_EV_CTRL_STATEV(state_ev));      

    /* ʹ���¼����� */
    amhw_sct_event_state_enable(p_hw_sct, evt_num, state_num);      
}

/**
 * \brief ʹ��SCT������Ӳ��Ρ�
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \return ��
 */
void sct_init (amhw_sct_t *p_hw_sct)
{

    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  | /* ��32λ��ʱ��      */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* ϵͳʱ����SCTʱ�� */
    
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(0), 10);  /* ����ƥ��0ֵΪ10ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(1), 15);  /* ����ƥ��1ֵΪ15ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(2), 18);  /* ����ƥ��2ֵΪ18ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(3), 23);  /* ����ƥ��3ֵΪ23ms */
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(4), 26);  /* ����ƥ��4ֵΪ26ms */ 
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(5), 3);   /* ����ƥ��5ֵΪ 3ms */ 
    sct_match_init(p_hw_sct, AMHW_SCT_MAT(6), 12);  /* ����ƥ��6ֵΪ12ms */ 
    
    amhw_sct_output_state_clr(p_hw_sct, OUT_NUM);   /* ������ */ 
    
    /* 
     * ״̬0�¼�����
     */

    /* �¼�0������ƥ��0�����ı�״ֵ̬����� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(0), AMHW_SCT_MAT(0), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(0));  
   
    /* �¼�1������ƥ��1�����ı�״ֵ̬�������� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(1), AMHW_SCT_MAT(1), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(1));  

    /* �¼�2������ƥ��2�����ı�״ֵ̬����� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(2), AMHW_SCT_MAT(2), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(2));      

    /* �¼�3������ƥ��3�����ı�״ֵ̬�������� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(3), AMHW_SCT_MAT(3), AMHW_SCT_STATE(0), 0, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(3));  

    /* �¼�4������ƥ��4���ı�״ֵ̬Ϊ1�������� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(4), AMHW_SCT_MAT(4), AMHW_SCT_STATE(0), 0, 1);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(4));

    /* ��״̬0 �У��¼�4��Ϊ�����¼� */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_EVT(4));
    
    /*
     * ״̬1�¼�����
     */     
     
    /* �¼�5������ƥ��5(3ms)�����ı�״ֵ̬�������� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(5), AMHW_SCT_MAT(5), AMHW_SCT_STATE(1), 0, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(5));  

    /* �¼�6������ƥ��0(10ms)�����ı�״ֵ̬����� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(6), AMHW_SCT_MAT(0), AMHW_SCT_STATE(1), 0, 0);
    amhw_sct_out_set_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(6));  

    /* �¼�7������ƥ��6(12ms)���ı�״ֵ̬Ϊ0�������� */
    sct_event_init(p_hw_sct, AMHW_SCT_EVT(7), AMHW_SCT_MAT(6), AMHW_SCT_STATE(1), AMHW_SCT_EV_CTRL_STATELD_LOAD, 0);
    amhw_sct_out_clr_enable(p_hw_sct, OUT_NUM, AMHW_SCT_EVT(7));     
  
    /* ʹ���¼�7���Ƽ�����ֵ */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_EVT(7));     
  
    /* ���õ�ǰ״ֵ̬Ϊ0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_STATE(0));
    
    /* ʹ���¼�0�����ж� */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
    
    /* ��CLRCTRλ���������Ϊ0 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* Ԥ��ƵΪ0��ʹ��ϵͳʱ�ӡ� */
    amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
    
}

/**
 * \brief ʹ��SCT������Ӳ���
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \return ��
 */
void sct_enable (amhw_sct_t *p_hw_sct)
{
    /* ��ֹͣλ��SCT��ʼ���� */
    amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
}

/**
 * \brief ��ֹSCT������Ӳ���
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \return ��
 */
void sct_disable (amhw_sct_t *p_hw_sct)
{
    /* ��ֹͣλ��SCTֹͣ���� */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
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
    
    AM_DBG_INFO("The demo for SCT in multi states \r\n");
    AM_DBG_INFO("The PIO0_5(SCT_OUT6) output waveform\r\n");
    
    am_gpio_pin_cfg(PIO0_5, PIO0_5_SCT0_OUT6);
    
    /* SCTʵ�ֶ�ʱ������ */
    sct_init(AMHW_SCT0);
 
    sct_enable(AMHW_SCT0);
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_multi_states] */

/* end of file */

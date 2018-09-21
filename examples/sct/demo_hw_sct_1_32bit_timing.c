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
 * \brief SCT 32λ��ʱ��ʵ�ֶ�ʱ���ܵ����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 * \par Դ����
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
 * \brief  SCT0�жϷ�����
 * \param[in]  p_arg : �û��Զ���������� am_int_connect() �������ݡ�
 * \return  ��
 */
void sct0_irq_handler(void *p_arg)
{
    /* �¼�0�����ж� */
    if (amhw_sct_event_flag_chk(AMHW_SCT0, AMHW_SCT_EVT(0)) == TRUE ) {
        
        am_led_toggle(LED0);
        
        /* �����־ */
        amhw_sct_event_flag_clr(AMHW_SCT0, AMHW_SCT_EVT(0));  
    }
}

/** 
 * \brief ��ʼ��SCTΪ��ʱ�����ܡ�
 *
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] freq  : �ж�Ƶ�ʡ�
 *
 * \return ��
 */
void sct_timer_init (amhw_sct_t *p_hw_sct, uint32_t freq)
{

    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  | /* ʹ��32λ��ʱ�� */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* ʹ��ϵͳʱ��   */
    
    /* ��ƥ�䲶׽�Ĵ�������Ϊƥ�书�� */
    amhw_sct_regmode_config(p_hw_sct, 
                            AMHW_SCT_MODE_UNIFY,    /* SCTģʽΪUNIFY(1 32-bit ������) */
                            0,                      /* ƥ��/����0                      */
                            AMHW_SCT_MATCAP_MATCH); /* ����ƥ��Ĵ���                  */
    
    /* ����ƥ��0������ƥ��ֵ */
    amhw_sct_mat_val_set(p_hw_sct, 
                         AMHW_SCT_MODE_UNIFY, 
                         AMHW_SCT_MAT(0), 
                         g_system_clkfreq / freq - 1);
    
    amhw_sct_mat_reload_val_set(p_hw_sct, 
                                AMHW_SCT_MODE_UNIFY, 
                                AMHW_SCT_MAT(0), 
                                g_system_clkfreq / freq - 1);
    
    /* �����¼�0���ƼĴ��� */
    amhw_sct_event_ctrl(p_hw_sct, 
                        AMHW_SCT_EVT(0),                  /* �¼�0                    */
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* �¼�������ƥ��0          */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* ֻ��ʹ��ָ����ƥ��Ĵ��� */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV ֵ���� STATE     */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* �� 0��STATEû�иı�      */
                   
    /* ���õ�ǰ״ֵ̬Ϊ0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
    
    /* ʹ��״̬0���¼�0���� */
    amhw_sct_event_state_enable(p_hw_sct, AMHW_SCT_EVT(0), AMHW_SCT_STATE(0));
    
    /* ʹ���¼�0���޶������� */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_EVT(0));
    
    /* ʹ���¼�0�����ж� */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
    
    /* ����SCT0���жϷ����� */
    am_int_connect(INUM_SCT0, sct0_irq_handler, (void *)0);
    
    /* ʹ��SCT0�ж� */
    am_int_enable(INUM_SCT0);
    
    /* ��CLRCTRλ���������Ϊ0 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* Ԥ��ƵΪ0��ʹ��ϵͳʱ�ӡ� */
    amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
}


/** 
 * \brief ʹ��SCTΪ��ʱ��(��ʼ����)
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \return ��
 */
void sct_timer_enable (amhw_sct_t *p_hw_sct)
{
    /* ��ֹͣλ��SCT��ʼ���� */
    amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);  
}

/** 
 * \brief  ��ֹSCTΪ��ʱ��(ֹͣ����)
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ��
 * \return  ��
 */
void sct_timer_disable (amhw_sct_t *p_hw_sct)
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

    AM_DBG_INFO("The demo for SCT timing:\r\n");
    AM_DBG_INFO("The led toggle in 10Hz \r\n");

    /* ʹ��SCTʵ�ֶ�ʱ���ܣ��ж�Ƶ��Ϊ10Hz */
    sct_timer_init(AMHW_SCT0, 10);
    
    /* ʹ��SCTΪ��ʱ�� */
    sct_timer_enable(AMHW_SCT0);
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_sct_1_32bit_timing] */

/* end of file */

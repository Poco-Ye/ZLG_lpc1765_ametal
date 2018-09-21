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
 * \brief SCT��32λ��ʱ��ʵ�ֲ����ܵ����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. ������ò����ܵõ���PWM�źŵ����ں�Ƶ�ʡ�
 *
 * - ע�⣺
 *   1. PIO0_29�������ڶ�ʱ��0���PWM(PIO0_29)��
 *   2. PIO0_25 ������SCT����ͨ��2�����벶��
 *   3. ����PIO0_29���ź�PIO0_25���ţ��������������ʵ��PWMƵ�ʵĲ�����
 *
 * \par Դ����
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


 
/** \brief �����ز��� */
#define SCT_CAP_TRIGGER_RISE  1

/** \brief �½��ز��� */
#define SCT_CAP_TRIGGER_FALL  2

/** 
 * \brief ��ʼ��SCT�����PWM��
 *
 *  ��ʼ��SCTʵ��32λ��ʱ�����ܣ�ʹ��MATCH0Ϊ�Զ����ơ�
 *  
 * \param[in] p_sct : ָ��SCT�Ĵ������ָ�롣
 * \return ��
 */
void sct_cap_init (amhw_sct_t *p_hw_sct)
{
    /* ��ֹͣλ��SCTֹͣ���� */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
    
    amhw_sct_config(p_hw_sct, 
                    AMHW_SCT_CONFIG_32BIT_COUNTER  |
                    AMHW_SCT_CONFIG_INSYNC_ALL     |
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK ); 
  
    /* ��CLRCTRλ���������Ϊ0 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* ���õ�ǰ״ֵ̬Ϊ0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_STATE(0));
    
    /* Ԥ��ƵΪ0��ʹ��ϵͳʱ�ӡ� */
    amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
}

/** 
 * \brief ��ʼ��һ·PWM�����
 *
 * \param[in] p_sct    : ָ��SCT�Ĵ������ָ�롣
 * \param[in] cap_num  : �����š�
 * \param[in] cap_edge : �������ѡ�� (#SCT_CAP_TRIGGER_RISE) �� (#SCT_CAP_TRIGGER_FALL)
 * 
 * \return  ��
 */
void sct_cap_chan_config (amhw_sct_t *p_hw_sct, uint32_t cap_num, uint8_t cap_edge)
{
    uint32_t  iocond;
    
    if (cap_edge == SCT_CAP_TRIGGER_RISE) {
        iocond = AMHW_SCT_EV_CTRL_IOCOND_RISE;
    } else {
        iocond = AMHW_SCT_EV_CTRL_IOCOND_FALL;
    }

    /* ��ƥ�䲶׽�Ĵ�������Ϊ������ */
    amhw_sct_regmode_config(p_hw_sct, 
                            AMHW_SCT_MODE_UNIFY, 
                            AMHW_SCT_MAT(cap_num), 
                            AMHW_SCT_MATCAP_CAPTURE);
    
    /* ʹ���¼�ԭ�� CAPn _L (UNIFY = 0) �Ĵ����ؼ��� */
    amhw_sct_cap_ctrl(p_hw_sct, 
                      AMHW_SCT_MODE_UNIFY, 
                      AMHW_SCT_CAP(cap_num), 
                      AMHW_SCT_EVT(cap_num), 
                      TRUE);
    
    /* ʹ���¼����ͬ��ͨ���š��¼�ֻ����IO������������ƥ��Ĵ�����*/
    amhw_sct_event_ctrl(p_hw_sct, 
                        AMHW_SCT_EVT(cap_num), 
                        AMHW_SCT_EV_CTRL_OUTSEL_INPUT    |
                        AMHW_SCT_EV_CTRL_IOSEL(cap_num)  |
                        iocond                           |
                        AMHW_SCT_EV_CTRL_COMBMODE_IO     | /* ʹ��ָ��IO           */
                        AMHW_SCT_EV_CTRL_STATELD_ADD     | /*  STATEV ֵ���� STATE */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));       /* �� 0��STATEû�иı�  */

}

/**
 * \brief ����PWM��Чʱ�䣨ռ�ձȣ���
 *
 * \param[in] p_sct   : ָ��SCT�Ĵ������ָ�롣
 * \param[in] num     : ����PWM��ƥ���š�
 * \param[in] duty_ns : ��Чʱ�䣬��λ��ns��
 *
 * \return ��
 *
 * \note ������ø�����������Ч��Ӧ�ڵ��øú���ǰ��ֹSCT��PWM(sct_pwm_disable())��
 *       ���øú�������ʹ��(sct_pwm_able())�����SCTû��ֹͣ����ֵ����д��
 *       ����ƥ��ֵ��������һ������Ч��
 */
static int sct_cap_chan_enable (amhw_sct_t *p_hw_sct, uint32_t cap_num)
{
    /* ʹ��״̬0���¼�0���� */
    amhw_sct_event_state_enable(p_hw_sct, AMHW_SCT_EVT(cap_num), AMHW_SCT_STATE(0));

    /* ����¼���־ */
    amhw_sct_event_flag_clr(p_hw_sct, AMHW_SCT_EVT(cap_num));
        
    /* ʹ���¼�0�����ж� */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(cap_num));
    
    amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
    
    return AM_OK;
}


volatile bool_t   g_flag    = FALSE;   /**< \brief �����־ */
volatile uint32_t g_time_ns = 0;       /**< \brief ������� */

/** 
 * \brief SCT�����жϷ�������
 * \param[in] p_arg : �û��Զ���������� am_int_connect() �������ݡ�
 * \return  ��
 */
void sct_cap_isr (void *p_arg)
{
    static uint32_t count1;
    static bool_t   first    = TRUE;
    amhw_sct_t     *p_hw_sct = (amhw_sct_t *)p_arg;
    uint32_t        cap_val;
    
    /* ����ͨ��2ʹ���¼�2 */
    if (amhw_sct_event_flag_chk(p_hw_sct, AMHW_SCT_EVT(2)) == TRUE ) {
        
        cap_val = amhw_sct_cap_val_get(p_hw_sct, AMHW_SCT_MODE_UNIFY, 2);
        
        if (g_flag == FALSE) {
        
            if (first == TRUE) {
                count1 = cap_val;
                first  = FALSE;
            } else {
                
                /* ת������ֵΪʱ��  */
                g_time_ns = 1000000000 / g_system_clkfreq * (cap_val - count1);
               
                first = TRUE;
                
                /* ��־ΪTRUE���������������� */
                g_flag = TRUE;
            }
        }
        
        /* ���¼���־ */
        amhw_sct_event_flag_clr(p_hw_sct, AMHW_SCT_EVT(2));
    }
}

/**
 * \brief ��������ڡ�
 */
int main (void)
{
    am_pwm_handle_t  timer0_pwm_handle;
    uint32_t         freq;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_timer0_pwm_init();
    amhw_plfm_sct0_cap_init();
    
    AM_DBG_INFO("The SCT demo for CAP service\r\n");
    
    /* ʹ�ö�ʱ��0���һ·PWM */
    timer0_pwm_handle = amdr_timer_pwm_init(&g_timer0_pwm_dev, 
                                            &g_timer0_pwm_devinfo);
    
    /* ͨ��1ʹ��PIO0_29���� amdr_hwconfig_sct_pwm.c ������ */
    am_pwm_config(timer0_pwm_handle, 1, 5000000 / 2, 5000000); /* Ƶ��Ϊ2KHz */
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

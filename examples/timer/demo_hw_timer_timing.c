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
 * \brief ��ʱ����ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED��˸Ƶ��10Hz��
 *
 * \par Դ����
 * \snippet demo_hw_timer_timing.c src_hw_timer_timing 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_timer_timing
 * \copydoc demo_hw_timer_timing.c
 */ 
 
/** [src_hw_timer_timing] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief  ��ʱ��0�жϴ�����
 * \param[in] p_arg : �ж���ڲ���
 * \return  ��
 */
void timer0_irq_handler (void *p_arg)
{
    /* �Ƿ�ƥ��ͨ��0 �ж� */
    if (amhw_timer_mat_pending_get(AMHW_TIMER0, 0) == TRUE) {  
        am_led_toggle(LED0);

        /* ����жϱ�־ */
        amhw_timer_mat_pending_clr(AMHW_TIMER0, 0);           
    }
}

/**
 * \brief ��ʼ����ʱ��0���ж�Ƶ��Ϊfreq_hz����
 *
 * \param[in] p_hw_timer : ָ��ʱ���Ĵ������ָ��
 * \param[in] chan       : ƥ��ͨ���ţ������÷�Χ0 ~ 3
 * \param[in] freq_hz    : �ж�Ƶ�ʲ�������λHz
 *
 * \return  ��
 */
void timer_init (amhw_timer_t *p_hw_timer, uint32_t chan, uint32_t freq_hz)
{
    uint32_t clkfreq;
        
    /* ��λ��ʱ������ֵ��Ԥ��Ƶ����ֵΪ0 */
    amhw_timer_reset(p_hw_timer);
    
    /* ���ö�ʱ��Ԥ��ƵΪ0 */
    amhw_timer_prescale_set(p_hw_timer, 0);
    
     /* ���ƥ���ж� */
    amhw_timer_mat_pending_clr(p_hw_timer, chan);
    
    /* ʹ��ƥ���¼���λ��ʱ����ֵ */
    amhw_timer_mat_reset_enable(p_hw_timer, chan);
    
    /* ʹ��ƥ���ж� */
    amhw_timer_mat_int_enable(p_hw_timer, chan);          
    
    clkfreq = amhw_clock_periph_freq_get(p_hw_timer);

    amhw_timer_mat_val_set(p_hw_timer, chan, clkfreq / freq_hz);
}

 

/**
 * \brief ������
 */
int main (void)
{
    /* �༶��ʼ�� */
    am_board_init();

    AM_DBG_INFO("The demo for simple timing function\r\n");
    
    /* ƽ̨��س�ʼ�� */
    amhw_plfm_timer0_timing_init();

    /* ��ʼ����ʱ��0���ж�Ƶ��Ϊ10Hz */
    timer_init(AMHW_TIMER0, 0, 10); 
    
    am_int_connect(INUM_TIMER0, timer0_irq_handler, (void *)0);

    /* ʹ�ܶ�ʱ��0�ж� */
    am_int_enable(INUM_TIMER0);
    
    /* ������ʱ������ʼ���� */
    amhw_timer_enable(AMHW_TIMER0);
    
    while (1) {
         __WFI();
    }
}

/** [src_hw_timer_timing] */

/* end of file */

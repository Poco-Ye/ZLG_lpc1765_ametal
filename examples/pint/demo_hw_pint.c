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
 * \brief GPIO�����жϣ�PINT�����̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *    1. PIO0_14�������ӵ�������
 *
 * - ʵ������
 *    1. ���°�����LED��״̬�仯��
 *
 * \par Դ����
 * \snippet demo_hw_pint.c src_hw_pint 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-08  asd, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_pint
 * \copydoc demo_hw_pint.c
 */

/** [src_hw_pint] */
#include "ametal.h"   
#include "am_board.h"


/**
 * \brief GPIO�������á�
 */
void pint_config (void)
{
    /* �������Ź��� */
    am_gpio_pin_cfg(PIO0_14, AM_GPIO_INPUT);
    
    /* ѡ�������ж�ͨ�� */
    amhw_inmux_pint_sel(AMHW_INMUX, AMHW_INMUX_CHAN_0, PIO0_14);
    
    /* ����Ϊ�½��ش��� */
    amhw_pint_trigger_select(AMHW_PINT, AMHW_PINT_CHAN_0, AMHW_PINT_TRIGGER_FALL);
}

/** 
 * \brief ƽ̨��ʼ����
 */
void plfm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_PINT);
    amhw_syscon_periph_reset(AMHW_RESET_PINT);

    amhw_clock_periph_enable(AMHW_CLOCK_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
}

/** 
 * \brief �����жϷ�������
 */
void pint_isr (void *p_arg)
{
    /* ����жϱ�־ */
    amhw_pint_status_clr(AMHW_PINT, AMHW_PINT_CHAN_0);
    
    am_led_toggle(0); 
}

/**
 * \brief ���������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�������ڰ弶��ʼ�����Ѿ���ʼ���ò��֣��ʲ���ִ�С� */
//    plfm_init();

    /* �����ж����� */
    pint_config();
    
    /* �����жϷ����� */
    am_int_connect(INUM_PIN_INT0, pint_isr, (void *)0);
    
    /* ʹ�������ж� */
    am_int_enable(INUM_PIN_INT0);
    
    while (1) {
       __WFI();
    }
}

/** [src_hw_pint] */

/* end of file */

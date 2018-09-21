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
 * \brief GPIO�����ж����̣�ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_14�������ӵ�������
 *   
 * - ʵ������
 *   1. ���°�����LED״̬�ı䡣
 * 
 * \par Դ����
 * \snippet demo_std_gpio_trigger.c src_std_gpio_trigger 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_gpio_trigger
 * \copydoc demo_std_gpio_trigger.c
 */

/** [src_std_gpio_trigger] */
#include "ametal.h" 
#include "am_board.h"


/**
 * \brief �����жϷ�����
 */
void gpio_isr (void *p_arg)
{
    am_led_toggle(0);
}

/**
 * \brief ���������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();

    /* �����жϷ����� */
    am_gpio_trigger_connect(PIO0_14, gpio_isr, (void *)0);

    /* ���ô������źʹ���ģʽ */
    am_gpio_trigger_cfg(PIO0_14, AM_GPIO_TRIGGER_FALL);

    /* ʹ�����Ŵ����ж� */
    am_gpio_trigger_on(PIO0_14);

    while (1) {
        __WFI();
    }
}

/** [src_std_gpio_trigger] */

/* end of file */

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
 * \brief LED���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��0.2s��ʱ������˸��
 * 
 * \par Դ����
 * \snippet demo_std_led.c src_std_led 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_led
 * \copydoc demo_std_led.c
 */

/** [src_std_led] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief ���������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();

    while (1) {
        am_led_on(LED0);
        am_mdelay(300);
        am_led_off(LED0);
        am_mdelay(300);
    }
}

/** [src_std_led] */

/* end of file */

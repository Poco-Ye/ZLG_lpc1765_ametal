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
 * \brief ���������̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ��������0.5s��ʱ�������С�
 *
 * \warning ������ռ����SCT_OUT5��PIO1_15���ţ��������ʹ�÷��������Ͳ��ܽ�SCT����
 *          Ϊ������PWM���ܡ�����Ҫ��Ӧ�ó�����ʹ��SCT���Ͳ��ܵ��÷�������API��
 *       
 *
 * \par Դ����
 * \snippet demo_std_buzzer.c src_std_buzzer 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_buzzer
 * \copydoc demo_std_buzzer.c
 */
 
/** [src_std_buzzer] */
#include "ametal.h"
#include "am_board.h"


/**
 * \brief ���������
 */
int main (void)
{  
    /* �弶��ʼ�� */
    am_board_init();
    
    am_buzzer_on();
    am_mdelay(500);
    am_buzzer_off();
    am_mdelay(500);
    
    while (1) {
        
        am_buzzer_beep(500);  /* ����������0.5s */
        am_mdelay(500);      
    }
}

/** [src_std_buzzer] */

/* end of file */

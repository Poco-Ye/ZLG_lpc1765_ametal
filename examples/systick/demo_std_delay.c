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
 * \brief ��ʱ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED0��˸Ƶ��10Hz
 *
 * \par Դ����
 * \snippet demo_std_delay.c src_std_delay
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_std_delay
 * \copydoc demo_std_delay.c
 */
 
/** [src_std_delay] */
#include "ametal.h"
#include "am_board.h"



/**
 * \brief ������
 */
int main (void)
{
    /*
     * �弶��ʼ��
     */
    am_board_init();

    AM_DBG_INFO("The demo for delay, The delay is implement through SYSTICK\r\n");
    
    am_delay_init();
    
    /* ��ʱ 1000us */
    am_udelay(1000);
    
    while (1) {
        
        am_led_toggle(LED0);
        
        /* ��ʱ100ms  */
        am_mdelay(100);
    }
}

/** [src_std_delay] */

/* end of file */

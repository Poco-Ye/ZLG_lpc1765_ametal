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
 * \brief ��ʱ����ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED��˸Ƶ��10Hz.
 *
 * \par Դ����
 * \snippet demo_std_timer_timing.c src_std_timer_timing
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_std_timer_timing
 * \copydoc demo_std_timer_timing.c
 */
 
/** [src_std_timer_timing] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief  ��ʱ��0�ص�����
 * \param[in] p_arg : �ص�������ڲ���
 * \return  ��
 */
void timer0_callback (void *p_arg)
{
    am_led_toggle(LED0);
}

/**
 * \brief ������
 */
int main (void)
{
    am_timer_handle_t  timer0_handle;
    am_timer_info_t    timer0_info;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��س�ʼ�� */
    amhw_plfm_timer0_timing_init();
    
    AM_DBG_INFO("The Timer demo for standard timing service\r\n");
    
    /* ��ʼ����ʱ��0Ϊ��ʱ���� */
    timer0_handle = amdr_timer_timing_init(&g_timer0_timing_dev, 
                                           &g_timer0_timing_devinfo); 

    am_timer_connect(timer0_handle);
    
    am_timer_info_get(timer0_handle, &timer0_info);
    
    /* STD��ʱ��ֻ֧��һ��ͨ������ͨ����һֱΪ0 */
    am_timer_callback_set(timer0_handle, 0, timer0_callback, NULL);
    
    while (1) {
        /* ʹ�ܶ�ʱ���ж�Ƶ��10Hz */
        am_timer_enable(timer0_handle, 0, timer0_info.clk_frequency / 10);
        am_mdelay(3000);
        am_timer_disable(timer0_handle, 0);
        am_mdelay(3000);
    }
}

/** [src_std_timer_timing] */

/* end of file */

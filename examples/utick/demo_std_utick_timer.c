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
 * \brief utick ��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED0 ��˸Ƶ��10Hz��
 *
 * \par Դ����
 * \snippet demo_std_utick_timer.c src_std_utick_timer 
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-17  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_std_utick_timer
 * \copydoc demo_std_utick_timer.c
 */
 
/** [src_std_utick_timer] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief  ��ʱ��0 �ص�����
 * \param[in] p_arg : �ص�������ڲ���
 * \return  None
 */
void utick_timing_callback (void *p_arg)
{
    am_led_toggle(LED0);
}

/**
 * \brief ������
 */
int main (void)
{
    am_timer_handle_t utick_handle;
    am_timer_info_t   utick_info;
    
    /* �༶��ʼ�� */
    am_board_init();
    
    /* utick ƽ̨��ʼ�� */
    amhw_plfm_utick_init();
    
    AM_DBG_INFO("The UTICK demo for standard timing service\r\n");
    
    /* ��ʼ��������0����Ϊ��ʱ���� */
    utick_handle = amdr_utick_init(&g_utick_dev, &g_utick_devinfo);
    
    am_timer_connect(utick_handle);
    
    am_timer_info_get(utick_handle, &utick_info);
    
    AM_DBG_INFO("The timer size is : %d-bit \r\n", 
                    AM_TIMER_SIZE_GET(utick_info.features));
                    
    AM_DBG_INFO("The timer clk_frequency: %d Hz\r\n", utick_info.clk_frequency);
    
    am_timer_callback_set(utick_handle, 0, utick_timing_callback, NULL);
    
    while (1) {

        am_timer_enable(utick_handle, 0, utick_info.clk_frequency / 10);
        am_mdelay(3000);
        am_timer_disable(utick_handle, 0);
        am_mdelay(3000);
    }
}

/** [src_std_utick_timer] */

/* end of file */

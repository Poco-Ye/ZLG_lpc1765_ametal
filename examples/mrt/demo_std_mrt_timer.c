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
 * \brief ��Ƶ�ʶ�ʱ����MRT�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 * 
 * \par Դ����
 * \snippet demo_std_mrt_timer.c src_std_mrt_timer 
 * 
 * \internal
 * \par History
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_std_mrt_timer
 * \copydoc demo_std_mrt_timer.c
 */

/** [src_std_mrt_timer] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief MRTͨ��0�ص�����
 */
void mrt_chan0_callback (void *p_arg) 
{
    /* LED0��ת */
    am_led_toggle(LED0);
}

/**
 * \brief ���������
 */
int main (void)
{  
    am_timer_handle_t mrt_handle; 
    am_timer_info_t   timer_info;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_mrt_init();
    
    AM_DBG_INFO("The MRT demo for standard timing service\r\n");
    
    mrt_handle = amdr_mrt_init(&g_mrt_dev, &g_mrt_devinfo);
    
    am_timer_connect(mrt_handle);
    
    am_timer_info_get(mrt_handle, &timer_info);
    
    AM_DBG_INFO("The timer size is : %d-bit \r\n",
                    AM_TIMER_SIZE_GET(timer_info.features));
                    
    AM_DBG_INFO("The timer clk_frequency: %d Hz\r\n", timer_info.clk_frequency);
    
    /* ʹ��ͨ��0����ͨ��0 ~ 3�� */
    am_timer_callback_set(mrt_handle, 0, mrt_chan0_callback, NULL);
    
    /* ʹ�ܶ�ʱ��10Hz�жϣ�ע�⣬���ֵΪ��0xFFFFFF */
    am_timer_enable(mrt_handle, 0, timer_info.clk_frequency / 10);
    
    while (1) {
        __WFI();
    }
}

/** [src_std_mrt_timer] */

/* end of file */

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
 * \brief SCTʵ�ֱ�׼��ʱ�����̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 *
 * \par Դ����
 * \snippet demo_std_sct_timer.c src_std_sct_timer
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */

 
/**
 * \addtogroup demo_if_std_sct_timer
 * \copydoc demo_std_sct_timer.c
 */
 
/** [src_std_sct_timer] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief  ��ʱ��0�ص�����
 * \param[in] p_arg : �û��Զ����������am_timer_callback_set() �������ݡ�
 * \return  ��
 */
void sct0_timing_callback (void *p_arg)
{
    am_led_toggle(LED0);
}

/**
 * \brief ���������
 */
int main (void)
{
    am_timer_handle_t sct0_timing_handle;
    am_timer_info_t   sct0_timing_info;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    amhw_plfm_sct0_timing_init();
    
    AM_DBG_INFO("The SCT demo for standard timing service\r\n");
    AM_DBG_INFO("The led toggle in 10Hz \r\n");
    
    /* ��ʼ����ʱ��0Ϊ��ʱ���� */
    sct0_timing_handle = amdr_sct_timing_init(&g_sct0_timing_dev, 
                                              &g_sct0_timing_devinfo); 
    am_timer_connect(sct0_timing_handle);
    
    am_timer_info_get(sct0_timing_handle, &sct0_timing_info);
    
    AM_DBG_INFO("The timer size is : %d-bit \r\n", 
                    AM_TIMER_SIZE_GET(sct0_timing_info.features));
                    
    AM_DBG_INFO("The timer clk_frequency: %d Hz\r\n", sct0_timing_info.clk_frequency);
  
    am_timer_callback_set(sct0_timing_handle, 1, sct0_timing_callback, NULL);
    
    while (1) {
        
        /* ʹ�ܶ�ʱ���ж�Ƶ��Ϊ10Hz */
        am_timer_enable(sct0_timing_handle, 1, sct0_timing_info.clk_frequency / 10);
        am_mdelay(3000);
        am_timer_disable(sct0_timing_handle, 1);
        am_mdelay(3000);
    }
}

/** [src_std_sct_timer] */

/* end of file */

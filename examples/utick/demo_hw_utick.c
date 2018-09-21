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
 * \brief utick��ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED0��˸Ƶ��10Hz��
 *   2. �������WDTʱ��ԴƵ�ʡ�
 *
 * \par Դ����
 * \snippet demo_hw_utick.c src_hw_utick 
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */
 
 /**
 * \addtogroup demo_if_hw_utick
 * \copydoc demo_hw_utick.c
 */
 
/** [src_hw_utick] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief UTICK �жϴ�����
 * \param[in]  p_arg  : �ж���ڲ���
 * \return �� 
 */
void utick_irq_handler (void *p_arg)
{
    if (amhw_utick_int_flag_check(AMHW_UTICK) == TRUE) {
        
        am_led_toggle(LED0);
        amhw_utick_int_flag_clr(AMHW_UTICK);
    }
}

/**
 * \brief  ������
 */
int main (void)
{   
    uint32_t ticks;
    
    /* 
     * �弶��ʼ��
     */
    am_board_init();

    AM_DBG_INFO("The demo for UTICK\r\n");
    
    /* utickƽ̨��ʼ�� */
    amhw_plfm_utick_init();
 
    /* 
     * ��ʱ 100ms 
     * ���ֵ��0x7FFFFFFF����ʱ 0x80000000 ���δ�ʱ�ӡ�
     * ��g_wdtosc_clkfreq = 500kHz, �����ʱʱ�� :
     *    0x80000000 / 500000 = 4294s
     * 
     * ��Сֵ�� 1����ʱ ���δ�ʱ�ӣ� 
     * �� g_wdtosc_clkfreq = 500kHz, ��С��ʱʱ�� :
     *    2 / 500000 = 4us
     */
    ticks = 100 * g_wdtosc_clkfreq / 1000;
         
    /* ����tick, FALSE��������ʱֻ��ִ��һ�� */
    amhw_utick_tick_set(AMHW_UTICK, ticks, FALSE);
     
    /* �ȴ���ʱ��� */
    while(amhw_utick_int_flag_check(AMHW_UTICK) == FALSE);
      
    amhw_utick_int_flag_clr(AMHW_UTICK);
    
    /* ����tick, TRUE��������ʱ�ظ�ִ�� */
    amhw_utick_tick_set(AMHW_UTICK, ticks, TRUE);    
    
    am_int_connect(INUM_UTICK, utick_irq_handler, (void *)0);     
    
    /* ʹ��UTICK�ж� */
    am_int_enable(INUM_UTICK);     

    AM_DBG_INFO("The WDT OSC freq is %d Hz \r\n", g_wdtosc_clkfreq);
 
    while (1) {
        __WFI();
    }
}

/** [src_hw_utick] */

/* end of file */

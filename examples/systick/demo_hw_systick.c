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
 * \brief SYSTICK��ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 *   ������ʱ������ʹ��SYSTICKʵ�֣��ʴ��ļ��в���ʹ����ʱ����
 *
 * - ʵ������:
 *   1. LED0��˸Ƶ��10Hz
 *
 * \par Դ����
 * \snippet demo_hw_systick.c src_hw_systick
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_systick
 * \copydoc demo_hw_systick.c
 */
 
/** [src_hw_systick] */
#include "ametal.h"
#include "am_board.h"



/**
 * \brief SYSTICK �жϴ�����
 * \return ��
 * \note SYSTICK�жϴ��������ں��жϣ����������
 *       am_int_connect() �� am_int_enable() ������
 */
void SysTick_Handler(void)
{
    am_led_toggle(LED0);
}

/**
 * \brief ������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();

    AM_DBG_INFO("The demo for SYSTICK\r\n");
    
    /* ʹ��ϵͳʱ����ΪSYSTICKʱ��Դ */
    am_systick_config(AMHW_SYSTICK, AMHW_SYSTICK_CONFIG_CLKSRC_SYSTEM);
    
    /* ��������ֵ�����ֵΪ0xFFFFFF */
    am_systick_reload_val_set(AMHW_SYSTICK, g_system_clkfreq / 10);    
    
    /* ���õ�ǰ��ֵΪ0 */
    am_systick_val_set(AMHW_SYSTICK, 0);
    
    /* ʹ��SYSTICK�ж� */
    am_systick_int_enable(AMHW_SYSTICK);
    
    /* ʹ��SYSTICK����ʼ���¼��� */
    am_systick_enable(AMHW_SYSTICK);
    
    while (1) {
        __WFI();
    }
}

/** [src_hw_systick] */

/* end of file */

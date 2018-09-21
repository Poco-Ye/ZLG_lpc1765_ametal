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
 * \brief WWDT���Ź���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 * 
 * - ʵ������:
 *   1. �ڳ�ʱǰ5�α����жϷ�����ִ��ι������
 *   2. Ȼ��2�������ʱ, LED0���������Ҵ������"Watchdog reset occurred"��
 *
 * \par Դ����
 * \snippet demo_hw_wwdt.c src_hw_wwdt 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  fft, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_wwdt
 * \copydoc demo_hw_wwdt.c
 */

/** [src_hw_wwdt] */
#include "ametal.h"
#include "am_board.h"
 
static volatile uint8_t wdt_update_count;

/** 
 * \brief ���Ź���ʱ�����жϴ�����
 * \param[in] p_arg : ��ڲ���
 * \return  ��
 */
void wdt_irq_handler (void *p_arg)
{
    uint32_t wdt_status = amhw_wwdt_status_get(AMHW_WWDT);
    
    /* ���Ź���ʱ�����ֳ�ʱ״̬ */
    if (wdt_status & AMHW_WWDT_WDMOD_WDTOF) {

        amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDTOF);
    }

    /*  */
    if (wdt_status & AMHW_WWDT_WDMOD_WDINT) {

        amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDINT);
        
        if (wdt_update_count < 5) {      /* �ڳ�ʱǰ5�α����жϷ�����
                                            ִ��ι������Ȼ�������Ź���λ */
            amhw_wwdt_feed(AMHW_WWDT);
            wdt_update_count++;
            AM_DBG_INFO("The %d times feed\r\n", wdt_update_count);
        }
    }
}

/**
 * \brief ������
 */
int main (void)
{
    uint32_t wdt_freq;

    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_wwdt_init();

    AM_DBG_INFO("The wdt osc freq is %d\r\n", g_wdtosc_clkfreq);
    
    /* ���Ź���ʱ��Ƶ��Ϊ����ʱ��Ƶ��4��Ƶ */
    wdt_freq = g_wdtosc_clkfreq / 4;
    
    /* ��⿴�Ź��Ƿ�λ */
    if (amhw_wwdt_status_get(AMHW_WWDT) & AMHW_WWDT_WDMOD_WDTOF) {
        am_led_set(0, TRUE);
        AM_DBG_INFO("Watchdog reset occurred\r\n");
        amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDTOF);
    }

    /* WWDT��ʼ�� */
    amhw_wwdt_init(AMHW_WWDT);

    /* 
     * ����Ϊ��ʱ�������Լ2s
     * ���ÿ��Ź�����ʱ��Ϊ512 ticks
     * ���ÿ��Ź����ڶ�ʱ��ʱ��Ϊ1s
     */
    amhw_wwdt_timeout_set(AMHW_WWDT, wdt_freq * 2);
    amhw_wwdt_warning_set(AMHW_WWDT, 1023);
    
    /* 
     * ��WWDT����ֵ���ڴ���ֵ�����������ι������
     */
    amhw_wwdt_window_set(AMHW_WWDT, wdt_freq * 1);

    /* �����ڳ�ʱ��λ */
    amhw_wwdt_option_set(AMHW_WWDT, AMHW_WWDT_WDMOD_WDRESET);

    /* ��������ͳ�ʱ�ж� */
    amhw_wwdt_status_clr(AMHW_WWDT, AMHW_WWDT_WDMOD_WDTOF | AMHW_WWDT_WDMOD_WDINT);

    am_int_connect(INUM_WWDT, wdt_irq_handler, (void *)0);
    am_int_enable(INUM_WWDT);

    /* �������Ź���ʱ�� */
    amhw_wwdt_start(AMHW_WWDT);

    while (1) {
        __WFI();
    }
}

/** [src_hw_wwdt] */

/* end of file */

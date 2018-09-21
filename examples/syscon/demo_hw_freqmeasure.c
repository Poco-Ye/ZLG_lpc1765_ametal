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
 * \brief Ƶ�ʲ�����ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. �������WDT��RTCʱ��ԴƵ��
 *
 * \par Դ����
 * \snippet demo_hw_freqmeasure.c src_hw_freqmeasure
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
 
/**
 * \addtogroup demo_if_hw_freqmeasure
 * \copydoc demo_hw_freqmeasure.c
 */
 
/** [src_hw_freqmeasure] */
#include "ametal.h"
#include "am_board.h"



/**
 * \brief Ƶ�ʲ�������
 *
 * \param[in] ref_clksrc  : �ο�ʱ��ԴThe reference clock source for freq measure 
 * \param[in] targ_clksrc : Ŀ��ʱ��ԴThe target clock source for freq measure 
 * \param[in] ref_clkfreq : �ο�ʱ��Ƶ��The reference clock frequency
 *
 * \return  Ŀ��ʱ��Դ��Ƶ��
 *
 * \note �ο�Ƶ��Ҫ�����Ŀ��Ƶ��
 */
uint32_t freq_measure(amhw_inmux_freqmsr_src_t  ref_clksrc, 
                      amhw_inmux_freqmsr_src_t  targ_clksrc, 
                      uint32_t                  ref_clkfreq)
{
    

    amhw_inmux_freqmsr_refclk_set(AMHW_INMUX, ref_clksrc);
    amhw_inmux_freqmsr_targclk_set(AMHW_INMUX, targ_clksrc); 
    
    /* ����Ƶ�ʲ��� */
    amhw_syscon_freqmeas_start();
    
    /* �ȴ�������� */
    while (amhw_syscon_freqmsr_complete_chk() == FALSE);
    
    return amhw_syscon_freqmeas_targfreq_get(ref_clkfreq);
    
}

/** 
 * \brief ƽ̨��ʼ��
 *
 * ʹ�ܲ���λ��������ʱ�ӣ��Լ�������ص�ƽ̨��ʼ��
 *
 * \return  None
 */
void amhw_plfm_init (void)
{
    /* ʹ�ܲ���λ��������ʱ�� */
    amhw_clock_periph_enable(AMHW_CLOCK_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
    
    amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);   /* ��WDTʱ�� */
    amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);   /* ��WDTʱ�� */
}

/**
 * \brief ������
 */
int main (void)
{
    uint32_t wdtosc_freq;
    uint32_t rtcosc_freq;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    AM_DBG_INFO("The demo for frequency measure\r\n");
    
    /* ƽ̨��س�ʼ�� */
    amhw_plfm_init();
    
    /* ��ʱ����Ϊ�ο�ʱ�ӣ�WDTʱ����ΪĿ��ʱ�� */
    wdtosc_freq = freq_measure(AMHW_INMUX_FREQMSR_SRC_MAINCLK, 
                               AMHW_INMUX_FREQMSR_SRC_WDTOSC, 
                               g_main_clkfreq);
    

    AM_DBG_INFO("The watch dog OSC clock rate is %d Hz\r\n", wdtosc_freq);
 
    /* IRCʱ����Ϊ�ο�ʱ�ӣ�RTC��ΪĿ��ʱ�� */
    rtcosc_freq = freq_measure(AMHW_INMUX_FREQMSR_SRC_IRC, 
                               AMHW_INMUX_FREQMSR_SRC_32KHZOSC, 
                               amhw_clock_irc_rate_get());
  
    AM_DBG_INFO("The RTC OSC clock rate is %d Hz\r\n", rtcosc_freq); 
 
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_hw_freqmeasure] */

/* end of file */



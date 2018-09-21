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
 * \brief ������ʾ���̣���˯��ģʽ�л���ϵͳ��ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. LED0��1sʱ������˸��
 *
 * \par Դ����
 * \snippet demo_hw_wakeup.c src_hw_wakeup 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_wakeup
 * \copydoc demo_hw_wakeup.c
 */
/** [src_hw_wakeup] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief  MRT �жϴ�����
 * \param[in] p_arg : �ж���ڲ��� 
 * \return  None
 */
void mrt_irq_handler (void *p_arg)
{
    amhw_mrt_int_pending_clr(AMHW_MRT, AMHW_MRT_CH(0));
}

/**
 * \brief ������
 */
int main (void)
{
    amhw_clock_main_src_t saved_clksrc;  /* ����ñ�����Ϊ�˱���ʱ�� */

    /* �弶��ʼ�� */
    am_board_init();

    /* MRT ƽ̨��ʼ�� */
    amhw_plfm_mrt_init();
 
    /* ���ROM�汾�� */
    AM_DBG_INFO("ROM version = %04x\r\n", amhw_power_rom_ver_get());

    /* �л���ʱ��λIRC���ҹر�PLL��Դ */
    saved_clksrc = amhw_clock_main_src_get();
    if (saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
        
        /* ����PLL�����Ϊ��ʱ�� */
        amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);  
        amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);
        
        amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_clock_main_clkrate_get());
    }

    /*
     * ��һ�μ�ʱ�ж�ģʽ�²���ͨ��0��1s���ж�
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(0), AMHW_MRT_MODE_ONESHOT);
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(0), amhw_clock_irc_rate_get(), TRUE);
    amhw_mrt_int_enable(AMHW_MRT, AMHW_MRT_CH(0)); 

    am_int_connect(INUM_MRT, mrt_irq_handler, (void *)0);
    am_int_enable(INUM_MRT);

    /* ʹ��MRT���� */
    amhw_syscon_wakeup_enable(AMHW_SYSCON_STARTER_MRT);

    AM_DBG_INFO("enter power down mode !");

    while (1) {
    
       /* 
        * ����˯��ģʽ
        */
        amhw_power_mode_enter(AMHW_POWER_MODE_SLEEP, 0);
        
        /* �ȴ������� */
        AM_DBG_INFO("wake up !\r\n");
        
        /* �л����ı䣩ʱ��ԴλPLL��� */
        if (saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            
            /* ��PLL��Դ */
            amhw_syscon_powerup(AMHW_SYSCON_PD_SYS_PLL);
            
            /* �ȴ�PLL ʱ�� */
            while (amhw_pll_locked_chk() == FALSE) {}
                
            amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_pll_out_clkrate_get());
                
            /* ����PLL���λ��ʱ�� */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);
                
            /* 
             * ����ʱ��Ƶ��
             * ���� g_main_clkfreq, g_system_clkfreq �� g_async_clkfreq
             */
            amhw_clock_freq_update();  
                
            AM_DBG_INFO("The main clock freq is %d Hz\r\n", g_main_clkfreq);
        }
        
        // ������
        
        /* ��������ɣ��ر�PLL��Դ */
        if (saved_clksrc == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
            
            /* ����IRCΪ��ʱ��  */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);  
            amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);
            
            amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_clock_main_clkrate_get());
        }

        amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(0), amhw_clock_main_clkrate_get(), TRUE);
        am_led_toggle(LED0);
    }
}

/** [src_hw_wakeup] */

/* end of file */

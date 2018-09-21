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
 * \brief ϵͳ��ʼ������
 *
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
 
#include "am_system.h"
#include "am_prj_config.h"

extern uint32_t gc_vectors[];    /* �� am_startup_armcc_lpc5410x.s �ļ��ж��� */

/**
 * \brief �ú����ڸ�λ����ã��ڸ�λ�������á�
 *
 * ��λ������ am_startup_armcc_lpc5410x.s �ļ��ж���
 *
 */
void SystemInit (void) 
{

/* ��M4���ϣ�����FPU��ʹ��ǰ������CPACR�Ĵ���ʹ��FPU */
#if (__FPU_PRESENT == 1)
    SCB->CPACR |= ((3UL << 10*2) |                 /* ���� CP10 ��ȫ����    */
                   (3UL << 11*2));                 /* ���� CP11 ��ȫ����    */
#endif

    /* �����ж��������ַ*/
    SCB->VTOR = ((uint32_t)(&gc_vectors[0])) & SCB_VTOR_TBLOFF_Msk;
}

#ifdef AM_CORTEX_M4

/** 
 * \brief ϵͳ��ʼ������
 *
 * ʹ��PLL�õ����ߵ�ʱ��Ƶ�� 
 */
void am_system_init (void)
{
    amhw_pll_stat_t stat;
    
    /* IRC������IRC��Ԫ�ϵ� */
    amhw_syscon_powerup(AMHW_SYSCON_PD_IRC_OSC | AMHW_SYSCON_PD_IRC);
    
    if (AM_CFG_MAIN_CLK_SRC  == AMHW_CLOCK_MAIN_SRC_PLLOUT ||
        AM_CFG_ASYNC_CLK_SRC == AMHW_CLOCK_ASYNC_SRC_PLLOUT) {
            
        /* ������PLL֮ǰ���л���ʱ��ԴΪIRC */
        amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);

#if (AM_CFG_PLL_USEPRECISE == 0)
            
        stat = amhw_pll_config(AM_CFG_PLL_CLK_SRC, 
                               AM_CFG_PLLOUT_FREQ, 
                               FALSE);
#else 
        stat = amhw_pll_config(AM_CFG_PLL_CLK_SRC, 
                               AM_CFG_PLLOUT_FREQ, 
                               TRUE);
#endif
    }

    amhw_clock_system_clkdiv_set(AM_CFG_SYSTEM_CLK_DIV);
    
    if (AM_CFG_MAIN_CLK_SRC  == AMHW_CLOCK_MAIN_SRC_PLLOUT) {
        
        if (stat == AMHW_PLL_SUCCESS) {
        
            /* ������ʱ��ԴΪPLL��� */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_PLLOUT);
        } else {
        
            /* PLL����ʧ��, ������ʱ��ԴΪIRC */
            amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);
        }
        
    } else {
         amhw_clock_main_src_set(AM_CFG_MAIN_CLK_SRC);
    }
    
    /* ʹ���첽ϵͳ */
    amhw_syscon_async_enable();
    
    /* �����첽ʱ�ӷ�Ƶֵ */
    amhw_clock_async_clkdiv_set(AM_CFG_ASYNC_CLK_DIV);    
    
    if (AM_CFG_ASYNC_CLK_SRC == AMHW_CLOCK_ASYNC_SRC_PLLOUT) {
        if (stat == AMHW_PLL_SUCCESS) {
        
            /* �����첽ʱ��ԴΪPLL��� */
            amhw_clock_async_src_set(AMHW_CLOCK_ASYNC_SRC_PLLOUT);
        } else {
        
            /* PLL����ʧ��, �����첽ʱ��ԴΪIRC */
            amhw_clock_async_src_set(AMHW_CLOCK_ASYNC_SRC_IRC);
        }
    } else {
        amhw_clock_async_src_set(AM_CFG_ASYNC_CLK_SRC);
    }

    /* 
     * ����ʱ��Ƶ��ֵ
     * ������ g_main_clkfreq, g_system_clkfreq �� g_async_clkfreq
     */
    amhw_clock_freq_update();  

    /* ���±�ʾWDT���������Ƶ��ȫ�ֱ���g_wdtosc_clkfreq��ֵ */
    amhw_clock_wdt_freq_update();
}

#else 

void am_system_init (void)
{    
    /* 
     * ����ʱ��Ƶ��ֵ
     * ������ g_main_clkfreq, g_system_clkfreq �� g_async_clkfreq
     */
    amhw_clock_freq_update();  

    /* ���±�ʾWDT���������Ƶ��ȫ�ֱ���g_wdtosc_clkfreq��ֵ */
    amhw_clock_wdt_freq_update();
}

#endif /* AM_CORTEX_M4 */

/* end of file */

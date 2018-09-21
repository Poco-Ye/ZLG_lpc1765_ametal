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
 * \brief LPC5410X ADC �û������ļ���
 * \sa amdr_hwconfig_adc.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  asd, first implementation.
 * \endinternal
 */
 
#include "amdr_hwconfig_adc.h"

/**
 * \addtogroup amdr_if_hwconfig_src_adc
 * \copydoc amdr_hwconfig_adc.c
 * @{
 */


/** \brief ADC0 �ж����� */
#define ADC_INT_CNTS         1

/** \brief ADC0 �жϺ����� */
static uint8_t intnums[ADC_INT_CNTS] = {
    INUM_ADC0_SEQA
};

/** \brief ADC0 �豸��Ϣ */
const amdr_adc_devinfo_t g_adc0_devinfo =
{
    AMHW_ADC0,                     /**< \brief ָ��ADC0�Ĵ������ָ�� */
    intnums,                       /**< \brief ADC0�жϺ�����         */
    ADC_INT_CNTS,                  /**< \brief ADC0�жϺ�����         */
    12,                            /**< \brief ADC0��������           */
    3270,                          /**< \brief ADC0�ο���ѹ����λ��mV */
    0                              /**< \brief ADC0����ʱ�ӷ�Ƶ       */
};

/** \brief ADC0�豸ʵ�� */
amdr_adc_dev_t g_adc0_dev;

/** 
 * \brief ADC0 ƽ̨��ʼ����
 */
void amdr_plfm_adc0_init (void)
{    
    /*  
     * ��ʼ��ADC0
     */
    amhw_syscon_powerup(AMHW_SYSCON_PD_ADC0     | 
                        AMHW_SYSCON_PD_VDDA_ENA |
                        AMHW_SYSCON_PD_VREFP);
    
    amhw_clock_periph_enable(AMHW_CLOCK_ADC0);
    amhw_syscon_periph_reset(AMHW_RESET_ADC0);
    
    amhw_clock_adc_src_set(AMHW_CLOCK_ADC_SRC_MAINCLK);
    amhw_clock_adc_clkdiv_set(0x01);
}

/** 
 * \brief ADC0 ƽ̨ȥ��ʼ����
 */
void amdr_plfm_adc0_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_ADC0);
    amhw_clock_periph_disable(AMHW_CLOCK_ADC0);
}


/**
 * @}
 */

/* end of file */

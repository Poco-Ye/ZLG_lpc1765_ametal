/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC Ӳ�������ӿ�ʵ�֡�
 *
 * - 12λ��αƽ�����ģת������
 * - ģ���������Ŷ��12����
 * - 2������������ת�����С�
 * - ��ѡ���/����ֵ�ȽϺ͡���㴩Խ����⡣
 * - ��ѹ������Χ�� Vrefn �� Vrefp (����ֵΪ 3V; ���ɳ��� VDD �ĵ�ѹֵ).
 * - 12λ��ת�����ʸߴ� 4.8 MHz. �ɼ�Сת��������ʵ�ָ��ߵ�ת�����ʡ�
 * - ͻ��ת��ģʽ֧�ֵ�ͨ�����ͨ�����롣
 * - ͬ�����첽�������� ADC ��ʱ��Ƶ���ڣ��첽�����������Ӧ��ͬ��ģʽ�ɼ���
 *   Ǳ�ڵĴ������š�������ȷ���������򶶶�����Ĵ�����Ӧ�ȡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-21  hbt, first implementation.
 * \endinternal
 */

#include "amhw_adc.h"

/* ��ʱ��Ƶ�� */
extern uint32_t g_main_clkfreq; 

/******************************************************************************
* Public functions
*******************************************************************************/

/**
 * \brief ���� ADC
 */
int amhw_adc_startup (amhw_adc_t *p_hw_adc)
{
    int i;
    
    amhw_adc_startup_set(p_hw_adc, AMHW_ADC_STARTUP_ENA);
    
    for (i = 0; i < 0x10; i++) {}

    amhw_adc_startup_set(p_hw_adc, AMHW_ADC_STARTUP_ENA | 
                                   AMHW_ADC_STARTUP_INIT);

    i = 0x7FFFF;
    while ((amhw_adc_startup_get(p_hw_adc) & AMHW_ADC_STARTUP_INIT) && --i );
        
    return i ? AM_OK : -AM_ETIME;
}

/**
 * \brief ADC У��
 */
void amhw_adc_calibrate (amhw_adc_t *p_hw_adc, uint32_t sysclk_freq)
{
    int i;
    
    /* 
     * ��δ��У�飬�����У�顣
     */
    if (amhw_adc_calib_isrun(p_hw_adc)) {
        uint32_t ctrl = amhw_adc_ctrl_get(p_hw_adc) & (0x00007FFF);
        uint32_t tmp  = ctrl;

        /* ���� ADC �첽ģʽ */
        tmp &= ~(1 << 8);
        
        /* Ϊ����˳�����У�飬ADCƵ��Ӧ�� 1MHz �� 30MHz ֮�� */
        if (sysclk_freq > 1000000UL) {
            tmp |= (((sysclk_freq / 1000000UL) - 1) & 0xFF);
            amhw_adc_config(p_hw_adc, tmp);
        }

        /* ʹ��У�� */
        amhw_adc_calib_enable(p_hw_adc);
        
        i = 0xF0000;
        while (amhw_adc_calib_get(p_hw_adc) && --i);
        
        amhw_adc_config(p_hw_adc, ctrl);
    }
}

/* end of file */

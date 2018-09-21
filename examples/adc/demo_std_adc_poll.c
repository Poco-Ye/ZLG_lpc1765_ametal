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
 * \brief ADC���̣����ò�ѯ��ʽ��ȡADCת�������ͨ����׼�ӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_0��������PC���ڵ�TXD��
 *   2. PIO0_1��������PC���ڵ�RXD��
 *   3. PIO0_29(ADCͨ��0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ���������ѹ����ֵ��
 *
 * \par Դ����
 * \snippet demo_std_adc_poll.c src_std_adc_poll
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_adc_poll
 * \copydoc demo_std_adc_poll.c
 */

/** [src_std_adc_poll] */
#include "ametal.h"
#include "am_board.h"

/** \brief ADC��׼���������� */ 
am_adc_handle_t g_adc0_handle;

/**
 * \brief ���������
 */
int main (void)
{
    uint32_t adc_bits = 0; 
    uint32_t adc_vref = 0;
    uint32_t adv_val[10];
    int i;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amdr_plfm_adc0_init(); 
    
    /* ����ADCģ���������� */
    am_gpio_pin_cfg(PIO0_29, PIO0_29_ADC_IN0 | PIO0_29_INACTIVE);  

    /* ��ʼ��ADC������ȡADC��׼���������� */
    g_adc0_handle = amdr_adc_init(&g_adc0_dev, &g_adc0_devinfo);

    /* ��ȡADCת������ */
    adc_bits = am_adc_bits_get(g_adc0_handle); 
    
    /* ��ȡADC�ο���ѹ����λ��mV */
    adc_vref = am_adc_vref_get(g_adc0_handle);
    
    while (1) {
        
        /* ��ͨ�����ݼĴ�����ȡADCת����� */
        am_adc_sync_read(g_adc0_handle, AMHW_ADC0_CHAN_0,adv_val,10);
        
        am_kprintf("The ADC value channel 0: \r\n");
        
        for (i = 0; i < 10; i++) {
            /* �������������ѹֵ */
            am_kprintf("%d mV ", adv_val[i] * adc_vref / ((1UL << adc_bits) - 1));
        }
        
        am_kprintf("\r\n");

        am_mdelay(500);
    }
}

/** [src_std_adc_poll] */
 
/* end of file */

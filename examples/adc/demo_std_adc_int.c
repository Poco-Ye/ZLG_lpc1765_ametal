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
 * \brief ADC���̣������жϷ�ʽ��ȡADCת�������ͨ����׼�ӿ�ʵ��
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
 * \snippet demo_std_adc_int.c src_std_adc_int
 *
 * \internal
 * \par Modification History
 * - 1.00 14-01-10  asd, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_adc_int
 * \copydoc demo_std_adc_int.c
 */

/** [src_std_adc_int] */
#include "ametal.h"  
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

/** \brief ADC���ݻ����� */
uint32_t g_adc_val;

/** \brief ADCת����ɱ�־ */
volatile bool_t g_complete_flag = FALSE;

/** \brief ADC��׼���������� */ 
am_adc_handle_t g_adc0_handle;


/**
 * \brief ADC�жϷ�����
 */
void adc_complete (void *p_arg)
{
    g_complete_flag = TRUE;
}

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
        
        g_complete_flag = FALSE;          /* ת����ɱ�־ */
        
        /* �첽��ȡת����� */
        am_adc_async_read(g_adc0_handle, AMHW_ADC0_CHAN_0,adv_val,10, adc_complete,NULL);
        
        while (g_complete_flag == FALSE); /* �ȴ�ת����� */
        
        am_kprintf("The ADC value channel 0: \r\n");
        
        for (i = 0; i < 10; i++) {
            /* �������������ѹֵ */
            am_kprintf("%d mV ", adv_val[i] * adc_vref / ((1UL << adc_bits) - 1));
        }
        
        am_kprintf("\r\n");

        am_mdelay(500);
    }
}

/** [src_std_adc_int] */
 
/* end of file */

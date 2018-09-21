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
 * \brief APL_StartKit ADC��ʾ����
 *
 * - ��������:
 *   1. ��APL_StartKit���ӵ�EasyARM-54000M4 demo�壻
 *   2. ������ñ����ADCͨ��3�����������ADC0����
 *   3. ��APL_StartKit����ϴ���0�ӿڣ�J3�����ӵ�PC���ϡ�
 *
 * - ʵ������:
 *   1. ͨ�����ڴ�ӡ��ADCͨ��3��ǰ�ĵ�ѹֵ���ı�ɵ����裬��ѹֵҲ��֮�ı䡣
 *
 * \par Դ����
 * \snippet demo_apl_startkit_adc.c src_apl_startkit_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 14-01-10  asd, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_apl_startkit_adc
 * \copydoc demo_apl_startkit_adc.c
 */

/** [src_apl_startkit_adc] */
#include "ametal.h"  
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

/** \brief ADC���ݻ����� */
uint32_t g_adc_val;

/** \brief ADC��ȡ��ɱ�־ */
volatile bool_t g_flag = TRUE;

/** \brief ADC��׼���������� */ 
am_adc_handle_t g_adc0_handle;


/**
 * \brief ADC�жϷ�����
 */
void adc_isr (void *p_arg)
{
    /* 
     * ʹ���жϻ�ȡADCת�����ʱ�������ȫ�����ݼĴ�����ȡ���ݣ�����ͬʱ����
     * ����жϱ�־��
     */
    g_adc_val = am_adc_global_read(g_adc0_handle);
    
    g_flag = TRUE;
}

/**
 * \brief ���������
 */
int main (void)
{
    uint32_t adc_bits = 0;  
    uint32_t adc_vref = 0;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amdr_plfm_adc0_init(); 
    
    /* ����ADCģ���������� */
    am_gpio_pin_cfg(PIO1_0, PIO1_0_ADC_IN3 | PIO1_0_INACTIVE);  

    /* ��ʼ��ADC������ȡADC��׼���������� */
    g_adc0_handle = amdr_adc_init(&g_adc0_dev, &g_adc0_devinfo);

    /* ��ȡADCת������ */
    adc_bits = am_adc_get_bits(g_adc0_handle);
    
    /* ����ADC�жϷ���������ʹ���ж� */
    am_int_connect(INUM_ADC0_SEQA, adc_isr, (void *)0); 
    am_int_enable(INUM_ADC0_SEQA);

    /* ��ȡADC�ο���ѹ����λ��mV */
    adc_vref = am_adc_get_vref(g_adc0_handle);
    
    /* ����ADCת�� */
    am_adc_start(g_adc0_handle, AMHW_ADC0_CHAN_3); 
    
    while (1) {
        if (g_flag == TRUE) {
            g_flag = FALSE;               /* �����ɱ�־ */
            
            /* ���������ѹ����ֵ */
            am_kprintf("The ADC voltage value: %d mV \r\n", g_adc_val * adc_vref / 
                                                      ((1UL << adc_bits) - 1));
            am_mdelay(200);
            
            /* ������һ��ADת�� */
            am_adc_start(g_adc0_handle, AMHW_ADC0_CHAN_3); 
        }
    }
}

/** [src_apl_startkit_adc] */
 
/* end of file */

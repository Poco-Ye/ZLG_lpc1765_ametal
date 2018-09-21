/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co.,  Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC��ֵ�Ƚϵ����̣�ͨ��HW��Ľӿ�ʵ��
 *  
 * - ������չʾ��2����ֵ�Ƚϣ�
 *   1. ��ֵ�Ƚ� 0: ��Χ�Ƚϣ�
 *   2. ��ֵ�Ƚ� 1: ��Խ�Ƚϡ�
 *
 * - �������裺
 *   1. PIO0_0��������PC���ڵ�TXD��
 *   2. PIO0_1��������PC���ڵ�RXD��
 *   3. PIO0_29(ADCͨ��0) ����ģ������1��
 *   3. PIO0_29(ADCͨ��1) ����ģ������2��
 *   4. ������ͨ����ģ�������ѹ�ֱ��0����3200 mV��
 *
 * - ʵ������
 *   1. ģ������1�ĵ�ѹ����1100mV�����2500mVʱ�����ڻ������ѹֵ���ȽϽ����
 *   1. ģ������2�ĵ�ѹ�仯����1100mV��2500mVʱ�����ڻ������ѹֵ���ȽϽ����
 *
 *
 * \par Դ����
 * \snippet demo_hw_adc_thcmp.c src_hw_adc_thcmp
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-20  hbt, modified.
 * - 1.00 14-12-08  asd, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_hw_adc_thcmp
 * \copydoc demo_hw_adc_thcmp.c
 */

/** [src_hw_adc_thcmp] */
#include "ametal.h"  
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"

/** \brief �ͱȽ���ֵ(mV)  */
#define THRE_LOW            ((1100 * 4095) / 3200)

/** \brief �߱Ƚ���ֵ(mV) */
#define THRE_HIGH           ((2500 * 4095) / 3200)


bool_t g_tc0_flag;  /** \brief ��ֵ�Ƚ�0�жϱ�־ */
bool_t g_tc1_flag;  /** \brief ��ֵ�Ƚ�1�жϱ�־ */

uint32_t g_val_chan0; /** \brief ADCͨ��0���ݻ����� */
uint32_t g_val_chan1; /** \brief ADCͨ��1���ݻ����� */

/** 
 * \brief ADC�жϷ�����
 */
void adc_isr (void *p_arg)
{
    uint32_t int_flags = 0;
    
    int_flags = amhw_adc_flags_get(AMHW_ADC0);
    
    if (int_flags & AMHW_ADC_FLAGS_THCMP_INT_MASK) {
        if (int_flags & AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_0)) {
            g_tc0_flag  = TRUE;
            g_val_chan0 = amhw_adc_chan_data_get(AMHW_ADC0, AMHW_ADC0_CHAN_0); 
            amhw_adc_flags_clr(AMHW_ADC0, AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_0));
        }
        
        if (int_flags & AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_1)) {
            g_tc1_flag  = TRUE;
            g_val_chan1 = amhw_adc_chan_data_get(AMHW_ADC0, AMHW_ADC0_CHAN_1);
            amhw_adc_flags_clr(AMHW_ADC0, AMHW_ADC_FLAGS_THCMP_MASK(AMHW_ADC0_CHAN_1));
        }
        
        amhw_adc_flags_clr(AMHW_ADC0, AMHW_ADC_FLAGS_THCMP_INT_MASK);
    }
}

/**
 * \brief ����
 */
void adc_config (void)
{
    uint32_t adc_flags, seq_flags;
    
    /* ����ADCģ���������� */
    am_gpio_pin_cfg(PIO0_29, PIO0_29_ADC_IN0 | PIO0_29_INACTIVE);  
    am_gpio_pin_cfg(PIO0_30, PIO0_30_ADC_IN1 | PIO0_30_INACTIVE);

    /* ADCʱ������ */
    amhw_clock_adc_src_set(AMHW_CLOCK_ADC_SRC_MAINCLK);
    amhw_clock_adc_clkdiv_set(0x01);
    
    /* ����ADC */
    amhw_adc_startup(AMHW_ADC0);

    adc_flags = AMHW_ADC_CTRL_CLK_DIV(0)     |    /* ʱ�ӷ�ƵΪ0��1��Ƶ�� */
                AMHW_ADC_CTRL_MODE_SYNC      |    /* ʹ��ͬ��ģʽ         */
                AMHW_ADC_CTRL_RESOL_12BIT    |    /* 12λ��������         */
                AMHW_ADC_CTRL_SAMPLE_TIME(0) |    /* ����Ĭ�ϲ���ʱ��     */
                AMHW_ADC_CTRL_BYPASS_CALIB;       /* ����У��             */ 
    
    /* ADC���� */
    amhw_adc_config(AMHW_ADC0, adc_flags);

    seq_flags = AMHW_ADC_SEQ_CTRL_TRIG_SOFT    |  /* �������               */
                AMHW_ADC_SEQ_CTRL_TRIG_POL_POS |  /* �Ƽ�ʹ�������ش�����ʽ */
                AMHW_ADC_SEQ_CTRL_MODE_EOS     |  /* ͨ��ת����ɴ����ж�   */
                AMHW_ADC_SEQ_CTRL_ENABLE_CH(1) |  /* ʹ��ADCͨ��0           */
                AMHW_ADC_SEQ_CTRL_ENABLE_CH(0);   /* ʹ��ADCͨ��1           */

    /* ADC����A���� */
    amhw_adc_seq_config(AMHW_ADC0, AMHW_ADC_SEQ_A, seq_flags);
    
    /* ʹ���ж� */
    amhw_adc_int_enable(AMHW_ADC0, AMHW_ADC_INTEN_CMP_OUTSIDETH(AMHW_ADC0_CHAN_0) |
                                   AMHW_ADC_INTEN_CMP_CROSSTH(AMHW_ADC0_CHAN_1));
    
    /* Ϊͨ��ѡ����ֵ�Ƚ� */
    amdr_adc_thr0_sel(AMHW_ADC0, AMHW_ADC0_CHAN_0);
    amdr_adc_thr1_sel(AMHW_ADC0, AMHW_ADC0_CHAN_1);
     
    /* ���ñȽ���ֵ */
    amhw_adc_thr_low_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_0, THRE_LOW);
    amhw_adc_thr_high_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_0, THRE_HIGH);
    
    amhw_adc_thr_low_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_1, THRE_LOW);
    amhw_adc_thr_high_set(AMHW_ADC0, AMHW_ADC_COMP_THRE_1, THRE_HIGH);
    
    /* ʹ������A */
    amhw_adc_seq_enable(AMHW_ADC0, AMHW_ADC_SEQ_A);
}

/**
 * \brief ���������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    amdr_plfm_adc0_init(); 

    /* ����ADC�жϷ���������ʹ���ж� */
    am_int_connect(INUM_ADC0_THCMP, adc_isr, (void *)0);
    am_int_enable(INUM_ADC0_THCMP);
    
    /* ADC���� */
    adc_config();

    while (1) {
        amhw_adc_seq_start(AMHW_ADC0, AMHW_ADC_SEQ_A);
        
        if (g_tc0_flag == TRUE) {
            g_tc0_flag = FALSE;
            
            am_kprintf("The ADC channel 0 voltage: %4d mV \r\n", 
                        AMHW_ADC_DR_RESULT(g_val_chan0) * 3200 / 4095);
            
            /* �ж�ͨ��0��ֵ�ȽϽ�� */
            if (AMHW_ADC_DR_THCMPRANGE(g_val_chan0) == 0x00) {
                am_kprintf("The ADC channel 0 voltage is in range.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPRANGE(g_val_chan0) == 0x01) {
                am_kprintf("The ADC channel 0 voltage is blow range.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPRANGE(g_val_chan0) == 0x02) {
                am_kprintf("The ADC channel 0 voltage is above range.\r\n");
            }
        }
        
        if (g_tc1_flag == TRUE) {
            g_tc1_flag = FALSE;
            
            am_kprintf("The ADC channel 1 voltage: %4d mV \r\n", 
                        AMHW_ADC_DR_RESULT(g_val_chan1) * 3200 / 4095);
            
            /* �ж�ͨ��1��ֵ�ȽϽ�� */
            if (AMHW_ADC_DR_THCMPCROSS(g_val_chan1) == 0x00) {
                am_kprintf("The ADC channel 1 voltage no threshold Crossing detected.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPCROSS(g_val_chan1) == 0x02) {
                am_kprintf("The ADC channel 1 voltage downward Threshold Crossing Detected.\r\n");
            
            } else if (AMHW_ADC_DR_THCMPCROSS(g_val_chan1) == 0x03) {
                am_kprintf("The ADC channel 1 voltage upward Threshold Crossing Detected.\r\n");
            }
        }
        am_mdelay(200);
    }
}

/** [src_hw_adc_thcmp] */

/* end of file */

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
 * \brief ADC���̣�ת���������ͨ��DMA���䣬ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_0��������PC���ڵ�TXD��
 *   2. PIO0_1��������PC���ڵ�RXD��
 *   3. PIO0_29(ADCͨ��0) ����ģ�����롣
 *
 * - ʵ������
 *   1. ADCת�����100�Σ����ڴ�ӡ��100��������ѹֵ��
 *
 * \par Դ����
 * \snippet demo_hw_adc_dma.c src_hw_adc_dma 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-20  hbt, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_adc_dma
 * \copydoc demo_hw_adc_dma.c
 */

/** [src_hw_adc_dma] */
#include "ametal.h"
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

/** \brief ADCת����������� */
uint32_t adc_abuf[100];
uint32_t adc_bbuf[100];

/** \brief DMA ���������� */
__align(16) amhw_dma_xfer_desc_t g_desc[2];

/** \brief DMA������ɱ�־ */
bool_t  g_trans_adone;
bool_t  g_trans_bdone; 

/** 
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� amdr_dma_isr_connect() �������ݡ� 
 * \param[in] p_flg : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AMDR_DMA_INTA)��(#AMDR_DMA_INTB) �� (#AMDR_DMA_INTERR)��
 *
 * \return    �ޡ�
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;
    
    if (flag == AMDR_DMA_INTA) {  
        
        /* DMA������� */
        g_trans_adone = TRUE;  
        
    } else if (flag == AMDR_DMA_INTB) {
        g_trans_bdone = TRUE;  
        
    } else if (flag == AMDR_DMA_INTERR) {
        // �û��Զ���ִ�д���
    }
}

/**
 * \brief DMA���䣺ƹ�Ҵ��䡣
 */
void dma_transfer (void)
{
    uint32_t flags1, flags2;
    
    /* DMAͨ������ */
    amdr_dma_chan_setup(DMA_CHAN_0,                     /* DMAͨ����                       */
                        AMHW_DMA_CHAN_PERIPH_REQ_OFF |  /* �������败��                    */
                        AMHW_DMA_CHAN_HWTRIG_LOW     |  /* �͵�ƽ����                      */
                        AMHW_DMA_CHAN_BURST_1        |  /* ͻ������ģʽ                    */
                        AMHW_DMA_CHAN_PRIO_1);          /* ͨ�����ȼ���1��0���ȼ���ߣ�    */
    
    amdr_dma_chan_start(DMA_CHAN_0);                    /* ��ʼDMA����                     */
    
    /* DMA�������� */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                  /* ��ǰͨ����������Ч              */
             AMHW_DMA_XFER_RELOAD |                     /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                     /* �������                        */
             AMHW_DMA_XFER_CLRTRIG |                    /* ���������־                    */
             AMHW_DMA_XFER_WIDTH_32BIT |                /* �������ݿ�ȣ�32 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* Դ�����ݵ�ַ������              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTA;                     /* ʹ���ж� A                      */

    /* DMA�������� */
    flags2 = AMHW_DMA_XFER_CFG_VALID |                  /* ��ǰͨ����������Ч              */
             AMHW_DMA_XFER_RELOAD |                     /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                     /* �������                        */
             AMHW_DMA_XFER_CLRTRIG |                    /* ���������־                    */
             AMHW_DMA_XFER_WIDTH_32BIT |                /* �������ݿ�ȣ�32 bit            */
             AMHW_DMA_XFER_NO_SRCINC |                  /* Դ�����ݵ�ַ������              */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTB;                     /* ʹ���ж� B                      */

    /* ����ͨ��������A */
    amdr_dma_xfer_desc_build(&g_desc[0],                    /* A������������               */
                             (uint32_t)(&AMHW_ADC0->dat0),  /* Դ�����ݵ�ַ                */
                             (uint32_t)&adc_abuf[0],        /* A��Ŀ��˻�������ַ         */
                             4 * 100,                       /* �����ֽ���                  */
                             flags1);                       /* ��������                    */

    /* ����ͨ��������B */
    amdr_dma_xfer_desc_build(&g_desc[1],                    /* B������������               */
                             (uint32_t)(&AMHW_ADC0->dat0),  /* Դ�����ݵ�ַ                */
                             (uint32_t)&adc_bbuf[0],        /* B��Ŀ��˻�������ַ         */
                             4 * 100,                       /* �����ֽ���                  */
                             flags2);                       /* ��������                    */

    /* ����DMA�жϷ����� */
    amdr_dma_isr_connect(DMA_CHAN_0, dma_isr, (void *)0);
    
    /* �������������� */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /* ����DMA���䣬���Ͽ�ʼ���� */
    amdr_dma_chan_xfer_startup(DMA_CHAN_0, &g_desc[0]);
}

/**
 * \brief ADC���ã�ͨ��HW�㺯���ӿ�ʵ�֡�
 */
void adc_config (void)
{
    uint32_t adc_flags, seq_flags;
    
    /* ����ADCģ���������� */
    am_gpio_pin_cfg(PIO0_29, PIO0_29_ADC_IN0 | PIO0_29_INACTIVE); 

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

    seq_flags = AMHW_ADC_SEQ_CTRL_MODE_BURST   |  /* ����ͻ��ת��ģʽ      */
                AMHW_ADC_SEQ_CTRL_MODE_EOS     |  /* ����ת����ɺ󴥷�DMA */ 
                AMHW_ADC_SEQ_CTRL_ENABLE_CH(0);   /* ʹ��ADCͨ��0          */ 

    /* ADC����A���� */
    amhw_adc_seq_config(AMHW_ADC0, AMHW_ADC_SEQ_A, seq_flags);
    
    /* ʹ������A�ж� */
    amhw_adc_int_enable(AMHW_ADC0, AMHW_ADC_INTEN_SEQA_ENABLE);
    
    /* ʹ������Aת�� */
    amhw_adc_seq_enable(AMHW_ADC0, AMHW_ADC_SEQ_A);
}

/**
 * \brief ���������
 */
int main (void)
{
    int i;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amdr_plfm_adc0_init(); 
    amhw_plfm_dma_init();
    
    /* ADC���� */
    adc_config();

    /* DMA��ʼ�� */
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);

    /* DMA���� */
    dma_transfer();
    
    while (1) {
        if (g_trans_adone) {
            g_trans_adone = FALSE;
            
            for (i = 0; i < 100; i++) {
                
                /* �������������ѹ */
                am_kprintf("The buffer A conversion %2d: %4d mV \r\n", i,
                            AMHW_ADC_DR_RESULT(adc_abuf[i]) * 3200 / 4095);
            }
            am_mdelay(50);
        }
        
        if (g_trans_bdone) {
            g_trans_bdone = FALSE;
            
            for (i = 0; i < 100; i++) {
                
                /* �������������ѹ */
                am_kprintf("The buffer B conversion %2d: %4d mV \r\n", i,
                            AMHW_ADC_DR_RESULT(adc_bbuf[i]) * 3200 / 4095);
            }
            am_mdelay(50);
        }
    }
}

/** [src_hw_adc_dma] */

/* end of file */

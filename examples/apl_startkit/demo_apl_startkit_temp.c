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
 * \brief APL_StartKit NTC �¶ȴ�������ʾ����
 *
 * - ��������:
 *   1. ��APL_StartKit���ӵ�EasyARM-54000M4 demo�壻
 *   2. ������ñ����ADCͨ��4�����������ADC1����
 *   3. ��APL_StartKit����ϴ���0�ӿڣ�J3�����ӵ�PC���ϡ�
 *
 * - ʵ������:
 *   1. ͨ��APL_StartKit���ϵ��������ʾ��ǰ�����¶�ֵ��
 *   2. ���¼��Ȱ������ɿ����¶�ֵ�������ߡ�
 *
 * \par Դ����
 * \snippet demo_apl_startkit_adc.c src_apl_startkit_adc
 *
 * \internal
 * \par Modification History
 * - 1.00 15-03-19  jon, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_apl_startkit_temp
 * \copydoc demo_apl_startkit_temp.c
 */

/** [src_apl_startkit_temp] */
#include "ametal.h"  
#include "am_board.h"
#include "am_prj_config.h"

#include "ntc_temp_app.h"
#include "digitron_app.h"

am_spi_handle_t    g_spi_handle;     /**< \brief SPI��׼���������� */
am_adc_handle_t    g_adc0_handle;    /**< \brief ADC��׼���������� */
uint32_t           g_temp_val = 0;   /**< \brief NTC �������ɼ����¶�ֵ */

bool_t   g_data_show_flag;
bool_t   g_data_updata_flag;

/** 
 * \brief  ��ʱ��0�ص�����
 * \param[in] p_arg : ��ڲ���
 * \return  ��
 */
void timer0_callback (void *p_arg)
{
    g_data_updata_flag = TRUE;
}


/** 
 * \brief  ��ʱ��1�ص�����
 * \param[in] p_arg : ��ڲ���
 * \return  ��
 */
void timer1_callback (void *p_arg)
{
    g_data_show_flag = TRUE;
}


/**
 * \brief ���������
 */
int main (void)
{
    am_timer_handle_t  timer0_handle;
    am_timer_handle_t  timer1_handle;
    am_timer_info_t    timer0_info;
    am_timer_info_t    timer1_info;
    uint32_t           adc_val = 0;
    uint8_t            data_tab[4];

    /* �弶��ʼ�� */
    am_board_init();
    
    /* APL_StartKit ��� HC595_RCK IO ��ʼ�� */
    digitron_rck_init();
    
    /* ƽ̨��ʼ�� */
    amdr_plfm_adc0_init(); 
    amhw_plfm_spi0_init();
    amhw_plfm_timer0_timing_init();
    amhw_plfm_timer1_timing_init();

    /* ����ADCģ���������� */
    am_gpio_pin_cfg(PIO1_1, PIO1_1_ADC_IN4 | PIO1_1_INACTIVE);
    
    /* ��ʼ��ADC������ȡADC��׼���������� */
    g_adc0_handle = amdr_adc_init(&g_adc0_dev, &g_adc0_devinfo);

    /* SPI��ʼ������ */
    g_spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);

    /* ��ʼ����ʱ��0 ����ʱ��1Ϊ��ʱ���� */
    timer0_handle = amdr_timer_timing_init(&g_timer0_timing_dev, 
                                           &g_timer0_timing_devinfo); 
    timer1_handle = amdr_timer_timing_init(&g_timer1_timing_dev, 
                                           &g_timer1_timing_devinfo);
    
    /* SPI�жϺ������� */
    am_spi_connect(g_spi_handle);
    
    am_timer_connect(timer0_handle);
    am_timer_connect(timer1_handle);
    
    am_timer_info_get(timer0_handle, &timer0_info);
    am_timer_info_get(timer1_handle, &timer1_info);
    
    /* STD��ʱ��ֻ֧��һ��ͨ������ͨ����һֱΪ0 */
    am_timer_callback_set(timer0_handle, 0, timer0_callback, NULL);
    am_timer_callback_set(timer1_handle, 0, timer1_callback, NULL);
    am_timer_enable(timer0_handle, 0, timer0_info.clk_frequency );
    am_timer_enable(timer1_handle, 0, timer1_info.clk_frequency / 1000);
    while (1) {
    

        /* �����ɨ�� Ƶ�� 2KHz */
        if(g_data_show_flag) {
            
            g_data_show_flag = FALSE;
            data_tab[0] = (g_temp_val/1000)+0x30;
            data_tab[1] = (g_temp_val%1000/100)+0x30;
            data_tab[2] = (g_temp_val%1000%100/10)+0x30;
            data_tab[3] = (g_temp_val%10)+0x30;

            if(data_tab[0] == '0') {
                data_tab[0] = ' ';
            }

            digitron_show_char(g_spi_handle, 0 , data_tab[0]);
            digitron_show_char(g_spi_handle, 1 , data_tab[1]);
            digitron_show_char(g_spi_handle, 2 , data_tab[2]);
            digitron_show_char(g_spi_handle, 2 , '.');
            digitron_show_char(g_spi_handle, 3 , data_tab[3]);
        } 
        
        /* �¶����ݸ��� 1�� */
        if(g_data_updata_flag) {
            g_data_updata_flag = FALSE;
            adc_val  = adc_vol_value_get(g_adc0_handle);
            g_temp_val = vol_to_temp_value(adc_val);
        }
    }
}

/** [src_apl_startkit_temp] */
 
/* end of file */

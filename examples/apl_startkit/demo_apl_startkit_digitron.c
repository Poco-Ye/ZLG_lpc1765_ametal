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
 * \brief APL_StartKit �������ʾ����
 *
 * - ��������:
 *   1. ��APL_StartKit���ӵ�EasyARM-54000M4 demo�壻
 *   2. ������ñ����SPI�ӿ�(MISO��MOSI��SCK��CS��RCK)��ʹHC595���ӵ�SPI0��
 *
 * - ʵ������:
 *   1. ���������ʾ0000-9999,1�����ݸ���һ�Ρ�
 *
 * \par Դ����
 * \snippet demo_apl_startkit_digitron.c src_apl_startkit_digitron
 *
 * \internal
 * \par History
 * - 1.00 15-03-18  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_apl_startkit_digitron
 * \copydoc demo_apl_startkit_digitron.c
 */
 
/** [src_apl_startkit_digitron] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"
#include "digitron_app.h"

bool_t g_data_show_flag;
bool_t g_data_updata_flag;


/** 
 * \brief  ��ʱ��0�ص�����
 * \param[in] p_arg : ��ڲ���
 * \return  ��
 */
void timer0_callback (void *p_arg)
{
    static int count = 0;
    if(count++ > 1000) {
        count = 0;
        g_data_updata_flag = TRUE;
    }
    g_data_show_flag = TRUE;
    am_led_toggle(LED0);
}


/**
 * \brief ������
 */
int main (void)
{
    am_spi_handle_t     spi_handle;
    am_timer_handle_t   timer0_handle;
    am_timer_info_t     timer0_info;
    uint8_t data_tab[4];
    uint32_t tmp_value = 0;
    /* �弶��ʼ�� */
    am_board_init();
    
    /* APL_StartKit ��� IO ��ʼ�� */
    digitron_rck_init();
    
    /*  ƽ̨��س�ʼ�� */
    amhw_plfm_spi0_init();
    amhw_plfm_timer0_timing_init();

    /* SPI��ʼ������ */
    spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);
    
    /* ��ʼ����ʱ��0Ϊ��ʱ���� */
    timer0_handle = amdr_timer_timing_init(&g_timer0_timing_dev, 
                                           &g_timer0_timing_devinfo); 
    
    /* SPI�жϺ������� */
    am_spi_connect(spi_handle);
    
    am_timer_connect(timer0_handle);
    
    am_timer_info_get(timer0_handle, &timer0_info);
    
    /* ��׼��ʱ��ֻ֧��һ��ͨ������ͨ����һֱΪ0 */
    am_timer_callback_set(timer0_handle, 0, timer0_callback, NULL);
    am_timer_enable(timer0_handle, 0, timer0_info.clk_frequency / 1000);

    while (1) {

        if(g_data_updata_flag) {
            g_data_updata_flag = FALSE;
            if ((tmp_value++) > 10000) {
                tmp_value = 0;
            }
                
            
        }
        if(g_data_show_flag) {
            g_data_show_flag = FALSE;
            data_tab[0] = (tmp_value/1000)+0x30;
            data_tab[1] = (tmp_value%1000/100)+0x30;
            data_tab[2] = (tmp_value%1000%100/10)+0x30;
            data_tab[3] = (tmp_value%10)+0x30;
            
            /** 
             * �������ʾ��ͨ�����ַ�ʽʵ�֣������ַ���ʾ���ַ�����ʾ���û�����ѡ��һ�ַ�ʽ
             * ��������ʹ���ַ�����ʽ��
             */
             
            /* �ַ�����ʾ��ʽ����ʾ���� */
            digitron_show_string(spi_handle, (const char *)&data_tab);
            
//            /* �����ַ���ʾ��ʽ����ʾ���� */
//            digitron_show_char(spi_handle, 0 , data_tab[0]);
//            digitron_show_char(spi_handle, 1 , data_tab[1]);
//            digitron_show_char(spi_handle, 2 , data_tab[2]);
//            digitron_show_char(spi_handle, 3 , data_tab[3]);
        }
    }
}

/** [src_apl_startkit_digitron] */

/* end of file */


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
 * \brief APL_StartKit NTC 温度传感器演示例程
 *
 * - 操作步骤:
 *   1. 将APL_StartKit配板接到EasyARM-54000M4 demo板；
 *   2. 用跳线帽连接ADC通道4（配板网络标号ADC1）；
 *   3. 将APL_StartKit配板上串口0接口（J3）连接到PC机上。
 *
 * - 实验现象:
 *   1. 通过APL_StartKit板上的数码管显示当前环境温度值；
 *   2. 按下加热按键，可看到温度值不断升高。
 *
 * \par 源代码
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

am_spi_handle_t    g_spi_handle;     /**< \brief SPI标准服务操作句柄 */
am_adc_handle_t    g_adc0_handle;    /**< \brief ADC标准服务操作句柄 */
uint32_t           g_temp_val = 0;   /**< \brief NTC 传感器采集到温度值 */

bool_t   g_data_show_flag;
bool_t   g_data_updata_flag;

/** 
 * \brief  定时器0回调函数
 * \param[in] p_arg : 入口参数
 * \return  无
 */
void timer0_callback (void *p_arg)
{
    g_data_updata_flag = TRUE;
}


/** 
 * \brief  定时器1回调函数
 * \param[in] p_arg : 入口参数
 * \return  无
 */
void timer1_callback (void *p_arg)
{
    g_data_show_flag = TRUE;
}


/**
 * \brief 主函数入口
 */
int main (void)
{
    am_timer_handle_t  timer0_handle;
    am_timer_handle_t  timer1_handle;
    am_timer_info_t    timer0_info;
    am_timer_info_t    timer1_info;
    uint32_t           adc_val = 0;
    uint8_t            data_tab[4];

    /* 板级初始化 */
    am_board_init();
    
    /* APL_StartKit 配板 HC595_RCK IO 初始化 */
    digitron_rck_init();
    
    /* 平台初始化 */
    amdr_plfm_adc0_init(); 
    amhw_plfm_spi0_init();
    amhw_plfm_timer0_timing_init();
    amhw_plfm_timer1_timing_init();

    /* 配置ADC模拟输入引脚 */
    am_gpio_pin_cfg(PIO1_1, PIO1_1_ADC_IN4 | PIO1_1_INACTIVE);
    
    /* 初始化ADC，并获取ADC标准服务操作句柄 */
    g_adc0_handle = amdr_adc_init(&g_adc0_dev, &g_adc0_devinfo);

    /* SPI初始化配置 */
    g_spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);

    /* 初始化定时器0 、定时器1为定时功能 */
    timer0_handle = amdr_timer_timing_init(&g_timer0_timing_dev, 
                                           &g_timer0_timing_devinfo); 
    timer1_handle = amdr_timer_timing_init(&g_timer1_timing_dev, 
                                           &g_timer1_timing_devinfo);
    
    /* SPI中断函数连接 */
    am_spi_connect(g_spi_handle);
    
    am_timer_connect(timer0_handle);
    am_timer_connect(timer1_handle);
    
    am_timer_info_get(timer0_handle, &timer0_info);
    am_timer_info_get(timer1_handle, &timer1_info);
    
    /* STD定时器只支持一个通道，故通道号一直为0 */
    am_timer_callback_set(timer0_handle, 0, timer0_callback, NULL);
    am_timer_callback_set(timer1_handle, 0, timer1_callback, NULL);
    am_timer_enable(timer0_handle, 0, timer0_info.clk_frequency );
    am_timer_enable(timer1_handle, 0, timer1_info.clk_frequency / 1000);
    while (1) {
    

        /* 数码管扫描 频率 2KHz */
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
        
        /* 温度数据更新 1秒 */
        if(g_data_updata_flag) {
            g_data_updata_flag = FALSE;
            adc_val  = adc_vol_value_get(g_adc0_handle);
            g_temp_val = vol_to_temp_value(adc_val);
        }
    }
}

/** [src_apl_startkit_temp] */
 
/* end of file */

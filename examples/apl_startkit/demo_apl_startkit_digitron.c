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
 * \brief APL_StartKit 数码管演示例程
 *
 * - 操作步骤:
 *   1. 将APL_StartKit配板接到EasyARM-54000M4 demo板；
 *   2. 用跳线帽连接SPI接口(MISO、MOSI、SCK、CS、RCK)，使HC595连接到SPI0。
 *
 * - 实验现象:
 *   1. 数码管上显示0000-9999,1秒数据更新一次。
 *
 * \par 源代码
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
 * \brief  定时器0回调函数
 * \param[in] p_arg : 入口参数
 * \return  无
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
 * \brief 主函数
 */
int main (void)
{
    am_spi_handle_t     spi_handle;
    am_timer_handle_t   timer0_handle;
    am_timer_info_t     timer0_info;
    uint8_t data_tab[4];
    uint32_t tmp_value = 0;
    /* 板级初始化 */
    am_board_init();
    
    /* APL_StartKit 配板 IO 初始化 */
    digitron_rck_init();
    
    /*  平台相关初始化 */
    amhw_plfm_spi0_init();
    amhw_plfm_timer0_timing_init();

    /* SPI初始化配置 */
    spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);
    
    /* 初始化定时器0为定时功能 */
    timer0_handle = amdr_timer_timing_init(&g_timer0_timing_dev, 
                                           &g_timer0_timing_devinfo); 
    
    /* SPI中断函数连接 */
    am_spi_connect(spi_handle);
    
    am_timer_connect(timer0_handle);
    
    am_timer_info_get(timer0_handle, &timer0_info);
    
    /* 标准定时器只支持一个通道，故通道号一直为0 */
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
             * 数码管显示可通过两种方式实现，单个字符显示，字符串显示，用户可以选择一种方式
             * 本例程中使用字符串方式。
             */
             
            /* 字符串显示方式，显示数据 */
            digitron_show_string(spi_handle, (const char *)&data_tab);
            
//            /* 单个字符显示方式，显示数据 */
//            digitron_show_char(spi_handle, 0 , data_tab[0]);
//            digitron_show_char(spi_handle, 1 , data_tab[1]);
//            digitron_show_char(spi_handle, 2 , data_tab[2]);
//            digitron_show_char(spi_handle, 3 , data_tab[3]);
        }
    }
}

/** [src_apl_startkit_digitron] */

/* end of file */


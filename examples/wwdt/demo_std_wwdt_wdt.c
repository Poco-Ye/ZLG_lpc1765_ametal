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
 * \brief WWDT演示例程，通过标准接口实现
 * 
 * - 实验现象:
 *   1. 若WWDT使芯片复位，串口提示"The chip Reset by WWDT\r\n"
 *   2. 修改宏定义WWDT_FEED_TIME_MS的值，超过1500ms,芯片复位
 *
 * \par 源代码
 * \snippet demo_std_wwdt_wdt.c src_std_wwdt_wdt 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-09  fft, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_wwdt_wdt
 * \copydoc demo_std_wwdt_wdt.c
 */
 
/** [src_std_wwdt_wdt] */ 
#include "ametal.h"
#include "am_board.h"


#define WWDT_TIMEOUT_MS       1500

/**
 * \brief 看门狗喂狗时间定义
 *        若喂狗时间超过 WWDT_TIMEOUT_MS的值, 看门狗将复位芯片
 */
#define WWDT_FEED_TIME_MS     1000

/**
 * \brief 主函数
 */
int main (void)
{
    am_wdt_handle_t handle = NULL;
    am_wdt_info_t   info;

    /* 板级初始化 */
    am_board_init();
    
    if ((amhw_syscon_rst_stat_get() & AMHW_SYSCON_RSTSTAT_WDT) != 0) {
        
        amhw_syscon_rst_stat_clr(AMHW_SYSCON_RSTSTAT_WDT);
        AM_DBG_INFO("The chip Reset by WWDT\r\n");
        am_led_on(LED0);
        
    } else {
        
        AM_DBG_INFO("The chip Reset by External Reset Pin \r\n");
    }

    /* WWDT平台初始化 */
    amhw_plfm_wwdt_init();
    
    /* 初始化WWDT */
    handle = amdr_wwdt_init(&g_wwdt_dev, &g_wwdt_devinfo);
    
    am_wdt_info_get(handle,&info);

    AM_DBG_INFO("The WDT support min time is %d ms \r\n",info.min_timeout_ms);
    AM_DBG_INFO("The WDT support max time is %d ms \r\n",info.max_timeout_ms);
    
    am_wdt_enable(handle,WWDT_TIMEOUT_MS);
    
    while (1) {
        /*
         * WWDT 复位时间是 1500ms(configured in g_wwdt_devinfo)
         * 若喂狗时间超过 1500ms,芯片将会复位
         */
        am_wdt_feed(handle);
        am_mdelay(WWDT_FEED_TIME_MS); 
        am_led_toggle(LED0);
    }
}

/** [src_std_wwdt_wdt] */ 

/* end of file */

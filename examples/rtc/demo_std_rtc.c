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
 * \brief RTC演示例程，通过标准接口实现
 *
 * - 实验现象:
 *  1. 串口打印当前时间信息, 例如： "Thu Jan 22 14:18:58 2015"
 *
 * \par 源代码
 * \snippet demo_std_rtc.c src_std_rtc 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_std_rtc
 * \copydoc demo_std_rtc.c
 */

/** [src_std_rtc] */
#include "ametal.h"
#include "am_board.h"
#include <time.h>

/* 当前的时间参数设置，例如 : 2015/1/22 14:17:23 */
struct am_tm now_time = {
    23,           /*  23秒 */
    17,           /*  17分 */
    14,           /*  14时 */
    22,           /*  22日 */
    1 - 1,        /*   1月 */
    2015 - 1900,  /*2015年 */
};

/**
 * \brief 主函数
 */
int main(void)
{
    uint32_t          time_sec = 0;
    am_rtc_handle_t   handle   = NULL;
    char time_str[30];

    /* 班级初始化  */
    am_board_init();
    
    AM_DBG_INFO("The demo RTC for standard service\r\n");
    
    /* RTC 平台初始化*/
    amhw_plfm_rtc_init();
    
    handle = amdr_rtc_init(&g_rtc_dev, &g_rtc_devinfo);

    /* 设定当前时间 */
    am_rtc_time_set(handle, &now_time);
 
    /* Sleep and do all the work in the RTC interrupt handler */
    while (1) {

        /* 通过RTC，获取当前时间信息，单位：秒 */
        am_rtc_time_get(handle, &now_time);
 
        /* 将计算出的时间信息转换成字符串格式 */
        asctime_r((struct tm*)&now_time, time_str);
        
        AM_DBG_INFO("%s", time_str);
        am_mdelay(1000);
    }
}

/** [src_std_rtc] */

/* end of file */

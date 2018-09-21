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
 * \brief 重复中断定时器(RIT)例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. LED以10Hz的频率闪烁。
 *
 * \par 源代码
 * \snippet demo_std_rit_timer.c src_std_rit_timer
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-17  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_std_rit_timer
 * \copydoc demo_std_rit_timer.c
 */

/** [src_std_rit_timer] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief 重复中断定时器中断服务函数
 * \param[in]  p_arg : 用户自定义参数，通过 am_int_connect() 函数传递。
 * \return 无
 */
void rit_timing_callback (void *p_arg)
{
    am_led_toggle(LED0);
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    am_timer_handle_t rit_handle;
    am_timer_info_t   rit_info;

    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_rit_init();

    AM_DBG_INFO("The RIT demo for standard timing service\r\n");

    /* 初始化RIT为定时功能 */
    rit_handle = amdr_rit_init(&g_rit_dev, &g_rit_devinfo);

    am_timer_connect(rit_handle);

    am_timer_info_get(rit_handle, &rit_info);

    AM_DBG_INFO("The timer size is : %d-bit \r\n",
                    AM_TIMER_SIZE_GET(rit_info.features));

    AM_DBG_INFO("The timer clk_frequency: %d Hz\r\n",rit_info.clk_frequency);
    am_timer_callback_set(rit_handle, 0, rit_timing_callback, NULL);

    while (1) {

        /*
         * 重复中断定时器是48-bit，应通过调用 am_timer_enable64() 函数使能定时器。
         */
        am_timer_enable64(rit_handle, 0, rit_info.clk_frequency / 10);
        am_mdelay(3000);
        am_timer_disable(rit_handle, 0);
        am_mdelay(3000);
    }
}

/** [src_std_rit_timer] */

/* end of file */

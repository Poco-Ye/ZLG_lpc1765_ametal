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
 * \brief 多频率定时器(MRT)例程,通过HW层的接口实现
 *
 * - 实验现象：
 *   1. LED0以10Hz的频率闪烁;
 *   2. PIO0_5引脚的输出电平状态以8KHz的频率变换，产生4KHz的波形。
 *
 * \par 源代码
 * \snippet demo_hw_mrt.c src_hw_mrt
 *
 * \internal
 * \par History
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hw_mrt
 * \copydoc demo_hw_mrt.c
 */

/** [src_hw_mrt] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief 多频率定时器中断服务函数。
 * \param[in] p_arg : 用户自定义的参数，通过 am_int_connect()传递。
 * \return 无
  */
void mrt_irq_handler (void *p_arg)
{
    if (amhw_mrt_int_pending_get(AMHW_MRT, AMHW_MRT_CH(0)) == TRUE) {

        /* 翻转PIO0_5引脚状态 */
        am_gpio_toggle(PIO0_5);

        /* 清中断等待标志 */
        amhw_mrt_int_pending_clr(AMHW_MRT, AMHW_MRT_CH(0));
    }

    if (amhw_mrt_int_pending_get(AMHW_MRT, AMHW_MRT_CH(1)) == TRUE) {

        am_led_toggle(LED0);

        /* 如果需要再次产生中断，one-shot模式应该再次加载中断值 */
        amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(1), g_system_clkfreq / 10, TRUE);

        /* 清中断等待标志 */
        amhw_mrt_int_pending_clr(AMHW_MRT, AMHW_MRT_CH(1));
    }
}

/**
 * \brief 主函数入口。
 */
int main (void)
{
    uint32_t ticks;

    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_mrt_init();

    am_gpio_pin_cfg(PIO0_5, PIO0_5_GPIO | PIO0_5_OUTPUT);

    /* 禁能所有通道的中断 */
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(0));
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(1));
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(2));
    amhw_mrt_int_disable(AMHW_MRT, AMHW_MRT_CH(3));

    am_int_connect(INUM_MRT, mrt_irq_handler, (void *)0);
    am_int_enable(INUM_MRT);

    /*
     * 通道0为AMHW_MRT_MODE_REPEAT模式，中断频率为8KHz，
     * 最大中断值为0xFFFFFF，
     * 在100MHz，最大时间为0xFFFFFF / 100 us = 167772 us，最小频率为：6 Hz。
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(0), AMHW_MRT_MODE_REPEAT);
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(0), g_system_clkfreq / 8000, TRUE);
    amhw_mrt_int_enable(AMHW_MRT, AMHW_MRT_CH(0));

    /*
     * 通道1为AMHW_MRT_MODE_ONESHOT模式，中断频率10Hz。
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(1), AMHW_MRT_MODE_ONESHOT);
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(1), g_system_clkfreq / 10, TRUE);
    amhw_mrt_int_enable(AMHW_MRT, AMHW_MRT_CH(1));


    /*
     * 通道2为AMHW_MRT_MODE_ONESHOT模式，延时100us。
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(2), AMHW_MRT_MODE_ONESHOT);

    ticks = 100 * (g_system_clkfreq / 1000000);

    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(2), ticks, TRUE);

    /* 等待 */
    while((amhw_mrt_stat_get(AMHW_MRT, AMHW_MRT_CH(2)) & AMHW_MRT_STAT_INTFLAG) == 0);

    /* 清中断标志 */
    amhw_mrt_int_flag_clr(AMHW_MRT, AMHW_MRT_CH(2));

    /*
     * 通道3为AMHW_MRT_MODE_ONESHOT_STALL模式延时100ns。
     * one-stall模式适用于非常短暂的延时。当总线写操作停止时，多频率定时器请求
     * 延时，延时完成后在进行写操作。不需要中断或查询状态标志。
     */
    amhw_mrt_mode_set(AMHW_MRT, AMHW_MRT_CH(3), AMHW_MRT_MODE_ONESHOT_STALL);

    /* 延时100个系统时钟，当延时完成，写操作也完成。 */
    amhw_mrt_intval_set(AMHW_MRT, AMHW_MRT_CH(3), 100, TRUE);

    while (1) {
        AM_DBG_INFO("idle channel :%d \r\n", amhw_mrt_idle_channel_get(AMHW_MRT));
        am_mdelay(1000);
    }
}

/** [src_hw_mrt] */

/* end of file */

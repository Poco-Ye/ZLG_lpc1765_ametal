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
 * \brief  内存到内存的DMA传输例程，通过驱动层的接口实现
 *
 * - 实验现象：
 *   1. 如果DMA传输成功，LED一直亮；
 *   2. 如果DMA传输失败，LED闪烁。
 *
 * \par 源代码
 * \snippet demo_dma_m2m.c src_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.10 14-12-09  hbt, add.
 * - 1.00 14-12-04  zen, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dma_m2m
 * \copydoc demo_dma_m2m.c
 */

/** [src_dma_m2m] */
#include "ametal.h"
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

uint8_t g_buf_src[512];          /**< \brief 源端数据缓冲区   */
uint8_t g_buf_dst[512];          /**< \brief 目标端数据缓冲区 */

bool_t  g_trans_done;            /**< \brief 传输完成标志     */

/**
 * \brief 非乒乓传输时，描述符的地址不要求16字节对齐。
 */
amhw_dma_xfer_desc_t g_desc;


/**
 * \brief DMA中断服务程序。
 *
 * \param[in] p_arg : 用户自定义参数，通过 amdr_dma_isr_connect() 函数传递。
 * \param[in] p_flg : DMA中断标志，由底层驱动传入，该参数的可能取值：
 *                    (#AMDR_DMA_INTA)、(#AMDR_DMA_INTB) 或 (#AMDR_DMA_INTERR)。
 *
 * \return    无。
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;

    if (flag == AMDR_DMA_INTA) {

        /* DMA传输完成 */
        g_trans_done = TRUE;

    } else if (flag == AMDR_DMA_INTERR) {
        // 用户自定义执行代码
    }
}

/**
 * \brief DMA传输：内存到内存。
 */
void dma_m2m_test (void)
{
    int      i;
    uint32_t flags;

    /* DMA通道配置 */
    amdr_dma_chan_setup(DMA_CHAN_0,                     /* DMA通道号                    */
                        AMHW_DMA_CHAN_PERIPH_REQ_OFF |  /* 禁能外设触发                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF     |  /* 禁止硬件触发                 */
                        AMHW_DMA_CHAN_SINGLE_TRANS   |  /* 单次传输模式                 */
                        AMHW_DMA_CHAN_PRIO_5);          /* 通道优先级：5（0优先级最高） */

    for (i = 0; i < 512; i++) {
        g_buf_src[i] = i;
        g_buf_dst[i] = 0;
    }

    /* 开始DMA传输 */
    amdr_dma_chan_start(DMA_CHAN_0);

    /* 连接DMA中断服务函数 */
    amdr_dma_isr_connect(DMA_CHAN_0, dma_isr, (void *)0);

    /* DMA传输配置 */
    flags = AMHW_DMA_XFER_CFG_VALID       |           /* 当前通道描述符有效              */
            AMHW_DMA_XFER_NO_RELOAD       |           /* 禁止重载通道描述符              */
            AMHW_DMA_XFER_SWTRIG          |           /* 软件触发                        */
            AMHW_DMA_XFER_NO_CLRTRIG      |           /* 不清除触发标志                  */
            AMHW_DMA_XFER_WIDTH_8BIT      |           /* 传输数据宽度：8 bit             */
            AMHW_DMA_XFER_SRCINC_1X_WIDTH |           /* 源端数据地址按1个数据宽度递增   */
            AMHW_DMA_XFER_DSTINC_1X_WIDTH |           /* 目标端数据地址按1个数据宽度递增 */
            AMHW_DMA_XFER_SETINTA;                    /* 使能中断 A                      */

    /* 建立通道描述符 */
    amdr_dma_xfer_desc_build(&g_desc,                 /* 通道描述符       */
                            (uint32_t)g_buf_src,      /* 源端数据缓冲区   */
                            (uint32_t)g_buf_dst,      /* 目标端数据缓冲区 */
                             512,                     /* 传输字节数       */
                             flags);                  /* 传输配置         */

    /* 启动DMA传输，马上开始传输 */
    amdr_dma_chan_xfer_startup(DMA_CHAN_0, &g_desc);

    am_mdelay(1);
    while(g_trans_done == FALSE);                   /* 等待传输完成  */

    amdr_dma_chan_stop(DMA_CHAN_0);                 /* 停止通道传输  */

    for (i = 0; i < 512; i++) {
        if (g_buf_src[i] != g_buf_dst[i]) {
            while (1) {                             /* 传输失败      */
                am_led_on(LED0);
                am_mdelay(200);
                am_led_off(LED0);
                am_mdelay(200);
            }
        }
    }

    am_led_on(LED0);
}


/**
 * \brief 主函数入口
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_dma_init();

    /* DMA初始化 */
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);

    am_led_off(LED0);

    dma_m2m_test();

    while (1) {
        ;
    }
}

/** [src_dma_m2m] */

/* end of file */

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
 * \brief  DMA乒乓传输例程，通过驱动层的接口实现
 *
 * - 实验现象：
 *   1. 如果DMA传输成功，LED一直亮；
 *   2. 如果DMA传输失败，LED闪烁。
 *
 * \par 源代码
 * \snippet demo_dma_ping_pong.c src_dma_ping_pong
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dma_ping_pong
 * \copydoc demo_dma_ping_pong.c
 */

/** [src_dma_ping_pong] */
#include "ametal.h"
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"


/** \brief 重载描述符，使用乒乓传输时，描述符必须是16字节对齐 */
__align(16) amhw_dma_xfer_desc_t g_desc[2];

uint8_t g_buf_src[16];           /**< \brief 源端数据缓冲区    */
uint8_t g_buf_dsta[16];          /**< \brief 目标端A数据缓冲区 */
uint8_t g_buf_dstb[16];          /**< \brief 目标端B数据缓冲区 */

bool_t  g_trans_a_done;          /**< \brief 传输完成标志      */  
bool_t  g_trans_b_done;          /**< \brief 传输完成标志      */
bool_t  g_trans_err;             /**< \brief 传输错误标志      */


/**
 * \brief DMA中断服务程序。
 *
 * \param[in] p_arg : 用户自定义参数，通过 amdr_dma_isr_connect() 函数传递。
 * \param[in] p_flg : DMA中断标志，由底层驱动传入，该参数的可能取值：
 *                    (#AMDR_DMA_INTA)、(#AMDR_DMA_INTB) 或 (#AMDR_DMA_INTERR)。
 *
 * \return    无。               
 *
 * \note 中断服务函数中的代码尽量少，避免频繁进中断，
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;

    g_trans_err = FALSE;

    if (flag == AMDR_DMA_INTA) {
        g_trans_a_done = TRUE;
    } else if (flag == AMDR_DMA_INTB) {
        g_trans_b_done = TRUE;
    } else if (flag == AMDR_DMA_INTERR) {
        g_trans_err = TRUE;
    }
}

/**
 * \brief DMA传输：乒乓模式。
 */
void dma_ping_pong_test (void)
{
    int      i;
    uint32_t flags1, flags2;

    /* DMA通道配置 */
    amdr_dma_chan_setup(DMA_CHAN_0,                     /* DMA通道号                    */
                        AMHW_DMA_CHAN_PERIPH_REQ_OFF |  /* 禁能外设触发                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF |      /* 禁止硬件触发                 */
                        AMHW_DMA_CHAN_PRIO_6);          /* 通道优先级：6（0优先级最高） */

    /* 开始DMA传输 */
    amdr_dma_chan_start(DMA_CHAN_0);

    for (i = 0; i < 16; i++) {
        g_buf_src[i] = i;
        g_buf_dsta[i] = 0;
        g_buf_dstb[i] = 0;
    }

    /* DMA传输配置 */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                  /* 当前通道描述符有效              */
             AMHW_DMA_XFER_RELOAD |                     /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                     /* 软件触发                        */
             AMHW_DMA_XFER_NO_CLRTRIG |                 /* 不清除触发标志                  */
             AMHW_DMA_XFER_WIDTH_8BIT |                 /* 传输数据宽度：8 bit             */
             AMHW_DMA_XFER_SRCINC_1X_WIDTH |            /* 源端数据地址按1个数据宽度递增   */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTA;                     /* 使能中断 A                      */

    /* DMA传输配置 */
    flags2 = AMHW_DMA_XFER_CFG_VALID |                  /* 当前通道描述符有效              */
             AMHW_DMA_XFER_RELOAD |                     /* 传输完成重载通道描述符          */
             AMHW_DMA_XFER_SWTRIG |                     /* 软件触发                        */
             AMHW_DMA_XFER_CLRTRIG |                    /* 除触发标志                      */
             AMHW_DMA_XFER_WIDTH_8BIT |                 /* 传输数据宽度：8 bit             */
             AMHW_DMA_XFER_SRCINC_1X_WIDTH |            /* 源端数据地址按1个数据宽度递增   */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* 目标端数据地址按1个数据宽度递增 */
             AMHW_DMA_XFER_SETINTB;                     /* 使能中断 B                      */

    /* 建立通道描述符A */
    amdr_dma_xfer_desc_build(&g_desc[0],                /* A的重载描述符       */
                             (uint32_t)g_buf_src,       /* 源端数据缓冲区      */
                             (uint32_t)g_buf_dsta,      /* A的目标端缓冲区地址 */
                             16,                        /* 传输字节数          */
                             flags1);                   /* 传输配置            */

    /* 建立通道描述符B */
    amdr_dma_xfer_desc_build(&g_desc[1],                /* B的重载描述符       */
                             (uint32_t)g_buf_src,       /* 源端数据缓冲区      */
                             (uint32_t)g_buf_dstb,      /* B的目标端缓冲区地址 */
                             16,                        /* 传输字节数          */
                             flags2);                   /* 传输配置            */

    /* 连接DMA中断服务函数 */
    amdr_dma_isr_connect(DMA_CHAN_0, dma_isr, (void *)0);

    /* 链接重载描述符 */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /* 启动DMA传输，马上开始传输 */
    amdr_dma_chan_xfer_startup(DMA_CHAN_0, &g_desc[0]);

    am_mdelay(1);
    while ((g_trans_a_done == FALSE) || (g_trans_b_done == FALSE)); /* 等待传输完成  */

    amdr_dma_chan_stop(DMA_CHAN_0);                                 /* 停止通道传输  */

    /* 核实传输数据 */
    for (i = 0; i < 16; i++) {
        if (g_buf_src[i] != g_buf_dsta[i]) {
            g_trans_err = TRUE;
            break;
        }
    }
    for (i = 0; i < 16; i++) {
        if (g_buf_src[i] != g_buf_dstb[i]) {
            g_trans_err = TRUE;
            break;
        }
    }

    if (g_trans_err == TRUE) {
        while (1) {
            am_led_on(LED0);
            am_mdelay(200);
            am_led_off(LED0);
            am_mdelay(200);
        }
    } else {
        am_led_on(LED0);
    }
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

    dma_ping_pong_test();

    while (1) {
        ;
    }
}

/** [src_dma_ping_pong] */

/* end of file */

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
 * \brief 双核（M4部分）互斥信号量演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. 串口输出 "The Cortex-M4 operation\r\n"。 
 * 
 * \par 源代码
 * \snippet demo_dualcore_mutex_m4.c src_dualcore_mutex_m4 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mutex_m4
 * \copydoc demo_dualcore_mutex_m4.c
 */

/** [src_dualcore_mutex_m4] */
#include "ametal.h"
#include "am_board.h"
#include "..\shared\lpc5410x_config_memory.h"

/** 
 * \brief Mailbox 平台初始化
 */
void amhw_plfm_mbox_init (void)
{
    /* 使能并复位消息邮箱时钟 */
    amhw_clock_periph_enable(AMHW_CLOCK_MAILBOX);
    amhw_syscon_periph_reset(AMHW_RESET_MAILBOX);
    
    /* 初始化共享区域的互斥访问，置位 */
    amhw_mbox_mutex_set(AMHW_MAILBOX);
}

/**
 * \brief Application Main entry point
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();
    
    /* 平台初始化 */
    amhw_plfm_mbox_init();

    /* 启动M0+内核 */
    amhw_cpu_boot_m0p(LPC5410X_CFG_MEM_FLASH_CM0_START);
    
    while (1) {
        
        /* 
         * 由于串口外设与 cortex-M0+共享的，
         * 为了避免两个内核同时访问串口， 加入共享互斥访问处理。
         */
        amhw_mbox_mutex_take(AMHW_MAILBOX);
        AM_DBG_INFO("The Cortex-M4 operation\r\n");
        amhw_mbox_mutex_give(AMHW_MAILBOX);
        
        am_mdelay(500);
    }
}

/** [src_dualcore_mutex_m4] */

/* end of file */

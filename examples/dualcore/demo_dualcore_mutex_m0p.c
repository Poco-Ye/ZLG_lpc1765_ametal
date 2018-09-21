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
 * \brief 双核（M0+部分）互斥信号量演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. 串口输出 "The Cortex-M0+ operation\r\n" 。
 * 
 * \par 源代码
 * \snippet demo_dualcore_mutex_m0p.c src_dualcore_mutex_m0p 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mutex_m0p
 * \copydoc demo_dualcore_mutex_m0p.c
 */

/** [src_dualcore_mutex_m0p] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief 主函数
 */
int main (void)
{
    /* The board initialization */
    am_board_init();

    while (1) {
        
        /* 
         * 由于串口外设与 cortex-M4共享的，
         * 为了避免两个内核同时访问串口， 加入共享互斥访问处理。
         */
        amhw_mbox_mutex_take(AMHW_MAILBOX);
        AM_DBG_INFO("The Cortex-M0+ operation\r\n");
        amhw_mbox_mutex_give(AMHW_MAILBOX);
        
        am_mdelay(500);
        
    }
}

/** [src_dualcore_mutex_m0p] */

/* end of file */

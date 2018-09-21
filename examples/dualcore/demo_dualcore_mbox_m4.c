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
 * \brief 双核（M4部分）MailBox演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. 共享变量递增1，并且以500ms时间间隔发送到M0+内核；
 *   2. 当接收到M0+内核的响应，串口输出字符串;
 *      "The value to send M0+ be received" 作为响应。
 * 
 * \par 源代码
 * \snippet demo_dualcore_mbox_m4.c src_dualcore_mbox_m4 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  jon, add mail box for CPUs communicate.
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mbox_m4
 * \copydoc demo_dualcore_mbox_m4.c
 */
 

/** [src_dualcore_mbox_m4] */
#include "ametal.h"
#include "am_board.h"
#include "..\shared\lpc5410x_config_memory.h"



/** 
 * \brief 消息邮箱中断处理函数
 * \param[in] p_arg : 中断入口参数
 * \return  无
 */
void mbox_irq_handler (void *p_arg)
{
    amhw_mailbox_t *p_hw_mbox = (amhw_mailbox_t *)p_arg;
    
    AM_DBG_INFO("The value to send M0+ be received\r\n");
    
    /* 清除M4 内核消息邮箱的所有数据位 */
    amhw_mbox_val_bits_clr(p_hw_mbox, AMHW_MBOX_M4_ID, 0xFFFFFFFF);
}

/** 
 * \brief 消息邮箱平台初始化
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
 * \brief  主函数
 */
int main (void)
{
    uint32_t shared_data = 0;
    
    /* 板级初始化 */
    am_board_init();
    
    /* 平台初始化 */
    amhw_plfm_mbox_init();

    /* 连接并使能消息邮箱中断 */
    am_int_connect(INUM_MAILBOX, mbox_irq_handler, (void *)AMHW_MAILBOX);
    am_int_enable(INUM_MAILBOX);
    
    /* 启动M0+内核 */
    amhw_cpu_boot_m0p(LPC5410X_CFG_MEM_FLASH_CM0_START);
    
    while (1) {

        /* 
         * 由于发送到M0+内核的数据是共享地址的数据，
         * 为了避免两个内核同时访问, 加入共享互斥访问处理。
         */
        amhw_mbox_mutex_take(AMHW_MAILBOX);
        shared_data++;
        amhw_mbox_mutex_give(AMHW_MAILBOX);
        
        /* 发送数据到M0+内核 */
        amhw_mbox_val_set(AMHW_MAILBOX, AMHW_MBOX_M0PLUS_ID, (uint32_t)&shared_data);
        am_mdelay(500);

    }
}

/** [src_dualcore_mbox_m4] */

/* end of files */

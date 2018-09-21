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
 * \brief 双核（M0+部分）MailBox演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. 当接收到偶数时，LED亮；
 *   2. 当接收到奇数是，LED灭，LED以500ms时间间隔闪烁；
 *   3. 当接收到共享数据时, 发送1到M4内核作为响应。
 * 
 * \par 源代码
 * \snippet demo_dualcore_mbox_m0p.c src_dualcore_mbox_m0p 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  jon, add mail box for CPUs communicate.
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_dualcore_mbox_m0p
 * \copydoc demo_dualcore_mbox_m0p.c
 */

/** [src_dualcore_mbox_m0p] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief mailbox中断处理函数
 * \param[in] p_arg : 中断入口参数
 * \return  无
 */
void mbox_irq_handler (void *p_arg)
{
    amhw_mailbox_t *p_hw_mbox = (amhw_mailbox_t *)p_arg;
    
    uint32_t shared_value;
    
    /* 
     * 读取M0+内核消息邮箱的数据
     */
    uint32_t *p_shared_vale = (uint32_t *)amhw_mbox_val_get(p_hw_mbox, AMHW_MBOX_M0PLUS_ID);
    
    /* 
     * 由于得到的数据是共享地址的数据 
     * 为了避免两个内核同时访问, 加入共享互斥访问处理
     */
    amhw_mbox_mutex_take(p_hw_mbox);
    shared_value = *p_shared_vale;
    amhw_mbox_mutex_give(p_hw_mbox);
    
    if (shared_value % 2 == 0) {
        am_led_on(LED0);
    
    } else {
        am_led_off(LED0);
    }

    /* 清除M0+内核消息邮箱的所有数据位 */
    amhw_mbox_val_bits_clr(p_hw_mbox, AMHW_MBOX_M0PLUS_ID, 0xFFFFFFFF);
    
    /* 写数据1到M4内核，表明接收到共享变量 */
    amhw_mbox_val_set(p_hw_mbox, AMHW_MBOX_M4_ID, 1);     
    
}

/**
 * \brief 主函数
 */
int main (void)
{
    /* 板级初始化 */
    am_board_init();

    /* 连接并使能消息邮箱中断 */
    am_int_connect(INUM_MAILBOX, mbox_irq_handler, (void *)AMHW_MAILBOX);
    am_int_enable(INUM_MAILBOX);
    
    while (1) {
        __WFI();
    }
}

/** [src_dualcore_mbox_m0p] */

/* end of file */

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
 * \brief 掉电检测演示例程，通过HW层的接口实现
 *
 * - 实验现象:
 *   1. 若外部引脚引起的复位，串口输出 "Reset by External Reset Pin"； 
 *   2. 若掉电检测引起的复位，串口输出 "Reset by BOD"；
 *   3. 若供电电压低于3.05V，将产生中断。
 *
 * \par 源代码
 * \snippet demo_hw_bod.c src_hw_bod
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_bod
 * \copydoc demo_hw_bod.c
 */
 
/** [src_hw_bod] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief BOD 中断处理函数
 * \param[in] p_arg : 中断入口参数
 * \return  None
 */
void bod_irq_handler (void *p_arg)
{
    AM_DBG_INFO("The BOD hanppen\r\n");
}

/**
 * \brief 主函数
 */
int main (void)
{
    /* 班级初始化 */
    am_board_init();

    /* 
     * 若掉电检测引起复位，串口输出提示字符，LED0亮 
     */
    if ((amhw_syscon_rst_stat_get() & AMHW_SYSCON_RSTSTAT_BOD) != 0) {
        amhw_syscon_rst_stat_clr(AMHW_SYSCON_RSTSTAT_BOD);
        
        AM_DBG_INFO("Reset by BOD\r\n");
        am_led_on(LED0);
        
    } else if ((amhw_syscon_rst_stat_get() & AMHW_SYSCON_RSTSTAT_EXTRST) != 0) {
        
        AM_DBG_INFO("Reset by External Reset Pin \r\n");
    }

    amhw_syscon_powerup(AMHW_SYSCON_PD_BOD_RST | AMHW_SYSCON_PD_BOD_INTR);
 
    /* 设定掉电检测中断电压3.05V，设备复位电压1.5V。 */
    amhw_pmu_bod_level_set(AMHW_PMU_BODRSTLVL_1_50V, AMHW_PMU_BODINTLVL_3_05V);
    
    amhw_pmu_bod_rst_enable();
    amhw_pmu_bod_int_enable();
    
    am_int_connect(INUM_BOD, bod_irq_handler, (void *)LED0);
    am_int_enable(INUM_BOD);

    while (1) {
        __WFI();
    }

}

/** [src_hw_bod] */

/* end of file */

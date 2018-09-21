/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief 使用系统滴答时钟(Systick) 实现标准的毫秒级别延时函数和微秒级别延时函数 
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
 
#include "am_delay.h"
#include "amhw_systick.h"
#include "amhw_lpc5410x.h"
#include "amhw_clock.h"

uint32_t __g_us_ticks;    /**< \brief 当延时1us的计数值   */
uint32_t __g_ms_ticks;    /**< \brief 当延时1ms的计数值   */

uint32_t __g_us_max;      /**< \brief 延时的最大us数      */
uint32_t __g_ms_max;      /**< \brief 延时的最大ms数      */


/**
 * \brief 延时函数初始化
 */
void am_delay_init (void)
{
    uint32_t system_clock = g_system_clkfreq;
    
    /* 使用系统时钟作为Systick定时器时钟源 */
    am_systick_config(AMHW_SYSTICK, AMHW_SYSTICK_CONFIG_CLKSRC_SYSTEM);
    
    am_systick_val_set(AMHW_SYSTICK, 0);
 
    __g_us_ticks =  system_clock / 1000000;    
    __g_ms_ticks =  system_clock / 1000;   
    
    __g_us_max   = (uint64_t)0xFFFFFF * (uint64_t)1000000 / system_clock; 
    
    __g_ms_max   = __g_us_max / 1000; 
}

/** 
 * \brief 毫秒级别延时函数
 */
void am_mdelay (uint32_t nms)
{
    uint32_t n_max  = nms / __g_ms_max;        
    uint32_t ms_rem = nms % __g_ms_max;       

    if (n_max > 0) {    
        am_systick_reload_val_set(AMHW_SYSTICK,__g_ms_max * __g_ms_ticks);
       
        am_systick_val_set(AMHW_SYSTICK,0);  /* 清零计数器值   */
        
        am_systick_enable(AMHW_SYSTICK);     /* 开始向下计数   */

        while (n_max > 0) {
            
            /* Wait for time up */
            while (am_systick_flag_check(AMHW_SYSTICK) != TRUE);
            n_max--;
        }
        am_systick_disable(AMHW_SYSTICK);    /* 停止计数       */
    }  

    am_systick_reload_val_set(AMHW_SYSTICK, ms_rem * __g_ms_ticks);
    
    am_systick_val_set(AMHW_SYSTICK, 0);     /* 清零计数器值   */
    am_systick_enable(AMHW_SYSTICK);         /* 开始向下计数   */
    
    /* 等待延时完成 */
    while (am_systick_flag_check(AMHW_SYSTICK) != TRUE);
 
    am_systick_disable(AMHW_SYSTICK);        /* 停止计数       */
    am_systick_val_set(AMHW_SYSTICK, 0);     /* 清零计数器值   */
}
 
/** 
 * \brief 微秒级别延时函数
 *
 * 当系统时钟为：100MHz, __g_us_max = 0xFFFFFF * 1000000 / 100000000 
 *                                  = 0xFFFFFF / 100 
 *                                  = 167772us
 * 当系统时钟为：12MHz, __g_us_max  = 0xFFFFFF * 1000000 / 12000000 
 *                                  = 0xFFFFFF / 12 
 *                                  = 1398101 us
 */
void am_udelay (uint32_t nus)
{
    /* 根据延时微秒数装载定时值 */
    am_systick_reload_val_set(AMHW_SYSTICK, nus * __g_us_ticks);

    am_systick_val_set(AMHW_SYSTICK, 0);    /* 清零计数器值   */
    am_systick_enable(AMHW_SYSTICK);        /* 开始向下计数   */
   
    /* 等待延时完成 */
    while (am_systick_flag_check(AMHW_SYSTICK) != TRUE);
    
    am_systick_disable(AMHW_SYSTICK);       /* 停止计数       */
    am_systick_val_set(AMHW_SYSTICK, 0);    /* 清零计数器值   */
}
 
/* end of file */

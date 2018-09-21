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
 * \brief LPC5410X GPIO 用户配置文件。
 * \sa amdr_hwconfig_gpio.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  asd, first implementation.
 * \endinternal
 */
 
#include "amdr_hwconfig_gpio.h"

/**
 * \addtogroup amdr_if_hwconfig_src_gpio
 * \copydoc amdr_hwconfig_gpio.c
 * @{
 */

/** \brief 引脚触发信息内存 */
static struct amdr_gpio_trigger_info g_gpio_triginfos[PIN_INT_MAX];

/** \brief 引脚触发信息映射 */
static uint8_t g_gpio_infomap[PIN_INT_MAX];

/** \brief GPIO设备信息 */
const amdr_gpio_devinfo_t g_gpio_devinfo = {
    
    AMHW_GPIO,                 /**< \brief 指向GPIO寄存器块的指针     */
    AMHW_IOCON,                /**< \brief 指向IOCON寄存器块的指针    */
    AMHW_PINT,                 /**< \brief 指向引脚中断寄存器块的指针 */
    AMHW_INMUX,                /**< \brief 指向输入复用寄存器块的指针 */
    
    {
        INUM_PIN_INT0,         /**< \brief PINT0中断号 */
        INUM_PIN_INT1,         /**< \brief PINT1中断号 */
        INUM_PIN_INT2,         /**< \brief PINT2中断号 */
        INUM_PIN_INT3,         /**< \brief PINT3中断号 */ 
        
#ifdef AM_CORTEX_M4
        
        INUM_PIN_INT4,         /**< \brief PINT4中断号 */
        INUM_PIN_INT5,         /**< \brief PINT5中断号 */
        INUM_PIN_INT6,         /**< \brief PINT6中断号 */
        INUM_PIN_INT7,         /**< \brief PINT7中断号 */
        
#endif
    },
    
    PIN_INT_MAX,               /**< \brief GPIO支持的引脚中断号数量 */
    g_gpio_infomap,            /**< \brief 引脚触发信息映射         */
    g_gpio_triginfos           /**< \brief 引脚触发信息内存         */
};

/** \brief GPIO设备实例 */
amdr_gpio_dev_t g_gpio_dev;

/** \brief GPIO平台初始化 */
void amhw_plfm_gpio_init (void)
{
    /* 使能GPIO相关外设时钟 */
    amhw_clock_periph_enable(AMHW_CLOCK_GPIO0);
    amhw_clock_periph_enable(AMHW_CLOCK_GPIO1);
    amhw_clock_periph_enable(AMHW_CLOCK_IOCON); 
    amhw_clock_periph_enable(AMHW_CLOCK_INMUX);
    amhw_clock_periph_enable(AMHW_CLOCK_PINT);

    /* 复位GPIO相关外设 */
    amhw_syscon_periph_reset(AMHW_RESET_GPIO0);
    amhw_syscon_periph_reset(AMHW_RESET_GPIO1);
    amhw_syscon_periph_reset(AMHW_RESET_IOCON);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_PINT);
}

/** \brief GPIO平台去初始化 */
void amhw_plfm_gpio_deinit (void)
{
    /* 复位GPIO相关外设 */
    amhw_syscon_periph_reset(AMHW_RESET_GPIO0);
    amhw_syscon_periph_reset(AMHW_RESET_GPIO1);
    amhw_syscon_periph_reset(AMHW_RESET_IOCON);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_PINT);
    
    /* 禁能GPIO相关外设时钟 */
    amhw_clock_periph_disable(AMHW_CLOCK_GPIO0);
    amhw_clock_periph_disable(AMHW_CLOCK_GPIO1);
    amhw_clock_periph_disable(AMHW_CLOCK_IOCON); 
    amhw_clock_periph_disable(AMHW_CLOCK_INMUX);
    amhw_clock_periph_disable(AMHW_CLOCK_PINT);
}


/**
 * @}
 */

/* end of file */

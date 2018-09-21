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
 * \brief LPC5410X USART 用户配置文件 
 * \sa amdr_hwconfig_usart.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_usart.h"

/**
 * \addtogroup amdr_if_hwconfig_src_usart
 * \copydoc amdr_hwconfig_usart.c
 * @{
 */

/**
 * \brief USART小数分频单元输出频率
 * 
 * 为了获取高精度的波特率，需要利用小数分频器（FRG）将串口的基本输入频率设置为
 * 期望波特率的整数倍。\n
 * 串口基本输入频率的范围是：g_async_clkfreq / (1 + 255/256) ~ g_async_clkfreq \n
 * 例如：\n
 * g_async_clkfreq = 12MHz \n
 * 串口基本输入频率的范围即为： 6,011,741Hz ~ 12MHz \n
 * 为了设置波特率为115200,故设置串口基本输入频率为：
 * 11,059,200Hz(11059200 = 115200 * 96)。\n
 * 实际上，串口基本输入频率设置为11.0592MHz，可满足大多数波特率的设置(9600,4800,115200) 
 *
 */
const uint32_t __g_usart_clkrate = 11059200;

/** \brief 串口0 设备信息 */
const amdr_usart_devinfo_t g_usart0_devinfo = {
    
    AMHW_USART0,                    /**< \brief 串口0              */
    INUM_USART0,                    /**< \brief 串口0的中断编号    */
    
    AMHW_USART_CFG_8BIT      |      /**< \brief 8位数据            */
    AMHW_USART_CFG_PARITY_NO |      /**< \brief 无极性             */
    AMHW_USART_CFG_STOP_1,          /**< \brief 1个停止位          */
    
    0,                              /**< \brief 无控制标志         */

    115200,                         /**< \brief 设置的波特率       */
    
    0,                              /**< \brief 无其他中断         */
    {
        AMHW_FIFO,
        AMHW_FIFO_USART0,
        4,                          /**< \brief 接收FIFO大小为4     */
        4,                          /**< \brief 接收FIFO大小为4     */
        2,                          /**< \brief 设置超时时间基值 2  */
        12,                         /**< \brief 设置超时时间12      */
                                    /**< \brief 故超时时间位 2 ^2 * 12 = 48 */
    },
};

amdr_usart_dev_t  g_usart0_dev;     /**< \brief 定义串口0 设备          */

/** \brief 串口0平台初始化 */
void amhw_plfm_usart0_init (void)
{
    /* 使能串口0时钟并复位 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART0);
    amhw_syscon_periph_reset(AMHW_RESET_USART0);
    
    /* 使能串口0FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U0TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U0RXFIFOEN);
    
    /* 配置PIO0_0作为UART0_RXD */
    am_gpio_pin_cfg(PIO0_0, PIO0_0_USART0_RXD | PIO0_0_PULLUP);
    
    /* 配置PIO0_1作为UART0_TXD */
    am_gpio_pin_cfg(PIO0_1, PIO0_1_USART0_TXD | PIO0_1_PULLUP);

    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief 解除串口0 平台初始化 */
void amhw_plfm_usart0_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART0);
    amhw_clock_periph_disable(AMHW_CLOCK_USART0);
    
    /* 禁能串口0FIFO */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U0TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U0RXFIFOEN);
}

/** \brief 串口1 设备信息 */
const amdr_usart_devinfo_t g_usart1_devinfo = {
    
    AMHW_USART1,                   /**< \brief 串口1              */
    INUM_USART1,                   /**< \brief 串口1的中断编号    */
                                   
    AMHW_USART_CFG_8BIT      |     /**< \brief 8位数据            */
    AMHW_USART_CFG_PARITY_NO |     /**< \brief 无极性             */
    AMHW_USART_CFG_STOP_1,         /**< \brief 1个停止位          */
                                   
    0,                             /**< \brief 无控制标志         */
                                   
    115200,                        /**< \brief 设置的波特率       */
                                   
    0,                             /**< \brief 无其他中断         */
    {                              
        AMHW_FIFO,                 
        AMHW_FIFO_USART1,          
        4,                         /**< \brief 接收FIFO大小为4     */
        4,                         /**< \brief 接收FIFO大小为4     */
        2,                         /**< \brief 设置超时时间基值 2  */
        12,                        /**< \brief 设置超时时间12      */
                                   /**< \brief 故超时时间位 2 ^2 * 12 = 48 */
    },
}; 

amdr_usart_dev_t  g_usart1_dev;    /**< \brief 定义串口1 设备          */

/** \brief 串口1平台初始化 */
void amhw_plfm_usart1_init (void)
{
    /* 使能串口1时钟并复位 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART1);
    amhw_syscon_periph_reset(AMHW_RESET_USART1);
    
    /* 使能串口1FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U1TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U1RXFIFOEN);
    
    /* 配置PIO0_5作为UART1_RXD */
    am_gpio_pin_cfg(PIO0_5, PIO0_5_USART1_RXD | PIO0_5_PULLUP);
    
    /* 配置PIO0_6作为UART1_TXD */
    am_gpio_pin_cfg(PIO0_6, PIO0_6_USART1_TXD | PIO0_6_PULLUP);
    
    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief 解除串口1 平台初始化 */
void amhw_plfm_usart1_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART1);
    amhw_clock_periph_disable(AMHW_CLOCK_USART1);
    
    /* 禁能串口1FIFO */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U1TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U1RXFIFOEN);
}

/** \brief 串口2 设备信息 */
const amdr_usart_devinfo_t g_usart2_devinfo = {
    
    AMHW_USART2,                  /**< \brief 串口2              */
    INUM_USART2,                  /**< \brief 串口2的中断编号    */
                                  
    AMHW_USART_CFG_8BIT      |    /**< \brief 8位数据            */
    AMHW_USART_CFG_PARITY_NO |    /**< \brief 无极性             */
    AMHW_USART_CFG_STOP_1,        /**< \brief 1个停止位          */
                                  
    0,                            /**< \brief 无控制标志         */
                                  
    115200,                       /**< \brief 设置的波特率       */
                                  
    0,                            /**< \brief 无其他中断         */
    {                             
        AMHW_FIFO,                
        AMHW_FIFO_USART2,         
        4,                        /**< \brief 接收FIFO大小为4     */
        4,                        /**< \brief 接收FIFO大小为4     */
        2,                        /**< \brief 设置超时时间基值 2  */
        12,                       /**< \brief 设置超时时间12      */
                                  /**< \brief 故超时时间位 2 ^2 * 12 = 48 */
    },
}; 

amdr_usart_dev_t  g_usart2_dev;   /**< \brief 定义串口2 设备          */

/** \brief 串口2平台初始化 */
void amhw_plfm_usart2_init (void)
{
    /* 使能串口2时钟并复位 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART2);
    amhw_syscon_periph_reset(AMHW_RESET_USART2);
    
    /* 使能串口2FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U2TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U2RXFIFOEN);
    
    /* 配置PIO0_8作为UART2_RXD */
    am_gpio_pin_cfg(PIO0_8, PIO0_8_USART2_RXD | PIO0_8_PULLUP);
    
    /* 配置PIO0_9作为UART2_TXD */
    am_gpio_pin_cfg(PIO0_9, PIO0_9_USART2_TXD | PIO0_9_PULLUP);
    
    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief 解除串口2 平台初始化 */
void amhw_plfm_usart2_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART2);
    amhw_clock_periph_disable(AMHW_CLOCK_USART2);
    
    /* 禁能串口2FIFO */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U2TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U2RXFIFOEN);
}

/** \brief 串口3 设备信息 */
const amdr_usart_devinfo_t g_usart3_devinfo = {
    
    AMHW_USART3,                   /**< \brief 串口3              */
    INUM_USART3,                   /**< \brief 串口3的中断编号    */
                                   
    AMHW_USART_CFG_8BIT      |     /**< \brief 8位数据            */
    AMHW_USART_CFG_PARITY_NO |     /**< \brief 无极性             */
    AMHW_USART_CFG_STOP_1,         /**< \brief 1个停止位          */
                                   
    0,                             /**< \brief 无控制标志         */
                                   
    115200,                        /**< \brief 设置的波特率       */
                                   
    0,                             /**< \brief 无其他中断         */
    {                              
        AMHW_FIFO,                 
        AMHW_FIFO_USART3,          
        4,                         /**< \brief 接收FIFO大小为4     */
        4,                         /**< \brief 接收FIFO大小为4     */
        2,                         /**< \brief 设置超时时间基值 2  */
        12,                        /**< \brief 设置超时时间12      */
                                   /**< \brief 故超时时间位 2 ^2 * 12 = 48 */
    },
}; 

amdr_usart_dev_t  g_usart3_dev;    /**< \brief 定义串口3 设备          */

/** \brief 串口3平台初始化 */
void amhw_plfm_usart3_init (void)
{
    /* 使能串口3时钟并复位 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART3);
    amhw_syscon_periph_reset(AMHW_RESET_USART3);
    
    /* 使能串口3FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U3TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U3RXFIFOEN);
    
    /* 配置PIO0_20作为UART3_RXD */
    am_gpio_pin_cfg(PIO0_20, PIO0_20_USART3_RXD | PIO0_20_PULLUP);
    
    /* 配置PIO0_18作为UART3_TXD */
    am_gpio_pin_cfg(PIO0_18, PIO0_18_USART3_TXD | PIO0_18_PULLUP);
    
    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief 解除串口3 平台初始化 */
void amhw_plfm_usart3_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART3);
    amhw_clock_periph_disable(AMHW_CLOCK_USART3);
    
    /* 禁能串口3 */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U3TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U3RXFIFOEN);
}

/**
 * @}
 */

/* end of file */

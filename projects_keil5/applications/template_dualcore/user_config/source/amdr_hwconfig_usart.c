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
 * \brief LPC5410X USART �û������ļ� 
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
 * \brief USARTС����Ƶ��Ԫ���Ƶ��
 * 
 * Ϊ�˻�ȡ�߾��ȵĲ����ʣ���Ҫ����С����Ƶ����FRG�������ڵĻ�������Ƶ������Ϊ
 * ���������ʵ���������\n
 * ���ڻ�������Ƶ�ʵķ�Χ�ǣ�g_async_clkfreq / (1 + 255/256) ~ g_async_clkfreq \n
 * ���磺\n
 * g_async_clkfreq = 12MHz \n
 * ���ڻ�������Ƶ�ʵķ�Χ��Ϊ�� 6,011,741Hz ~ 12MHz \n
 * Ϊ�����ò�����Ϊ115200,�����ô��ڻ�������Ƶ��Ϊ��
 * 11,059,200Hz(11059200 = 115200 * 96)��\n
 * ʵ���ϣ����ڻ�������Ƶ������Ϊ11.0592MHz�����������������ʵ�����(9600,4800,115200) 
 *
 */
const uint32_t __g_usart_clkrate = 11059200;

/** \brief ����0 �豸��Ϣ */
const amdr_usart_devinfo_t g_usart0_devinfo = {
    
    AMHW_USART0,                    /**< \brief ����0              */
    INUM_USART0,                    /**< \brief ����0���жϱ��    */
    
    AMHW_USART_CFG_8BIT      |      /**< \brief 8λ����            */
    AMHW_USART_CFG_PARITY_NO |      /**< \brief �޼���             */
    AMHW_USART_CFG_STOP_1,          /**< \brief 1��ֹͣλ          */
    
    0,                              /**< \brief �޿��Ʊ�־         */

    115200,                         /**< \brief ���õĲ�����       */
    
    0,                              /**< \brief �������ж�         */
    {
        AMHW_FIFO,
        AMHW_FIFO_USART0,
        4,                          /**< \brief ����FIFO��СΪ4     */
        4,                          /**< \brief ����FIFO��СΪ4     */
        2,                          /**< \brief ���ó�ʱʱ���ֵ 2  */
        12,                         /**< \brief ���ó�ʱʱ��12      */
                                    /**< \brief �ʳ�ʱʱ��λ 2 ^2 * 12 = 48 */
    },
};

amdr_usart_dev_t  g_usart0_dev;     /**< \brief ���崮��0 �豸          */

/** \brief ����0ƽ̨��ʼ�� */
void amhw_plfm_usart0_init (void)
{
    /* ʹ�ܴ���0ʱ�Ӳ���λ */
    amhw_clock_periph_enable(AMHW_CLOCK_USART0);
    amhw_syscon_periph_reset(AMHW_RESET_USART0);
    
    /* ʹ�ܴ���0FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U0TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U0RXFIFOEN);
    
    /* ����PIO0_0��ΪUART0_RXD */
    am_gpio_pin_cfg(PIO0_0, PIO0_0_USART0_RXD | PIO0_0_PULLUP);
    
    /* ����PIO0_1��ΪUART0_TXD */
    am_gpio_pin_cfg(PIO0_1, PIO0_1_USART0_TXD | PIO0_1_PULLUP);

    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief �������0 ƽ̨��ʼ�� */
void amhw_plfm_usart0_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART0);
    amhw_clock_periph_disable(AMHW_CLOCK_USART0);
    
    /* ���ܴ���0FIFO */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U0TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U0RXFIFOEN);
}

/** \brief ����1 �豸��Ϣ */
const amdr_usart_devinfo_t g_usart1_devinfo = {
    
    AMHW_USART1,                   /**< \brief ����1              */
    INUM_USART1,                   /**< \brief ����1���жϱ��    */
                                   
    AMHW_USART_CFG_8BIT      |     /**< \brief 8λ����            */
    AMHW_USART_CFG_PARITY_NO |     /**< \brief �޼���             */
    AMHW_USART_CFG_STOP_1,         /**< \brief 1��ֹͣλ          */
                                   
    0,                             /**< \brief �޿��Ʊ�־         */
                                   
    115200,                        /**< \brief ���õĲ�����       */
                                   
    0,                             /**< \brief �������ж�         */
    {                              
        AMHW_FIFO,                 
        AMHW_FIFO_USART1,          
        4,                         /**< \brief ����FIFO��СΪ4     */
        4,                         /**< \brief ����FIFO��СΪ4     */
        2,                         /**< \brief ���ó�ʱʱ���ֵ 2  */
        12,                        /**< \brief ���ó�ʱʱ��12      */
                                   /**< \brief �ʳ�ʱʱ��λ 2 ^2 * 12 = 48 */
    },
}; 

amdr_usart_dev_t  g_usart1_dev;    /**< \brief ���崮��1 �豸          */

/** \brief ����1ƽ̨��ʼ�� */
void amhw_plfm_usart1_init (void)
{
    /* ʹ�ܴ���1ʱ�Ӳ���λ */
    amhw_clock_periph_enable(AMHW_CLOCK_USART1);
    amhw_syscon_periph_reset(AMHW_RESET_USART1);
    
    /* ʹ�ܴ���1FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U1TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U1RXFIFOEN);
    
    /* ����PIO0_5��ΪUART1_RXD */
    am_gpio_pin_cfg(PIO0_5, PIO0_5_USART1_RXD | PIO0_5_PULLUP);
    
    /* ����PIO0_6��ΪUART1_TXD */
    am_gpio_pin_cfg(PIO0_6, PIO0_6_USART1_TXD | PIO0_6_PULLUP);
    
    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief �������1 ƽ̨��ʼ�� */
void amhw_plfm_usart1_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART1);
    amhw_clock_periph_disable(AMHW_CLOCK_USART1);
    
    /* ���ܴ���1FIFO */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U1TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U1RXFIFOEN);
}

/** \brief ����2 �豸��Ϣ */
const amdr_usart_devinfo_t g_usart2_devinfo = {
    
    AMHW_USART2,                  /**< \brief ����2              */
    INUM_USART2,                  /**< \brief ����2���жϱ��    */
                                  
    AMHW_USART_CFG_8BIT      |    /**< \brief 8λ����            */
    AMHW_USART_CFG_PARITY_NO |    /**< \brief �޼���             */
    AMHW_USART_CFG_STOP_1,        /**< \brief 1��ֹͣλ          */
                                  
    0,                            /**< \brief �޿��Ʊ�־         */
                                  
    115200,                       /**< \brief ���õĲ�����       */
                                  
    0,                            /**< \brief �������ж�         */
    {                             
        AMHW_FIFO,                
        AMHW_FIFO_USART2,         
        4,                        /**< \brief ����FIFO��СΪ4     */
        4,                        /**< \brief ����FIFO��СΪ4     */
        2,                        /**< \brief ���ó�ʱʱ���ֵ 2  */
        12,                       /**< \brief ���ó�ʱʱ��12      */
                                  /**< \brief �ʳ�ʱʱ��λ 2 ^2 * 12 = 48 */
    },
}; 

amdr_usart_dev_t  g_usart2_dev;   /**< \brief ���崮��2 �豸          */

/** \brief ����2ƽ̨��ʼ�� */
void amhw_plfm_usart2_init (void)
{
    /* ʹ�ܴ���2ʱ�Ӳ���λ */
    amhw_clock_periph_enable(AMHW_CLOCK_USART2);
    amhw_syscon_periph_reset(AMHW_RESET_USART2);
    
    /* ʹ�ܴ���2FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U2TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U2RXFIFOEN);
    
    /* ����PIO0_8��ΪUART2_RXD */
    am_gpio_pin_cfg(PIO0_8, PIO0_8_USART2_RXD | PIO0_8_PULLUP);
    
    /* ����PIO0_9��ΪUART2_TXD */
    am_gpio_pin_cfg(PIO0_9, PIO0_9_USART2_TXD | PIO0_9_PULLUP);
    
    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief �������2 ƽ̨��ʼ�� */
void amhw_plfm_usart2_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART2);
    amhw_clock_periph_disable(AMHW_CLOCK_USART2);
    
    /* ���ܴ���2FIFO */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U2TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U2RXFIFOEN);
}

/** \brief ����3 �豸��Ϣ */
const amdr_usart_devinfo_t g_usart3_devinfo = {
    
    AMHW_USART3,                   /**< \brief ����3              */
    INUM_USART3,                   /**< \brief ����3���жϱ��    */
                                   
    AMHW_USART_CFG_8BIT      |     /**< \brief 8λ����            */
    AMHW_USART_CFG_PARITY_NO |     /**< \brief �޼���             */
    AMHW_USART_CFG_STOP_1,         /**< \brief 1��ֹͣλ          */
                                   
    0,                             /**< \brief �޿��Ʊ�־         */
                                   
    115200,                        /**< \brief ���õĲ�����       */
                                   
    0,                             /**< \brief �������ж�         */
    {                              
        AMHW_FIFO,                 
        AMHW_FIFO_USART3,          
        4,                         /**< \brief ����FIFO��СΪ4     */
        4,                         /**< \brief ����FIFO��СΪ4     */
        2,                         /**< \brief ���ó�ʱʱ���ֵ 2  */
        12,                        /**< \brief ���ó�ʱʱ��12      */
                                   /**< \brief �ʳ�ʱʱ��λ 2 ^2 * 12 = 48 */
    },
}; 

amdr_usart_dev_t  g_usart3_dev;    /**< \brief ���崮��3 �豸          */

/** \brief ����3ƽ̨��ʼ�� */
void amhw_plfm_usart3_init (void)
{
    /* ʹ�ܴ���3ʱ�Ӳ���λ */
    amhw_clock_periph_enable(AMHW_CLOCK_USART3);
    amhw_syscon_periph_reset(AMHW_RESET_USART3);
    
    /* ʹ�ܴ���3FIFO */
    amhw_syscon_fifo_enable(AMHW_SYSCON_FIFO_U3TXFIFOEN | 
                            AMHW_SYSCON_FIFO_U3RXFIFOEN);
    
    /* ����PIO0_20��ΪUART3_RXD */
    am_gpio_pin_cfg(PIO0_20, PIO0_20_USART3_RXD | PIO0_20_PULLUP);
    
    /* ����PIO0_18��ΪUART3_TXD */
    am_gpio_pin_cfg(PIO0_18, PIO0_18_USART3_TXD | PIO0_18_PULLUP);
    
    amhw_clock_usart_baseclkrate_set(__g_usart_clkrate);
}

/** \brief �������3 ƽ̨��ʼ�� */
void amhw_plfm_usart3_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_USART3);
    amhw_clock_periph_disable(AMHW_CLOCK_USART3);
    
    /* ���ܴ���3 */
    amhw_syscon_fifo_disable(AMHW_SYSCON_FIFO_U3TXFIFOEN | 
                             AMHW_SYSCON_FIFO_U3RXFIFOEN);
}

/**
 * @}
 */

/* end of file */

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
 * \brief EasyARM-54000M4 ���ڵ��Զ˿�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */
 
#include "am_prj_config.h"
#include "amhw_usart.h"
#include "amhw_clock.h"
#include "am_debug.h"

/**
 * \brief ����֧�ֱ�׼����:printf
 */
struct __FILE {
    int handle;      /**< \brief ������� */
}; 

/**
 * \brief FILE ���� ��stdio.h�ļ��ж���
 * @{
 */
FILE __stdout;       /**< \brief ��׼��� */
FILE __stdin;        /**< \brief ��׼���� */
/** @} */

/**
 * \brief ���� _sys_exit, ���������ģʽ
 */
_sys_exit (int x) 
{ 
    x = x; 
}

static amhw_usart_t  *__gp_debug_usart = NULL;

/**
 * \brief fputc�����ض���
 */
int fputc (int ch, FILE *f)
{  

    while ((amhw_usart_stat_get(__gp_debug_usart) & AMHW_USART_STAT_TXRDY) == 0);
    
    amhw_usart_txdata_write(__gp_debug_usart, ch);
    
    return ch;
}

/**
 * \brief fgetc�����ض���
 */
int fgetc (FILE *f)
{    
    int ch;
    
    while ((amhw_usart_stat_get(__gp_debug_usart) & AMHW_USART_STAT_RXRDY) == 0);
    
    ch = amhw_usart_rxdata_read(__gp_debug_usart);
    
    return ch;

}

void am_debug_init (void)
{
#if (AM_CFG_DEBUG_USART == 0)
    __gp_debug_usart = AMHW_USART0;
    
    /* ʹ�ܴ���0ʱ�ӣ���λ����0 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART0);
    amhw_syscon_periph_reset(AMHW_RESET_USART0);
    
    /* ����PIO0_0 �ܽ���Ϊ USART0_RXD */
    am_gpio_pin_cfg(PIO0_0, PIO0_0_USART0_RXD | PIO0_0_PULLUP);
    
    /* ����PIO0_1 �ܽ���Ϊ USART0_TXD */
    am_gpio_pin_cfg(PIO0_1, PIO0_1_USART0_TXD | PIO0_1_PULLUP);

#endif
    
#if (AM_CFG_DEBUG_USART == 1)
    __gp_debug_usart = AMHW_USART1;
    
    /* ʹ�ܴ���1ʱ�ӣ���λ����1 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART1);
    amhw_syscon_periph_reset(AMHW_RESET_USART1);
    
    /* ����PIO0_5 �ܽ���Ϊ USART1_RXD */
    am_gpio_pin_cfg(PIO0_5, PIO0_5_USART1_RXD | PIO0_5_PULLUP);
    
    /* ����PIO0_6 �ܽ���Ϊ USART1_TXD */
    am_gpio_pin_cfg(PIO0_6, PIO0_6_USART1_TXD | PIO0_6_PULLUP);
    
#endif
    
#if (AM_CFG_DEBUG_USART == 2)
    __gp_debug_usart = AMHW_USART2;
    
    /* ʹ�ܴ���2ʱ�ӣ���λ����2 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART2);
    amhw_syscon_periph_reset(AMHW_RESET_USART2);
    
    /* ����PIO0_8 �ܽ���Ϊ USART2_RXD */
    am_gpio_pin_cfg(PIO0_8, PIO0_8_USART2_RXD | PIO0_8_PULLUP);
    
    /* ����PIO0_9 �ܽ���Ϊ USART2_TXD */
    am_gpio_pin_cfg(PIO0_9, PIO0_9_USART2_TXD | PIO0_9_PULLUP);
    
#endif
    
#if (AM_CFG_DEBUG_USART == 3)
    __gp_debug_usart = AMHW_USART3;
    
    /* ʹ�ܴ���3ʱ�ӣ���λ����3 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART3);
    amhw_syscon_periph_reset(AMHW_RESET_USART3);
    
    /* ����PIO0_20 �ܽ���Ϊ USART3_RXD */
    am_gpio_pin_cfg(PIO0_20, PIO0_20_USART3_RXD | PIO0_20_PULLUP);
    
    /* ����PIO0_18 �ܽ���Ϊ USART3_TXD */
    am_gpio_pin_cfg(PIO0_18, PIO0_18_USART3_TXD | PIO0_18_PULLUP);
    
#endif

    amhw_clock_usart_baseclkrate_set(11059200);
    
    amhw_usart_config(__gp_debug_usart, AMHW_USART_CFG_8BIT       |
                                        AMHW_USART_CFG_PARITY_NO  |
                                        AMHW_USART_CFG_STOP_1); 
    
    amhw_usart_baudrate_set(__gp_debug_usart,
                            amhw_clock_usart_baseclkrate_get(),
                            AM_CFG_DEBUG_BAUDRATE);
    
    amhw_usart_enable(__gp_debug_usart);
}

int am_kprintf (const char *fmt, ...)
{
    int     len;
    va_list args;

    va_start(args, fmt);
    len = vprintf(fmt, args);
    va_end(args);

    return len;
}

/* end of file */

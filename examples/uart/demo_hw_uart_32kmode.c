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
 * \brief  USART 32kmodeģʽ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - �������裺
 *   1. PIO0_0 ��������PC���ڵ�TXD;
 *   2. PIO0_1 ��������PC���ڵ�RXD��
 *
 * - ʵ������
 *   1. MCU������磨power down��ģʽ�����յ�һ���ַ�ʱ��MCU����ӵ��磨power down��ģʽ���ѣ�
 *      ��ͨ�����ڷ��͡�wake up���ַ���
 *
 * \par Դ����
 * \snippet demo_hw_uart_32kmode.c src_hw_uart_32kmode
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-15  hbt, first implementation.
 * \endinternal
 */
/**
 * \addtogroup demo_if_hw_uart_32kmode
 * \copydoc demo_hw_uart_32kmode.c
 */

/** [src_hw_uart_32kmode] */
#include "ametal.h"
#include "am_board.h"

#define    USART_CH           AMHW_USART0

/**\brief �����ʣ���32kmodeģʽ�£����������Ϊ9600������������4800��2400��1200... */
#define    USART_BAUDRATE     (9600)

uint8_t g_int_rec;

void usart0_irq_handler(void *p_arg)
{
    am_led_on(LED0);

    if ((amhw_usart_intstat_get(USART_CH) & AMHW_USART_STAT_RXRDY) != 0) {

        g_int_rec = amhw_usart_rxdata_read(USART_CH);

    }
}


/**
 * \brief ��ʼ��USART
 */
void usart_init (void)
{
    /* ʹ��USART0ʱ�ӣ�����λUSART0 */
    amhw_clock_periph_enable(AMHW_CLOCK_USART0);
    amhw_syscon_periph_reset(AMHW_RESET_USART0);

    /* ��PIO0_0��������ΪUART0_RXD */
    am_gpio_pin_cfg(PIO0_0, PIO0_0_USART0_RXD | PIO0_0_PULLUP);

    /* ��PIO0_1��������ΪUART0_TXD */
    am_gpio_pin_cfg(PIO0_1, PIO0_1_USART0_TXD | PIO0_1_PULLUP);

    /* ��RTC 32K���� */
    amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);

    /*
     * ʹ��RTC������������Ƶ�ʿ���ͨ������
     * am_clock_rtcosc_rate_get() �������
     */
    amhw_clock_rtcosc_enable();

    amhw_usart_config(USART_CH, AMHW_USART_CFG_8BIT       |
                                AMHW_USART_CFG_PARITY_NO  |
                                AMHW_USART_CFG_STOP_1     |
                                AMHW_USART_CFG_MODE32K);

    amhw_usart_baudrate_set(USART_CH,
                            32768,
                            USART_BAUDRATE);

    amhw_usart_int_enable(USART_CH, AMHW_USART_INT_RXRDY);

    am_int_connect(INUM_USART0, usart0_irq_handler, (void *)0);
    am_int_enable(INUM_USART0);

    amhw_usart_enable(USART_CH);

    amhw_syscon_wakeup_enable(AMHW_SYSCON_STARTER_USART0);
}

/**
 * \brief ���������
 */
int main (void)
{

    /* �弶��ʼ�� */
    am_board_init();

    /* USART��ʼ�� */
    usart_init();

    amhw_usart_poll_send(USART_CH, "The USART0 32k-mode for powerdown mode\r\n",
                                  sizeof("The USART0 32-kmode for powerdown mode\r\n") - 1);

    /* �л���ϵͳʱ��ΪIRC�͹ر�PLL��Դ */
    if (amhw_clock_main_src_get() == AMHW_CLOCK_MAIN_SRC_PLLOUT) {

        /* ��PLL�����Ϊ��ʱ�� */
        amhw_clock_main_src_set(AMHW_CLOCK_MAIN_SRC_IRC);
        amhw_syscon_powerdown(AMHW_SYSCON_PD_SYS_PLL);

        amhw_power_voltage_set(AMHW_POWER_VOL_MODE_LOW_POWER, amhw_clock_main_clkrate_get());
        amhw_clock_freq_update();
        am_delay_init();
    }

    while (1) {

        am_led_off(LED0);

        /*  ����˯��״̬ */
        amhw_power_mode_enter(AMHW_POWER_MODE_POWER_DOWN, AMHW_POWER_PD_IRC_OSC  |
                                                          AMHW_POWER_PD_IRC      |
                                                          AMHW_POWER_PD_SRAM0A   |
                                                          AMHW_POWER_PD_ROM      |
                                                          AMHW_POWER_PD_SRAM0B   |
                                                          AMHW_POWER_PD_SRAM1    |
                                                          AMHW_POWER_PD_SRAM2    |
                                                          AMHW_POWER_PD_FLASH    |
                                                          AMHW_POWER_PD_32K_OSC);

        amhw_usart_poll_send(USART_CH, "wake up!\r\n",
                                      sizeof("wake up!\r\n") - 1);


        am_mdelay(20);
    }
}

/** [src_hw_uart_32kmode] */

/* end of file */

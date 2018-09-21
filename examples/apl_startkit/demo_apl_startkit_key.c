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
 * \brief APL_StartKit ������ʾ����
 *
 * - �������裺
 *   1. ʹ������ñ���ӣ�KEY1��KEY2��KEY3��KEY4��KEY5����
 *   2. ʹ������ñ���ӣ�LED1��LED2��LED3��LED4����
 *   3. ��APL_StartKit����ϴ���0�ӿڣ�J3�����ӵ�PC���ϡ�
 *
 * - ʵ������
 *   1. ���°���KEY1��LED1״̬��ת��ͨ�����������Press Down Key!����
 *   2. ���°���KEY2��LED2״̬��ת��ͨ�����������Press Right Key!����
 *   3. ���°���KEY3��LED1��LED2��LED3��LED4״̬ȫ����ת��ͨ�����������Press Ok Key!����
 *   4. ���°���KEY4��LED3״̬��ת��ͨ�����������Press Left Key!����
 *   5. ���°���KEY5��LED4״̬��ת��ͨ�����������Press Up Key!����
 * 
 * \par Դ����
 * \snippet demo_apl_startkit_key.c src_apl_startkit_key 
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_apl_startkit_key
 * \copydoc demo_apl_startkit_key.c
 */

/** [src_apl_startkit_key] */
#include "ametal.h" 
#include "am_board.h"


/* APL_StartKit defines */
#define  LED1           PIO1_6
#define  LED2           PIO1_7
#define  LED3           PIO1_8
#define  LED4           PIO1_9

#define  KEY1           PIO1_10
#define  KEY2           PIO1_11
#define  KEY3           PIO1_12
#define  KEY4           PIO1_13
#define  KEY5           PIO0_8
/**
 * \brief KEY1(down)�жϷ�����
 */
void key_down_isr (void *p_arg)
{
    am_gpio_toggle(LED1);
    AM_DBG_INFO("Press Down Key!\r\n");
}

/**
 * \brief KEY2(right)�жϷ�����
 */
void key_right_isr (void *p_arg)
{
    am_gpio_toggle(LED2);
    AM_DBG_INFO("Press Right Key!\r\n");
}

/**
 * \brief KEY3(OK)�жϷ�����
 */
void key_ok_isr (void *p_arg)
{
    am_gpio_toggle(LED1);
    am_gpio_toggle(LED2);
    am_gpio_toggle(LED3);
    am_gpio_toggle(LED4);
    AM_DBG_INFO("Press Ok Key!\r\n");
}

/**
 * \brief KEY4(left)�жϷ�����
 */
void key_left_isr (void *p_arg)
{
    am_gpio_toggle(LED3);
    AM_DBG_INFO("Press Left Key!\r\n");
}

/**
 * \brief KEY5(up)�жϷ�����
 */
void key_up_isr (void *p_arg)
{
    am_gpio_toggle(LED4);
    AM_DBG_INFO("Press Up Key!\r\n");
}

void apl_startkit_gpio_init(void)
{
    am_gpio_pin_cfg(LED1, AM_GPIO_OUTPUT);        /* ���� LED1 ���ģʽ */
    am_gpio_set(LED1, 1);                         /* LED1 ��ʼ״̬Ϩ��  */
    am_gpio_pin_cfg(LED2, AM_GPIO_OUTPUT);        /* ���� LED2 ���ģʽ */
    am_gpio_set(LED2, 1);                         /* LED2 ��ʼ״̬Ϩ��  */
    am_gpio_pin_cfg(LED3, AM_GPIO_OUTPUT);        /* ���� LED3 ���ģʽ */
    am_gpio_set(LED3, 1);                         /* LED3 ��ʼ״̬Ϩ��  */
    am_gpio_pin_cfg(LED4, AM_GPIO_OUTPUT);        /* ���� LED4 ���ģʽ */
    am_gpio_set(LED4, 1);                         /* LED4 ��ʼ״̬Ϩ��  */
}
/**
 * \brief ���������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();

    apl_startkit_gpio_init();
    
    am_gpio_trigger_connect(KEY1, key_down_isr, (void *)0);  /* KEY1�����жϷ�����       */
    am_gpio_trigger_cfg(KEY1, AM_GPIO_TRIGGER_FALL);         /* ����KEY1�������źʹ���ģʽ */
    am_gpio_trigger_on(KEY1);                                /* ʹ��KEY1���Ŵ����ж�       */
    
    am_gpio_trigger_connect(KEY2, key_right_isr, (void *)0); /* KEY2�����жϷ�����       */
    am_gpio_trigger_cfg(KEY2, AM_GPIO_TRIGGER_FALL);         /* ����KEY2�������źʹ���ģʽ */
    am_gpio_trigger_on(KEY2);                                /* ʹ��KEY2���Ŵ����ж�       */
    
    am_gpio_trigger_connect(KEY3, key_ok_isr, (void *)0);    /* KEY3�����жϷ�����       */
    am_gpio_trigger_cfg(KEY3, AM_GPIO_TRIGGER_FALL);         /* ����KEY3�������źʹ���ģʽ */
    am_gpio_trigger_on(KEY3);                                /* ʹ��KEY3���Ŵ����ж�       */
   
    am_gpio_trigger_connect(KEY4, key_left_isr, (void *)0);  /* KEY4�����жϷ�����       */
    am_gpio_trigger_cfg(KEY4, AM_GPIO_TRIGGER_FALL);         /* ����KEY4�������źʹ���ģʽ */    
    am_gpio_trigger_on(KEY4);                                /* ʹ��KEY4���Ŵ����ж�       */
    
    am_gpio_trigger_connect(KEY5, key_up_isr, (void *)0);    /* KEY5�����жϷ�����       */
    am_gpio_trigger_cfg(KEY5, AM_GPIO_TRIGGER_FALL);         /* ����KEY5�������źʹ���ģʽ */
    am_gpio_trigger_on(KEY5);                                /* ʹ��KEY5���Ŵ����ж�       */
    
    while (1) {
        __WFI();
    }
}

/** [src_apl_startkit_key] */

/* end of file */

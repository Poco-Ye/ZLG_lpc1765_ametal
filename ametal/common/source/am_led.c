/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief LED��׼�ӿ�ʵ��
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-25  fft, first implementation.
 * \endinternal
 */

#include "ametal.h"
#include "am_led.h"
#include "am_gpio.h"


/*******************************************************************************
  ȫ�ֱ���
*******************************************************************************/

am_led_info_t *__pg_led_info = NULL;
uint32_t       __g_led_num   = 0;

/*******************************************************************************
  ��������
*******************************************************************************/ 

/**
 * \brief ��ʼ�� EasyARM-54000 �ϵ�LED.
 */ 
void am_led_init (const am_led_info_t *p_led_info, const uint32_t led_num)
{
    int i;
    
    if (p_led_info != NULL && led_num != 0) {
        __pg_led_info = (am_led_info_t *)p_led_info;
        __g_led_num   = (uint32_t)led_num;
    }
    
    for (i = 0; i < led_num; i++) {
        
        am_gpio_pin_cfg(p_led_info[i].pin, AM_GPIO_OUTPUT);
        
        /* Ϩ��LED */
        am_gpio_set(p_led_info[i].pin, 
                    (int)p_led_info[i].active_low);
    }
}

/**
 * \brief  ����LED״̬��
 */
void am_led_set (uint8_t led_id, bool_t state)
{
    if (led_id < __g_led_num) {
        state = (bool_t)(state ^ (__pg_led_info[led_id].active_low));
        
        am_gpio_set(__pg_led_info[led_id].pin, (int)state);
    }
}

/**
 * \brief ����LED��
 */
void am_led_on (uint8_t led_id)
{
    if (led_id < __g_led_num) {
        
        if (__pg_led_info[led_id].active_low == TRUE) {
            am_gpio_set(__pg_led_info[led_id].pin, (int)FALSE);
        } else {
            am_gpio_set(__pg_led_info[led_id].pin, (int)TRUE);
        }
    }   
}

/**
 * \brief Ϩ��LED��
 */
void am_led_off (uint8_t led_id)
{
    if (led_id < __g_led_num) {
        if (__pg_led_info[led_id].active_low == TRUE) {
            am_gpio_set(__pg_led_info[led_id].pin, (int)TRUE); 
        } else {
             am_gpio_set(__pg_led_info[led_id].pin, (int)FALSE);
        }
    }    
}

/**
 * \brief ��ȡָ��LED��״̬��
 */
bool_t am_led_get (uint8_t led_id)
{
    bool_t state;
    
    if (led_id < __g_led_num) {
        state = (bool_t)__pg_led_info[led_id].active_low;
        
        state ^= (bool_t)am_gpio_get(__pg_led_info[led_id].pin);
       
        return state;
    }

    return FALSE;
}

/**
 * \brief ��תָ��LED��״̬��
 */
void am_led_toggle (uint8_t led_id)
{
    if (led_id < __g_led_num) {
        am_gpio_toggle(__pg_led_info[led_id].pin);
    }
}

/* end of file */

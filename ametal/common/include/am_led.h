/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief  LED��׼�ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.01 14-12-01  tee, add the LED to the standard interface
 * - 1.00 14-11-25  fft, first implementation.
 * \endinternal
 */

#ifndef __AM_LED_H
#define __AM_LED_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"


/**
 * \addtogroup am_if_led
 * \copydoc am_led.h
 * @{
 */


/**
 * \brief LED��Ϣ
 */
typedef struct am_led_info {
    uint32_t pin;          /**< \brief LEDռ�õ�GPIO����     */
    bool_t   active_low;   /**< \brief LED��ʱ�����Ƿ�͵�ƽ */
} am_led_info_t;

/**
 * \brief LED��ʼ��
 * \param[in] p_led_info : ָ��LED��Ϣ��ָ��
 * \param[in] led_num    : LED����
 * \return ��
 */
void am_led_init(const am_led_info_t *p_led_info, const uint32_t led_num);
    
/**
 * \brief ���ð弶LED��״̬
 *
 * \param[in] led_id : LED��ID
 * \param[in] state  : TRUE : LED��
 *                     FALSE: LED��
 *
 * \return ��
 */
void am_led_set(uint8_t led_id, bool_t state);

/**
 * \brief ����LED
 * \param[in] led_id : LED��ID
 * \return ��
 */
void am_led_on(uint8_t led_id);

/**
 * \brief Ϩ��LED
 * \param[in] led_id : LED��ID
 * \return ��
 */
void am_led_off(uint8_t led_id);

/**
 * \brief ��ȡָ��LED��״̬
 * \param[in] led_id : LED��ID
 * 
 * \retval TRUE  : LED��
 * \retval FALSE : LED��
 */
bool_t am_led_get(uint8_t led_id);

/**
 * \brief ��תָ��LED��״̬
 * \param[in] led_id : LED��ID
 * \return ��
 */
void am_led_toggle(uint8_t led_id);


/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_LED_H */

/* end of file */

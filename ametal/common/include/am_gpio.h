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
 * \brief GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-01  hbt, first implementation.
 * \endinternal
 */

#ifndef __AM_GPIO_H
#define __AM_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 
#include "am_gpio_util.h"

/**
 * \addtogroup am_if_gpio
 * \copydoc am_gpio.h
 * @{
 */

/**
 * \name GPIO ���Ź���
 * \anchor grp_am_gpio_pin_function
 * @{
 */

/** \brief GPIO �������� */
#define AM_GPIO_INPUT                AM_GPIO_COM_FUNC_CODE(AM_GPIO_INPUT_VAL)

/** \brief GPIO ������� */
#define AM_GPIO_OUTPUT               AM_GPIO_COM_FUNC_CODE(AM_GPIO_OUTPUT_VAL)

/** \brief GPIO ��������ߵ�ƽ */
#define AM_GPIO_OUTPUT_INIT_HIGH     AM_GPIO_COM_FUNC_CODE(AM_GPIO_OUTPUT_INIT_HIGH_VAL)

/** \brief GPIO ��������͵�ƽ */
#define AM_GPIO_OUTPUT_INIT_LOW      AM_GPIO_COM_FUNC_CODE(AM_GPIO_OUTPUT_INIT_LOW_VAL)

/** @} */


/**
 * \name GPIO ����ģʽ
 * \anchor grp_am_gpio_pin_mode
 * @{
 */

/** \brief ����ģʽ */
#define AM_GPIO_PULLUP               AM_GPIO_COM_MODE_CODE(AM_GPIO_PULL_UP_VAL)

/** \brief ����ģʽ */
#define AM_GPIO_PULLDOWN             AM_GPIO_COM_MODE_CODE(AM_GPIO_PULL_DOWN_VAL)

/** \brief ����ģʽ */
#define AM_GPIO_FLOAT                AM_GPIO_COM_MODE_CODE(AM_GPIO_FLOAT_VAL)

/** \brief ��©ģʽ */
#define AM_GPIO_OPEN_DRAIN           AM_GPIO_COM_MODE_CODE(AM_GPIO_OPEN_DRAIN_VAL)

/** \brief ����ģʽ */
#define AM_GPIO_PUSH_PULL            AM_GPIO_COM_MODE_CODE(AM_GPIO_PUSH_PULL_VAL)

/** @} */


/**
 * \name GPIO ���Ŵ�������
 * \anchor grp_am_gpio_pin_trigger_function
 * @{
 */

/** \brief �رմ��� */
#define AM_GPIO_TRIGGER_OFF          0

/** \brief �ߵ�ƽ���� */
#define AM_GPIO_TRIGGER_HIGH         1

/** \brief �͵�ƽ���� */
#define AM_GPIO_TRIGGER_LOW          2

/** \brief �����ش��� */
#define AM_GPIO_TRIGGER_RISE         3

/** \brief �½��ش��� */
#define AM_GPIO_TRIGGER_FALL         4

/** \brief ˫���ش��� */
#define AM_GPIO_TRIGGER_BOTH_EDGES   5

/** @} */

/**
 * \name GPIO ���ŵ�ƽ
 * \anchor grp_am_gpio_pin_level
 * @{
 */
 
/** \brief �͵�ƽ */
#define AM_GPIO_LEVEL_LOW            0

/** \brief �ߵ�ƽ */
#define AM_GPIO_LEVEL_HIGH           1

/** @} */


/**
 * \brief ����GPIO���Ź���
 *
 * ͨ������ \a flags �������Ź��� \a flags �ĸ�ʽΪ:
 * (���� | ģʽ | ƽ̨), 
 * - ���ܣ�
 *   - \ref grp_am_gpio_pin_function
 * - ģʽ��
 *   - \ref grp_am_gpio_pin_mode
 * - ƽ̨��
 *   - xxx_pin.h 
 *
 * ����������ŵĹ��ܺ�ģʽ��ƽ̨�����ó�ͻ���������ģʽ������ȼ���ߣ���
 * ����ƽ̨��������á�
 * 
 * \param[in] pin      : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_am_gpio_pin_function ��
 *                       \ref grp_am_gpio_pin_mode �� xxx_pin.h
 * 
 * \retval  AM_OK      : ���óɹ�
 * \retval -AM_ENOTSUP : ��֧�ָù���
 */
int am_gpio_pin_cfg(int pin, uint32_t flags);

/**
 * \brief ��ȡGPIO����״̬
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \return          ����״̬
 */
int am_gpio_get(int pin);

/**
 * \brief �����������״̬
 *
 * \param[in] pin   : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] value : ����״̬���μ�
 *                    \ref grp_am_gpio_pin_level
 *
 * \retval  AM_OK   : �����ɹ�
 */
int am_gpio_set(int pin, int value);

/**
 * \brief ��תGPIO�������״̬
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_toggle(int pin);

/**
 * \brief ����GPIO���Ŵ�������
 * 
 * \param[in] pin  : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] flag : ���ò������μ�
 *                   \ref grp_am_gpio_pin_trigger_function
 * 
 * \retval AM_OK   : ���óɹ�
 */
int am_gpio_trigger_cfg(int pin, uint32_t flag);

/**
 * \brief ���ӻص�����������
 *
 * \param[in] pin          : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص���������ڲ���
 *
 * \retval  AM_OK          : �����ɹ�
 */
int am_gpio_trigger_connect(int           pin,
                            am_pfnvoid_t  pfn_callback,
                            void         *p_arg);

/**
 * \brief ɾ�����ӵ����ŵĻص�����
 *
 * \param[in] pin          : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] pfn_callback : �ص�����ָ��
 * \param[in] p_arg        : �ص���������ڲ���
 *
 * \retval  AM_OK          : �����ɹ�
 */
int am_gpio_trigger_disconnect(int           pin,
                               am_pfnvoid_t  pfn_callback,
                               void         *p_arg);

/**
 * \brief ʹ�����Ŵ����ж�
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_trigger_on(int pin);

/**
 * \brief �������Ŵ����ж�
 * \param[in] pin : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \retval  AM_OK : �����ɹ�
 */
int am_gpio_trigger_off(int pin);


/** 
 * @}  
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_GPIO_H */

/* end of file */

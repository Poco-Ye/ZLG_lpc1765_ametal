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
 * \brief GPIO Ӳ�������ӿ�
 * 
 * 1. GPIO �����ܹ�ͨ���������Ϊ���������
 * 2. ����GPIO ����Ĭ��Ϊ���룬�ڸ�λʱ�жϽ��ܣ�
 * 3. ���żĴ����������ŵ������û���ͬʱ���á�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-24  hbt, first implementation.
 * \endinternal
 */

#ifndef __AMHW_GPIO_H
#define __AMHW_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 

/** 
 * \addtogroup amhw_if_gpio 
 * \copydoc amhw_gpio.h
 * @{
 */

/** 
 * \name GPIO �˿ڱ��
 * @{
 */

#define AMHW_GPIO_PORT_0        0        /**< \brief �˿� 0  */ 
#define AMHW_GPIO_PORT_1        1        /**< \brief �˿� 1  */

/** @} */

/**
 * \name GPIO ���ŵ�ƽ
 * @{
 */
 
#define AMHW_GPIO_LEVEL_LOW     0        /**< \brief �͵�ƽ */
#define AMHW_GPIO_LEVEL_HIGH    1        /**< \brief �ߵ�ƽ */

/** @} */
    
/**
 * \brief GPIO �Ĵ�����ṹ��
 */
typedef struct amhw_gpio {
    __IO uint8_t  b[128][32];       /**< \brief �����ֽڼĴ���       */
    __IO uint32_t w[32][32];        /**< \brief �����ּĴ���         */
    __IO uint32_t dir[32];          /**< \brief ����Ĵ���           */
    __IO uint32_t mask[32];         /**< \brief ����Ĵ�             */
    __IO uint32_t pin[32];          /**< \brief �˿����żĴ���       */
    __IO uint32_t mpin[32];         /**< \brief �˿�����Ĵ���       */
    __IO uint32_t set[32];          /**< \brief ����Ķ�����λ�Ĵ��� */
    __O  uint32_t clr[32];          /**< \brief �˿�����Ĵ���       */
    __O  uint32_t toggle[32];       /**< \brief �˿ڷ�ת�Ĵ���       */
} amhw_gpio_t;


/**
 * \brief ����GPIO���ŷ���Ϊ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return    ��
 */
am_static_inline 
void amhw_gpio_pin_dir_output (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->dir[pin >> 5] |= (1UL << (pin & 0x1F));
}

/**
 * \brief ����GPIO���ŷ���Ϊ����
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return    ��
 */
am_static_inline 
void amhw_gpio_pin_dir_input (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->dir[pin >> 5] &= ~(1UL << (pin & 0x1F));
}

/**
 * \brief ��ȡָ�����ŵķ���
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \retval  0  : ����
 * \retval  1  : ���
 */
am_static_inline
int amhw_gpio_pin_dir_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return (((p_hw_gpio->dir[pin >> 5] & 
             (1UL << (pin & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief ����GPIO�˿ڵ�����ֵ�����ڶ˿ڵĶ���д
 *
 *  ��ֵӰ��Զ˿ڵĶ���д.д0ʱ��ʹ�ܶ���д��д1ʱ����ֹд���λ����ʱʼ��Ϊ0.
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port      : �˿ڱ�ţ�ֵΪ AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 * \param[in] value     : ����ֵ�������ڶ���д
 * 
 * \return    ��
 */
am_static_inline 
void amhw_gpio_mask_set (amhw_gpio_t *p_hw_gpio, 
                         int          port, 
                         uint32_t     value)
{
    p_hw_gpio->mask[port] = value;
}

/**
 * \brief ��ȡGPIOָ���˿ڵ�����ֵ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port      : �˿ڱ�ţ�ֵΪ AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return    �˿ڵ�����ֵ
 */
am_static_inline 
uint32_t amhw_gpio_mask_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->mask[port];
}

/**
 * \brief ��ȡ���ŵĵ�ƽ״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \retval  0  : �͵�ƽ
 * \retval  1  : �ߵ�ƽ
 */
am_static_inline 
int amhw_gpio_pin_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return (((p_hw_gpio->pin[pin >> 5] & 
             (1UL << (pin & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief ����ָ���˿ڵ�����GPIO���ŵ�״̬���������޹أ�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port      : �˿ڱ�ţ�ֵΪ AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 * \param[in] value     : GPIO����״̬
 *
 * \return    ��
 */
am_static_inline 
void amhw_gpio_port_set (amhw_gpio_t *p_hw_gpio, int port, uint32_t value)
{
    p_hw_gpio->pin[port] = value;
}

/**
 * \brief ��ȡָ���˿ڵ�����GPIO���ŵ�״̬���������޹أ�
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port      : �˿ڱ�ţ�ֵΪ AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return   �˿ڵ�����״̬
 */
am_static_inline 
uint32_t amhw_gpio_port_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->pin[port];
}

/**
 * \brief ͨ�� MASKP0 �Ĵ�������������GPIO�˿ڵ�����״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port      : �˿ڱ�ţ�ֵΪ AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) ��
 * \param[in] value     : ����GPIO�˿����ŵ�״̬
 *
 * \return    ��
 *
 * \note ���ĳһλ��Ӧ��MASK�Ĵ���ֵΪ1�������Ϊ������Ӱ��
 */
am_static_inline 
void amhw_gpio_port_masked_set (amhw_gpio_t *p_hw_gpio, 
                                int          port, 
                                uint32_t     value)
{
    p_hw_gpio->mpin[port] = value;
}

/**
 * \brief ͨ�� MASKP0 �Ĵ����������ȡGPIO�˿ڵ�����״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] port      : �˿ڱ�ţ�ֵΪ AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return������GPIO�˿�����״̬
 */
am_static_inline 
uint32_t amhw_gpio_port_masked_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->mpin[port];
}

/**
 * \brief ����GPIO��������ߵ�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return    ��.
 *
 * \note �ù��ܽ�����������Ϊ���������
 */
am_static_inline 
void amhw_gpio_pin_out_high (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->set[pin >> 5] = (1UL << (pin & 0x1F));
}

/**
 * \brief ����GPIO��������͵�ƽ
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return    ��
 *
 * \note �ù��ܽ�����������Ϊ���������
 */
am_static_inline 
void amhw_gpio_pin_out_low (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->clr[pin >> 5] = (1UL << (pin & 0x1F));
}

/**
 * \brief ��תGPIO������ŵĵ�ƽ״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return ��
 *
 * \note �ù��ܽ�����������Ϊ���������
 */
am_static_inline 
void amhw_gpio_pin_toggle (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->toggle[pin >> 5] = (1UL << (pin & 0x1F));
}

/**
 * \briefͨ���ֽ�����GPIO������״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] byte      : 0Ϊ�ͣ�1Ϊ��
 *
 * \return    ��
 */         
am_static_inline 
void amhw_gpio_pin_byte_set (amhw_gpio_t *p_hw_gpio, int pin, uint8_t byte)
{
    p_hw_gpio->b[pin >> 5][(pin & 0x1F)] = byte;
}

/**
 * \brief ��ȡһ���ֽڱ�ʾ��GPIO����״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return    ���ֽڱ�ʾ������״̬
 *
 * \note ����ǰ��������Ϊģ������ʱ��������ֵʼ��Ϊ0
 */
am_static_inline 
uint8_t amhw_gpio_pin_byte_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return p_hw_gpio->b[pin >> 5][(pin & 0x1F)];
}

/**
 * \brief ͨ��������GPIO������״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 * \param[in] word      : 0Ϊ�͵�ƽ�������Ϊ�ߵ�ƽ
 *
 * \return    ��
 */        
am_static_inline 
void amhw_gpio_pin_word_set (amhw_gpio_t *p_hw_gpio, int pin, uint32_t word)
{
    p_hw_gpio->w[pin >> 5][(pin & 0x1F)] = word;
}

/**
 * \brief ��ȡһ���ֱ�ʾ��GPIO����״̬
 *
 * \param[in] p_hw_gpio : ָ��GPIO�Ĵ������ָ��
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return    ���ֱ�ʾ������״̬
 */
am_static_inline 
uint32_t amhw_gpio_pin_word_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return p_hw_gpio->w[pin >> 5][(pin & 0x1F)];
}


/**
 * @} amhw_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_GPIO_H */

/* end of file */

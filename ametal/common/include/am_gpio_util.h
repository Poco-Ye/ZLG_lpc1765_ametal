/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief GPIO��׼�ӿڵĸ������ߺ�
 *
 * ���ļ�ֻ�� \sa am_gpio.h ���������Ҳ��ܱ��޸� ���ļ�����������ͨ�õĹ��ܺ�
 * ģʽ��
 *
 * \internal
 * \par Modification History
 * - 1.00 15-02-03  hbt, first implementation.
 * \endinternal
 */

#ifndef __AM_GPIO_UTIL_H
#define __AM_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 

/**
 * \addtogroup am_if_gpio_util
 * \copydoc am_gpio_util.h
 * @{
 */

/**
 * \name bit[2:0] ͨ�ù�����λ��
 * @{
 */

#define AM_GPIO_FUNCBITS_START          0       /**< \brief ��������ʼλ   */
#define AM_GPIO_FUNCBITS_LEN            3       /**< \brief �����볤��     */

#define AM_GPIO_FUNC_INVALID_VAL        0x0     /**< \brief ��Ч����       */
#define AM_GPIO_INPUT_VAL               0x1     /**< \brief ���빦��       */
#define AM_GPIO_OUTPUT_VAL              0x2     /**< \brief �������       */
#define AM_GPIO_OUTPUT_INIT_HIGH_VAL    0x3     /**< \brief ��ʼ��Ϊ�ߵ�ƽ */
#define AM_GPIO_OUTPUT_INIT_LOW_VAL     0x4     /**< \brief ��ʼ��Ϊ�͵�ƽ */
 
/** \brief �ù����� */
#define AM_GPIO_COM_FUNC_CODE(value)    AM_SBF((value), AM_GPIO_FUNCBITS_START)

/** \brief ��ȡ������ */
#define AM_GPIO_COM_FUNC_GET(data)      AM_BITS_GET((data), AM_GPIO_FUNCBITS_START, \
                                                     AM_GPIO_FUNCBITS_LEN)

/** \brief ��Ч���� */
#define AM_GPIO_COM_FUNC_INVALID        AM_GPIO_COM_FUNC_CODE(AM_GPIO_FUNC_INVALID_VAL)

/** @} */

/** 
 * \name bit[5:3] ͨ��ģʽ��λ��
 * @{
 */

#define AM_GPIO_MODEBITS_START          3       /**< \brief ģʽ����ʼλ */
#define AM_GPIO_MODEBITS_LEN            3       /**< \brief ģʽ�볤��   */

#define AM_GPIO_MODE_INVALID_VAL        0x0     /**< \brief ��Чģʽ     */
#define AM_GPIO_PULL_UP_VAL             0x1     /**< \brief ����ģʽ     */
#define AM_GPIO_PULL_DOWN_VAL           0x2     /**< \brief ����ģʽ     */
#define AM_GPIO_FLOAT_VAL               0x3     /**< \brief ����ģʽ     */
#define AM_GPIO_OPEN_DRAIN_VAL          0x4     /**< \brief ��©ģʽ     */
#define AM_GPIO_PUSH_PULL_VAL           0x5     /**< \brief ����ģʽ     */

/** \brief ��ģʽ�� */
#define AM_GPIO_COM_MODE_CODE(value)    AM_SBF((value), AM_GPIO_MODEBITS_START)

/** \brief ��ȡģʽ�� */
#define AM_GPIO_COM_MODE_GET(data)      AM_BITS_GET((data), AM_GPIO_MODEBITS_START, \
                                                    AM_GPIO_MODEBITS_LEN)

/** \brief ��Чģʽ */
#define AM_GPIO_COM_MODE_INVALID        AM_GPIO_COM_MODE_CODE(AM_GPIO_MODE_INVALID_VAL)

/** @} */


/**
 * \name ƽ̨����
 *
 * bit[11:6] ����
 * bit[31:12] ����ƽ̨����
 *
 * @{
 */

#define AM_GPIO_PLFM_BITS_START          12     /**< \brief ƽ̨������ʼλ */
#define AM_GPIO_PLFM_BITS_LEN            20     /**< \brief ƽ̨���峤��   */

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AM_GPIO_UTIL_H */

/* end of file */

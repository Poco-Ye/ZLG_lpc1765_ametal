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
 * \brief LPC5410x GPIO �������ò�������
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-01-06  hbt, first implementation.
 * \endinternal
 */

#ifndef __LPC5410X_PIN_H
#define __LPC5410X_PIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "amdr_gpio_util.h"

 /** 
 * \addtogroup amhw_if_pin
 * \copydoc lpc5410x_pin.h
 * @{
 */


/** 
 * \name LPC5410x GPIO ���ű��
 * @{
 */

#define PIO0_0          0        /**< \brief PIO0_0���ź�  */
#define PIO0_1          1        /**< \brief PIO0_1���ź�  */
#define PIO0_2          2        /**< \brief PIO0_2���ź�  */
#define PIO0_3          3        /**< \brief PIO0_3���ź�  */
#define PIO0_4          4        /**< \brief PIO0_4���ź�  */
#define PIO0_5          5        /**< \brief PIO0_5���ź�  */
#define PIO0_6          6        /**< \brief PIO0_6���ź�  */
#define PIO0_7          7        /**< \brief PIO0_7���ź�  */
#define PIO0_8          8        /**< \brief PIO0_8���ź�  */
#define PIO0_9          9        /**< \brief PIO0_9���ź�  */
#define PIO0_10         10       /**< \brief PIO0_10���ź� */
#define PIO0_11         11       /**< \brief PIO0_11���ź� */
#define PIO0_12         12       /**< \brief PIO0_12���ź� */
#define PIO0_13         13       /**< \brief PIO0_13���ź� */
#define PIO0_14         14       /**< \brief PIO0_14���ź� */
#define PIO0_15         15       /**< \brief PIO0_15���ź� */
#define PIO0_16         16       /**< \brief PIO0_16���ź� */
#define PIO0_17         17       /**< \brief PIO0_17���ź� */
#define PIO0_18         18       /**< \brief PIO0_18���ź� */
#define PIO0_19         19       /**< \brief PIO0_19���ź� */
#define PIO0_20         20       /**< \brief PIO0_20���ź� */
#define PIO0_21         21       /**< \brief PIO0_21���ź� */
#define PIO0_22         22       /**< \brief PIO0_22���ź� */
#define PIO0_23         23       /**< \brief PIO0_23���ź� */
#define PIO0_24         24       /**< \brief PIO0_24���ź� */
#define PIO0_25         25       /**< \brief PIO0_25���ź� */
#define PIO0_26         26       /**< \brief PIO0_26���ź� */
#define PIO0_27         27       /**< \brief PIO0_27���ź� */
#define PIO0_28         28       /**< \brief PIO0_28���ź� */
#define PIO0_29         29       /**< \brief PIO0_29���ź� */
#define PIO0_30         30       /**< \brief PIO0_30���ź� */
#define PIO0_31         31       /**< \brief PIO0_31���ź� */

#define PIO1_0          32       /**< \brief PIO1_0���ź�  */
#define PIO1_1          33       /**< \brief PIO1_1���ź�  */
#define PIO1_2          34       /**< \brief PIO1_2���ź�  */
#define PIO1_3          35       /**< \brief PIO1_3���ź�  */
#define PIO1_4          36       /**< \brief PIO1_4���ź�  */
#define PIO1_5          37       /**< \brief PIO1_5���ź�  */
#define PIO1_6          38       /**< \brief PIO1_6���ź�  */
#define PIO1_7          39       /**< \brief PIO1_7���ź�  */
#define PIO1_8          40       /**< \brief PIO1_8���ź�  */
#define PIO1_9          41       /**< \brief PIO1_9���ź�  */
#define PIO1_10         42       /**< \brief PIO1_10���ź� */
#define PIO1_11         43       /**< \brief PIO1_11���ź� */
#define PIO1_12         44       /**< \brief PIO1_12���ź� */
#define PIO1_13         45       /**< \brief PIO1_13���ź� */
#define PIO1_14         46       /**< \brief PIO1_14���ź� */
#define PIO1_15         47       /**< \brief PIO1_15���ź� */
#define PIO1_16         48       /**< \brief PIO1_16���ź� */
#define PIO1_17         49       /**< \brief PIO1_17���ź� */

/** @} */


#ifdef AM_CORTEX_M4

/** 
 * \brief ʹ��Cortex-M4�ں�ʱ��֧����������ж�����8��
 * ʹ��Cortex-M0+�ں�ʱ��֧����������ж�����4.
*/
#define PIN_INT_MAX     8  
#endif

#ifdef AM_CORTEX_M0

/** 
 * \brief ʹ��Cortex-M4�ں�ʱ��֧����������ж�����8��
 * ʹ��Cortex-M0+�ں�ʱ��֧����������ж�����4.
*/
#define PIN_INT_MAX     4  
#endif


/**
 * \name GPIO ����ģʽ
 *       ��Ϊ���� am_gpio_pin_cfg() �ĵڶ������������磺
 *       am_gpio_pin_cfg(PIO0_4, AMDR_GPIO_OUPUT)
 * @{
 */
 
/** \brief ����ģʽ(������/����) */
#define AMDR_GPIO_INACTIVE     AMDR_GPIO_MODE_CODE(0x0)

/** \brief ����ģʽ */
#define AMDR_GPIO_PULLDOWN     AMDR_GPIO_MODE_CODE(0x1)

/** \brief ����ģʽ */
#define AMDR_GPIO_PULLUP       AMDR_GPIO_MODE_CODE(0x2)

/** \brief �м�ģʽ */
#define AMDR_GPIO_REPEATER     AMDR_GPIO_MODE_CODE(0x3)

/** @} */

/******************************************************************************/

/**
 * \name PIO0_0���Ź���
 * @{
 */

#define PIO0_0_GPIO            AMDR_GPIO_FUNC_CODE(0x0)    /**< \brief GPIO          */
#define PIO0_0_INPUT           AMDR_GPIO_DIR_CODE(0x0)     /**< \brief ����           */
#define PIO0_0_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)     /**< \brief ���           */
#define PIO0_0_USART0_RXD      AMDR_GPIO_FUNC_CODE(0x1)    /**< \brief USART0_RXD     */
#define PIO0_0_SPI0_SSELN0     AMDR_GPIO_FUNC_CODE(0x2)    /**< \brief SPI0_SSELN0    */
#define PIO0_0_CT0_CAP0        AMDR_GPIO_FUNC_CODE(0x3)    /**< \brief CT0_CAP0       */
#define PIO0_0_SCT0_OUT3       AMDR_GPIO_FUNC_CODE(0x5)    /**< \brief SCT0_OUT3      */

/** @} */

/**
 * \name PIO0_0����ģʽ
 * @{
 */

#define PIO0_0_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)    /**< \brief ����ģʽ(������/����) */
#define PIO0_0_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)    /**< \brief ����ģʽ              */
#define PIO0_0_PULLUP          AMDR_GPIO_MODE_CODE(0x2)    /**< \brief ����ģʽ              */
#define PIO0_0_REPEATER        AMDR_GPIO_MODE_CODE(0x3)    /**< \brief �м�ģʽ              */
                                                                                      
/** @} */

/**
 * \name PIO0_0 ���뼫��
 * @{
 */
#define PIO0_0_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_0_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_0 ��������˲�
 * @{
 */
#define PIO0_0_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_0_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_0 ������ת����
 * @{
 */
#define PIO0_0_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_0_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_0 ��©ģʽ
 * @{
 */
#define PIO0_0_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_0_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_1���Ź���
 * @{
 */

#define PIO0_1_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO            */
#define PIO0_1_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����            */
#define PIO0_1_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���            */
#define PIO0_1_USART0_TXD      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART0_TXD      */
#define PIO0_1_SPI0_SSELN1     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI0_SSELN1     */
#define PIO0_1_CT0_CAP1        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_CAP1        */
#define PIO0_1_SCT0_OUT1       AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief SCT0_OUT1       */

/** @} */

/**
 * \name PIO0_1����ģʽ
 * @{
 */
 
#define PIO0_1_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_1_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_1_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_1_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_1 ���뼫��
 * @{
 */
#define PIO0_1_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_1_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_1 ��������˲�
 * @{
 */
#define PIO0_1_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_1_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_1 ������ת����
 * @{
 */
#define PIO0_1_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_1_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_1 ��©ģʽ
 * @{
 */
#define PIO0_1_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_1_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_2���Ź���
 * @{
 */

#define PIO0_2_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO     */
#define PIO0_2_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����     */
#define PIO0_2_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���     */
#define PIO0_2_CTS             AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief CTS      */
#define PIO0_2_CT2_CAP1        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_CAP1 */
/** @} */

/**
 * \name PIO0_2����ģʽ
 * @{
 */
 
#define PIO0_2_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_2_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_2_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_2_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_2 ���뼫��
 * @{
 */
#define PIO0_2_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_2_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_2 ��������˲�
 * @{
 */
#define PIO0_2_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_2_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_2 ������ת����
 * @{
 */
#define PIO0_2_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_2_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_2 ��©ģʽ
 * @{
 */
#define PIO0_2_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_2_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_3���Ź���
 * @{
 */

#define PIO0_3_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_3_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_3_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_3_USART0_RTS      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USQRT0_RTS */
#define PIO0_3_CT1_MAT3        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT1_MAT3   */

/** @} */

/**
 * \name PIO0_3����ģʽ
 * @{
 */
 
#define PIO0_3_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_3_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_3_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_3_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_3 ���뼫��
 * @{
 */
#define PIO0_3_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_3_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_3 ��������˲�
 * @{
 */
#define PIO0_3_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_3_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_3 ������ת����
 * @{
 */
#define PIO0_3_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_3_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_3 ��©ģʽ
 * @{
 */
#define PIO0_3_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_3_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_4���Ź���
 * @{
 */

#define PIO0_4_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_4_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_4_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_4_USART0_SCLK     AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART0_SCLK */
#define PIO0_4_SPI0_SSELN2     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI0_SSELN2 */
#define PIO0_4_CT0_CAP2        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_CAP2    */

/** @} */


/**
 * \name PIO0_4����ģʽ
 * @{
 */
 
#define PIO0_4_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_4_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_4_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_4_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_4 ���뼫��
 * @{
 */
#define PIO0_4_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_4_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_4 ��������˲�
 * @{
 */
#define PIO0_4_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_4_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_4 ������ת����
 * @{
 */
#define PIO0_4_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_4_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_4 ��©ģʽ
 * @{
 */
#define PIO0_4_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_4_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_5���Ź���
 * @{
 */

#define PIO0_5_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_5_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_5_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_5_USART1_RXD      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART1_RXD */
#define PIO0_5_SCT0_OUT6       AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT6  */
#define PIO0_5_CT0_MAT0        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT0   */

/** @} */

/**
 * \name PIO0_5����ģʽ
 * @{
 */
 
#define PIO0_5_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_5_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_5_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_5_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_5 ���뼫��
 * @{
 */
#define PIO0_5_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_5_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_5 ��������˲�
 * @{
 */
#define PIO0_5_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_5_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_5 ������ת����
 * @{
 */
#define PIO0_5_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_5_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_5 ��©ģʽ
 * @{
 */
#define PIO0_5_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_5_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_6���Ź���
 * @{
 */

#define PIO0_6_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_6_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_6_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_6_USART1_TXD      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART1_TXD */
#define PIO0_6_CT0_MAT1        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT1   */
                               
/** @} */

/**
 * \name PIO0_6����ģʽ
 * @{
 */
 
#define PIO0_6_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_6_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_6_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_6_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_6 ���뼫��
 * @{
 */
#define PIO0_6_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_6_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_6 ��������˲�
 * @{
 */
#define PIO0_6_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_6_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_6 ������ת����
 * @{
 */
#define PIO0_6_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_6_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_6 ��©ģʽ
 * @{
 */
#define PIO0_6_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_6_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_7���Ź���
 * @{
 */

#define PIO0_7_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_7_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_7_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_7_USART1_SCLK     AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART1_SCLK */
#define PIO0_7_SCT0_OUT0       AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT0   */
#define PIO0_7_CT0_MAT2        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT2    */
#define PIO0_7_CT0_CAP2        AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT0_CAP2    */

/** @} */

/**
 * \name PIO0_7����ģʽ
 * @{
 */
 
#define PIO0_7_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_7_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_7_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_7_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_7 ���뼫��
 * @{
 */
#define PIO0_7_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_7_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_7 ��������˲�
 * @{
 */
#define PIO0_7_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_7_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_7 ������ת����
 * @{
 */
#define PIO0_7_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_7_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_7 ��©ģʽ
 * @{
 */
#define PIO0_7_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_7_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_8���Ź���
 * @{
 */

#define PIO0_8_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_8_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_8_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_8_USART2_RXD      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART2_RXD */
#define PIO0_8_SCT0_OUT1       AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT1  */
#define PIO0_8_CT0_MAT3        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT3   */

/** @} */

/**
 * \name PIO0_8����ģʽ
 * @{
 */
 
#define PIO0_8_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_8_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_8_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_8_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_8 ���뼫��
 * @{
 */
#define PIO0_8_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_8_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_8 ��������˲�
 * @{
 */
#define PIO0_8_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_8_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_8 ������ת����
 * @{
 */
#define PIO0_8_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_8_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_8 ��©ģʽ
 * @{
 */
#define PIO0_8_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_8_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_9���Ź���
 * @{
 */

#define PIO0_9_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_9_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_9_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_9_USART2_TXD      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART2_TXD  */
#define PIO0_9_SCT0_OUT2       AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT2   */
#define PIO0_9_CT3_CAP0        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_CAP0    */
#define PIO0_9_SPI0_SSELN0     AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief SPI0_SSELN0 */

/** @} */

/**
 * \name PIO0_9����ģʽ
 * @{
 */
 
#define PIO0_9_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO0_9_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO0_9_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO0_9_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_9 ���뼫��
 * @{
 */
#define PIO0_9_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_9_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_9 ��������˲�
 * @{
 */
#define PIO0_9_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_9_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_9 ������ת����
 * @{
 */
#define PIO0_9_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO0_9_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_9 ��©ģʽ
 * @{
 */
#define PIO0_9_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO0_9_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_10���Ź���
 * @{
 */

#define PIO0_10_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_10_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_10_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_10_USART2_SCLK    AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART2_SCLK */
#define PIO0_10_SCT0_OUT3      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT3   */
#define PIO0_10_CT3_MAT0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_MAT0    */

/** @} */

/**
 * \name PIO0_10����ģʽ
 * @{
 */
 
#define PIO0_10_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_10_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_10_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_10_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_10 ���뼫��
 * @{
 */
#define PIO0_10_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_10_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_10 ��������˲�
 * @{
 */
#define PIO0_10_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_10_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_10 ������ת����
 * @{
 */
#define PIO0_10_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_10_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_10 ��©ģʽ
 * @{
 */
#define PIO0_10_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_10_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_11���Ź���
 * @{
 */

#define PIO0_11_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_11_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_11_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_11_SPI0_SCK       AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief SPI0_SCK   */
#define PIO0_11_USART1_RXD     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART1_RXD */
#define PIO0_11_CT2_MAT1       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_MAT1   */

/** @} */

/**
 * \name PIO0_11����ģʽ
 * @{
 */
 
#define PIO0_11_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_11_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_11_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_11_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_11 ���뼫��
 * @{
 */
#define PIO0_11_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_11_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_11 ��������˲�
 * @{
 */
#define PIO0_11_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_11_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_11 ������ת����
 * @{
 */
#define PIO0_11_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_11_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_11 ��©ģʽ
 * @{
 */
#define PIO0_11_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_11_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_12���Ź���
 * @{
 */

#define PIO0_12_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_12_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_12_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_12_SPI0_MOSI      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief SPI0_MOSI  */
#define PIO0_12_USART1_TXD     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART1_TXD */
#define PIO0_12_CT2_MAT3       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_MAT3   */

/** @} */

/**
 * \name PIO0_12����ģʽ
 * @{
 */
 
#define PIO0_12_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_12_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_12_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_12_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_12 ���뼫��
 * @{
 */
#define PIO0_12_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_12_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_12 ��������˲�
 * @{
 */
#define PIO0_12_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_12_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_12 ������ת����
 * @{
 */
#define PIO0_12_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_12_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_12 ��©ģʽ
 * @{
 */
#define PIO0_12_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_12_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_13���Ź���
 * @{
 */

#define PIO0_13_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO0_13_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO0_13_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO0_13_SPI0_MISO      AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief SPI0_MISO */
#define PIO0_13_SCT0_OUT4      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT4 */
#define PIO0_13_CT2_MAT0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_MAT0  */

/** @} */

/**
 * \name PIO0_13����ģʽ
 * @{
 */
 
#define PIO0_13_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_13_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_13_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_13_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_13 ���뼫��
 * @{
 */
#define PIO0_13_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_13_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_13 ��������˲�
 * @{
 */
#define PIO0_13_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_13_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_13 ������ת����
 * @{
 */
#define PIO0_13_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_13_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_13 ��©ģʽ
 * @{
 */
#define PIO0_13_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_13_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_14���Ź���
 * @{
 */

#define PIO0_14_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_14_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_14_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_14_SPI0_SSELN0    AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief SPI0_SSELN0 */
#define PIO0_14_SCT0_OUT5      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT5   */
#define PIO0_14_CT2_MAT1       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_MAT1    */

/** @} */

/**
 * \name PIO0_14����ģʽ
 * @{
 */
 
#define PIO0_14_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_14_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_14_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_14_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_14 ���뼫��
 * @{
 */
#define PIO0_14_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_14_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_14 ��������˲�
 * @{
 */
#define PIO0_14_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_14_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_14 ������ת����
 * @{
 */
#define PIO0_14_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_14_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_14 ��©ģʽ
 * @{
 */
#define PIO0_14_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_14_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_15���Ź���
 * @{
 */

#define PIO0_15_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_15_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_15_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_15_SPI0_SSELN1    AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief SPI0_SSELN1 */
#define PIO0_15_SWO            AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SWO         */
#define PIO0_15_CT2_MAT2       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_MAT2    */

/** @} */

/**
 * \name PIO0_15����ģʽ
 * @{
 */
 
#define PIO0_15_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_15_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_15_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_15_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_15 ���뼫��
 * @{
 */
#define PIO0_15_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_15_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_15 ��������˲�
 * @{
 */
#define PIO0_15_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_15_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_15 ������ת����
 * @{
 */
#define PIO0_15_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_15_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_15 ��©ģʽ
 * @{
 */
#define PIO0_15_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_15_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_16���Ź���
 * @{
 */

#define PIO0_16_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_16_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_16_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_16_SPI0_SSELN2    AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief SPI0_SSELN2 */
#define PIO0_16_USART1_CTS     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART1_CTS  */
#define PIO0_16_CT3_MAT1       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_MAT1    */
#define PIO0_16_SWCLK_TCK      AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief SWCLK_TCK   */

/** @} */

/**
 * \name PIO0_16����ģʽ
 * @{
 */
 
#define PIO0_16_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_16_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_16_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_16_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_16 ���뼫��
 * @{
 */
#define PIO0_16_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_16_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_16 ��������˲�
 * @{
 */
#define PIO0_16_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_16_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_16 ������ת����
 * @{
 */
#define PIO0_16_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_16_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_16 ��©ģʽ
 * @{
 */
#define PIO0_16_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_16_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_17���Ź���
 * @{
 */

#define PIO0_17_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_17_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_17_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_17_SPI0_SSELN3    AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief SPI0_SSELN3 */
#define PIO0_17_USART1_RTS     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART1_RTS  */
#define PIO0_17_CT3_MAT2       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_MAT2    */
#define PIO0_17_SWDIO          AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief SWDIO       */

/** @} */

/**
 * \name PIO0_17����ģʽ
 * @{
 */
 
#define PIO0_17_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_17_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_17_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_17_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_17 ���뼫��
 * @{
 */
#define PIO0_17_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_17_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_17 ��������˲�
 * @{
 */
#define PIO0_17_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_17_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_17 ������ת����
 * @{
 */
#define PIO0_17_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_17_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_17 ��©ģʽ
 * @{
 */
#define PIO0_17_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_17_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_18���Ź���
 * @{
 */

#define PIO0_18_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_18_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_18_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_18_USART3_TXD     AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART3_TXD */
#define PIO0_18_SCT0_OUT0      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT0  */
#define PIO0_18_CT0_MAT0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT0   */

/** @} */

/**
 * \name PIO0_18����ģʽ
 * @{
 */
 
#define PIO0_18_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_18_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_18_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_18_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_18 ���뼫��
 * @{
 */
#define PIO0_18_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_18_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_18 ��������˲�
 * @{
 */
#define PIO0_18_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_18_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_18 ������ת����
 * @{
 */
#define PIO0_18_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_18_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_18 ��©ģʽ
 * @{
 */
#define PIO0_18_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_18_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_19���Ź���
 * @{
 */

#define PIO0_19_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_19_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_19_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_19_USART3_SCLK    AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART3_SCLK */
#define PIO0_19_SCT0_OUT1      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT1   */
#define PIO0_19_CT0_MAT1       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT1    */

/** @} */

/**
 * \name PIO0_19����ģʽ
 * @{
 */
 
#define PIO0_19_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_19_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_19_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_19_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_19 ���뼫��
 * @{
 */
#define PIO0_19_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_19_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_19 ��������˲�
 * @{
 */
#define PIO0_19_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_19_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_19 ������ת����
 * @{
 */
#define PIO0_19_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_19_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_19 ��©ģʽ
 * @{
 */
#define PIO0_19_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_19_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_20���Ź���
 * @{
 */

#define PIO0_20_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_20_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_20_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_20_USART3_RXD     AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief USART3_RXD  */
#define PIO0_20_USART0_SCLK    AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART0_SCLK */
#define PIO0_20_CT3_CAP0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_CAP0    */

/** @} */

/**
 * \name PIO0_20����ģʽ
 * @{
 */
 
#define PIO0_20_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_20_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_20_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_20_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_20 ���뼫��
 * @{
 */
#define PIO0_20_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_20_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_20 ��������˲�
 * @{
 */
#define PIO0_20_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_20_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_20 ������ת����
 * @{
 */
#define PIO0_20_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_20_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_20 ��©ģʽ
 * @{
 */
#define PIO0_20_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_20_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_21���Ź���
 * @{
 */

#define PIO0_21_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_21_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_21_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_21_CLKOUT         AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief CLKOUT     */
#define PIO0_21_USART0_TXD     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART0_TXD */
#define PIO0_21_CT3_MAT0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_MAT0   */
/** @} */

/**
 * \name PIO0_21����ģʽ
 * @{
 */
 
#define PIO0_21_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_21_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_21_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_21_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_21 ���뼫��
 * @{
 */
#define PIO0_21_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_21_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_21 ��������˲�
 * @{
 */
#define PIO0_21_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_21_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_21 ������ת����
 * @{
 */
#define PIO0_21_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_21_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_21 ��©ģʽ
 * @{
 */
#define PIO0_21_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_21_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_22���Ź���
 * @{
 */

#define PIO0_22_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_22_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_22_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_22_CLKIN          AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief CLKIN      */
#define PIO0_22_USART0_RXD     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART0_RXD */
#define PIO0_22_CT3_MAT3       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_MAT3   */

/** @} */

/**
 * \name PIO0_22����ģʽ
 * @{
 */
 
#define PIO0_22_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_22_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_22_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_22_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_22 ���뼫��
 * @{
 */
#define PIO0_22_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_22_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_22 ��������˲�
 * @{
 */
#define PIO0_22_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_22_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_22 ������ת����
 * @{
 */
#define PIO0_22_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO0_22_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO0_22 ��©ģʽ
 * @{
 */
#define PIO0_22_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_22_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO0_23���Ź���
 * @{
 */

#define PIO0_23_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO0_23_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO0_23_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */ 
#define PIO0_23_I2C0_SCL       AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief I2C0_SCL  */
#define PIO0_23_CT0_CAP0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_CAP0  */

/** @} */

/**
 * \name PIO0_23 ����I2C���Ż�ת����
 * @{
 */
#define PIO0_23_SLEWDISABLE    AMDR_GPIO_I2CSLEWBIT_CODE(0x0)   /**< \brief I2Cģʽ   */
#define PIO0_23_SLEWENABLE     AMDR_GPIO_I2CSLEWBIT_CODE(0x1)   /**< \brief GPIOģʽ  */
/** @} */

/**
 * \name PIO0_23 ���뼫��
 * @{
 */
#define PIO0_23_INVDISABLE     AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_23_INVENABLE      AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_23 ��������˲�
 * @{
 */
#define PIO0_23_FILDISABLE     AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_23_FILENABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_23 �������ŵĵ�����������
 * @{
 */
#define PIO0_23_DRIVEDISABLE    AMDR_GPIO_I2CDRIVE_CODE(0x0)    /**< \brief ������   */
#define PIO0_23_DRIVEENABLE     AMDR_GPIO_I2CDRIVE_CODE(0x1)    /**< \brief ������   */
/** @} */

/**
 * \name PIO0_23 ����I2C�����ԣ���׼ģʽ������ģʽ�ͳ�����ģʽ��
 * @{
 */
#define PIO0_23_FILTERENABLE    AMDR_GPIO_I2CFILTER_CODE(0x0)   /**< \brief 50 ns �����˲�ʹ�� */
#define PIO0_23_FILTERDISABLE   AMDR_GPIO_I2CFILTER_CODE(0x1)   /**< \brief 50 ns �����˲����� */
/** @} */

/**
 * \name PIO0_23 ���ŵ�I2C����
 * @{
 */

#define PIO0_23_4MA_DRIVE       AMDR_PIO_4MA_DRIVE              /**< \brief GPIO 4 mA����    */
#define PIO0_23_20MA_DRIVE      AMDR_PIO_20MA_DRIVE             /**< \brief GPIO 20 mA����   */
#define PIO0_23_STD_I2C         AMDR_FAST_STD_MODE              /**< \brief I2C����/��׼ģʽ */
#define PIO0_23_MOD_PLU_IIC     AMDR_FAST_MODE_PLUS             /**< \brief I2C������ģʽ    */
#define PIO0_23_HIGH_I2C        AMDR_HIGH_SPEED_SLAVE           /**< \brief I2C���ٴӻ�ģʽ  */

/** @} */

/******************************************************************************/

/**
 * \name PIO0_24���Ź���
 * @{
 */

#define PIO0_24_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO0_24_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO0_24_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO0_24_I2C0_SDA       AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief I2C0_SDA  */
#define PIO0_24_CT0_CAP1       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_CAP1  */                         
#define PIO0_24_CT0_MAT0       AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT0_MAT0  */
/** @} */

/**
 * \name PIO0_24 ����I2C���Ż�ת����
 * @{
 */
#define PIO0_24_SLEWDISABLE    AMDR_GPIO_I2CSLEWBIT_CODE(0x0)   /**< \brief I2Cģʽ   */
#define PIO0_24_SLEWENABLE     AMDR_GPIO_I2CSLEWBIT_CODE(0x1)   /**< \brief GPIOģʽ  */
/** @} */

/**
 * \name PIO0_24 ���뼫��
 * @{
 */
#define PIO0_24_INVDISABLE     AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_24_INVENABLE      AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_24 ��������˲�
 * @{
 */
#define PIO0_24_FILDISABLE     AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_24_FILENABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_24 �������ŵĵ�����������
 * @{
 */
#define PIO0_24_DRIVEDISABLE    AMDR_GPIO_I2CDRIVE_CODE(0x0)    /**< \brief ������   */
#define PIO0_24_DRIVEENABLE     AMDR_GPIO_I2CDRIVE_CODE(0x1)    /**< \brief ������   */
/** @} */

/**
 * \name PIO0_24 ����I2C�����ԣ���׼ģʽ������ģʽ�ͳ�����ģʽ��
 * @{
 */
#define PIO0_24_FILTERENABLE    AMDR_GPIO_I2CFILTER_CODE(0x0)   /**< \brief 50 ns �����˲�ʹ�� */
#define PIO0_24_FILTERDISABLE   AMDR_GPIO_I2CFILTER_CODE(0x1)   /**< \brief 50 ns �����˲����� */
/** @} */

/**
 * \name PIO0_24 ���ŵ�I2C����
 * @{
 */

#define PIO0_24_4MA_DRIVE      AMDR_PIO_4MA_DRIVE               /**< \brief GPIO 4 mA����    */
#define PIO0_24_20MA_DRIVE     AMDR_PIO_20MA_DRIVE              /**< \brief GPIO 20 mA����   */
#define PIO0_24_STD_I2C        AMDR_FAST_STD_MODE               /**< \brief I2C����/��׼ģʽ */
#define PIO0_24_MOD_PLU_IIC    AMDR_FAST_MODE_PLUS              /**< \brief I2C������ģʽ    */
#define PIO0_24_HIGH_I2C       AMDR_HIGH_SPEED_SLAVE            /**< \brief I2C���ٴӻ�ģʽ  */

/** @} */


/******************************************************************************/

/**
 * \name PIO0_25���Ź���
 * @{
 */

#define PIO0_25_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_25_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_25_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_25_I2C1_SCL       AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief I2C1_SCL   */
#define PIO0_25_USART1_CTS     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART1_CTS */
#define PIO0_25_CT0_CAP2       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_CAP2   */ 
#define PIO0_25_CT1_CAP1       AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT1_CAP1   */

/** @} */

/**
 * \name PIO0_25 ����I2C���Ż�ת����
 * @{
 */
#define PIO0_25_SLEWDISABLE    AMDR_GPIO_I2CSLEWBIT_CODE(0x0)   /**< \brief I2Cģʽ   */
#define PIO0_25_SLEWENABLE     AMDR_GPIO_I2CSLEWBIT_CODE(0x1)   /**< \brief GPIOģʽ  */
/** @} */

/**
 * \name PIO0_25 ���뼫��
 * @{
 */
#define PIO0_25_INVDISABLE     AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_25_INVENABLE      AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_25 ��������˲�
 * @{
 */
#define PIO0_25_FILDISABLE     AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_25_FILENABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_25 �������ŵĵ�����������
 * @{
 */
#define PIO0_25_DRIVEDISABLE   AMDR_GPIO_I2CDRIVE_CODE(0x0)     /**< \brief ������   */
#define PIO0_25_DRIVEENABLE    AMDR_GPIO_I2CDRIVE_CODE(0x1)     /**< \brief ������   */
/** @} */

/**
 * \name PIO0_25 ����I2C�����ԣ���׼ģʽ������ģʽ�ͳ�����ģʽ��
 * @{
 */
#define PIO0_25_FILTERENABLE   AMDR_GPIO_I2CFILTER_CODE(0x0)    /**< \brief 50 ns �����˲�ʹ�� */
#define PIO0_25_FILTERDISABLE  AMDR_GPIO_I2CFILTER_CODE(0x1)    /**< \brief 50 ns �����˲����� */
/** @} */

/**
 * \name PIO0_25 ���ŵ�I2C����
 * @{
 */

#define PIO0_25_4MA_DRIVE      AMDR_PIO_4MA_DRIVE               /**< \brief GPIO 4 mA����    */
#define PIO0_25_20MA_DRIVE     AMDR_PIO_20MA_DRIVE              /**< \brief GPIO 20 mA����   */
#define PIO0_25_STD_I2C        AMDR_FAST_STD_MODE               /**< \brief I2C����/��׼ģʽ */
#define PIO0_25_MOD_PLU_IIC    AMDR_FAST_MODE_PLUS              /**< \brief I2C������ģʽ    */
#define PIO0_25_HIGH_I2C       AMDR_HIGH_SPEED_SLAVE            /**< \brief I2C���ٴӻ�ģʽ  */

/** @} */


/******************************************************************************/

/**
 * \name PIO0_26���Ź���
 * @{
 */
#define PIO0_26_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO0_26_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO0_26_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO0_26_I2C1_SDA       AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief I2C1_SDA  */
#define PIO0_26_CT0_CAP3       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_CAP3  */

/** @} */

/**
 * \name PIO0_26 ����I2C���Ż�ת����
 * @{
 */
#define PIO0_26_SLEWDISABLE    AMDR_GPIO_I2CSLEWBIT_CODE(0x0)   /**< \brief I2Cģʽ   */
#define PIO0_26_SLEWENABLE     AMDR_GPIO_I2CSLEWBIT_CODE(0x1)   /**< \brief GPIOģʽ  */
/** @} */

/**
 * \name PIO0_26 ���뼫��
 * @{
 */
#define PIO0_26_INVDISABLE     AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_26_INVENABLE      AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_26 ��������˲�
 * @{
 */
#define PIO0_26_FILDISABLE     AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_26_FILENABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_26 �������ŵĵ�����������
 * @{
 */
#define PIO0_26_DRIVEDISABLE   AMDR_GPIO_I2CDRIVE_CODE(0x0)     /**< \brief ������   */
#define PIO0_26_DRIVEENABLE    AMDR_GPIO_I2CDRIVE_CODE(0x1)     /**< \brief ������   */
/** @} */

/**
 * \name PIO0_26 ����I2C�����ԣ���׼ģʽ������ģʽ�ͳ�����ģʽ��
 * @{
 */
#define PIO0_26_FILTERENABLE   AMDR_GPIO_I2CFILTER_CODE(0x0)    /**< \brief 50 ns �����˲�ʹ�� */
#define PIO0_26_FILTERDISABLE  AMDR_GPIO_I2CFILTER_CODE(0x1)    /**< \brief 50 ns �����˲����� */
/** @} */

/**
 * \name PIO0_26 ���ŵ�I2C����
 * @{
 */

#define PIO0_26_4MA_DRIVE      AMDR_PIO_4MA_DRIVE               /**< \brief GPIO 4 mA����    */
#define PIO0_26_20MA_DRIVE     AMDR_PIO_20MA_DRIVE              /**< \brief GPIO 20 mA����   */
#define PIO0_26_STD_I2C        AMDR_FAST_STD_MODE               /**< \brief I2C����/��׼ģʽ */
#define PIO0_26_MOD_PLU_IIC    AMDR_FAST_MODE_PLUS              /**< \brief I2C������ģʽ    */
#define PIO0_26_HIGH_I2C       AMDR_HIGH_SPEED_SLAVE            /**< \brief I2C���ٴӻ�ģʽ  */

/** @} */


/******************************************************************************/

/**
 * \name PIO0_27���Ź���
 * @{
 */

#define PIO0_27_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO0_27_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO0_27_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO0_27_I2C2_SCL       AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief I2C2_SCL  */
#define PIO0_27_CT2_CAP0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_CAP0  */

/** @} */

/**
 * \name PIO0_27 ����I2C���Ż�ת����
 * @{
 */
#define PIO0_27_SLEWDISABLE    AMDR_GPIO_I2CSLEWBIT_CODE(0x0)   /**< \brief I2Cģʽ   */
#define PIO0_27_SLEWENABLE     AMDR_GPIO_I2CSLEWBIT_CODE(0x1)   /**< \brief GPIOģʽ  */
/** @} */

/**
 * \name PIO0_27 ���뼫��
 * @{
 */
#define PIO0_27_INVDISABLE     AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_27_INVENABLE      AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_27 ��������˲�
 * @{
 */
#define PIO0_27_FILDISABLE     AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_27_FILENABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_27 �������ŵĵ�����������
 * @{
 */
#define PIO0_27_DRIVEDISABLE   AMDR_GPIO_I2CDRIVE_CODE(0x0)     /**< \brief ������   */
#define PIO0_27_DRIVEENABLE    AMDR_GPIO_I2CDRIVE_CODE(0x1)     /**< \brief ������   */
/** @} */

/**
 * \name PIO0_27 ����I2C�����ԣ���׼ģʽ������ģʽ�ͳ�����ģʽ��
 * @{
 */
#define PIO0_27_FILTERENABLE   AMDR_GPIO_I2CFILTER_CODE(0x0)    /**< \brief 50 ns �����˲�ʹ�� */
#define PIO0_27_FILTERDISABLE  AMDR_GPIO_I2CFILTER_CODE(0x1)    /**< \brief 50 ns �����˲����� */
/** @} */

/**
 * \name PIO0_27 ���ŵ�I2C����
 * @{
 */

#define PIO0_27_4MA_DRIVE      AMDR_PIO_4MA_DRIVE               /**< \brief GPIO 4 mA����    */
#define PIO0_27_20MA_DRIVE     AMDR_PIO_20MA_DRIVE              /**< \brief GPIO 20 mA����   */
#define PIO0_27_STD_I2C        AMDR_FAST_STD_MODE               /**< \brief I2C����/��׼ģʽ */
#define PIO0_27_MOD_PLU_IIC    AMDR_FAST_MODE_PLUS              /**< \brief I2C������ģʽ    */
#define PIO0_27_HIGH_I2C       AMDR_HIGH_SPEED_SLAVE            /**< \brief I2C���ٴӻ�ģʽ  */

/** @} */

/******************************************************************************/

/**
 * \name PIO0_28���Ź���
 * @{
 */

#define PIO0_28_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_28_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_28_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_28_I2C2_SDA       AMDR_GPIO_FUNC_CODE(0x1)         /**< \brief I2C2_SDA    */
#define PIO0_28_CT2_MAT0       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_MAT0    */

/** @} */

/**
 * \name PIO0_28 ����I2C���Ż�ת����
 * @{
 */
#define PIO0_28_SLEWDISABLE    AMDR_GPIO_I2CSLEWBIT_CODE(0x0)   /**< \brief I2Cģʽ   */
#define PIO0_28_SLEWENABLE     AMDR_GPIO_I2CSLEWBIT_CODE(0x1)   /**< \brief GPIOģʽ  */
/** @} */

/**
 * \name PIO0_28 ���뼫��
 * @{
 */
#define PIO0_28_INVDISABLE     AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO0_28_INVENABLE      AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_28 ��������˲�
 * @{
 */
#define PIO0_28_FILDISABLE     AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_28_FILENABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_28 �������ŵĵ�����������
 * @{
 */
#define PIO0_28_DRIVEDISABLE   AMDR_GPIO_I2CDRIVE_CODE(0x0)     /**< \brief ������   */
#define PIO0_28_DRIVEENABLE    AMDR_GPIO_I2CDRIVE_CODE(0x1)     /**< \brief ������   */
/** @} */


/**
 * \name PIO0_28 ����I2C�����ԣ���׼ģʽ������ģʽ�ͳ�����ģʽ��
 * @{
 */
#define PIO0_28_FILTERENABLE   AMDR_GPIO_I2CFILTER_CODE(0x0)    /**< \brief 50 ns �����˲�ʹ�� */
#define PIO0_28_FILTERDISABLE  AMDR_GPIO_I2CFILTER_CODE(0x1)    /**< \brief 50 ns �����˲����� */
/** @} */


/**
 * \name PIO0_28 ���ŵ�I2C����
 * @{
 */

#define PIO0_28_4MA_DRIVE      AMDR_PIO_4MA_DRIVE               /**< \brief GPIO 4 mA����    */
#define PIO0_28_20MA_DRIVE     AMDR_PIO_20MA_DRIVE              /**< \brief GPIO 20 mA����   */
#define PIO0_28_STD_I2C        AMDR_FAST_STD_MODE               /**< \brief I2C����/��׼ģʽ */
#define PIO0_28_MOD_PLU_IIC    AMDR_FAST_MODE_PLUS              /**< \brief I2C������ģʽ    */
#define PIO0_28_HIGH_I2C       AMDR_HIGH_SPEED_SLAVE            /**< \brief I2C���ٴӻ�ģʽ  */

/** @} */

/******************************************************************************/

/**
 * \name PIO0_29���Ź���
 * @{
 */

#define PIO0_29_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO0_29_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO0_29_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO0_29_ADC_IN0        AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN0    */
#define PIO0_29_SCT0_OUT2      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT2  */
#define PIO0_29_CT0_MAT3       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT3   */
#define PIO0_29_CT0_CAP1       AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT0_CAP1   */
#define PIO0_29_CT0_MAT1       AMDR_GPIO_FUNC_CODE(0x6)         /**< \brief CT0_MAT1   */

/** @} */

/**
 * \name PIO0_29����ģʽ
 * @{
 */
 
#define PIO0_29_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_29_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_29_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_29_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_29 ���뼫��
 * @{
 */
#define PIO0_29_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_29_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_29 ��������˲�
 * @{
 */
#define PIO0_29_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_29_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_29 ��©ģʽ
 * @{
 */
#define PIO0_29_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_29_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO0_30���Ź���
 * @{
 */

#define PIO0_30_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO0_30_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO0_30_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO0_30_ADC_IN1        AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN1   */
#define PIO0_30_SCT0_OUT3      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SCT0_OUT3 */
#define PIO0_30_CT0_MAT2       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_MAT2  */                       
#define PIO0_30_CT0_CAP2       AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT0_CAP2  */

/** @} */

/**
 * \name PIO0_30����ģʽ
 * @{
 */
 
#define PIO0_30_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_30_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_30_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_30_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_30 ���뼫��
 * @{
 */
#define PIO0_30_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_30_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_30 ��������˲�
 * @{
 */
#define PIO0_30_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_30_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_30 ��©ģʽ
 * @{
 */
#define PIO0_30_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_30_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/
 
/**
 * \name PIO0_31���Ź���
 * @{
 */  

#define PIO0_31_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO0_31_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO0_31_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO0_31_ADC_IN2        AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN2     */
#define PIO0_31_USART2_CTS     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART2_CTS  */
#define PIO0_31_CT2_CAP2       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT2_CAP2    */
#define PIO0_31_CT0_CAP3       AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT0_CAP3    */
#define PIO0_31_CT0_MAT3       AMDR_GPIO_FUNC_CODE(0x6)         /**< \brief CT0_MAT3    */

/** @} */

/**
 * \name PIO0_31����ģʽ
 * @{
 */
 
#define PIO0_31_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO0_31_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO0_31_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO0_31_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO0_31 ���뼫��
 * @{
 */
#define PIO0_31_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO0_31_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO0_31 ��������˲�
 * @{
 */
#define PIO0_31_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO0_31_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO0_31 ��©ģʽ
 * @{
 */
#define PIO0_31_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO0_31_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_0���Ź���
 * @{
 */

#define PIO1_0_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO       */
#define PIO1_0_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����       */
#define PIO1_0_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���       */
#define PIO1_0_ADC_IN3         AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN3    */
#define PIO1_0_USART2_RTS      AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART2_RTS */
#define PIO1_0_CT3_MAT1        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT3_MAT1   */
#define PIO1_0_CT0_CAP0        AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT0_CAP0   */

/** @} */

/**
 * \name PIO1_0����ģʽ
 * @{
 */
 
#define PIO1_0_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_0_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_0_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_0_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_0 ���뼫��
 * @{
 */
#define PIO1_0_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_0_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_0 ��������˲�
 * @{
 */
#define PIO1_0_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_0_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_0 ��©ģʽ
 * @{
 */
#define PIO1_0_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_0_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_1���Ź���
 * @{
 */

#define PIO1_1_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO1_1_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO1_1_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO1_1_ADC_IN4         AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN4   */
#define PIO1_1_SWO             AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SWO       */
#define PIO1_1_SCT0_OUT4       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief SCT0_OUT4 */

/** @} */ 

/**
 * \name PIO1_1����ģʽ
 * @{
 */
 
#define PIO1_1_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_1_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_1_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_1_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_1 ���뼫��
 * @{
 */
#define PIO1_1_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_1_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_1 ��������˲�
 * @{
 */
#define PIO1_1_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_1_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_1 ��©ģʽ
 * @{
 */
#define PIO1_1_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_1_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_2���Ź���
 * @{
 */

#define PIO1_2_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO          */
#define PIO1_2_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����          */
#define PIO1_2_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���          */
#define PIO1_2_ADC_IN5         AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN5       */
#define PIO1_2_SPI1_SSELN3     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI1_SSELN3   */
#define PIO1_2_SSCT0_OUT5      AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief SCT0_OUT5     */

/** @} */

/**
 * \name PIO1_2����ģʽ
 * @{
 */
 
#define PIO1_2_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_2_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_2_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_2_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_2 ���뼫��
 * @{
 */
#define PIO1_2_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_2_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_2 ��������˲�
 * @{
 */
#define PIO1_2_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_2_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_2 ��©ģʽ
 * @{
 */
#define PIO1_2_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_2_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_3���Ź���
 * @{
 */

#define PIO1_3_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO1_3_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO1_3_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO1_3_ADC_IN6         AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN6     */
#define PIO1_3_SPI1_SSELN2     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI1_SSELN2 */
#define PIO1_3_SCT0_OUT6       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief SCT0_OUT6   */
#define PIO1_3_SPI0_SCK        AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief SPI0_SCK    */
#define PIO1_3_CT0_CAP1        AMDR_GPIO_FUNC_CODE(0x6)         /**< \brief CT0_CAP1    */

/** @} */

/**
 * \name PIO1_3����ģʽ
 * @{
 */
 
#define PIO1_3_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_3_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_3_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_3_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_3 ���뼫��
 * @{
 */
#define PIO1_3_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_3_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_3 ��������˲�
 * @{
 */
#define PIO1_3_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_3_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_3 ��©ģʽ
 * @{
 */
#define PIO1_3_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_3_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_4���Ź���
 * @{
 */

#define PIO1_4_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO1_4_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO1_4_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO1_4_ADC_IN7         AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN7     */
#define PIO1_4_SPI1_SSELN1     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI1_SSELN1 */
#define PIO1_4_SCT0_OUT7       AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief SCT0_OUT7   */
#define PIO1_4_SPI0_MISO       AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief SPI0_MISO   */
#define PIO1_4_CT0_MAT1        AMDR_GPIO_FUNC_CODE(0x6)         /**< \brief CT0_MAT1    */

/** @} */

/**
 * \name PIO1_4����ģʽ
 * @{
 */
 
#define PIO1_4_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_4_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_4_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_4_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_4 ���뼫��
 * @{
 */
#define PIO1_4_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_4_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_4 ��������˲�
 * @{
 */
#define PIO1_4_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_4_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_4 ��©ģʽ
 * @{
 */
#define PIO1_4_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_4_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_5���Ź���
 * @{
 */

#define PIO1_5_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO1_5_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO1_5_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO1_5_ADC_IN8         AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief  ADC_IN8    */
#define PIO1_5_SPI1_SSELN0     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI1_SSELN0 */
#define PIO1_5_CT1_CAP0        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT1_CAP0    */
#define PIO1_5_CT1_MAT3        AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT1_MAT3    */

/** @} */

/**
 * \name PIO1_5����ģʽ
 * @{
 */
 
#define PIO1_5_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_5_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_5_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_5_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_5 ���뼫��
 * @{
 */
#define PIO1_5_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_5_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_5 ��������˲�
 * @{
 */
#define PIO1_5_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_5_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_5 ��©ģʽ
 * @{
 */
#define PIO1_5_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_5_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_6���Ź���
 * @{
 */

#define PIO1_6_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO     */
#define PIO1_6_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����     */
#define PIO1_6_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���     */
#define PIO1_6_ADC_IN9         AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN9  */
#define PIO1_6_SPI1_SCK        AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI1_SCK */
#define PIO1_6_CT1_CAP2        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT1_CAP2 */
#define PIO1_6_CT1_MAT2        AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT1_MAT2 */
/** @} */

/**
 * \name PIO1_6����ģʽ
 * @{
 */
 
#define PIO1_6_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_6_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_6_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_6_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_6 ���뼫��
 * @{
 */
#define PIO1_6_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_6_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_6 ��������˲�
 * @{
 */
#define PIO1_6_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_6_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_6 ��©ģʽ
 * @{
 */
#define PIO1_6_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_6_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_7���Ź���
 * @{
 */

#define PIO1_7_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO1_7_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO1_7_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO1_7_ADC_IN10        AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN10  */
#define PIO1_7_SPI1_MOSI       AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI1_MOSI */
#define PIO1_7_CT1_MAT2        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT1_MAT2  */
#define PIO1_7_CT1_CAP2        AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT1_CAP2  */

/** @} */

/**
 * \name PIO1_7����ģʽ
 * @{
 */
 
#define PIO1_7_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_7_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_7_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_7_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_7 ���뼫��
 * @{
 */
#define PIO1_7_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_7_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_7 ��������˲�
 * @{
 */
#define PIO1_7_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_7_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_7 ��©ģʽ
 * @{
 */
#define PIO1_7_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_7_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_8���Ź���
 * @{
 */

#define PIO1_8_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO      */
#define PIO1_8_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����      */
#define PIO1_8_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���      */
#define PIO1_8_ADC_IN11        AMDR_GPIO_ADC_FUNC_CODE(0x0)     /**< \brief ADC_IN11  */
#define PIO1_8_SPI1_MISO       AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI1_MISO */
#define PIO1_8_CT1_MAT3        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT1_MAT3  */
#define PIO1_8_CT1_CAP3        AMDR_GPIO_FUNC_CODE(0x5)         /**< \brief CT1_CAP3  */

/** @} */

/**
 * \name PIO1_8����ģʽ
 * @{
 */
 
#define PIO1_8_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_8_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_8_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_8_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_8 ���뼫��
 * @{
 */
#define PIO1_8_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_8_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_8 ��������˲�
 * @{
 */
#define PIO1_8_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_8_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_8 ��©ģʽ
 * @{
 */
#define PIO1_8_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_8_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_9���Ź���
 * @{
 */

#define PIO1_9_GPIO            AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO1_9_INPUT           AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO1_9_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO1_9_SPI0_MOSI       AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief SPI0_MOSI   */
#define PIO1_9_CT0_CAP2        AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief CT0_CAP2    */

/** @} */

/**
 * \name PIO1_9����ģʽ
 * @{
 */
 
#define PIO1_9_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)         /**< \brief ����ģʽ(������/����) */
#define PIO1_9_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)         /**< \brief ����ģʽ              */
#define PIO1_9_PULLUP          AMDR_GPIO_MODE_CODE(0x2)         /**< \brief ����ģʽ              */
#define PIO1_9_REPEATER        AMDR_GPIO_MODE_CODE(0x3)         /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_9 ���뼫��
 * @{
 */
#define PIO1_9_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)    /**< \brief ����ת   */
#define PIO1_9_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)    /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_9 ��������˲�
 * @{
 */
#define PIO1_9_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_9_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_9 ������ת����
 * @{
 */
#define PIO1_9_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)      /**< \brief ��׼ģʽ */
#define PIO1_9_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)      /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_9 ��©ģʽ
 * @{
 */
#define PIO1_9_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)        /**< \brief ����     */
#define PIO1_9_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)        /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_10���Ź���
 * @{
 */

#define PIO1_10_GPIO           AMDR_GPIO_FUNC_CODE(0x0)         /**< \brief GPIO        */
#define PIO1_10_INPUT          AMDR_GPIO_DIR_CODE(0x0)          /**< \brief ����        */
#define PIO1_10_OUTPUT         AMDR_GPIO_DIR_CODE(0x1)          /**< \brief ���        */
#define PIO1_10_USART1_TXD     AMDR_GPIO_FUNC_CODE(0x2)         /**< \brief USART1_TXD  */
#define PIO1_10_SCT0_OUT4      AMDR_GPIO_FUNC_CODE(0x3)         /**< \brief SCT0_OUT4   */

/** @} */

/**
 * \name PIO1_10����ģʽ
 * @{
 */
 
#define PIO1_10_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_10_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_10_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_10_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_10 ���뼫��
 * @{
 */
#define PIO1_10_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_10_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_10 ��������˲�
 * @{
 */
#define PIO1_10_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_10_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_10 ������ת����
 * @{
 */
#define PIO1_10_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_10_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_10 ��©ģʽ
 * @{
 */
#define PIO1_10_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_10_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_11���Ź���
 * @{
 */

#define PIO1_11_GPIO            AMDR_GPIO_FUNC_CODE(0x0)        /**< \brief GPIO       */
#define PIO1_11_INPUT           AMDR_GPIO_DIR_CODE(0x0)         /**< \brief ����       */
#define PIO1_11_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)         /**< \brief ���       */
#define PIO1_11_USART1_RTS      AMDR_GPIO_FUNC_CODE(0x2)        /**< \brief USART1_RTS */
#define PIO1_11_CT1_CAP0        AMDR_GPIO_FUNC_CODE(0x3)        /**< \brief CT1_CAP0   */

/** @} */

/**
 * \name PIO1_11����ģʽ
 * @{
 */
 
#define PIO1_11_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_11_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_11_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_11_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_11 ���뼫��
 * @{
 */
#define PIO1_11_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_11_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_11 ��������˲�
 * @{
 */
#define PIO1_11_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_11_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_11 ������ת����
 * @{
 */
#define PIO1_11_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_11_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_11 ��©ģʽ
 * @{
 */
#define PIO1_11_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_11_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_12���Ź���
 * @{
 */

#define PIO1_12_GPIO            AMDR_GPIO_FUNC_CODE(0x0)        /**< \brief GPIO       */
#define PIO1_12_INPUT           AMDR_GPIO_DIR_CODE(0x0)         /**< \brief ����       */
#define PIO1_12_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)         /**< \brief ���       */
#define PIO1_12_USART3_RXD      AMDR_GPIO_FUNC_CODE(0x2)        /**< \brief USART3_RXD */
#define PIO1_12_CT1_MAT0        AMDR_GPIO_FUNC_CODE(0x3)        /**< \brief CT1_MAT0   */
#define PIO1_12_SPI1_SCK        AMDR_GPIO_FUNC_CODE(0x4)        /**< \brief SPI1_SCK   */

/** @} */

/**
 * \name PIO1_12����ģʽ
 * @{
 */
 
#define PIO1_12_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_12_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_12_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_12_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_12 ���뼫��
 * @{
 */
#define PIO1_12_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_12_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_12 ��������˲�
 * @{
 */
#define PIO1_12_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_12_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_12 ������ת����
 * @{
 */
#define PIO1_12_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_12_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_12 ��©ģʽ
 * @{
 */
#define PIO1_12_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_12_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_13���Ź���
 * @{
 */

#define PIO1_13_GPIO            AMDR_GPIO_FUNC_CODE(0x0)        /**< \brief GPIO       */
#define PIO1_13_INPUT           AMDR_GPIO_DIR_CODE(0x0)         /**< \brief ����       */
#define PIO1_13_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)         /**< \brief ���       */
#define PIO1_13_USART3_TXD      AMDR_GPIO_FUNC_CODE(0x2)        /**< \brief USART3_TXD */
#define PIO1_13_CT1_MAT1        AMDR_GPIO_FUNC_CODE(0x3)        /**< \brief CT1_MAT1   */
#define PIO1_13_SPI1_MOSI       AMDR_GPIO_FUNC_CODE(0x4)        /**< \brief SPI1_MOSI  */

/** @} */

/**
 * \name PIO1_13����ģʽ
 * @{
 */
 
#define PIO1_13_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_13_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_13_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_13_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_13 ���뼫��
 * @{
 */
#define PIO1_13_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_13_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_13 ��������˲�
 * @{
 */
#define PIO1_13_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_13_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_13 ������ת����
 * @{
 */
#define PIO1_13_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_13_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_13 ��©ģʽ
 * @{
 */
#define PIO1_13_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_13_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_14���Ź���
 * @{
 */

#define PIO1_14_GPIO            AMDR_GPIO_FUNC_CODE(0x0)        /**< \brief GPIO         */
#define PIO1_14_INPUT           AMDR_GPIO_DIR_CODE(0x0)         /**< \brief ����         */
#define PIO1_14_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)         /**< \brief ���         */
#define PIO1_14_USART2_RXD      AMDR_GPIO_FUNC_CODE(0x2)        /**< \brief USART2_RXD   */
#define PIO1_14_SCT0_OUT7       AMDR_GPIO_FUNC_CODE(0x3)        /**< \brief SCT0_OUT7    */
#define PIO1_14_SPI1_MISO       AMDR_GPIO_FUNC_CODE(0x4)        /**< \brief SPI1_MISO    */

/** @} */

/**
 * \name PIO1_14����ģʽ
 * @{
 */
 
#define PIO1_14_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_14_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_14_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_14_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_14 ���뼫��
 * @{
 */
#define PIO1_14_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_14_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_14 ��������˲�
 * @{
 */
#define PIO1_14_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_14_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_14 ������ת����
 * @{
 */
#define PIO1_14_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_14_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_14 ��©ģʽ
 * @{
 */
#define PIO1_14_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_14_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/******************************************************************************/

/**
 * \name PIO1_15���Ź���
 * @{
 */

#define PIO1_15_GPIO            AMDR_GPIO_FUNC_CODE(0x0)        /**< \brief GPIO        */
#define PIO1_15_INPUT           AMDR_GPIO_DIR_CODE(0x0)         /**< \brief ����        */
#define PIO1_15_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)         /**< \brief ���        */
#define PIO1_15_SCT0_OUT5       AMDR_GPIO_FUNC_CODE(0x2)        /**< \brief SCT0_OUT5   */
#define PIO1_15_CT1_CAP3        AMDR_GPIO_FUNC_CODE(0x3)        /**< \brief CT1_CAP3    */
#define PIO1_15_SPI1_SSELN0     AMDR_GPIO_FUNC_CODE(0x4)        /**< \brief SPI1_SSELN0 */

/** @} */

/**
 * \name PIO1_15����ģʽ
 * @{
 */
 
#define PIO1_15_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_15_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_15_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_15_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_15 ���뼫��
 * @{
 */
#define PIO1_15_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_15_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_15 ��������˲�
 * @{
 */
#define PIO1_15_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_15_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_15 ������ת����
 * @{
 */
#define PIO1_15_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_15_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_15 ��©ģʽ
 * @{
 */
#define PIO1_15_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_15_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_16���Ź���
 * @{
 */

#define PIO1_16_GPIO            AMDR_GPIO_FUNC_CODE(0x0)        /**< \brief GPIO        */
#define PIO1_16_INPUT           AMDR_GPIO_DIR_CODE(0x0)         /**< \brief ����        */
#define PIO1_16_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)         /**< \brief ���        */
#define PIO1_16_CT0_MAT0        AMDR_GPIO_FUNC_CODE(0x2)        /**< \brief CT0_MAT0    */
#define PIO1_16_CT0_CAP0        AMDR_GPIO_FUNC_CODE(0x3)        /**< \brief CT0_CAP0    */
#define PIO1_16_SPI1_SSELN1     AMDR_GPIO_FUNC_CODE(0x4)        /**< \brief SPI1_SSELN1 */

/** @} */

/**
 * \name PIO1_16����ģʽ
 * @{
 */
 
#define PIO1_16_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_16_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_16_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_16_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_16 ���뼫��
 * @{
 */
#define PIO1_16_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_16_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_16 ��������˲�
 * @{
 */
#define PIO1_16_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_16_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_16 ������ת����
 * @{
 */
#define PIO1_16_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_16_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_16 ��©ģʽ
 * @{
 */
#define PIO1_16_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_16_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */

/******************************************************************************/

/**
 * \name PIO1_17���Ź���
 * @{
 */

#define PIO1_17_GPIO            AMDR_GPIO_FUNC_CODE(0x0)        /**< \brief GPIO          */
#define PIO1_17_INPUT           AMDR_GPIO_DIR_CODE(0x0)         /**< \brief ����          */
#define PIO1_17_OUTPUT          AMDR_GPIO_DIR_CODE(0x1)         /**< \brief ���          */

/** @} */

/**
 * \name PIO1_17����ģʽ
 * @{
 */
 
#define PIO1_17_INACTIVE        AMDR_GPIO_MODE_CODE(0x0)        /**< \brief ����ģʽ(������/����) */
#define PIO1_17_PULLDOWN        AMDR_GPIO_MODE_CODE(0x1)        /**< \brief ����ģʽ              */
#define PIO1_17_PULLUP          AMDR_GPIO_MODE_CODE(0x2)        /**< \brief ����ģʽ              */
#define PIO1_17_REPEATER        AMDR_GPIO_MODE_CODE(0x3)        /**< \brief �м�ģʽ              */

/** @} */

/**
 * \name PIO1_17 ���뼫��
 * @{
 */
#define PIO1_17_INVDISABLE      AMDR_GPIO_INVERTBIT_CODE(0x0)   /**< \brief ����ת   */
#define PIO1_17_INVENABLE       AMDR_GPIO_INVERTBIT_CODE(0x1)   /**< \brief ��ת     */
/** @} */

/**
 * \name PIO1_17 ��������˲�
 * @{
 */
#define PIO1_17_FILDISABLE      AMDR_GPIO_FILTEROFFBIT_CODE(0x1) /**< \brief �˲�ʹ�� */
#define PIO1_17_FILENABLE       AMDR_GPIO_FILTEROFFBIT_CODE(0x0) /**< \brief �˲����� */
/** @} */

/**
 * \name PIO1_17 ������ת����
 * @{
 */
#define PIO1_17_SLEWDISABLE     AMDR_GPIO_SLEWBIT_CODE(0x0)     /**< \brief ��׼ģʽ */
#define PIO1_17_SLEWENABLE      AMDR_GPIO_SLEWBIT_CODE(0x1)     /**< \brief ����ģʽ */
/** @} */

/**
 * \name PIO1_17 ��©ģʽ
 * @{
 */
#define PIO1_17_ODDISABLE       AMDR_GPIO_ODBIT_CODE(0x0)       /**< \brief ����     */
#define PIO1_17_ODENABLE        AMDR_GPIO_ODBIT_CODE(0x1)       /**< \brief ��©     */
/** @} */


/** 
 * @}
 */

/**
 * @} amhw_if_pin
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC5410X_PIN_H */

/* end of file */

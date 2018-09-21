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
 * \brief GPIOƽ̨�������ߺ�
 *
 * ���ļ��������� \sa lpc5410x_pin.h. �䶨����GPIOƽ̨���ŵĸ������ܡ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-07  hbt, first implementation.
 * \endinternal
 */

#ifndef __AMDR_GPIO_UTIL_H
#define __AMDR_GPIO_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 


/** 
 * \addtogroup amdr_if_gpio_util
 * \copydoc amdr_gpio_util.h
 * @{
 */

/**
 * \brief �궨��
 * 
 * bit[31:12] ƽ̨����
 *
 * bit[21:12] ʹ��λ
 * bit[12]    IOCON bits[2:0] ʹ��λ
 * bit[13]    IOCON bits[5:3] ʹ��λ
 * bit[14]    IOCON bit[5] ʹ��λ
 * bit[15]    IOCON bit[6] ʹ��λ
 * bit[16]    IOCON bit[8] ʹ��λ
 * bit[17]    IOCON bit[9] ʹ��λ
 * bit[18]    IOCON bit[10] ʹ��λ
 * bit[19]    I2C ʹ��λ
 * bit[20]    ADC ʹ��λ
 * bit[20]    ���÷���ʹ��λ
 *
 * bit[24:22] ������
 *
 * bit[25]    ���÷��� (��ֹI2C����)
 * bit[30:25] I2C ģʽ (I2C��ʹ��)
 *
 * bit[26]    I2C ��תʹ�� (I2C��ʹ��)
 * bit[27:26] I2C ģʽ������ (��ֹI2C����)
 *
 * bit[28]    ��תʹ��
 * bit[29]    ��ֹ�˲�ʹ��
 * bit[30]    ��תʹ�ܻ�I2C����ʹ��(I2C��ʹ��)
 * bit[31]    ��©ʹ�ܻ�I2C�˲�ʹ��(I2C��ʹ��)
 */
 
/** 
 * \name IOCON ����λ��
 * @{
 */
 
#define AMDR_GPIO_CON_BIT0               AM_BIT(12)   /**< \brief IOCON bits[2:0] ʹ��λ */
#define AMDR_GPIO_CON_BIT3               AM_BIT(13)   /**< \brief IOCON bits[5:3] ʹ��λ */
#define AMDR_GPIO_CON_BIT5               AM_BIT(14)   /**< \brief IOCON bit[5] ʹ��λ    */
#define AMDR_GPIO_CON_BIT6               AM_BIT(15)   /**< \brief IOCON bit[6] ʹ��λ    */
#define AMDR_GPIO_CON_BIT8               AM_BIT(16)   /**< \brief IOCON bit[8] ʹ��λ    */
#define AMDR_GPIO_CON_BIT9               AM_BIT(17)   /**< \brief IOCON bit[9] ʹ��λ    */
#define AMDR_GPIO_CON_BIT10              AM_BIT(18)   /**< \brief IOCON bit[10] ʹ��λ   */

#define AMDR_GPIO_I2CEN_BIT              AM_BIT(19)   /**< \brief I2C ʹ��λ             */
#define AMDR_GPIO_ADCEN_BIT              AM_BIT(20)   /**< \brief ADC ʹ��λ             */
#define AMDR_GPIO_DIREN_BIT              AM_BIT(21)   /**< \brief ���÷���ʹ��λ         */


#define AMDR_GPIO_FUNCBITS_START         22           /**< \brief ������ʼλ   */
#define AMDR_GPIO_FUNCBITS_LEN           3            /**< \brief �����볤��   */

/** \brief �ù����� */
#define AMDR_GPIO_FUNC_CODE(a)          (AM_SBF((a), AMDR_GPIO_FUNCBITS_START) |  \
                                         AMDR_GPIO_CON_BIT0) 

/** \brief ��ȡ������ */
#define AMDR_GPIO_FUNC_GET(data)         AM_BITS_GET((data), AMDR_GPIO_FUNCBITS_START, \
                                         AMDR_GPIO_FUNCBITS_LEN)

/** \brief ��ADC������ */
#define AMDR_GPIO_ADC_FUNC_CODE(a)      (AM_SBF((a), AMDR_GPIO_FUNCBITS_START) | AMDR_GPIO_ADCEN_BIT)

/** \brief ����λƫ�� */
#define AMDR_GPIO_DIRBIT_OFFSET          25

/** \brief �÷����� */
#define AMDR_GPIO_DIR_CODE(a)           (AM_SBF((a), AMDR_GPIO_DIRBIT_OFFSET) |  \
                                         AMDR_GPIO_DIREN_BIT)

/** \brief ��ȡ������ */
#define AMDR_GPIO_DIR_GET(data)          AM_BIT_GET((data), AMDR_GPIO_DIRBIT_OFFSET)

/** \brief ģʽ��ʼλ */
#define AMDR_GPIO_MODEBITS_START         26

/** \brief ģʽ�볤�� */
#define AMDR_GPIO_MODEBITS_LEN           2

/** \brief ��ģʽ�� */
#define AMDR_GPIO_MODE_CODE(a)          (AM_SBF((a), AMDR_GPIO_MODEBITS_START) |       \
                                         AMDR_GPIO_CON_BIT3)

/** \brief ��ȡģʽ�� */
#define AMDR_GPIO_MODE_GET(data)         AM_BITS_GET((data), AMDR_GPIO_MODEBITS_START, \
                                         AMDR_GPIO_MODEBITS_LEN)

/** \brief ��תλƫ�� */
#define AMDR_GPIO_INVERTBIT_OFFSET       28

/** \brief �÷�ת�� */
#define AMDR_GPIO_INVERTBIT_CODE(a)     (AM_SBF((a), AMDR_GPIO_INVERTBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT6)

/** \brief ��ȡ��ת�� */
#define AMDR_GPIO_INVERTBIT_GET(data)    AM_BIT_GET((data), AMDR_GPIO_INVERTBIT_OFFSET)

/** \brief �˲�λƫ�� */
#define AMDR_GPIO_FILTEROFFBIT_OFFSET    29

/** \brief ���˲��� */
#define AMDR_GPIO_FILTEROFFBIT_CODE(a)  (AM_SBF((a), AMDR_GPIO_FILTEROFFBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT8)

/** \brief ��ȡ�˲��� */
#define AMDR_GPIO_FILTEROFFBIT_GET(data) AM_BIT_GET((data), AMDR_GPIO_FILTEROFFBIT_OFFSET)

/** \brief ��תλƫ�� */
#define AMDR_GPIO_SLEWBIT_OFFSET         30

/** \brief �û�ת�� */
#define AMDR_GPIO_SLEWBIT_CODE(a)       (AM_SBF((a), AMDR_GPIO_SLEWBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT9)

/** \brief ��ȡ��ת�� */
#define AMDR_GPIO_SLEWBIT_GET(data)      AM_BIT_GET((data), AMDR_GPIO_SLEWBIT_OFFSET)

/** \brief ��©λƫ�� */
#define AMDR_GPIO_ODBIT_OFFSET           31

/** \brief �ÿ�©�� */
#define AMDR_GPIO_ODBIT_CODE(a)         (AM_SBF((a), AMDR_GPIO_ODBIT_OFFSET) |  \
                                         AMDR_GPIO_CON_BIT10)

/** \brief ��ȡ��©�� */
#define AMDR_GPIO_ODBIT_GET(data)        AM_BIT_GET((data), AMDR_GPIO_ODBIT_OFFSET)

/** @} */

/**
 * \name I2Cģʽλ��
 *
 *  ����I2C�Ĺ������ã�Ϊ��ֹ�����ŵ��������ܳ�ͻ�������õ���ʼλΪ25��
 */
 
#define AMDR_GPIO_I2CBITS_OFFSET         25   /**< \brief I2C suggest mode start bit   */
#define AMDR_GPIO_I2CBITS_LEN            6    /**< \brief I2C suggest mode bits length */

/** \brief ��I2C������ */
#define AMDR_GPIO_I2C_FUNC_CODE(a)       AM_SBF((a), AMDR_GPIO_I2CBITS_OFFSET)

/** \brief ��ȡI2C������ */
#define AMDR_GPIO_I2C_FUNC_GET(data)     AM_BITS_GET((data), AMDR_GPIO_I2CBITS_OFFSET, \
                                         AMDR_GPIO_I2CBITS_LEN)

/** \brief GPIO 4 mA ���� */
#define AMDR_PIO_4MA_DRIVE               AMDR_GPIO_I2C_FUNC_CODE(0x05) | \
                                         AMDR_GPIO_I2CEN_BIT

/** \brief GPIO 20 mA ���� */
#define AMDR_PIO_20MA_DRIVE              AMDR_GPIO_I2C_FUNC_CODE(0x15) | \
                                         AMDR_GPIO_I2CEN_BIT  

/** \brief I2C����/��׼ģʽ */
#define AMDR_FAST_STD_MODE               AMDR_GPIO_I2C_FUNC_CODE(0x0C) |  \
                                         AMDR_GPIO_I2CEN_BIT 

/** \brief I2C������ģʽ */
#define AMDR_FAST_MODE_PLUS              AMDR_GPIO_I2C_FUNC_CODE(0x3C) |  \
                                         AMDR_GPIO_I2CEN_BIT 

/** \brief I2C���ٴӻ�ģʽ */
#define AMDR_HIGH_SPEED_SLAVE            AMDR_GPIO_I2C_FUNC_CODE(0x3C) | \
                                         AMDR_GPIO_I2CEN_BIT 

/** \brief I2C��תλƫ�� */
#define AMDR_GPIO_I2CSLEWBIT_OFFSET      26

/** \brief ��I2C��ת�� */
#define AMDR_GPIO_I2CSLEWBIT_CODE(a)    (AM_SBF((a), AMDR_GPIO_I2CSLEWBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT5)

/** \brief ��ȡI2C��ת�� */
#define AMDR_GPIO_I2CSLEWBIT_GET(data)   AM_BIT_GET((data), AMDR_GPIO_I2CSLEWBIT_OFFSET)

/** \brief ��I2C������ */
#define AMDR_GPIO_I2CDRIVE_CODE(a)       AMDR_GPIO_SLEWBIT_CODE(a)

/** \brief ��ȡI2C������ */
#define AMDR_GPIO_I2CDRIVE_GET(data)     AMDR_GPIO_SLEWBIT_GET(data)

/** \brief ��I2C�˲��� */
#define AMDR_GPIO_I2CFILTER_CODE(a)      AMDR_GPIO_ODBIT_CODE(a)

/** \brief ��ȡI2C�˲��� */
#define AMDR_GPIO_I2CFILTER_GET(data)    AMDR_GPIO_ODBIT_GET(data)

/** @} */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_GPIO_UTIL_H */

/* end of file */

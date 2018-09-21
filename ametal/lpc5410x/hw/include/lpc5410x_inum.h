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
 * \brief LPC5410X �жϺŶ���
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-06  hbt, first implementation.
 * \endinternal
 */


#ifndef __LPC5410X_INUM_H
#define __LPC5410X_INUM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc5410x.h"

/** 
 * \addtogroup amhw_if_inum
 * \copydoc lpc5410x_inum.h
 * @{
 */

/**
 * \name LPC5410x CPU �жϺ�
 * @{
 */
                                                                                            
#define INUM_WWDT                0    /**< \brief ���Ź��ж�             */
#define INUM_BOD                 1    /**< \brief BOD�ж�                */
#define INUM_DMA                 3    /**< \brief DMA�ж�                */
#define INUM_GINT0               4    /**< \brief GPIO���ж�0            */
#define INUM_PIN_INT0            5    /**< \brief �����ж�0              */
#define INUM_PIN_INT1            6    /**< \brief �����ж�1              */
#define INUM_PIN_INT2            7    /**< \brief �����ж�2              */
#define INUM_PIN_INT3            8    /**< \brief �����ж�3              */
#define INUM_UTICK               9    /**< \brief Micro-tick ��ʱ���ж�  */
#define INUM_MRT                 10   /**< \brief Multi-rate ��ʱ���ж�  */
#define INUM_TIMER0              11   /**< \brief ��ʱ��0�ж�            */
#define INUM_TIMER1              12   /**< \brief ��ʱ��1�ж�            */
#define INUM_TIMER2              13   /**< \brief ��ʱ��2�ж�            */
#define INUM_TIMER3              14   /**< \brief ��ʱ��3�ж�            */
#define INUM_TIMER4              15   /**< \brief ��ʱ��4�ж�            */
#define INUM_SCT0                16   /**< \brief SCT�ж�                */
#define INUM_USART0              17   /**< \brief USART0�ж�             */
#define INUM_USART1              18   /**< \brief USART1�ж�             */
#define INUM_USART2              19   /**< \brief USART2�ж�             */
#define INUM_USART3              20   /**< \brief USART3�ж�             */
#define INUM_I2C0                21   /**< \brief I2C0�ж�               */
#define INUM_I2C1                22   /**< \brief I2C1�ж�               */
#define INUM_I2C2                23   /**< \brief I2C2�ж�               */
#define INUM_SPI0                24   /**< \brief SPI0�ж�               */
#define INUM_SPI1                25   /**< \brief SPI1�ж�               */
#define INUM_ADC0_SEQA           26   /**< \brief ADC0����A�ж�          */
#define INUM_ADC0_SEQB           27   /**< \brief ADC0����B�ж�          */
#define INUM_ADC0_THCMP          28   /**< \brief ADC0��ֵ�ȽϺʹ����ж� */
#define INUM_RTC                 29   /**< \brief RTC ���Ӻͻ����ж�     */
#define INUM_MAILBOX             31   /**< \brief �����ж�               */

#ifdef AM_CORTEX_M4

#define INUM_GINT1               32   /**< \brief GPIO���ж�1��ֻ Cortex-M4 ��֧�� */
#define INUM_PIN_INT4            33   /**< \brief �����ж�4��ֻ Cortex-M4 ��֧��   */
#define INUM_PIN_INT5            34   /**< \brief �����ж�5��ֻ Cortex-M4 ��֧��   */
#define INUM_PIN_INT6            35   /**< \brief �����ж�6��ֻ Cortex-M4 ��֧��   */
#define INUM_PIN_INT7            36   /**< \brief �����ж�7��ֻ Cortex-M4 ��֧��   */
#define INUM_RIT                 40   /**< \brief RIT�жϣ�ֻ Cortex-M4 ��֧��     */

#endif /* AM_CORTEX_M4 */

/** @} */


#if AM_CORTEX_M4

/**
 * \brief ʹ��Cortex-M4�ں�ʱ�����ж���Ϊ��(INUM_RIT - INUM_WWDT + 1),
 * ʹ��Cortex-M0+�ں�ʱ�����ж���Ϊ��(INUM_MAILBOX - INUM_WWDT + 1).
 */
#define INUM_INTERNAL_COUNT     (INUM_RIT - INUM_WWDT + 1)

/** 
 * \brief ʹ��Cortex-M4�ں�ʱ������жϺ�Ϊ��INUM_RIT��ʹ��Cortex-M0+�ں�ʱ��
 * ��С�жϺ�Ϊ��INUM_MAILBOX.
 */
#define INUM_INTERNAL_MAX        INUM_RIT

#endif

#if AM_CORTEX_M0

/**
 * \brief ʹ��Cortex-M4�ں�ʱ�����ж���Ϊ��(INUM_RIT - INUM_WWDT + 1),
 * ʹ��Cortex-M0+�ں�ʱ�����ж���Ϊ��(INUM_MAILBOX - INUM_WWDT + 1).
 */
#define INUM_INTERNAL_COUNT     (INUM_MAILBOX - INUM_WWDT + 1)

/** 
 * \brief ʹ��Cortex-M4�ں�ʱ������жϺ�Ϊ��INUM_RIT��ʹ��Cortex-M0+�ں�ʱ��
 * ��С�жϺ�Ϊ��INUM_MAILBOX.
 */
#define INUM_INTERNAL_MAX        INUM_MAILBOX

#endif

/** \brief ��С�жϺţ�Cortex-M4 �� Cortex-M0+ ��һ���� */
#define INUM_INTERNAL_MIN        INUM_WWDT


/**
 * \name LPC5410x �����жϺ�
 * @{
 */

#define INUM_PIO0_0              41   /**< \brief PIO0_0�жϺ�  */
#define INUM_PIO0_1              42   /**< \brief PIO0_1�жϺ�  */
#define INUM_PIO0_2              43   /**< \brief PIO0_2�жϺ�  */
#define INUM_PIO0_3              44   /**< \brief PIO0_3�жϺ�  */
#define INUM_PIO0_4              45   /**< \brief PIO0_4�жϺ�  */
#define INUM_PIO0_5              46   /**< \brief PIO0_5�жϺ�  */
#define INUM_PIO0_6              47   /**< \brief PIO0_6�жϺ�  */
#define INUM_PIO0_7              48   /**< \brief PIO0_7�жϺ�  */
#define INUM_PIO0_8              49   /**< \brief PIO0_8�жϺ�  */
#define INUM_PIO0_9              50   /**< \brief PIO0_9�жϺ�  */
#define INUM_PIO0_10             51   /**< \brief PIO0_10�жϺ� */
#define INUM_PIO0_11             52   /**< \brief PIO0_11�жϺ� */
#define INUM_PIO0_12             53   /**< \brief PIO0_12�жϺ� */
#define INUM_PIO0_13             54   /**< \brief PIO0_13�жϺ� */
#define INUM_PIO0_14             55   /**< \brief PIO0_14�жϺ� */
#define INUM_PIO0_15             56   /**< \brief PIO0_15�жϺ� */
#define INUM_PIO0_16             57   /**< \brief PIO0_16�жϺ� */
#define INUM_PIO0_17             58   /**< \brief PIO0_17�жϺ� */
#define INUM_PIO0_18             59   /**< \brief PIO0_18�жϺ� */
#define INUM_PIO0_19             60   /**< \brief PIO0_19�жϺ� */
#define INUM_PIO0_20             61   /**< \brief PIO0_20�жϺ� */
#define INUM_PIO0_21             62   /**< \brief PIO0_21�жϺ� */
#define INUM_PIO0_22             63   /**< \brief PIO0_22�жϺ� */
#define INUM_PIO0_23             64   /**< \brief PIO0_23�жϺ� */
#define INUM_PIO0_24             65   /**< \brief PIO0_24�жϺ� */
#define INUM_PIO0_25             66   /**< \brief PIO0_25�жϺ� */
#define INUM_PIO0_26             67   /**< \brief PIO0_26�жϺ� */
#define INUM_PIO0_27             68   /**< \brief PIO0_27�жϺ� */
#define INUM_PIO0_28             69   /**< \brief PIO0_28�жϺ� */
#define INUM_PIO0_29             70   /**< \brief PIO0_29�жϺ� */
#define INUM_PIO0_30             71   /**< \brief PIO0_30�жϺ� */
#define INUM_PIO0_31             72   /**< \brief PIO0_31�жϺ� */
             
#define INUM_PIO1_0              73   /**< \brief PIO1_0�жϺ�  */
#define INUM_PIO1_1              74   /**< \brief PIO1_1�жϺ�  */
#define INUM_PIO1_2              75   /**< \brief PIO1_2�жϺ�  */
#define INUM_PIO1_3              76   /**< \brief PIO1_3�жϺ�  */
#define INUM_PIO1_4              77   /**< \brief PIO1_4�жϺ�  */
#define INUM_PIO1_5              78   /**< \brief PIO1_5�жϺ�  */
#define INUM_PIO1_6              79   /**< \brief PIO1_6�жϺ�  */
#define INUM_PIO1_7              80   /**< \brief PIO1_7�жϺ�  */
#define INUM_PIO1_8              81   /**< \brief PIO1_8�жϺ�  */
#define INUM_PIO1_9              82   /**< \brief PIO1_9�жϺ�  */
#define INUM_PIO1_10             83   /**< \brief PIO1_10�жϺ� */
#define INUM_PIO1_11             84   /**< \brief PIO1_11�жϺ� */
#define INUM_PIO1_12             85   /**< \brief PIO1_12�жϺ� */
#define INUM_PIO1_13             86   /**< \brief PIO1_13�жϺ� */
#define INUM_PIO1_14             87   /**< \brief PIO1_14�жϺ� */
#define INUM_PIO1_15             88   /**< \brief PIO1_15�жϺ� */
#define INUM_PIO1_16             89   /**< \brief PIO1_16�жϺ� */
#define INUM_PIO1_17             90   /**< \brief PIO1_17�жϺ� */

/** @} */

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC5410X_INUM_H */

/* end of file */

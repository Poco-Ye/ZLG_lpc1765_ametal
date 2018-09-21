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
 * \brief LPC5410X 中断号定义
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
 * \name LPC5410x CPU 中断号
 * @{
 */
                                                                                            
#define INUM_WWDT                0    /**< \brief 看门狗中断             */
#define INUM_BOD                 1    /**< \brief BOD中断                */
#define INUM_DMA                 3    /**< \brief DMA中断                */
#define INUM_GINT0               4    /**< \brief GPIO组中断0            */
#define INUM_PIN_INT0            5    /**< \brief 引脚中断0              */
#define INUM_PIN_INT1            6    /**< \brief 引脚中断1              */
#define INUM_PIN_INT2            7    /**< \brief 引脚中断2              */
#define INUM_PIN_INT3            8    /**< \brief 引脚中断3              */
#define INUM_UTICK               9    /**< \brief Micro-tick 定时器中断  */
#define INUM_MRT                 10   /**< \brief Multi-rate 定时器中断  */
#define INUM_TIMER0              11   /**< \brief 定时器0中断            */
#define INUM_TIMER1              12   /**< \brief 定时器1中断            */
#define INUM_TIMER2              13   /**< \brief 定时器2中断            */
#define INUM_TIMER3              14   /**< \brief 定时器3中断            */
#define INUM_TIMER4              15   /**< \brief 定时器4中断            */
#define INUM_SCT0                16   /**< \brief SCT中断                */
#define INUM_USART0              17   /**< \brief USART0中断             */
#define INUM_USART1              18   /**< \brief USART1中断             */
#define INUM_USART2              19   /**< \brief USART2中断             */
#define INUM_USART3              20   /**< \brief USART3中断             */
#define INUM_I2C0                21   /**< \brief I2C0中断               */
#define INUM_I2C1                22   /**< \brief I2C1中断               */
#define INUM_I2C2                23   /**< \brief I2C2中断               */
#define INUM_SPI0                24   /**< \brief SPI0中断               */
#define INUM_SPI1                25   /**< \brief SPI1中断               */
#define INUM_ADC0_SEQA           26   /**< \brief ADC0序列A中断          */
#define INUM_ADC0_SEQB           27   /**< \brief ADC0序列B中断          */
#define INUM_ADC0_THCMP          28   /**< \brief ADC0阈值比较和错误中断 */
#define INUM_RTC                 29   /**< \brief RTC 闹钟和唤醒中断     */
#define INUM_MAILBOX             31   /**< \brief 邮箱中断               */

#ifdef AM_CORTEX_M4

#define INUM_GINT1               32   /**< \brief GPIO组中断1，只 Cortex-M4 才支持 */
#define INUM_PIN_INT4            33   /**< \brief 引脚中断4，只 Cortex-M4 才支持   */
#define INUM_PIN_INT5            34   /**< \brief 引脚中断5，只 Cortex-M4 才支持   */
#define INUM_PIN_INT6            35   /**< \brief 引脚中断6，只 Cortex-M4 才支持   */
#define INUM_PIN_INT7            36   /**< \brief 引脚中断7，只 Cortex-M4 才支持   */
#define INUM_RIT                 40   /**< \brief RIT中断，只 Cortex-M4 才支持     */

#endif /* AM_CORTEX_M4 */

/** @} */


#if AM_CORTEX_M4

/**
 * \brief 使用Cortex-M4内核时，总中断数为：(INUM_RIT - INUM_WWDT + 1),
 * 使用Cortex-M0+内核时，总中断数为：(INUM_MAILBOX - INUM_WWDT + 1).
 */
#define INUM_INTERNAL_COUNT     (INUM_RIT - INUM_WWDT + 1)

/** 
 * \brief 使用Cortex-M4内核时，最大中断号为：INUM_RIT，使用Cortex-M0+内核时，
 * 最小中断号为：INUM_MAILBOX.
 */
#define INUM_INTERNAL_MAX        INUM_RIT

#endif

#if AM_CORTEX_M0

/**
 * \brief 使用Cortex-M4内核时，总中断数为：(INUM_RIT - INUM_WWDT + 1),
 * 使用Cortex-M0+内核时，总中断数为：(INUM_MAILBOX - INUM_WWDT + 1).
 */
#define INUM_INTERNAL_COUNT     (INUM_MAILBOX - INUM_WWDT + 1)

/** 
 * \brief 使用Cortex-M4内核时，最大中断号为：INUM_RIT，使用Cortex-M0+内核时，
 * 最小中断号为：INUM_MAILBOX.
 */
#define INUM_INTERNAL_MAX        INUM_MAILBOX

#endif

/** \brief 最小中断号，Cortex-M4 和 Cortex-M0+ 均一样。 */
#define INUM_INTERNAL_MIN        INUM_WWDT


/**
 * \name LPC5410x 引脚中断号
 * @{
 */

#define INUM_PIO0_0              41   /**< \brief PIO0_0中断号  */
#define INUM_PIO0_1              42   /**< \brief PIO0_1中断号  */
#define INUM_PIO0_2              43   /**< \brief PIO0_2中断号  */
#define INUM_PIO0_3              44   /**< \brief PIO0_3中断号  */
#define INUM_PIO0_4              45   /**< \brief PIO0_4中断号  */
#define INUM_PIO0_5              46   /**< \brief PIO0_5中断号  */
#define INUM_PIO0_6              47   /**< \brief PIO0_6中断号  */
#define INUM_PIO0_7              48   /**< \brief PIO0_7中断号  */
#define INUM_PIO0_8              49   /**< \brief PIO0_8中断号  */
#define INUM_PIO0_9              50   /**< \brief PIO0_9中断号  */
#define INUM_PIO0_10             51   /**< \brief PIO0_10中断号 */
#define INUM_PIO0_11             52   /**< \brief PIO0_11中断号 */
#define INUM_PIO0_12             53   /**< \brief PIO0_12中断号 */
#define INUM_PIO0_13             54   /**< \brief PIO0_13中断号 */
#define INUM_PIO0_14             55   /**< \brief PIO0_14中断号 */
#define INUM_PIO0_15             56   /**< \brief PIO0_15中断号 */
#define INUM_PIO0_16             57   /**< \brief PIO0_16中断号 */
#define INUM_PIO0_17             58   /**< \brief PIO0_17中断号 */
#define INUM_PIO0_18             59   /**< \brief PIO0_18中断号 */
#define INUM_PIO0_19             60   /**< \brief PIO0_19中断号 */
#define INUM_PIO0_20             61   /**< \brief PIO0_20中断号 */
#define INUM_PIO0_21             62   /**< \brief PIO0_21中断号 */
#define INUM_PIO0_22             63   /**< \brief PIO0_22中断号 */
#define INUM_PIO0_23             64   /**< \brief PIO0_23中断号 */
#define INUM_PIO0_24             65   /**< \brief PIO0_24中断号 */
#define INUM_PIO0_25             66   /**< \brief PIO0_25中断号 */
#define INUM_PIO0_26             67   /**< \brief PIO0_26中断号 */
#define INUM_PIO0_27             68   /**< \brief PIO0_27中断号 */
#define INUM_PIO0_28             69   /**< \brief PIO0_28中断号 */
#define INUM_PIO0_29             70   /**< \brief PIO0_29中断号 */
#define INUM_PIO0_30             71   /**< \brief PIO0_30中断号 */
#define INUM_PIO0_31             72   /**< \brief PIO0_31中断号 */
             
#define INUM_PIO1_0              73   /**< \brief PIO1_0中断号  */
#define INUM_PIO1_1              74   /**< \brief PIO1_1中断号  */
#define INUM_PIO1_2              75   /**< \brief PIO1_2中断号  */
#define INUM_PIO1_3              76   /**< \brief PIO1_3中断号  */
#define INUM_PIO1_4              77   /**< \brief PIO1_4中断号  */
#define INUM_PIO1_5              78   /**< \brief PIO1_5中断号  */
#define INUM_PIO1_6              79   /**< \brief PIO1_6中断号  */
#define INUM_PIO1_7              80   /**< \brief PIO1_7中断号  */
#define INUM_PIO1_8              81   /**< \brief PIO1_8中断号  */
#define INUM_PIO1_9              82   /**< \brief PIO1_9中断号  */
#define INUM_PIO1_10             83   /**< \brief PIO1_10中断号 */
#define INUM_PIO1_11             84   /**< \brief PIO1_11中断号 */
#define INUM_PIO1_12             85   /**< \brief PIO1_12中断号 */
#define INUM_PIO1_13             86   /**< \brief PIO1_13中断号 */
#define INUM_PIO1_14             87   /**< \brief PIO1_14中断号 */
#define INUM_PIO1_15             88   /**< \brief PIO1_15中断号 */
#define INUM_PIO1_16             89   /**< \brief PIO1_16中断号 */
#define INUM_PIO1_17             90   /**< \brief PIO1_17中断号 */

/** @} */

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __LPC5410X_INUM_H */

/* end of file */

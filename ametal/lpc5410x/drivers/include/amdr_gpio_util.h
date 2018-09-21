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
 * \brief GPIO平台辅助工具宏
 *
 * 该文件被包含于 \sa lpc5410x_pin.h. 其定义了GPIO平台引脚的各个功能。
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
 * \brief 宏定义
 * 
 * bit[31:12] 平台定义
 *
 * bit[21:12] 使能位
 * bit[12]    IOCON bits[2:0] 使能位
 * bit[13]    IOCON bits[5:3] 使能位
 * bit[14]    IOCON bit[5] 使能位
 * bit[15]    IOCON bit[6] 使能位
 * bit[16]    IOCON bit[8] 使能位
 * bit[17]    IOCON bit[9] 使能位
 * bit[18]    IOCON bit[10] 使能位
 * bit[19]    I2C 使能位
 * bit[20]    ADC 使能位
 * bit[20]    配置方向使能位
 *
 * bit[24:22] 功能码
 *
 * bit[25]    配置方向 (禁止I2C功能)
 * bit[30:25] I2C 模式 (I2C须使能)
 *
 * bit[26]    I2C 回转使能 (I2C须使能)
 * bit[27:26] I2C 模式功能码 (禁止I2C功能)
 *
 * bit[28]    反转使能
 * bit[29]    禁止滤波使能
 * bit[30]    回转使能或I2C驱动使能(I2C须使能)
 * bit[31]    开漏使能或I2C滤波使能(I2C须使能)
 */
 
/** 
 * \name IOCON 控制位域
 * @{
 */
 
#define AMDR_GPIO_CON_BIT0               AM_BIT(12)   /**< \brief IOCON bits[2:0] 使能位 */
#define AMDR_GPIO_CON_BIT3               AM_BIT(13)   /**< \brief IOCON bits[5:3] 使能位 */
#define AMDR_GPIO_CON_BIT5               AM_BIT(14)   /**< \brief IOCON bit[5] 使能位    */
#define AMDR_GPIO_CON_BIT6               AM_BIT(15)   /**< \brief IOCON bit[6] 使能位    */
#define AMDR_GPIO_CON_BIT8               AM_BIT(16)   /**< \brief IOCON bit[8] 使能位    */
#define AMDR_GPIO_CON_BIT9               AM_BIT(17)   /**< \brief IOCON bit[9] 使能位    */
#define AMDR_GPIO_CON_BIT10              AM_BIT(18)   /**< \brief IOCON bit[10] 使能位   */

#define AMDR_GPIO_I2CEN_BIT              AM_BIT(19)   /**< \brief I2C 使能位             */
#define AMDR_GPIO_ADCEN_BIT              AM_BIT(20)   /**< \brief ADC 使能位             */
#define AMDR_GPIO_DIREN_BIT              AM_BIT(21)   /**< \brief 配置方向使能位         */


#define AMDR_GPIO_FUNCBITS_START         22           /**< \brief 功能起始位   */
#define AMDR_GPIO_FUNCBITS_LEN           3            /**< \brief 功能码长度   */

/** \brief 置功能码 */
#define AMDR_GPIO_FUNC_CODE(a)          (AM_SBF((a), AMDR_GPIO_FUNCBITS_START) |  \
                                         AMDR_GPIO_CON_BIT0) 

/** \brief 获取功能码 */
#define AMDR_GPIO_FUNC_GET(data)         AM_BITS_GET((data), AMDR_GPIO_FUNCBITS_START, \
                                         AMDR_GPIO_FUNCBITS_LEN)

/** \brief 置ADC功能码 */
#define AMDR_GPIO_ADC_FUNC_CODE(a)      (AM_SBF((a), AMDR_GPIO_FUNCBITS_START) | AMDR_GPIO_ADCEN_BIT)

/** \brief 方向位偏移 */
#define AMDR_GPIO_DIRBIT_OFFSET          25

/** \brief 置方向码 */
#define AMDR_GPIO_DIR_CODE(a)           (AM_SBF((a), AMDR_GPIO_DIRBIT_OFFSET) |  \
                                         AMDR_GPIO_DIREN_BIT)

/** \brief 获取方向码 */
#define AMDR_GPIO_DIR_GET(data)          AM_BIT_GET((data), AMDR_GPIO_DIRBIT_OFFSET)

/** \brief 模式起始位 */
#define AMDR_GPIO_MODEBITS_START         26

/** \brief 模式码长度 */
#define AMDR_GPIO_MODEBITS_LEN           2

/** \brief 置模式码 */
#define AMDR_GPIO_MODE_CODE(a)          (AM_SBF((a), AMDR_GPIO_MODEBITS_START) |       \
                                         AMDR_GPIO_CON_BIT3)

/** \brief 获取模式码 */
#define AMDR_GPIO_MODE_GET(data)         AM_BITS_GET((data), AMDR_GPIO_MODEBITS_START, \
                                         AMDR_GPIO_MODEBITS_LEN)

/** \brief 反转位偏移 */
#define AMDR_GPIO_INVERTBIT_OFFSET       28

/** \brief 置反转码 */
#define AMDR_GPIO_INVERTBIT_CODE(a)     (AM_SBF((a), AMDR_GPIO_INVERTBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT6)

/** \brief 获取反转码 */
#define AMDR_GPIO_INVERTBIT_GET(data)    AM_BIT_GET((data), AMDR_GPIO_INVERTBIT_OFFSET)

/** \brief 滤波位偏移 */
#define AMDR_GPIO_FILTEROFFBIT_OFFSET    29

/** \brief 置滤波吗 */
#define AMDR_GPIO_FILTEROFFBIT_CODE(a)  (AM_SBF((a), AMDR_GPIO_FILTEROFFBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT8)

/** \brief 获取滤波码 */
#define AMDR_GPIO_FILTEROFFBIT_GET(data) AM_BIT_GET((data), AMDR_GPIO_FILTEROFFBIT_OFFSET)

/** \brief 回转位偏移 */
#define AMDR_GPIO_SLEWBIT_OFFSET         30

/** \brief 置回转码 */
#define AMDR_GPIO_SLEWBIT_CODE(a)       (AM_SBF((a), AMDR_GPIO_SLEWBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT9)

/** \brief 获取回转码 */
#define AMDR_GPIO_SLEWBIT_GET(data)      AM_BIT_GET((data), AMDR_GPIO_SLEWBIT_OFFSET)

/** \brief 开漏位偏移 */
#define AMDR_GPIO_ODBIT_OFFSET           31

/** \brief 置开漏码 */
#define AMDR_GPIO_ODBIT_CODE(a)         (AM_SBF((a), AMDR_GPIO_ODBIT_OFFSET) |  \
                                         AMDR_GPIO_CON_BIT10)

/** \brief 获取开漏码 */
#define AMDR_GPIO_ODBIT_GET(data)        AM_BIT_GET((data), AMDR_GPIO_ODBIT_OFFSET)

/** @} */

/**
 * \name I2C模式位域
 *
 *  建议I2C的功能配置，为防止与引脚的其他功能冲突，该配置的起始位为25。
 */
 
#define AMDR_GPIO_I2CBITS_OFFSET         25   /**< \brief I2C suggest mode start bit   */
#define AMDR_GPIO_I2CBITS_LEN            6    /**< \brief I2C suggest mode bits length */

/** \brief 置I2C功能码 */
#define AMDR_GPIO_I2C_FUNC_CODE(a)       AM_SBF((a), AMDR_GPIO_I2CBITS_OFFSET)

/** \brief 获取I2C功能码 */
#define AMDR_GPIO_I2C_FUNC_GET(data)     AM_BITS_GET((data), AMDR_GPIO_I2CBITS_OFFSET, \
                                         AMDR_GPIO_I2CBITS_LEN)

/** \brief GPIO 4 mA 驱动 */
#define AMDR_PIO_4MA_DRIVE               AMDR_GPIO_I2C_FUNC_CODE(0x05) | \
                                         AMDR_GPIO_I2CEN_BIT

/** \brief GPIO 20 mA 驱动 */
#define AMDR_PIO_20MA_DRIVE              AMDR_GPIO_I2C_FUNC_CODE(0x15) | \
                                         AMDR_GPIO_I2CEN_BIT  

/** \brief I2C快速/标准模式 */
#define AMDR_FAST_STD_MODE               AMDR_GPIO_I2C_FUNC_CODE(0x0C) |  \
                                         AMDR_GPIO_I2CEN_BIT 

/** \brief I2C超快速模式 */
#define AMDR_FAST_MODE_PLUS              AMDR_GPIO_I2C_FUNC_CODE(0x3C) |  \
                                         AMDR_GPIO_I2CEN_BIT 

/** \brief I2C高速从机模式 */
#define AMDR_HIGH_SPEED_SLAVE            AMDR_GPIO_I2C_FUNC_CODE(0x3C) | \
                                         AMDR_GPIO_I2CEN_BIT 

/** \brief I2C回转位偏移 */
#define AMDR_GPIO_I2CSLEWBIT_OFFSET      26

/** \brief 置I2C回转码 */
#define AMDR_GPIO_I2CSLEWBIT_CODE(a)    (AM_SBF((a), AMDR_GPIO_I2CSLEWBIT_OFFSET) | \
                                         AMDR_GPIO_CON_BIT5)

/** \brief 获取I2C回转码 */
#define AMDR_GPIO_I2CSLEWBIT_GET(data)   AM_BIT_GET((data), AMDR_GPIO_I2CSLEWBIT_OFFSET)

/** \brief 置I2C驱动码 */
#define AMDR_GPIO_I2CDRIVE_CODE(a)       AMDR_GPIO_SLEWBIT_CODE(a)

/** \brief 获取I2C驱动码 */
#define AMDR_GPIO_I2CDRIVE_GET(data)     AMDR_GPIO_SLEWBIT_GET(data)

/** \brief 置I2C滤波码 */
#define AMDR_GPIO_I2CFILTER_CODE(a)      AMDR_GPIO_ODBIT_CODE(a)

/** \brief 获取I2C滤波码 */
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

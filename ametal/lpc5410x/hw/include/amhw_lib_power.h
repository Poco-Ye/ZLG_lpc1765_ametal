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
 * \brief 电源管理/电源控制接口
 *
 * 电源管理库lib_power.lib/lib_power_m0.lib接口函数, 这些电源管理函数用于控制系
 * 电源、设置器件的进入指定的低功耗模式。
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_LIB_POWER_H
#define __AMHW_LIB_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

enum amhw_power_vol_mode;
enum amhw_power_mode;

uint32_t Chip_POWER_GetROMVersion(void);
uint32_t Chip_POWER_SetVoltage(enum amhw_power_vol_mode mode, uint32_t desired_freq);

void Chip_POWER_EnterPowerMode(enum amhw_power_mode mode, uint32_t peripheral_ctrl);
void Chip_POWER_EnterPowerModeIramOnly(uint32_t peripheral_ctrl);


/**
 * \addtogroup amhw_if_lib_power
 * \copydoc amhw_lib_power.h
 * @{
 */

/**
 * \name 电源控制位定义，包括了处理器内核相关和外设的电源控制
 * @{
 */

#define AMHW_POWER_PD_IRC_OSC    (1 << 3)  /**< \brief IRC振荡器输出          */
#define AMHW_POWER_PD_IRC        (1 << 4)  /**< \brief IRC振荡器电源          */
#define AMHW_POWER_PD_FLASH      (1 << 5)  /**< \brief Flash存储器            */
#define AMHW_POWER_PD_BOD_RST    (1 << 7)  /**< \brief 掉电检测复位电源       */
#define AMHW_POWER_PD_BOD_INTR   (1 << 8)  /**< \brief 掉电检测中断电源       */
#define AMHW_POWER_PD_ADC0       (1 << 10) /**< \brief ADC0                   */
#define AMHW_POWER_PD_SRAM0A     (1 << 13) /**< \brief SRAM0起始8KB内存电源   */
#define AMHW_POWER_PD_SRAM0B     (1 << 14) /**< \brief SRAM0余下内存电源      */
#define AMHW_POWER_PD_SRAM1      (1 << 15) /**< \brief SRAM1                  */
#define AMHW_POWER_PD_SRAM2      (1 << 16) /**< \brief SRAM2                  */
#define AMHW_POWER_PD_ROM        (1 << 17) /**< \brief ROM                    */
#define AMHW_POWER_PD_VDDA_ENA   (1 << 19) /**< \brief ADC的VDDA电源          */
#define AMHW_POWER_PD_WDT_OSC    (1 << 20) /**< \brief 看门狗振荡器电源       */
#define AMHW_POWER_PD_SYS_PLL    (1 << 22) /**< \brief PLL0                   */
#define AMHW_POWER_PD_VREFP      (1 << 23) /**< \brief ADC的Vrefp电源         */
#define AMHW_POWER_PD_32K_OSC    (1 << 24) /**< \brief RTC晶体振荡器电源      */

/** @} */

/**
 * \brief 'mode' 输入值定义，用于函数：amhw_power_voltage_set()
 */
typedef enum amhw_power_vol_mode {
    AMHW_POWER_VOL_MODE_LOW_POWER = 0,    /**< \brief 省电模式         */
    AMHW_POWER_VOL_MODE_BALANCED,         /**< \brief 平衡模式         */
    AMHW_POWER_VOL_MODE_HIGH_PERFORMANCE  /**< \brief 高性能模式       */
} amhw_power_vol_mode_t;

/** 'mode' 输入值定义,用于函数：amhw_power_powermode_enter()   */
typedef enum amhw_power_mode {
    AMHW_POWER_MODE_SLEEP = 0,            /**< \brief 睡眠模式        */
    AMHW_POWER_MODE_DEEP_SLEEP,           /**< \brief 深度睡眠模式    */
    AMHW_POWER_MODE_POWER_DOWN,           /**< \brief 掉电模式        */
    AMHW_POWER_MODE_DEEP_POWER_DOWN       /**< \brief 深度掉电模式    */
} amhw_power_mode_t;

/**
 * \brief 得到ROM程序版本号
 * \return ROM程序版本号
 * \note  ROM程序版本号定义
 *        -(0x1100) ：v17.0
 *        -(0x1101) ：v17.1
 *        -(0x1102) ：v17.2
 */
am_static_inline
uint32_t amhw_power_rom_ver_get (void)
{
    return Chip_POWER_GetROMVersion();
}

/**
 * \brief 设置系统电源模式
 *
 * \param[in] mode : 电源模式
 * \param[in] freq : 系统频率(Hz)
 *
 * \retval 0 : 成功
 * \retval 1 : 模式非法
 * \retval 2 : 时钟频率过高
 *
 * \note 该函数将会根据系统时钟频率和电源模式调整系统电压至最佳状态，一旦系统频
 *       率发生变化，该函数应该被调用。
 */
am_static_inline
uint32_t amhw_power_voltage_set (amhw_power_vol_mode_t mode, uint32_t freq)
{
    return Chip_POWER_SetVoltage(mode, freq);
}

/**
 * \brief 进入指定的低功耗模式
 *
 * \param[in] mode            : 低功耗模式
 * \param[in] peripheral_ctrl : 进入低功耗模式后，需要保持上电状态的外设
 *
 * \return 无
 * \note  'peripheral_ctrl' 值是AMHW_POWER_PD_*宏值或多个AMHW_POWER_PD_*宏的或值.
 *
 * 下面描述了那些外设在特定低功耗模式中是出于掉电状态的，设置相对应的标志可以使该
 * 外设在睡眠模式期间仍然保持上电状态。 
 *
 * 1. 睡眠模式（AMHW_POWER_MODE_SLEEP）中，没有外设会被关闭电源。
 * 2. 深度睡眠模式(AMHW_POWER_MODE_DEEP_SLEEP)中，下列外设会被关闭电源：
 *    - AMHW_POWER_PD_IRC_OSC
 *    - AMHW_POWER_PD_IRC
 *    - AMHW_POWER_PD_FLASH
 *    - AMHW_POWER_PD_BOD_INTR
 *    - AMHW_POWER_PD_ADC0
 *    - AMHW_POWER_PD_ROM
 *    - AMHW_POWER_PD_VDDA_ENA
 *    - AMHW_POWER_PD_SYS_PLL
 *    - AMHW_POWER_PD_VREFP
 * 3. 掉电模式(AMHW_POWER_MODE_POWER_DOWN)中，下列外设会被关闭电源：
 *    - AMHW_POWER_PD_IRC_OSC
 *    - AMHW_POWER_PD_IRC
 *    - AMHW_POWER_PD_FLASH
 *    - AMHW_POWER_PD_BOD_RST
 *    - AMHW_POWER_PD_BOD_INTR
 *    - AMHW_POWER_PD_ADC0
 *    - AMHW_POWER_PD_SRAMHW0A
 *    - AMHW_POWER_PD_SRAMHW0B
 *    - AMHW_POWER_PD_SRAMHW1
 *    - AMHW_POWER_PD_SRAMHW2
 *    - AMHW_POWER_PD_ROM
 *    - AMHW_POWER_PD_VDDA_ENA
 *    - AMHW_POWER_PD_WDT_OSC
 *    - AMHW_POWER_PD_SYS_PLL
 *    - AMHW_POWER_PD_VREFP
 *    - AMHW_POWER_PD_32K_OSC
 * 4. 深度掉电(AMHW_POWER_MODE_DEEP_POWER_DOWN)模式中，所有外设被关闭电源
 *
 * 例如，如果需要利用RTC将器件从掉电模式中唤醒，则需要保持RTC模块上电：
 *  am_power_mode_enter(AMHW_POWER_MODE_POWER_DOWN, AMHW_POWER_PD_32K_OSC)。
 */
am_static_inline
void amhw_power_mode_enter (amhw_power_mode_t mode, uint32_t peripheral_ctrl)
{
    Chip_POWER_EnterPowerMode(mode, peripheral_ctrl);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_LIB_POWER_H */

/* end of file */

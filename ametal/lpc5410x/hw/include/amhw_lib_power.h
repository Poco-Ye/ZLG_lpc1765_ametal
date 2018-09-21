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
 * \brief ��Դ����/��Դ���ƽӿ�
 *
 * ��Դ�����lib_power.lib/lib_power_m0.lib�ӿں���, ��Щ��Դ���������ڿ���ϵ
 * ��Դ�����������Ľ���ָ���ĵ͹���ģʽ��
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
 * \name ��Դ����λ���壬�����˴������ں���غ�����ĵ�Դ����
 * @{
 */

#define AMHW_POWER_PD_IRC_OSC    (1 << 3)  /**< \brief IRC�������          */
#define AMHW_POWER_PD_IRC        (1 << 4)  /**< \brief IRC������Դ          */
#define AMHW_POWER_PD_FLASH      (1 << 5)  /**< \brief Flash�洢��            */
#define AMHW_POWER_PD_BOD_RST    (1 << 7)  /**< \brief �����⸴λ��Դ       */
#define AMHW_POWER_PD_BOD_INTR   (1 << 8)  /**< \brief �������жϵ�Դ       */
#define AMHW_POWER_PD_ADC0       (1 << 10) /**< \brief ADC0                   */
#define AMHW_POWER_PD_SRAM0A     (1 << 13) /**< \brief SRAM0��ʼ8KB�ڴ��Դ   */
#define AMHW_POWER_PD_SRAM0B     (1 << 14) /**< \brief SRAM0�����ڴ��Դ      */
#define AMHW_POWER_PD_SRAM1      (1 << 15) /**< \brief SRAM1                  */
#define AMHW_POWER_PD_SRAM2      (1 << 16) /**< \brief SRAM2                  */
#define AMHW_POWER_PD_ROM        (1 << 17) /**< \brief ROM                    */
#define AMHW_POWER_PD_VDDA_ENA   (1 << 19) /**< \brief ADC��VDDA��Դ          */
#define AMHW_POWER_PD_WDT_OSC    (1 << 20) /**< \brief ���Ź�������Դ       */
#define AMHW_POWER_PD_SYS_PLL    (1 << 22) /**< \brief PLL0                   */
#define AMHW_POWER_PD_VREFP      (1 << 23) /**< \brief ADC��Vrefp��Դ         */
#define AMHW_POWER_PD_32K_OSC    (1 << 24) /**< \brief RTC����������Դ      */

/** @} */

/**
 * \brief 'mode' ����ֵ���壬���ں�����amhw_power_voltage_set()
 */
typedef enum amhw_power_vol_mode {
    AMHW_POWER_VOL_MODE_LOW_POWER = 0,    /**< \brief ʡ��ģʽ         */
    AMHW_POWER_VOL_MODE_BALANCED,         /**< \brief ƽ��ģʽ         */
    AMHW_POWER_VOL_MODE_HIGH_PERFORMANCE  /**< \brief ������ģʽ       */
} amhw_power_vol_mode_t;

/** 'mode' ����ֵ����,���ں�����amhw_power_powermode_enter()   */
typedef enum amhw_power_mode {
    AMHW_POWER_MODE_SLEEP = 0,            /**< \brief ˯��ģʽ        */
    AMHW_POWER_MODE_DEEP_SLEEP,           /**< \brief ���˯��ģʽ    */
    AMHW_POWER_MODE_POWER_DOWN,           /**< \brief ����ģʽ        */
    AMHW_POWER_MODE_DEEP_POWER_DOWN       /**< \brief ��ȵ���ģʽ    */
} amhw_power_mode_t;

/**
 * \brief �õ�ROM����汾��
 * \return ROM����汾��
 * \note  ROM����汾�Ŷ���
 *        -(0x1100) ��v17.0
 *        -(0x1101) ��v17.1
 *        -(0x1102) ��v17.2
 */
am_static_inline
uint32_t amhw_power_rom_ver_get (void)
{
    return Chip_POWER_GetROMVersion();
}

/**
 * \brief ����ϵͳ��Դģʽ
 *
 * \param[in] mode : ��Դģʽ
 * \param[in] freq : ϵͳƵ��(Hz)
 *
 * \retval 0 : �ɹ�
 * \retval 1 : ģʽ�Ƿ�
 * \retval 2 : ʱ��Ƶ�ʹ���
 *
 * \note �ú����������ϵͳʱ��Ƶ�ʺ͵�Դģʽ����ϵͳ��ѹ�����״̬��һ��ϵͳƵ
 *       �ʷ����仯���ú���Ӧ�ñ����á�
 */
am_static_inline
uint32_t amhw_power_voltage_set (amhw_power_vol_mode_t mode, uint32_t freq)
{
    return Chip_POWER_SetVoltage(mode, freq);
}

/**
 * \brief ����ָ���ĵ͹���ģʽ
 *
 * \param[in] mode            : �͹���ģʽ
 * \param[in] peripheral_ctrl : ����͹���ģʽ����Ҫ�����ϵ�״̬������
 *
 * \return ��
 * \note  'peripheral_ctrl' ֵ��AMHW_POWER_PD_*��ֵ����AMHW_POWER_PD_*��Ļ�ֵ.
 *
 * ������������Щ�������ض��͹���ģʽ���ǳ��ڵ���״̬�ģ��������Ӧ�ı�־����ʹ��
 * ������˯��ģʽ�ڼ���Ȼ�����ϵ�״̬�� 
 *
 * 1. ˯��ģʽ��AMHW_POWER_MODE_SLEEP���У�û������ᱻ�رյ�Դ��
 * 2. ���˯��ģʽ(AMHW_POWER_MODE_DEEP_SLEEP)�У���������ᱻ�رյ�Դ��
 *    - AMHW_POWER_PD_IRC_OSC
 *    - AMHW_POWER_PD_IRC
 *    - AMHW_POWER_PD_FLASH
 *    - AMHW_POWER_PD_BOD_INTR
 *    - AMHW_POWER_PD_ADC0
 *    - AMHW_POWER_PD_ROM
 *    - AMHW_POWER_PD_VDDA_ENA
 *    - AMHW_POWER_PD_SYS_PLL
 *    - AMHW_POWER_PD_VREFP
 * 3. ����ģʽ(AMHW_POWER_MODE_POWER_DOWN)�У���������ᱻ�رյ�Դ��
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
 * 4. ��ȵ���(AMHW_POWER_MODE_DEEP_POWER_DOWN)ģʽ�У��������豻�رյ�Դ
 *
 * ���磬�����Ҫ����RTC�������ӵ���ģʽ�л��ѣ�����Ҫ����RTCģ���ϵ磺
 *  am_power_mode_enter(AMHW_POWER_MODE_POWER_DOWN, AMHW_POWER_PD_32K_OSC)��
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

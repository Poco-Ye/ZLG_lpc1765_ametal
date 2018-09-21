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
 * \brief ϵͳ���ƽӿ�
 *
 * 1. ϵͳ���������ã�
 * 2. ��λ���ƣ�
 * 3. ���ѿ��ƣ�
 * 4. BOD�������⣩���ã�
 * 5. �߾���ʱ��Ƶ�ʲ�����Ԫ��
 * 6. �豸 ID �Ĵ�����
 *
 * \internal
 * \par History
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_SYSCON_H
#define __AMHW_SYSCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc5410x.h"

/**
 * \addtogroup amhw_if_syscon
 * \copydoc amhw_syscon.h
 * @{
 */

/**
  * \brief ϵͳ���ƼĴ�����ṹ��
  */
typedef struct amhw_syscon {
    __IO uint32_t  sysmemremap;     /**< \brief ϵͳ�ڴ��ض���Ĵ���          */
    __IO uint32_t  ahbmatprio;      /**< \brief AHB���߾������ȼ����üĴ���   */
    __I  uint32_t  reserved[3];     /**< \brief ����������ʹ��                */
    __IO uint32_t  systckcal;       /**< \brief SystickУ׼�Ĵ���             */
    __I  uint32_t  reserved1;       /**< \brief ����������ʹ��                */
    __IO uint32_t  nmisrc;          /**< \brief ���������ж�(NMI)�ж�Դѡ��   */
    __IO uint32_t  asyncapbctrl;    /**< \brief �첽APB���ƼĴ���             */
    __I  uint32_t  reserved2[7];    /**< \brief ����������ʹ��                */
    __IO uint32_t  sysrststat;      /**< \brief ϵͳ��λ״̬�Ĵ���            */
    __IO uint32_t  presetctrl0;     /**< \brief ���踴λ���ƼĴ���0           */
    __IO uint32_t  presetctrl1;     /**< \brief ���踴λ���ƼĴ���1           */
    __O  uint32_t  presetctrlset0;  /**< \brief ��λ���踴λ���ƼĴ���0��Ӧλ */
    __O  uint32_t  presetctrlset1;  /**< \brief ��λ���踴λ���ƼĴ���1��Ӧλ */
    __O  uint32_t  presetctrlclr0;  /**< \brief �������踴λ���ƼĴ���0��Ӧλ */
    __O  uint32_t  presetctrlclr1;  /**< \brief �������踴λ���ƼĴ���1��Ӧλ */
    __I  uint32_t  pioporcap[2];    /**< \brief �ϵ縴λ�����PIO״̬         */
    __I  uint32_t  reserved3;       /**< \brief ����������ʹ��                */
    __I  uint32_t  piorescap[2];    /**< \brief ��λ�����PIO״̬             */
    __I  uint32_t  reserved4[4];    /**< \brief ����������ʹ��                */
    __IO uint32_t  mainclksela;     /**< \brief Main A ʱ��Դѡ��Ĵ���       */
    __IO uint32_t  mainclkselb;     /**< \brief Main B ʱ��Դѡ��Ĵ���       */
    __I  uint32_t  reserved5;       /**< \brief ����������ʹ��                */
    __IO uint32_t  adcclksel;       /**< \brief ADC ʱ��Դѡ��Ĵ���          */
    __I  uint32_t  reserved6;       /**< \brief ����������ʹ��                */
    __IO uint32_t  clkoutsela;      /**< \brief CLKOUT Aʱ��Դѡ��            */
    __IO uint32_t  clkoutselb;      /**< \brief CLKOUT Bʱ��Դѡ��            */
    __I  uint32_t  reserved7;       /**< \brief ����������ʹ��                */
    __IO uint32_t  syspllclksel;    /**< \brief PLL ʱ��Դѡ��Ĵ���          */
    __I  uint32_t  reserved8[7];    /**< \brief ����������ʹ��                */
    __IO uint32_t  ahbclkctrl0;     /**< \brief AHBʱ�ӿ��ƼĴ���0            */
    __IO uint32_t  ahbclkctrl1;     /**< \brief AHBʱ�ӿ��ƼĴ���1            */
    __O  uint32_t  ahbclkctrlset0;  /**< \brief ��λAHBʱ�ӿ��ƼĴ���0��Ӧλ  */
    __O  uint32_t  ahbclkctrlset1;  /**< \brief ��λAHBʱ�ӿ��ƼĴ���1��Ӧλ  */
    __O  uint32_t  ahbclkctrlclr0;  /**< \brief ����AHBʱ�ӿ��ƼĴ���0��Ӧλ  */
    __O  uint32_t  ahbclkctrlclr1;  /**< \brief ����AHBʱ�ӿ��ƼĴ���1��Ӧλ  */
    __I  uint32_t  reserved9[2];    /**< \brief ����������ʹ��                */
    __IO uint32_t  systickclkdiv;   /**< \brief SYSTICK ʱ�ӷ�Ƶ�Ĵ���        */
    __I  uint32_t  reserved10[7];   /**< \brief ����������ʹ��                */
    __IO uint32_t  ahbclkdiv;       /**< \brief ϵͳʱ�ӷ�Ƶ�Ĵ���            */
    __I  uint32_t  reserved11;      /**< \brief ����������ʹ��                */
    __IO uint32_t  adcclkdiv;       /**< \brief ADCʱ�ӷ�Ƶ�Ĵ���             */
    __IO uint32_t  clkoutdiv;       /**< \brief CLKOUTʱ�ӷ�Ƶ�Ĵ���          */
    __I  uint32_t  reserved12[4];   /**< \brief ����������ʹ��                */
    __IO uint32_t  freqmectrl;      /**< \brief Ƶ�ʲ�����Ԫ���ƼĴ���        */
    __IO uint32_t  flashcfg;        /**< \brief Flash�ȴ�״̬���üĴ���       */
    __I  uint32_t  reserved13[8];   /**< \brief ����������ʹ��                */
    __IO uint32_t  fifoctrl;        /**< \brief �����豸��FIFOʹ�ܼĴ���      */
    __I  uint32_t  reserved14[14];  /**< \brief ����������ʹ��                */
    __IO uint32_t  ircctrl;         /**< \brief IRC�������ƼĴ���           */
    __I  uint32_t  reserved15[2];   /**< \brief ����������ʹ��                */
    __IO uint32_t  rtcoscctrl;      /**< \brief RTC��������������ƼĴ���   */
    __I  uint32_t  reserved16[7];   /**< \brief ����������ʹ��                */
    __IO uint32_t  syspllctrl;      /**< \brief PLL���ƼĴ���                 */
    __I  uint32_t  syspllstat;      /**< \brief PLL״̬�Ĵ���                 */
    __IO uint32_t  syspllndec;      /**< \brief PLL N ������                  */
    __IO uint32_t  syspllpdec;      /**< \brief PLL P ������                  */
    __IO uint32_t  syspllssctrl0;   /**< \brief PLLƵչ���ƼĴ���0            */
    __IO uint32_t  syspllssctrl1;   /**< \brief PLLƵչ���ƼĴ���1            */
    __I  uint32_t  reserved17[18];  /**< \brief ����������ʹ��                */
    __IO uint32_t  pdruncfg;        /**< \brief ��Դ���ƼĴ���                */
    __O  uint32_t  pdruncfgset;     /**< \brief ��λ��Դ���ƼĴ�������Ӧλ    */
    __O  uint32_t  pdruncfgclr;     /**< \brief �����Դ���ƼĴ�������Ӧλ    */
    __I  uint32_t  reserved18[9];   /**< \brief ����������ʹ��                */
    __IO uint32_t  starterp0;       /**< \brief ʹ�ܻ��ѼĴ���0               */
    __IO uint32_t  starterp1;       /**< \brief ʹ�ܻ��ѼĴ���1               */
    __O  uint32_t  starterpset0;    /**< \brief ��λ���ѼĴ���0����Ӧλ       */
    __O  uint32_t  starterpset1;    /**< \brief ��λ���ѼĴ���1����Ӧλ       */
    __O  uint32_t  starterpclr0;    /**< \brief ���㻽�ѼĴ���0����Ӧλ       */
    __O  uint32_t  starterpclr1;    /**< \brief ���㻽�ѼĴ���1����Ӧλ       */
    __I  uint32_t  reserved19[42];  /**< \brief ����������ʹ��                */
    __IO uint32_t  cpuctrl;         /**< \brief CPU���ƼĴ���                 */
    __IO uint32_t  cpboot;          /**< \brief Э������������ַ              */
    __IO uint32_t  cpstack;         /**< \brief Э��������ջ��ַ              */
    __I  uint32_t  reserved20[58];  /**< \brief ����������ʹ��                */
    __I  uint32_t  jtagidcode;      /**< \brief JTAG ID �Ĵ���                */
    __I  uint32_t  device_id0;      /**< \brief Part ID �Ĵ���                */
    __I  uint32_t  device_id1;      /**< \brief Boot ROM �汾�żĴ���         */
} amhw_syscon_t;

/**
  * \brief �첽ϵͳ���üĴ�����ṹ��
  */
typedef struct amhw_asyncsyscon {
    __IO uint32_t  asyncpresetctrl;    /**< \brief �첽���踴λ���ƼĴ���     */
    __O  uint32_t  asyncpresetctrlset; /**< \brief ��λ�첽���踴λ���ƼĴ��� */
    __O  uint32_t  asyncpresetctrlclr; /**< \brief �����첽���踴λ���ƼĴ��� */
    __I  uint32_t  reserved;           /**< \brief ����������ʹ��             */
    __IO uint32_t  asyncapbclkctrl;    /**< \brief �첽����ʱ�ӿ��ƼĴ���     */
    __O  uint32_t  asyncapbclkctrlset; /**< \brief ��λ�첽����ʱ�ӿ��ƼĴ��� */
    __O  uint32_t  asyncapbclkctrlclr; /**< \brief �����첽����ʱ�ӿ��ƼĴ��� */
    __I  uint32_t  reserved1;          /**< \brief ����������ʹ��             */
    __IO uint32_t  asyncapbclksela;    /**< \brief �첽APBʱ��Դѡ��Ĵ���A   */
    __IO uint32_t  asyncapbclkselb;    /**< \brief �첽APBʱ��Դѡ��Ĵ���B   */
    __IO uint32_t  asyncclkdiv;        /**< \brief �첽APBʱ�ӷ�Ƶ�Ĵ���      */
    __I  uint32_t  reserved2;          /**< \brief ����������ʹ��             */
    __IO uint32_t  frgctrl;            /**< \brief ����С����Ƶ�����ƼĴ���   */
    __I  uint32_t  reserved3[4];       /**< \brief ����������ʹ��             */
} amhw_asyncsyscon_t;

/**
 * \brief ϵͳ�ڴ���ӳ�䣬������ӳ���ж�������
 */
typedef enum amhw_syscon_bootmode_remap {

    /** \brief �ж���������ӳ��������ROM��  */
    AM_SYSYCON_REMAP_BOOTROM_MODE = 0,

    /** \brief �ж���������ӳ����SRAM��     */
    AM_SYSYCON_REMAP_SRAM_MODE,

    /** \brief �ж���������ӳ����FLASH��    */
    AM_SYSYCON_REMAP_FLASH_MODE,
} amhw_syscon_bootmode_remap_t;

/**
 * \brief �������ͣ���������AHB���ߵ����ȼ�
 */
typedef enum am_ahb_bus_type {
    AM_AHB_BUS_ICODE = 0,    /**< \brief I-Code ����      */
    AM_AHB_BUS_DCODE = 2,    /**< \brief D-Code ����      */
    AM_AHB_BUS_SYS   = 4,    /**< \brief ϵͳ ����        */
    AM_AHB_BUS_DMA   = 8,    /**< \brief DMA������ ����   */
    AM_AHB_BUS_FIFO  = 14,   /**< \brief FIFO ����        */
    AM_AHB_BUS_M0    = 16    /**< \brief Cortex-M0+ ����  */
} am_ahb_bus_type_t;

/**
 * \brief ��ӳ���ж�������
 * \param[in] remap : ѡ����ӳ���������ڴ���
 * \return ��
 */
am_static_inline
void amhw_syscon_remap_set (amhw_syscon_bootmode_remap_t remap)
{
    AMHW_SYSCON->sysmemremap = (uint32_t)remap;
}

/**
 * \brief ��ȡ�ж����������ӳ��ֵ
 * \return �ж����������ӳ��ֵ
 */
am_static_inline
amhw_syscon_bootmode_remap_t amhw_syscon_remap_get (void)
{
    return (amhw_syscon_bootmode_remap_t)AMHW_SYSCON->sysmemremap;
}

/**
 * \brief ����������AHB���߾����е����ȼ�
 *
 * \param[in] bus_type : ���������ȼ�����������
 * \param[in] priority : ���ȼ�ֵ����Ч��Χ��0 ~ 3(������ȼ�)
 *
 * \return ��
 *
 * \note �����ȼ�ֵ��ͬʱ�����нϵ� master num ֵ�����߾��и��ߵ����ȼ���һ�ֵ�
 *       �͵������ǽ� Cortex-M4 D-code ��������Ϊ������ȼ�����������I-Code���ߡ�
 *       �������е����߹���һ�������ȼ���
 *             bus_type     |    master num
 *       ------------------ | ----------------
 *        AM_AHB_BUS_ICODE  |        0
 *        AM_AHB_BUS_DCODE  |        1
 *        AM_AHB_BUS_SYS    |        2
 *        AM_AHB_BUS_DMA    |        5
 *        AM_AHB_BUS_FIFO   |        9
 *        AM_AHB_BUS_M0     |        10
 *
 */
void amhw_syscon_ahb_priority_set(am_ahb_bus_type_t bus_type, uint8_t priority);

/**
 * \brief ����Systick��У׼ֵ
 * \param[in] systickcal_val : Systick��У׼ֵ
 * \return ��
 */
am_static_inline
void amhw_syscon_systickcal_set (uint32_t systickcal_val)
{
    AMHW_SYSCON->systckcal = systickcal_val;
}

/**
 * \name ����ʹ����Ӧ�˵Ĳ��������жϣ�NMI��
 * @{
 */

/** \brief Enable the Non-Maskable Interrupt M0 (NMI) source */
#define AMHW_SYSCON_NMISRC_M0_ENABLE   ((uint32_t) 1 << 30)

/** \brief Enable the Non-Maskable Interrupt M4 (NMI) source */
#define AMHW_SYSCON_NMISRC_M4_ENABLE   ((uint32_t) 1 << 31)

/** @} */

/**
 * \brief ���ò��������ж�Դ
 * \param[in] intsrc : ����NMI���жϺţ�IRQ number��
 * \return ��
 * \note NMI�ж�Դ��ʱ���Ǵ��ڽ�ֹ״̬�ģ�����ʹ��amhw_syscon_nmisrc_enable()����
 *       ʹ������NMI�ж�Դ���жϡ�
 */
void amhw_syscon_nmisrc_set(uint32_t intsrc);

/**
 * \brief ʹ��NMI�ж�Դ���ж�
 * \return ��
 */
void amhw_syscon_nmisrc_enable(void);

/**
 * \brief ����NMI�ж�Դ���ж�
 * \return ��
 */
void amhw_syscon_nmisrc_disable(void);

/**
 * \brief ʹ���첽APB���첽APB��ϵͳ
 * \return ��
 * \note  �����κ��첽����֮ǰ������ȷ���ú����ѱ�����
 */
am_static_inline
void amhw_syscon_async_enable (void)
{
    AMHW_SYSCON->asyncapbctrl = 0x01;
}

/**
 * \brief �����첽APB���첽APB��ϵͳ
 * \return ��
 */
am_static_inline
void amhw_syscon_async_disable (void)
{
    AMHW_SYSCON->asyncapbctrl = 0x00;
}

/**
 * \brief ���ô���С����Ƶ����ֵ
 *
 * \param[in] fmul : С����Ƶ���ı�����
 * \param[in] fdiv : С����Ƶ���ĳ��� (������0xFF)
 *
 * \return ��
 */
am_static_inline
void amhw_syscon_usart_frgctrl_set (uint8_t fmul, uint8_t fdiv)
{
    AMHW_ASYNCSYSCON->frgctrl = ((uint32_t) fmul << 8) | fdiv;
}

/**
 * \name ϵͳ��λ״ֵ̬
 * @{
 */

#define AMHW_SYSCON_RSTSTAT_POR    (1 << 0)   /**< \brief �ϵ縴λ            */
#define AMHW_SYSCON_RSTSTAT_EXTRST (1 << 1)   /**< \brief �ⲿ�ܽŸ�λ        */
#define AMHW_SYSCON_RSTSTAT_WDT    (1 << 2)   /**< \brief ���Ź���λ          */
#define AMHW_SYSCON_RSTSTAT_BOD    (1 << 3)   /**< \brief �����⸴λ        */
#define AMHW_SYSCON_RSTSTAT_SYSRST (1 << 4)   /**< \brief �����λ            */

/** @} */

/**
 * \brief ��ȡϵͳ��λ״̬
 * \return AMHW_SYSCON_RSTSTAT_* ��ֵ����AMHW_SYSCON_RSTSTAT_*��Ļ�OR��ֵ
 *         (#AMHW_SYSCON_RSTSTAT_POR)
 */
am_static_inline
uint32_t amhw_syscon_rst_stat_get (void)
{
    return AMHW_SYSCON->sysrststat;
}

/**
 * \brief ���ϵͳ��λ״̬
 * \param[in] reset : AMHW_SYSCON_RSTSTAT_* ��ֵ����AMHW_SYSCON_RSTSTAT_*���
                      ��OR��ֵ(#AMHW_SYSCON_RSTSTAT_POR)
 * \return ��
 */
am_static_inline
void amhw_syscon_rst_stat_clr (uint32_t reset)
{
    AMHW_SYSCON->sysrststat = reset;
}

/**
 * \brief �������踴λ��ö��ֵ
 */
typedef enum amhw_syscon_periph_reset {
    AMHW_RESET_FLASH = 7,          /**< \brief FLASH������                 */
    AMHW_RESET_FMC,                /**< \brief FLASH������                 */
    AMHW_RESET_INMUX = 11,         /**< \brief ���븴��(INPUT MUX)         */
    AMHW_RESET_IOCON = 13,         /**< \brief IO������(IOCON)             */
    AMHW_RESET_GPIO0,              /**< \brief GPIO �˿� 0(GPIO0)          */
    AMHW_RESET_GPIO1,              /**< \brief GPIO �˿� 1(GPIO1)          */
    AMHW_RESET_PINT = 18,          /**< \brief �ܽ��ж�                    */
    AMHW_RESET_GINT,               /**< \brief �������ж� (GINT)           */
    AMHW_RESET_DMA,                /**< \brief DMA                         */
    AMHW_RESET_CRC,                /**< \brief ѭ������У��(CRC)           */
    AMHW_RESET_WWDT,               /**< \brief ���Ź�                      */
    AMHW_RESET_RTC,                /**< \brief ʵʱʱ��                    */
    AMHW_RESET_MAILBOX = 26,       /**< \brief ˫��ͨ������                */
    AMHW_RESET_ADC0,               /**< \brief ADC0                        */

    AMHW_RESET_MRT = 32 + 0,       /**< \brief ��Ƶ�ʶ�ʱ��(MRT)           */
    AMHW_RESET_RIT,                /**< \brief ���ظ��ж϶�ʱ����RIT��     */
    AMHW_RESET_SCT0,               /**< \brief ״̬�ɱ�̶�ʱ��0           */
    AMHW_RESET_FIFO = 32 + 9,      /**< \brief ϵͳ FIFO                   */
    AMHW_RESET_UTICK,              /**< \brief Micro-tick Timer            */
    AMHW_RESET_TIMER2 = 32 + 22,   /**< \brief ��ʱ��2                     */
    AMHW_RESET_TIMER3 = 32 + 26,   /**< \brief ��ʱ��3                     */
    AMHW_RESET_TIMER4,             /**< \brief ��ʱ��4                     */
 
    AMHW_RESET_USART0 = 128 + 1,   /**< \brief ����0                       */
    AMHW_RESET_USART1,             /**< \brief ����1                       */
    AMHW_RESET_USART2,             /**< \brief ����2                       */
    AMHW_RESET_USART3,             /**< \brief ����3                       */
    AMHW_RESET_I2C0,               /**< \brief I2C0                        */
    AMHW_RESET_I2C1,               /**< \brief I2C1                        */
    AMHW_RESET_I2C2,               /**< \brief I2C2                        */
    AMHW_RESET_SPI0 = 128 + 9,     /**< \brief SPI0                        */
    AMHW_RESET_SPI1,               /**< \brief SPI1                        */
    AMHW_RESET_TIMER0 = 128 + 13,  /**< \brief ��ʱ��0                     */
    AMHW_RESET_TIMER1,             /**< \brief ��ʱ��1                     */
    AMHW_RESET_FRG0                /**< \brief ����С����Ƶ������          */
} amhw_syscon_periph_reset_t;

/**
 * \brief ��λһ������
 * \param[in] periph : ��Ҫ��λ������
 * \return ��
 */
void amhw_syscon_periph_reset(amhw_syscon_periph_reset_t periph);

/**
 * \brief ��ȡ�ϵ縴λ���񵽵�IO״̬
 * \param[in] port : IO�˿ںţ�0-GPIO0,1-GPIO1
 * \return �ϵ縴λ���񵽵�IO״̬
 */
am_static_inline
uint32_t amhw_syscon_porcap_stat_get (uint8_t port)
{
    return AMHW_SYSCON->pioporcap[port];
}

/**
 * \brief ��ȡ��λ���񵽵�IO״̬
 * \param[in] port : IO�˿ںţ�0-GPIO0,1-GPIO1
 * \return ��λ���񵽵�IO״̬s
 * \note ����λ�����ϵ縴λʱʹ��
 */
am_static_inline
uint32_t amhw_syscon_rstcap_stat_get (uint8_t port)
{
    return AMHW_SYSCON->piorescap[port];
}

/**
 * \brief ��ʼƵ�ʲ���
 * \return ��
 * \note �ú����������� amhw_inmux_freqmsr_refclk_set() �� amhw_inmux_freqmsr_targclk_set()
 *       �������úòο�ʱ�Ӻ�Ŀ��ʱ��֮��.
 */
am_static_inline
void amhw_syscon_freqmeas_start (void)
{
    AMHW_SYSCON->freqmectrl = 0;
    AMHW_SYSCON->freqmectrl = (1UL << 31);
}

/**
 * \brief ���Ƶ�ʲ����Ƿ����
 * \retval  TRUE  : ����Ƶ�ʲ������
 * \retval  FALSE : ����Ƶ�ʲ���δ���
 */
am_static_inline
bool_t amhw_syscon_freqmsr_complete_chk (void)
{
    return (bool_t) ((AMHW_SYSCON->freqmectrl & (1UL << 31)) == 0);
}

/**
 * \brief �õ�Ƶ�ʲ�����Ԫ����ֵ
 * \return  Ƶ�ʲ�����Ԫ����ֵ(������Ƶ�ʣ���Ҫת��)
 */
am_static_inline
uint32_t amhw_syscon_freqmeas_capval_get (void)
{
    return AMHW_SYSCON->freqmectrl & 0x3FFF;
}

/**
 * \brief �õ�Ƶ�ʲ�����ԪĿ��ʱ�ӵ�Ƶ��
 * \param[in] ref_clkrate : Ƶ�ʲ�����Ԫ�ο�ʱ�ӵ�Ƶ��
 * \return Ƶ�ʲ�����ԪĿ��ʱ�ӵ�Ƶ��
 * \note ���øú���ǰȷ��Ƶ�ʲ����Ѿ����
 */
uint32_t amhw_syscon_freqmeas_targfreq_get(uint32_t ref_clkrate);

/**
 * \brief FLASH����ʱ�䶨��
 */
typedef enum amhw_syscon_flashtim {
    AMHW_SYSCON_FLASH_1CYCLE = 0, /**< \brief Flash ����ʹ��1��CPUʱ��   */
    AMHW_FLASHTIM_20MHZ_CPU  = 0, /**< \brief Flash ����ʹ��1��CPUʱ��   */
    AMHW_SYSCON_FLASH_2CYCLE,     /**< \brief Flash ����ʹ��2��CPUʱ��   */
    AMHW_SYSCON_FLASH_3CYCLE,     /**< \brief Flash ����ʹ��3��CPUʱ��   */
    AMHW_SYSCON_FLASH_4CYCLE,     /**< \brief Flash ����ʹ��4��CPUʱ��   */
    AMHW_SYSCON_FLASH_5CYCLE,     /**< \brief Flash ����ʹ��5��CPUʱ��   */
    AMHW_SYSCON_FLASH_6CYCLE,     /**< \brief Flash ����ʹ��6��CPUʱ��   */
    AMHW_SYSCON_FLASH_7CYCLE,     /**< \brief Flash ����ʹ��7��CPUʱ��   */
    AMHW_SYSCON_FLASH_8CYCLE      /**< \brief Flash ����ʹ��8��CPUʱ��   */
} amhw_syscon_flashtim_t;

/**
 * \brief ����FLASH����ʱ��
 * \param[in] clks : FLASH����ʱ��
 * \return ��
 */
am_static_inline
void amhw_syscon_flashaccess_set (amhw_syscon_flashtim_t clks)
{
    uint32_t tmp;

    tmp = AMHW_SYSCON->flashcfg & ~(0xF << 12);

    AMHW_SYSCON->flashcfg = tmp | ((uint32_t) clks << 12);
}

/**
 * \brief ����ϵͳʱ��Ƶ������FLASH����ʱ��
 * \param[in] freq : ϵͳʱ�ӵ�Ƶ��
 * \return ��
 */
void amhw_syscon_setupflashclocks(uint32_t freq);

/**
 * \name ϵͳ���� FIFO ʹ��λ����
 * @{
 */

#define AMHW_SYSCON_FIFO_U0TXFIFOEN      (1 << 0)  /**< \brief ����0���� FIFO */
#define AMHW_SYSCON_FIFO_U1TXFIFOEN      (1 << 1)  /**< \brief ����1���� FIFO */
#define AMHW_SYSCON_FIFO_U2TXFIFOEN      (1 << 2)  /**< \brief ����2���� FIFO */
#define AMHW_SYSCON_FIFO_U3TXFIFOEN      (1 << 3)  /**< \brief ����3���� FIFO */
#define AMHW_SYSCON_FIFO_SPI0TXFIFOEN    (1 << 4)  /**< \brief SPI0 ���� FIFO */
#define AMHW_SYSCON_FIFO_SPI1TXFIFOEN    (1 << 5)  /**< \brief SPI1 ���� FIFO */
#define AMHW_SYSCON_FIFO_U0RXFIFOEN      (1 << 8)  /**< \brief ����0���� FIFO */
#define AMHW_SYSCON_FIFO_U1RXFIFOEN      (1 << 9)  /**< \brief ����1���� FIFO */
#define AMHW_SYSCON_FIFO_U2RXFIFOEN      (1 << 10) /**< \brief ����2���� FIFO */
#define AMHW_SYSCON_FIFO_U3RXFIFOEN      (1 << 11) /**< \brief ����3���� FIFO */
#define AMHW_SYSCON_FIFO_SPI0RXFIFOEN    (1 << 12) /**< \brief SPI0 ���� FIFO */
#define AMHW_SYSCON_FIFO_SPI1RXFIFOEN    (1 << 13) /**< \brief SPI1 ���� FIFO */

/** @} */

/**
 * \brief ʹ��ָ�������ϵͳFIFO
 * \param[in] en_mask : AMHW_SYSCON_FIFO_* ��ֵ���� AMHW_SYSCON_FIFO_*��� ��
                       ��OR��ֵ  (#AMHW_SYSCON_FIFO_U0TXFIFOEN)
 * \return ��
 */
am_static_inline
void amhw_syscon_fifo_enable (uint32_t en_mask)
{
    AMHW_SYSCON->fifoctrl |= en_mask;
}

/**
 * \brief ����ָ�������ϵͳFIFO
 * \param[in] dis_mask : AMHW_SYSCON_FIFO_* ��ֵ���� AMHW_SYSCON_FIFO_*��� ��
                       ��OR��ֵ  (#AMHW_SYSCON_FIFO_U0TXFIFOEN)
 * \return ��
 */
am_static_inline
void amhw_syscon_fifo_disable (uint32_t dis_mask)
{
    AMHW_SYSCON->fifoctrl &= ~dis_mask;
}

/**
 * \name ��Դ����λ����(0 = powered, 1 = powered down)
 * @{
 */

#define AMHW_SYSCON_PD_IRC_OSC    (1 << 3)     /**< \brief IRC �������     */
#define AMHW_SYSCON_PD_IRC        (1 << 4)     /**< \brief IRC ����         */
#define AMHW_SYSCON_PD_FLASH      (1 << 5)     /**< \brief Flash              */
#define AMHW_SYSCON_PD_BOD_RST    (1 << 7)     /**< \brief �����⸴λ��Ԫ   */
#define AMHW_SYSCON_PD_BOD_INTR   (1 << 8)     /**< \brief �������жϵ�Ԫ   */
#define AMHW_SYSCON_PD_ADC0       (1 << 10)    /**< \brief ADC0               */
#define AMHW_SYSCON_PD_SRAM0A     (1 << 13)    /**< \brief SRAM0��ʼ��8KB�ڴ� */
#define AMHW_SYSCON_PD_SRAM0B     (1 << 14)    /**< \brief SRAM0��ʼ8KB֮����ڴ� */
#define AMHW_SYSCON_PD_SRAM1      (1 << 15)    /**< \brief SRAM1              */
#define AMHW_SYSCON_PD_SRAM2      (1 << 16)    /**< \brief SRAM2              */
#define AMHW_SYSCON_PD_ROM        (1 << 17)    /**< \brief ROM                */
#define AMHW_SYSCON_PD_VDDA_ENA   (1 << 19)    /**< \brief ADC��VDDA����      */
#define AMHW_SYSCON_PD_WDT_OSC    (1 << 20)    /**< \brief ���Ź�������Դ   */
#define AMHW_SYSCON_PD_SYS_PLL    (1 << 22)    /**< \brief PLL0               */
#define AMHW_SYSCON_PD_VREFP      (1 << 23)    /**< \brief ADC��VREFP����     */
#define AMHW_SYSCON_PD_32K_OSC    (1 << 24)    /**< \brief 32 kHz RTC ����  */

/** @} */

/**
 * \brief �õ���ǰ�ĵ�Դ���ƼĴ���״̬
 * \return  AMHW_SYSCON_PD_* ��ֵ���� AMHW_SYSCON_PD_*��� ��OR��ֵ
            (#AMHW_SYSCON_PD_IRC)
 * \note  ��ӦλΪ�ߵ�ƽ����������δ���磬�͵�ƽ��������
 */
am_static_inline
uint32_t amhw_syscon_powerstat_get (void)
{
    return AMHW_SYSCON->pdruncfg;
}

/**
 * \brief �ر������Դ
 * \param[in] powerdownmask ��AMHW_SYSCON_PD_* ��ֵ���� AMHW_SYSCON_PD_*���
                              ��OR��ֵ(#AMHW_SYSCON_PD_IRC)
 * \return ��
 */
am_static_inline
void amhw_syscon_powerdown (uint32_t powerdownmask)
{
    AMHW_SYSCON->pdruncfgset = powerdownmask;
}

/**
 * \brief �������Դ
 * \param[in] powerupmask ��AMHW_SYSCON_PD_* ��ֵ���� AMHW_SYSCON_PD_*���
                            ��OR��ֵ(#AMHW_SYSCON_PD_IRC)
 * \return ��
 */
void amhw_syscon_powerup(uint32_t powerupmask);

/**
 * \brief ���ָ�������Ƿ��ϵ�
 * \param[in] powermask : AMHW_SYSCON_PD_* ��ֵ
 * \retval    TRUE      : �������ϵ�
 * \retval    FALSE     : ����δ�ϵ�
 */
am_static_inline
bool_t amhw_syscon_power_check (uint32_t powermask)
{
    return (bool_t)((AMHW_SYSCON->pdruncfg & powermask) == 0);
}

/**
 * \brief ö��ֵ������ʹ�ܻ��߽��������жϵĻ����߼�
 * 
 *  ���ʹ����ĳ����Ļ����߼�������ж��ܹ���оƬ�����˯��ģʽ�͵���ģʽ����
 */
typedef enum amhw_syscon_wakeup {
    AMHW_SYSCON_STARTER_WWDT = 0,        /**< \brief ���Ź�(WWDT)             */
    AMHW_SYSCON_STARTER_BOD,             /**< \brief ������(BOD)            */
    AMHW_SYSCON_STARTER_DMA = 3,         /**< \brief DMA                      */
    AMHW_SYSCON_STARTER_GINT0,           /**< \brief GINT0                    */
    AMHW_SYSCON_STARTER_PINT0,           /**< \brief PINT0                    */
    AMHW_SYSCON_STARTER_PINT1,           /**< \brief PINT1                    */
    AMHW_SYSCON_STARTER_PINT2,           /**< \brief PINT2                    */
    AMHW_SYSCON_STARTER_PINT3,           /**< \brief PINT3                    */
    AMHW_SYSCON_STARTER_UTICK,           /**< \brief UTICK(Micro-tick timer)  */
    AMHW_SYSCON_STARTER_MRT,             /**< \brief MRT                      */
    AMHW_SYSCON_STARTER_TIMER0,          /**< \brief ��ʱ��0                  */
    AMHW_SYSCON_STARTER_TIMER1,          /**< \brief ��ʱ��1                  */
    AMHW_SYSCON_STARTER_TIMER2,          /**< \brief ��ʱ��2                  */
    AMHW_SYSCON_STARTER_TIMER3,          /**< \brief ��ʱ��3                  */
    AMHW_SYSCON_STARTER_TIMER4,          /**< \brief ��ʱ��4                  */
    AMHW_SYSCON_STARTER_SCT0,            /**< \brief SCT0                     */
    AMHW_SYSCON_STARTER_USART0,          /**< \brief ����0                    */
    AMHW_SYSCON_STARTER_USART1,          /**< \brief ����1                    */
    AMHW_SYSCON_STARTER_USART2,          /**< \brief ����2                    */
    AMHW_SYSCON_STARTER_USART3,          /**< \brief ����3                    */
    AMHW_SYSCON_STARTER_I2C0,            /**< \brief I2C0                     */
    AMHW_SYSCON_STARTER_I2C1,            /**< \brief I2C1                     */
    AMHW_SYSCON_STARTER_I2C2,            /**< \brief I2C2                     */
    AMHW_SYSCON_STARTER_SPI0,            /**< \brief SPI0                     */
    AMHW_SYSCON_STARTER_SPI1,            /**< \brief SPI1                     */
    AMHW_SYSCON_STARTER_ADC0_SEQA,       /**< \brief ADC0_SEQA                */
    AMHW_SYSCON_STARTER_ADC0_SEQB,       /**< \brief ADC0_SEQB                */
    AMHW_SYSCON_STARTER_ADC0_THCMP,      /**< \brief ADC0_THCMP               */
    AMHW_SYSCON_STARTER_RTC,             /**< \brief ʵʱʱ��(RTC)            */
    AMHW_SYSCON_STARTER_MAILBOX = 31,    /**< \brief ˫��ͨ������             */
    /* ������M4������Ч */
    AMHW_SYSCON_STARTER_GINT1 = 32,      /**< \brief GINT1                    */
    AMHW_SYSCON_STARTER_PINT4,           /**< \brief PINT4                    */
    AMHW_SYSCON_STARTER_PINT5,           /**< \brief PINT5                    */
    AMHW_SYSCON_STARTER_PINT6,           /**< \brief PINT6                    */
    AMHW_SYSCON_STARTER_PINT7,           /**< \brief PINT7                    */
    AMHW_SYSCON_STARTER_RIT = 32 + 8,    /**< \brief RIT                      */
} amhw_syscon_wakeup_t;

/**
 * \brief ʹ������Ļ����߼�
 * \param[in] periph_id :  AMHW_SYSCON_STARTER_* ��ֵ(#AMHW_SYSCON_STARTER_WWDT)
 * \return ��
 */
am_static_inline
void amhw_syscon_wakeup_enable (amhw_syscon_wakeup_t periph_id)
{
    uint32_t pid = (uint32_t)periph_id;

    if (pid < 32) {
        AMHW_SYSCON->starterpset0 = (1 << pid);
    } else {
        AMHW_SYSCON->starterpset1 = (1 << (pid - 32));
    }
}

/**
 * \brief ��������Ļ����߼�
 * \param[in] periph_id :  AMHW_SYSCON_STARTER_* ��ֵ(#AMHW_SYSCON_STARTER_WWDT)
 * \return ��
 */
am_static_inline
void amhw_syscon_wakeup_disable (amhw_syscon_wakeup_t periph_id)
{
    uint32_t pid = (uint32_t) periph_id;

    if (pid < 32) {
        AMHW_SYSCON->starterpclr0 = (1 << pid);
    }
    else {
        AMHW_SYSCON->starterpclr1 = (1 << (pid - 32));
    }
}

/**
 * \brief ��ȡ�豸ID 0
 * \return �豸ID 0
 */
am_static_inline
uint32_t amhw_syscon_deviceid0_get (void)
{
    return AMHW_SYSCON->device_id0;
}

/**
 * \brief ��ȡ�豸ID 1
 * \return �豸ID 1
 */
am_static_inline
uint32_t amhw_syscon_deviceid1_get (void)
{
    return AMHW_SYSCON->device_id1;
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_SYSCON_H */

/* end of file */

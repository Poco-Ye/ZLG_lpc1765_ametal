/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief LPC5410X SPI �û������ļ�
 * \sa amdr_hwconfig_spi.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  jon, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_spi.h"

/**
 * \addtogroup amdr_if_hwconfig_src_spi
 * \copydoc amdr_hwconfig_spi.c
 * @{
 */

/**
 * \brief SPI0 �豸��Ϣ
 */
const  struct amdr_spi_devinfo  g_spi0_devinfo = {
 
    8,                  /**< \brief ����֡����Ϊ8          */
    AM_SPI_CFG_MODE_0,  /**< \brief SPI0 ģʽ0             */
    3000000,            /**< \brief ��ʼ������3MHz         */
    AMHW_SPI0,          /**< \brief ָ��SPI0�Ĵ������ָ��  */ 
    INUM_SPI0,          /**< \brief SPI0 �жϱ��          */
    
};

/** \brief SPI0 �豸ʵ�� */
amdr_spi_dev_t g_spi0_dev;

/** \brief SPI0 ƽ̨��ʼ�� */
void amhw_plfm_spi0_init (void)
{
    am_gpio_pin_cfg(PIO0_13, PIO0_13_SPI0_MISO | PIO0_13_PULLUP);
    am_gpio_pin_cfg(PIO0_12, PIO0_12_SPI0_MOSI | PIO0_12_PULLUP);
    am_gpio_pin_cfg(PIO0_11, PIO0_11_SPI0_SCK  | PIO0_11_PULLUP);
    
    amhw_clock_periph_enable(AMHW_CLOCK_SPI0);
    amhw_syscon_periph_reset(AMHW_RESET_SPI0);
}

/** \brief ���SPI0 ƽ̨��ʼ�� */
void amhw_plfm_spi0_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_SPI0);
    amhw_clock_periph_disable(AMHW_CLOCK_SPI0);
}

/**
 * \brief SPI1 �豸��Ϣ
 */
const  struct amdr_spi_devinfo  g_spi1_devinfo = {
    
    8,                  /**< \brief ����֡����Ϊ8          */
    AM_SPI_CFG_MODE_0,  /**< \brief SPI0 ģʽ0             */
    3000000,            /**< \brief ��ʼ������3MHz         */
    AMHW_SPI1,          /**< \brief ָ��SPI1�Ĵ������ָ��  */
    INUM_SPI1,          /**< \brief SPI1 �жϱ��          */
};

/** \brief SPI1 �豸ʵ�� */
amdr_spi_dev_t g_spi1_dev;

/** \brief SPI1 ƽ̨��ʼ�� */
void amhw_plfm_spi1_init (void)
{
    am_gpio_pin_cfg(PIO1_8, PIO1_8_SPI1_MISO | PIO1_8_PULLUP);
    am_gpio_pin_cfg(PIO1_7, PIO1_7_SPI1_MOSI | PIO1_7_PULLUP);       
    am_gpio_pin_cfg(PIO1_6, PIO1_6_SPI1_SCK  | PIO1_6_PULLUP);
    am_gpio_pin_cfg(PIO1_5, PIO1_5_SPI1_SSELN0 | PIO1_5_PULLUP);
    
    amhw_clock_periph_enable(AMHW_CLOCK_SPI1);
    amhw_syscon_periph_reset(AMHW_RESET_SPI1);
}

/** \brief ���SPI1 ƽ̨��ʼ�� */
void amhw_plfm_spi1_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_SPI1);
    amhw_clock_periph_disable(AMHW_CLOCK_SPI1);
}

/**
 * @}
 */

/* end of file */

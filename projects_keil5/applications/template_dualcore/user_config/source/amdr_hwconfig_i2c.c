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
 * \brief LPC5410X I2C �û������ļ�
 * \sa amdr_hwconfig_i2c.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  jon, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_i2c.h"

/**
 * \addtogroup amdr_if_hwconfig_src_i2c
 * \copydoc amdr_hwconfig_i2c.c
 * @{
 */

/**
 * \name I2C0 ��������������
 * @{
 */
 
#define CLKDIV_VALUE_I2C0  (6)             /**< \brief I2C0 ʱ�ӷ�Ƶ�������� */
#define BUS_SPEED_I2C0     (400000)        /**< \brief I2C0 �������ʲ������� */

/** @} */

/**
 * \brief I2C0 �豸��Ϣ
 */
const  struct amdr_i2c_devinfo  g_i2c0_devinfo = {

    BUS_SPEED_I2C0,
    AMHW_I2C0,                              /**< \brief ָ��I2C0�Ĵ������ָ�� */
    INUM_I2C0,                              /**< \brief I2C0 �жϱ�� */
};
amdr_i2c_dev_t g_i2c0_dev;                  /**< \brief I2C0 �豸ʵ�� */


/** \brief I2C0 ƽ̨��ʼ������ */
void amhw_plfm_i2c0_init (void)
{
    am_gpio_pin_cfg(PIO0_23, PIO0_23_I2C0_SCL | PIO0_23_MOD_PLU_IIC);  
    am_gpio_pin_cfg(PIO0_24, PIO0_24_I2C0_SDA | PIO0_24_MOD_PLU_IIC);

    amhw_clock_periph_enable(AMHW_CLOCK_I2C0);
    amhw_syscon_periph_reset(AMHW_RESET_I2C0);
}

/** \brief ���I2C0 ƽ̨��ʼ������ */
void amhw_plfm_i2c0_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_I2C0);
    amhw_clock_periph_disable(AMHW_CLOCK_I2C0);
}

/**
 * \name I2C1 ��������������
 * @{
 */
 
#define CLKDIV_VALUE_I2C1  (6)          /**< \brief I2C1 ʱ�ӷ�Ƶ�������� */
#define BUS_SPEED_I2C1     (400000)     /**< \brief I2C1 �������ʲ������� */

/** @} */

/**
 * \brief I2C1 �豸��Ϣ
 */
const  struct amdr_i2c_devinfo  g_i2c1_devinfo = {
    
    BUS_SPEED_I2C1,                         /**< \brief I2C1 ����ʱ������ */
                                              
    AMHW_I2C1,                              /**< \brief ָ��I2C1�Ĵ������ָ�� */
    INUM_I2C1,                              /**< \brief I2C1 �жϱ�� */
};                                              
amdr_i2c_dev_t g_i2c1_dev;                  /**< \brief I2C1 �豸ʵ�� */

/** \brief I2C1 ƽ̨��ʼ������ */
void amhw_plfm_i2c1_init (void)
{
    am_gpio_pin_cfg(PIO0_25, PIO0_25_I2C1_SCL | PIO0_25_MOD_PLU_IIC);  
    am_gpio_pin_cfg(PIO0_26, PIO0_26_I2C1_SDA | PIO0_26_MOD_PLU_IIC);

    amhw_clock_periph_enable(AMHW_CLOCK_I2C1);
    amhw_syscon_periph_reset(AMHW_RESET_I2C1);
}

/** \brief ���I2C1 ƽ̨��ʼ������ */
void amhw_plfm_i2c1_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_I2C1);
    amhw_clock_periph_disable(AMHW_CLOCK_I2C1);
}

/**
 * \name I2C2 ��������������
 * @{
 */
 
#define CLKDIV_VALUE_I2C2  (6)            /**< \brief I2C2 ʱ�ӷ�Ƶ�������� */
#define BUS_SPEED_I2C2     (400000)       /**< \brief I2C2 �������ʲ������� */

/** @} */

/**
 * \brief I2C2 �豸��Ϣ
 */
const  struct amdr_i2c_devinfo  g_i2c2_devinfo = {

    BUS_SPEED_I2C2,                         /**< \brief I2C2 ����ʱ������ */
                                          
    AMHW_I2C2,                              /**< \brief ָ��I2C2�Ĵ������ָ�� */
    INUM_I2C2,                              /**< \brief I2C2 �жϱ�� */
    
};

amdr_i2c_dev_t g_i2c2_dev;                  /**< \brief I2C2 �豸ʵ�� */


/** \brief I2C2 ƽ̨��ʼ������ */
void amhw_plfm_i2c2_init (void)
{
    am_gpio_pin_cfg(PIO0_27, PIO0_27_I2C2_SCL | PIO0_27_MOD_PLU_IIC);  
    am_gpio_pin_cfg(PIO0_28, PIO0_28_I2C2_SDA | PIO0_28_MOD_PLU_IIC);
    
    amhw_clock_periph_enable(AMHW_CLOCK_I2C2);
    amhw_syscon_periph_reset(AMHW_RESET_I2C2);
}

/** \brief ���I2C2 ƽ̨��ʼ������ */
void amhw_plfm_i2c2_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_I2C2);
    amhw_clock_periph_disable(AMHW_CLOCK_I2C2);
}

/** @} */

/* end of file */

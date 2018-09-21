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
 * \brief LPC5410X GPIO �û������ļ���
 * \sa amdr_hwconfig_gpio.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  asd, first implementation.
 * \endinternal
 */
 
#include "amdr_hwconfig_gpio.h"

/**
 * \addtogroup amdr_if_hwconfig_src_gpio
 * \copydoc amdr_hwconfig_gpio.c
 * @{
 */

/** \brief ���Ŵ�����Ϣ�ڴ� */
static struct amdr_gpio_trigger_info g_gpio_triginfos[PIN_INT_MAX];

/** \brief ���Ŵ�����Ϣӳ�� */
static uint8_t g_gpio_infomap[PIN_INT_MAX];

/** \brief GPIO�豸��Ϣ */
const amdr_gpio_devinfo_t g_gpio_devinfo = {
    
    AMHW_GPIO,                 /**< \brief ָ��GPIO�Ĵ������ָ��     */
    AMHW_IOCON,                /**< \brief ָ��IOCON�Ĵ������ָ��    */
    AMHW_PINT,                 /**< \brief ָ�������жϼĴ������ָ�� */
    AMHW_INMUX,                /**< \brief ָ�����븴�üĴ������ָ�� */
    
    {
        INUM_PIN_INT0,         /**< \brief PINT0�жϺ� */
        INUM_PIN_INT1,         /**< \brief PINT1�жϺ� */
        INUM_PIN_INT2,         /**< \brief PINT2�жϺ� */
        INUM_PIN_INT3,         /**< \brief PINT3�жϺ� */ 
        
#ifdef AM_CORTEX_M4
        
        INUM_PIN_INT4,         /**< \brief PINT4�жϺ� */
        INUM_PIN_INT5,         /**< \brief PINT5�жϺ� */
        INUM_PIN_INT6,         /**< \brief PINT6�жϺ� */
        INUM_PIN_INT7,         /**< \brief PINT7�жϺ� */
        
#endif
    },
    
    PIN_INT_MAX,               /**< \brief GPIO֧�ֵ������жϺ����� */
    g_gpio_infomap,            /**< \brief ���Ŵ�����Ϣӳ��         */
    g_gpio_triginfos           /**< \brief ���Ŵ�����Ϣ�ڴ�         */
};

/** \brief GPIO�豸ʵ�� */
amdr_gpio_dev_t g_gpio_dev;

/** \brief GPIOƽ̨��ʼ�� */
void amhw_plfm_gpio_init (void)
{
    /* ʹ��GPIO�������ʱ�� */
    amhw_clock_periph_enable(AMHW_CLOCK_GPIO0);
    amhw_clock_periph_enable(AMHW_CLOCK_GPIO1);
    amhw_clock_periph_enable(AMHW_CLOCK_IOCON); 
    amhw_clock_periph_enable(AMHW_CLOCK_INMUX);
    amhw_clock_periph_enable(AMHW_CLOCK_PINT);

    /* ��λGPIO������� */
    amhw_syscon_periph_reset(AMHW_RESET_GPIO0);
    amhw_syscon_periph_reset(AMHW_RESET_GPIO1);
    amhw_syscon_periph_reset(AMHW_RESET_IOCON);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_PINT);
}

/** \brief GPIOƽ̨ȥ��ʼ�� */
void amhw_plfm_gpio_deinit (void)
{
    /* ��λGPIO������� */
    amhw_syscon_periph_reset(AMHW_RESET_GPIO0);
    amhw_syscon_periph_reset(AMHW_RESET_GPIO1);
    amhw_syscon_periph_reset(AMHW_RESET_IOCON);
    amhw_syscon_periph_reset(AMHW_RESET_INMUX);
    amhw_syscon_periph_reset(AMHW_RESET_PINT);
    
    /* ����GPIO�������ʱ�� */
    amhw_clock_periph_disable(AMHW_CLOCK_GPIO0);
    amhw_clock_periph_disable(AMHW_CLOCK_GPIO1);
    amhw_clock_periph_disable(AMHW_CLOCK_IOCON); 
    amhw_clock_periph_disable(AMHW_CLOCK_INMUX);
    amhw_clock_periph_disable(AMHW_CLOCK_PINT);
}


/**
 * @}
 */

/* end of file */

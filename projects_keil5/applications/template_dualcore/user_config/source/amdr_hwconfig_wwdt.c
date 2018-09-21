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
 * \brief LPC5410X WWDT �û������ļ� 
 * \sa amdr_hwconfig_wwdt.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_wwdt.h"

/**
 * \addtogroup amdr_if_hwconfig_src_wwdt
 * \copydoc amdr_hwconfig_wwdt.c
 * @{
 */

/** \brief WWDT �豸��Ϣ */
const amdr_wwdt_devinfo_t  g_wwdt_devinfo = {
    AMHW_WWDT,                 /* ָ��WWDT�Ĵ������ָ�� */
};

/** \brief WWDT�豸ʵ��  */
amdr_wwdt_dev_t            g_wwdt_dev;

/** \brief WWDT ƽ̨��ʼ�� */
void amhw_plfm_wwdt_init (void)
{
    /* ʹ�ܲ���λWWDTʱ�� */
    amhw_clock_periph_enable(AMHW_CLOCK_WWDT);
    amhw_syscon_periph_reset(AMHW_RESET_WWDT);
    
    /* �л���WDTʱ��Դ*/
    amhw_syscon_powerup(AMHW_SYSCON_PD_WDT_OSC);

    amhw_clock_wdt_freq_update();
}

/** \brief ���WWDT ƽ̨��ʼ�� */
void amhw_plfm_wwdt_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_WWDT);
    amhw_clock_periph_disable(AMHW_CLOCK_WWDT);
}

/**
 * @}
 */

/* end of file */

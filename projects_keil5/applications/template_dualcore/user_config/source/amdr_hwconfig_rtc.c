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
 * \brief LPC5410X RTC�û������ļ� 
 * \sa amdr_hwconfig_rtc.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_rtc.h"

/**
 * \addtogroup amdr_if_hwconfig_src_rtc
 * \copydoc amdr_hwconfig_rtc.c
 * @{
 */

/** \brief RTC �豸��Ϣ */
const amdr_rtc_devinfo_t  g_rtc_devinfo = {
    AMHW_RTC,                /**< \brief RTC */
};

/** \brief RTC �豸ʵ�� */
amdr_rtc_dev_t            g_rtc_dev;

/** \brief RTCƽ̨��ʼ�� */
void amhw_plfm_rtc_init (void)
{
    /* ʹ�ܲ���λRTCʱ�� */
    amhw_clock_periph_enable(AMHW_CLOCK_RTC);
    amhw_syscon_periph_reset(AMHW_RESET_RTC);
    
     /* �л�ʱ��Դλ32K */
    amhw_syscon_powerup(AMHW_SYSCON_PD_32K_OSC);

    /*
     * ʹ��RTCʱ��Դ
     */
    amhw_clock_rtcosc_enable();
}

/** \brief ���RTCƽ̨��ʼ�� */
void amhw_plfm_rtc_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_RTC);
    amhw_clock_periph_disable(AMHW_CLOCK_RTC);
}

/**
 * @}
 */

/* end of file */

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
 * \brief LPC5410X CRC �û������ļ� 
 * \sa amdr_hwconfig_crc.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_crc.h"

/**
 * \addtogroup amdr_if_hwconfig_src_crc
 * \copydoc amdr_hwconfig_crc.c
 * @{
 */

/** \brief CRC �豸��Ϣ */
const amdr_crc_devinfo_t  g_crc_devinfo = {
    AMHW_CRC,                /** \brief ָ��CRC�Ĵ������ָ�� */
};

/** \brief CRC�豸���� */
amdr_crc_dev_t            g_crc_dev;

/** \brief CRCƽ̨��ʼ�� */
void amhw_plfm_crc_init (void)
{
    /* ʹ�ܲ���λCRCʱ�� */
    amhw_clock_periph_enable(AMHW_CLOCK_CRC);
    amhw_syscon_periph_reset(AMHW_RESET_CRC);
 
}

/** \brief ���CRCƽ̨��ʼ�� */
void amhw_plfm_crc_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_CRC);
    amhw_clock_periph_disable(AMHW_CLOCK_CRC);
}

/**
 * @}
 */

/* end of file */

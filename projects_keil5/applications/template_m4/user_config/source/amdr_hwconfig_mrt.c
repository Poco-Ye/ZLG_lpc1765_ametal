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
 * \brief LPC5410X MRT���ڶ�ʱ���ܵ��û������ļ�
 * \sa amdr_hwconfig_mrt.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_mrt.h"

/**
 * \addtogroup amdr_if_hwconfig_src_mrt
 * \copydoc amdr_hwconfig_mrt.c
 * @{
 */

/** \brief MRT�豸��Ϣ */
const amdr_mrt_devinfo_t  g_mrt_devinfo = {
    AMHW_MRT,                /**< \brief ָ��MRT�Ĵ������ָ�� */
    INUM_MRT,                /**< \brief MRT �жϱ��          */
    4,                       /**< \brief ֧��4��ͨ��           */
};

amdr_mrt_dev_t  g_mrt_dev;   /**< \brief  MRT �豸���� */

/** \brief MRTƽ̨��ʼ�� */
void amhw_plfm_mrt_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_MRT);
    amhw_syscon_periph_reset(AMHW_RESET_MRT);
}

/** \brief ���MRTƽ̨��ʼ�� */
void amhw_plfm_mrt_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_MRT);
    amhw_clock_periph_disable(AMHW_CLOCK_MRT);
}

/**
 * @}
 */

/* end of file */

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
 * \brief LPC5410X RIT ���ڶ�ʱ���ܵ��û������ļ� 
 * \sa amdr_hwconfig_rit.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-12  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_rit.h"

/**
 * \addtogroup amdr_if_hwconfig_src_rit
 * \copydoc amdr_hwconfig_rit.c
 * @{
 */

/** 
 * \brief ����RIT��������M4�ںˣ���RIT��ʱ����ֻ����M4�ں������� 
 */
#ifdef AM_CORTEX_M4

/** \brief RIT�豸��Ϣ */
const amdr_rit_devinfo_t  g_rit_devinfo = {
    AMHW_RIT,                  /**< \brief  ָ��RIT�Ĵ������ָ�� */
    INUM_RIT,                  /**< \brief  RIT�жϱ��           */
};

/** \brief RIT�豸���� */
amdr_rit_dev_t            g_rit_dev;

/** \brief RIT ƽ̨��ʼ�� */
void amhw_plfm_rit_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_RIT);
    amhw_syscon_periph_reset(AMHW_RESET_RIT);
}

/** \brief ���RIT ƽ̨��ʼ�� */
void amhw_plfm_rit_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_RIT);
    amhw_clock_periph_disable(AMHW_CLOCK_RIT);
}

#endif

/**
 * @}
 */

/* end of file */

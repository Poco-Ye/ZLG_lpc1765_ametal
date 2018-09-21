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
 * \brief LPC5410X FIFO �û������ļ� 
 * \sa amdr_hwconfig_fifo.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_fifo.h"

/**
 * \addtogroup amdr_if_hwconfig_src_fifo
 * \copydoc amdr_hwconfig_fifo.c
 * @{
 */

/** \brief FIFOƽ̨��ʼ�� */
void amhw_plfm_fifo_init (void)
{
    /* ʹ�ܲ���λFIFOʱ��  */
    amhw_clock_periph_enable(AMHW_CLOCK_FIFO);
    amhw_syscon_periph_reset(AMHW_RESET_FIFO);
}

/** \brief ���FIFOƽ̨��ʼ�� */
void amhw_plfm_fifo_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_FIFO);
    amhw_clock_periph_disable(AMHW_CLOCK_FIFO);
}

/** @} */

/* end of file */

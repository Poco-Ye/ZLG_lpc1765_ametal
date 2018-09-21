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
 * \brief LPC5410X DMA �û������ļ�
 * \sa amdr_hwconfig_dma.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-22  hbt, first implementation.
 * \endinternal
 */
 
#include "amdr_hwconfig_dma.h"

/**
 * \addtogroup amdr_if_hwconfig_src_dma
 * \copydoc amdr_hwconfig_dma.c
 * @{
 */


/** \brief DMA ͨ���������б�����512�ֽڶ��� */
__align(512) static amhw_dma_xfer_desc_t __g_dma_desc_tab[AMHW_DMA_CHAN_CNT];


/** \brief DMA �豸��Ϣ */
const amdr_dma_devinfo_t g_dma_devinfo = {
    AMHW_DMA,                      /**< \brief ָ��DMA�Ĵ������ָ��          */
    (void *)(&__g_dma_desc_tab),   /**< \brief SRAM ����ַ��������512�ֽڶ��� */
    INUM_DMA                       /**< \brief DMA�жϺ�                      */
};

/** \brief DMA�豸ʵ�� */
amdr_dma_dev_t g_dma_dev;

/** 
 * \brief DMA ƽ̨��ʼ����
 */
void amhw_plfm_dma_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_DMA);
    amhw_syscon_periph_reset(AMHW_RESET_DMA);
}

/** 
 * \brief DMA ƽ̨ȥ��ʼ����
 */
void amhw_plfm_dma_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_DMA);
    amhw_clock_periph_disable(AMHW_CLOCK_DMA);
}


/**
 * @} 
 */

/* end of file */

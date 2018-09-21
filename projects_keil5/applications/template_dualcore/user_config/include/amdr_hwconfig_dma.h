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
 * \brief LPC5410X DMA �û�����ͷ�ļ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  hbt, first implementation.
 * \endinternal
 */
 
#ifndef __AMDR_HWCONFIG_DMA_H
#define __AMDR_HWCONFIG_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ametal.h"
    
/** 
 * \brief DMA ƽ̨��ʼ����
 * \return �ޡ�
 */
void amhw_plfm_dma_init(void);

/** 
 * \brief DMA ƽ̨ȥ��ʼ����
 * \return �ޡ�
 */
void amhw_plfm_dma_deinit(void);


extern const amdr_dma_devinfo_t g_dma_devinfo; /**< \brief DMA�豸��Ϣ */
extern amdr_dma_dev_t           g_dma_dev;     /**< \brief DMA�豸     */

#ifdef __cplusplus
}
#endif

#endif  /* __AMDR_HWCONFIG_DMA_H */

/* end of file */

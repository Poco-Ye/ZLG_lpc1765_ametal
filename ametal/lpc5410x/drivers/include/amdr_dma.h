/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief DMA����������DMA�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.10 14-12-11  hbt, add device and device information.
 * - 1.00 14-12-01  zen, first implementation.
 * \endinternal
 */

#ifndef __AMDR_DMA_H
#define __AMDR_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_dma.h"

/**
 * \addtogroup amdr_if_dma
 * \copydoc amdr_dma.h
 * @{
 */


/**
 * \name ͨ�������жϱ�־ 
 * \anchor amdr_dma_chan_cfg_flags
 * @{
 */

#define AMDR_DMA_INTA         0     /**< \brief �ж�A��־     */
#define AMDR_DMA_INTB         1     /**< \brief �ж�B��־     */
#define AMDR_DMA_INTERR       2     /**< \brief �����жϱ�־  */

/** @} */


/** \brief DMA�жϻص��������� */
typedef void (*amdr_pfn_dma_isr_t)(void *p_arg, void *p_flg);

/** \brief DMA�жϻص�������Ϣ */
struct amdr_dma_int_info {
    
    /** \brief DMA�����ص����� */
    amdr_pfn_dma_isr_t  pfn_isr;

    /** \brief �ص������ĵ�һ����ڲ��� */
    void               *p_arg;
};

/** \brief DMA�豸��Ϣ */
typedef struct amdr_dma_devinfo {
    
    /** \brief ָ��DMA�Ĵ������ָ�� */
    amhw_dma_t *p_hw_dma;
    
    /** \brief SRAM ����ַ��������512�ֽڶ��� */
    void       *p_sram_base;
    
    /** \brief DMA�жϺ� */
    uint8_t     inum;
    
} amdr_dma_devinfo_t;

/**
 * \brief DMA�豸ʵ��
 */
typedef struct amdr_dma_dev {
    
    /** \brief ָ��DMA�豸��Ϣ��ָ�� */
    const amdr_dma_devinfo_t *p_devinfo;
    
} amdr_dma_dev_t;


/**
 * \brief ����ͨ������ 
 *
 * \param[in] chan  : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                   (#DMA_CHAN_USART0_RX_REQ)
 * \param[in] flags : ���ò������μ�
 *                    \ref grp_amhw_dma_chan_cfg_flags "Channel Configuration Flags".
 * 
 * \retval AM_OK    : �����ɹ� 
 */
int amdr_dma_chan_setup(int chan, uint32_t flags);

/**
 * \brief ��ʼͨ������ 
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                  (#DMA_CHAN_USART0_RX_REQ).
 * \retval AM_OK   : �����ɹ� 
 */
int amdr_dma_chan_start(int chan);

/**
 * \brief ֹͣͨ������ 
 * \param[in] chan : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                  (#DMA_CHAN_USART0_RX_REQ).
 * \retval AM_OK   : �����ɹ� 
 */
int amdr_dma_chan_stop(int chan);

/**
 * \brief �������������� 
 *
 * \attention ��ʹ��ƹ�Ҵ��䣬�����������ĵ�ַ������16�ֽڶ���  
 * 
 * \param[in] p_desc   : ָ��DMA������������ָ�� 
 * \param[in] src_addr : Դ���׵�ַ 
 * \param[in] dst_addr : Ŀ����׵�ַ 
 * \param[in] nbytes   : �����ֽ�����ע��Ҫ�롰flags���Ŀ�ȶ�Ӧ 
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_amhw_dma_chan_xfercfg_flags "Transfer Configuration Flags"
 *
 * \retval  AM_OK      : �����ɹ� 
 * \retval -AM_EINVAL  : ��Ч���� 
 */
int amdr_dma_xfer_desc_build(amhw_dma_xfer_desc_t *p_desc,
                             uint32_t              src_addr,
                             uint32_t              dst_addr,
                             uint32_t              nbytes,
                             uint32_t              flags);

/**
 * \brief �������� 
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                     (#DMA_CHAN_USART0_RX_REQ) 
 * \param[in] p_desc  : ָ��DMA������������ָ�� 
 *
 * \retval  AM_OK     : �����ɹ� 
 * \retval -AM_EINVAL : ������Ч 
 */
int amdr_dma_chan_xfer_startup(int chan, amhw_dma_xfer_desc_t *p_desc);

/**
 * \brief ����DMA�ص����� 
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTA)��(#AMDR_DMA_INTB) �� (#AMDR_DMA_INTERR) 
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                     (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] pfn_isr : �ص�����ָ�� 
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ��� 
 *
 * \retval  AM_OK     : ���ӳɹ� 
 * \retval -AM_EPERM  : �������� 
 */
int amdr_dma_isr_connect(int                 chan,
                         amdr_pfn_dma_isr_t  pfn_isr, 
                         void               *p_arg);

/**
 * \brief ɾ��DMA�ص����������� 
 *
 * \attention �ûص������ĵڶ��������ɴ�������ã��ò�����ȡֵ��Χ�� AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTA)��(#AMDR_DMA_INTB) �� (#AMDR_DMA_INTERR) 
 *
 * \param[in] chan    : DMA ͨ���ţ�ֵΪ��DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                     (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] pfn_isr : �ص�����ָ�� 
 * \param[in] p_arg   : �ص������ĵ�һ����ڲ��� 
 *
 * \retval  AM_OK     : ɾ���ɹ� 
 * \retval -AM_EPERM  : �������� 
 */
int amdr_dma_isr_disconnect(int                 chan,
                            amdr_pfn_dma_isr_t  pfn_isr, 
                            void               *p_arg);

/**
 * \brief ������������������ 
 *
 * \attention �����������ĵ�ַ���붼��16�ֽڶ��� 
 *
 * \param[in] p_desc : ָ��ǰ������������ָ�룬����16�ֽڶ��� 
 * \param[in] p_next : ָ����һ��������������ָ�룬����16�ֽڶ��� 
 *
 * \retval  AM_OK    : ���ӳɹ� 
 */
int amdr_dma_xfer_desc_link(amhw_dma_xfer_desc_t *p_desc, 
                            amhw_dma_xfer_desc_t *p_next);

/**
 * \brief DMA��ʼ��
 *
 * \param[in] p_dev     : ָ��DMA�豸��ָ�� 
 * \param[in] p_devinfo : ָ��DMA�豸��Ϣ��ָ�� 
 *
 * \retval  AM_OK       : ��ʼ���ɹ� 
 */
int amdr_dma_init(amdr_dma_dev_t *p_dev, const amdr_dma_devinfo_t *p_devinfo);


/**
 * \brief DMAȥ��ʼ�� 
 *
 * \param[in] p_dev : ָ��DMA�豸��ָ�� 
 *
 * \return  ��
 */
void amdr_dma_deinit (amdr_dma_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AMDR_DMA_H */

/* end of file */

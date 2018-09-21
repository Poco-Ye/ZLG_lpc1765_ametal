/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief ���븴�� (INMUX) Ӳ�������ӿ�
 *
 * 1. ����������Ϊ�����жϿ�Ͳ���ƥ������;
 * 2. ����������ΪDMA���ź�;
 * 3. ����������ΪƵ�ʲ������ܡ��ù�����SYSCON��FREQMECTRL�Ĵ�����Ӱ�졣
 *
 * \internal
 * \par Modification History
 * - 1.10 15-01-01  hbt, modified.
 * - 1.00 14-12-05  asd, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_INMUX_H
#define __AMHW_INMUX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

 /** 
 * \addtogroup amhw_if_inmux
 * \copydoc amhw_inmux.h
 * @{
 */
 
/**
 * \brief  ���븴�üĴ�����ṹ��
 */
typedef struct amhw_inmux {
    __IO uint32_t reserved0[6];         /**< \brief ����                     */
    __I  uint32_t reserved1[42];        /**< \brief ����                     */
    __IO uint32_t pintsel[8];           /**< \brief �����ж�ѡ��Ĵ���       */
    __IO uint32_t dma_itrig_inmux[22];  /**< \brief DMA ����Դ���븴�üĴ��� */
    __I  uint32_t reserved2[2];         /**< \brief ����                     */  
    __IO uint32_t dma_otrig_inmux[4];   /**< \brief DMA ������������Ĵ���   */
    __I  uint32_t reserved3[4];         /**< \brief ����                     */
    __IO uint32_t freqmeas_ref;         /**< \brief Ƶ�ʲ����ο�ʱ��ѡ��     */ 
    __IO uint32_t freqmeas_target;      /**< \brief Ƶ�ʲ���Ŀ��ʱ��ѡ��     */
} amhw_inmux_t;


/**
 * \name LPC5410X �����ж�ѡ��
 * \anchor grp_amhw_inmux_chan
 * @{
 */
 
#define AMHW_INMUX_CHAN_0         0    /**< \brief �����ж�ͨ�� 0 */
#define AMHW_INMUX_CHAN_1         1    /**< \brief �����ж�ͨ�� 1 */
#define AMHW_INMUX_CHAN_2         2    /**< \brief �����ж�ͨ�� 2 */
#define AMHW_INMUX_CHAN_3         3    /**< \brief �����ж�ͨ�� 3 */
#define AMHW_INMUX_CHAN_4         4    /**< \brief �����ж�ͨ�� 4 */
#define AMHW_INMUX_CHAN_5         5    /**< \brief �����ж�ͨ�� 5 */
#define AMHW_INMUX_CHAN_6         6    /**< \brief �����ж�ͨ�� 6 */
#define AMHW_INMUX_CHAN_7         7    /**< \brief �����ж�ͨ�� 7 */

/** @} */

/**
 * \brief �����ж�ͨ��ѡ������
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] pint_sel   : GPIO �����ж�ͨ���ţ��μ�
 *                         \ref grp_amhw_inmux_chan
 * \param[in] pin       : ���ű�ţ�ֵΪ PIO* (#PIO0_0)
 *
 * \return  ��
 */
am_static_inline 
void amhw_inmux_pint_sel (amhw_inmux_t *p_hw_inmux,
                          int           pint_sel,
                          int           pin)
{
    p_hw_inmux->pintsel[pint_sel] = pin;
}


/** \brief DMA �����ź�Դ */
typedef enum amhw_inmux_dma_trigsrc {
    AMHW_INMUX_DMATRIG_ADC0_SEQA_IRQ = 0, /**< \brief ADC0 ����A�ж�     */
    AMHW_INMUX_DMATRIG_ADC0_SEQB_IRQ,     /**< \brief ADC0 ����B�ж�     */
    AMHW_INMUX_DMATRIG_SCT0_DMA0,         /**< \brief SCT 0 DMA 0 ����   */
    AMHW_INMUX_DMATRIG_SCT0_DMA1,         /**< \brief SCT 1 DMA 1 ����   */
    AMHW_INMUX_DMATRIG_TIMER0_MATCH0,     /**< \brief Timer 0 ƥ�� 0     */
    AMHW_INMUX_DMATRIG_TIMER0_MATCH1,     /**< \brief Timer 0 ƥ�� 1     */
    AMHW_INMUX_DMATRIG_TIMER1_MATCH0,     /**< \brief Timer 1 ƥ�� 0     */
    AMHW_INMUX_DMATRIG_TIMER2_MATCH0,     /**< \brief Timer 2 ƥ�� 0     */
    AMHW_INMUX_DMATRIG_TIMER2_MATCH1,     /**< \brief Timer 2 ƥ�� 1     */
    AMHW_INMUX_DMATRIG_TIMER3_MATCH0,     /**< \brief Timer 3 ƥ�� 0     */
    AMHW_INMUX_DMATRIG_TIMER4_MATCH0,     /**< \brief Timer 4 ƥ�� 0     */
    AMHW_INMUX_DMATRIG_TIMER4_MATCH1,     /**< \brief Timer 4 ƥ�� 1     */
    AMHW_INMUX_DMATRIG_PININT0,           /**< \brief �����ж� 0         */
    AMHW_INMUX_DMATRIG_PININT1,           /**< \brief �����ж� 1         */
    AMHW_INMUX_DMATRIG_PININT2,           /**< \brief �����ж� 2         */
    AMHW_INMUX_DMATRIG_PININT3,           /**< \brief �����ж� 3         */
    AMHW_INMUX_DMATRIG_OUTMUX0,           /**< \brief DMA ����������� 0 */
    AMHW_INMUX_DMATRIG_OUTMUX1,           /**< \brief DMA ����������� 1 */
    AMHW_INMUX_DMATRIG_OUTMUX2,           /**< \brief DMA ����������� 2 */
    AMHW_INMUX_DMATRIG_OUTMUX3            /**< \brief DMA ����������� 3 */
} amhw_inmux_dma_trigsrc_t;

/**
 * \brief Ϊָ��DMAͨ��ѡ�񴥷�Դ
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] chan       : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                         (#DMA_CHAN_USART0_RX_REQ)
* \param[in] trig        : ����Դ
 *
 * \return ��
 */
am_static_inline 
void amhw_inmux_dma_trig_set (amhw_inmux_t            *p_hw_inmux,
                              int                      chan, 
                              amhw_inmux_dma_trigsrc_t trig)
{
    p_hw_inmux->dma_itrig_inmux[chan] = (uint32_t)trig;
}

/** 
 * \brief DMAͨ��ѡ�����������Դ
 */
typedef enum amhw_inmux_dma_otrig {
    AMHW_INMUX_DMATRIG_OUT0 = 0,  /**< \brief DMA �������Դ 0 */
    AMHW_INMUX_DMATRIG_OUT1,      /**< \brief DMA �������Դ 1 */
    AMHW_INMUX_DMATRIG_OUT2,      /**< \brief DMA �������Դ 2 */
    AMHW_INMUX_DMATRIG_OUT3       /**< \brief DMA �������Դ 3 */
} amhw_inmux_dma_otrig_t;

/**
 * \brief ѡ��DMAͨ�����������Դ
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] index      : ѡ�����ͨ�� (#AMHW_INMUX_DMATRIG_OUT0).
 * \param[in] chan       : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                         (#DMA_CHAN_USART0_RX_REQ). ֻ���� DMA_CHAN_0 �� DMA_CHAN_19.
 *
 * \return ��
 */
am_static_inline 
void amhw_inmux_dma_outmux_set (amhw_inmux_t           *p_hw_inmux, 
                                amhw_inmux_dma_otrig_t  index, 
                                int                     chan)
{
    p_hw_inmux->dma_otrig_inmux[index] = (uint32_t)chan;
}

/**
 * \brief Ƶ�ʲ����Ĳο�ʱ�Ӻ�Ŀ��ʱ��Դ
 */
typedef enum amhw_inmux_freqmsr_src {
    AMHW_INMUX_FREQMSR_SRC_CLKIN = 0, /**< \brief ʱ������           */
    AMHW_INMUX_FREQMSR_SRC_IRC,       /**< \brief IRC ����         */
    AMHW_INMUX_FREQMSR_SRC_WDTOSC,    /**< \brief ���Ź�ʱ������   */
    AMHW_INMUX_FREQMSR_SRC_32KHZOSC,  /**< \brief 32KHz (RTC) ���� */
    AMHW_INMUX_FREQMSR_SRC_MAINCLK,   /**< \brief ��ʱ��             */
    AMHW_INMUX_FREQMSR_SRC_PIO0_4,    /**< \brief �ⲿ���� PIO0_4    */
    AMHW_INMUX_FREQMSR_SRC_PIO0_20,   /**< \brief �ⲿ���� PIO0_20   */
    AMHW_INMUX_FREQMSR_SRC_PIO0_24,   /**< \brief �ⲿ���� PIO0_24   */
    AMHW_INMUX_FREQMSR_SRC_PIO1_4     /**< \brief �ⲿ���� PIO1_4    */
} amhw_inmux_freqmsr_src_t;

/**
 * \brief ѡ��ο�ʱ��ʵ��Ƶ�ʲ���
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] ref_src    : �ο�ʱ��
 *
 * \return ��
 */
am_static_inline 
void amhw_inmux_freqmsr_refclk_set (amhw_inmux_t            *p_hw_inmux, 
                                    amhw_inmux_freqmsr_src_t ref_src)
{
    p_hw_inmux->freqmeas_ref = (uint32_t)ref_src;
}

/**
 * \brief ѡ��Ŀ��ʱ��ʵ��Ƶ�ʲ���
 *
 * \param[in] p_hw_inmux : ָ�����븴�üĴ������ָ��
 * \param[in] targ_src   : Ŀ��ʱ��
 *
 * \return ��
 */
am_static_inline 
void amhw_inmux_freqmsr_targclk_set (amhw_inmux_t             *p_hw_inmux, 
                                     amhw_inmux_freqmsr_src_t  targ_src)
{
    p_hw_inmux->freqmeas_target = (uint32_t)targ_src;
}

/**
 * @} 
 */


#ifdef __cplusplus
}
#endif

#endif /* __AMHW_INMUX_H */

/* end of file */

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
 * \brief DMA Ӳ�������ӿڡ�
 *
 * 1. 22 ��ͨ��, ����21��ͨ������������ͨ��������Щ����ֱ���USART��SPI��I2C�ȡ�
 *    ʣ�µ�1��ͨ���������ӵ��������󣬵��ܹ������ڴ浽�ڴ�����ݰ��ˣ�
 * 2. Ƭ�ڻ�Ƭ���¼����ܴ���DMA����.ÿ��DMAͨ������ѡ��20�����봥��Դ.����Դ��
 *    ADC�жϡ���ʱ���жϡ������жϺ�SCT DMA�����У�
 * 3. ÿ��ͨ�������趨���ȼ����ߴ�8�����ȼ����ã���
 * 4. ���������ȼ��ٲã�
 * 5. 4����ڵ�cache��ַ��ÿ������ǵ�ַ��һ���֣���
 * 6. ����Чʹ�����������ߣ�
 * 7. ���δ������ɴ�1024�֣�
 * 8. ��ַ������ѡ���װ��/�򲻷�װ���ݡ�
 *
 * \internal
 * \par Modification History
 * - 1.10 14-12-01  zen, refine the implementation.
 * - 1.00 14-11-24  hbt, first implementation.
 * \endinternal
 */

#ifndef __AMHW_DMA_H
#define __AMHW_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 
#include "am_common.h"

/**
 * \addtogroup amhw_if_dma
 * \copydoc amhw_dma.h
 * @{
 */

/** \brief DMA ͨ������ */
#define AMHW_DMA_CHAN_CNT           22

/**
 * \brief DMA ͨ���Ĵ����ṹ��
 */
typedef struct amhw_dma_chan {
    __IO  uint32_t  cfg;            /**< \brief DMA ͨ�����üĴ���       */
    __IO  uint32_t  ctlstat;        /**< \brief DMA ͨ�����ƺ�״̬�Ĵ��� */
    __IO  uint32_t  xfercfg;        /**< \brief DMA �������üĴ���       */
    __IO  uint32_t  reserved;       /**< \brief ����                     */
} amhw_dma_chan_t;

/**
 * \brief DMA �������Ĵ�����ṹ�� 
 */
typedef struct amhw_dma {
    __IO  uint32_t    ctrl;          /**< \brief DMA ���ƼĴ���                */
    __IO  uint32_t    intstat;       /**< \brief DMA �ж�״̬�Ĵ���            */
    __IO  uint32_t    srambase;      /**< \brief DMA ͨ�������б��SRAM��ַ    */
    __IO  uint32_t    reserved0[5];  /**< \brief ����                          */
    __IO  uint32_t    enableset0;    /**< \brief ��������DMAͨ��ʹ�ܼĴ���     */
    __IO  uint32_t    reserved1;     /**< \brief ����                          */
    __IO  uint32_t    enableclr0;    /**< \brief ���DMAͨ��ʹ�ܼĴ���         */
    __IO  uint32_t    reserved2;     /**< \brief ����                          */
    __IO  uint32_t    active0;       /**< \brief DMAͨ����Ч״̬�Ĵ���         */
    __IO  uint32_t    reserved3;     /**< \brief ����                          */
    __IO  uint32_t    busy0;         /**< \brief DMAͨ��busy״̬�Ĵ���         */
    __IO  uint32_t    reserved4;     /**< \brief ����                          */
    __IO  uint32_t    errint0;       /**< \brief DMA ͨ�������ж�״̬�Ĵ���    */
    __IO  uint32_t    reserved5;     /**< \brief ����                          */
    __IO  uint32_t    intenset0;     /**< \brief ��������DMAͨ���ж�ʹ�ܼĴ��� */
    __IO  uint32_t    reserved6;     /**< \brief ����                          */
    __IO  uint32_t    intenclr0;     /**< \brief ���DMAͨ���ж�ʹ�ܼĴ���     */
    __IO  uint32_t    reserved7;     /**< \brief ����                          */
    __IO  uint32_t    inta0;         /**< \brief DMA A�жϱ�־�Ĵ���           */
    __IO  uint32_t    reserved8;     /**< \brief ����                          */
    __IO  uint32_t    intb0;         /**< \brief DMA B�жϱ�־�Ĵ���           */
    __IO  uint32_t    reserved9;     /**< \brief ����                          */
    __IO  uint32_t    setvalid0;     /**< \brief DMAͨ����Ч�ȴ�����λ�Ĵ���   */
    __IO  uint32_t    reserved10;    /**< \brief ����                          */
    __IO  uint32_t    settrig0;      /**< \brief DMAͨ����������λ�Ĵ���       */
    __IO  uint32_t    reserved11;    /**< \brief ����                          */
    __IO  uint32_t    abort0;        /**< \brief DMAͨ���������λ�Ĵ���       */
    __IO  uint32_t    reserved12[225]; /**< \brief ����                        */
    
    amhw_dma_chan_t chan[AMHW_DMA_CHAN_CNT];   /**< \brief DMAͨ���Ĵ���       */
    
} amhw_dma_t;

/**
 * \brief DMA ����������
 * \attention �����������ĵ�ַ������16�ֽڶ���
 */
typedef struct amhw_dma_xfer_desc {
    volatile uint32_t xfercfg;            /**< \brief ��������         */
    volatile uint32_t src_end_addr;       /**< \brief Դ����ĩ��ַ     */
    volatile uint32_t dst_end_addr;       /**< \brief Ŀ������ĩ��ַ   */
    volatile uint32_t link;               /**< \brief ָ����һ�������� */
} amhw_dma_xfer_desc_t;


/**
 * \brief ʹ��DMA������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dma_enable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->ctrl = 1UL;
}

/**
 * \brief ����DMA������
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_dma_disable (amhw_dma_t *p_hw_dma)
{
    p_hw_dma->ctrl = 0;
}

/**
 * \brief ��ȡDMA�ж�״̬
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return    �ж�״̬��
 */
am_static_inline
uint32_t amhw_dma_int_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat;
}

/**
 * \brief �Ƿ����жϣ��������ж��⣩�ڵȴ�����
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \retval  non-0      : ������һ���ж��ڵȴ�����
 * \retval  0          : ���ж��ڵȴ�����
 */
am_static_inline
uint32_t amhw_dma_int_pending (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat & 0x02UL;
}

/**
 * \brief �Ƿ��д����ж��ڵȴ�����
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \retval  non-0      : ������һ�������ж��ڵȴ�����
 * \retval  0          : �޴����ж��ڵȴ�����
 */
am_static_inline
uint32_t amhw_dma_errint_pending (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intstat & 0x04UL;
}

/**
 * \brief ����SRAM����ַ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] addr     : ͨ���������б����ʼ��ַ���õ�ַ������512�ֽڶ���
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_sram_addr_set (amhw_dma_t *p_hw_dma, uint32_t addr)
{
    p_hw_dma->srambase = addr;
}

/**
 * \brief ��ȡSRAM����ַ
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \return  ͨ���������б����ʼ��ַ���õ�ַ������512�ֽڶ���
 */
am_static_inline
uint32_t amhw_dma_sram_addr_get (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->srambase;
}

/**
 * \brief ��ȡͨ����������ַ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return  ͨ����������ַ
 */
am_static_inline
uint32_t amhw_dma_chan_desc_addr_get (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return (amhw_dma_sram_addr_get(p_hw_dma) + (chan << 4));
}

/**
 * \brief ʹ��DMAͨ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_enable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->enableset0 = (1UL << chan);
}

/**
 * \brief ����DMAͨ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_disable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->enableclr0 = (1UL << chan);
}

/**
 * \brief ָ��ͨ���Ƿ���Ч
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 * 
 * \retval  non-0      : ͨ����Ч
 * \retval  0          : ͨ����Ч
 */
am_static_inline
uint32_t amhw_dma_chan_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->active0;
}

/**
 * \brief ָ��ͨ���Ƿ�busy
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 * 
 * \retval  non-0      : ͨ��busy
 * \retval  0          : ͨ�� unbusy
 */
am_static_inline
uint32_t amhw_dma_chan_busy (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->busy0 & (1UL << chan);
}

/**
 * \brief ָ��ͨ���Ĵ����ж��Ƿ���Ч
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ�롣
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : ͨ���Ĵ����ж���Ч
 * \retval  0          : ͨ���Ĵ����ж���Ч
 */
am_static_inline
uint32_t amhw_dma_chan_errint_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->errint0 & (1UL << chan);
}

/**
 * \brief ��ָ��ͨ���Ĵ����ж�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_errint_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->errint0 = (1UL << chan);
}

/**
 * \brief ʹ��DMAͨ���ж�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_int_enable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->intenset0 = (1UL << chan);
}

/**
 * \brief ����DMAͨ���ж�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_int_disable (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->intenclr0 = (1UL << chan);
}

/**
 * \brief ��ȡ�����жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return    �����жϱ�־, bit[21:0] �Ǵ����־λ��Bit n ��Ӧͨ�� n
 */
am_static_inline
uint32_t amhw_dma_errint_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->errint0;
}

/**
 * \brief ͨ��������������жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[21:0] ��ӦDMAͨ�� n�� �����λ������ ERRINT ���Ӧ.
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_errint_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->errint0 = mask;
}

/**
 * \brief ��ȡA�ж�״̬��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return    A�жϱ�־��bit[21:0] ��DMAͨ�� n ��A�жϱ�־��Bit n ��ӦDMAͨ�� n 
 */
am_static_inline
uint32_t amhw_dma_inta_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->inta0;
}

/**
 * \brief ͨ���������A�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[21:0] ��ӦDMAͨ�� n, �ñ����Ϊ������ NTA ���Ӧ��
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_inta_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->inta0 = mask;
}

/**
 * \brief ָ��ͨ����A�ж��Ƿ���Ч
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : ͨ����A�ж���Ч
 * \retval  0          : ͨ����A�ж���Ч
 */
am_static_inline
uint32_t amhw_dma_chan_inta_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->inta0 & (1UL << chan);
}

/**
 * \brief ���ָ��ͨ����A�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_inta_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->inta0 = (1UL << chan);
}

/**
 * \brief ��ȡB�ж�״̬
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 *
 * \return    B�жϱ�־��bit[21:0] ��DMAͨ�� n ��B�жϱ�־��Bit n ��ӦDMAͨ�� n ��
 */
am_static_inline
uint32_t amhw_dma_intb_status (amhw_dma_t *p_hw_dma)
{
    return p_hw_dma->intb0;
}

/**
 * \brief ͨ���������B�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] mask     : bit[21:0] ��ӦDMAͨ�� n, �ñ����Ϊ������ NTB ���Ӧ��
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_intb_clear (amhw_dma_t *p_hw_dma, uint32_t mask)
{
    p_hw_dma->intb0 = mask;
}

/**
 * \brief ָ��ͨ����B�ж��Ƿ���Ч
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : ͨ����B�ж���Ч
 * \retval  0          : ͨ����B�ж���Ч
 */
am_static_inline
uint32_t amhw_dma_chan_intb_active (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->intb0 & (1UL << chan);
}

/**
 * \brief ���ָ��ͨ����B�жϱ�־
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_intb_clear (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->intb0 = (1UL << chan);
}

/**
 * \brief ָ��ͨ����Ч
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ)
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_set_valid (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->setvalid0 |= (1UL << chan);
}

/**
 * \brief ����DMAͨ������λ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_set_trig (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->settrig0 |= (1UL << chan);
}

/**
 * \brief ����DMAͨ��
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_abort (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->abort0 |= (1UL << chan);
}


/**
 * \name ����ͨ�����ò���
 * \anchor grp_amhw_dma_chan_cfg_flags
 * @{
 */

#define AMHW_DMA_CHAN_PERIPH_REQ_OFF     0            /**< \brief ��������DMA���� */
#define AMHW_DMA_CHAN_PERIPH_REQ_EN      AM_BIT(0)    /**< \brief ʹ������DMA���� */

#define AMHW_DMA_CHAN_HWTRIG_OFF         0                                   /**< \brief ��ֹӲ��������             */
#define AMHW_DMA_CHAN_HWTRIG_FALL        AM_BIT(1)                           /**< \brief DMA Ӳ���������½������С� */
#define AMHW_DMA_CHAN_HWTRIG_RISE       (AM_BIT(1) | AM_BIT(4))              /**< \brief DMA Ӳ�����������������С� */
#define AMHW_DMA_CHAN_HWTRIG_LOW        (AM_BIT(1) | AM_BIT(5))              /**< \brief DMA Ӳ���������͵�ƽ���С� */
#define AMHW_DMA_CHAN_HWTRIG_HIGH       (AM_BIT(1) | AM_BIT(4) | AM_BIT(5))  /**< \brief DMA Ӳ���������ߵ�ƽ���С� */

#define AMHW_DMA_CHAN_SINGLE_TRANS       0                           /**< \brief Ӳ���������𵥴δ��䡣                  */
#define AMHW_DMA_CHAN_BURST_1           (AM_BIT(6) | AM_SBF(0,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 1    */
#define AMHW_DMA_CHAN_BURST_2           (AM_BIT(6) | AM_SBF(1,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 2    */
#define AMHW_DMA_CHAN_BURST_4           (AM_BIT(6) | AM_SBF(2,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 4    */
#define AMHW_DMA_CHAN_BURST_8           (AM_BIT(6) | AM_SBF(3,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 8    */
#define AMHW_DMA_CHAN_BURST_16          (AM_BIT(6) | AM_SBF(4,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 16   */
#define AMHW_DMA_CHAN_BURST_32          (AM_BIT(6) | AM_SBF(5,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 32   */
#define AMHW_DMA_CHAN_BURST_64          (AM_BIT(6) | AM_SBF(6,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 64   */
#define AMHW_DMA_CHAN_BURST_128         (AM_BIT(6) | AM_SBF(7,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 128  */
#define AMHW_DMA_CHAN_BURST_256         (AM_BIT(6) | AM_SBF(8,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 256  */
#define AMHW_DMA_CHAN_BURST_512         (AM_BIT(6) | AM_SBF(9,  8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 512  */
#define AMHW_DMA_CHAN_BURST_1024        (AM_BIT(6) | AM_SBF(10, 8))  /**< \brief Ӳ����������ͻ�����䣬Burst size = 1024 */

#define AMHW_DMA_CHAN_SRC_BURST_NO_WRAP  0              /**< \brief Դ��ͻ�������ơ�    */
#define AMHW_DMA_CHAN_DST_BURST_NO_WRAP  0              /**< \brief Ŀ���ͻ�������ơ�  */
#define AMHW_DMA_CHAN_SRC_BURST_WRAP     AM_BIT(14)     /**< \brief Դ��ͻ�����ơ�      */
#define AMHW_DMA_CHAN_DST_BURST_WRAP     AM_BIT(15)     /**< \brief Ŀ���ͻ�����ơ�    */

#define AMHW_DMA_CHAN_PRIO_0             AM_SBF(0, 16)  /**< \brief ͨ�����ȼ� 0 (0 Ϊ������ȼ�) */
#define AMHW_DMA_CHAN_PRIO_1             AM_SBF(1, 16)  /**< \brief ͨ�����ȼ� 1 (0 Ϊ������ȼ�) */
#define AMHW_DMA_CHAN_PRIO_2             AM_SBF(2, 16)  /**< \brief ͨ�����ȼ� 2 (0 Ϊ������ȼ�) */
#define AMHW_DMA_CHAN_PRIO_3             AM_SBF(3, 16)  /**< \brief ͨ�����ȼ� 3 (0 Ϊ������ȼ�) */
#define AMHW_DMA_CHAN_PRIO_4             AM_SBF(4, 16)  /**< \brief ͨ�����ȼ� 4 (0 Ϊ������ȼ�) */
#define AMHW_DMA_CHAN_PRIO_5             AM_SBF(5, 16)  /**< \brief ͨ�����ȼ� 5 (0 Ϊ������ȼ�) */
#define AMHW_DMA_CHAN_PRIO_6             AM_SBF(6, 16)  /**< \brief ͨ�����ȼ� 6 (0 Ϊ������ȼ�) */
#define AMHW_DMA_CHAN_PRIO_7             AM_SBF(7, 16)  /**< \brief ͨ�����ȼ� 7 (0 Ϊ������ȼ�) */

/** @} */


/**
 * \brief DMA ͨ������
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_amhw_dma_chan_cfg_flags "Channel Configuration Flags"
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_cfg_set (amhw_dma_t *p_hw_dma, unsigned int chan, uint32_t flags)
{
    p_hw_dma->chan[chan].cfg = flags;
}

/**
 * \brief ָ��ͨ���Ƿ���Ч�ȴ�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : ��Ч�ȴ���
 * \retval  0          : ����ЧDMA������
 */
am_static_inline
uint32_t amhw_dma_chan_valid_pending (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->chan[chan].ctlstat & (1UL << 0);
}

/**
 * \brief ��ǰͨ�������Ƿ���λ
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \retval  non-0      : ��ǰͨ����������λ��DMA���䱻ִ��
 * \retval  0          : ��ǰͨ������δ����λ��DMA���䲻��ִ��
 */
am_static_inline
uint32_t amhw_dma_chan_triggered (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    return p_hw_dma->chan[chan].ctlstat & (1UL << 2);
}


/**
 * \name ���崫�����ò���
 * \anchor grp_amhw_dma_chan_xfercfg_flags
 * @{
 */

#define AMHW_DMA_XFER_CFG_INVALID      0              /**< \brief ���Ƕ�Ӧ�� SETVALID0 ����λ�� Ҫ��Ȼ��ǰͨ��������һֱ��Ч�� */
#define AMHW_DMA_XFER_CFG_VALID        AM_BIT(0)      /**< \brief ��ǰͨ����������Ч��                                         */

#define AMHW_DMA_XFER_NO_RELOAD        0              /**< \brief ��ǰ�������������ʱ���������µ�ͨ���������� */
#define AMHW_DMA_XFER_RELOAD           AM_BIT(1)      /**< \brief ��ǰ�������������ʱ�������µ�ͨ����������   */

#define AMHW_DMA_XFER_NO_SWTRIG        0              /**< \brief ��ǰͨ����ʹ�����������             */
#define AMHW_DMA_XFER_SWTRIG           AM_BIT(2)      /**< \brief ��ǰͨ��ʹ��������������Ͻ��д��䡣 */

#define AMHW_DMA_XFER_NO_CLRTRIG       0              /**< \brief ��ǰ�������������ʱ�������źŲ�������� */
#define AMHW_DMA_XFER_CLRTRIG          AM_BIT(3)      /**< \brief ��ǰ�������������ʱ�������źű������   */

#define AMHW_DMA_XFER_SETINTA          AM_BIT(4)      /**< \brief ��ǰ�������������ʱ����ͨ����A�жϱ�־��λ�� */
#define AMHW_DMA_XFER_SETINTB          AM_BIT(5)      /**< \brief ��ǰ�������������ʱ����ͨ����B�жϱ�־��λ�� */

#define AMHW_DMA_XFER_WIDTH_8BIT       AM_SBF(0, 8)   /**< \brief ִ�� 8-bit ���� (Դ���ݶ���Ŀ������д��Ϊ 8-bit)��   */
#define AMHW_DMA_XFER_WIDTH_16BIT      AM_SBF(1, 8)   /**< \brief ִ�� 16-bit ���� (Դ���ݶ���Ŀ������д��Ϊ 16-bit)�� */
#define AMHW_DMA_XFER_WIDTH_32BIT      AM_SBF(2, 8)   /**< \brief ִ�� 32-bit ���� (Դ���ݶ���Ŀ������д��Ϊ 32-bit)�� */
#define AMHW_DMA_XFER_WIDTH_MASK       AM_SBF(0x3, 8) /**< \brief ����λ�����롣                                       */

#define AMHW_DMA_XFER_NO_SRCINC        AM_SBF(0, 12)  /**< \brief ÿ�δ���Դ��ַ�����ӡ�              */
#define AMHW_DMA_XFER_SRCINC_1X_WIDTH  AM_SBF(1, 12)  /**< \brief ÿ�δ���Դ��ַ����1��ָ�����ݿ�ȡ� */
#define AMHW_DMA_XFER_SRCINC_2X_WIDTH  AM_SBF(2, 12)  /**< \brief ÿ�δ���Դ��ַ����2��ָ�����ݿ�ȡ� */
#define AMHW_DMA_XFER_SRCINC_4X_WIDTH  AM_SBF(3, 12)  /**< \brief ÿ�δ���Դ��ַ����4��ָ�����ݿ�ȡ� */

#define AMHW_DMA_XFER_NO_DSTINC        AM_SBF(0, 14)  /**< \brief ÿ�δ���Ŀ���ַ�����ӡ�              */ 
#define AMHW_DMA_XFER_DSTINC_1X_WIDTH  AM_SBF(1, 14)  /**< \brief ÿ�δ���Ŀ���ַ����1��ָ�����ݿ�ȡ� */ 
#define AMHW_DMA_XFER_DSTINC_2X_WIDTH  AM_SBF(2, 14)  /**< \brief ÿ�δ���Ŀ���ַ����2��ָ�����ݿ�ȡ� */
#define AMHW_DMA_XFER_DSTINC_4X_WIDTH  AM_SBF(3, 14)  /**< \brief ÿ�δ���Ŀ���ַ����4��ָ�����ݿ�ȡ� */

#define AMHW_DMA_XFERCOUNT(n)          AM_SBF(n, 16)  /**< \brief �����ܴ���������Ϊ1�Ρ�  */

/** @} */

/**
 * \brief ����DMAͨ�������ò���
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] flags    : ���ò������μ�
 *                       \ref grp_amhw_dma_chan_xfercfg_flags "Transfer Configuration Flags"
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_xfercfg_set (amhw_dma_t   *p_hw_dma, 
                                unsigned int  chan, 
                                uint32_t      flags)
{
    p_hw_dma->chan[chan].xfercfg = flags;
}

/**
 * \brief ָ��ͨ��ʹ��A�ж�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_inta_set (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg |= AM_BIT(4);
}

/**
 * \brief ָ��ͨ��ʹ��B�ж�
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_intb_set (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg |= AM_BIT(5);
}

/**
 * \brief ���ָ��ͨ����A�ж�����
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_inta_clr (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg &= ~AM_BIT(4);
}

/**
 * \brief ���ָ��ͨ����B�ж�����
 *
 * \param[in] p_hw_dma : ָ��DMA�������Ĵ������ָ��
 * \param[in] chan     : DMAͨ����ֵΪ DMA_CHAN_* (#DMA_CHAN_0) �� 
 *                       (#DMA_CHAN_USART0_RX_REQ).
 *
 * \return    ��
 */
am_static_inline
void amhw_dma_chan_intb_clr (amhw_dma_t *p_hw_dma, unsigned int chan)
{
    p_hw_dma->chan[chan].xfercfg &= ~AM_BIT(5);
}

/**
 * @} amhw_if_dma
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_DMA_H */

/* end of file */

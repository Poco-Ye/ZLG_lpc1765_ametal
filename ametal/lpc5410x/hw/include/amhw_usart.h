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
 * \brief ���ڣ�USART�������ӿ�
 *
 * 1. ֧��7��8��9�������ݿ�ȣ�֧��1λ��2λֹͣλ��
 * 2. ����ģʽ�ʹӻ�ģʽ��֧��ͬ��ģʽ���䣬����������λѡ��ͳ���ʱ�����ã�
 * 3. ������ģʽ(9λ����λ)֧�������ַƥ�䣻
 * 4. ֧��RS-485 �շ������ʹ�ܣ�
 * 5. ��żУ��Ĳ����ͼ�飺֧����У�顢żУ�����У�飻
 * 6. ���첽ģʽ�£�����ɱ�̹�����ʱ������֧��5 ~ 16ʱ�Ӳ�����
 * 7. һ�����ͺ�һ���������ݻ�������
 * 8. ϵͳFIFO֧�֣�
 * 9. RTS/CTS Ӳ���ź������Զ�������. ��������ƿ���ʹ��Delta CTS ��⣬���ͽ���
 *   ���ƺ�һ�������IO�ڣ����ڲ���RTS�źţ�ʵ�֣�
 * 10. �������ݺ�״̬���Դ�һ���Ĵ�����һ���Զ�����
 * 11. �ж�(Break)�����ͷ��֣�
 * 12. �������ݲ��ö�β���������2/3�ĵ�ƽֵΪ���ղ���ֵ��
 * 13. �ڽ������ʲ�������֧���Զ����������ԣ�
 * 14. һ��С����Ƶ���������еĴ��ڡ����ڲ������߾��ȵĲ����ʣ�
 * 15. �ж�(Interrupt)֧��: ����׼�������� ����׼�����������տ��У�����break��⵽�仯��
 *     ֡������żУ����������Delta CTS ��⣬���ղ���������⣻
 * 16. ��·ģʽ�����ڲ������ݺ������ƣ�
 * 17. ��������ģʽ��ʹ��32kHz��RTC����������Ϊʱ��Դ���������������9600������
 *     �£���ģʽ�����ڵ���ģʽ(Power-down mode)��ʹ�ô��ڣ��������ڽ��յ�һ���ַ�
 *     ʱ�����豸��
 * 18. USART ���ͺͽ��տ���ʹ��DMA��������
 *
 * \internal
 * \par Modification History
 * - 1.01 14-12-03  jon, add USART interrupt mode.
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_USART_H
#define __AMHW_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup amhw_if_usart
 * \copydoc amhw_usart.h
 * @{
 */

/**
 * \brief USART �Ĵ�����ṹ��
 */
typedef struct amhw_usart {
    __IO uint32_t cfg;         /**< \brief USART ���üĴ���             */
    __IO uint32_t ctl;         /**< \brief USART ���ƼĴ���             */
    __IO uint32_t stat;        /**< \brief USART ״̬�Ĵ���             */
    __IO uint32_t int_enset;   /**< \brief �ж�ʹ�ܼĴ���               */
    __O  uint32_t int_enclr;   /**< \brief �ж�ʹ�ܼĴ���λ����Ĵ���   */
    __I  uint32_t rxdat;       /**< \brief �������ݼĴ���.              */
    __I  uint32_t rxdatstat;   /**< \brief �������ݺͽ���״̬�Ĵ���     */
    __IO uint32_t txdat;       /**< \brief �������ݼĴ���               */
    __IO uint32_t brg;         /**< \brief �����ʲ����Ĵ���             */
    __I  uint32_t intstat;     /**< \brief �ж�״̬�Ĵ���               */
    __IO uint32_t osr;         /**< \brief ������ѡ��Ĵ���             */
    __IO uint32_t addr;        /**< \brief ��ַ�Ĵ���                   */
} amhw_usart_t;


/**
 * \name �������ݼĴ�����ַ���壬(������DMA�õ�)
 * @{
 */

/** \brief USART0 �������ݼĴ�����ַ  */
#define AMHW_USART0_RXDAT_ADDR  (&(AMHW_USART0->rxdat))

/** \brief USART0 �������ݼĴ�����ַ  */
#define AMHW_USART0_TXDAT_ADDR  (&(AMHW_USART0->txdat))

/** \brief USART1 �������ݼĴ�����ַ  */
#define AMHW_USART1_RXDAT_ADDR  (&(AMHW_USART1->rxdat))

/** \brief USART1 �������ݼĴ�����ַ  */
#define AMHW_USART1_TXDAT_ADDR  (&(AMHW_USART1->txdat))

/** \brief USART2 �������ݼĴ�����ַ  */
#define AMHW_USART2_RXDAT_ADDR  (&(AMHW_USART2->rxdat))

/** \brief USART2 �������ݼĴ�����ַ  */
#define AMHW_USART2_TXDAT_ADDR  (&(AMHW_USART2->txdat))

/** \brief USART3 �������ݼĴ�����ַ  */
#define AMHW_USART3_RXDAT_ADDR  (&(AMHW_USART3->rxdat))

/** \brief USART3 �������ݼĴ�����ַ  */
#define AMHW_USART3_TXDAT_ADDR  (&(AMHW_USART3->txdat))

/** @} */


/**
 * \name ���ݳ��ȶ���
 * @{
 */

#define AMHW_USART_CFG_7BIT         0       /**< \brief 7λ���ݳ���      */
#define AMHW_USART_CFG_8BIT        (1 << 2) /**< \brief 8λ���ݳ���      */
#define AMHW_USART_CFG_9BIT        (1 << 3) /**< \brief 9λ���ݳ���      */

/** @} */

/**
 * \name ��żУ�鶨��
 * @{
 */

#define AMHW_USART_CFG_PARITY_NO     0        /**< \brief ��ʹ����żУ��      */
#define AMHW_USART_CFG_PARITY_EVEN  (2 << 5)  /**< \brief żУ��              */
#define AMHW_USART_CFG_PARITY_ODD   (3 << 4)  /**< \brief ��У��              */

/** @} */

/**
 * \brief ֹͣλ����
 * @{
 */

#define AMHW_USART_CFG_STOP_1     0        /**< \brief 1λֹͣλ    */
#define AMHW_USART_CFG_STOP_2    (1 << 6)  /**< \brief 2λֹͣλ    */

/** @} */


/** \brief USARTʱ��ʹ�� 32KHz RTC ��������ʱ��  */
#define AMHW_USART_CFG_MODE32K   (1 << 7)

/** \brief Break ���Ͳ��������� LIN ����ģʽ     */
#define AMHW_USART_CFG_LINMODE   (1 << 8)

/** \brief ʹ��Ӳ��������                          */
#define AMHW_USART_CFG_HWFLOW    (1 << 9)
 
/** \brief ʹ��ͬ��ģʽ                            */
#define AMHW_USART_CFG_SYNMODE   (1 << 11)

/**
 * \brief ����ͬ��ģʽ�����ݲ�����SCLK���½��� 
 *        (������#AMHW_USART_CFG_SYNMODE��һ��ʹ�ã����ɵ���ʹ��)
 */
#define AMHW_USART_CFG_FALLING    0

/**
 * \brief ����ͬ��ģʽ�����ݲ�����SCLK�������� 
 *        (������#AMHW_USART_CFG_SYNMODE��һ��ʹ�ã����ɵ���ʹ��)
 */
#define AMHW_USART_CFG_RISING    (1 << 12)

/**
 * \brief ����ͬ��ģʽ�����ڹ���������ģʽ
 *        (������#AMHW_USART_CFG_SYNMODE��һ��ʹ�ã����ɵ���ʹ��)
 */
#define AMHW_USART_CFG_MASTER    (1 << 14)

/** \brief ���ڽ������ڻ�·ģʽ(LoopBack mode) */
#define AMHW_USART_CFG_LOOPBACK  (1 << 15)

/** \brief ���ڹ����� IrDA ģʽ               */
#define AMHW_USART_CFG_IRDAMHODE (1 << 16)

/**
 * \brief ����RS-485ģʽ: RTS ���ڿ���RS-485�շ��������ʹ��
 */
#define AMHW_USART_CFG_OESEL     (1 << 20)

/**
 * \brief ����RS-485ģʽ: ���ʹ��ʧЧ(De-assertion)�źŽ������ӳ�һ���ַ�ʱ��
 *        ��Ҫ�� #AMHW_USART_CFG_OESEL ��һ��ʹ��
 */
#define AMHW_USART_CFG_OETA      (1 << 18)

/**
 * \brief �Զ���ַƥ��ʹ�ܣ�����ַƥ��ģʽ��ʹ�ܺ�#AMHW_USART_CTL_ADDRDET����
 *        ��ַƥ��ͨ��Ӳ����ɣ�ʹ�õ�ַ�Ĵ����е�ֵ��ɵ�ַƥ��
 */
#define AMHW_USART_CFG_AUTOADDR  (1 << 19)

/**
 * \brief ����RS-485ģʽ: ���ʹ���źŸߵ�ƽ��Ч������Ĭ��������ǵ͵�ƽ��Ч
 */
#define AMHW_USART_CFG_OEPOLHIGH (1 << 21)

/**
 * \brief �ߵ��������ݹܽŵĵ�ƽ����
 */
#define AMHW_USART_CFG_RXPOL     (1 << 22)

/**
 * \brief �ߵ��������ݹܽŵĵ�ƽ����
 */
#define AMHW_USART_CFG_TXPOL     (1 << 23)

/**
 * \name USART���Ʊ�־����Щ��־���ں��� amhw_usart_control().
 * @{
 */

#define AMHW_USART_CTL_TXBRKEN   (1 << 1)  /**< \brief ����breakģʽ          */
#define AMHW_USART_CTL_ADDRDET   (1 << 2)  /**< \brief ʹ�ܵ�ַƥ��ģʽ       */
#define AMHW_USART_CTL_TXDIS     (1 << 6)  /**< \brief ���ͽ���               */
#define AMHW_USART_CTL_CC        (1 << 8)  /**< \brief ����ʱ�Ӳ���           */
#define AMHW_USART_CTL_CLRCCONRX (1 << 9)  /**< \brief ���յ�һ���ַ�ʱ���CCλ */
#define AMHW_USART_CTL_AUTOBAUD  (1 << 16) /**< \brief �Զ�������ʹ��         */

/** @} */

/**
 * \name USART״̬��־
 * @{
 */

#define AMHW_USART_STAT_RXRDY    (1 << 0)   /**< \brief ����׼������          */
#define AMHW_USART_STAT_RXIDLE   (1 << 1)   /**< \brief ���տ���              */
#define AMHW_USART_STAT_TXRDY    (1 << 2)   /**< \brief ����׼������          */
#define AMHW_USART_STAT_TXIDLE   (1 << 3)   /**< \brief ���Ϳ���              */

/** \brief ��λʵʱ��ӳ��ǰ��CTS�ź�״̬  */
#define AMHW_USART_STAT_CTS      (1 << 4)

/**
 * \brief ������⵽CTS�źŷ����仯���ñ�־��������
 */
#define AMHW_USART_STAT_DELTACTS (1 << 5)

#define AMHW_USART_STAT_TXDIS    (1 << 6)   /**< \brief ���ͽ���״̬��־      */
#define AMHW_USART_STAT_OVR      (1 << 8)   /**< \brief ��������־          */
#define AMHW_USART_STAT_BREAK    (1 << 10)  /**< \brief �����жϱ�־          */

/**
 * \brief ������⵽����break״̬�仯���ñ�־��������
 */
#define AMHW_USART_STAT_DELTARXBRK    (1 << 11)

/**
 * ������������⵽��ʼ��START���ź�
 */
#define AMHW_USART_STAT_START       (1 << 12)

#define AMHW_USART_STAT_FRMERR      (1 << 13)  /**< \brief ֡�����־         */
#define AMHW_USART_STAT_PARERR      (1 << 14)  /**< \brief ��żУ������־   */
#define AMHW_USART_STAT_RXNOISE     (1 << 15)  /**< \brief ����������־       */
#define AMHW_USART_STAT_ABAUDERR    (1 << 16)  /**< \brief �Զ������ʴ����־ */

/** @} */

/**
 * \name USART�����ж�״̬��־������ͨ������am_uart_intstat_get()��ȡ�ж�״̬
 * @{
 */

#define AMHW_USART_INTSTAT_RXRDY      (1 << 0) /**< \brief ����׼������       */
#define AMHW_USART_INTSTAT_TXRDY      (1 << 2) /**< \brief ����׼������       */
#define AMHW_USART_INTSTAT_TXIDLE     (1 << 3) /**< \brief ���Ϳ���           */

/**
 * \brief ������⵽CTS�źŷ����仯��
 */
#define AMHW_USART_INTSTAT_DELTACTS   (1 << 5)

#define AMHW_USART_INTSTAT_TXDIS      (1 << 6) /**< \brief ���ͽ����жϱ�־   */
#define AMHW_USART_INTSTAT_OVR        (1 << 8) /**< \brief ����жϱ�־       */


/**
 * \brief ������⵽����break״̬�仯
 */
#define AMHW_USART_INTSTAT_DELTARXBRK (1 << 11)

/**
 * \brief ��������⵽��ʼ��START���ź�
 */
#define AMHW_USART_INTSTAT_START     (1 << 12)

#define AMHW_USART_INTSTAT_FRMERR    (1 << 13) /**< \brief ֡�����ж�         */
#define AMHW_USART_INTSTAT_PARERR    (1 << 14) /**< \brief ��żУ������ж�   */
#define AMHW_USART_INTSTAT_RXNOISE   (1 << 15) /**< \brief ���������ж�       */
#define AMHW_USART_INTSTAT_ABAUDERR  (1 << 16) /**< \brief �Զ������ʴ����ж� */

/** @} interrupt state */

/**
 * \name �����ж�Դ����
 * @{
 */

#define AMHW_USART_INT_RXRDY      (1 << 0) /**< \brief ����׼������           */
#define AMHW_USART_INT_TXRDY      (1 << 2) /**< \brief ����׼������           */
#define AMHW_USART_INT_TXIDLE     (1 << 3) /**< \brief ���Ϳ���               */
#define AMHW_USART_INT_DELTACTS   (1 << 5) /**< \brief ��⵽CTS�źŷ����仯  */
#define AMHW_USART_INT_TXDIS      (1 << 6) /**< \brief ��������ֹ�ж�         */
#define AMHW_USART_INT_OVR        (1 << 8) /**< \brief ����ж�               */

/** \brief ��⵽����break״̬�仯       */
#define AMHW_USART_INT_DELTARXBRK     (1 << 11)

/** \brief ��������⵽��ʼ��START���ź� */
#define AMHW_USART_INT_START          (1 << 12)

#define AMHW_USART_INT_FRMERR      (1 << 13) /**< \brief ֡�����ж�           */
#define AMHW_USART_INT_PARERR      (1 << 14) /**< \brief ��żУ������ж�     */
#define AMHW_USART_INT_RXNOISE     (1 << 15) /**< \brief ���������ж�         */
#define AMHW_USART_INT_ABAUDERR    (1 << 16) /**< \brief �Զ������ʴ����ж�   */

#define AMHW_USART_INT_ALL         (0x1F96D) /**< \brief �����ж�             */

/** @} */

/**
 * \brief ���ô���
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] cfg_flags  : AMHW_USART_CFG_*��ֵ����AMHW_USART_CFG_*��Ļ�ֵ
 *                         (#AMHW_USART_CFG_8BIT)
 *
 * \return ��
 *
 * \note ������ڵ�ʱ��Դ��RTC�����������ʱ�ӣ�����Ƶ��Ϊ32.768KHz�������
 *       ʹ��#AMHW_USART_CFG_MODE32K ��־������ǰ��ȷ�����ڴ��ڽ���״̬��
 *       ͨ�����ú��� amhw_usart_disable()��
 */
am_static_inline
void amhw_usart_config (amhw_usart_t *p_hw_usart, uint32_t cfg_flags)
{
    p_hw_usart->cfg = cfg_flags;
}

/**
 * \brief ���ô��ڿ��ƼĴ���ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] ctl_flags  :  AMHW_USART_CTL_*��ֵ����AMHW_USART_CTL_*��Ļ�ֵ
 *                         (#AMHW_USART_CTL_ADDRDET)
 * \return ��
 */
am_static_inline
void amhw_usart_control (amhw_usart_t *p_hw_usart, uint32_t ctl_flags)
{
    p_hw_usart->ctl = ctl_flags;
}

/**
 * \brief ���ÿ��ƼĴ�������ӦλΪ1
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] flags      : AMHW_USART_CTL_*��ֵ����AMHW_USART_CTL_*��Ļ�ֵ
 *                         (#AMHW_USART_CTL_ADDRDET)��δ���õ�λ����Ӱ�졣
 *
 * \return ��
 */
am_static_inline
void amhw_usart_ctl_set (amhw_usart_t *p_hw_usart, uint32_t flags)
{
    p_hw_usart->ctl |= flags;
}

/**
 * \brief ������ƼĴ���
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] flags      : AMHW_USART_CTL_*��ֵ����AMHW_USART_CTL_*��Ļ�ֵ
 *                         (#AMHW_USART_CTL_ADDRDET)��δ���õ�λ����Ӱ�졣
 *
 * \return ��
 */
am_static_inline
void amhw_usart_ctl_clr (amhw_usart_t *p_hw_usart, uint32_t flags)
{
    p_hw_usart->ctl &= ~flags;
}

/**
 * \brief ʹ�ܴ���
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_usart_enable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->cfg |= 0x01;
}

/**
 * \brief ���ܴ���
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_usart_disable (amhw_usart_t *p_hw_usart)
{
    p_hw_usart->cfg &= ~(0x01);
}

/**
 * \brief ��ȡ����״̬
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \return ����״̬��AMHW_USART_STAT_*��ֵ����AMHW_USART_STAT_*��Ļ�ֵ
 *         ��#AMHW_USART_STAT_OVR��
 */
am_static_inline
uint32_t amhw_usart_stat_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->stat;
}

/**
 * \brief �ȴ����ڷ��Ϳ���
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \return ��
 */
am_static_inline
void amhw_usart_wait_idle (amhw_usart_t *p_hw_usart)
{
    while ((p_hw_usart->stat & AMHW_USART_STAT_TXIDLE) == 0);
}

/**
 * \brief �������״̬��־
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] clr_flags  : AMHW_USART_STAT_*��ֵ����AMHW_USART_STAT_*��Ļ�ֵ
 *                         (#AMHW_USART_STAT_START)
 *
 * \return ��
 *
 * \note �������־���Զ����.�ٲ��ֱ�־����Ҫ������:
 *       #AMHW_USART_STAT_DELTACTS, #AMHW_USART_STAT_OVR, #AMHW_USART_STAT_DELTARXBRK,
 *       #AMHW_USART_STAT_START, #AMHW_USART_STAT_FRMERR, #AMHW_USART_STAT_PARERR
 *       #AMHW_USART_STAT_RXNOISE, #AMHW_USART_STAT_ABAUDERR
 */
am_static_inline
void amhw_usart_stat_clr (amhw_usart_t *p_hw_usart, uint32_t clr_flags)
{
    p_hw_usart->stat = clr_flags;
}

/**
 * \brief �õ������ж�״̬
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \return AMHW_USART_INTSTAT_*��ֵ����AMHW_USART_INTSTAT_*��Ļ�ֵ
 *         (#AMHW_USART_INTSTAT_RXRDY)
 */
am_static_inline
uint32_t amhw_usart_intstat_get (amhw_usart_t *p_hw_usart)
{
    return p_hw_usart->intstat;
}

/**
 * \brief ʹ��ָ���Ĵ����ж�
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] int_enable : AMHW_USART_INT_* ��ֵ����AMHW_USART_INT_*��Ļ�ֵ
 *                         (#AMHW_USART_INT_RXRDY)
 *
 * \return ��
 */
am_static_inline
void amhw_usart_int_enable (amhw_usart_t *p_hw_usart, uint32_t int_enable)
{
     p_hw_usart->int_enset |= int_enable;
}

/**
 * \brief ����ָ���Ĵ����ж�
 *
 * \param[in] p_hw_usart  : ָ�򴮿ڼĴ������ָ��
 * \param[in] int_disable : AMHW_USART_INT_* ��ֵ����AMHW_USART_INT_*��Ļ�ֵ
 *                          (#AMHW_USART_INT_RXRDY)
 *
 * \return ��
 */
am_static_inline
void amhw_usart_int_disable (amhw_usart_t *p_hw_usart, uint32_t int_disable)
{
     p_hw_usart->int_enclr = int_disable;
}

/**
 * \brief д���ڷ��ͼĴ���ֵ������һ�����ݣ�
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] data       : ���͵�����
 *
 * \return ��
 */
am_static_inline
void amhw_usart_txdata_write (amhw_usart_t *p_hw_usart, uint32_t data)
{
     p_hw_usart->txdat = data;
}

/**
 * \brief ��ȡ���ڽ�������
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \return ���ڽ��յ�������
 */
am_static_inline
uint32_t amhw_usart_rxdata_read (amhw_usart_t *p_hw_usart)
{
     return p_hw_usart->rxdat;
}

/**
 * \brief ��ȡ���ڽ������ݣ�ͬʱ�����������״̬
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \return ��ȡ����ֵ
 *          - bit0 ~ bit8 : ���յ�������
 *          - bit13       : ֡����״̬
 *          - bit14       : ��żУ�����״̬
 *          - bit15       : ��������
 */
am_static_inline
uint32_t amhw_usart_rxdata_stat_read (amhw_usart_t *p_hw_usart)
{
     return p_hw_usart->rxdatstat;
}

/**
 * \brief ���ô��ڲ����ʲ����Ĵ���ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] brg_val    : ����ֵ������ʱ�ӽ���(brg_val + 1)��Ƶ
 *
 * \return ��
 *
 * \note ���ڲ����ʲ�������һ���򵥵�16λ������Ƶ������32k RTC��Ϊʱ��Դʱ���÷�
 *       Ƶ����Ȼ��Ч�����Ҫ�õ�9600�Ĳ����ʣ���ֵ�ͱ�������Ϊ0.
 *       ������ֵǰ��ȷ������û�����ڽ��з��ͺͽ��ա�
 */
am_static_inline
void amhw_usart_brg_set (amhw_usart_t *p_hw_usart, uint16_t brg_val)
{
    p_hw_usart->brg = brg_val;
}

/**
 * \brief ���ù�����ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] osr_val    : ���ͺͽ���ÿλʹ��(osr_val + 1)��ʱ�ӽ��в�������Чֵ
 *                         Ϊ 4 ~ 15.
 *
 * \return ��
 *
 * \note OSR�Ĵ������������첽ģʽ�µĹ�����ֵ��Ĭ�ϲ���ֵ��16��
 */
am_static_inline
void amhw_usart_osr_set (amhw_usart_t *p_hw_usart, uint8_t osr_val)
{
    if (osr_val >= 4 && osr_val <= 15) {
        p_hw_usart->osr = osr_val;
    }
}

/**
 * \brief ���õ�ַ�Ĵ�����ֵ
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] addr_val   : 8λ�ĵ�ֵַ
 *
 * \return ��
 *
 * \note �ڵ�ַƥ��ģʽ�У����ʹ���˵�ַ�Զ�ƥ��ģʽ����õ�ַ�Ĵ��������ŵĵ�
 *       ֵַ����Ӳ����ַƥ�䡣
 */
am_static_inline
void amhw_usart_addr_set (amhw_usart_t *p_hw_usart, uint8_t addr_val)
{
    p_hw_usart->addr = addr_val;
}

/**
 * \brief ���ڲ���������
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] u_clk      : ���ڵ�����ʱ��Ƶ��
 * \param[in] baudrate   : �������õĴ��ڲ�����
 *
 * \return ����0��ʾʵ�ʵĲ����ʣ�С��0��������ʧ�ܡ�
 */
int amhw_usart_baudrate_set (amhw_usart_t *p_hw_usart,
                             uint32_t      u_clk,
                             uint32_t      baudrate);

/**
 * \brief USART���ݷ���(��ѯģʽ)
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] p_txbuf    : �������ݻ�����
 * \param[in] nbytes     : �������ݸ���
 *
 * \return �ɹ����͵����ݸ���
 */
int amhw_usart_poll_send(amhw_usart_t  *p_hw_usart,
                         const uint8_t *p_txbuf,
                         uint32_t       nbytes);

/**
 * \brief USART���ݽ���(��ѯģʽ)
 *
 * \param[in] p_hw_usart : ָ�򴮿ڼĴ������ָ��
 * \param[in] p_rxbuf    : �������ݻ�����
 * \param[in] nbytes     : �������ݸ���
 *
 * \return �ɹ����յ����ݸ���
 */
int amhw_usart_poll_receive(amhw_usart_t *p_hw_usart,
                            uint8_t      *p_rxbuf,
                            uint32_t      nbytes);

/**
 * @} amhw_if_usart
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_USART_H */

/* end of file */

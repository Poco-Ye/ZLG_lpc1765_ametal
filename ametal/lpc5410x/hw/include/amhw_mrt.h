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
 * \brief MRT(Multi-Rate Timer)�����ӿ�
 *
 * 1. 24λ��Ƶ�ʶ�ʱ����
 * 2. 4�����������¼���ͨ�����ɷֱ����ö�����ֵ��
 * 3. ֧���ظ��ж�ģʽ��һ�μ�ʱģʽ��һ�μ�ʱ������ͣ�ͣ�ģʽ��
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_MRT_H
#define __AMHW_MRT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_mrt
 * \copydoc amhw_mrt.h
 * @{
 */
 
/**
 * \brief MRTͨ��������
 */
#define AMHW_MRT_CHANNELS_NUM      (4)   
    
/** 
 * \brief MRTͨ��ID,���ڲ��������ĳ��ͨ������Ч��Χ��0 ~ AMHW_MRT_CHANNELS_NUM - 1 
 */
#define AMHW_MRT_CH(n)             (n)
    
/**
 * \brief MRT ͨ���Ĵ�����ṹ��
 */
typedef struct amhw_mrt_chan {
    __IO uint32_t intval;                /**< \brief ͨ����ʱ���ֵ���üĴ��� */
    __O  uint32_t timer;                 /**< \brief ��ǰͨ������ֵֵ�Ĵ���   */
    __IO uint32_t ctrl;                  /**< \brief ��ʱ��ͨ�����ƼĴ���     */
    __IO uint32_t stat;                  /**< \brief ��ʱ��ͨ��״̬�Ĵ���     */
} amhw_mrt_chan_t;

/**
 * \brief MRT�Ĵ�����ṹ��
 */
typedef struct amhw_mrt {
    amhw_mrt_chan_t channel[AMHW_MRT_CHANNELS_NUM]; /**< \brief ͨ���Ĵ�����   */
    uint32_t        unused[44];                     /**< \brief ��������Ӧʹ�� */
    __IO uint32_t   modcfg;                         /**< \brief ģʽ���üĴ��� */
    __O  uint32_t   idle_ch;                        /**< \brief ����ͨ���Ĵ��� */
    __IO uint32_t   irq_flag;                       /**< \brief �жϱ�־�Ĵ��� */ 
} amhw_mrt_t;

/**
 * \brief MRT ģʽ����
 */
typedef enum {
    AMHW_MRT_MODE_REPEAT        = (0 << 1),  /**< \brief �ظ���ʱ�ж�ģʽ     */
    AMHW_MRT_MODE_ONESHOT       = (1 << 1),  /**< \brief һ�μ�ʱ�ж�ģʽ     */
    AMHW_MRT_MODE_ONESHOT_STALL = (2 << 1)   /**< \brief һ�μ�ʱ����ͣ��ģʽ */
} amhw_mrt_mode_t;

/**
 * \name ����MRT�Ĵ��������ĺ궨��
 * @{
 */
 
/** \brief ����ʱֵ��24λ�����ֵ       */
#define AMHW_MRT_INTVAL_MAX       (0xFFFFFF)  

/** \brief ǿ������д���ʱֵ             */
#define AMHW_MRT_INTVAL_LOAD      (1ul << 31)

/** \brief �ж�ʹ��                       */
#define AMHW_MRT_CTRL_INTEN       (1ul << 0)

/** \brief ģʽ��������λ                 */
#define AMHW_MRT_CTRL_MODE_MASK   (3ul << 1)
 
/** \brief �жϱ�־                       */
#define AMHW_MRT_STAT_INTFLAG     (1ul << 0)

/** \brief ͨ�����б�־                   */
#define AMHW_MRT_STAT_RUNNING     (1ul << 1)

/** \brief ͨ��ʹ�ñ�־                   */
#define AMHW_MRT_STAT_INUSE       (1ul << 2)

/** @}*/

/**
 * \brief ����ͨ���Ķ�ʱֵ��INTVAL��
 *
 *  ��ֵ�ᱻת�ؽ�timer����ǰͨ������ֵֵ�Ĵ������У�ͨ������� 
 *  ����ֵ - 1 ��ʼ�ݼ����� 
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 * \param[in] value    ����ʱֵ��INTVAL����24λ��Ч��
 * \param[in] forced   : TRUE : INTVALֵ������ת��
 *                       FALSE: NTVALֵ�¸���ʱ��������ת��
 *
 * \return ��
 */
am_static_inline
void amhw_mrt_intval_set (amhw_mrt_t *p_hw_mrt,
                          uint8_t     chan,
                          uint32_t    value,
                          bool_t      forced)
{
    value &= AMHW_MRT_INTVAL_MAX; 
    
    /* ֵ������ת����timer������ */
    if (forced == TRUE) {
        value |= AMHW_MRT_INTVAL_LOAD;
    }
    
    p_hw_mrt->channel[chan].intval = value;
}

/**
 * \brief ��ȡ��ʱ����ͨ����ʱֵ��INTVAL��
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ͨ����ʱֵ��INTVAL��
 */
am_static_inline
uint32_t amhw_mrt_intval_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (p_hw_mrt->channel[chan].intval) & AMHW_MRT_INTVAL_MAX;
}

/**
 * \brief ��ȡ��ʱ��ͨ����ǰ�����¼�������ֵ
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ͨ����ǰ�����¼�������ֵ����intval - 1 ��ʼ�ݼ���
 */
am_static_inline 
uint32_t amhw_mrt_chan_count_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (p_hw_mrt->channel[chan].timer);
}


/**
 * \brief ʹ�ܶ�ʱ��ͨ���ж�
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ��
 */
am_static_inline  
void amhw_mrt_int_enable (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->channel[chan].ctrl |= AMHW_MRT_CTRL_INTEN;
}

/**
 * \brief ���ܶ�ʱ��ͨ���ж�
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ��
 */
am_static_inline 
void amhw_mrt_int_disable (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->channel[chan].ctrl &= ~AMHW_MRT_CTRL_INTEN;
}

/**
 * \brief ���ö�ʱ��ͨ��ģʽ
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 * \param[in] mode     : ��ʱ��ͨ��ģʽ
 *
 * \return �� 
 */
am_static_inline
void amhw_mrt_mode_set (amhw_mrt_t     *p_hw_mrt, 
                        uint8_t         chan,
                        amhw_mrt_mode_t mode)
{
    p_hw_mrt->channel[chan].ctrl = (p_hw_mrt->channel[chan].ctrl 
                                 & (~AMHW_MRT_CTRL_MODE_MASK))
                                 | (uint32_t) mode;
}
/**
 * \brief ��ȡ��ʱ��ͨ����ģʽ
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ��ʱ��ͨ����ģʽ
 */
am_static_inline
amhw_mrt_mode_t amhw_mrt_mode_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (amhw_mrt_mode_t)(p_hw_mrt->channel[chan].ctrl 
                                     & AMHW_MRT_CTRL_MODE_MASK);
}


/**
 * \brief ��Ƭ��ͨ��״̬
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��.
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ͨ��״̬�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_mrt_stat_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return p_hw_mrt->channel[chan].stat;
}

/**
 * \brief ���ͨ�����ж�״̬��־������ͨ�������״̬�Ĵ�����
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��.
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ��
 */
am_static_inline
void amhw_mrt_int_flag_clr (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->channel[chan].stat |= AMHW_MRT_STAT_INTFLAG;
}


/**
 * \brief ��ȡ��ǰ���е�ͨ���У�ͨ������С��ͨ��
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \return ͨ������С�Ŀ���ͨ����ͨ����
 */
am_static_inline
uint8_t amhw_mrt_idle_channel_get (amhw_mrt_t *p_hw_mrt)
{
    return (uint8_t)((p_hw_mrt->idle_ch) >> 4);
}

/**
 * \brief ��ȡָ��ͨ�����ж�״̬
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ��
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
* \retval  TRUE  : �жϷ���
* \retval  FALSE : �ж�δ����
 */
am_static_inline
bool_t amhw_mrt_int_pending_get (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    return (bool_t)((p_hw_mrt->irq_flag & (1 << chan)) != 0);
}

/**
 * \brief ���ͨ�����жϹ����־������ȫ���жϱ�־�Ĵ�����
 *
 * \param[in] p_hw_mrt : ָ��MRT�Ĵ������ָ�� 
 * \param[in] chan     : ͨ��ID��ʹ�ú�#AMHW_MRT_CH(n)
 *
 * \return ��
 */
am_static_inline
void amhw_mrt_int_pending_clr (amhw_mrt_t *p_hw_mrt, uint8_t chan)
{
    p_hw_mrt->irq_flag = (1 << chan);
}

/**
 * @} amhw_if_mrt
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_MRT_H */

/* end of file */

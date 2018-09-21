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
 * \brief PINT Ӳ�������ӿ�
 *
 * �����жϣ�
 * �C ��GPIO�Ķ˿�0���˿�1���ߴ�8����ѡ��������Ϊ�����жϣ�֧�ֱ��ػ��ƽ����
 *   �ж�����ÿһ���ж����������NVIC�н����������жϣ�
 * �C ���������жϿ�����Ϊ�����ء��½��ػ�˫���أ�
 * �C ��ƽ�����жϿ�����Ϊ�ߵ�ƽ��͵�ƽ��
 *
 * \internal
 * \par Modification History
 * - 1.10 15-01-01  hbt, modified.
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */
#ifndef __AMHW_PINT_H
#define __AMHW_PINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_pint
 * \copydoc amhw_pint.h
 * @{
 */

/**
 * \brief LPC5410X �����жϼĴ�����ṹ��
 */
typedef struct amhw_pint {
    __IO uint32_t isel;   /**< \brief �����ж�ģʽ�Ĵ���               */
    __IO uint32_t ienr;   /**< \brief �����ػ��ƽ�ж�ʹ�ܼĴ���       */
    __IO uint32_t sienr;  /**< \brief �����ػ��ƽ�ж����üĴ���       */
    __IO uint32_t cienr;  /**< \brief �����ػ��ƽ�ж����ʹ�ܼĴ���   */
    __IO uint32_t ienf;   /**< \brief �½��ػ�ߵ�ƽ�ж�ʹ�ܼĴ���     */
    __IO uint32_t sienf;  /**< \brief �½��ػ�ߵ�ƽ�ж����üĴ���     */
    __IO uint32_t cienf;  /**< \brief �½��ػ�ߵ�ƽ�ж����ʹ�ܼĴ��� */
    __IO uint32_t rise;   /**< \brief �����ؼĴ���                     */
    __IO uint32_t fall;   /**< \brief �½��ؼĴ���                     */
    __IO uint32_t ist;    /**< \brief �����ж�״̬�Ĵ���               */
    __IO uint32_t pmctrl; /**< \brief ģʽƥ���жϿ��ƼĴ���           */
    __IO uint32_t pmsrc;  /**< \brief ģʽƥ���ж�λ�Ĵ���             */
    __IO uint32_t pmcfg;  /**< \brief ģʽƥ���ж�λ���ƼĴ���         */
} amhw_pint_t;

/**
 * \name LPC5410X �����жϺ�ģʽƥ������Ĵ���λ��ͺ궨��
 * @{
 */
 
/** \brief �����ж�ģʽ���� */
#define AMHW_PINT_ISEL_PMODE_MASK      ((uint32_t)0x00FF)

/** \brief ģʽƥ��������� */
#define AMHW_PINT_PMCTRL_MASK          ((uint32_t)0xFF000003)

/** 
 * \brief ģʽƥ��ָ��8�������жϿ��ơ�
 */
#define AMHW_PINT_PMCTRL_PMATCH_SEL    (1 << 0)

/**
 * \brief ��ָ���������ʽ��ֵΪ�棬ʹ�ܡ������¼��������CPU�ͣ���GPIO�����
 */
#define AMHW_PINT_PMCTRL_RXEV_ENA      (1 << 1)

/** \brief ����Դ��ʼλ */
#define AMHW_PINT_SRC_BITSOURCE_START  8

/** \brief ����Դ���� */
#define AMHW_PINT_SRC_BITSOURCE_MASK   7

/** \brief ������ʼλ */
#define AMHW_PINT_SRC_BITCFG_START     8

/** \brief �������� */
#define AMHW_PINT_SRC_BITCFG_MASK      7

/** @} */

/**
 * \name LPC5410X �����ж�ͨ�����
 * \anchor grp_amhw_pint_chan
 * @{
 */
 
#define AMHW_PINT_CHAN_0      (1 << 0)     /**< \brief �����ж�ͨ�� 0  */
#define AMHW_PINT_CHAN_1      (1 << 1)     /**< \brief �����ж�ͨ�� 1  */
#define AMHW_PINT_CHAN_2      (1 << 2)     /**< \brief �����ж�ͨ�� 2  */
#define AMHW_PINT_CHAN_3      (1 << 3)     /**< \brief �����ж�ͨ�� 3  */
#define AMHW_PINT_CHAN_4      (1 << 4)     /**< \brief �����ж�ͨ�� 4  */
#define AMHW_PINT_CHAN_5      (1 << 5)     /**< \brief �����ж�ͨ�� 5  */
#define AMHW_PINT_CHAN_6      (1 << 6)     /**< \brief �����ж�ͨ�� 6  */
#define AMHW_PINT_CHAN_7      (1 << 7)     /**< \brief �����ж�ͨ�� 7  */
#define AMHW_PINT_CHAN_(ch)   (1 << (ch))  /**< \brief �����ж�ͨ�� ch */

/** @} */

/**
 * \brief ��������Ϊ��������
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_edge_set (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->isel = (p_hw_pint->isel & AMHW_PINT_ISEL_PMODE_MASK) & ~chan;
}

/**
 * \brief ��������Ϊ��ƽ����
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_level_set (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->isel = (p_hw_pint->isel & AMHW_PINT_ISEL_PMODE_MASK) | chan;
}

/**
 * \brief ��ȡ�����ж�����״̬
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 *
 * \retval  0 : ��������
 * \retval  1 : ��ƽ����
 */
am_static_inline 
uint32_t amhw_pint_mode_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->isel & AMHW_PINT_ISEL_PMODE_MASK;
}

/**
 * \brief ��ȡ�����ػ��ƽ���е�ʹ��״̬
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 *
 * \retval  0 : ����
 * \retval  1 : ʹ��
 */
am_static_inline 
uint32_t amhw_pint_high_enabled_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->ienr;
}

/**
 * \brief ʹ�������ػ��ƽ�����ж�
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_high_enable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->sienr = chan;
}

/**
 * \brief ���������ػ��ƽ�����ж�
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_high_disable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->cienr = chan;
}

/**
 * \brief ��ȡ�½����ж�״̬����Ч��ƽ�ж�״̬
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \retval  0 : �½����жϽ��ܻ�͵�ƽ�ж�
 * \retval  1 : �½����ж�ʹ�ܻ�ߵ�ƽ�ж�
 */
am_static_inline 
uint32_t amhw_pint_low_enabled_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->ienf;
}

/**
 * \brief ѡ��ߵ�ƽ���½����ж�
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_low_enable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->sienf = chan;
}

/**
 * \brief ���ܵ͵�ƽ���½����ж�
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
*/
am_static_inline 
void amhw_pint_low_disable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->cienf = chan;
}

/**
 * \brief ��ȡ�����ؼ���״̬�����д���״̬
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    ״̬
 */
am_static_inline 
uint32_t amhw_pint_rise_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->rise;
}

/**
 * \brief �����Ӧ���ŵ������ؼ��
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_rise_clr (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->rise = chan;
}

/**
 * \brief ��ȡ�½��ؼ���״̬�����д���״̬
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    ״̬��
 */
am_static_inline 
uint32_t amhw_pint_fall_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->fall;
}

/**
 * \brief �����Ӧ���ŵ��½��ؼ��
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_fall_clr (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->fall = chan;
}

/**
 * \brief ��ȡ�ж�״̬
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    �ж�״̬ (PININTn �� bit n = 1����ζ���ж�pending).
 */
am_static_inline 
uint32_t amhw_pint_status_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->ist;
}

/**
 * \brief ���ͨ����Ӧ���ŵı��ش�������
 *
 * �ж�ģʽѡ���������ʱ��������ش������ܣ�
 * �ж�ģʽѡ���ƽ����ʱ���л�������ƽ��
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ���ţ��μ� 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    ��
 */
am_static_inline 
void amhw_pint_status_clr (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->ist = chan;
}

/**
 * \brief ʹ��ģʽƥ���ж�
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_pint_match_enable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           | AMHW_PINT_PMCTRL_PMATCH_SEL;
}

/**
 * \brief ����ģʽƥ���ж�
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_pint_match_disable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           & ~AMHW_PINT_PMCTRL_PMATCH_SEL;
}

/**
 * \brief ʹ�������жϵġ������¼������
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_pint_match_rxev_enable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           | AMHW_PINT_PMCTRL_RXEV_ENA;
}

/**
 * \brief ���������жϵġ������¼������
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_pint_match_rxev_disable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           & ~AMHW_PINT_PMCTRL_RXEV_ENA;
}

/**
 * \brief ��ȡģʽƥ��״̬
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \return    8 bit ��ģʽƥ��״̬����ĳһλΪ1ʱ�����Ӧ�� product term ƥ��
 */
am_static_inline 
uint32_t amhw_pint_match_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->pmctrl >> 24;
}
   
/**
 * \brief �����ж�ͨ������
 */
typedef enum amhw_pint_select {
    AMHW_PINT_SELECT0 = 0,       /**< \brief �����ж�ѡ��ͨ��0 */
    AMHW_PINT_SELECT1 = 1,       /**< \brief �����ж�ѡ��ͨ��1 */
    AMHW_PINT_SELECT2 = 2,       /**< \brief �����ж�ѡ��ͨ��2 */
    AMHW_PINT_SELECT3 = 3,       /**< \brief �����ж�ѡ��ͨ��3 */
    AMHW_PINT_SELECT4 = 4,       /**< \brief �����ж�ѡ��ͨ��4 */
    AMHW_PINT_SELECT5 = 5,       /**< \brief �����ж�ѡ��ͨ��5 */
    AMHW_PINT_SELECT6 = 6,       /**< \brief �����ж�ѡ��ͨ��6 */
    AMHW_PINT_SELECT7 = 7        /**< \brief �����ж�ѡ��ͨ��7 */
} amhw_pint_select_t;


/**
 * \brief ������ʽ����
 */
typedef enum amhw_pint_trigger_mode { 
    AMHW_PINT_TRIGGER_HIGH       = 0x0,   /**< \brief �ߵ�ƽ���� */
    AMHW_PINT_TRIGGER_LOW        = 0x1,   /**< \brief �͵�ƽ���� */
    AMHW_PINT_TRIGGER_RISE       = 0x2,   /**< \brief �����ش��� */
    AMHW_PINT_TRIGGER_FALL       = 0x3,   /**< \brief �½��ش��� */
    AMHW_PINT_TRIGGER_BOTH_EDGES = 0x4    /**< \brief ˫���ش��� */
} amhw_pint_trigger_mode_t;

/**
 * \brief ������ʽѡ��
 *
 * \param[in] p_hw_pint    : ָ�������жϼĴ������ָ��
 * \param[in] chan         : �����ж�ͨ���ţ��μ�
 *                           \ref grp_amhw_pint_chan
 * \param[in] trigger_type : ��ʽѡ��
 *                           - AMHW_PINT_TRIGGER_HIGH       : �ߵ�ƽ����
 *                           - AMHW_PINT_TRIGGER_LOW        : �͵�ƽ����
 *                           - AMHW_PINT_TRIGGER_RISE       : �����ش���
 *                           - AMHW_PINT_TRIGGER_FALL       : �½��ش���
 *                           - AMHW_PINT_TRIGGER_BOTH_EDGES : ˫���ش���
 *
 * \return    ��
 */
void amhw_pint_trigger_select(amhw_pint_t              *p_hw_pint, 
                              uint8_t                   chan,
                              amhw_pint_trigger_mode_t  trigger_type);

/**
 * \brief �����ж�λƬ���
 */
typedef enum amhw_pint_bitslice {
    AMHW_PINT_BITSLICE0 = 0,            /**< \brief λƬ0���  */
    AMHW_PINT_BITSLICE1,                /**< \brief λƬ1���  */
    AMHW_PINT_BITSLICE2,                /**< \brief λƬ2���  */
    AMHW_PINT_BITSLICE3,                /**< \brief λƬ3���  */
    AMHW_PINT_BITSLICE4,                /**< \brief λƬ4���  */
    AMHW_PINT_BITSLICE5,                /**< \brief λƬ5���  */
    AMHW_PINT_BITSLICE6,                /**< \brief λƬ6���  */
    AMHW_PINT_BITSLICE7                 /**< \brief λƬ7���  */
} amhw_pint_bitslice_t;

/**
 * \brief ���������ж�ģʽƥ���Դ
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] chan      : �����ж�ͨ����
 * \param[in] slicenum  : λƬ���
 *
 * \return    ��
 */
void amhw_pint_match_src_set(amhw_pint_t          *p_hw_pint, 
                             amhw_pint_select_t    chan, 
                             amhw_pint_bitslice_t  slicenum);

/**
 * \brief ����ƥ���ж�λƬ����ֵ
 */
typedef enum amhw_pint_bitslice_cfg {
    AMHW_PINT_PATTERNCONST1          = 0x0, /**< \brief ��׼1��        */ 
    AMHW_PINT_PATTERNRISING          = 0x1, /**< \brief ������         */ 
    AMHW_PINT_PATTERNFALLING         = 0x2, /**< \brief �½���         */ 
    AMHW_PINT_PATTERNRISINGORFALLING = 0x3, /**< \brief �����ػ��½��� */ 
    AMHW_PINT_PATTERNHIGH            = 0x4, /**< \brief �ߵ�ƽ         */ 
    AMHW_PINT_PATTERNLOW             = 0x5, /**< \brief �͵�ƽ         */ 
    AMHW_PINT_PATTERNCONST0          = 0x6, /**< \brief ��׼0          */ 
    AMHW_PINT_PATTERNEVENT           = 0x7  /**< \brief �¼�           */ 
} amhw_pint_bitslice_cfg_t;

/**
 * \brief �������ж�������ģʽƥ��
 *
 * \param[in] p_hw_pint : ָ�������жϼĴ������ָ��
 * \param[in] slice_num : λƬ���
 * \param[in] slice_cfg : λƬ���ò���
 * \param[in] end_point : �����ֵΪTURE����ǰλƬ��Ϊ���չ���
 *
 * \return    ��
 */
void amhw_pint_match_config(amhw_pint_t              *p_hw_pint, 
                            amhw_pint_bitslice_t      slice_num, 
                            amhw_pint_bitslice_cfg_t  slice_cfg, 
                            bool_t                    end_point);

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PINT_H */

/* end of file */

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
 * \brief ��Ƕ�������жϿ�����(NVIC) Ӳ�������ӿ�
 * 
 * 1. ��Ƕ���ж�������������CPU��һ���֣�
 * 2. ������ϵ��жϿ������ṩ�˵��ӳ��жϣ�
 * 3. ���������쳣�жϺ������жϣ�
 * 4. Cortex-M4 �� NVIC ֧��:
 *    - 37 ���ж�������
 *    - 8���ɱ���ж����ȼ���Ӳ�����ȼ������Σ�
 *    - �ж�������ƫ�ƼĴ��� VTOR��
 *    - ��������жϣ�
 * 5. Cortex- M0+ ֧��: ǰ32���ж�
 *    - 32���ж�������
 *    - 4���ɱ���ж����ȼ���Ӳ�����ȼ������Σ�
 *    - �ж�������ƫ�ƼĴ��� VTOR��
 * 6. �����жϿ�����Ϊ���������жϡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  hbt, first implementation.
 * \endinternal
 */


#ifndef __AMHW_INT_H
#define __AMHW_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc5410x.h"

/** 
 * \addtogroup amhw_if_int
 * \copydoc amhw_int.h
 * @{
 */

/**
 * \brief NVIC �Ĵ�����ṹ��
 */
typedef struct amhw_int {
    __IO uint32_t  iser[2];                    /**< \brief �ж�ʹ�ܼĴ���       */
    __I  uint32_t  reserved1[30];              /**< \brief ����                 */
    __IO uint32_t  icer[2];                    /**< \brief ����ж�ʹ�ܼĴ���   */   
    __I  uint32_t  reserved2[30];              /**< \brief ����                 */
    __IO uint32_t  ispr[2];                    /**< \brief �жϵȴ��Ĵ���       */ 
    __I  uint32_t  reserved3[30];              /**< \brief ����                 */
    __IO uint32_t  icpr[2];                    /**< \brief ����жϵȴ��Ĵ���   */  
    __I  uint32_t  reserved4[30];              /**< \brief ����                 */
    __I  uint32_t  iabr[2];                    /**< \brief �ж���Ч�Ĵ���       */ 
    __I  uint32_t  reserved5[62];              /**< \brief ����                 */
    __IO uint8_t   ipr[44];                    /**< \brief �ж����ȼ��Ĵ���     */ 
    __I  uint32_t  reserved6[566];             /**< \brief ����                 */
    __I  uint32_t  icsr;                       /**< \brief �жϿ��ƺ�״̬�Ĵ��� */ 
    __I  uint32_t  reserved7[126];             /**< \brief ����                 */
    __O  uint32_t  stir;                       /**< \brief ��������жϼĴ���   */
} amhw_int_t;                                                              

  
/**
 * \brief ��ȡ��ǰ�жϺ�
 * \param[in] p_hw_int : ָ��NVIC�Ĵ������ָ��
 * \return �жϺ�
 */
am_static_inline 
int amhw_inum_get (amhw_int_t *p_hw_int)
{
    return (int)((p_hw_int->icsr - 16) & 0xFF);
}

/**
 * \brief ʹ���ж�
 *
 * \param[in] p_hw_int : ָ��NVIC�Ĵ������ָ��
 * \param[in] inum     : �жϺţ� �μ� 
 *                       \sa lpc5410x_inum.h
 *
 * \return ��
 */
am_static_inline 
void amhw_int_enable (amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->iser[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief �����ж�
 *
 * \param[in] p_hw_int : ָ��NVIC�Ĵ������ָ��
 * \param[in] inum     : �жϺţ� �μ� 
 *                       \sa lpc5410x_inum.h
 *
 * \return ��
 */
am_static_inline 
void amhw_int_disable (amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->icer[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief ��λ�жϵȴ�
 *
 * \param[in] p_hw_int : ָ��NVIC�Ĵ������ָ��
 * \param[in] inum     : �жϺţ� �μ� 
 *                       \sa lpc5410x_inum.h
 *
 * \return    ��
 */
am_static_inline 
void amhw_int_set_pending (amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->ispr[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief ����ȴ��ж�
 *
 * \param[in] p_hw_int : ָ��NVIC�Ĵ������ָ��
 * \param[in] inum     : �жϺţ� �μ� 
 *                       \sa lpc5410x_inum.h
 *
 * \return    ��
 */
am_static_inline 
void amhw_int_clr_pending(amhw_int_t *p_hw_int, int inum)
{
    p_hw_int->icpr[(uint32_t)(inum) >> 5] = (1UL << ((uint32_t)(inum) & 0x1F));
}

/**
 * \brief ��ȡ�ж���Ч״̬
 *
 * \param[in] p_hw_int : ָ��NVIC�Ĵ������ָ��
 * \param[in] inum     : �жϺţ� �μ� 
 *                       \sa lpc5410x_inum.h
 * 
 * \retval TRUE  : ��Ч�ж�
 * \retval FALSE : ��Ч�ж�
 */
am_static_inline 
bool_t amhw_int_active_state(amhw_int_t *p_hw_int, int inum)
{
    return ((p_hw_int->iabr[(uint32_t)(inum) >> 5] & 
            (1UL << ((uint32_t)(inum) & 0x1F))) ? TRUE : FALSE);
}

/**
 * \brief �����ж����ȼ�
 *
 * \param[in] p_hw_int : ָ��NVIC�Ĵ������ָ��
 * \param[in] inum     : �жϺţ� �μ� 
 *                       \sa lpc5410x_inum.h
 * \param[in] prio     : �ж����ȼ�
 * 
 * \return   ��
 */
am_static_inline 
void amhw_int_set_priority (amhw_int_t *p_hw_int, int inum, uint32_t prio)
{
    AMHW_INT->ipr[(uint32_t)(inum) >> 5] = ((prio << 4) & 0xFF);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_INT_H */

/* end of file */

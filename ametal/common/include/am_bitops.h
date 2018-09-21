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
 * \brief λ������ض���ͷ�ļ�
 *
 * ���ļ��ṩ�˳��õ�λ�������ߺ꣬���磺AM_BIT_SET()�� AM_BIT_GET()����������
 * ��ο� \ref am_if_bitops ��
 *
 * \internal
 * \par Modification history:
 * - 1.01 14-12-15  fft, comment formate and translate to English version
 * - 1.00 13-01-15  orz, move defines from am_common.h
 * \endinternal
 */

#ifndef __AM_BITOPS_H
#define __AM_BITOPS_H

/**
 * \addtogroup am_if_bitops
 * \copydoc am_bitops.h
 * @{
 */

/******************************************************************************/

/**
 * \name ͨ��λ��������
 * @{
 */

/** \brief ������λ�� */
#ifndef AM_BITS_PER_LONG
#define AM_BITS_PER_LONG       32
#endif

/** \brief �ֽ�λ�� */
#define AM_BITS_PER_BYTE       8

/** @} */

/******************************************************************************/

/**
 * \name ͨ��λ����
 * @{
 */

#ifndef AM_BIT_MASK

/** \brief ����n bits���� */
#define AM_BIT_MASK(nr)              (1UL << ((nr) % BITS_PER_LONG))
#endif

#ifndef AM_BIT_WORD

/** \brief bitsת��Ϊ�ָ��� */
#define AM_BIT_WORD(nr)              ((nr) / BITS_PER_LONG)
#endif

#ifndef AM_BITS_TO_LONGS

/** \brief bit��long��bit map�е����� */
#define AM_BITS_TO_LONGS(nr)         AM_DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#endif

/** \brief bit��λ */
#define AM_BIT(bit)                  (1u << (bit))

/** \brief ֵ��λ */
#define AM_SBF(value, field)         ((value) << (field))

/** \brief bit��λ */
#define AM_BIT_SET(data, bit)        ((data) |= AM_BIT(bit))

/** \brief bit���� */
#define AM_BIT_CLR(data, bit)        ((data) &= ~AM_BIT(bit))

/** \brief bit��λ, ���� mask ָ����λ */
#define AM_BIT_SET_MASK(data, mask)  ((data) |= (mask))

/** \brief bit����, ���� mask ָ����λ */
#define AM_BIT_CLR_MASK(data, mask)  ((data) &= ~(mask))

/** \brief bit��ת */
#define AM_BIT_TOGGLE(data, bit)     ((data) ^= AM_BIT(bit))

/** \brief bit�޸� */
#define AM_BIT_MODIFY(data, bit, value) \
    ((value) ? AM_BIT_SET(data, bit) : AM_BIT_CLR(data, bit))

/** \brief ����bit�Ƿ���λ */
#define AM_BIT_ISSET(data, bit)      ((data) & AM_BIT(bit))

/** \brief ��ȡbitֵ */
#define AM_BIT_GET(data, bit)        (AM_BIT_ISSET(data, bit) ? 1 : 0)

/** \brief ��ȡ n bits ����ֵ */
#define AM_BITS_MASK(n)              (~((~0u) << (n)))

/** \brief ��ȡλ��ֵ */
#define AM_BITS_GET(data, start, len)  \
    (((data) >> (start)) & AM_BITS_MASK(len))

/** \brief ����λ��ֵ */
#define AM_BITS_SET(data, start, len, value) \
    ((data) = (((data) & ~AM_SBF(AM_BITS_MASK(len), (start))) | \
        AM_SBF((value) & (AM_BITS_MASK(len)), (start))))

/** @} */ 

/**
 * @}  
 */

#endif /* __AM_BITOPS_H */

/* end of file */

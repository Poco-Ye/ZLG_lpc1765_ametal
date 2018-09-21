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
 * \brief ѭ������У��(CRC) �����ӿ�
 *
 * 1. ֧��3��CRC���ɶ���ʽ�� CRC-CCITT, CRC-16, and CRC-32
 *    - CRC-CCITT : x16 + x12 + x5 + 1   (0x1021);
 *    - CRC-16    : x16 + x15 + x2 + 1   (0x8005);
 *    - CRC-32    : x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 +
 *                   x5 + x4 + x2+ x + 1  (0x04C11DB7);
 * 2. ֧���������ݺ�CRCУ��͵�λ�����1's����;
 * 3. �ɱ��������������;
 * 4. ֧�� PIO back-to-back ���䷽ʽ;
 * 5. ֧���������ݿ�ȵ���������: 8λ��16λ��32λ
 *    - 8 λ����д��: ����1������;
 *    - 16λ����д��: ����2������;
 *    - 32λ����д��: ����4�����ڡ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_CRC_H
#define __AMHW_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_crc
 * \copydoc amhw_crc.h
 * @{
 */

/*
 * \brief �����ṹ��εĿ�ʼ
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \brief CRC �Ĵ�����ṹ��
 */
typedef struct amhw_crc {
    __IO    uint32_t    mode;           /**< \brief CRC ģʽ�Ĵ���            */
    __IO    uint32_t    seed;           /**< \brief CRC ���ӼĴ���            */
    union {
        __I     uint32_t    sum;        /**< \brief CRC У��Ĵ���            */
        __O     uint32_t    wrdata32;   /**< \brief CRC д���ݼĴ�����32λд��*/
        __O     uint16_t    wrdata16;   /**< \brief CRC д���ݼĴ�����16λд��*/
        __O     uint8_t     wrdata8;    /**< \brief CRC д���ݼĴ�����8λд�� */
    };
} amhw_crc_t;


/**
 * \name CRCģʽ����
 * @{
 */

#define AMHW_CRC_MODE_WRDATA_BIT_RVS (1 << 2)  /**< \brief ��������λ����             */
#define AMHW_CRC_MODE_WRDATA_CMPL    (1 << 3)  /**< \brief �������ݽ���1's��������    */
#define AMHW_CRC_MODE_SUM_BIT_RVS    (1 << 4)  /**< \brief ���CRCֵλ����            */
#define AMHW_CRC_MODE_SUM_CMPL       (1 << 5)  /**< \brief ���CRCֵʱ����1's�������� */

/** @} */

/**
 * \brief CRC���ɶ���ʽ����
 */
typedef enum amhw_crc_poly {
    AMHW_CRC_POLY_CCITT = 0,              /**< \brief CRC-CCIT ����ʽ   */
    AMHW_CRC_POLY_CRC16 = 1,              /**< \brief CRC-16   ����ʽ   */
    AMHW_CRC_POLY_CRC32 = 2,              /**< \brief CRC-32   ����ʽ   */
} amhw_crc_poly_t;


/**
 * \brief ����CRCģʽ�����ɶ���ʽ
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] poly     : CRC�����ɶ���ʽ
 * \param[in] flags    : AMHW_CRC_MODE_*��ֵ����AMHW_CRC_MODE_*��Ļ�ֵ
 *                        - #AMHW_CRC_MODE_WRDATA_BIT_RVS
 *                        - #AMHW_CRC_MODE_WRDATA_CMPL
 *                        - #AMHW_CRC_MODE_SUM_BIT_RVS
 *                        - #AMHW_CRC_MODE_SUM_CMPL
 *                       ���û�б�־���ã����ֵΪ0.
 *
 * \return ��
 */
am_static_inline
void amhw_crc_mode_set (amhw_crc_t     *p_hw_crc,
                        amhw_crc_poly_t poly,
                        uint32_t        flags)
{
    p_hw_crc->mode = (uint32_t)poly | flags;
}

/**
 * \brief ��ȡCRCģʽ�Ĵ���ֵ
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \return ��ǰCRCģʽ�Ĵ���ֵ
 */
am_static_inline
uint32_t amhw_crc_mode_get (amhw_crc_t *p_hw_crc)
{
    return p_hw_crc->mode;
}

/**
 * \brief ����CRC����ֵ
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] seed     : CRC����ֵ
 *
 * \return ��
 */
am_static_inline
void amhw_crc_seed_set (amhw_crc_t *p_hw_crc, uint32_t seed)
{
    p_hw_crc->seed = seed;
}


/**
 * \brief ��ȡCRC����ֵ
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \return CRC����ֵ
 */
am_static_inline
uint32_t amhw_crc_seed_get (amhw_crc_t *p_hw_crc)
{
    return p_hw_crc->seed;
}

/**
 * \brief д��1��8λ������CRC�������CRC����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] data     : д���8λ����
 *
 * \return ��
 */
am_static_inline
void amhw_crc_wrdata8 (amhw_crc_t *p_hw_crc, uint8_t data)
{
    p_hw_crc->wrdata8 = data;
}

/**
 * \brief д��1��16λ������CRC�������CRC����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] data     : д���16λ����
 *
 * \return ��
 */
am_static_inline
void amhw_crc_wrdata16 (amhw_crc_t *p_hw_crc, uint16_t data)
{
    p_hw_crc->wrdata16 = data;
}

/**
 * \brief д��1��32λ������CRC�������CRC����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] data     : д���32λ����
 *
 * \return ��
 */
am_static_inline
void amhw_crc_wrdata32 (amhw_crc_t *p_hw_crc, uint32_t data)
{
    p_hw_crc->wrdata32 = data;
}

/**
 * \brief д��n��8λ������CRC�������CRC����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] p_data   : ָ�������CRC������������ݻ�����(8λ���ݻ�����)
 * \param[in] nbytes   : 8λ���ݵĸ���
 *
 * \return ��
 */
void amhw_crc_data8_write(amhw_crc_t    *p_hw_crc,
                          const uint8_t *p_data,
                          uint32_t       nbytes);

/**
 * \brief д��n��16λ������CRC�������CRC����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] p_data   : ָ�������CRC������������ݻ�����(16λ���ݻ�����)
 * \param[in] nhwords  : 16λ���ݵĸ���
 *
 * \return ��
 */
void amhw_crc_data16_write(amhw_crc_t     *p_hw_crc,
                           const uint16_t *p_data,
                           uint32_t        nhwords);


/**
 * \brief д��n��32λ������CRC�������CRC����
 *
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \param[in] p_data   : ָ�������CRC������������ݻ�����(32λ���ݻ�����)
 * \param[in] nwords   : 32λ���ݵĸ���
 *
 * \return ��
 */
void amhw_crc_data32_write(amhw_crc_t     *p_hw_crc,
                           const uint32_t *p_data,
                           uint32_t        nwords);

/**
 * \brief ��ȡCRC������ֵ
 * \param[in] p_hw_crc : ָ��CRC�Ĵ������ָ��
 * \return CRC������ֵ
 */
am_static_inline
uint32_t amhw_crc_sum_get (amhw_crc_t *p_hw_crc)
{
    return p_hw_crc->sum;
}

/*
 * \brief �����ṹ��εĽ���
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_CRC_H */

/* end of file */

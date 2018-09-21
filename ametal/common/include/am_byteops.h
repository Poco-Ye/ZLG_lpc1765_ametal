/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief �ֽڲ�����ض���ͷ�ļ�
 *
 * ���ļ��ṩ�˳��õ�λ�������ߺ꣬���磺AM_LSB(), AM_LONGSWAP()����������
 * ��ο� \ref am_if_byteops ��
 *
 * \internal
 * \par Modification history:
 * - 1.01 14-12-15  fft, comment formate and translate to english version
 * - 1.00 13-01-15  orz, move defines from am_common.h
 * \endinternal
 */

#ifndef __AM_BYTEOPS_H
#define __AM_BYTEOPS_H

/**
 * \addtogroup am_if_byteops
 * \copydoc am_byteops.h
 * @{
 */

/**
 * \brief ȡ2-byte�����ĸ�λbyte
 *
 * \par ʾ��
 * \code
 *  uint16_t a = 0x1234;
 *  uint16_t b;
 *
 *  b = AM_MSB(a);  //b=0x12
 * \endcode
 */
#define AM_MSB(x)       (((x) >> 8) & 0xff)

/**
 * \brief ȡ2-byte�����ĵ�λbyte
 *
 * \par ʾ��
 * \code
 *  uint16_t a = 0x1234;
 *  uint16_t b;
 *
 *  b = AM_LSB(a);  //b=0x34
 * \endcode
 */
#define AM_LSB(x)       ((x) & 0xff)

/**
 * \brief ȡ2-word�����ĸ�λword
 *
 * \par ʾ��
 * \code
 *  uint32_t a = 0x12345678;
 *  uint32_t b;
 *
 *  b = AM_MSW(a);  //b=0x1234
 * \endcode
 */
#define AM_MSW(x)       (((x) >> 16) & 0xffff)

/**
 * \brief ȡ2-word�����ĵ�λword
 *
 * \par ʾ��
 * \code
 *  uint32_t a = 0x12345678;
 *  uint32_t b;
 *
 *  b = AM_LSW(a);  //b=0x5678
 * \endcode
 */
#define AM_LSW(x)       ((x) & 0xffff)

/**
 * \brief ����32-bit�����ĸ�λword�͵�λword
 *
 * \par ʾ��
 * \code
 *  uint32_t a = 0x12345678;
 *  uint32_t b;
 *
 *  b = AM_WORDSWAP(a); //b=0x56781234
 * \endcode
 */
#define AM_WORDSWAP(x)  (AM_MSW(x) | (AM_LSW(x) << 16))

/**
 * \brief ����32-bit�������ֽ�˳��
 *
 * \par ʾ��
 * \code
 *  uint32_t a = 0x12345678;
 *  uint32_t b;
 *
 *  b = AM_LONGSWAP(a); //b=0x78563412
 * \endcode
 */
#define AM_LONGSWAP(x)  ((AM_LLSB(x) << 24) | \
                        (AM_LNLSB(x) << 16) | \
                        (AM_LNMSB(x) << 8)  | \
                        (AM_LMSB(x)))

#define AM_LLSB(x)      ((x) & 0xff)            /**< \brief ȡ32bit������1���ֽ� */
#define AM_LNLSB(x)     (((x) >> 8) & 0xff)     /**< \brief ȡ32bit������2���ֽ� */
#define AM_LNMSB(x)     (((x) >> 16) & 0xff)    /**< \brief ȡ32bit������3���ֽ� */
#define AM_LMSB(x)      (((x) >> 24) & 0xff)    /**< \brief ȡ32bit������4���ֽ� */

/** 
 * @}  
 */

#endif /* __AM_BYTEOPS_H */

/* end of file */

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
 * \brief ͨ�ù��ߺ궨��ͷ�ļ�
 *
 * ���ļ��ṩ���õĹ��ߺ꣬���磺 min(), max(), offsetof()����������
 * ��ο��� \ref am_if_common ��
 *
 * \internal
 * \par Modification history:
 * - 1.03 14-12-15  fft, comment format and translate to english version
 * - 1.02 13-01-15  orz, move some defines to separate files.
 * - 1.01 12-09-05  orz, fix some defines.
 * - 1.00 12-08-23  zen, first implementation.
 * \endinternal
 */

#ifndef __AM_COMMON_H
#define __AM_COMMON_H

/**
 * \addtogroup am_if_common
 * \copydoc am_common.h
 * @{
 */

#include "am_types.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus  */

/******************************************************************************/

/**
 * \name ͨ�ó�������
 * @{
 */

#define AM_OK               0         /**< \brief OK               */
#define AM_ERROR          (-1)        /**< \brief һ�����         */

#define AM_NO_WAIT          0         /**< \brief ��ʱ�����ȴ�     */
#define AM_WAIT_FOREVER   (-1)        /**< \brief ��ʱ����Զ�ȴ�   */

#ifndef EOF
#define EOF               (-1)        /**< \brief �ļ�����         */
#endif

#define NONE              (-1)        /**< \brief ÿ��Ϊ��ʱ��ִ�� */
#define EOS               '\0'        /**< \brief C�ַ�������      */

#ifndef NULL
#define NULL             ((void *)0)  /**< \brief ��ָ��           */
#endif

#define AM_LITTLE_ENDIAN  1234        /**< \brief С��ģʽ         */
#define AM_BIG_ENDIAN     3412        /**< \brief ���ģʽ         */

/** @} */

/******************************************************************************/

/**
 * \name ���ú궨��
 * @{
 */

/**
 * \brief ��ṹ���Ա��ƫ��
 * \attention ��ͬƽ̨�ϣ����ڳ�Ա��С���ڴ�����ԭ��
 *            ͬһ�ṹ���Ա��ƫ�ƿ����ǲ�һ����
 *
 * \par ʾ��
 * \code
 *  struct my_struct = {
 *      int  m1;
 *      char m2;
 *  };
 *  int offset_m2;
 *
 *  offset_m2 = AM_OFFSET(struct my_struct, m2);
 * \endcode
 */
#define AM_OFFSET(structure, member)    ((size_t)(&(((structure *)0)->member)))

/** \brief ��ṹ���Ա��ƫ�ƣ�ͬ \ref AM_OFFSET һ�� */
#ifndef offsetof
#define offsetof(type, member)           AM_OFFSET(type, member)
#endif

/**
 * \brief ͨ���ṹ���Աָ���ȡ�����ýṹ���Ա�Ľṹ��
 *
 * \param ptr    ָ��ṹ���Ա��ָ��
 * \param type   �ṹ������
 * \param member �ṹ���иó�Ա������
 *
 * \par ʾ��
 * \code
 *  struct my_struct = {
 *      int  m1;
 *      char m2;
 *  };
 *  struct my_struct  my_st;
 *  char             *p_m2 = &my_st.m2;
 *  struct my_struct *p_st = AM_CONTAINER_OF(p_m2, struct my_struct, m2);
 * \endcode
 */
#define AM_CONTAINER_OF(ptr, type, member) \
            ((type *)((char *)(ptr) - offsetof(type,member)))

/**
 * \brief ͨ���ṹ���Աָ���ȡ�����ýṹ���Ա�Ľṹ�壬
 *        ͬ \ref AM_CONTAINER_OF һ��
 */
#ifndef container_of
#define container_of(ptr, type, member)     AM_CONTAINER_OF(ptr, type, member)
#endif

/** \brief Ԥȡ */
#ifndef prefetch
#define prefetch(x) (void)0
#endif

/**
 * \brief ����ṹ���Ա�Ĵ�С
 *
 * \code
 *  struct a = {
 *      uint32_t m1;
 *      uint32_t m2;
 *  };
 *  int size_m2;
 *
 *  size_m2 = AM_MEMBER_SIZE(a, m2);   //size_m2 = 4
 * \endcode
 */
#define AM_MEMBER_SIZE(structure, member)  (sizeof(((structure *)0)->member))

/**
 * \brief ��������Ԫ�ظ���
 *
 * \code
 *  int a[] = {0, 1, 2, 3};
 *  int element_a = AM_NELEMENTS(a);    // element_a = 4
 * \endcode
 */
#define AM_NELEMENTS(array)               (sizeof (array) / sizeof ((array) [0]))

/**
 * \brief ����ѭ��
 *
 * д��Զѭ��������ʱ�󲿷ֳ���Աϲ����while(1)��������䣬
 * ����Щϲ����for(;;)��������䡣while(1)��ĳЩ�ϵĻ��ϸ�ı�������
 * ���ܻ���־��棬��Ϊ1�����ֶ������߼����ʽ
 *
 * \code
 * AM_FOREVER {
 *     ; // ѭ����һЩ���������ĳЩ����������
 * }
 * \endcode
 */
#define AM_FOREVER  for (;;)

/******************************************************************************/

/**
 * \brief min �� max �� C++ �ı�׼�������� C++ �Ŀ��ṩ��
 */
#ifndef __cplusplus

/**
 * \brief ��ȡ2�����еĽϴ����ֵ
 * \param x ����1
 * \param y ����2
 * \return 2�����еĽϴ����ֵ
 * \note ��������ʹ��++��--����
 */
#ifndef max
#define max(x, y)               (((x) < (y)) ? (y) : (x))
#endif

/**
 * \brief ��ȡ2�����еĽ�С����ֵ
 * \param x ����1
 * \param y ����2
 * \return 2�����еĽ�С��ֵ
 * \note ��������ʹ��++��--����
 */
#ifndef min
#define min(x, y)               (((x) < (y)) ? (x) : (y))
#endif

#endif /* __cplusplus */

/**
 * \brief ��������
 *
 * \param x     ���������
 * \param align �������أ�����Ϊ2�ĳ˷�
 *
 * \code
 * int size = AM_ROUND_UP(15, 4);   // size = 16
 * \endcode
 */
#define AM_ROUND_UP(x, align)   (((int) (x) + (align - 1)) & ~(align - 1))

/**
 * \brief ��������
 *
 * \param x     ���������
 * \param align �������أ�����Ϊ2�ĳ˷�
 *
 * \code
 * int size = AM_ROUND_DOWN(15, 4);   // size = 12
 * \endcode
 */
#define AM_ROUND_DOWN(x, align) ((int)(x) & ~(align - 1))

/** \brief ������������ */
#define AM_DIV_ROUND_UP(n, d)   (((n) + (d) - 1) / (d))

/**
 * \brief �����Ƿ����
 *
 * \param x     ���������
 * \param align �������أ�����Ϊ2�ĳ˷�
 *
 * \code
 * if (AW_ALIGNED(x, 4) {
 *     ; // x����
 * } else {
 *     ; // x������
 * }
 * \endcode
 */
#define AM_ALIGNED(x, align)    (((int)(x) & (align - 1)) == 0)

/******************************************************************************/

/** \brief �ѷ���ת��Ϊ�ַ��� */
#define AM_STR(s)               #s

/** \brief �Ѻ�չ����Ľ��ת��Ϊ�ַ��� */
#define AM_XSTR(s)              AM_STR(s)

/******************************************************************************/

/** \brief ��1�ֽ�BCD����ת��Ϊ16�������� */
#define AM_BCD_TO_HEX(val)     (((val) & 0x0f) + ((val) >> 4) * 10)

/** \brief ��1�ֽ�16��������ת��ΪBCD���� */
#define AM_HEX_TO_BCD(val)     ((((val) / 10) << 4) + (val) % 10)

/** @} */


/** 
 * @}  
 */

#include "am_bitops.h"
#include "am_byteops.h"
#include "am_errno.h"
#include "am_types.h"

#include "am_adc.h"
#include "am_dac.h"
#include "am_buzzer_pwm.h"
#include "am_cap.h"
#include "am_crc.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_gpio.h"
#include "am_gpio_util.h"
#include "am_i2c.h"
#include "am_int.h"
#include "am_led.h"
#include "am_pwm.h"
#include "am_ringbuf.h"
#include "am_rtc.h"
#include "am_spi.h"
#include "am_timer.h"
#include "am_uart.h"
#include "am_uart_int.h"
#include "am_uart_ringbuf.h"
#include "am_wdt.h"
#include "am_wait.h"

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#endif /* __AM_COMMON_H */

/* end of file */

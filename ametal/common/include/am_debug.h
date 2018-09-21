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
 * \brief ���ӻ����Ա�׼�ӿ�
 *
 * \par ��ʵ��
 * \code
 *  #include "ametal.h"
 *  #include "am_debug.h"
 *
 *  int age = 18;
 *  am_kprintf("I'm %d years old!\n", age);
 * \endcode
 *
 * \internal
 * \par modification history:
 * - 1.00 15-01-16  tee, first implementation
 * \endinternal
 */

#ifndef __AM_DEBUG_H
#define __AM_DEBUG_H

#include "am_types.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_debug
 * \copydoc am_debug.h
 * @{
 */

/**
 * \brief ���������AM_VDEBUG��,�� AM_DBG_INFO() �꽫��������Ϣ������
 *        AM_DBG_INFO()��ʵ��Ϊ��
 */
#ifdef AM_VDEBUG
#define AM_DBG_INFO(...)    (void)am_kprintf(__VA_ARGS__)
#else
#define AM_DBG_INFO(msg)
#endif

/**
 * \brief ���Գ�ʼ��
 * 
 * ��ʹ�õ��������Ϣǰ��ȷ�����Դ����ѵ��øú�����ʼ�� 
 *
 * \return ��
 */
void am_debug_init(void);

/**
 * \brief ���������Ϣ������printf()����ʹ��
 * \return �ɹ��������Ϣ�ַ�����
 */
int am_kprintf(const char *fmt, ...);

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DEBUG_H */

/* end of file */

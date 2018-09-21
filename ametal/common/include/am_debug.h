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
 * \brief 可视化调试标准接口
 *
 * \par 简单实例
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
 * \brief 如果定义了AM_VDEBUG宏,则 AM_DBG_INFO() 宏将输出相关信息，否则
 *        AM_DBG_INFO()宏实际为空
 */
#ifdef AM_VDEBUG
#define AM_DBG_INFO(...)    (void)am_kprintf(__VA_ARGS__)
#else
#define AM_DBG_INFO(msg)
#endif

/**
 * \brief 调试初始化
 * 
 * 在使用调试输出信息前，确保调试串口已调用该函数初始化 
 *
 * \return 无
 */
void am_debug_init(void);

/**
 * \brief 调试输出信息，类似printf()函数使用
 * \return 成功输出的信息字符个数
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

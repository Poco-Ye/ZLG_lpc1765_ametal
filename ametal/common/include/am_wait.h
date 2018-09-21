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
 * \brief 等待(wait)标准接口
 *
 * 该接口的使用方式是，首先定义一个等待信号：am_wait_t wait;
 * 在需要等待的地方调用:am_wait_on(&wait);
 * 在需要结束之前开启等待的地方调用：am_wait_off(&wait)
 *
 * 通常情况下,am_wait_on() 打开等待后，程序将直到等待到有其他程序调用 am_wait_off()
 * 后才会继续后面的程序段执行。
 *
 * \internal
 * \par Modification History
 * - 1.00 15-06-12  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_WAIT_H
#define __AM_WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_wait
 * \copydoc am_wait.h
 * @{
 */

 /**
  * \brief 定义等待信号类型
  */
typedef volatile bool_t am_wait_t;

/** 
 * \brief 等待信号初始化
 * \param[in] p_wait  : 指向等待信号的指针
 * \retval  AM_OK  初始化成功
 */
am_static_inline
int am_wait_init (am_wait_t *p_wait)
{
    *p_wait = FALSE;
    return AM_OK;
}

/** 
 * \brief 启动等待事件
 *
 * 程序会一直等待，直到调用 am_wait_done() 指明等待完成
 * 
 * \param[in] p_wait  : 指向等待信号的指针
 *
 * \retval  AM_OK  初始化成功
 */
am_static_inline 
int am_wait_on (am_wait_t *p_wait)
{
    *p_wait = FALSE;
    while(*p_wait == FALSE);
    return AM_OK;
}

/** 
 * \brief 指定的等待事件完成
 *
 * 调用该函数后，am_wait_on() 启动的等待序列将等待完成，结束等待
 * 
 * \param[in] p_wait  : 指向等待信号的指针
 *
 * \retval AM_OK  初始化成功
 */
am_static_inline 
int am_wait_done (am_wait_t *p_wait)
{
    *p_wait = TRUE;
    return AM_OK;
}

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_WAIT_H */

/* end of file */

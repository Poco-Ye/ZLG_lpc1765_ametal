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
 * \brief 错误号相关定义头文件
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  zen, first implementation.
 * \endinternal
 */

#ifndef __AM_ERRNO_H
#define __AM_ERRNO_H
 
#ifdef __cplusplus
extern "C" {
#endif


/**
 * \addtogroup am_if_errno
 * \copydoc am_errno.h
 * @{
 */

/**
 * \name 错误值定义
 * @{
 */

#define AM_OK               0    /**< \brief 操作成功         */
    
#define AM_EINVAL           1    /**< \brief 无效参数         */
#define AM_EPERM            2    /**< \brief 操作不允许       */
#define AM_ENXIO            3    /**< \brief 设备或地址不存在 */ 
#define AM_EFAULT           4    /**< \brief 地址错误         */
#define AM_EFULL            5    /**< \brief 满               */ 
#define AM_EEMPTY           6    /**< \brief 空               */
#define AM_ERXOV            7    /**< \brief 接收溢出         */
#define AM_ETXUR            8    /**< \brief 传输过低         */
#define AM_ESSA             9    /**< \brief 从机断言         */
#define AM_ESSD             10   /**< \brief 从机解除断言     */
#define AM_EAGAIN           11   /**< \brief 无效，需重新尝试 */
#define AM_ETIME            12   /**< \brief 连接超时         */
#define AM_EIO              13   /**< \brief SIO 错误         */
#define AM_ENOTSUP          14   /**< \brief 不支持该功能     */
#define AM_EINPROGRESS      15   /**< \brief 操作正在进行中   */
#define AM_EBUSY            16   /**< \brief 设备忙           */
#define AM_EHIGH            17   /**< \brief 值过高           */
#define AM_ELOW             18   /**< \brief 值过低           */

#define AM_ERRNO_USER_START 2000

/** \brief 用户自定义错误值 */
#define AM_ERRNO_USER(x)    (AM_ERRNO_USER_START + (x))

/** @} */

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ERRNO_H */

/* end of file */

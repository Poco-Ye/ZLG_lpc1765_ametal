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
 * \brief �������ض���ͷ�ļ�
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
 * \name ����ֵ����
 * @{
 */

#define AM_OK               0    /**< \brief �����ɹ�         */
    
#define AM_EINVAL           1    /**< \brief ��Ч����         */
#define AM_EPERM            2    /**< \brief ����������       */
#define AM_ENXIO            3    /**< \brief �豸���ַ������ */ 
#define AM_EFAULT           4    /**< \brief ��ַ����         */
#define AM_EFULL            5    /**< \brief ��               */ 
#define AM_EEMPTY           6    /**< \brief ��               */
#define AM_ERXOV            7    /**< \brief �������         */
#define AM_ETXUR            8    /**< \brief �������         */
#define AM_ESSA             9    /**< \brief �ӻ�����         */
#define AM_ESSD             10   /**< \brief �ӻ��������     */
#define AM_EAGAIN           11   /**< \brief ��Ч�������³��� */
#define AM_ETIME            12   /**< \brief ���ӳ�ʱ         */
#define AM_EIO              13   /**< \brief SIO ����         */
#define AM_ENOTSUP          14   /**< \brief ��֧�ָù���     */
#define AM_EINPROGRESS      15   /**< \brief �������ڽ�����   */
#define AM_EBUSY            16   /**< \brief �豸æ           */
#define AM_EHIGH            17   /**< \brief ֵ����           */
#define AM_ELOW             18   /**< \brief ֵ����           */

#define AM_ERRNO_USER_START 2000

/** \brief �û��Զ������ֵ */
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

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
 * \brief UART��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_UART_H
#define __AM_UART_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_uart
 * \copydoc am_uart.h
 * @{
 */

/**
 * \name UARTģʽ����
 * @{
 */

#define AM_UART_MODE_POLL         1    /**< \brief UART ��ѯģʽ */
#define AM_UART_MODE_INT          2    /**< \brief UART �ж�ģʽ */

/** @} */

/**
 * \name UARTͨ�ÿ���ָ��
 * @{
 */

#define AM_UART_BAUD_SET          1   /**< \brief ���ò�����         */
#define AM_UART_BAUD_GET          2   /**< \brief ��ȡ������         */

#define AM_UART_OPTS_SET          3   /**< \brief ����Ӳ����������   */
#define AM_UART_OPTS_GET          4   /**< \brief ��ȡӲ����������   */

#define AM_UART_MODE_SET          5   /**< \brief ����ģʽ           */
#define AM_UART_MODE_GET          6   /**< \brief ��ȡ��ǰģʽ       */
#define AM_UART_AVAIL_MODES_GET   7   /**< \brief ��ȡ֧�ֵ���Чģʽ */

/** @} */

/**
 * \name Ӳ����������ѡ�����Ӳ������ʱ�������Ƕ��ѡ��Ļ�ֵ
 * @{
 */

#define AM_UART_CSIZE    0xc   /**< \brief λ3 ~ λ4Ϊ���ݿ��                */
#define AM_UART_CS5      0x0   /**< \brief ���ݿ��Ϊ5λ                      */
#define AM_UART_CS6      0x4   /**< \brief ���ݿ��Ϊ6λ                      */
#define AM_UART_CS7      0x8   /**< \brief ���ݿ��Ϊ7λ                      */
#define AM_UART_CS8      0xc   /**< \brief ���ݿ��Ϊ8λ                      */

#define AM_UART_STOPB    0x20  /**< \brief ����ֹͣλΪ2λ��Ĭ��Ϊ1λ         */
#define AM_UART_PARENB   0x40  /**< \brief ʹ����żУ�飬Ĭ����żУ���ǹرյ� */
#define AM_UART_PARODD   0x80  /**< \brief ����У��Ϊ��У�飬Ĭ����żУ��     */

/** @} */

/**
 * \name �����豸�ص��������ͱ��룬����ָ��ע����ֻص�����
 * @{
 */

#define AM_UART_CALLBACK_GET_TX_CHAR   0 /**< \brief ��ȡһ�������ַ�      */
#define AM_UART_CALLBACK_PUT_RCV_CHAR  1 /**< \brief �ύһ�����յ����ַ�  */
#define AM_UART_CALLBACK_ERROR         2 /**< \brief ����ص�����          */

/** @} */

/**
 * \name �ص��������Ͷ���
 * @{
 */

/** \brief ��ȡһ�������ַ��ص��������� */
typedef int  (*pfn_uart_txchar_get_t)(void *p_arg, char *p_char);

/** \brief �ύһ�����յ����ַ�         */
typedef int  (*pfn_uart_rxchar_put_t)(void *p_arg, char  ch);

/** \brief ����ص�����                 */
typedef int  (*pfn_uart_err_t)(void *p_arg, int code, void *p_data, int size);

/** @} */


/**
 * \brief UART���������ṹ��
 */
struct am_uart_drv_funcs {

    /**\brief UART���ƺ���     */
    int (*pfn_uart_ioctl)(void *p_drv,int request, void *p_arg);

    /**\brief ����UART���ͺ��� */
    int (*pfn_uart_tx_startup)(void *p_drv);

    /**\brief ���ô��ڻص����� */
    int (*pfn_uart_callback_set)(void  *p_drv,
                                 int    callback_type,
                                 int  (*pfn_callback)(void *),
                                 void  *p_callback_arg);

    /**\brief �Ӵ��ڻ�ȡһ���ַ�����ѯģʽ�� */
    int (*pfn_uart_poll_getchar)(void *p_drv, char *p_inchar);

    /**\brief ���һ���ַ�����ѯģʽ��       */
    int (*pfn_uart_poll_putchar)(void *p_drv, char outchar);

    /**\brief �������ӣ������Ӵ����жϺ���   */
    int (*pfn_uart_connect)(void *p_drv);
};

/**
 * \brief UART����
 */
typedef struct am_uart_serv {

    /** \brief UART���������ṹ��ָ��    */
    struct am_uart_drv_funcs *p_funcs;

    /** \brief �������������ĵ�һ������  */
    void                     *p_drv;
} am_uart_serv_t;

/** \brief UART��׼�������������Ͷ���  */
typedef am_uart_serv_t *am_uart_handle_t;


/**
 * \brief ���ڿ��ƺ���
 *
 * \param[in] handle  : UART��׼����������
 * \param[in] request : ����ָ��
 *            - AM_UART_BAUD_SET : ���ò�����, p_argΪ uint32_t����,ֵΪ������
 *            - AM_UART_BAUD_GET : ��ȡ������, p_argΪ uint32_tָ������
 *            - AM_UART_OPTS_SET ������Ӳ��������p_arg Ϊ uint32_t���ͣ��磺#AM_UART_CS8��
 *            - AM_UART_OPTS_GET ����ȡ��ǰ��Ӳ���������ã�p_argΪ uint32_tָ������
 *            - AM_UART_MODE_SET : ����ģʽ, p_argֵΪ AM_UART_MODE_POLL ���� AM_UART_MODE_INT
 *            - AM_UART_MODE_GET : ��ȡ��ǰģʽ, p_argΪ uint32_tָ������
 *            - AM_UART_AVAIL_MODES_GET : ��ȡ��ǰ���õ�ģʽ, p_argΪ uint32_tָ������
 * \param[in,out] p_arg : ��ָ���Ӧ�Ĳ���
 *
 * \retval AM_OK       : ����ָ��ִ�гɹ�
 * \retval -AM_EIO     : ִ�д���
 * \retval -AM_ENOTSUP : ָ�֧��
 */
am_static_inline
int am_uart_ioctl (am_uart_handle_t handle,int request, void *p_arg)
{
    return handle->p_funcs->pfn_uart_ioctl(handle->p_drv,request,p_arg);
}

/**
 * \brief ����UART����
 * \param[in] handle : UART��׼����������
 * \retval AM_OK : �����ɹ�
 */
am_static_inline
int am_uart_tx_startup (am_uart_handle_t handle)
{
    return handle->p_funcs->pfn_uart_tx_startup(handle->p_drv);
}

/**
 * \brief ����UART�ص�����
 *
 * \param[in] handle         : UART��׼����������
 * \param[in] callback_type  : ָ�����õĺ��ֻص�����
 *            - AM_UART_CALLBACK_GET_TX_CHAR  : ��ȡһ�������ַ�����
 *            - AM_UART_CALLBACK_PUT_RCV_CHAR : �ύһ�����յ����ַ���Ӧ�ó���
 *            - AM_UART_CALLBACK_ERROR        : ����ص�����
 * \param[in] pfn_callback   : ָ��ص�������ָ��
 * \param[in] p_callback_arg : �ص��������û�����
 *
 * \retval  AM_OK      : �ص��������óɹ�
 * \retval -AM_EINVAL  : ����ʧ�ܣ���������
 */
am_static_inline
int am_uart_callback_set (am_uart_handle_t  handle,
                          int               callback_type,
                          int             (*pfn_callback)(void *),
                          void             *p_callback_arg)
{
    return handle->p_funcs->pfn_uart_callback_set(handle->p_drv,
                                                  callback_type,
                                                  pfn_callback,
                                                  p_callback_arg);
}

/**
 * \brief UART����һ������(��ѯģʽ)
 *
 * \param[in]  handle   : UART��׼����������
 * \param[out] p_inchar : ���ڻ�ȡ���ݵ�ָ��
 *
 * \retval  AM_OK       : �������ݳɹ�
 * \retval -AM_EAGAIN   : ��������δ׼��������������
 */
am_static_inline
int am_uart_poll_getchar (am_uart_handle_t handle, char *p_inchar)
{
    return handle->p_funcs->pfn_uart_poll_getchar(handle->p_drv, p_inchar);
}

/**
 * \brief UART����һ������(��ѯģʽ)
 *
 * \param[in] handle  : UART��׼����������
 * \param[in] outchar : �����͵�����
 *
 * \retval  AM_OK     : �������ݳɹ�
 * \retval -AM_EAGAIN : ����δ������������
 */
am_static_inline
int am_uart_poll_putchar (am_uart_handle_t handle, char outchar)
{
    return handle->p_funcs->pfn_uart_poll_putchar(handle->p_drv, outchar);
}

/**
 * \brief UART�жϺ������ӣ���ʹ���ж�ģʽʱ��Ҫ���ô˺���
 * \param[in] handle  : UART��׼����������
 * \retval  AM_OK     : ���ӳɹ�
 * \retval -AM_EINVAL : ʧ�ܣ���������
 */
am_static_inline
int am_uart_connect (am_uart_handle_t handle)
{
    return handle->p_funcs->pfn_uart_connect(handle->p_drv);
}

/**
 * \brief UART���ݷ��ͣ���ѯģʽ��
 *
 * \param[in] handle  : UART��׼����������
 * \param[in] p_txbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 *
 * \return �ɹ��������ݵĸ���
 */
int am_uart_poll_send(am_uart_handle_t  handle,
                      const uint8_t    *p_txbuf,
                      uint8_t           nbytes);


/**
 * \brief UART���ݽ��գ���ѯģʽ��
 *
 * \param[in] handle  : UART��׼����������
 * \param[in] p_rxbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 *
 * \return �ɹ��������ݵĸ���
 */
int am_uart_poll_receive(am_uart_handle_t  handle,
                         uint8_t          *p_rxbuf,
                         uint32_t          nbytes);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_UART_H */

/* end of file */

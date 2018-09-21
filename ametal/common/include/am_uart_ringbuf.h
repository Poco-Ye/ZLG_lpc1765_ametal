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
 * \brief UART(ʹ��ring buffer���ж�ģʽ)��׼�ӿ�
 *
 * ���ļ������ӿڵ�ʵ�ֻ���UART��׼�ӿڣ�Ϊ�����û�ʹ����ƣ�����ΪUART�ӿں���
 * ��ʹ�÷�����
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_UART_RINGBUF_H
#define __AM_UART_RINGBUF_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "am_ringbuf.h"

/**
 * \addtogroup am_if_uart_ringbuf
 * \copydoc am_uart_ringbuf.h
 * @{
 */

/**
 * \brief UART����ring buffer���ж�ģʽ���豸�ṹ��
 */
typedef struct am_uart_ringbuf_dev {

    /** \brief UART��׼���������� */
    am_uart_handle_t  handle;

    /** \brief �������ݻ��λ�����   */
    am_ringbuf_t      rx_ringbuf;

    /** \brief �������ݻ��λ�����   */
    am_ringbuf_t      tx_ringbuf;
} am_uart_ringbuf_dev_t;

/** \brief UART����ring buffer���ж�ģʽ����׼�������������Ͷ��� */
typedef struct am_uart_ringbuf_dev * am_uart_ringbuf_handle_t;


/**
 * \brief ��ʼ��UARTΪ��ring buffer���ж�ģʽ
 *
 * \param[in] p_dev      : UART����ring buffer���ж�ģʽ���豸�ṹ��ָ��
 * \param[in] handle     : UART��׼����������
 * \param[in] p_rxbuf    : ָ����ջ�������ָ�룬����ʵ�ֽ��ջ��λ�����
 * \param[in] rxbuf_size : ���ջ������Ĵ�С
 * \param[in] p_txbuf    : ָ���ͻ�������ָ�룬����ʵ�ַ��ͻ��λ�����
 * \param[in] txbuf_size : ���ͻ������Ĵ�С
 *
 * \return UART����ring buffer���ж�ģʽ����׼���������������ֵΪNULL��������
 *         ʼ��ʧ��
 */
am_uart_ringbuf_handle_t am_uart_ringbuf_init(am_uart_ringbuf_dev_t *p_dev,
                                              am_uart_handle_t       handle,
                                              char                  *p_rxbuf,
                                              uint32_t               rxbuf_size,
                                              char                  *p_txbuf,
                                              uint32_t               txbuf_size);

/**
 * \brief UART���ݷ��ͣ���ring buffer���ж�ģʽ��
 *
 * \param[in] handle  : UART����ring buffer���ж�ģʽ����׼����������
 * \param[in] p_txbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 * 
 * \return �ɹ��������ݵĸ���
 */
int am_uart_ringbuf_send(am_uart_ringbuf_handle_t  handle,
                         const uint8_t            *p_txbuf,
                         uint32_t                  nbytes);

/**
 * \brief UART���ݽ��գ���ring buffer���ж�ģʽ��
 *
 * \param[in] handle  : UART����ring buffer���ж�ģʽ����׼����������
 * \param[in] p_rxbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 *
 * \return �ɹ��������ݵĸ���
 */
int am_uart_ringbuf_receive(am_uart_ringbuf_handle_t  handle,
                            uint8_t                  *p_rxbuf,
                            uint32_t                  nbytes);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_UART_RINGBUF_H */

/* end of file */

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
 * \brief UART(�ж�ģʽ)��׼�ӿ�
 *
 * ���ļ������ӿڵ�ʵ�ֻ���UART��׼�ӿڣ�Ϊ�����û�ʹ����ƣ�����ΪUART�ӿں���
 * ��ʹ�÷�����
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_UART_INT_H
#define __AM_UART_INT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "am_wait.h"

/**
 * \addtogroup am_if_uart_int
 * \copydoc am_uart_int.h
 * @{
 */
    
/**
 * \brief UART���ж�ģʽ���豸�ṹ��
 */
typedef struct am_uart_int_dev {
    
    /** \brief UART��׼����������     */
    am_uart_handle_t   handle;

    /** \brief ָ��UART���ͻ�������ָ�� */
    uint8_t           *p_txbuf;
    
    /** \brief �������ݸ���             */
    volatile uint32_t  tx_nbytes;
    
    /** \brief ָ��UART���ջ�������ָ�� */
    volatile uint8_t  *p_rxbuf;
    
    /** \brief �������ݸ���             */
    volatile uint32_t  rx_nbytes;
    
    /** \brief ���ڹر����ڵȴ����ͻ������ɵĵȴ����� */
    am_wait_t         *p_wait;
} am_uart_int_dev_t;

/** \brief UART���ж�ģʽ����׼�������������Ͷ��� */
typedef struct am_uart_int_dev *am_uart_int_handle_t;


/**
 * \brief ��ʼ��UARTΪ�ж�ģʽ
 *
 * \param[in] p_dev   : UART���ж�ģʽ���豸�ṹ��ָ��
 * \param[in] handle  : UART��׼����������
 *
 * \return UART���ж�ģʽ����׼���������������ֵΪNULL��������ʼ��ʧ��
 */
am_uart_int_handle_t am_uart_int_init(am_uart_int_dev_t *p_dev,
                                      am_uart_handle_t   handle);

/**
 * \brief UART���ݷ��ͣ��ж�ģʽ��
 *
 * \param[in] handle  : UART���ж�ģʽ����׼����������
 * \param[in] p_txbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 * 
 * \return �ɹ��������ݵĸ���
 */
int am_uart_int_send(am_uart_int_handle_t  handle,
                     const uint8_t        *p_txbuf,
                     uint32_t              nbytes);
                            

/**
 * \brief UART���ݽ��գ��ж�ģʽ��
 *
 * \param[in] handle  : UART���ж�ģʽ����׼����������
 * \param[in] p_rxbuf : �������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 * 
 * \return �ɹ��������ݵĸ���
 */
int am_uart_int_receive(am_uart_int_handle_t  handle,
                        uint8_t              *p_rxbuf,
                        uint32_t              nbytes);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_UART_INT_H */

/* end of file */

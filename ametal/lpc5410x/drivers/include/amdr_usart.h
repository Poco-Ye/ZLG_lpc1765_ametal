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
 * \brief USART����������UART��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 14-12-03  jon, add USART interrupt mode.
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_USART_H
#define __AMDR_USART_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_uart.h"
#include "amhw_usart.h"
#include "amhw_fifo.h"

/**
 * \addtogroup amdr_if_usart
 * \copydoc amdr_usart.h
 * @{
 */

/**
 * \name �������ţ�����ص�������code���������������ݸ��û���ָ����ǰ�Ĵ�������
 *
 *  ����ص������Ĳ���ԭ�ͣ�\n
 *  int uart_err(void *p_arg, int code, void *p_data, int size);
 *  p_arg���û�ע����û�������p_data��size��ͬ�Ĵ������Ͱ�������Ϣ������ͬ��
 *  ����ʹ��am_uart_callback_set() �������ô��ڴ���ص�������
 * @{
 */

/** \brief ����FIFO���ߴ���p_data��������Ϣ��ΪNULL,size��ֵΪ0 */
#define AMDR_UART_ERRCODE_FIFO_BUSERR      1

/**
 * \brief �û�ָ���������жϷ���,p_data������Ϊuint32_t��ֵΪ���ڵ��ж�״̬����
 *        ���û��жϾ�����ж�Դ��sizeΪ1��
 */
#define AMDR_UART_ERRCODE_USART_OTHER_INT  2

/** @} */

/**
 * \brief ����FIFO��Ϣ�ṹ��
 */
typedef struct amdr_usart_fifo_info {

    amhw_fifo_t          *p_hw_fifo;   /**< \brief ָ��ϵͳFIFO�Ĵ������ָ�� */
    amhw_fifo_usart_ch_t  usart_ch;    /**< \brief FIFO�д��ڶ�Ӧʹ�õ�ͨ���� */

    /**
     * \brief ���ڴ��ڽ��յ�FIFO��С�����еĴ���ʹ�õ�FIFO���մ�С֮�Ͳ��ܳ���16��
     *        ��ֵΪ0������ʹ�ô��ڽ���FIFO��
     */
    uint8_t   rx_size;

    /**
     * \brief ���ڴ��ڷ��͵�FIFO��С�����еĴ���ʹ�õ�FIFO���ʹ�С֮�Ͳ��ܳ���16��
     *        ��ֵΪ0������ʹ�ô��ڷ���FIFO��
     */
    uint8_t   tx_size;

    /**
     * \brief FIFO���ճ�ʱ���ã���ʱʱ�Ӹ���Ϊ��2 ^ timeout_base * timeout_value
     *        ��ЧֵΪ 0 ~ 15
     */
    uint8_t   timeout_base;

    /**
     * \brief FIFO���ճ�ʱ���ã���ʱʱ�Ӹ���Ϊ��2 ^ timeout_base * timeout_value
     *        ��ЧֵΪ 2 ~ 15
     */
    uint8_t   timeout_value;

} amdr_usart_fifo_info_t;

/**
 * \brief �����豸��Ϣ�ṹ�壬���豸��Ϣ���ڴ��ڳ�ʼ��
 */
typedef struct amdr_usart_devinfo {

    amhw_usart_t *p_hw_usart;       /**< \brief ָ��USART�Ĵ������ָ��       */

    uint8_t      inum;              /**< \brief �����жϺ�                    */

    /**
     * \brief �������ñ�־��AMHW_USART_CFG_*�����AMHW_USART_CFG_*��Ļ�ֵ
     *        (�磺#AMHW_USART_CFG_8BIT)
     */
    uint32_t     cfg_flags;

    /**
     * \brief ���ڿ��Ʊ�־��AMHW_USART_CTL_*�����AMHW_USART_CTL_*��Ļ�ֵ
     *        (�磺#AMHW_USART_CTL_ADDRDET)
     */
    uint32_t     ctl_flags;
    uint32_t     baud_rate;           /**< \brief ��ʼ��������                */

    /**
     * \brief ָ��ʹ�ܵ������ж�,AMHW_USART_INT_*��ֵ����AMHW_USART_INT_*���
     *        ��ֵ������(#AMHW_USART_INT_RXRDY),(#AMHW_USART_INT_TXRDY) and
     *        (#AMHW_USART_INT_TXIDLE)�������жϡ�
     */
    uint32_t other_int_enable;

    amdr_usart_fifo_info_t fifo_info; /**< \brief ����ʹ�õ�FIFO��Ϣ          */

} amdr_usart_devinfo_t;

/**
 * \brief �����豸�ṹ�嶨��
 */
typedef struct amdr_usart_dev {

    am_uart_serv_t  uart_serv;                /**< \brief ��׼UART����        */

    int (*pfn_txchar_get)(void *, char *);    /**< \brief ָ���û�ע���txchar_get���� */
    int (*pfn_rxchar_put)(void *, char);      /**< \brief ָ���û�ע���rxchar_put���� */
    int (*pfn_err)(void *, int, void *, int); /**< \brief ָ���û�ע��Ĵ���ص�����   */

    void     *txget_arg;                      /**< \brief txchar_get��������     */
    void     *rxput_arg;                      /**< \brief rxchar_put��������     */
    void     *err_arg;                        /**< \brief ����ص������û�����   */

    uint8_t   channel_mode;                   /**< \brief ����ģʽ �ж�/��ѯ     */
    uint32_t  baud_rate;                      /**< \brief ���ڲ�����             */
    uint16_t  options;                        /**< \brief Ӳ������ѡ��           */

    uint32_t  other_int_enable;               /**< \brief ָ��ʹ�ܵ������ж�     */

    const amdr_usart_devinfo_t *p_devinfo;    /**< \brief ָ���豸��Ϣ������ָ�� */

} amdr_usart_dev_t;

/**
 * \brief ��ʼ��USART������UART��׼����������
 *
 * \param[in] p_dev     : ָ�򴮿��豸��ָ��
 * \param[in] p_devinfo : ָ�򴮿��豸��Ϣ������ָ��
 *
 * \return UART��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_uart_handle_t amdr_usart_init(amdr_usart_dev_t           *p_dev,
                                 const amdr_usart_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��USARTʱ�����ʼ��USART���ͷ������Դ
 * \param[in] p_dev : ָ�򴮿��豸��ָ��
 * \return ��
 */
void amdr_usart_deinit(amdr_usart_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_USART_H */

/* end of file */

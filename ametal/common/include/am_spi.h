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
 * \brief SPI��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AM_SPI_H
#define __AM_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    

#include "am_common.h"


/**
 * \addtogroup am_if_spi
 * \copydoc am_spi.h
 * @{
 */

/**
 * \name SPI���ñ�־������am_spi_config()��������Ϣ�е� cfg_flags����
 * @{
 */

#define AM_SPI_CFG_CPHA         0x01  /**< \brief ʱ����λ������            */
#define AM_SPI_CFG_CPOL         0x02  /**< \brief ʱ�Ӽ��Կ�����            */
#define AM_SPI_CFG_LSB_FIRST    0x08  /**< \brief ����λ�ȳ��ķ�ʽ��������֡ */
#define AM_SPI_CFG_3WIRE        0x10  /**< \brief 3��ģʽ��SI/SO �ź��߹��� */
#define AM_SPI_CFG_LOOP         0x20  /**< \brief �ػ�ģʽ                  */
#define AM_SPI_CFG_READY        0x80  /**< \brief READY�ź�,�ӻ����ʹ��ź���ͣ���� */

/** \brief SPIģʽ0    */
#define AM_SPI_CFG_MODE_0   (0 | 0)

/** \brief SPIģʽ1 */
#define AM_SPI_CFG_MODE_1   (0 | AM_SPI_CFG_CPHA)

/** \brief SPIģʽ2 */
#define AM_SPI_CFG_MODE_2   (AM_SPI_CFG_CPOL | 0)

/** \brief SPIģʽ3 */
#define AM_SPI_CFG_MODE_3   (AM_SPI_CFG_CPOL | AM_SPI_CFG_CPHA)

/** \brief SPI�ڶ�ȡ������MOSI��������ߵ�ƽ��Ĭ��Ϊ�͵�ƽ��*/
#define AM_SPI_CFG_READ_MOSI_HIGH    0x01

/** @} */
    
/**
 * \name ������Ʊ�ʶ,���� am_spi_mktrans() �� flags����
 * @{
 */
 
/**
 * \brief ���ô�����һϵ�д�������һ�����䣨��SSEL�ź�Ϊ��Ч״̬ǰ�Ĵ��䣩
 *        Ӧ�����øñ�־λ
 */
#define AM_SPI_TRANS_EOT       0x1000

/** @} */

/**
 * \brief SPI ����
 *
 * - SPI ����д�ĸ������ǵ��ڶ��ĸ�����Э������Ӧ�������ṩ \a rx_buf ��/��
 * \a tx_buf ����ĳЩ����£�����ͬ���������ṩ���ݴ����DMA��ַ�������Ļ�����
 * ����������ʹ��DMA���Խ������ݴ���Ĵ��ۡ�
 *
 * - ������仺����\a tx_buf ΪNULL���������\a rx_buf ʱ��0���ᱻ�Ƴ��������ϡ�
 * ������ջ����� \a rx_buf ΪNULL�������������������ݽ��ᱻ������ֻ�� \a len
 * ���ֽڻᱻ�Ƴ������롣�����Ƴ��������Ǵ���Ĳ��������磬�Ƴ�3���ֽڶ��ִ�С
 * �� 16 �� 20 bit��ǰ��ÿ����ʹ��2���ֽڣ�������ʹ��4���ֽڡ�
 *
 * - ���ڴ��У��������ǰ�CPU�ĵı����ֽ�˳���ţ������ֽ�˳���� (����ˣ�����
 * �豸ģʽ�����־�б������� AW_SPI_CFG_LSB_FIRST)�����磬��\a bits_per_word Ϊ
 * 16��������Ϊ 2N �ֽڳ� (\a len = 2N) ������CPU�ֽ�˳�㱣��N��16-bit�֡�
 *
 * - �� SPI ������ִ�С����2���ݴα�8-bitʱ����Щ�ڴ��е��ֽ����������bit����
 * ���У����������Ҷ���ģ���ˣ�δ���� (rx) ��δʹ�� (tx) ��λ���������Чλ��
 *
 * - ����SPI���俪ʼʱ��Ƭѡ�����Ч��ͨ����һֱ������Ч�������һϵ�д����е����һ��
 *   ���䣬���һ������Ӧ�����ô����־λ��#AM_SPI_TRANS_EOT
 *
 */
typedef struct am_spi_transfer {
    const void *p_txbuf;                   /**< \brief ָ�������ݻ����ָ�� */
    void       *p_rxbuf;                   /**< \brief ָ��������ݻ����ָ�� */
    uint32_t    nbytes;                    /**< \brief ���ݳ���(�ֽ���)      */
    uint32_t    flags;                     /**< \brief ������Ʊ�־          */
    void      (*pfn_callback)(void *,int); /**< \brief SPI������ɻص�����    */
    void       *p_arg;                     /**< \brief �ص���������ڲ���     */
} am_spi_transfer_t;


/**
 * \brief SPI�������ò�����Ϣ
 */
typedef struct am_spi_cfg_info {
    
    uint8_t     bpw;         /**< \brief bit_per_word,�ִ�С                       */
    uint32_t    speed;       /**< \brief SPI�ٶ�                                   */
    uint32_t    cfg_flags;   /**< \brief ģʽ��ʶ,������SPIģʽ��ʶ�ĺ������Ļ�ֵ */
   
} am_spi_cfg_info_t;

/**
 * \brief SPI���������ṹ��
 */
struct am_spi_drv_funcs {
    
    /** \brief ָ��SPI�������ú��� */
    int (*pfn_spi_config)(void              *p_drv,
                          am_spi_cfg_info_t *p_info);

    /** \brief ָ��SPI���亯�� */
    int (*pfn_spi_transfer)(void              *p_drv, 
                            am_spi_transfer_t *p_trans);
    
    /** \brief ָ��SPI�ж����Ӻ��� */
    int (*pfn_spi_connect)(void *p_drv);
    
};

/**
 * \brief SPI ��׼����ṹ��
 */
typedef struct am_spi_serv {
    struct am_spi_drv_funcs   *p_drv_funcs;    /**< \brief SPI  SPI��������     */
    void                      *p_drv;          /**< \brief SPI  SPI������������ */
} am_spi_serv_t;

/** \brief SPI ��׼�������������� */
typedef am_spi_serv_t *am_spi_handle_t;

/**
 * \brief SPI�ж����Ӻ���
 * \param[in] handle : SPI��׼����������
 * \retval  AM_OK    : ���ӳɹ�
 */
am_static_inline
int am_spi_connect (am_spi_handle_t handle)
{
    return handle->p_drv_funcs->pfn_spi_connect(handle->p_drv);
}

/**
 * \brief SPI�������ú������������ʡ�λ��ģʽ��
 *
 * \param[in] handle     : SPI��׼����������
 * \param[in] p_info     : ��Ҫ���õĲ�����Ϣ
 *
 * \retval   AM_OK           : ���óɹ�
 * \retval  -AM_EHIGH        : ����ʧ�ܣ�Ƶ��̫�ߣ�֧�ֵ����Ƶ�ʽ������ p_info->speed �С�
 * \retval  -AM_ELOW         : ����ʧ�ܣ�Ƶ��̫�ͣ�֧�ֵ���СƵ�ʽ������ p_info->speed �С�
 * \retval  -AM_ENOTSUP      : ����ʧ�ܣ���֧�ֵ�λ��ģʽ
 *
 * \note ������ɺ�p_info�д����ʵ�ʵ����ý�������ʿ��ܴ���һ��ƫ�  
 */
am_static_inline
int am_spi_config (am_spi_handle_t handle, am_spi_cfg_info_t *p_info)
{
    return handle->p_drv_funcs->pfn_spi_config(handle->p_drv, p_info);
}

/**
 * \brief SPI����ṹ���������
 *
 * \param[in] p_trans      : ָ��SPI����ṹ���ָ��
 * \param[in] p_txbuf      : ָ�������ݻ����ָ��,������ʱӦ����ΪNULL
 * \param[in] p_rxbuf      : ָ��������ݻ����ָ��,������ʱӦ����ΪNULL
 * \param[in] nbytes       : ��ǰ�������ݳ��ȣ��ֽ�����16λ����ʱ���ֽ���Ӧ����2 * N�����ݸ�������
 * \param[in] flags        : SPI������Ʊ�־λ��AM_SPI_TRANS_*�ĺ�ֵ���߶�AM_SPI_TRANS_*��� ��OR��ֵ
 * \param[in] pfn_callback : �ص�����
 * \param[in] p_arg        : �ص���������ڲ���
 *
 * \retval  AM_OK     : ����ṹ������������
 *
 * \note ������ͺͽ������ݻ���������Ч�����ȷ�����ǵ����ݳ�����һ�µġ�
 *       ���ڻ����������ͺ����ݴ����ֽ�����
 *        - 1  ~ 8 λ��ʱ��uint8_t ���ͣ�nbytes = ���ݴ���ĸ���
 *        - 9  ~ 16λ��ʱ��uint16_t���ͣ�nbytes = 2 * ���ݴ���ĸ���
 *        - 17 ~ 31λ��ʱ��uint32_t���ͣ�nbytes = 4 * ���ݴ���ĸ���
 */
am_static_inline
int am_spi_mktrans (am_spi_transfer_t *p_trans,
                    const void        *p_txbuf,
                    void              *p_rxbuf,
                    uint32_t           nbytes,
                    uint32_t           flags,
                    void             (*pfn_callback)(void *,int),
                    void              *p_arg)
{
    if(p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->p_txbuf      = p_txbuf;
    p_trans->p_rxbuf      = p_rxbuf;
    p_trans->nbytes       = nbytes;
    p_trans->flags        = flags;
    p_trans->pfn_callback = pfn_callback; 
    p_trans->p_arg        = p_arg;
    
    return AM_OK;
}

/**
 * \brief SPI���亯��
 *
 * \param[in] handle  : SPI��׼����������
 * \param[in] p_trans : ָ��SPI����ṹ���ָ��
 *
 * \retval   AM_OK     : �����������д���
 * \retval -AM_EINVAL : �����������
 *  ��������Լ����״̬��ͨ������ص�������ȡ״̬λ
 *    \li  AW_OK  : �������
 *    \li -AM_EIO : �������
 */
am_static_inline
int am_spi_transfer (am_spi_handle_t handle, am_spi_transfer_t *p_trans)
{
    return handle->p_drv_funcs->pfn_spi_transfer(handle->p_drv, p_trans);
}


/**
 * \brief ��д���
 *
 * �������Ƚ���SPIд�������ٽ��ж�������
 * ��ʵ��Ӧ���У�д����������Ϊ��ַ����������ΪҪ�Ӹõ�ַ��ȡ�����ݡ�
 *
 * \param[in]   handle  SPI��׼����������
 * \param[in]   p_txbuf ���ݷ��ͻ�����
 * \param[in]   n_tx    Ҫ���͵������ֽڸ���
 * \param[out]  p_rxbuf ���ݽ��ջ�����
 * \param[in]   n_rx    Ҫ���յ������ֽڸ���
 *
 * \retval AM_OK        ��Ϣ����ɹ�
 * \retval -AM_EINVAL   ��������
 * \retval -AM_EIO      �������
 */
int am_spi_write_then_read (am_spi_handle_t  handle,
                            const uint8_t   *p_txbuf,
                            size_t           n_tx,
                            uint8_t         *p_rxbuf,
                            size_t           n_rx);

/**
 * \brief ִ������д����
 *
 * ����������ִ������д���������η������ݻ�����0�ͻ�����1�е����ݡ�
 * ��ʵ��Ӧ���У�������0����Ϊ��ַ��������1ΪҪд��õ�ַ�����ݡ�
 *
 * \param[in]   handle  SPI��׼����������
 * \param[in]   p_txbuf0 ���ݷ��ͻ�����0
 * \param[in]   n_tx0    ������0���ݸ���
 * \param[in]   p_txbuf1 ���ݷ��ͻ�����1
 * \param[in]   n_tx1    ������1���ݸ���
 *
 * \retval AM_OK        ��Ϣ����ɹ�
 * \retval -AM_EINVAL   ��������
 * \retval -AM_EIO      �������
 */
int am_spi_write_then_write (am_spi_handle_t  handle,
                             const uint8_t   *p_txbuf0,
                             size_t           n_tx0,
                             const uint8_t   *p_txbuf1,
                             size_t           n_tx1);
/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_SPI_H */

/*end of file */

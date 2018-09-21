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
 * \brief SPI����������SPI��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-15  jon, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SPI_H
#define __AMDR_SPI_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"    
#include "am_spi.h"
#include "amhw_spi.h"
#include "am_int.h"

/**
 * \addtogroup amdr_if_spi
 * \copydoc amdr_spi.h
 * @{
 */
 
/**
 * \brief SPI �豸���������ṹ�� 
 */
typedef struct amdr_spi_mst_param {
    uint8_t      bits_per_word;                     /**< \brief ����֡��λ��            */
    uint16_t     scl_mode;                          /**< \brief SPI SCL��ģʽ           */
    uint16_t     lsb_first;                         /**< \brief SPI LSB���ȷ�������� */
    amhw_slave_t slave;                             /**< \brief SPI �ӻ�Ƭѡ����ѡ��    */
} amdr_spi_mst_param_t;


/**
 * \brief SPI �豸��Ϣ�ṹ��
 */
typedef struct amdr_spi_devinfo {
    
    uint8_t           bits_per_word;       /**< \brief ����֡��λ��          */
    uint32_t          flags;               /**< \brief SPI ���ñ�ʶ          */
    uint32_t          speed;               /**< \brief ��ʼ������            */
    struct amhw_spi  *p_hw_spi;            /**< \brief ָ��SPI�Ĵ������ָ��  */
    uint16_t          inum;                /**< \brief SPI �жϱ��          */

} amdr_spi_devinfo_t;

/** \brief SPI �豸��Ϣ�ض��� */
typedef amdr_spi_devinfo_t am_spi_devinfo_hw_t;


/**
 * \brief SPI �豸
 */
typedef struct amdr_spi_dev {
    
     /** \brief SPI��׼���������� */
    am_spi_serv_t             spi_serve;
    
    /** \brief ָ��SPI����ṹ���ָ�� */
    am_spi_transfer_t        *p_trans;
    
    /** \brief ָ��I2C�豸��Ϣ��ָ�� */
    const amdr_spi_devinfo_t *p_devinfo;
    
    /** \brief ������״̬��״̬  */
    int         state;  
    
    uint32_t    cur_speed;      /**< \brief ��������ǰ�ٶ�   */
    uint8_t     cur_bpw;        /**< \brief ��������ǰ֡��С */
    uint8_t     cur_flags;      /**< \brief ��������ǰģʽ   */
    uint16_t    cur_dly;        /**< \brief ��ǰ�������ʱ   */
    
    uint32_t    nbytes_to_recv; /**< \brief �����յ��ֽ���   */
    uint32_t    data_ptr;       /**< \brief ���ݴ������     */
    
} amdr_spi_dev_t;

/** \brief SPI �豸�ض��� */
typedef amdr_spi_dev_t am_spi_dev_hw_t;

/**
 * \brief SPI ��ʼ��
 *
 * \param[in] p_dev     : ָ��SPI�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��SPI�豸��Ϣ�ṹ���ָ��
 *
 * \return  SPI��׼���������� 
 */
am_spi_handle_t amdr_spi_init(amdr_spi_dev_t           *p_dev,
                              const amdr_spi_devinfo_t *p_devinfo);

/**
 * \brief ���SPI��ʼ��
 * \param[in] p_dev : ָ��SPI�豸�ṹ���ָ��
 * \return ��
 */
void amdr_spi_deinit(amdr_spi_dev_t *p_dev);

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SPI_H */

/*end of file */

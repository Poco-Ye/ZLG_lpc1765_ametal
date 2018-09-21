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
 * \brief CRC����������CRC��׼�ӿ�
 *
 * ��CRC����֧��3��CRCģ�ͣ�
 * 
 * 1. width     = 16; \n
 *    poly      = 0x1021; \n
 *    initvalue = ����������ֵ; \n
 *    refin     = TRUE ���� FALSE; \n
 *    refout    = TRUE ���� FALSE; \n
 *    xorout    = 0x0000 ���� 0xFFFF; \n
 * 2. width     = 16; \n
 *    poly      = 0x8005; \n
 *    initvalue = ����������ֵ; \n
 *    refin     = TRUE ���� FALSE; \n
 *    refout    = TRUE ���� FALSE; \n
 *    xorout    = 0x0000 ���� 0xFFFF; \n
 * 3. width     = 32; \n
 *    poly      = 0x04C11DB7; \n
 *    initvalue = ����������ֵ; \n
 *    refin     = TRUE ���� FALSE; \n
 *    refout    = TRUE ���� FALSE; \n
 *    xorout    = 0x00000000 ���� 0xFFFFFFFF; \n
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-19  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_CRC_H
#define __AMDR_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_crc.h"
#include "amhw_crc.h"

/**
 * \addtogroup amdr_if_crc
 * \copydoc amdr_crc.h
 * @{
 */

/**
 * \brief CRC�豸��Ϣ�ṹ��
 */
typedef struct amdr_crc_devinfo {
    amhw_crc_t   *p_hw_crc;               /**< \brief ָ��CRC�Ĵ������ָ��   */
} amdr_crc_devinfo_t;
    
/**
 * \brief CRC�豸�ṹ��
 */
typedef struct amdr_crc_dev {

    am_crc_serv_t              crc_serv;  /**< \brief ��׼CRC����               */
    am_crc_pattern_t          *p_patern;  /**< \brief ָ��CRCģ�͵�ָ��         */
    const amdr_crc_devinfo_t  *p_devinfo; /**< \brief ָ��CRC�豸��Ϣ������ָ�� */

} amdr_crc_dev_t;

/**
 * \brief ��ʼ��CRC
 *
 * \param[in] p_dev     : ָ��CRC�豸��ָ��
 * \param[in] p_devinfo : ָ��CRC�豸��Ϣ������ָ��
 *
 * \return CRC��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_crc_handle_t amdr_crc_init(amdr_crc_dev_t            *p_dev,
                              const amdr_crc_devinfo_t  *p_devinfo);

/**
 * \brief ��ʹ��CRCʱ�����ʼ��CRC���ͷ������Դ
 * \param[in] p_dev : ָ��CRC�豸��ָ��
 * \return ��
 */
void amdr_crc_deinit(amdr_crc_dev_t *p_dev);

/** 
 * @}  
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_CRC_H */

/* end of file */

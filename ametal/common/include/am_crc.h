/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief ѭ������У��(CRC)��׼�ӿ�
 *
 * \internal
 * \par modification history
 * - 1.00 15-01-19  tee, first implementation
 * \endinternal
 */

#ifndef __AM_CRC_H
#define __AM_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup am_if_crc
 * \copydoc am_crc.h
 * @{
 */
#include "am_common.h"

/**
 * \brief CRC ģ��
 */
typedef struct am_crc_pattern {
    uint8_t    width;     /**< \brief CRC���(�磺CRC5 �Ŀ��Ϊ 5)            */
    uint32_t   poly;      /**< \brief CRC���ɶ���ʽ                           */
    uint32_t   initvalue; /**< \brief CRC��ʼֵ                               */
    bool_t     refin;     /**< \brief �������������Ҫλ��ת�����ֵΪTRUE    */
    bool_t     refout;    /**< \brief ���������ֵ��Ҫλ��ת�����ֵΪTRUE  */
    uint32_t   xorout;    /**< \brief ������ֵ                              */
} am_crc_pattern_t;


/**
 * \brief CRC���������ṹ��
 */
struct am_crc_drv_funcs {

    /** \brief ����CRCģ�ͳ�ʼ��CRC��ΪCRC��������׼�� */
    int (*pfn_crc_init) (void *p_cookie, am_crc_pattern_t *p_pattern);

    /** \brief CRC����                                 */
    int (*pfn_crc_cal) (void *p_cookie,const uint8_t *p_data, uint32_t nbytes);

    /** \brief ��ȡCRC������                         */
    int (*pfn_crc_final) (void *p_cookie, uint32_t *p_value);
};

/** 
 * \brief CRC����
 */
typedef struct am_crc_serv {

    /** \brief CRC���������ṹ��ָ��    */
    struct am_crc_drv_funcs *p_funcs;
    
    /** \brief �������������ĵ�һ������ */
    void                    *p_drv;     
} am_crc_serv_t;

/** \brief CRC��׼�������������Ͷ���  */
typedef am_crc_serv_t *am_crc_handle_t;


/** 
 * \brief ����CRCģ�ͳ�ʼ��CRC��ΪCRC��������׼��
 * 
 * \param[in] handle    : CRC��׼����������
 * \param[in] p_pattern : ָ��CRCģ����Ϣ�ṹ��ָ��
 *
 * \retval  AM_OK       : ��ʼ���ɹ�
 * \retval -AM_EINVAL   : ��ʼ��ʧ��, ��������
 * \retval -AM_ENOTSUP  : ��ʼ��ʧ��, CRCģ�Ͳ�֧��
 */
am_static_inline
int am_crc_init (am_crc_handle_t handle, am_crc_pattern_t *p_pattern)
{
    return handle->p_funcs->pfn_crc_init(handle->p_drv, p_pattern);
}

/** 
 * \brief CRC����(���ݴ���)
 * 
 * \param[in] handle  : CRC��׼����������
 * \param[in] p_data  : ָ����������ݻ�����
 * \param[in] nbytes  : ���������ݵĸ���
 *
 * \retval  AM_OK     : CRC����ɹ�
 * \retval -AM_EINVAL : CRC����ʧ��, ��������
 */
am_static_inline
int am_crc_cal (am_crc_handle_t handle, const uint8_t *p_data, uint32_t nbytes)
{
    return handle->p_funcs->pfn_crc_cal(handle->p_drv, p_data, nbytes);
}

/** 
 * \brief ��ȡCRC������ֵ
 *
 * \param[in]  handle  : CRC��׼����������
 * \param[out] p_value : ���ڻ�ȡCRC������ֵ
 *
 * \retval  AM_OK      : ��ȡCRC������ֵ�ɹ�
 * \retval -AM_EINVAL  : ��ȡCRC������ֵʧ��, ��������
 */
am_static_inline
int am_crc_final (am_crc_handle_t handle, uint32_t *p_value) 
{
    return handle->p_funcs->pfn_crc_final(handle->p_drv, p_value);
}

/** 
 * @}  
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_CRC_H */

/* end of file */

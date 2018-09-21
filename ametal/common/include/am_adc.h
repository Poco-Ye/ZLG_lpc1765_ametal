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
 * \brief ADC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.10 15-01-15  hbt, add am_adc_global_read,
 *                       delete am_adc_connect.
 * - 1.00 14-01-10  asd, first implementation.
 * \endinternal
 */

#ifndef __AM_ADC_H
#define __AM_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_adc
 * \copydoc am_adc.h
 * \{
 */
 
/**
 * \brief ADC��������
 */
struct am_adc_drv_funcs {

    /**
     * \brief ����һ��ADת��
     *
     * \param[in] p_drv            ��Ϊ���������ĵ�һ������
     * \param[in] channel          ��ת����ͨ��
     * \param[in] p_val            ת�������ŵĻ�����
     * \param[in] desired_cnt      ������ת��������ʵ��ת������ͨ���ص���������
     * \param[in] pfn_convert_cb   һ��ת����ɵĻص�����
     * \param[in] p_arg            �ص������ĵ�һ���������û�����
     *
     * \retval   AM_OK     ����ת���ɹ�
     * \retval -AM_ENXIO   ͨ��������
     * \retval -AM_EINVAL  ��Ч����
     */
    int (*pfn_adc_start) (void               *p_drv,
                          int                 channel,
                          uint32_t           *p_val,
                          uint32_t            desired_cnt,
                          void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt),
                          void               *p_arg);
    
    /** \brief ��ȡADCת������ */
    uint32_t (*pfn_bits_get)(void *p_drv);

    /** \brief ��ȡADC�ο���ѹ */
    uint32_t (*pfn_vref_get)(void *p_drv);
};

/**
 * \brief ADC��׼����
 */
typedef struct am_adc_serv {

    /** \brief ָ��ADC����������ָ�� */
    const struct am_adc_drv_funcs *p_funcs;

    /** \brief ����������һ����ڲ��� */
    void                          *p_drv;
} am_adc_serv_t;

/** \brief ADC��׼�������������Ͷ��� */
typedef am_adc_serv_t *am_adc_handle_t;

/**
 * \brief ��ȡADCת������
 * \param[in] handle : ADC��׼����������
 * \return ADCת������
 */
am_static_inline
uint32_t am_adc_bits_get (am_adc_handle_t handle)
{
    return handle->p_funcs->pfn_bits_get(handle->p_drv);
}

/**
 * \brief ��ȡADC�ο���ѹ����λ��mV
 * \param[in] handle : ADC��׼����������
 * \return ADC�ο���ѹ
 */
am_static_inline
uint32_t am_adc_vref_get (am_adc_handle_t handle)
{
    return handle->p_funcs->pfn_vref_get(handle->p_drv);
}

/**
 * \brief ͬ����ȡָ��ͨ����ADCת��ֵ��ת�������󷵻أ�
 *
 * \param[in] handle : ADC��׼����������
 * \param[in] chan   : ADCͨ����
 * \param[in] p_val  : ת�������ŵĻ�����
 * \param[in] count  : ת������
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   ADCͨ���Ų�����
 * \retval  -AM_EINVAL  ��Ч����
 */
int am_adc_sync_read(am_adc_handle_t  handle,
                     int              chan,
                     uint32_t        *p_val,
                     uint32_t         count);

                     
/**
 * \brief �첽��ȡָ��ͨ����ADCת��ֵ�������������أ�ת�����������û�ָ���Ļص�������
 *
 * \param[in] handle       : ADC��׼����������
 * \param[in] chan         : ADCͨ����
 * \param[in] p_val        : ת�������ŵĻ�����
 * \param[in] count        : ת������
 * \param[in] pfn_complete : ת����ɻص�����
 * \param[in] p_arg        : �ص������û�����
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   ADCͨ���Ų�����
 * \retval  -AM_EINVAL  ��Ч����
 */
int am_adc_async_read(am_adc_handle_t  handle,
                      int              chan,
                      uint32_t        *p_val,
                      uint32_t         count,
                      am_pfnvoid_t     pfn_complete,
                      void            *p_arg); 

                      
/**
 * \brief ����һ��ADת��
 *
 * �û�������ô˺�����ֱ��ʹ��am_adc_sync_read() ��am_adc_async_read() �������ɡ�
 *
 * \param[in] handle         : ADC��׼����������
 * \param[in] chan           : ��ת����ͨ��
 * \param[in] p_val          : ת�������ŵĻ�����
 * \param[in] desired_cnt    : ������ת��������ʵ��ת������ͨ���ص���������
 * \param[in] pfn_convert_cb : һ��ת����ɵĻص�����
 * \param[in] p_arg          : �ص������ĵ�һ���������û�����
 *
 * \retval   AM_OK     ����ת���ɹ�
 * \retval -AM_ENXIO   ͨ��������
 * \retval -AM_EINVAL  ��Ч����
 */
am_static_inline
int am_adc_start (am_adc_handle_t     handle,
                  int                 chan,
                  uint32_t           *p_val,
                  uint32_t            desired_cnt,
                  void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt),
                  void               *p_arg) 
{
                        
     return handle->p_funcs->pfn_adc_start(handle->p_drv,
                                           chan,
                                           p_val,
                                           desired_cnt,
                                           pfn_convert_cb,
                                           p_arg);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_ADC_H */

/* end of file */

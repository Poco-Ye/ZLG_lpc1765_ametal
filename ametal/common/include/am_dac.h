/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief DAC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-04-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_DAC_H
#define __AM_DAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_dac
 * \copydoc am_dac.h
 * @{
 */

/**
 * \brief DAC��������
 */
struct am_dac_drv_funcs {

    /** \brief ��ȡDACת������           */
    uint32_t (*pfn_bits_get)(void *p_drv);

    /** \brief ��ȡDAC�ο���ѹ           */
    uint32_t (*pfn_vref_get)(void *p_drv);

    /** \brief ����ͨ����DACת��ֵ       */
    int (*pfn_dac_val_set)(void *p_drv, int chan, uint32_t value);

    /** \brief ʹ��DACת����������õ�ѹ  */
    int (*pfn_enable)(void *p_drv, int chan);

    /** \brief ����DACת��               */
    int (*pfn_disable)(void *p_drv, int chan);
    
};

/**
 * \brief DAC��׼����
 */
typedef struct am_dac_serv {

    /** \brief ָ��DAC����������ָ��     */
    const struct am_dac_drv_funcs *p_funcs;

    /** \brief DAC����������һ����ڲ��� */
    void                          *p_drv;
} am_dac_serv_t;

/** \brief DAC��׼�������������Ͷ��� */
typedef am_dac_serv_t *am_dac_handle_t;


/**
 * \brief ��ȡDACת��λ��
 * \param[in] handle : DAC��׼����������
 * \return DACת��λ��
 */
am_static_inline
uint32_t am_dac_bits_get (am_dac_handle_t handle)
{
    return handle->p_funcs->pfn_bits_get(handle->p_drv);
}

/**
 * \brief ��ȡDAC�ο���ѹ����λ��mV
 * \param[in] handle : DAC��׼����������
 * \return DAC�ο���ѹ(mV)
 */
am_static_inline
uint32_t am_dac_vref_get (am_dac_handle_t handle)
{
    return handle->p_funcs->pfn_vref_get(handle->p_drv);
}

/**
 * \brief ʹ��DACת����������õ�ѹ
 *
 * \param[in] handle : DAC��׼����������
 * \param[in] chan   : DACͨ����
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   DACͨ���Ų�����
 */
am_static_inline
uint32_t am_dac_enable (am_dac_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_enable(handle->p_drv, chan);
}


/**
 * \brief ����DACת��
 * \param[in] handle : DAC��׼����������
 * \param[in] chan   : DACͨ����
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   DACͨ���Ų�����
 */
am_static_inline
uint32_t am_dac_disable (am_dac_handle_t handle, int chan)
{
    return handle->p_funcs->pfn_disable(handle->p_drv, chan);
}

/**
 * \brief ����DACͨ����ת��ֵ
 *
 * \param[in] handle : DAC��׼����������
 * \param[in] chan   : DACͨ����
 * \param[in] val    : ���õ�DACת��ֵ
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   DACͨ���Ų�����
 */
am_static_inline
int am_dac_val_set (am_dac_handle_t handle, int chan, uint32_t val)
{
    return handle->p_funcs->pfn_dac_val_set(handle->p_drv, chan, val);
}

/**
 * \brief ����DACͨ���ĵ�ѹֵ����λ��mV��
 *
 * \param[in] handle : DAC��׼����������
 * \param[in] chan   : DACͨ����
 * \param[in] mv     : ���õĵ�ѹֵ
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   DACͨ���Ų�����
 */
int am_dac_mv_set(am_dac_handle_t handle, int chan, uint32_t mv);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_DAC_H */

/* end of file */

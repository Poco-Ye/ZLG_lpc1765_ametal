/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief UART implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-04-27  tee, first implementation.
 * \endinternal
 */
#include "am_adc.h"

struct adc_cb_arg {
    am_adc_handle_t    handle;
    int                channel;
    volatile uint32_t  count;
    uint32_t          *p_val;
    am_pfnvoid_t       pfn_complete;
    void              *p_arg;
};

/*******************************************************************************
  public functions
*******************************************************************************/

/* adcת���ص����� */
void adc_convert_cb (void *p_arg, uint32_t actual_cnt)
{
    struct adc_cb_arg *p_cb_arg = (struct adc_cb_arg *)p_arg;
    
    if (p_cb_arg->count <= actual_cnt) {
        p_cb_arg->count = 0;                      /* ת����� */
        if (p_cb_arg->pfn_complete != NULL) {
            p_cb_arg->pfn_complete(p_cb_arg->p_arg);
        }
        
    } else {
        p_cb_arg->count -= actual_cnt;
        p_cb_arg->p_val += actual_cnt;
        
        /* �ٴ����� */
        p_cb_arg->handle->p_funcs->pfn_adc_start(p_cb_arg->handle->p_drv,
                                                 p_cb_arg->channel,
                                                 p_cb_arg->p_val,
                                                 p_cb_arg->count,
                                                 adc_convert_cb,
                                                 p_cb_arg);
    }
    
    
    
}


/**
 * \brief ����DACͨ���ĵ�ѹֵ����λ��mV��
 *
 * \param[in] handle : DAC��׼����������
 * \param[in] chan   : DACͨ����
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   ADCͨ���Ų�����
 */
int am_adc_sync_read (am_adc_handle_t  handle, 
                      int              chan,
                      uint32_t        *p_val,
                      uint32_t         count)
{
    
    struct adc_cb_arg cb_arg;
    int               ret;
    
    cb_arg.handle  = handle;
    cb_arg.channel = chan;
    cb_arg.p_val   = p_val;
    cb_arg.count   = count;
    
    cb_arg.pfn_complete = NULL;
    cb_arg.p_arg        = NULL;
    
    ret = handle->p_funcs->pfn_adc_start(handle->p_drv,
                                         chan,
                                         p_val,
                                         count,
                                         adc_convert_cb,
                                         &cb_arg);
    if (ret != AM_OK) {
        return ret;
    }
    
    while(cb_arg.count != 0);      /* �ȴ�ָ��ת��������� */
    
    return  AM_OK;
}

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
int am_adc_async_read (am_adc_handle_t  handle,
                       int              chan,
                       uint32_t        *p_val,
                       uint32_t         count,
                       am_pfnvoid_t     pfn_complete,
                       void            *p_arg)
{
    
    struct adc_cb_arg cb_arg;
    int               ret;
    
    cb_arg.handle  = handle;
    cb_arg.channel = chan;
    cb_arg.p_val   = p_val;
    cb_arg.count   = count;
    
    cb_arg.pfn_complete = pfn_complete;
    cb_arg.p_arg        = p_arg;
    
    ret = handle->p_funcs->pfn_adc_start(handle->p_drv,
                                         chan,
                                         p_val,
                                         count,
                                         adc_convert_cb,
                                         &cb_arg);
    
    return  ret;
}

/* end of file */

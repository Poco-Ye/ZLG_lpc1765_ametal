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

/* adc转换回调函数 */
void adc_convert_cb (void *p_arg, uint32_t actual_cnt)
{
    struct adc_cb_arg *p_cb_arg = (struct adc_cb_arg *)p_arg;
    
    if (p_cb_arg->count <= actual_cnt) {
        p_cb_arg->count = 0;                      /* 转换完成 */
        if (p_cb_arg->pfn_complete != NULL) {
            p_cb_arg->pfn_complete(p_cb_arg->p_arg);
        }
        
    } else {
        p_cb_arg->count -= actual_cnt;
        p_cb_arg->p_val += actual_cnt;
        
        /* 再次启动 */
        p_cb_arg->handle->p_funcs->pfn_adc_start(p_cb_arg->handle->p_drv,
                                                 p_cb_arg->channel,
                                                 p_cb_arg->p_val,
                                                 p_cb_arg->count,
                                                 adc_convert_cb,
                                                 p_cb_arg);
    }
    
    
    
}


/**
 * \brief 设置DAC通道的电压值（单位：mV）
 *
 * \param[in] handle : DAC标准服务操作句柄
 * \param[in] chan   : DAC通道号
 *
 * \retval   AW_OK      操作成功
 * \retval  -AW_ENXIO   ADC通道号不存在
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
    
    while(cb_arg.count != 0);      /* 等待指定转换次数完成 */
    
    return  AM_OK;
}

/**
 * \brief 异步读取指定通道的ADC转换值（函数立即返回，转换结束调用用户指定的回调函数）
 *
 * \param[in] handle       : ADC标准服务操作句柄
 * \param[in] chan         : ADC通道号
 * \param[in] p_val        : 转换结果存放的缓冲区
 * \param[in] count        : 转换次数
 * \param[in] pfn_complete : 转换完成回调函数
 * \param[in] p_arg        : 回调函数用户参数
 *
 * \retval   AW_OK      操作成功
 * \retval  -AW_ENXIO   ADC通道号不存在
 * \retval  -AM_EINVAL  无效参数
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

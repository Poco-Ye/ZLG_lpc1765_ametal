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
 * \brief ADC标准接口
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
 * \brief ADC驱动函数
 */
struct am_adc_drv_funcs {

    /**
     * \brief 启动一次AD转换
     *
     * \param[in] p_drv            作为驱动函数的第一个参数
     * \param[in] channel          待转换的通道
     * \param[in] p_val            转换结果存放的缓冲区
     * \param[in] desired_cnt      期望的转换次数，实际转换次数通过回调函数返回
     * \param[in] pfn_convert_cb   一次转换完成的回调函数
     * \param[in] p_arg            回调函数的第一个参数，用户设置
     *
     * \retval   AM_OK     启动转换成功
     * \retval -AM_ENXIO   通道不存在
     * \retval -AM_EINVAL  无效参数
     */
    int (*pfn_adc_start) (void               *p_drv,
                          int                 channel,
                          uint32_t           *p_val,
                          uint32_t            desired_cnt,
                          void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt),
                          void               *p_arg);
    
    /** \brief 获取ADC转换精度 */
    uint32_t (*pfn_bits_get)(void *p_drv);

    /** \brief 获取ADC参考电压 */
    uint32_t (*pfn_vref_get)(void *p_drv);
};

/**
 * \brief ADC标准服务
 */
typedef struct am_adc_serv {

    /** \brief 指向ADC驱动函数的指针 */
    const struct am_adc_drv_funcs *p_funcs;

    /** \brief 驱动函数第一个入口参数 */
    void                          *p_drv;
} am_adc_serv_t;

/** \brief ADC标准服务操作句柄类型定义 */
typedef am_adc_serv_t *am_adc_handle_t;

/**
 * \brief 获取ADC转换精度
 * \param[in] handle : ADC标准服务操作句柄
 * \return ADC转换精度
 */
am_static_inline
uint32_t am_adc_bits_get (am_adc_handle_t handle)
{
    return handle->p_funcs->pfn_bits_get(handle->p_drv);
}

/**
 * \brief 获取ADC参考电压，单位：mV
 * \param[in] handle : ADC标准服务操作句柄
 * \return ADC参考电压
 */
am_static_inline
uint32_t am_adc_vref_get (am_adc_handle_t handle)
{
    return handle->p_funcs->pfn_vref_get(handle->p_drv);
}

/**
 * \brief 同步读取指定通道的ADC转换值（转换结束后返回）
 *
 * \param[in] handle : ADC标准服务操作句柄
 * \param[in] chan   : ADC通道号
 * \param[in] p_val  : 转换结果存放的缓冲区
 * \param[in] count  : 转换次数
 *
 * \retval   AW_OK      操作成功
 * \retval  -AW_ENXIO   ADC通道号不存在
 * \retval  -AM_EINVAL  无效参数
 */
int am_adc_sync_read(am_adc_handle_t  handle,
                     int              chan,
                     uint32_t        *p_val,
                     uint32_t         count);

                     
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
int am_adc_async_read(am_adc_handle_t  handle,
                      int              chan,
                      uint32_t        *p_val,
                      uint32_t         count,
                      am_pfnvoid_t     pfn_complete,
                      void            *p_arg); 

                      
/**
 * \brief 启动一次AD转换
 *
 * 用户无需调用此函数，直接使用am_adc_sync_read() 或　am_adc_async_read() 函数即可。
 *
 * \param[in] handle         : ADC标准服务操作句柄
 * \param[in] chan           : 待转换的通道
 * \param[in] p_val          : 转换结果存放的缓冲区
 * \param[in] desired_cnt    : 期望的转换次数，实际转换次数通过回调函数返回
 * \param[in] pfn_convert_cb : 一次转换完成的回调函数
 * \param[in] p_arg          : 回调函数的第一个参数，用户设置
 *
 * \retval   AM_OK     启动转换成功
 * \retval -AM_ENXIO   通道不存在
 * \retval -AM_EINVAL  无效参数
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

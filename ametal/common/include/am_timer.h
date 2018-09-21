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
 * \brief ��ʱ����׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_TIMER_H
#define __AM_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"

/**
 * \addtogroup am_if_timer
 * \copydoc am_timer.h
 * @{
 */

/**
 * \name ��ʱ������
 *  
 *  - ��8λ����ʱ��λ������32λ��ʱ�������8λֵΪ32
 *  - 8 ~ 15 λ��ʾ��ʱ��ͨ����
 *  - ������ʱ�����Խ�ռһλ���ӵ�16λ��ʼ��AM_TIMER_FEATURE(0) ~ AM_TIMER_FEATURE(15)
 * @{
 */

/** \brief ��ʱ��λ��                     */
#define AM_TIMER_SIZE(width)             ((uint32_t)(width & 0x00ffu))

/** \brief �������л�ȡ��ʱ��λ��         */
#define AM_TIMER_SIZE_GET(features)      (features & 0x00ffu)

/** \brief ��ʱ��ͨ����                   */
#define AM_TIMER_CHAN_NUM(num)           (((uint32_t)num << 8) & 0xff00u)

/** \brief �������л�ȡ��ʱ��ͨ����       */
#define AM_TIMER_CHAN_NUM_GET(features)  ((features & 0x00ff00u) >> 8)
 
/** \brief ����������ʱ�����Զ���         */
#define AM_TIMER_FEATURE(feature_id)     ((uint32_t)(1u << (feature_id + 16)))

/** \brief ��ʱ�����Բ����ж�             */
#define AM_TIMER_CAN_INTERRUPT             AM_TIMER_FEATURE(0)

/** \brief ��ʱ�����Զ�ȡ��ǰ��������ֵ   */
#define AM_TIMER_INTERMEDIATE_COUNT        AM_TIMER_FEATURE(1)

/** \brief ��ʱ�����ܱ�ֹͣ               */
#define AM_TIMER_CANNOT_DISABLE            AM_TIMER_FEATURE(2)

/** \brief ��ʱ���ڶ�ȡ����ֵʱ��ֹͣ     */
#define AM_TIMER_STOP_WHILE_READ           AM_TIMER_FEATURE(3)

/** \brief ��ʱ��֧���Զ���װ�ؼ���ֵ     */
#define AM_TIMER_AUTO_RELOAD               AM_TIMER_FEATURE(4)

/** \brief ��ʱ��ֻ�����У����ܸı䷭תֵ */
#define AM_TIMER_CANNOT_MODIFY_ROLLOVER    AM_TIMER_FEATURE(5)

/** \brief ��ʱ������֧����СƵ�ʺ����Ƶ��֮�������Ƶ��  */
#define AM_TIMER_CANNOT_SUPPORT_ALL_FREQS  AM_TIMER_FEATURE(6)

/** @} */


/** 
 * \brief ��ʱ����Ϣ�ṹ��
 */
typedef struct am_timer_info {
    uint32_t  clk_frequency;   /**< \brief ��ʱ��������Ƶ��       */
    uint32_t  min_frequency;   /**< \brief ��С����Ƶ��(�ж�Ƶ��) */
    uint32_t  max_frequency;   /**< \brief �����Ƶ��(�ж�Ƶ��) */
    uint32_t  features;        /**< \brief ��ʱ������             */
} am_timer_info_t;

/** 
 * \brief ��ʱ�����������ṹ��
 */
struct am_timer_drv_funcs {

    /** \brief ��ȡ��ʱ����Ϣ */
    int (*pfn_timer_info_get) (void *p_drv, am_timer_info_t *p_info);
    
    /** 
     * \brief ��ȡ��ǰ��ʱ������ֵ
     * ���صļ���ֵӦ���Ǽ��趨ʱ�����������ϼ���ģʽ�µĵ�ǰ����ֵ
     */
    int (*pfn_timer_count_get) (void     *p_drv,
                                uint8_t   chan,
                                uint32_t *p_count);
    
    /** \brief ��ȡ��ʱ����תֵ */
    int (*pfn_timer_rollover_get) (void     *p_drv,
                                   uint8_t   chan,
                                   uint32_t *p_rollover);
    
    /** \brief ���ܶ�ʱ��                         */
    int (*pfn_timer_disable) (void *p_drv, uint8_t chan);
    
    /** \brief ʹ�ܶ�ʱ����ͬʱ�趨��ʱcountֵ    */
    int (*pfn_timer_enable) (void     *p_drv, 
                             uint8_t   chan,
                             uint32_t  max_timer_count);
    
    /** \brief ���ûص�������ÿ��һ����ʱ�������ʱ���� */
    int (*pfn_timer_callback_set)(void  *p_drv,
                                  uint8_t chan,
                                  void (*pfn_callback)(void *),
                                  void  *p_arg);
                             
    /**
     * \brief ��ȡ64λ��ʱ����ǰ����ֵ
     * ���صļ���ֵӦ���Ǽ��趨ʱ�����������ϼ���ģʽ�µĵ�ǰ����ֵ
     */
    int (*pfn_timer_count_get64) (void      *p_drv,
                                  uint8_t    chan,
                                  uint64_t  *p_count);
                               
    /** \brief ��ȡ64λ��ʱ���ķ�תֵ */
    int (*pfn_timer_rollover_get64) (void     *p_drv,
                                     uint8_t   chan,
                                     uint64_t *p_rollover);
    
    /** \brief ʹ��64λ��ʱ����ͬʱ�趨64λ��ʱcountֵ */
    int (*pfn_timer_enable64) (void     *p_drv, 
                               uint8_t   chan,
                               uint64_t  max_timer_count);
    
    /** \brief �����жϻص�����       */
    int (*pfn_timer_connect) (void *p_drv);
};


/** 
 * \brief ��ʱ������
 */
typedef struct am_timer_serv {

    /** \brief ��ʱ�����������ṹ��ָ�� */
    struct am_timer_drv_funcs *p_funcs; 
    
    /** \brief �������������ĵ�һ������ */
    void                      *p_drv;   
} am_timer_serv_t;

/** \brief ��ʱ����׼�������������Ͷ��� */
typedef am_timer_serv_t *am_timer_handle_t;

/** 
 * \brief ��ȡ��ʱ����Ϣ
 * 
 * \param[in]  handle : ��ʱ����׼����������
 * \param[out] p_info : ���ڻ�ȡ��ʱ����Ϣ��ָ��
 *
 * \retval  AM_OK     : ��ȡ��Ϣ�ɹ�
 * \retval -AM_EINVAL : ��ȡ��Ϣʧ��, ��������
 */
am_static_inline
int am_timer_info_get (am_timer_handle_t handle, am_timer_info_t *p_info)
{
    return handle->p_funcs->pfn_timer_info_get(handle->p_drv,p_info);
}

/** 
 * \brief ��ȡ��ʱ����ǰ�ļ���ֵ
 * 
 * ���صļ���ֵӦ���Ǽ��趨ʱ�����������ϼ���ģʽ�µĵ�ǰ����ֵ
 *
 * \param[in]  handle  : ��ʱ����׼����������
 * \param[in]  chan    : ��ʱ��ͨ��
 * \param[out] p_count : ���ڻ�ȡ��ʱ����ǰ����ֵ��ָ��
 *
 * \retval  AM_OK      : ��ȡ��ʱ����ǰ����ֵ�ɹ�
 * \retval -AM_EINVAL  : ��ȡʧ��, ��������
 */
am_static_inline
int am_timer_count_get (am_timer_handle_t handle, 
                        uint8_t           chan, 
                        uint32_t         *p_count)
{
    return handle->p_funcs->pfn_timer_count_get(handle->p_drv,
                                                chan,
                                                p_count);
}

/** 
 * \brief ��ȡ��ʱ����תֵ
 *
 * \param[in]  handle     : ��ʱ����׼����������
 * \param[in]  chan       : ��ʱ��ͨ��
 * \param[out] p_rollover : ���ڻ�ȡ��ʱ����תֵ��ָ��
 *
 * \retval  AM_OK         : ��ȡ��ʱ����תֵ�ɹ�
 * \retval -AM_EINVAL     : ��ȡʧ��, ��������
 */
am_static_inline
int am_timer_rollover_get (am_timer_handle_t  handle, 
                           uint8_t            chan, 
                           uint32_t          *p_rollover)
{
    return handle->p_funcs->pfn_timer_rollover_get(handle->p_drv,
                                                   chan,
                                                   p_rollover);
}

/** 
 * \brief ���ܶ�ʱ����ֹͣ��ʱ��
 *
 * \param[in] handle  : ��ʱ����׼����������
 * \param[in] chan    : ��ʱ��ͨ��
 *
 * \retval  AM_OK     : ���ܶ�ʱ���ɹ�
 * \retval -AM_EINVAL : ����ʧ��, ��������
 */
am_static_inline
int am_timer_disable (am_timer_handle_t handle, uint8_t chan)
{
    return handle->p_funcs->pfn_timer_disable(handle->p_drv, chan);
}

/** 
 * \brief ʹ�ܶ�ʱ����ͬʱ�趨��ʱcountֵ 
 *
 * \param[in] handle          : ��ʱ����׼����������
 * \param[in] chan            : ��ʱ��ͨ��
 * \param[in] max_timer_count : ��ʱcountֵ 
 *
 * \retval  AM_OK             : ʹ�ܳɹ�
 * \retval -AM_EINVAL         : ʧ��, ��������
 *
 * \note ͨ������ʱ������ֵ�ﵽ�趨�Ķ�ʱcountֵʱ��������жϡ�ͬʱ����λ����ֵ
 *       Ϊ0�������ż�����ʱ��
 */
am_static_inline
int am_timer_enable (am_timer_handle_t  handle, 
                     uint8_t            chan,
                     uint32_t           max_timer_count)
{
     return handle->p_funcs->pfn_timer_enable(handle->p_drv,
                                              chan,
                                              max_timer_count);
}

/** 
 * \brief ���ûص�������ÿ��һ����ʱ�������ʱ����
 *
 * \param[in] handle       : ��ʱ����׼����������
 * \param[in] chan         : ��ʱ��ͨ��
 * \param[in] pfn_callback : �ص�����
 * \param[in] p_arg        : �ص��������û�����
 *
 * \retval  AM_OK     : ���óɹ�
 * \retval -AM_EINVAL : ����ʧ��, ��������
 *
 */
am_static_inline
int am_timer_callback_set (am_timer_handle_t  handle, 
                           uint8_t            chan,
                           void             (*pfn_callback)(void *),
                           void              *p_arg)
{
    return handle->p_funcs->pfn_timer_callback_set(handle->p_drv,
                                                   chan,
                                                   pfn_callback,
                                                   p_arg);
}

/** 
 * \brief ��ȡ33 ~ 64λ��ʱ���ĵ�ǰ����ֵ
 *
 * ���صļ���ֵӦ���Ǽ��趨ʱ�����������ϼ���ģʽ�µĵ�ǰ����ֵ
 *
 * \param[in]  handle  : ��ʱ����׼����������
 * \param[in]  chan    : ��ʱ��ͨ��
 * \param[out] p_count : ���ڻ�ȡ��ʱ����ǰ����ֵ��ָ��
 *
 * \retval  AM_OK      : ��ȡ���ĵ�ǰ��ʱ������ֵ
 * \retval -AM_EINVAL  : ��ȡʧ��, ��������
 *
 * \note �����ʱ��λ����33��64֮�䣬������øú�����ȡ��ʱ���ĵ�ǰ����ֵ
 */
am_static_inline
int am_timer_count_get64 (am_timer_handle_t  handle, 
                          uint8_t            chan,
                          uint64_t          *p_count)
{
    return handle->p_funcs->pfn_timer_count_get64(handle->p_drv,
                                                  chan,
                                                  p_count);
}
                           
/** 
 * \brief ��ȡ33 ~ 64λ��ʱ���ķ�תֵ
 *
 * \param[in]  handle     : ��ʱ����׼����������
 * \param[in]  chan       : ��ʱ��ͨ��
 * \param[out] p_rollover : ���ڻ�ȡ��ʱ����תֵ��ָ��
 *
 * \retval  AM_OK         : ��ȡ��תֵ�ɹ�
 * \retval -AM_EINVAL     : ��ȡ��תֵʧ��, ��������
 *
 * \note �����ʱ��λ����33��64֮�䣬������øú�����ȡ��תֵ
 */
am_static_inline
int am_timer_rollover_get64 (am_timer_handle_t  handle, 
                             uint8_t            chan,
                             uint64_t          *p_rollover)
{
    return handle->p_funcs->pfn_timer_rollover_get64(handle->p_drv,
                                                     chan,
                                                     p_rollover);
}

/** 
 * \brief ʹ��33��64λ��ʱ���������ö�ʱcountֵ
 *
 * \param[in] handle          : ��ʱ����׼����������
 * \param[in] chan            : ��ʱ��ͨ��
 * \param[in] max_timer_count : ��ʱ��countֵ
 *
 * \retval  AM_OK             : ʹ�ܳɹ�
 * \retval -AM_EINVAL         : ʹ��ʧ��, ��������
 *
 * \note �����ʱ��λ����33��64֮�䣬������øú���ʹ�ܶ�ʱ��
 */
am_static_inline
int am_timer_enable64 (am_timer_handle_t  handle, 
                       uint8_t            chan,
                       uint64_t           max_timer_count)
{
    return handle->p_funcs->pfn_timer_enable64(handle->p_drv,
                                               chan,
                                               max_timer_count);
}

/**
 * \brief ���Ӷ�ʱ�����жϺ���
 * \param[in] handle : ��ʱ����׼����������
 * \return None
 * \note �����Ҫʹ�õ�ע��Ļص�������������øú���
 */
am_static_inline
int am_timer_connect(am_timer_handle_t  handle)
{
    return handle->p_funcs->pfn_timer_connect(handle->p_drv);
}

/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_TIMER_H */

/* end of file */

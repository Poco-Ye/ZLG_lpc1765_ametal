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
 * \brief RTCӲ�������ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-27  fft, first implementation.
 * \endinternal
 */

#ifndef __AMHW_RTC_H
#define __AMHW_RTC_H


#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_common.h"

/** 
 * \addtogroup amhw_if_rtc
 * \copydoc amhw_rtc.h
 * @{
 */

/**
 * \brief ʵʱʱ�ӼĴ�����Ľṹ��
 */
typedef struct amhw_rtc {                                                                 
    __IO uint32_t ctrl;   /**< \brief RTC ���ƼĴ��� */
    __IO uint32_t match;  /**< \brief RTC ƥ��Ĵ��� */
    __IO uint32_t count;  /**< \brief RTC �����Ĵ��� */
    __IO uint32_t wake;   /**< \brief RTC ���ѼĴ��� */
} amhw_rtc_t;

/** 
 * \brief RTC ����λ����
 * @{
 */

/** \brief �����λ����λ */
#define AMHW_RTC_CTRL_SWRESET      AM_BIT(0)

/** \brief �������ʧ��״̬  */
#define AMHW_RTC_CTRL_OFD          AM_BIT(1)    

/** \brief RTC 1Hz��ʱƥ�� */
#define AMHW_RTC_CTRL_ALARM1HZ     AM_BIT(2)  

/** \brief RTC 1 kHz ��ʱ���� */
#define AMHW_RTC_CTRL_WAKE1KHZ     AM_BIT(3)   

/** \brief RTC 1 Hz ��ʱƥ�䣬���Ѵ���ȵ���ģʽ */
#define AMHW_RTC_CTRL_ALARMDPD_EN  AM_BIT(4)   

/** \brief RTC 1 kHz ��ʱ���ѣ����Ѵ���ȵ���ģʽ */
#define AMHW_RTC_CTRL_WAKEDPD_EN   AM_BIT(5) 

/** \brief ʹ��RTC 1KHz ��ʱ�� */
#define AMHW_RTC_CTRL_RTC1KHZ_EN   AM_BIT(6)    

/** \brief ʹ��RTC */
#define AMHW_RTC_CTRL_RTC_EN       AM_BIT(7)

/** \brief RTC ����λ���� */
#define AMHW_RTC_CTRL_MASK         ((uint32_t) 0xF1)  

/** @} */


/**
 * \brief RTC ����λ���ú���
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] flags    : AMHW_RTC_CTRL_*�ĺ�ֵ����
 *                       AMHW_RTC_CTRL_*��Ļ�(OR)ֵ(#AMHW_RTC_CTRL_OFD)
 *
 * \return    None
 */
am_static_inline 
void amhw_rtc_control (amhw_rtc_t *p_hw_rtc, uint32_t flags)
{
    p_hw_rtc->ctrl = flags;
}

/**
 * \brief ѡ����ʹ��RTC
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] flags    : AMHW_RTC_CTRL_*�ĺ�ֵ����
 *                       AMHW_RTC_CTRL_*��Ļ�(OR)ֵ(#AMHW_RTC_CTRL_ALARMDPD_EN) 
 *
 * \return    ��
 * \note ͨ������־λ���л����������ͬʱʹ�ܶ��RTCѡ�� ���磺
 *       AMHW_RTC_CTRL_ALARMDPD_EN, AMHW_RTC_CTRL_WAKEDPD_EN, AMHW_RTC_CTRL_RTC1KHZ_EN, and
 *       AMHW_RTC_CTRL_RTC_EN 
 */
am_static_inline 
void amhw_rtc_ctl_set (amhw_rtc_t *p_hw_rtc, uint32_t flags)
{
    p_hw_rtc->ctrl = (p_hw_rtc->ctrl & AMHW_RTC_CTRL_MASK) | flags;
}

/**
 * \brief ѡ���Խ���RTC
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] flags    : AMHW_RTC_CTRL_*�ĺ�ֵ����
 *                       AMHW_RTC_CTRL_*��Ļ�(OR)ֵ(#AMHW_RTC_CTRL_ALARMDPD_EN) 
 *
 * \return    ��
 * \note ͨ������־λ���л����������ͬʱ���ܶ��RTCѡ�� ���磺
 *       AMHW_RTC_CTRL_ALARMDPD_EN, AMHW_RTC_CTRL_WAKEDPD_EN, AMHW_RTC_CTRL_RTC1KHZ_EN, and
 *       AMHW_RTC_CTRL_RTC_EN flags with this function.
 */
am_static_inline 
void amhw_rtc_ctl_clr (amhw_rtc_t *p_hw_rtc, uint32_t flags)
{
    p_hw_rtc->ctrl = (p_hw_rtc->ctrl & AMHW_RTC_CTRL_MASK) & ~flags;
}

/**
 * \brief ʹ��RTC������
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    ��
 *
 * \note ����ͨ��amhw_rtc_ctl_set()����д��AMHW_RTC_CTRL_RTC_EN��־λʹ��
 */
am_static_inline 
void amhw_rtc_enable (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_RTC_EN);
}

/**
 * \brief ����RTC������
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    ��
 *
 * \note ����ͨ��amhw_rtc_ctl_clr()����д��AMHW_RTC_CTRL_RTC_EN��־λ����
 */
am_static_inline 
void amhw_rtc_disable (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_clr(p_hw_rtc, AMHW_RTC_CTRL_RTC_EN);
}

/**
 * \brief ��λRTC������
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    ��
 *
 * \note RTC��״̬�Ĵ���������Ĭ��ֵ
 */
am_static_inline 
void amhw_rtc_reset (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_SWRESET);
    amhw_rtc_ctl_clr(p_hw_rtc, AMHW_RTC_CTRL_SWRESET);
}

/**
 * \brief ��������Ƿ���������
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 *
 * \retval TRUE  : �������ʧ��״̬
 * \retval FALSE : ������������
 */
am_static_inline 
bool_t amhw_rtc_ofd_check (amhw_rtc_t *p_hw_rtc) 
{
    return (bool_t)((p_hw_rtc->ctrl & AMHW_RTC_CTRL_OFD) != 0);
}

/**
 * \brief ����������ʧ��״̬
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return ��
 */
am_static_inline 
void amhw_rtc_ofd_clr (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_OFD);
}

/**
 * \brief ʹ��RTC 1KHz��ʱ
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    None
 * \note ����ͨ��amhw_rtc_ctl_set()����д��AMHW_RTC_CTRL_RTC1KHZ_EN��־λʹ��        
 */
am_static_inline 
void amhw_rtc_enable_1kHz (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_set(p_hw_rtc, AMHW_RTC_CTRL_RTC1KHZ_EN);
}

/**
 * \brief ����RTC 1KHz��ʱ
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    None
 * \note ����ͨ��amhw_rtc_ctl_clr()����д��AMHW_RTC_CTRL_RTC1KHZ_EN��־λ����     
 */
am_static_inline
void amhw_rtc_disable_1kHz (amhw_rtc_t *p_hw_rtc)
{
    amhw_rtc_ctl_clr(p_hw_rtc, AMHW_RTC_CTRL_RTC1KHZ_EN);
}

/**
 * \brief ѡ����ʹ��RTC�жϻ���
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] ints     : �ɻ���RTC���жϱ�־λ
 *
 * \return    None
 * \note ѡ��һ�����߶���ɻ���RTC�жϵı�־λ������AMHW_RTC_CTRL_ALARMDPD_EN
 *       AMHW_RTC_CTRL_WAKEDPD_EN 
 *       ����ͨ��amhw_rtc_ctl_set()����д��AMHW_RTC_CTRL_ALARMDPD_EN��־λʹ��   
 */
am_static_inline 
void amhw_rtc_enable_wakeup (amhw_rtc_t *p_hw_rtc, uint32_t ints)
{
    amhw_rtc_ctl_set(p_hw_rtc, ints);
}

/**
 * \brief ѡ���Խ���RTC�жϻ���
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] ints     : �жϱ�־λ
 *
 * \return    None
 * \note ѡ��һ�����߶���жϵı�־λ������AMHW_RTC_CTRL_ALARMDPD_EN
 *       AMHW_RTC_CTRL_WAKEDPD_EN 
 *       ����ͨ��amhw_rtc_ctl_clr()����д��AMHW_RTC_CTRL_ALARMDPD_EN��־λ����   
 */
am_static_inline 
void amhw_rtc_disable_wakeup (amhw_rtc_t *p_hw_rtc, uint32_t ints)
{
    amhw_rtc_ctl_clr(p_hw_rtc, ints);
}

/**
 * \brief ���RTC״̬λ
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] sts_mask : ��Ҫ�����״̬λ
 *
 * \return    ��
 * \note �����������״̬λд1������ı�־�����磺AMHW_RTC_CTRL_OFD, 
 *        AMHW_RTC_CTRL_ALARM1HZ, ��AMHW_RTC_CTRL_WAKE1KHZ��
 */
am_static_inline 
void amhw_rtc_stat_clr (amhw_rtc_t *p_hw_rtc, uint32_t sts_mask)
{
    p_hw_rtc->ctrl = (p_hw_rtc->ctrl & AMHW_RTC_CTRL_MASK) | sts_mask;
}

/**
 * \brief ��ȡRTC״̬�Ĵ�����ֵ 
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return   RTC CTRL�Ĵ�����ֵ 
 */
am_static_inline
uint32_t amhw_rtc_stat_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->ctrl;
}

/**
 * \brief �趨RTCƥ��ֵ
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] count    : �趨��ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_rtc_alarm_set (amhw_rtc_t *p_hw_rtc, uint32_t count)
{
    p_hw_rtc->match = count;
}

/**
 * \brief ��ȡRTCƥ��Ĵ�����ֵ
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    MATCH�Ĵ�����ֵ
 */
am_static_inline 
uint32_t amhw_rtc_alarm_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->match;
}

/**
 * \brief �趨RTCƥ�����ֵ
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] count    : ��ʼ����ֵ�趨
 *
 * \return    ��
 */
am_static_inline 
void amhw_rtc_count_set (amhw_rtc_t *p_hw_rtc, uint32_t count)
{
    p_hw_rtc->count = count;
}

/**
 * \brief ��ȡRTC�����Ĵ���ֵ
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    �����Ĵ�����ֵ
 */
am_static_inline 
uint32_t amhw_rtc_count_get (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->count;
}

/**
 * \brief ����RTC���ѵ���ʱ��ֵ (��λ��ms)
 *
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \param[in] count    : ����ʱ��ֵ
 *
 * \return    ��
 * \note д����ֵ�����ѼĴ��������뻽�Ѷ�ʱ��
 */
am_static_inline 
void amhw_rtc_setwake (amhw_rtc_t *p_hw_rtc, uint16_t count)
{
    p_hw_rtc->wake = count;
}

/**
 * \brief ��ȡRTC���ѼĴ�����ֵ
 * \param[in] p_hw_rtc : ָ��RTC�Ĵ������ָ��
 * \return    RTC���ѼĴ�����ֵ
 */
am_static_inline 
uint16_t amhw_rtc_getwake (amhw_rtc_t *p_hw_rtc)
{
    return p_hw_rtc->wake;
}

/**
 * @} amhw_if_rtc
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_RTC_H */

/* end of file */

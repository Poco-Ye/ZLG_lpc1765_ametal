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
 * \brief  WWDTӲ�������ӿ�
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-25  fft, first implementation.
 * \endinternal
 */

#ifndef __AMHW_WWDT_H
#define __AMHW_WWDT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_common.h"
#include "amhw_clock.h"
    
/** 
 * \addtogroup amhw_if_wwdt
 * \copydoc amhw_wwdt.h
 * @{
 */

/**
 * \brief WWDT�Ĵ�����Ľṹ��
 */
typedef struct amhw_wwdt {
    __IO uint32_t  mod;         /**< \brief ���Ź���ʱ��ģʽ�Ĵ���          */
    __IO uint32_t  tc;          /**< \brief ���Ź���ʱ����ʱʱ���趨�Ĵ���  */
    __O  uint32_t  feed;        /**< \brief ���Ź�ι�����мĴ���(0xAA 0x55) */
    __I  uint32_t  tv;          /**< \brief ���Ź���ʱ��ֵ�趨�Ĵ���        */
    __I  uint32_t  reserved0;   /**< \brief ����                   */
    __IO uint32_t  warnint;     /**< \brief ���Ź������жϱȽ���ֵ */
    __IO uint32_t  window;      /**< \brief ���Ź���ʱ������ֵ     */
} amhw_wwdt_t;

/**
* \name WWDT ģʽ����
* @{
*/

#define AMHW_WWDT_WDMOD_BITMASK    ((uint32_t)0x3F)  /**< \brief ���Ź�ģʽλ���� */      
#define AMHW_WWDT_WDMOD_WDEN       AM_BIT(0)         /**< \brief ���Ź�ʹ��λ  */ 
#define AMHW_WWDT_WDMOD_WDRESET    AM_BIT(1)         /**< \brief ���Ź���λλ  */ 
#define AMHW_WWDT_WDMOD_WDTOF      AM_BIT(2)         /**< \brief ���Ź���ʱ��־*/    

  
#define AMHW_WWDT_WDMOD_WDINT      AM_BIT(3)         /**< \brief ���Ź������жϱ�־ */ 
#define AMHW_WWDT_WDMOD_WDPROTECT  AM_BIT(4)         /**< \brief ���Ź�����ģʽ */ 
#define AMHW_WWDT_WDMOD_LOCK       AM_BIT(5)         /**< \brief ���Ź�����λ   */

/** @} */
 
 
/**
 * \brief ��ʼ��WWDT
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \return    ��
 */
am_static_inline
void amhw_wwdt_init (amhw_wwdt_t *p_hw_wwdt)
{
    /* ���ܿ��Ź� */
    p_hw_wwdt->mod     = 0;
    p_hw_wwdt->tc      = 0xFF;
    p_hw_wwdt->warnint = 0x0;
    p_hw_wwdt->window  = 0xFFFFFF;
}

/**
 * \brief ���ÿ��Ź���ʱ����ʱʱ�䣬����ι��
 *
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \param[in] timeout   : ��ʱʱ��, ��Χ 0xFF - 0xFFFFFF
 *
 * \return    ��
 */
am_static_inline 
void amhw_wwdt_timeout_set (amhw_wwdt_t *p_hw_wwdt, uint32_t timeout)
{
    p_hw_wwdt->tc = timeout;
}

/**
 * \brief ���Ź�ι������
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \return    ��
 * \note ����ú���δ�����ã����������Ź������ж�
 */
am_static_inline 
void amhw_wwdt_feed (amhw_wwdt_t *p_hw_wwdt)
{
    p_hw_wwdt->feed = 0xAA;
    p_hw_wwdt->feed = 0x55;
}

/**
 * \brief �趨�����жϵ�ֵ
 *
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \param[in] timeout   : ���Ź������жϵıȽ�ֵ
 *
 * \return    ��
 *
 * \note  ���Ź���ʱ����ֵ���趨��ֵƥ�䣬����һ���ж�
 */
am_static_inline
void amhw_wwdt_warning_set (amhw_wwdt_t *p_hw_wwdt, uint32_t timeout)
{
    p_hw_wwdt->warnint = timeout;
}

/**
 * \brief ��ȡ�����жϼĴ�����ֵ
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ�� 
 * \return    ��ǰ�����жϼĴ�����ֵ
 */
am_static_inline 
uint32_t amhw_wwdt_warning_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->warnint;
}

/**
 * \brief �趨���Ź����ڶ�ʱ����ֵ
 *
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \param[in] timeout   : ���ڶ�ʱ����ֵ
 *
 * \return    ��
 */
am_static_inline 
void amhw_wwdt_window_set (amhw_wwdt_t *p_hw_wwdt, uint32_t timeout)
{
    p_hw_wwdt->window = timeout;
}

/**
 * \brief ��ȡ���Ź����ڶ�ʱ����ֵ
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \return    ���Ź����ڶ�ʱ���Ĵ�����ֵ
 */
am_static_inline 
uint32_t amhw_wwdt_window_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->window;
}

/**
 * \brief ʹ�ܿ��Ź���ʱ��ѡ��
 *
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \param[in] options   : ʹ�ܵĿ��Ź���ʱ��ѡ��
 *                        ���磺AMHW_WWDT_WDMOD_WDEN, AMHW_WWDT_WDMOD_WDRESET, 
 *                              �� AMHW_WWDT_WDMOD_WDPROTECT
 * \return    ��
 *
 * \note ʹ��һ���������ɽ���־λ���л����(AMHW_WWDT_WDMOD_WDRESET | 
 *                                            AMHW_WWDT_WDMOD_WDPROTECT)
 *       
 */
am_static_inline 
void amhw_wwdt_option_set (amhw_wwdt_t *p_hw_wwdt, uint32_t options)
{
    p_hw_wwdt->mod = (p_hw_wwdt->mod & AMHW_WWDT_WDMOD_BITMASK) | options;
}

/**
 * \brief ʹ��WWDT
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_wwdt_start (amhw_wwdt_t *p_hw_wwdt)
{
    amhw_wwdt_option_set(p_hw_wwdt, AMHW_WWDT_WDMOD_WDEN);
    amhw_wwdt_feed(p_hw_wwdt);
}

/**
 * \brief ��ȡWWDT״̬��־λ
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \return    ״̬λ, WWDT_WDMOD_*�ĺ�ֵ���߶��WWDT_WDMOD_*��Ļ�OR��ֵ
 */
am_static_inline 
uint32_t amhw_wwdt_status_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->mod;
}

/**
 * \brief ���WWDT״̬λ
 *
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \param[in] flags     : ����ı�־λ
 *
 * \return  ��
 *
 * \note ���������־λ AMHW_WWDT_WDMOD_WDINT, AMHW_WWDT_WDMOD_WDTOF 
 */
am_static_inline
void amhw_wwdt_status_clr (amhw_wwdt_t *p_hw_wwdt, uint32_t flags)
{
    if (flags & AMHW_WWDT_WDMOD_WDTOF) {
        p_hw_wwdt->mod &= (~AMHW_WWDT_WDMOD_WDTOF) & 0x3F;
    }
    
    /* д1������жϱ�־λ */
    if (flags & AMHW_WWDT_WDMOD_WDINT) {
        p_hw_wwdt->mod = (p_hw_wwdt->mod & 0x3F) | AMHW_WWDT_WDMOD_WDINT;
    }
}

/**
 * \brief ��ȡ���Ź���ʱ����ֵ
 * \param[in] p_hw_wwdt : ָ��WWDT�Ĵ������ָ��
 * \return    ���Ź�TV�Ĵ�����ֵ
 */
am_static_inline 
uint32_t amhw_wwdt_currentcount_get (amhw_wwdt_t *p_hw_wwdt)
{
    return p_hw_wwdt->tv;
}

/**
 * @} amhw_if_wwdt
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_WWDT_H */

/* end of file */

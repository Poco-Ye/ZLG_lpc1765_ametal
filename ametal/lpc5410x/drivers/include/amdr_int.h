/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief  NVIC�����������жϱ�׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-29  hbt, first implementation.
 * \endinternal
 */

#ifndef __AMDR_INT_H
#define __AMDR_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_int.h"

/**
 * \addtogroup amdr_if_int
 * \copydoc amdr_int.h
 * @{
 */
    

/**
 * \brief �жϷ�����Ϣ
 */
struct awdr_int_servinfo {

    /** \brief ��ʼ�жϺ� */
    int inum_start;

    /** \brief ĩβ�жϺ� */
    int inum_end;
};

/** \brief �жϷ���������Ϣ */
struct amdr_int_isr_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_isr;

    /** \brief �ص������Ĳ��� */
    void         *p_arg;
};


/** \brief �ж��豸��Ϣ */
typedef struct amdr_int_devinfo {
    
    /** \brief �жϷ�����Ϣʵ�� */
    const struct awdr_int_servinfo int_servinfo;
    
    /** \brief ָ���жϿ������Ĵ������ָ�� */
    amhw_int_t *p_hw_int;
    
    /** \brief ���ж����� */
    int input_cnt;

    /** \brief ISR ��Ϣӳ��(��С�� input_cnt һ��) */
    uint8_t *p_isrmap;

    /** \brief ISR ��Ϣ���� */
    int isrinfo_cnt;

    /** \brief ISR ��Ϣӳ���ڴ�(��С�� isrinfo_cnt һ��) */
    struct amdr_int_isr_info *p_isrinfo;
    
} amdr_int_devinfo_t;

/**
 * \brief �ж��豸ʵ�� 
 */
typedef struct amdr_int_dev {
    
    /** \brief ָ���ж��豸��Ϣ��ָ�� */
    const amdr_int_devinfo_t *p_devinfo;
    
    /** \brief ������Ч��־ */
    bool_t                     valid_flg;
    
} amdr_int_dev_t;



/**
 * \brief �жϳ�ʼ�� 
 *
 * \param[in] p_dev     : ָ���ж��豸��ָ�� 
 * \param[in] p_devinfo : ָ���ж��豸��Ϣ��ָ�� 
 *
 * \retval  AM_OK       : �����ɹ� 
 * \retval -AM_EINVAL   : ��Ч���� 
 */
int amdr_int_init(amdr_int_dev_t *p_dev, const amdr_int_devinfo_t *p_devinfo);

/**
 * \brief �ж�ȥ��ʼ�� 
 *
 * \param[in] p_dev : ָ���ж��豸��ָ�� 
 *
 * \return  �� 
 */
void amdr_int_deinit(amdr_int_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AMDR_INT_H */

/* end of file */

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
 * \brief �ȴ�(wait)��׼�ӿ�
 *
 * �ýӿڵ�ʹ�÷�ʽ�ǣ����ȶ���һ���ȴ��źţ�am_wait_t wait;
 * ����Ҫ�ȴ��ĵط�����:am_wait_on(&wait);
 * ����Ҫ����֮ǰ�����ȴ��ĵط����ã�am_wait_off(&wait)
 *
 * ͨ�������,am_wait_on() �򿪵ȴ��󣬳���ֱ���ȴ���������������� am_wait_off()
 * ��Ż��������ĳ����ִ�С�
 *
 * \internal
 * \par Modification History
 * - 1.00 15-06-12  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_WAIT_H
#define __AM_WAIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup am_if_wait
 * \copydoc am_wait.h
 * @{
 */

 /**
  * \brief ����ȴ��ź�����
  */
typedef volatile bool_t am_wait_t;

/** 
 * \brief �ȴ��źų�ʼ��
 * \param[in] p_wait  : ָ��ȴ��źŵ�ָ��
 * \retval  AM_OK  ��ʼ���ɹ�
 */
am_static_inline
int am_wait_init (am_wait_t *p_wait)
{
    *p_wait = FALSE;
    return AM_OK;
}

/** 
 * \brief �����ȴ��¼�
 *
 * �����һֱ�ȴ���ֱ������ am_wait_done() ָ���ȴ����
 * 
 * \param[in] p_wait  : ָ��ȴ��źŵ�ָ��
 *
 * \retval  AM_OK  ��ʼ���ɹ�
 */
am_static_inline 
int am_wait_on (am_wait_t *p_wait)
{
    *p_wait = FALSE;
    while(*p_wait == FALSE);
    return AM_OK;
}

/** 
 * \brief ָ���ĵȴ��¼����
 *
 * ���øú�����am_wait_on() �����ĵȴ����н��ȴ���ɣ������ȴ�
 * 
 * \param[in] p_wait  : ָ��ȴ��źŵ�ָ��
 *
 * \retval AM_OK  ��ʼ���ɹ�
 */
am_static_inline 
int am_wait_done (am_wait_t *p_wait)
{
    *p_wait = TRUE;
    return AM_OK;
}

/** 
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AM_WAIT_H */

/* end of file */

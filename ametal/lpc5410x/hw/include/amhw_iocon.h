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
* e-mail:      apollo.support\zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief I/O �������� (IOCON) Ӳ�������ӿ�
 * 
 * ����Ϊ�Ա�׼�˿������йص�ѧ���Ե����ã�
 *  - ����/������
 *  - ��©ģʽ��
 *  - ��ת���ܣ�
 *  - ���� PIO0_23 �� PIO0_28 �ǿ�©���ţ�������Ϊ��ͬ��I2C�����ٶȡ�
 * 
 * \internal
 * \par Modification History
 * - 1.01 14-12-06  hbt, amend.
 * - 1.00 14-11-03  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_IOCON_H
#define __AMHW_IOCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
    
 /** 
 * \addtogroup amhw_if_iocon
 * \copydoc amhw_iocon.h
 * @{
 */


/**
  * \brief LPC5410x IOCON �Ĵ�����ṹ��
 */
typedef struct amhw_iocon {
    __IO uint32_t  pio[2][32];       /**< \brief ���� I/O ���ƼĴ��� */
} amhw_iocon_t;


/**
 * \brief I/O ���ܺ�ģʽ����
 *
 * \param[in] p_hw_iocon : ָ��IOCON�Ĵ������ָ��
 * \param[in] pin        : ���ű�ţ�ֵΪ PIO* (#PIO0_0).
 * \param[in] flags      : ���ò���
 *
 * \return    ��
 */
am_local am_inline 
void amhw_iocon_cfg (amhw_iocon_t *p_hw_iocon, int pin, uint32_t flags)
{
    p_hw_iocon->pio[pin >> 5][(pin & 0x1F)] = flags;
}


/**
 * @} amhw_if_iocon
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_IOCON_H */

/* end of file */

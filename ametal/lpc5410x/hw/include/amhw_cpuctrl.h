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
 * \brief CPU����Ӳ�������ӿ�
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-08  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_CPUCTRL_H
#define __AMHW_CPUCTRL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
 
/**
 * \addtogroup amhw_if_cpuctrl
 * \copydoc amhw_cpuctrl.h
 * @{
 */
#define AMHW_CM4_CLK_ENABLE       (1 << 2)    /**< \brief M4��ʱ��ʹ��  */
#define AMHW_CM0_CLK_ENABLE       (1 << 3)    /**< \brief M0+��ʱ��ʹ�� */
#define AMHW_CM4_RESET_ENABLE     (1 << 4)    /**< \brief M4�˸�λʹ��  */
#define AMHW_CM0_RESET_ENABLE     (1 << 5)    /**< \brief M0+�˸�λʹ�� */

/**
 * \brief �Ƿ�����M4�ں˳���
 * \retval  TRUE  : ����M4�ں˳���
 * \retval  FALSE : ����M0+�ں˳���
 */
bool_t amhw_cpu_is_m4core(void);

/**
 * \brief ��ǰ���ں���Ϊ�������Ǵӻ�
 * \retval TRUE  : ����
 * \retval FALSE : �ӻ�
 */
bool_t amhw_cpu_is_master_core(void);

/**
 * \brief ʹ��M4�ں�����M0+�ں�
 * \param[in] m0p_entryaddr : M0+�ں���ڵ�ַ
 * \return None
 */
void amhw_cpu_boot_m0p(uint32_t m0p_entryaddr);

/**
 * @} amhw_if_cpuctrl
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_CPUCTRL_H */ 

/* end of file */

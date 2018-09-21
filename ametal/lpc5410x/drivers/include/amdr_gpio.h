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
 * \brief GPIO����������GPIO��׼�ӿ�
 *
 * \internal
 * \par Modification history
 * - 1.10 14-12-15  hbt, modified interfaces.
 * - 1.00 14-12-02  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_GPIO_H
#define __AMDR_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"  
#include "am_bitops.h"

#include "lpc5410x_pin.h"
#include "amhw_gpio.h"
#include "amhw_iocon.h"
#include "amhw_inmux.h"
#include "amhw_pint.h"

/** 
 * \addtogroup amdr_if_gpio
 * \copydoc amdr_gpio.h
 * @{
 */

/**
 * \brief ���ŵĴ�����Ϣ 
 */
struct amdr_gpio_trigger_info {

    /** \brief �����ص����� */
    am_pfnvoid_t  pfn_callback;

    /** \brief �ص������Ĳ��� */
    void *p_arg;
};

/**
 * \brief GPIO �豸��Ϣ
 */
typedef struct amdr_gpio_devinfo {
    
    /** \brief ָ��GPIO�Ĵ������ָ�� */
    amhw_gpio_t  *p_hw_gpio;
    
    /** \brief ָ��IOCON�Ĵ������ָ�� */
    amhw_iocon_t *p_hw_iocon;

    /** \brief ָ�������жϼĴ������ָ�� */
    amhw_pint_t  *p_hw_pint;

    /** \brief ָ�����븴�üĴ������ָ�� */
    amhw_inmux_t *p_hw_inmux;

    /** \brief GPIO�����жϺ��б� */
    const int8_t inum_pin[PIN_INT_MAX];

    /** \brief GPIO֧�ֵ������жϺ����� */
    size_t       pint_count;

    /** \brief ������Ϣӳ�� */
    uint8_t     *p_infomap;

    /** \brief ָ�����Ŵ�����Ϣ��ָ�� */
    struct amdr_gpio_trigger_info *p_triginfo;
    
} amdr_gpio_devinfo_t;

/**
 * \brief GPIO�豸ʵ�� 
 */
typedef struct amdr_gpio_dev {
    
    /** \brief ָ��GPIO�豸��Ϣ��ָ�� */
    const amdr_gpio_devinfo_t *p_devinfo;
    
    /** \brief ������Ч��־ */
    bool_t                     valid_flg;
    
} amdr_gpio_dev_t;

/**
 * \brief GPIO��ʼ�� 
 *
 * \param[in] p_dev     : ָ��GPIO�豸��ָ�� 
 * \param[in] p_devinfo : ָ��GPIO�豸��Ϣ��ָ�� 
 *
 * \retval AM_OK : �����ɹ� 
 */
int amdr_gpio_init(amdr_gpio_dev_t           *p_dev, 
                   const amdr_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIOȥ��ʼ��
 *
 * \param[in] p_dev : ָ��GPIO�豸��ָ�� 
 *
 * \return �� 
 */
void amdr_gpio_deinit(amdr_gpio_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_GPIO_H */

/* end of file */

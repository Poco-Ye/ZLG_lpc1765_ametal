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
 * \brief I2C����������I2C��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 15-04-16  tee, modified some interface,add the function to support am_i2c_speed_set()
 * - 1.00 15-01-10  jon, first implementation.
 * \endinternal
 */

#ifndef __AMDR_I2C_H
#define __AMDR_I2C_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_int.h"
#include "am_i2c.h"
#include "amhw_i2c.h"

/**
 * \addtogroup amdr_if_i2c
 * \copydoc amdr_i2c.h
 * @{
 */

/**
 * \brief I2C �豸��Ϣ�����ṹ��
 */
typedef struct amdr_i2c_devinfo {
    
    uint32_t         bus_speed;      /**< \brief I2C��ʼ�������ٶ�,am_i2c_speed_set() ��׼�ӿڿ��Ըı����� */
 
    struct amhw_i2c *p_hw_i2c;       /**< \brief ָ��I2C�Ĵ������ָ��  */
    uint16_t         inum;           /**< \brief I2C ���������жϺ�     */
} amdr_i2c_devinfo_t;

/**
 * \brief I2C �豸�ṹ��
 */
typedef struct amdr_i2c_dev {
   
     /** \brief ��׼I2C����           */
    am_i2c_serv_t             i2c_serv;

    /** \brief ָ��I2C����ṹ���ָ��,ͬһʱ��ֻ�ܴ���һ������ */
    am_i2c_transfer_t        *p_trans;
    
    /** \brief �������ݽ���/���ͼ���   */
    uint32_t                  data_ptr; 
    
    /** \brief æ��ʶ                 */
    bool_t                    busy;
    
    /** \brief ״̬                   */
    uint8_t                   state;    
    
    /** \brief ָ��I2C�豸��Ϣ��ָ��   */
    const amdr_i2c_devinfo_t *p_devinfo;
    
} amdr_i2c_dev_t;


/**
 * \brief I2C ��ʼ��
 *
 * \param[in] p_dev     : ָ��I2C�豸�ṹ���ָ��
 * \param[in] p_devinfo : ָ��I2C�豸��Ϣ�ṹ���ָ��
 *
 * \return  I2C��׼���������� 
 */
am_i2c_handle_t amdr_i2c_init(amdr_i2c_dev_t           *p_dev,
                              const amdr_i2c_devinfo_t *p_devinfo);

/**
 * \brief ���I2C��ʼ��
 * \param[in] p_dev : ָ��I2C�豸�ṹ���ָ��
 * \return ��
 */
void amdr_i2c_deinit(amdr_i2c_dev_t *p_dev);



/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_I2C_H */

/* end of file */

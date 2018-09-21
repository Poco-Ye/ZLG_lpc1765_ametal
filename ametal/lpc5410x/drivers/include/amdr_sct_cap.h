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
 * \brief SCT����������CAP��׼�ӿ�
 *
 * 1. SCT֧���ṩ�������ֱ�׼���񣬱������ṩ���Ƿ���CAP��׼�����������
 *     - ��ʱ
 *     - PWM���
 *     - ����
 * 2. �ڱ������У�SCT�����Դʹ�����£�
 *    - ����ͨ��0���ڲ���SCT����0�����¼�0��������Բ����ж�
 *    - ����ͨ��1���ڲ���SCT����1�����¼�1��������Բ����ж�
 *    - ����ͨ��2���ڲ���SCT����2�����¼�2��������Բ����ж�
 *    - ����ͨ��3���ڲ���SCT����3�����¼�3��������Բ����ж�
 *    - ����ͨ��4���ڲ���SCT����4�����¼�4��������Բ����ж�
 *    - ����ͨ��5���ڲ���SCT����5�����¼�5��������Բ����ж�
 *    - ����ͨ��6���ڲ���SCT����6�����¼�6��������Բ����ж�
 *    - ����ͨ��7���ڲ���SCT����7�����¼�7��������Բ����ж�
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-14  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_SCT_CAP_H
#define __AMDR_SCT_CAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_cap.h"
#include "amhw_sct.h"

/**
 * \addtogroup amdr_if_sct_cap
 * \copydoc amdr_sct_cap.h
 * @{
 */

/**
 * \brief SCT��������ص�GPIO��Ϣ��SCT�����ܹ���8��ͨ����ͨ��6��ͨ��7���ڲ���Ϣ
 *        ����Ҫ�ⲿGPIO�ܽ�
 */
typedef struct amdr_sct_cap_ioinfo {
    uint32_t gpio;           /**< \brief ��Ӧ��GPIO�ܽ�                       */
    uint32_t func;           /**< \brief Ϊ������ʱ��GPIO��������           */
    uint32_t dfunc;          /**< \brief ���ܹܽŲ�����ʱ��Ĭ��GPIO�������� */
} amdr_sct_cap_ioinfo_t;

/**
 * \brief SCT��������ص��豸��Ϣ
 */
typedef struct amdr_sct_cap_devinfo {
    amhw_sct_t             *p_hw_sct;      /**< \brief ָ��SCT�Ĵ������ָ��  */
    uint8_t                 inum;          /**< \brief SCT��Ӧ���жϺ�        */
    uint8_t                 channels_num;  /**< \brief ʹ�õ�ͨ���������Ϊ8  */
    amdr_sct_cap_ioinfo_t  *p_ioinfo;      /**< \brief ָ�򲶻�ܽ���Ϣ�ṹ�� */
} amdr_sct_cap_devinfo_t;

/**
 * \brief SCT�������豸
 */
typedef struct amdr_sct_cap_dev {
    am_cap_serv_t          cap_serv;       /**< \brief ��׼CAP����            */

    struct {
        am_cap_callback_t  callback_func;  /**< \brief �ص�����                    */
        void              *p_arg;          /**< \brief �ص��������û�����          */
    } callback_info[8];                    /**< \brief �洢���8ͨ���Ļص�������Ϣ */

    /** \brief ָ��SCT(������)�豸��Ϣ������ָ�� */
    const amdr_sct_cap_devinfo_t *p_devinfo;

} amdr_sct_cap_dev_t;

/**
 * \brief ��ʼ��SCTΪ������
 *
 * \param[in] p_dev     : ָ��SCT(������)�豸��ָ��
 * \param[in] p_devinfo : ָ��SCT(������)�豸��Ϣ������ָ��
 *
 * \return CAP��׼������������ֵΪNULLʱ������ʼ��ʧ��
 */
am_cap_handle_t amdr_sct_cap_init(amdr_sct_cap_dev_t           *p_dev,
                                  const amdr_sct_cap_devinfo_t *p_devinfo);

/**
 * \brief ��ʹ��SCT������ʱ�����ʼ��SCT�����ܣ��ͷ������Դ
 * \param[in] p_dev : ָ��SCT(������)�豸��ָ��
 * \return ��
 */
void amdr_sct_cap_deinit(amdr_sct_cap_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_SCT_CAP_H */

/* end of file */

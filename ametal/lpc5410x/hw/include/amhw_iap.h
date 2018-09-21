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
 * \brief IAP(In-Application programming)�����ӿ�
 *
 * IAPͨ������ROM�еĺ���ʵ��,����������������FLASH��д�Ȳ���.
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_IAP_H
#define __AMHW_IAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc5410x.h"

/**
 * \addtogroup amhw_if_iap
 * \copydoc amhw_iap.h
 * @{
 */

/** IAP ��ROM API�������Ͷ��� */
typedef void (*amhw_iap_entry_t)(unsigned int[], unsigned int[]);

/**
 * \name IAPָ��궨��
 * @{
 */

#define AMHW_IAP_CMD_PREPARE             50  /**< \brief ����׼��ָ��         */
#define AMHW_IAP_CMD_COPY_RAM_TO_FLASH   51  /**< \brief ��RAM����������FLASH */
#define AMHW_IAP_CMD_ERASE_SECTOR        52  /**< \brief ��������ָ��         */
#define AMHW_IAP_CMD_BLANK_CHECK         53  /**< \brief �������ָ��         */
#define AMHW_IAP_CMD_PARTID_READ         54  /**< \brief �� PartID ָ��       */
#define AMHW_IAP_CMD_BOOT_VER_READ       55  /**< \brief �� Boot code �汾��  */
#define AMHW_IAP_CMD_COMPARE             56  /**< \brief ���ݱȽ�ָ��         */
#define AMHW_IAP_CMD_REINVOKE_ISP        57  /**< \brief ���½���ISPģʽ      */
#define AMHW_IAP_CMD_READ_UID            58  /**< \brief ��UIDָ��            */
#define AMHW_IAP_CMD_ERASE_PAGE          59  /**< \brief ҳ����ָ��           */
#define AMHW_IAP_CMD_SIGNATURE_READ      70  /**< \brief ��Signature ָ��     */

/** @} */

/**
 * \brief IAP����״̬����
 */
typedef enum amhw_iap_stat {
    AMHW_IAP_STAT_SUCCESS      = 0,    /**< \brief ָ��ִ�гɹ�               */
    AMHW_IAP_STAT_INVALID_CMD,         /**< \brief �Ƿ�ָ��                   */
    AMHW_IAP_STAT_SRC_ADDR_ERROR,      /**< \brief Դ��ַ���ǰ��ֶ���         */
    AMHW_IAP_STAT_DST_ADDR_ERROR,      /**< \brief Ŀ���ַû����ȷ�ĵ�ַ���� */
    AMHW_IAP_STAT_SRC_ADDR_NOT_MAPPED, /**< \brief Դ��ַ�����ڴ�ӳ����       */
    AMHW_IAP_STAT_DST_ADDR_NOT_MAPPED, /**< \brief Ŀ���ַ�����ڴ�ӳ����     */
    AMHW_IAP_STAT_COUNT_ERROR,         /**< \brief �ֽڸ���ֵ����             */
    AMHW_IAP_STAT_INVALID_SECTOR,      /**< \brief ����ֵ����                 */
    AMHW_IAP_STAT_SECTOR_NOT_BLANK,    /**< \brief �����ǿ�                   */
    AMHW_IAP_STAT_SECTOR_NOT_PREPARED, /**< \brief ����׼��ָ��û��ִ��       */
    AMHW_IAP_STAT_COMPARE_ERROR,       /**< \brief Դ��ַ��Ŀ���ַ���ݲ�ͬ   */
    AMHW_IAP_STAT_BUSY,                /**< \brief FLASH��̽ӿ�æ            */
} amhw_iap_stat_t;


/**
 * \brief �ú�������ֱ�ӵ���ROM API����
 *
 * \param[in]  cmd_param     : ָ���������
 * \param[out] status_result : ָ��ִ�н�����������
 *
 * \return ��
 */
am_static_inline
void amhw_iap_entry (unsigned int cmd_param[], unsigned int status_result[])
{
    ((amhw_iap_entry_t) AMHW_IAP_ENTRY_LOCATION)(cmd_param, status_result);
}

/**
 * \brief д����ǰ������׼������
 *
 * \param[in] start_sec : ��ʼ������
 * \param[in] end_sec   : ����������
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ���������ű�����ڻ������ʼ������
 *
 */
amhw_iap_stat_t amhw_iap_prepare(uint32_t start_sec, uint32_t end_sec);

/**
 * \brief ����RAM��������FLASH�У��൱��FLASHд����
 *
 * \param[in] dst_addr : Ŀ��FLASH��ַ��Ӧ���� 256 �ֽڶ���
 * \param[in] src_addr : ����ԴRAM�ĵ�ַ��Ӧ�����ֶ���
 * \param[in] nbytes   : ���Ƶ����ݸ���, Ӧ���� 256��512 ��1024 ���� 4096
 * \param[in] clkfreq  : ϵͳʱ��Ƶ��(��λ��Hz)
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note �ú�����������FLASH���������ڵ��øú���ǰ����amhw_iap_prepare()��������
 *       д��׼������
 */
amhw_iap_stat_t amhw_iap_copy(uint32_t dst_addr,
                              uint32_t src_addr,
                              uint32_t nbytes,
                              uint32_t clkfreq);

/**
 * \brief ��������
 *
 * \param[in] start_sec : ��ʼ������
 * \param[in] end_sec   : ����������
 * \param[in] clkfreq   : ϵͳʱ��Ƶ��(��λ��Hz)
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ���������ű�����ڻ������ʼ�����ţ��ú�����������FLASH���������ڵ��ø�
 *       ����ǰ����amhw_iap_prepare()��������׼������
 */
amhw_iap_stat_t amhw_iap_erase_sector(uint32_t start_sec,
                                      uint32_t end_sec,
                                      uint32_t clkfreq);

/**
 * \brief ҳ��������ҳ���ҳ����
 *
 * \param[in] start_page : ��ʼҳ��
 * \param[in] end_page   : ����ҳ��
 * \param[in] clkfreq    : ϵͳʱ��Ƶ��(��λ��Hz)
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ����ҳ�ű�����ڻ������ʼҳ�ţ��ú�����������FLASH���������ڵ��ø�
 *       ����ǰ����amhw_iap_prepare()��������׼������
 */
amhw_iap_stat_t amhw_iap_erase_page(uint32_t start_page,
                                    uint32_t end_page,
                                    uint32_t clkfreq);

/**
 * \brief �������������������
 *
 * \param[in] start_sec : ��ʼ������
 * \param[in] end_sec   : ����������
 *
 * \return IAPָ��ִ�е�״̬��ִ������ɹ�(AMHW_IAP_STAT_SUCCESS)��������Ϊ�ա�
 *
 * \note ���������ű�����ڻ������ʼ������
 */
amhw_iap_stat_t amhw_iap_blank_check(uint32_t start_sec, uint32_t end_sec);

/**
 * \brief ��Part IDֵ
 * \return Part IDֵ
 */
uint32_t amhw_iap_part_id_read(void);

/**
 * \brief ��boot code�汾��
 * \return boot code�汾��, �汾�Ÿ�ʽ��<�ֽ�1(���汾��)>.<�ֽ�0(�ΰ汾��)>
 */
uint16_t amhw_iap_boot_ver_read(void);

/**
 * \brief �Ƚ������ڴ��е�����
 *
 * \param[in] dst_addr : ���ݱȽϵ�����Ŀ���ַ��������FLASH��ַ����RAM��ַ
 * \param[in] src_addr : ���ݱȽϵ�����Դ��ַ��������FLASH��ַ����RAM��ַ
 * \param[in] nbytes   : ���ݱȽϵĸ���
 *
 * \return IAPָ��ִ�е�״̬
 *
 * \note ��ַӦ�����ֶ��룬�ֽڸ���Ӧ����4��������
 */
amhw_iap_stat_t amhw_iap_compare(uint32_t dst_addr,
                                 uint32_t src_addr,
                                 uint32_t nbytes);

/**
 * \brief ͨ��IAP�� boot loader�����л���ISPģʽ
 * \return ��
 */
void amhw_iap_reinvoke_isp(void);

/**
 * \brief ��������UID(��128λ)
 * \param[out] uid :
 *              - uid[0] : ��һ��32λ���� (��͵�ַ�����λ0~31��
 *              - uid[1] : �ڶ���32λ����
 *              - uid[2] : ������32λ����
 *              - uid[3] : ���ĸ�32λ����
 * \return IAPָ��ִ�е�״̬
 */
amhw_iap_stat_t amhw_iap_unique_id_read(uint32_t uid[4]);

/**
 * \brief �� signature(FLASH ǩ��) ֵ
 * \return 32λsignatureֵ
 */
uint32_t amhw_iap_signature_read(void);

/**
 * @} amhw_if_iap
 */

#ifdef __cplusplus
}
#endif

#endif

/* end of files */

/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief IAP���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. ���UID,PID,Boot����汾�ź�ǩ����
 *   2. ����RAM��Flash��������ҳ���ݣ�
 *   3. ����������죬˵��IAPָ����ִ�в�������
 *
 * \note ��������ָ�������ſɽ���IAP��ISPָ����������⣬�ɽ���ҳ������������СΪ
 *       32KB��ҳ��СΪ256�ֽڣ�һ����������128ҳ������0��ҳ0λ��0x0000 0000��ַ��
 *
 *       �������   |    ������С[kB]  |    ҳ���   |         ��ַ��Χ
 *    ------------- | ---------------- | ----------- | -------------------------
 *          1       |        32        |    0 - 127  | 0x0000 0000 - 0x0000 7FFF
 *          1       |        32        |  128 - 255  | 0x0000 8000 - 0x0000 FFFF
 *          2       |        32        |  256 - 383  | 0x0001 0000 - 0x0001 7FFF
 *          3       |        32        |  384 - 511  | 0x0001 8000 - 0x0001 FFFF
 *          4       |        32        |  512 - 639  | 0x0002 0000 - 0x0002 7FFF
 *          5       |        32        |  640 - 767  | 0x0002 8000 - 0x0002 FFFF
 *          6       |        32        |  768 - 895  | 0x0003 0000 - 0x0003 7FFF
 *          7       |        32        |  896 - 1023 | 0x0003 8000 - 0x0003 FFFF
 *          8       |        32        | 1024 - 1151 | 0x0004 0000 - 0x0004 7FFF
 *          9       |        32        | 1152 - 1279 | 0x0004 8000 - 0x0004 FFFF
 *          10      |        32        | 1280 - 1407 | 0x0005 0000 - 0x0005 7FFF
 *          11      |        32        | 1408 - 1535 | 0x0005 8000 - 0x0005 FFFF
 *          12      |        32        | 1536 - 1663 | 0x0006 0000 - 0x0006 7FFF
 *          13      |        32        | 1664 - 1791 | 0x0006 8000 - 0x0006 FFFF
 *          14      |        32        | 1792 - 1919 | 0x0007 0000 - 0x0007 7FFF
 *          15      |        32        | 1920 - 2047 | 0x0007 8000 - 0x0007 FFFF
 *
 * \par Դ����
 * \snippet demo_hw_iap.c src_hw_iap
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_hw_iap
 * \copydoc demo_hw_iap.c
 */

/** [src_hw_iap] */
#include "ametal.h"
#include "am_board.h"

/**
 * \brief ���һҳ���ݡ�
 *
 * \param[in]  sector_num     : ������ţ�ȡֵ��Χ��0 ~ 15��
 * \param[in]  page_in_sector : ҳ��ţ�ȡֵ��Χ��0 ~ 127��
 *
 * \return  ��
 */
void print_page_data (uint32_t sector_num, uint8_t page_in_sector)
{
    unsigned char *p_data = NULL;
    uint32_t page_num;
    uint32_t i;

    if (sector_num > 15 || page_in_sector > 127) {
        return;
    }

    page_num = sector_num * 128 + page_in_sector;

    AM_DBG_INFO("The page %d in sector %d data is : \r\n",page_in_sector,sector_num);

    p_data = (uint8_t *)(256 * page_num); /* ҳ����ʼ��ַ */

    /* һҳ�Ĵ�СΪ256�ֽ� */
    for (i = 0; i < 256; i++) {
        AM_DBG_INFO("%3d  ",*p_data++);
        if (((i+1) % 8) == 0) {
            AM_DBG_INFO("\r\n");
        }
    }
    AM_DBG_INFO("\r\n");
}

/**
 * \brief ���������
 */
int main (void)
{
    uint32_t uid[4] = {0,0,0,0};
    uint32_t pid;
    uint8_t  boot_ver[2] = {0,0};
    uint32_t signature;

    uint32_t i;

    amhw_iap_stat_t stat;

    /* ��RAM�е����ݿ�����Flashʱ��RAM��ַ�������ֶ��� */
    __align(4) unsigned char data[512];

    /* �弶��ʼ�� */
    am_board_init();

    /* Flash��������ʱ����ֹ���жϴ�ϣ���Ҫ���ж� */
    __disable_irq();


    /* ��ȡUID */
    stat = amhw_iap_unique_id_read(uid);

    if (stat != AMHW_IAP_STAT_SUCCESS) {

        AM_DBG_INFO("Read UID failed : %d \r\n",stat);
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("uid = 0x%04x%04x%04x%04x\r\n",uid[3],uid[2],uid[1],uid[0]);
    }

    /* ��ȡPID */
    pid = amhw_iap_part_id_read();
    AM_DBG_INFO("PID = 0x%x\r\n",pid);

    /* ��ȡboot����汾�� */
    *((uint16_t *)boot_ver) = amhw_iap_boot_ver_read();
    AM_DBG_INFO("Boot Code version: %d.%d \r\n",boot_ver[1],boot_ver[0]);

    signature = amhw_iap_signature_read();
    AM_DBG_INFO("Signature : 0x%x \r\n", signature);

    /*
     * �����ݴ�RAM������Flash��
     * ������ţ�15����ַ��Χ��0x0007 8000 - 0x0007 FFFF��
     */
    for (i = 0; i < 256; i++) {
        data[i] = i + 1;
    }

    for (i = 256; i < 512; i++) {
        data[i] = i + 7;
    }

    /* ׼������15 */
    amhw_iap_prepare(15,15);

    /* ��������15 */
    amhw_iap_erase_sector(15,15,g_system_clkfreq);

    /* ��������Ƿ�հ� */
    stat = amhw_iap_blank_check(15,15);

    if (stat != AMHW_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The Sector 15 is not blank\r\n");
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("The Sector 15 is blank! \r\n");
    }

    amhw_iap_prepare(15,15);

    /*
     * �����ݴ�RAM������Flash��
     * ����15����ʼ��ַ��0x0007 8000��
     */
    stat = amhw_iap_copy(0x00078000,(uint32_t)&data[0],512,g_system_clkfreq);

    if (stat != AMHW_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("Copy to FLASH failed \r\n");
        am_buzzer_beep(500);
    } else {
        AM_DBG_INFO("Copy to FLASH success \r\n");
    }

    stat = amhw_iap_compare(0x00078000,(uint32_t)&data[0],512);

    if (stat != AMHW_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The data compare failed,%d \r\n",stat);
        am_buzzer_beep(500);
    } else {
        AM_DBG_INFO("The data compare success,the data in flash as follow :\r\n");
        print_page_data(15,0);
        print_page_data(15,1);
    }

    amhw_iap_prepare(15,15);

    /* ����ҳ1920
     * ����15����ʼҳ�����1920(15 * 128).
     * ����15��ʼҳ�����ݶ�����Ϊ��0xFF
     */
    amhw_iap_erase_page(1920,1920,g_system_clkfreq);

    if (stat != AMHW_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The page erase failed,%d \r\n",stat);
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("The page erase success,the data in flash as follow :\r\n");
        print_page_data(15,0);  /* ��������ӦΪ255 */
        print_page_data(15,1);
    }

    /* ����ʹ���ж� */
    __enable_irq();

    while (1) {

        am_led_on(0);
        am_mdelay(200);
        am_led_off(0);
        am_mdelay(200);
    }
}

/** [src_hw_iap] */

/* end of file */

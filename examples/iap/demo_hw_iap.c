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
 * \brief IAP例程，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. 输出UID,PID,Boot代码版本号和签名；
 *   2. 拷贝RAM到Flash，输出相关页数据；
 *   3. 如果蜂鸣器响，说明IAP指令在执行产生错误。
 *
 * \note 在扇区和指定扇区号可进行IAP和ISP指令操作。另外，可进行页擦除。扇区大小为
 *       32KB，页大小为256字节，一个扇区包含128页，扇区0和页0位于0x0000 0000地址。
 *
 *       扇区编号   |    扇区大小[kB]  |    页编号   |         地址范围
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
 * \par 源代码
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
 * \brief 输出一页数据。
 *
 * \param[in]  sector_num     : 扇区编号，取值范围：0 ~ 15。
 * \param[in]  page_in_sector : 页编号，取值范围：0 ~ 127。
 *
 * \return  无
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

    p_data = (uint8_t *)(256 * page_num); /* 页的起始地址 */

    /* 一页的大小为256字节 */
    for (i = 0; i < 256; i++) {
        AM_DBG_INFO("%3d  ",*p_data++);
        if (((i+1) % 8) == 0) {
            AM_DBG_INFO("\r\n");
        }
    }
    AM_DBG_INFO("\r\n");
}

/**
 * \brief 主函数入口
 */
int main (void)
{
    uint32_t uid[4] = {0,0,0,0};
    uint32_t pid;
    uint8_t  boot_ver[2] = {0,0};
    uint32_t signature;

    uint32_t i;

    amhw_iap_stat_t stat;

    /* 将RAM中的数据拷贝到Flash时，RAM地址必须是字对齐 */
    __align(4) unsigned char data[512];

    /* 板级初始化 */
    am_board_init();

    /* Flash更新数据时，禁止被中断打断，需要关中断 */
    __disable_irq();


    /* 读取UID */
    stat = amhw_iap_unique_id_read(uid);

    if (stat != AMHW_IAP_STAT_SUCCESS) {

        AM_DBG_INFO("Read UID failed : %d \r\n",stat);
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("uid = 0x%04x%04x%04x%04x\r\n",uid[3],uid[2],uid[1],uid[0]);
    }

    /* 读取PID */
    pid = amhw_iap_part_id_read();
    AM_DBG_INFO("PID = 0x%x\r\n",pid);

    /* 读取boot代码版本号 */
    *((uint16_t *)boot_ver) = amhw_iap_boot_ver_read();
    AM_DBG_INFO("Boot Code version: %d.%d \r\n",boot_ver[1],boot_ver[0]);

    signature = amhw_iap_signature_read();
    AM_DBG_INFO("Signature : 0x%x \r\n", signature);

    /*
     * 将数据从RAM拷贝到Flash。
     * 扇区编号：15，地址范围：0x0007 8000 - 0x0007 FFFF。
     */
    for (i = 0; i < 256; i++) {
        data[i] = i + 1;
    }

    for (i = 256; i < 512; i++) {
        data[i] = i + 7;
    }

    /* 准备扇区15 */
    amhw_iap_prepare(15,15);

    /* 擦除扇区15 */
    amhw_iap_erase_sector(15,15,g_system_clkfreq);

    /* 检查扇区是否空白 */
    stat = amhw_iap_blank_check(15,15);

    if (stat != AMHW_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The Sector 15 is not blank\r\n");
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("The Sector 15 is blank! \r\n");
    }

    amhw_iap_prepare(15,15);

    /*
     * 将数据从RAM拷贝到Flash。
     * 扇区15的起始地址是0x0007 8000。
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

    /* 擦除页1920
     * 扇区15的起始页编号是1920(15 * 128).
     * 扇区15起始页的数据都将改为：0xFF
     */
    amhw_iap_erase_page(1920,1920,g_system_clkfreq);

    if (stat != AMHW_IAP_STAT_SUCCESS) {
        AM_DBG_INFO("The page erase failed,%d \r\n",stat);
        am_buzzer_beep(500);

    } else {
        AM_DBG_INFO("The page erase success,the data in flash as follow :\r\n");
        print_page_data(15,0);  /* 所有数据应为255 */
        print_page_data(15,1);
    }

    /* 重新使能中断 */
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

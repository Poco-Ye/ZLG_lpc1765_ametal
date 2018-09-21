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
 * \brief CRC���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. �������CRC��������
 *   2. LED��0.5s��ʱ������˸��
 * 
 * \par Դ����
 * \snippet demo_std_crc.c src_std_crc 
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-01-19  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_crc
 * \copydoc demo_std_crc.c
 */

/** [src_std_crc] */
#include "ametal.h"
#include "am_board.h"

/** \brief CRC�������� */
const uint8_t data_test[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

/** \brief CRC�������ݵĳ��� */
uint32_t length_test = sizeof(data_test) / sizeof(data_test[0]);

/**
 * \brief ���������
 */
int main (void)
{  
    am_crc_handle_t crc_handle;
    uint32_t        crc_result;
    
    /* ����CRC-16ģ�� */
    am_crc_pattern_t crc_pattern = {
        16,          /* CRC���(�磺CRC5 �Ŀ��Ϊ 5)           */
        0x8005,      /* CRC���ɶ���ʽ                          */
        0x0000,      /* CRC��ʼֵ                              */
        TRUE,        /* �������������Ҫλ��ת�����ֵΪTRUE   */
        TRUE,        /* ���������ֵ��Ҫλ��ת�����ֵΪTRUE */
        0x0000,      /* ������ֵ                             */
    };

    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_crc_init();
    
    crc_handle = amdr_crc_init(&g_crc_dev, 
                               &g_crc_devinfo);
    
    /* ��ʼ��CRCΪCRC-16ģ�� */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-16 init failed\r\n");
    } else {
        am_crc_cal(crc_handle, data_test, length_test);
        am_crc_final(crc_handle, &crc_result);
        
        /* ������ӦΪ��0xbb3d     */
        AM_DBG_INFO("CRC-16 result is        : 0x%x \r\n", crc_result);
    }
    
    /* �ı�ģ��ΪCRC-CCITTģ�� */
    
    crc_pattern.width     = 16;
    crc_pattern.poly      = 0x1021;
    crc_pattern.initvalue = 0xFFFF;
    crc_pattern.refin     = FALSE;
    crc_pattern.refout    = FALSE;
    crc_pattern.xorout    = 0x0000;
    
    /* ��ʼ��CRCΪCRC-CCITTģ�� */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-ccitt init failed\r\n");
    
    } else {
        am_crc_cal(crc_handle, data_test, length_test);
        am_crc_final(crc_handle, &crc_result);
        
        /* ������ӦΪ��0x29b1     */
        AM_DBG_INFO("CRC-CCITT result is     : 0x%x \r\n", crc_result);
    }
    
    /* �ı�ģ��ΪCRC-32ģ�� */
    crc_pattern.width     = 32;
    crc_pattern.poly      = 0x04C11DB7;
    crc_pattern.initvalue = 0xFFFFFFFF;
    crc_pattern.refin     = TRUE;
    crc_pattern.refout    = TRUE;
    crc_pattern.xorout    = 0xFFFFFFFF;

    /* ��ʼ��CRCΪCRC-32ģ�� */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-32 init failed\r\n");
    
    } else {
        am_crc_cal(crc_handle, data_test, length_test);
        am_crc_final(crc_handle, &crc_result);
        
        /* ������ӦΪ��0xcbf43926     */
        AM_DBG_INFO("CRC-32 result is        : 0x%x \r\n", crc_result);
    }
    
    while (1) {
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}

/** [src_std_crc] */

/* end of file */

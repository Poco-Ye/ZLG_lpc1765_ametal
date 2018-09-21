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
 * \brief ��I2C�ж�ģʽ�²���EEPROM��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *   1. ��I2C�ӿں�EEPROM�ӿڶ�Ӧ�������ӣ�
 *   2. ���������ص�demo���ϣ��������ϵ��λ��
 *
 * - ʵ������:
 *   1. ��ȡEEPROM�е�����ͨ�����ڴ�ӡ������
 *   2. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED��200ms�����˸��
 *
 * \note ����ʾ���̺� demo_std_i2c_master ��ʾ���̣�ʵ�ֵ����õĽӿں�����ͬ����������ͬ
 *
 * \par Դ����
 * \snippet demo_std_i2c_int_eeprom.c src_std_i2c_int_eeprom 
 * 
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_std_i2c_int_eeprom
 * \copydoc demo_std_i2c_int_eeprom.c
 */

/** [src_std_i2c_int_eeprom] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"

#define EEPROM_ADDR             0x50            /**< \brief EEPROM�豸�ĵ�ַ */
#define TEST_LEN                0x10            /**< \brief ����EEPROM��ҳ��С */


/**
 * \brief ������
 */
int main (void)
{
    am_i2c_handle_t    i2c_handle;
    am_i2c_device_t    eeprom;                      /* I2C �����豸����           */
    uint8_t            eeprom_buf[16] = {0};        /* ���ݻ��涨��               */
    uint8_t            test_addr      =  0x90 ;     /* I2C �����ӻ��豸�ӵ�ַ���� */
    uint8_t            i;
    int                ret;
    
    am_board_init();                                /* �弶��ʼ�� */

    amhw_plfm_i2c0_init();                          /* I2C0 Ӳ��ƽ̨��ʼ�� */
    
    AM_DBG_INFO("I2C operate EEPROM demo.\r\n");
    
    /* I2C ��ʼ�� */
    i2c_handle = amdr_i2c_init(&g_i2c0_dev, &g_i2c0_devinfo);
    am_i2c_connect(i2c_handle);                     /* I2C �ж����� */
    
    am_i2c_mkdevice(&eeprom,
                    EEPROM_ADDR,
                    AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = (i + 5);
    }
    
    /* д�����ݵ�ָ����EEPROM��ַ */
    ret = am_i2c_write(i2c_handle,
                       &eeprom,
                        test_addr,
                       (uint8_t *)eeprom_buf, 
                       TEST_LEN);
    
    if (ret != AM_OK) {
        AM_DBG_INFO("д���ݣ�I2C������ִ���,������룺%d\r\n",ret);
    }

    am_mdelay(10);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    
    /* ��ȡ���ݵ�ָ����EEPROM��ַ */
    ret = am_i2c_read(i2c_handle,
                      &eeprom,
                      test_addr,
                      (uint8_t *)eeprom_buf, 
                      TEST_LEN);

    if (ret != AM_OK) {
        AM_DBG_INFO("�����ݣ�I2C������ִ���,������룺%d\r\n",ret);
        while(1);
    }
    
    am_mdelay(10);

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is %2X\r\n", i ,eeprom_buf[i]);
        
        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 5)) {
            while(1);
        }
    }
    
    /* У��ɹ���LED��200msʱ������˸ */
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_std_i2c_int_eeprom] */

/* end of file */

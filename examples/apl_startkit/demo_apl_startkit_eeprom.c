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
 * \brief APL_StartKit EEPROM��ʾ����
 *
 * - ��������:
 *   1. ��APL_StartKit���ӵ�EasyARM-54000M4 demo�壻
 *   2. ��APL_StartKit����ϴ���0�ӿڣ�J3�����ӵ�PC���ϡ�
 *
 * - ʵ������:
 *   1. ��ȡEEPROM�е�����ͨ�����ڴ�ӡ������
 *   2. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED_RUN(��)��200ms�����˸,
 *      ��֮��RUN_LED(��)����
 *
 * \par Դ����
 * \snippet demo_apl_startkit_eeprom.c src_apl_startkit_eeprom 
 * 
 * \internal
 * \par History
 * - 1.00 15-03-17  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_apl_startkit_eeprom
 * \copydoc demo_apl_startkit_eeprom.c
 */

/** [src_apl_startkit_eeprom] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"

/**
 * \name EEPROM �豸��������
 * @{ 
 */
#define EEPROM_ADDR             0x50            /**< \brief EEPROM�豸�ĵ�ַ   */

/** \brief EEPROM�豸�ӵ�ַ��CAT240C02�ӵ�ַ��Χ0x00-0xFF */
#define TEST_ADDR               0x10            
#define TEST_LEN                0x10            /**< \brief ����EEPROM��ҳ��С */
/** @} */

/**
 * \name APL_StartKit ���IO����
 * @{ 
 */
#define RUN_LED                 PIO1_5          /**< \brief RUNָʾ��IO�˿ڶ��� */
#define ERR_LED                 PIO0_9          /**< \brief ERRָʾ��IO�˿ڶ��� */
/** @} */

/**
 * \brief APL_StartKit �����س�ʼ��
 */
void apl_startkit_init(void)
{
    am_gpio_pin_cfg(RUN_LED, AM_GPIO_OUTPUT);        /* ����PIO1_4 RUN_LED   */
    am_gpio_set(RUN_LED, 1);                         /* RUN_LED ��ʼ״̬Ϩ�� */
    am_gpio_pin_cfg(ERR_LED, AM_GPIO_OUTPUT);        /* ����PIO1_5 ERR_LED   */
    am_gpio_set(ERR_LED, 1);                         /* RUN_LED ��ʼ״̬Ϩ�� */
}

/**
 * \brief ������
 */
int main (void)
{
    am_i2c_handle_t    i2c_handle;
    am_i2c_device_t    eeprom;                      /* I2C �����豸����           */
    uint8_t            eeprom_buf[16] = {0};        /* ���ݻ��涨��               */
    uint8_t            i;
    bool_t             verify_ok_flag = TRUE;       /* У��ɹ�����־��
                                                        TRUE-У��ɹ� 
                                                        FALSE-У��ʧ�� */
    
    am_board_init();                                /* �弶��ʼ�� */
    
    apl_startkit_init();                            /* APL_StartKit ��ʼ�� */
    
    amhw_plfm_i2c0_init();                          /* I2C0 Ӳ��ƽ̨��ʼ�� */
    
    AM_DBG_INFO("I2C operate APL_StartKit��s EEPROM .\r\n");
    
    /* I2C ��ʼ�� */
    i2c_handle = amdr_i2c_init(&g_i2c0_dev, &g_i2c0_devinfo);
    am_i2c_connect(i2c_handle);                     /* I2C �ж����� */
    
    am_i2c_mkdevice(&eeprom,
                    EEPROM_ADDR,
                    AM_I2C_ADDR_7BIT | AW_I2C_SUBADDR_1BYTE,
                    0x01);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = (i + 5);
    }
    
    /* д�����ݵ�ָ����EEPROM��ַ */
    am_i2c_write(i2c_handle,
                 &eeprom,
                 TEST_ADDR,
                 (uint8_t *)eeprom_buf, 
                 TEST_LEN);

    am_mdelay(10);

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    
    /* ��ȡ���ݵ�ָ����EEPROM��ַ */
    am_i2c_read(i2c_handle,
                &eeprom,
                TEST_ADDR,
                (uint8_t *)eeprom_buf, 
                TEST_LEN);

    am_mdelay(10);

    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is %2X\r\n", i ,eeprom_buf[i]);
        
        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 5)) {
            AM_DBG_INFO(" Verify failed!\r\n");
            verify_ok_flag = FALSE;
        }
    }
    
    
    while (1) {
        
        /* У��ɹ���RUN_LED(�̵�)��200msʱ������˸ */
        if(verify_ok_flag) {
            am_gpio_set(RUN_LED, 0); 
            am_mdelay(200);
        
            am_gpio_set(RUN_LED, 1); 
            am_mdelay(200);
            
        /* У��ʧ�ܣ�ERR_LED(���)���� */
        } else {
            am_gpio_set(ERR_LED, 0); 
        }
    }
}


/** [src_apl_startkit_eeprom] */

/* end of file */

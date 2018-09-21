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
 * \brief I2C������ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������::
 *   1. ������I2C�ӿںʹӻ�I2C�ӿڶ�Ӧ�������ӣ�
 *   2. ���������ص�demo���ϣ��������ϵ��λ��
 *
 * - ʵ������:
 *   1. ����д��ַ�����ݵ��ӻ�����ͨ�����ڴ�ӡ������
 *   2. �������մӻ����ݣ���ͨ�����ڴ�ӡ����
 *   3. ����д������ݺͽ��յ��Ĵӻ��ӻ�����һ�£�У��ͨ����LED��200msʱ������˸��
 *
 * \note ����ʾ���̺� demo_std_i2c_int_eeprom ��ʾ�������õĽӿں�����ͬ����������ͬ
 *
 * \par Դ����
 * \snippet demo_std_i2c_master.c src_std_i2c_master 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_std_i2c_master
 * \copydoc demo_std_i2c_master.c
 */
 
/** [src_std_i2c_master] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


#define EEPROM_ADDR             0x50            /**< \brief EEPROM�豸�ĵ�ַ */
#define TEST_LEN                0x10            /**< \brief ����EEPROM��ҳ��С */


bool_t g_trans_flag;                            /**< \brief �����־λ���� */
/**
 * \brief I2C ������ɻص�����
 * \param[in] p_arg  : �ص�������ڲ���
 * \param[in] status : ����״̬λ
 * \return  ��
 */
void  i2c_transfer_complete(void *p_arg, int status)
{
    if(status == AM_OK) {
        g_trans_flag = TRUE;
    } else {
//        AM_DBG_INFO("I2C transfer error, status is %d",status);
    }
    
}



/**
 * \brief ������
 */
int main (void)
{
    am_i2c_handle_t    i2c_handle;
    am_i2c_transfer_t  trans;
    uint8_t            eeprom_buf[16] = {0};        /* ���ݻ��涨��               */
    uint8_t            test_addr[2]   = {0x10};     /* I2C �����ӻ��豸�ӵ�ַ���� */
    uint8_t            i;
    
    am_board_init();                                /* �弶��ʼ�� */

    amhw_plfm_i2c0_init();                          /* I2C0 Ӳ��ƽ̨��ʼ�� */
    
    AM_DBG_INFO("I2C master test demo.\r\n");
    
    /* I2C ��ʼ�� */
    i2c_handle = amdr_i2c_init(&g_i2c0_dev, &g_i2c0_devinfo);
    am_i2c_connect(i2c_handle);                     /* I2C �ж����� */
 
    /* ����transfer�ṹ�������д���ַ */
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_WR,
                   (uint8_t *)test_addr, 
                   1,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));

    /* ����transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* �ȴ�transfer��� */
    while (!g_trans_flag);
    g_trans_flag = FALSE;

    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = (i + 6);
    }
    
    /* ����transfer�ṹ�������д������ */
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_NOSTART | AM_I2C_M_WR | AM_I2C_M_STOP, 
                   (uint8_t *)eeprom_buf, 
                   TEST_LEN,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));

    /* ����transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* �ȴ�transfer��� */
    while (!g_trans_flag);   
    g_trans_flag = FALSE;

    am_mdelay(10);
    
    /* ����transfer�ṹ�������д���ַ */
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE  | AM_I2C_M_WR, 
                   (uint8_t *)test_addr, 
                   1,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));
    
    /* ����transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* �ȴ�transfer��� */
    while (!g_trans_flag);
    g_trans_flag = FALSE;
                   
    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    
    /* ����transfer�ṹ���������ȡ����ģʽ*/
    am_i2c_mktrans(&trans, 
                   EEPROM_ADDR, 
                   AM_I2C_ADDR_7BIT | AM_I2C_SUBADDR_1BYTE | AM_I2C_M_RD | AM_I2C_M_STOP,
                   (uint8_t *)eeprom_buf, 
                   TEST_LEN,
                   (int (*)(void *,int))i2c_transfer_complete,
                   (void *)(i2c_handle));
    
    /* ����transfer */
    am_i2c_transfer(i2c_handle, &trans);
    
    /* �ȴ�transfer��� */
    while (!g_trans_flag);  
    g_trans_flag = FALSE;


    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is %2X\r\n", i ,eeprom_buf[i]);
        
        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 6)) {
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

/** [src_std_i2c_master] */

/* end of file */

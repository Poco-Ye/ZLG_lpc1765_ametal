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
 * \brief I2C�ӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ���ӻ�I2C�ӿں�����I2C�ӿڶ�Ӧ�������ӣ�
 *   2. ���������ص�demo���ϣ��������ϵ��λ��
 *
 * - ʵ������:
 *   1. �ӻ���������д��ַ�����ݵ��ӻ�����ͨ�����ڴ�ӡ���� ��
 *   2. �ӻ������������������ݣ���ͨ�����ڴ�ӡ���� ��
 *   3. LED��200msʱ������˸��
 *
 * \par Դ����
 * \snippet demo_hw_i2c_slave.c src_hw_i2c_slave 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_i2c_slave
 * \copydoc demo_hw_i2c_slave.c
 */
 
/** [src_hw_i2c_slave] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


#define I2C_SLAVE            AMHW_I2C0        /* I2C�ӻ�������ͨ����   */ 
#define OPERATE_ADDR         0x50             /* ���������ӻ���ַ����*/


/**
 * \brief I2C�ӻ���ʼ�����ú��� 
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] dev_addr : ���������ӻ��ĵ�ַ����
 *
 * \retval  AM_OK  : ��ʼ���������
 */
int i2c_slave_init (amhw_i2c_t *p_hw_i2c, uint8_t dev_addr)
{
    amhw_i2c_mode_disable(p_hw_i2c, AM_I2C_SLAVE_MODE);
    amhw_i2c_slvadr0_set(p_hw_i2c, dev_addr << 1);
    amhw_i2c_mode_enable(p_hw_i2c, AM_I2C_SLAVE_MODE);
    return AM_OK;
}

/**
 * \brief I2C�ӻ���������
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] p_txbuf  : ��������/��ַ����
 * \param[in] nbytes   : ���ͻ���ĳ���
 *
 * \retval  AM_OK  : �������
 */
int i2c_slv_send (amhw_i2c_t      *p_hw_i2c, 
                  const uint8_t   *p_txbuf, 
                  uint32_t         nbytes)
{
    uint8_t i;
    amhw_i2c_slv_continue(p_hw_i2c);
    for (i = 0;i < nbytes; i++) {
        
        while ((p_hw_i2c->stat & AMHW_I2C_SLAVE_STATE_MASK) != 
                AMHW_I2C_STAT_SLVTX);

        amhw_i2c_slvdat_write(p_hw_i2c, *p_txbuf++);
        amhw_i2c_slv_continue(p_hw_i2c); 
    }
   
    return AM_OK;
}

/**
 * \brief I2C�ӻ���������
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] p_rxbuf  : ��������/��ַ����
 * \param[in] nbytes   : ���ջ���ĳ���
 *
 * \retval  AM_OK  : �������
 */
int i2c_slv_recv(amhw_i2c_t *p_hw_i2c, 
                 uint8_t    *p_rxbuf, 
                 uint32_t    nbytes)
{
    uint8_t i;
    amhw_i2c_slv_continue(p_hw_i2c);
    for (i = 0;i < nbytes; i++) {
        
        while ((p_hw_i2c->stat & AMHW_I2C_SLAVE_STATE_MASK) != 
                AMHW_I2C_STAT_SLVRX);
        
       *p_rxbuf++ = amhw_i2c_slvdat_read(p_hw_i2c);
        amhw_i2c_slv_continue(p_hw_i2c);
    }
    return 0;
}


/**
 * \brief ������
 */
int main (void)
{
    uint8_t    i2c_rxdata_buf[32];
    uint8_t    i2c_rxaddr_buf[32];
    uint32_t   length = 16; 
    uint16_t   i;
    
    am_board_init();                                /* �弶��ʼ�� */
    amhw_plfm_i2c0_init();                          /* I2C0 Ӳ��ƽ̨��ʼ�� */
    
    AM_DBG_INFO("I2C slave test demo.\r\n");
        
    i2c_slave_init(I2C_SLAVE, OPERATE_ADDR);        /* I2C �ӻ���ʼ������ */
    
    
    /* �����������͸��ӻ��ĵ�ַ */
    i2c_slv_recv(I2C_SLAVE, 
                 (uint8_t *)i2c_rxaddr_buf, 
                 1);
    
    /* �����������͸��ӻ������� */
    i2c_slv_recv(I2C_SLAVE, 
                 (uint8_t *)i2c_rxdata_buf, 
                 length);

    AM_DBG_INFO("slave receive address is : 0x%2x \r\n", i2c_rxaddr_buf[0]);
    
    for (i = 0;i < length; i++) {
        AM_DBG_INFO("slave receive %2dst data is : 0x%2x \r\n", i, i2c_rxdata_buf[i]);
    }
    
    /* �����������͸��ӻ��ĵ�ַ */
    i2c_slv_recv(I2C_SLAVE, 
                 (uint8_t *)i2c_rxaddr_buf, 
                 1);

    
    /* ���ʹ��������յ������� */
    i2c_slv_send(I2C_SLAVE, 
                 (uint8_t *)i2c_rxdata_buf, 
                 length);

    AM_DBG_INFO("slave receive address is : 0x%2x \r\n", i2c_rxaddr_buf[0]);

    for (i = 0;i < length; i++) {
        AM_DBG_INFO("slave transmit %2dst data is : 0x%2x \r\n", i, i2c_rxdata_buf[i]);
    }
    
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);

    }  
}

/** [src_hw_i2c_slave] */

/* end of file */


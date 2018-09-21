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
 * \brief ��I2C��ѯģʽ�²���EEPROM��ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������:
 *   1. ��I2C�ӿں�EEPROM�ӿڶ�Ӧ�������ӣ�
 *   2. ���������ص�demo���ϣ��������ϵ��λ��
 *
 * - ʵ������:
 *   1. ��ȡEEPROM�е�����ͨ�����ڴ�ӡ������
 *   2. ��д�����ݺͶ�ȡ������һ�£�У��ͨ����LED��200ms�����˸��
 *
 * \par Դ����
 * \snippet demo_hw_i2c_polling_eeprom.c src_hw_i2c_polling_eeprom 
 * 
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_i2c_polling_eeprom
 * \copydoc demo_hw_i2c_polling_eeprom.c
 */
 
/** [src_hw_i2c_polling_eeprom] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"

#define I2C_M_7BIT      0x0000u    /**< \brief 7-bits �豸��ַ  */
#define I2C_M_10BIT     0x0001u    /**< \brief 10-bit �豸��ַ  */
#define I2C_M_WR        0x0000u    /**< \brief д����           */
#define I2C_M_RD        0x0002u    /**< \brief ������           */
#define I2C_M_NOSTART   0x0010u    /**< \brief ��������������ʶ */


#define I2C_MASTER      AMHW_I2C0  /**< \brief I2C����������ͨ���Ŷ���   */
#define I2C_SPEED       400000     /**< \brief I2C�������ٶȲ�������     */
#define I2C_CLKDIV      6          /**< \brief I2C������ʱ�ӷ�Ƶ�������� */
#define EEPROM_ADDR     0x50       /**< \brief EEPROM�豸��ַ����        */
#define TEST_LEN        0x10       /**< \brief ����EEPROM��ҳ��С        */

/**
 * \brief I2C����ṹ�嶨�壬��Ҫ����I2C��ѯģʽ�¡�
 */ 
typedef struct i2c_transfer {
    volatile uint16_t   addr;      /**< \brief I2C�豸��ַ          */ 
    volatile uint16_t   flags;     /**< \brief I2C �豸�����Լ�transfer��Ҫ�������ʶ */
    volatile void      *p_buf;     /**< \brief I2C �������ݻ���ָ�� */
    volatile uint16_t   length;    /**< \brief I2C ���ݻ��泤��     */
} i2c_transfer_t;

i2c_transfer_t __g_i2c0_transfer;

/**
 * \brief I2C����ṹ��������ú���
 *
 * \param[in] p_trans : ָ��I2C����ṹ���ָ��
 * \param[in] addr    : �豸��ַ����
 * \param[in] flags   : ������Ʊ�ʶλ���� 
 * \param[in] p_buf   : ָ���ͻ��߽������ݻ����ָ��
 * \param[in] length  : ������ֽڳ��Ȳ���
 *
 * \retval  AM_OK     : ����ṹ���������
 */
int i2c_mktrans (i2c_transfer_t    *p_trans, 
                 uint16_t           addr,  
                 uint16_t           flags, 
                 void              *p_buf, 
                 uint16_t           length)
{
    if(p_trans == NULL) {
        return -AM_EINVAL;
    }
    
    p_trans->addr   = addr;
    p_trans->flags  = flags;
    p_trans->p_buf  = p_buf; 
    p_trans->length = length;
    
    return AM_OK;
}

/**
 * \brief I2C������������
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] p_trans  : ָ��I2C����ṹ���ָ��
 *
 * return   ��
 */
void i2c_mst_start (amhw_i2c_t     *p_hw_i2c, 
                    i2c_transfer_t *p_trans)
{
    uint16_t dev_addr = (p_trans->addr) << 1;
    
    if(!(p_trans->flags & I2C_M_NOSTART)) {
        
        if (p_trans->flags & I2C_M_RD) {
            dev_addr |= 0x1;            /* ����bit0Ϊ1��������ǰΪ������ */
        } else {
            dev_addr |= 0x0;            /* ����bit0Ϊ0��������ǰΪд���� */
        }
   
    /* �����豸��ַ */
    amhw_i2c_mstdat_write(p_hw_i2c, dev_addr);
    amhw_i2c_mst_start(p_hw_i2c);       /* I2C ���������������ź� */
    }
}

/**
 * \brief I2C�������͵�ַ/����
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] p_trans  : ָ��I2C����ṹ���ָ��
 *
 * \retval  AM_OK  : ������� 
 */
int i2c_mst_send (amhw_i2c_t     *p_hw_i2c, 
                  i2c_transfer_t *p_trans)
                      
{
    uint8_t i;

    for (i = 0;i < p_trans->length; i++) {

        while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)) ; 
        while ((p_hw_i2c->stat & AMHW_I2C_MASTER_STATE_MASK) != AMHW_I2C_STAT_MSTTX);
        
        amhw_i2c_mstdat_write(p_hw_i2c, ((uint8_t *)(p_trans->p_buf))[i]);
        amhw_i2c_mst_continue(p_hw_i2c);
    }
    while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)); 
    while ((p_hw_i2c->stat & AMHW_I2C_MASTER_STATE_MASK) != AMHW_I2C_STAT_MSTTX);

    return AM_OK;
}

/**
 * \brief  I2C�������յ�ַ/����
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] p_trans  : ָ��I2C����ṹ���ָ��
 *
 * \retval  AM_OK  : ������� 
 */
int i2c_mst_recv (amhw_i2c_t     *p_hw_i2c, 
                  i2c_transfer_t *p_trans)
{
    uint8_t i;

    for (i = 0; i < p_trans->length; i++) {
        while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)) ; 

        while (!(p_hw_i2c->stat & AMHW_I2C_STAT_MSTPEND)) ; 
        while ((p_hw_i2c->stat & AMHW_I2C_MASTER_STATE_MASK) != AMHW_I2C_STAT_MSTRX); 
        
        /* receive data */
        ((uint8_t *)(p_trans->p_buf))[i] = amhw_i2c_mstdat_read(p_hw_i2c);

        if (i != (p_trans->length - 1)) {
            amhw_i2c_mst_continue(p_hw_i2c);
        }
    }
    return AM_OK;    
}

/**
 * \brief I2C������������
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] speed    : �����ٶȲ���
 *
 * \retval  AM_OK  : �������
 */
int i2c_speed_set (amhw_i2c_t *p_hw_i2c, uint32_t speed)
{

    uint32_t    scl;
    uint32_t    scl_h, scl_l;
    
    scl = amhw_clock_periph_freq_get(p_hw_i2c) / 
          ((amhw_i2c_clkdiv_get(p_hw_i2c)+1) * speed);

    scl_h = scl >> 1;
    scl_l = (scl - scl_h);
    if (scl_h < 2) {
        scl_h = 2;
    
    } else if (scl_h > 9) {
        scl_h = 9;
    }
    
    if (scl_l < 2) {
        scl_l = 2;
   
   } else if (scl_l > 9) {
        scl_l = 9;
    }
    amhw_i2c_msttime_set(p_hw_i2c, ((scl_l-2) << 0) | ((scl_h-2) << 4));
    
    return AM_OK;
}

/**
 * \brief I2C������ʼ������ 
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] speed    : �����ٶȲ���
 * \param[in] clkdiv   : I2C ����ʱ�ӷ�Ƶ����
 *
 * \retval  AM_OK      : �������
 * \retval  -AM_EINVAL : ������Ч
 */
int i2c_mst_init (amhw_i2c_t *p_hw_i2c, uint32_t speed, uint32_t clkdiv)
{

    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }
    
    /* �ر�I2C�����������ò��� */
    amhw_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);

    /* ����ʱ�ӷ�Ƶ���� */
    amhw_i2c_clkdiv_set(p_hw_i2c, clkdiv);
    
    /* �������� */
    i2c_speed_set(p_hw_i2c, speed);

    /* ����������ɣ�����I2C������ */
    amhw_i2c_mode_enable(p_hw_i2c, AM_I2C_MASTER_MODE);

    return AM_OK;
}

/**
 * \brief ������
 */
int main (void)
{
    i2c_transfer_t   *p_trans = &__g_i2c0_transfer;
    uint8_t           eeprom_buf[16] = {0};
    uint8_t           test_addr[2]   = {0x90};
    uint8_t           i;
                     
    
    am_board_init();                                 /* �弶��ʼ��          */
    amhw_plfm_i2c0_init();                           /* I2C0 ƽ̨��س�ʼ�� */
    
    AM_DBG_INFO("I2C operate EEPROM demo in polling mode .\r\n");
    
    
    i2c_mst_init(I2C_MASTER, I2C_SPEED, I2C_CLKDIV); /* I2C������ʼ������ */

     /* ����transfer�ṹ�������д���ַ */
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_WR), 
                (uint8_t *)test_addr, 
                1);
                
    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_send (I2C_MASTER, p_trans);
    
    for (i = 0;i < TEST_LEN; i++) {
        eeprom_buf[i] = i + 0xA;
    }

     /* ����transfer�ṹ�������д������ */
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_NOSTART | I2C_M_WR), 
                (uint8_t *)eeprom_buf, 
                TEST_LEN);

    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_send(I2C_MASTER, p_trans);
    
    /* ������ǰ���� */
    amhw_i2c_mst_stop(I2C_MASTER);

    am_mdelay(10);
    
    /* ����transfer�ṹ�������д���ַ */
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_WR), 
                (uint8_t *)test_addr, 
                1);

    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_send (I2C_MASTER, p_trans);

    
   /* ����transfer�ṹ���������ȡ���� */
    for (i = 0; i < TEST_LEN; i++) {
        eeprom_buf[i] = 0;
    }
    i2c_mktrans(p_trans, 
                EEPROM_ADDR, 
                (I2C_M_7BIT | I2C_M_RD), 
                (uint8_t *)eeprom_buf, 
                TEST_LEN);

    i2c_mst_start(I2C_MASTER, p_trans);
    i2c_mst_recv(I2C_MASTER, p_trans);
    
    /* ������ǰ���� */
    amhw_i2c_mst_stop(I2C_MASTER);
    
    am_mdelay(10);
    
    /* У��д��Ͷ�ȡ�������Ƿ�һ�� */
    for (i = 0;i < TEST_LEN; i++) {
        AM_DBG_INFO("Read EEPROM the %2dth data is  : 0x%2X\r\n", i, eeprom_buf[i]);
        
        /* У��ʧ�� */
        if(eeprom_buf[i] != (i + 0xA)) {
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

/** [src_hw_i2c_polling_eeprom] */

/* end of file */

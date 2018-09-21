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
 * \brief ��I2C�ж�ģʽ�µĴӻ���ʾ���̣�ͨ��HW��Ľӿ�ʵ��
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
 * \snippet demo_hw_i2c_slave_int.c src_hw_i2c_slave_int 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_hw_i2c_slave_int
 * \copydoc demo_hw_i2c_slave_int.c
 */
 
/** [src_hw_i2c_slave_int] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


#define I2C_SLAVE            AMHW_I2C0        /* I2C�ӻ�������ͨ����   */ 
#define OPERATE_ADDR         0x50             /* ���������ӻ���ַ����*/

volatile uint8_t  g_i2c_slvrxrdyflg  = 0;     /* I2C�ӻ�����׼��������ʶλ */
volatile uint8_t  g_i2c_slvtxrdyflg  = 0;     /* I2C�ӻ�����׼��������ʶλ */

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
    amhw_i2c_int_enable(p_hw_i2c, AMHW_I2C_INTENSET_SLVPEND);

    for (i = 0; i < nbytes; i++) {
        while (!g_i2c_slvtxrdyflg);
        g_i2c_slvtxrdyflg = 0;
        
        /* �ӻ�д������ */
        amhw_i2c_slvdat_write(p_hw_i2c, *p_txbuf++);
        
        amhw_i2c_slv_continue(p_hw_i2c); 
        amhw_i2c_int_enable(p_hw_i2c, AMHW_I2C_INTENSET_SLVPEND);
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
int i2c_slv_recv (amhw_i2c_t *p_hw_i2c,
                  uint8_t    *p_rxbuf,
                  uint32_t    nbytes)
{
    uint8_t i;
    
    amhw_i2c_int_enable(p_hw_i2c, AMHW_I2C_INTENSET_SLVPEND);
    
    for (i = 0; i < nbytes; i++) {
        
        while (!g_i2c_slvrxrdyflg);
        g_i2c_slvrxrdyflg = 0;
        
        /* �ӻ��������� */
        *p_rxbuf++ = amhw_i2c_slvdat_read(p_hw_i2c);
        
        amhw_i2c_slv_continue(p_hw_i2c);
        amhw_i2c_int_enable(p_hw_i2c, AMHW_I2C_INTENSET_SLVPEND);

    }
  
    return AM_OK;
}


/**
 * \brief I2C�ӻ�����״̬����
 *
 * \param[in] p_hw_i2c   : ָ��I2C�Ĵ������ָ��
 * \param[in] i2c_status : ��ǰI2C��������״̬����
 *
 * \return  ��
 */
void i2c_slv_errorstat (amhw_i2c_t *p_hw_i2c, uint32_t i2c_status)
{
    uint32_t slverr_stat = i2c_status;
    
    if(slverr_stat & AMHW_I2C_STAT_SLVNOTSTR) {       
        p_hw_i2c->intenclr = AMHW_I2C_STAT_SLVNOTSTR; 
                                                      
    } else if (slverr_stat & AMHW_I2C_STAT_SLVDESEL) {
        p_hw_i2c->stat = AMHW_I2C_STAT_SLVDESEL;      
    }
}

/**
 * \brief I2C�ӻ�״̬������
 *
 * \param[in] p_hw_i2c   : ָ��I2C�Ĵ������ָ��
 * \param[in] i2c_status : ��ǰI2C��������״̬����
 *
 * \return  ��
 */
void i2c_slv_sm_event (amhw_i2c_t *p_hw_i2c,uint32_t i2c_status)
{

    uint32_t i2c_slv_stat = (p_hw_i2c->stat) & AMHW_I2C_SLAVE_STATE_MASK;
    
    switch (i2c_slv_stat) {
        
    case AMHW_I2C_STAT_SLVADDR:                 
        amhw_i2c_slv_continue(p_hw_i2c);
        amhw_i2c_int_enable(p_hw_i2c, AMHW_I2C_INTENSET_SLVPEND); 
        break;
        
    case AMHW_I2C_STAT_SLVRX: 
        g_i2c_slvrxrdyflg = 1;
        break;
        
    case AMHW_I2C_STAT_SLVTX:
        g_i2c_slvtxrdyflg = 1;
        break;
    
    default:
        break;
    }
}

/**
 * \brief I2C�ӻ��жϷ�����
 * \param[in] p_arg : �жϺ�������ڲ���
 * \return   ��
 */
void i2c_slave_isr (void *p_arg)
{
    amhw_i2c_t *p_hw_i2c = (amhw_i2c_t *)p_arg;
    uint32_t i2c_status = p_hw_i2c->intstat;
    
    if (i2c_status == 0) {
        return;
    }
    
    i2c_slv_errorstat(p_hw_i2c, i2c_status);
   
    if (i2c_status & AMHW_I2C_STAT_SLVPEND) {
        p_hw_i2c->intenclr = AMHW_I2C_INTENCLR_SLVPEND;
        i2c_slv_sm_event(p_hw_i2c, i2c_status);
    }
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
    
    /* ʹ��slave����ж� */
    amhw_i2c_int_enable(I2C_SLAVE, AMHW_I2C_INTENSET_SLVPEND |
                                   AMHW_I2C_INTENSET_SLVNOTSTR |
                                   AMHW_I2C_INTENSET_SLVDESEL);
    
    am_int_connect(INUM_I2C0,  i2c_slave_isr, I2C_SLAVE);
    am_int_enable(INUM_I2C0);
    
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

/** [src_hw_i2c_slave_int] */

/* end of file */


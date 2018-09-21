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
 * \brief ��SPI�ж�ģʽ�²���SPI_FLASH��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ��������:
 *   1. ��SPI�ӿں�SPI_FLASH��Ӧ�Ľӿ�����������
 *   2. ���������ص�demo�壬�����ϵ���߸�λ��
 *
 * - ʵ������:
 *   1. ��SPI_FLASH�ж�ȡ�������ݣ�ͨ�����ڴ�ӡ������
 *   2. д�����ݺͶ�ȡ��������ͬ��SPI_FLASH��д���Գɹ���LED0��200ms�����˸��
 *
 * \note
 *   1. �ɼ������������£�ֱ��ʹ�� am_spi_write_then_read() �� am_spi_write_then_write() �������ɡ�
 *
 * \par Դ����
 * \snippet demo_std_spi_flash_int.c src_std_spi_flash_int
 *
 * \internal
 * \par History
 * - 1.00 14-12-04  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_std_spi_flash_int
 * \copydoc demo_std_spi_flash_int.c
 */
 
/** [src_std_spi_flash_int] */
#include "ametal.h"
#include "am_board.h"
#include "am_prj_config.h"


/**
 * \brief SPI flash defines
 */
#define WREN            0x06                       /**< \brief SPI_FLASH дʹ������   */
#define WRDI            0x04                       /**< \brief SPI_FLASH ��ȡID����   */
#define RDSR            0x05                       /**< \brief SPI_FLASH ��ȡ״̬���� */
#define WRSR            0x01                       /**< \brief SPI_FLASH д״̬����   */
#define READ            0x03                       /**< \brief SPI_FLASH ����������   */
#define WRITE           0x02                       /**< \brief SPI_FLASH д��������   */
#define SE              0x20                       /**< \brief SPI_FLASH ������������ */
#define CHIP_ERASE      0x60                       /**< \brief SPI_FLASH ��Ƭ�������� */

#define FLASH_PAGE_SIZE    256                     /**< \brief SPI_FLASH ҳ��С����   */

#define TEST_ADDR          0x0900                  /**< \brief SPI_FLASH ����ҳ��ַ   */
#define TEST_LEN           FLASH_PAGE_SIZE         /**< \brief �����ֽڳ���           */

uint8_t g_tx_buf[TEST_LEN]={0x9F};                /**< \brief SPI_FLASH д���ݻ��� */
uint8_t g_rx_buf[TEST_LEN]={0};                   /**< \brief SPI_FLASH �����ݻ��� */

volatile bool_t g_trans_flag;                               /**< \brief SPI �����־ */

/**
 * \brief SPI������ɻص�����
 */
void spi_transfer_complete(void *p_arg,int status)
{
    if(status == AM_OK) {
        g_trans_flag = TRUE;
    } else {
        AM_DBG_INFO("SPI transfer error, status is %d", status);
    }
}

/**
 * \brief �ж�SPI_FLASH �Ƿ���æ״̬
 * \param[in] spi_handle : SPI��׼����������
 * \retval TURE  : æ״̬
 * \retval FALSE : ����״̬
 */
bool_t flash_isbusy_chk (am_spi_handle_t spi_handle) 
{
    uint8_t           cmd_data = RDSR;
    uint8_t           status_data;

    am_spi_write_then_read(spi_handle,
                           &cmd_data,
                           1,
                           &status_data,
                           1);

    return (status_data & 0x01) ? TRUE : FALSE;
}

/* FLASH дʹ�� */
void flash_wren (am_spi_handle_t spi_handle) 
{
    am_spi_transfer_t trans;
    
    uint8_t  tx_cmd = WREN;       /* ���͵�ָ�� */
 
    /* ����transfer������ ����дʹ������ */ 
    am_spi_mktrans( &trans, 
                    &tx_cmd,
                    NULL,
                    1,
                    AM_SPI_TRANS_EOT,
                    spi_transfer_complete,
                    NULL);
                   
    am_spi_transfer(spi_handle, &trans);
    while (!g_trans_flag);
    g_trans_flag = FALSE;
}


/**
 * \brief SPI_FLASH��������
 *
 * \param[in] spi_handle : SPI��׼����������
 * \param[in] addr       : SPI_FLASH������ҳ��ַ
 *
 * \return  ��
 */
void spi_flash_erase (am_spi_handle_t spi_handle, 
                      uint32_t        addr)
{
    am_spi_transfer_t trans;
    
    uint8_t  tx_cmd[4];  /* ���͵�ָ�� */
    uint8_t  cmd_len;    /* ָ���   */

    flash_wren(spi_handle);

    tx_cmd[0] = SE;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;
    
    cmd_len   = 4;
    
    /* ����transfer������ ���Ͳ��������Լ�������ַ */
    am_spi_mktrans(&trans, 
                   tx_cmd, 
                   NULL, 
                   cmd_len, 
                   AM_SPI_TRANS_EOT,
                   spi_transfer_complete,
                   (void *)(spi_handle));
                   
    am_spi_transfer(spi_handle, &trans);
    while (!g_trans_flag);
    g_trans_flag = FALSE;
                   
    /* �ȴ�SPI_FLASH���ڿ���״̬ */
    while (flash_isbusy_chk(spi_handle) == TRUE) {
        am_mdelay(1);
    }
}

/**
 * \brief SPI_FLASH д����
 *
 * \param[in] spi_handle : SPI��׼����������
 * \param[in] addr       : Ҫд�����ݵĵ�ַ
 * \param[in] length     : ���ݻ���ĳ���
 *
 * \return  ��
 */
 void spi_flash_write (am_spi_handle_t spi_handle, 
                         uint32_t        addr, 
                         uint32_t        length)
{
    uint8_t  tx_cmd[4];       /* ���͵�ָ�� */

    flash_wren(spi_handle);

    /* д��дָ���24λ��ַ */
    tx_cmd[0] = WRITE;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;
 
    am_spi_write_then_write(spi_handle,
                            tx_cmd,
                            4,
                            g_tx_buf,
                            length);

    /* �ȴ�SPI_FLASH���ڿ���״̬ */
    while (flash_isbusy_chk(spi_handle) == TRUE);
}

/**
 * \brief SPI_FLASH������
 *
 * \param[in] spi_handle : SPI��׼����������
 * \param[in] addr       : Ҫ��ȡ���ݵĵ�ַ
 * \param[in] length     : ���ݻ���ĳ���
 *
 * \return  ��
 */
void spi_flash_read (am_spi_handle_t spi_handle, 
                     uint32_t        addr, 
                     uint32_t        length)
{
    uint8_t  tx_cmd[4];       /* ���͵�ָ�� */

    /* д���ָ���24λ��ַ */
    tx_cmd[0] = READ;
    tx_cmd[1] = addr >> 16;
    tx_cmd[2] = addr >>  8;
    tx_cmd[3] = addr;
    
    am_spi_write_then_read(spi_handle,
                           tx_cmd,
                           4,
                           g_rx_buf,
                           length);
 
    /* �ȴ�SPI_FLASH���ڿ���״̬ */
    while (flash_isbusy_chk(spi_handle) == TRUE);
}

/**
 * \brief SPI_FLASH������
 *
 * \param[in] spi_handle : SPI��׼����������
 * \param[in] addr       : Ҫ��ȡ���ݵĵ�ַ
 * \param[in] length     : ���ݻ���ĳ���
 *
 * \return  ��
 */
void flash_id_chk (am_spi_handle_t spi_handle)
{

    uint8_t  tx_cmd = 0x9F;       /* ���͵�ָ�� */
    uint8_t  rd_id[3];
    
    am_spi_write_then_read(spi_handle,
                           &tx_cmd,
                           1,
                           rd_id,
                           3);
 
    /* �ȴ�SPI_FLASH���ڿ���״̬ */
    while (flash_isbusy_chk(spi_handle) == TRUE);
    
    
    am_kprintf("The ID is %x, %x ,%x\r\n",rd_id[0], rd_id[1], rd_id[2]);
}

/**
 * \brief SPI_FLASH����demo
 *         1. ������Ҫ������ַ�е����ݣ� 
 *         2. д�����ݵ��趨�ĵ�ַ�� 
 *         3. �Ӹõ�ַ�ж�ȡ���ݣ� 
 *         4. ����У�顣
 *
 * \param[in] spi_handle : SPI��׼����������
 * \param[in] addr       : ��Ҫ������SPI_FLASHҳ��ַ
 * \param[in] length     : ���ݳ���
 *
 * \return  ��
 */
void spi_flash_test_demo (am_spi_handle_t spi_handle, 
                          uint32_t        addr, 
                          uint32_t        length) 
{
    uint32_t           i;
    am_spi_cfg_info_t  cfg_info;
    
    /**
     * ����Ƭѡ����ΪPIO0_14������SSEL���ܣ�������ʵ��SPIӲ���Զ����ƣ�������
     * ֻ��Ҫ������������ΪSPI0��SSEL���ܼ��ɡ�
     * �������SPI��SSEL���ܣ�������ֶ����ƣ�����gpio��׼�ӿڡ�
     */
    am_gpio_pin_cfg(PIO0_14, PIO0_14_SPI0_SSELN0 | PIO0_14_PULLUP);

    /* �趨���ò��� */
    cfg_info.speed       = 2000000;             /* SPI��������Ϊ4MHz  */
    cfg_info.cfg_flags   = AM_SPI_CFG_MODE_0;   /* ʹ��SPIģʽ0       */
    cfg_info.bpw         = 8;                   /* λ��Ϊ8λ          */
    
    /* ����SPI������ */
    am_spi_config(spi_handle, &cfg_info);
    
    /* ���оƬID */
    flash_id_chk(spi_handle);
    
    /* ������ǰ��ַ������ */
    spi_flash_erase(spi_handle, addr);
 
    am_kprintf("FLASH�������\r\n");
    
    for (i = 0; i < length; i++) {
        g_tx_buf[i] = i + 7;
    }
    
    /* д�����ݵ��趨SPI_FLASH��ַ */
    spi_flash_write(spi_handle, addr, length);
    am_mdelay(10);

    am_kprintf("FLASH����д�����\r\n");
    
    for (i = 0; i < length; i++) {
        g_rx_buf[i] = 0;
    }
    
    /* ���趨��SPI_FLASH��ַ�ж�ȡ���� */
    spi_flash_read(spi_handle, addr, length);
    am_mdelay(10);
 
    /* ����У�� */
    for (i = 0; i < length; i++) {
        
        /* ����ȡ��������ͨ�����ڴ�ӡ���� */
        AM_DBG_INFO(" read %2dst data is : 0x%2x \r\n", i, g_rx_buf[i]);
        if(g_rx_buf[i] != ((7 + i) & 0xFF)) {
            AM_DBG_INFO("verify failed!\r\n");
            while(1);
        }
    }
}
/**
 * \brief ������
 */
int main (void)
{
    am_spi_handle_t     spi_handle;
    
    /* �弶��ʼ�� */
    am_board_init();

    /* SPI0 ƽ̨��س�ʼ�� */
    amhw_plfm_spi0_init();

    /* SPI��ʼ������ */
    spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);

    /* SPI�жϺ������� */
    am_spi_connect(spi_handle);

    spi_flash_test_demo(spi_handle, TEST_ADDR, TEST_LEN);
    
    /* SPI_FLASH��д����У��ɹ���LED0 ��200msʱ������˸ */
    while (1) {
        am_led_on(LED0);
        am_mdelay(200);
        am_led_off(LED0);
        am_mdelay(200);
    }
}

/** [src_std_spi_flash_int] */

/* end of file */

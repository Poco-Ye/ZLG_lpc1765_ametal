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
 * \brief APL_StartKit SPI FLASH��ʾ����
 *
 * - ��������:
 *   1. ��APL_StartKit���ӵ�EasyARM-54000M4 demo�壻
 *   2. ������ñ����SPI�ӿ�(MISO��MOSI��SCK��CS)��ʹSPI_FLASH���ӵ�SPI0��
 *   3. ��APL_StartKit����ϴ���0�ӿڣ�J3�����ӵ�PC���ϡ�
 *
 * - ʵ������:
 *   1. ��SPI_FLASH�ж�ȡ�������ݣ�ͨ�����ڴ�ӡ������
 *   2. д�����ݺͶ�ȡ��������ͬ��SPI_FLASH��д���Գɹ���LED_RUN(��)��200ms�����˸,
 *      ��֮��RUN_LED(��)����
 *
 * \par Դ����
 * \snippet demo_apl_startkit_spiflash.c src_apl_startkit_spiflash
 *
 * \internal
 * \par History
 * - 1.00 15-03-19  jon, first implementation.
 * \endinternal
 */
 
/**
 * \addtogroup demo_if_apl_startkit_spiflash
 * \copydoc demo_apl_startkit_spiflash.c
 */
 
/** [src_apl_startkit_spiflash] */
#include "ametal.h"
#include "am_board.h"
#include "am_spi_flash.h"
#include "am_prj_config.h"




#define TEST_ADDR          0x0900                  /**< \brief SPI_FLASH ����ҳ��ַ   */
#define TEST_LEN           256                     /**< \brief �����ֽڳ���           */

uint8_t g_tx_buf[TEST_LEN]={0};                    /**< \brief SPI_FLASH д���ݻ��� */
uint8_t g_rx_buf[TEST_LEN]={0};                    /**< \brief SPI_FLASH �����ݻ��� */


bool_t g_verify_flag = TRUE;                       /**< \brief У��ɹ�����־��
                                                               TRUE-У��ɹ� 
                                                               FALSE-У��ʧ�� */

/* APL_StartKit definitions */
#define  RUN_LED        PIO1_5
#define  ERR_LED        PIO0_9


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
void spi_flash_test (am_spi_handle_t spi_handle, 
                     uint32_t        addr, 
                     uint32_t        length) 
{
    uint32_t i;

    /* ������ǰ��ַ������ */
    am_spi_flash_erase(spi_handle, addr);

    for (i = 0; i < length; i++) {
        g_tx_buf[i] = i ;
    }
    
    /* д�����ݵ��趨SPI_FLASH��ַ */
    am_spi_flash_write(spi_handle, addr, (uint8_t *)g_tx_buf, length);
    am_mdelay(10);

    for (i = 0; i < length; i++) {
        g_tx_buf[i] = 0;
    }
    
    /* ���趨��SPI_FLASH��ַ�ж�ȡ���� */
    am_spi_flash_read(spi_handle, addr, (uint8_t *)g_tx_buf,length);
    am_mdelay(10);
    
    /* ����У�� */
    for (i = 0; i < length; i++) {
        
        /* ����ȡ��������ͨ�����ڴ�ӡ���� */
        AM_DBG_INFO(" read FLASH %2dst data is : 0x%2x \r\n", i, g_tx_buf[i]);
        if(g_tx_buf[i] != (i & 0xFF)) {
            g_verify_flag = FALSE;
            AM_DBG_INFO("verify failed!\r\n");
        }
    }
}

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
    am_spi_handle_t     spi_handle;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* APL_StartKit ���LED IO ��ʼ�� */
    apl_startkit_init();
   
    /* SPI0 ƽ̨��س�ʼ�� */
    amhw_plfm_spi0_init();

    /* SPI��ʼ������ */
    spi_handle = amdr_spi_init(&g_spi0_dev, &g_spi0_devinfo);

    /* SPI�жϺ������� */
    am_spi_connect(spi_handle);

    spi_flash_test(spi_handle, TEST_ADDR, TEST_LEN);
    
    /* SPI_FLASH��д����У��ɹ���LED0 ��200msʱ������˸ */
    while (1) {
        /* У��ɹ���RUN_LED(�̵�)��200msʱ������˸ */
        if(g_verify_flag) {        
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

/** [src_apl_startkit_spiflash] */

/* end of file */

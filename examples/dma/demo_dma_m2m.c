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
 * \brief  �ڴ浽�ڴ��DMA�������̣�ͨ��������Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. ���DMA����ɹ���LEDһֱ����
 *   2. ���DMA����ʧ�ܣ�LED��˸��
 *
 * \par Դ����
 * \snippet demo_dma_m2m.c src_dma_m2m
 *
 * \internal
 * \par Modification History
 * - 1.10 14-12-09  hbt, add.
 * - 1.00 14-12-04  zen, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dma_m2m
 * \copydoc demo_dma_m2m.c
 */

/** [src_dma_m2m] */
#include "ametal.h"
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"

uint8_t g_buf_src[512];          /**< \brief Դ�����ݻ�����   */
uint8_t g_buf_dst[512];          /**< \brief Ŀ������ݻ����� */

bool_t  g_trans_done;            /**< \brief ������ɱ�־     */

/**
 * \brief ��ƹ�Ҵ���ʱ���������ĵ�ַ��Ҫ��16�ֽڶ��롣
 */
amhw_dma_xfer_desc_t g_desc;


/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� amdr_dma_isr_connect() �������ݡ�
 * \param[in] p_flg : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AMDR_DMA_INTA)��(#AMDR_DMA_INTB) �� (#AMDR_DMA_INTERR)��
 *
 * \return    �ޡ�
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;

    if (flag == AMDR_DMA_INTA) {

        /* DMA������� */
        g_trans_done = TRUE;

    } else if (flag == AMDR_DMA_INTERR) {
        // �û��Զ���ִ�д���
    }
}

/**
 * \brief DMA���䣺�ڴ浽�ڴ档
 */
void dma_m2m_test (void)
{
    int      i;
    uint32_t flags;

    /* DMAͨ������ */
    amdr_dma_chan_setup(DMA_CHAN_0,                     /* DMAͨ����                    */
                        AMHW_DMA_CHAN_PERIPH_REQ_OFF |  /* �������败��                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF     |  /* ��ֹӲ������                 */
                        AMHW_DMA_CHAN_SINGLE_TRANS   |  /* ���δ���ģʽ                 */
                        AMHW_DMA_CHAN_PRIO_5);          /* ͨ�����ȼ���5��0���ȼ���ߣ� */

    for (i = 0; i < 512; i++) {
        g_buf_src[i] = i;
        g_buf_dst[i] = 0;
    }

    /* ��ʼDMA���� */
    amdr_dma_chan_start(DMA_CHAN_0);

    /* ����DMA�жϷ����� */
    amdr_dma_isr_connect(DMA_CHAN_0, dma_isr, (void *)0);

    /* DMA�������� */
    flags = AMHW_DMA_XFER_CFG_VALID       |           /* ��ǰͨ����������Ч              */
            AMHW_DMA_XFER_NO_RELOAD       |           /* ��ֹ����ͨ��������              */
            AMHW_DMA_XFER_SWTRIG          |           /* �������                        */
            AMHW_DMA_XFER_NO_CLRTRIG      |           /* �����������־                  */
            AMHW_DMA_XFER_WIDTH_8BIT      |           /* �������ݿ�ȣ�8 bit             */
            AMHW_DMA_XFER_SRCINC_1X_WIDTH |           /* Դ�����ݵ�ַ��1�����ݿ�ȵ���   */
            AMHW_DMA_XFER_DSTINC_1X_WIDTH |           /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
            AMHW_DMA_XFER_SETINTA;                    /* ʹ���ж� A                      */

    /* ����ͨ�������� */
    amdr_dma_xfer_desc_build(&g_desc,                 /* ͨ��������       */
                            (uint32_t)g_buf_src,      /* Դ�����ݻ�����   */
                            (uint32_t)g_buf_dst,      /* Ŀ������ݻ����� */
                             512,                     /* �����ֽ���       */
                             flags);                  /* ��������         */

    /* ����DMA���䣬���Ͽ�ʼ���� */
    amdr_dma_chan_xfer_startup(DMA_CHAN_0, &g_desc);

    am_mdelay(1);
    while(g_trans_done == FALSE);                   /* �ȴ��������  */

    amdr_dma_chan_stop(DMA_CHAN_0);                 /* ֹͣͨ������  */

    for (i = 0; i < 512; i++) {
        if (g_buf_src[i] != g_buf_dst[i]) {
            while (1) {                             /* ����ʧ��      */
                am_led_on(LED0);
                am_mdelay(200);
                am_led_off(LED0);
                am_mdelay(200);
            }
        }
    }

    am_led_on(LED0);
}


/**
 * \brief ���������
 */
int main (void)
{
    /* �弶��ʼ�� */
    am_board_init();

    /* ƽ̨��ʼ�� */
    amhw_plfm_dma_init();

    /* DMA��ʼ�� */
    amdr_dma_init(&g_dma_dev, &g_dma_devinfo);

    am_led_off(LED0);

    dma_m2m_test();

    while (1) {
        ;
    }
}

/** [src_dma_m2m] */

/* end of file */

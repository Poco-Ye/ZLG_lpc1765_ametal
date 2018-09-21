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
 * \brief  DMAƹ�Ҵ������̣�ͨ��������Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. ���DMA����ɹ���LEDһֱ����
 *   2. ���DMA����ʧ�ܣ�LED��˸��
 *
 * \par Դ����
 * \snippet demo_dma_ping_pong.c src_dma_ping_pong
 *
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  hbt, first implementation.
 * \endinternal
 */

/**
 * \addtogroup demo_if_dma_ping_pong
 * \copydoc demo_dma_ping_pong.c
 */

/** [src_dma_ping_pong] */
#include "ametal.h"
#include "am_board.h"
#include "am_debug.h"
#include "am_delay.h"
#include "am_prj_config.h"


/** \brief ������������ʹ��ƹ�Ҵ���ʱ��������������16�ֽڶ��� */
__align(16) amhw_dma_xfer_desc_t g_desc[2];

uint8_t g_buf_src[16];           /**< \brief Դ�����ݻ�����    */
uint8_t g_buf_dsta[16];          /**< \brief Ŀ���A���ݻ����� */
uint8_t g_buf_dstb[16];          /**< \brief Ŀ���B���ݻ����� */

bool_t  g_trans_a_done;          /**< \brief ������ɱ�־      */  
bool_t  g_trans_b_done;          /**< \brief ������ɱ�־      */
bool_t  g_trans_err;             /**< \brief ��������־      */


/**
 * \brief DMA�жϷ������
 *
 * \param[in] p_arg : �û��Զ��������ͨ�� amdr_dma_isr_connect() �������ݡ�
 * \param[in] p_flg : DMA�жϱ�־���ɵײ��������룬�ò����Ŀ���ȡֵ��
 *                    (#AMDR_DMA_INTA)��(#AMDR_DMA_INTB) �� (#AMDR_DMA_INTERR)��
 *
 * \return    �ޡ�               
 *
 * \note �жϷ������еĴ��뾡���٣�����Ƶ�����жϣ�
 */
void dma_isr (void *p_arg, void *p_flg)
{
    int flag = (int)p_flg;

    g_trans_err = FALSE;

    if (flag == AMDR_DMA_INTA) {
        g_trans_a_done = TRUE;
    } else if (flag == AMDR_DMA_INTB) {
        g_trans_b_done = TRUE;
    } else if (flag == AMDR_DMA_INTERR) {
        g_trans_err = TRUE;
    }
}

/**
 * \brief DMA���䣺ƹ��ģʽ��
 */
void dma_ping_pong_test (void)
{
    int      i;
    uint32_t flags1, flags2;

    /* DMAͨ������ */
    amdr_dma_chan_setup(DMA_CHAN_0,                     /* DMAͨ����                    */
                        AMHW_DMA_CHAN_PERIPH_REQ_OFF |  /* �������败��                 */
                        AMHW_DMA_CHAN_HWTRIG_OFF |      /* ��ֹӲ������                 */
                        AMHW_DMA_CHAN_PRIO_6);          /* ͨ�����ȼ���6��0���ȼ���ߣ� */

    /* ��ʼDMA���� */
    amdr_dma_chan_start(DMA_CHAN_0);

    for (i = 0; i < 16; i++) {
        g_buf_src[i] = i;
        g_buf_dsta[i] = 0;
        g_buf_dstb[i] = 0;
    }

    /* DMA�������� */
    flags1 = AMHW_DMA_XFER_CFG_VALID |                  /* ��ǰͨ����������Ч              */
             AMHW_DMA_XFER_RELOAD |                     /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                     /* �������                        */
             AMHW_DMA_XFER_NO_CLRTRIG |                 /* �����������־                  */
             AMHW_DMA_XFER_WIDTH_8BIT |                 /* �������ݿ�ȣ�8 bit             */
             AMHW_DMA_XFER_SRCINC_1X_WIDTH |            /* Դ�����ݵ�ַ��1�����ݿ�ȵ���   */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTA;                     /* ʹ���ж� A                      */

    /* DMA�������� */
    flags2 = AMHW_DMA_XFER_CFG_VALID |                  /* ��ǰͨ����������Ч              */
             AMHW_DMA_XFER_RELOAD |                     /* �����������ͨ��������          */
             AMHW_DMA_XFER_SWTRIG |                     /* �������                        */
             AMHW_DMA_XFER_CLRTRIG |                    /* ��������־                      */
             AMHW_DMA_XFER_WIDTH_8BIT |                 /* �������ݿ�ȣ�8 bit             */
             AMHW_DMA_XFER_SRCINC_1X_WIDTH |            /* Դ�����ݵ�ַ��1�����ݿ�ȵ���   */
             AMHW_DMA_XFER_DSTINC_1X_WIDTH |            /* Ŀ������ݵ�ַ��1�����ݿ�ȵ��� */
             AMHW_DMA_XFER_SETINTB;                     /* ʹ���ж� B                      */

    /* ����ͨ��������A */
    amdr_dma_xfer_desc_build(&g_desc[0],                /* A������������       */
                             (uint32_t)g_buf_src,       /* Դ�����ݻ�����      */
                             (uint32_t)g_buf_dsta,      /* A��Ŀ��˻�������ַ */
                             16,                        /* �����ֽ���          */
                             flags1);                   /* ��������            */

    /* ����ͨ��������B */
    amdr_dma_xfer_desc_build(&g_desc[1],                /* B������������       */
                             (uint32_t)g_buf_src,       /* Դ�����ݻ�����      */
                             (uint32_t)g_buf_dstb,      /* B��Ŀ��˻�������ַ */
                             16,                        /* �����ֽ���          */
                             flags2);                   /* ��������            */

    /* ����DMA�жϷ����� */
    amdr_dma_isr_connect(DMA_CHAN_0, dma_isr, (void *)0);

    /* �������������� */
    amdr_dma_xfer_desc_link(&g_desc[1], &g_desc[0]);
    amdr_dma_xfer_desc_link(&g_desc[0], &g_desc[1]);

    /* ����DMA���䣬���Ͽ�ʼ���� */
    amdr_dma_chan_xfer_startup(DMA_CHAN_0, &g_desc[0]);

    am_mdelay(1);
    while ((g_trans_a_done == FALSE) || (g_trans_b_done == FALSE)); /* �ȴ��������  */

    amdr_dma_chan_stop(DMA_CHAN_0);                                 /* ֹͣͨ������  */

    /* ��ʵ�������� */
    for (i = 0; i < 16; i++) {
        if (g_buf_src[i] != g_buf_dsta[i]) {
            g_trans_err = TRUE;
            break;
        }
    }
    for (i = 0; i < 16; i++) {
        if (g_buf_src[i] != g_buf_dstb[i]) {
            g_trans_err = TRUE;
            break;
        }
    }

    if (g_trans_err == TRUE) {
        while (1) {
            am_led_on(LED0);
            am_mdelay(200);
            am_led_off(LED0);
            am_mdelay(200);
        }
    } else {
        am_led_on(LED0);
    }
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

    dma_ping_pong_test();

    while (1) {
        ;
    }
}

/** [src_dma_ping_pong] */

/* end of file */

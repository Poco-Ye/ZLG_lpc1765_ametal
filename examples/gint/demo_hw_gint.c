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
 * \brief ���ж�(GINT)���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ��������
 *    1. PIO0_13��������������1�� 
 *    2. PIO0_14��������������2�� 
 *    3. PIO1_9��������������3�� 
 *    4. PIO1_10��������������4��
 *
 * - ʵ������
 *    1. ���°���1�򰴼�2ʱ��LED��ת��
 *    2. ͬʱ���°���3�Ͱ���4��LED��˸5�Ρ�
 *
 * \warning ֻ��Cortex-M4�ں˲���ʹ��GINT1
 *
 * \par Դ����
 * \snippet demo_hw_gint.c src_hw_gint 
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-01-22  hbt, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_gint
 * \copydoc demo_hw_gint.c
 */
 
/** [src_hw_gint] */
#include "ametal.h" 
#include "am_board.h"



/** \brief �жϱ�־ */
bool_t g_gint0_flag;

#if AM_CORTEX_M4 
bool_t g_gint1_flag;
#endif

/**
 * \brief ���ж����á�
 */
void gint_config (void)
{
    /* Group0: GPIO�������� */
    am_gpio_pin_cfg(PIO0_13, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO0_14, AM_GPIO_INPUT);

#if AM_CORTEX_M4
    
    /* Group1: GPIO�������� */
    am_gpio_pin_cfg(PIO1_9, AM_GPIO_INPUT);
    am_gpio_pin_cfg(PIO1_10, AM_GPIO_INPUT); 
#endif
    
    /* �������жϹ��� */
    amhw_gint_ctrl_set(AMHW_GINT, AMHW_GROUP_0, AMHW_GINT_CTRL_COMB_OR | 
                                                AMHW_GINT_CTRL_TRIG_EDGE); 

#if AM_CORTEX_M4 
    amhw_gint_ctrl_set(AMHW_GINT, AMHW_GROUP_1, AMHW_GINT_CTRL_COMB_AND |
                                                AMHW_GINT_CTRL_TRIG_LEVEL);    
#endif

    /* Group0: ѡ�����ŵ�ָ�����жϵĵ͵�ƽ���� */
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_0, PIO0_13);
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_0, PIO0_14);

#if AM_CORTEX_M4 

    /* Group1: ѡ�����ŵ�ָ�����жϵĵ͵�ƽ���� */
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_1, PIO1_9);
    amhw_gint_low_level_sel(AMHW_GINT, AMHW_GROUP_1, PIO1_10);     
#endif
    
    /* ʹ�����ж�0�������ж� */
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_0, PIO0_13);    
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_0, PIO0_14);

#if AM_CORTEX_M4 

    /* ʹ�����ж�1�������ж� */
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_1, PIO1_9);
    amhw_gint_enabled(AMHW_GINT, AMHW_GROUP_1, PIO1_10);     
#endif
}

/** 
 * \brief ƽ̨��ʼ��
 */
void plfm_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_GINT);
    amhw_syscon_periph_reset(AMHW_RESET_GINT);
}

/** 
 * \brief ���ж�0������
 */
void gint0_isr (void *p_arg)
{
    amhw_gint_status_clr(AMHW_GINT, AMHW_GROUP_0);
    
    g_gint0_flag = TRUE;
}

#if AM_CORTEX_M4 
/** 
 * \brief ���ж�1������
 */
void gint1_isr (void *p_arg)
{
    amhw_gint_status_clr(AMHW_GINT, AMHW_GROUP_1);
    
    g_gint1_flag = TRUE;
}
#endif

/**
 * \brief ���������
 */
int main (void)
{
    int i;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ƽ̨��ʼ�� */
    plfm_init();
    
    /* ���ж����� */
    gint_config();
    
    /* �����жϷ����� */
    am_int_connect(INUM_GINT0, gint0_isr, (void *)0); 
    
#if AM_CORTEX_M4 
    am_int_connect(INUM_GINT1, gint1_isr, (void *)0);   
#endif
    
    /* ʹ���ж� */
    am_int_enable(INUM_GINT0);
    
#if AM_CORTEX_M4 
    am_int_enable(INUM_GINT1);      
#endif
    
    while (1) {
        
        /* ���ж�0�����жϣ�LED��ת */
        if (g_gint0_flag == TRUE) {
            g_gint0_flag = FALSE;
            am_led_toggle(0);
        }

#if AM_CORTEX_M4 

         /* ���ж�1�����жϣ���˸5�� */
        if (g_gint1_flag == TRUE) {
            g_gint1_flag = FALSE;
            for (i = 0; i < 5; i++) {
                am_led_toggle(0);
                am_mdelay(200);
            }
        }
#endif
    }
}

/** [src_hw_gint] */

/* end of file */

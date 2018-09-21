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
 * \brief �ظ��ж϶�ʱ��(RIT)���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������
 *   1. LED��10Hz��Ƶ����˸��
 * 
 * \par Դ����
 * \snippet demo_hw_rit.c src_hw_rit 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_hw_rit
 * \copydoc demo_hw_rit.c
 */

/** [src_hw_rit] */
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief �ظ��ж϶�ʱ���жϷ�����
 * \param[in]  p_arg : �û��Զ��������ͨ�� am_int_connect() �������ݡ�
 * \return ��
 */
void rit_irq_handler (void *p_arg)
{
    if (amhw_rit_int_flag_check(AMHW_RIT) == TRUE) {
        
        am_led_toggle(LED0);
        
        amhw_rit_int_flag_clr(AMHW_RIT);
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
    amhw_plfm_rit_init();
    
    amhw_rit_count_set(AMHW_RIT, 0);     /* ���ü�����Ϊ 0  */
    
    /* ���ñȽ�ֵ�Բ���10Hz���ж� */
    amhw_rit_compval_set(AMHW_RIT, (uint64_t)(g_main_clkfreq / 10)); 
    
    am_int_connect(INUM_RIT, rit_irq_handler, (void *)0);
    
    /* ʹ��RIT�ж� */
    am_int_enable(INUM_RIT);
   
    amhw_rit_clear_enable(AMHW_RIT);  /* ���ƥ������� */
    
    amhw_rit_enable(AMHW_RIT);
         
    while (1) {
 
        __WFI();
    }
}

/** [src_hw_rit] */

/* end of file */

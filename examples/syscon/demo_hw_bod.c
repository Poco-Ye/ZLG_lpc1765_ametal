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
 * \brief ��������ʾ���̣�ͨ��HW��Ľӿ�ʵ��
 *
 * - ʵ������:
 *   1. ���ⲿ��������ĸ�λ��������� "Reset by External Reset Pin"�� 
 *   2. ������������ĸ�λ��������� "Reset by BOD"��
 *   3. �������ѹ����3.05V���������жϡ�
 *
 * \par Դ����
 * \snippet demo_hw_bod.c src_hw_bod
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_hw_bod
 * \copydoc demo_hw_bod.c
 */
 
/** [src_hw_bod] */
#include "ametal.h"
#include "am_board.h"



/** 
 * \brief BOD �жϴ�����
 * \param[in] p_arg : �ж���ڲ���
 * \return  None
 */
void bod_irq_handler (void *p_arg)
{
    AM_DBG_INFO("The BOD hanppen\r\n");
}

/**
 * \brief ������
 */
int main (void)
{
    /* �༶��ʼ�� */
    am_board_init();

    /* 
     * ������������λ�����������ʾ�ַ���LED0�� 
     */
    if ((amhw_syscon_rst_stat_get() & AMHW_SYSCON_RSTSTAT_BOD) != 0) {
        amhw_syscon_rst_stat_clr(AMHW_SYSCON_RSTSTAT_BOD);
        
        AM_DBG_INFO("Reset by BOD\r\n");
        am_led_on(LED0);
        
    } else if ((amhw_syscon_rst_stat_get() & AMHW_SYSCON_RSTSTAT_EXTRST) != 0) {
        
        AM_DBG_INFO("Reset by External Reset Pin \r\n");
    }

    amhw_syscon_powerup(AMHW_SYSCON_PD_BOD_RST | AMHW_SYSCON_PD_BOD_INTR);
 
    /* �趨�������жϵ�ѹ3.05V���豸��λ��ѹ1.5V�� */
    amhw_pmu_bod_level_set(AMHW_PMU_BODRSTLVL_1_50V, AMHW_PMU_BODINTLVL_3_05V);
    
    amhw_pmu_bod_rst_enable();
    amhw_pmu_bod_int_enable();
    
    am_int_connect(INUM_BOD, bod_irq_handler, (void *)LED0);
    am_int_enable(INUM_BOD);

    while (1) {
        __WFI();
    }

}

/** [src_hw_bod] */

/* end of file */

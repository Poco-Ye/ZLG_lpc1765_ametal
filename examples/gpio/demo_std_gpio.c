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
 * \brief GPIO���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������
 *   1. ���0.5s��LED��˸5�Σ�
 *   2. ֮��LED��0.2s�ļ��һֱ��˸��
 * 
 * \par Դ����
 * \snippet demo_std_gpio.c src_std_gpio 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-08  hbt, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_gpio
 * \copydoc demo_std_gpio.c
 */
 
/** [src_std_gpio] */
#include "ametal.h"  
#include "am_board.h"
#include "am_delay.h"
#include "am_prj_config.h"

/**
 * \brief ���������
 */
int main (void)
{
    uint8_t i;
    
    /* �弶��ʼ�� */
    am_board_init();
    
    /* ����GPIO���Ź��� */
    am_gpio_pin_cfg(PIO1_16, AM_GPIO_OUTPUT);
    
    /* ���0.5s��LED��˸5�� */
    for (i = 0; i < 5; i++) {
        am_gpio_set(PIO1_16, 0); 
        am_mdelay(500);
        
        am_gpio_set(PIO1_16, 1); 
        am_mdelay(500);
    }
    
    while (1) {
        
        /* LED��0.2s�ļ��һֱ��˸ */
        am_gpio_toggle(PIO1_16);
        am_mdelay(200);
    }
}

/** [src_std_gpio] */

/* end of file */

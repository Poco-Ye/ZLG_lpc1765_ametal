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
 * \brief The M4 core template for dualcore
 *
 * \internal
 * \par History
 * - 1.00 14-12-11  tee, first implementation.
 * \endinternal
 */ 

#include "ametal.h"
#include "am_board.h"

/** 
 * \brief Cortex-M0+ and Cortex-M4 memory configure
 *
 * This header file for amhw_cpu_boot_m0p() to start up the m0+ core in here
 */
#include "..\shared\lpc5410x_config_memory.h"

/**
 * \brief  Application Main entry point
 */
int main (void)
{   
    /* The board initialization  */
    am_board_init();
    
    /* Start up the cortex M0+ */
    amhw_cpu_boot_m0p(LPC5410X_CFG_MEM_FLASH_CM0_START);

    while (1) {
        am_led_on(LED0);
        am_mdelay(100);
        am_led_off(LED0);
        am_mdelay(100);
    }
}

/* end of file */

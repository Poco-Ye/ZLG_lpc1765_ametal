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
 * \brief The M0+ core template for dualcore
 *
 * \internal
 * \par History
 * - 1.00 14-12-11  tee, first implementation.
 * \endinternal
 */ 
 
#include "ametal.h"
#include "am_board.h"

/** 
 * \brief Cortex-M0+ and Cortex-M4 memory config
 */
#include "..\shared\lpc5410x_config_memory.h"

/**
 * \brief Application Main entry point
 */
int main (void)
{     
    /* The board initialization  */
    am_board_init();

    while (1) {
        am_buzzer_on();
        am_mdelay(500);
        am_buzzer_off();
        am_mdelay(500);
    }
}

/* end of file */

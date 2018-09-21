/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
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
 * \brief SOC(片上系统),包含了芯片所有的外设
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-11  tee, first implementation.
 * \endinternal
 */

#ifndef __AM_SOC_H
#define __AM_SOC_H


#ifdef __cplusplus
extern "C" {
#endif

#include "amhw_adc.h"
#include "amhw_clock.h"
#include "amhw_cpuctrl.h"
#include "amhw_crc.h"
#include "amhw_dma.h"
#include "amhw_fifo.h"
#include "amhw_gint.h"
#include "amhw_gpio.h"
#include "amhw_i2c.h"
#include "amhw_iap.h"
#include "amhw_inmux.h"
#include "amhw_int.h"
#include "amhw_iocon.h"
#include "amhw_mbox.h"
#include "amhw_mrt.h"
#include "amhw_pint.h"
#include "amhw_pll.h"
#include "amhw_pmu.h"
#include "amhw_rit.h"
#include "amhw_rtc.h"
#include "amhw_sct.h"
#include "amhw_spi.h"
#include "amhw_syscon.h"
#include "amhw_systick.h"
#include "amhw_timer.h"
#include "amhw_usart.h"
#include "amhw_utick.h" 
#include "amhw_wwdt.h"

#include "amhw_lib_power.h"
#include "amhw_lpc5410x.h"
#include "lpc5410x_pin.h"  
#include "lpc5410x_inum.h" 
#include "lpc5410x_dma_chan.h" 

#ifdef __cplusplus
}
#endif

#endif /*__AM_SOC_H */

/* end of file */

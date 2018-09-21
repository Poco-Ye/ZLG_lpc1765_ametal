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
 * \brief WWDT drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-25  fft, first implementation.
 * \endinternal
 */
 
#include "amdr_wwdt.h"
#include "amhw_clock.h"
#include "am_int.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

static int __wwdt_feed(void *p_drv);
static int __wwdt_enable(void *p_drv, uint32_t timeout_ms);
static int __wwdt_info_get(void *p_drv, am_wdt_info_t *p_info);
    
/** \brief wwdt driver functions */
static const struct am_wdt_drv_funcs __g_wwdt_drv_funcs = {
    __wwdt_info_get,
    __wwdt_enable,
    __wwdt_feed,
};

static int __wwdt_info_get(void *p_drv, am_wdt_info_t *p_info)
{
    amdr_wwdt_dev_t *p_dev     = (amdr_wwdt_dev_t *)p_drv;
    amhw_wwdt_t     *p_hw_wwdt = p_dev->p_devinfo->p_hw_wwdt;
    uint32_t         wdt_freq;
    
    wdt_freq  = amhw_clock_periph_freq_get(p_hw_wwdt) / 4;
    
    p_info->min_timeout_ms = (0xFF + 1) * 1000 / wdt_freq;
    p_info->max_timeout_ms = (uint64_t)(0xFFFFFFFF + 1) / (uint64_t)wdt_freq * 1000;
    
    return AM_OK;
}

static int __wwdt_feed(void *p_drv)
{
    amdr_wwdt_dev_t *p_dev     = (amdr_wwdt_dev_t *)p_drv;
    amhw_wwdt_t     *p_hw_wwdt = p_dev->p_devinfo->p_hw_wwdt;
    
    amhw_wwdt_feed(p_hw_wwdt);

    return AM_OK;
}

static int __wwdt_enable(void *p_drv, uint32_t timeout_ms)
{
    amdr_wwdt_dev_t *p_dev     = (amdr_wwdt_dev_t *)p_drv;
    amhw_wwdt_t     *p_hw_wwdt = p_dev->p_devinfo->p_hw_wwdt;
    uint32_t         wdt_freq;
    uint32_t         ticks;
    
    wdt_freq  = amhw_clock_periph_freq_get(p_hw_wwdt) / 4;
    
    ticks = (uint64_t)(timeout_ms) * (uint64_t)1000000 / (1000000000 / wdt_freq);
    
    if (ticks <= 0xFF) {
        ticks = 0xFF;
    } else if (ticks >= 0xFFFFFF) {
        ticks = 0xFFFFFF;
    }
    
    amhw_wwdt_timeout_set(p_hw_wwdt, ticks);
    
    /* Check if reset is due to Watchdog */
    if (amhw_wwdt_status_get(p_hw_wwdt) & AMHW_WWDT_WDMOD_WDTOF) {
        amhw_wwdt_status_clr(p_hw_wwdt, AMHW_WWDT_WDMOD_WDTOF);
    }
 
    /* Configure WWDT to reset on time out */
    amhw_wwdt_option_set(p_hw_wwdt, AMHW_WWDT_WDMOD_LOCK | AMHW_WWDT_WDMOD_WDRESET);
    
    /* Clear watchdog warning and time out interrupts */
    amhw_wwdt_status_clr(p_hw_wwdt, AMHW_WWDT_WDMOD_WDTOF | AMHW_WWDT_WDMOD_WDINT);
    
    /* The WWDT start up */
    amhw_wwdt_start(p_hw_wwdt);
    
    return AM_OK;
}

am_wdt_handle_t amdr_wwdt_init (amdr_wwdt_dev_t           *p_dev,
                                const amdr_wwdt_devinfo_t *p_devinfo)
{
    amhw_wwdt_t *p_hw_wwdt;

    
    if (p_devinfo == NULL || p_devinfo->p_hw_wwdt == NULL) {
        return NULL;
    }
    
    p_hw_wwdt               = p_devinfo->p_hw_wwdt;
    p_dev->p_devinfo        = p_devinfo;
    p_dev->wdt_serv.p_funcs = (struct am_wdt_drv_funcs *)&__g_wwdt_drv_funcs;
    p_dev->wdt_serv.p_drv   = p_dev;

    amhw_wwdt_init(p_hw_wwdt);
    
    /* Check if reset is due to Watchdog */
    if (amhw_wwdt_status_get(p_hw_wwdt) & AMHW_WWDT_WDMOD_WDTOF) {
        amhw_wwdt_status_clr(p_hw_wwdt, AMHW_WWDT_WDMOD_WDTOF);
    }
    
    return &(p_dev->wdt_serv);
}

void amdr_wwdt_deinit (amdr_wwdt_dev_t *p_dev)
{
    /* The WWDT can not deinit */
}

/* end of file */

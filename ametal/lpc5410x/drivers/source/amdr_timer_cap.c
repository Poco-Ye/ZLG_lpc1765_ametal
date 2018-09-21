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
 * \brief Capture driver implementation for standard timer
 *
 * 1. The standard timer can provide 3 service as follows,This driver implement 
 *    the capture function.
 *     - Timing
 *     - PWM
 *     - CAP
 * 2. In the driver,The four match register used as follows:
 *     - The capture register 0 to generate capture channel 0
 *     - The capture register 1 to generate capture channel 1
 *     - The capture register 2 to generate capture channel 2
 *     - The capture register 3 to generate capture channel 3
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#include "amdr_timer_cap.h"
#include "am_int.h"
#include "amhw_clock.h"
#include "am_gpio.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/** \brief Configure the PWM */
static int __timer_cap_config(void              *p_cookie,
                              int                chan,
                              unsigned int       flags,
                              am_cap_callback_t  pfn_callback,
                              void              *p_arg);

/** \brief Enable the PWM OUTPUT */
static int __timer_cap_enable(void *p_drv, int chan);

/** \brief Disable the PWM OUTPUT */
static int __timer_cap_disable(void *p_drv, int chan);
                                 
/** \brief Disable the capture channel */
static int __timer_cap_reset(void *p_drv, int chan);

static int __timer_cap_count_to_time(void         *p_drv,
                                     int           chan,
                                     unsigned int  count1,
                                     unsigned int  count2,
                                     unsigned int *p_time_ns);

static void __timer_cap_irq_handler (void *p_arg);
                                     
/** \brief timer for PWMs driver functions */
static const struct am_cap_drv_funcs __g_timer_cap_drv_funcs = {
    __timer_cap_config,
    __timer_cap_enable,
    __timer_cap_disable,
    __timer_cap_reset,
    __timer_cap_count_to_time,
};

/******************************************************************************/

/** \brief Configure the PWM  */
static int __timer_cap_config (void              *p_drv,
                               int                chan,
                               unsigned int       options,
                               am_cap_callback_t  pfn_callback,
                               void              *p_arg)
{
    amdr_timer_cap_dev_t *p_dev      = (amdr_timer_cap_dev_t *)p_drv;
    amhw_timer_t         *p_hw_timer = p_dev->p_devinfo->p_hw_timer;
    
    /* The valid channel num is 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }
    
    /*  Support rising edge */
    if ((options & AM_CAP_TRIGGER_RISE) == AM_CAP_TRIGGER_RISE) {
        amhw_timer_cap_rising_enable(p_hw_timer, chan);
        amhw_timer_cap_falling_disable(p_hw_timer, chan);
    } 
    
    if ((options & AM_CAP_TRIGGER_FALL) == AM_CAP_TRIGGER_FALL) {
        amhw_timer_cap_rising_disable(p_hw_timer, chan);
        amhw_timer_cap_falling_enable(p_hw_timer, chan);
    }
    
    if ((options & AM_CAP_TRIGGER_BOTH_EDGES) == AM_CAP_TRIGGER_BOTH_EDGES) {
        amhw_timer_cap_rising_enable(p_hw_timer, chan);
        amhw_timer_cap_falling_enable(p_hw_timer, chan);
    }
    
    p_dev->callback_info[chan].callback_func = pfn_callback;
    p_dev->callback_info[chan].p_arg         = p_arg;
    
    return AM_OK;
}

/** \brief Enable the PWM OUTPUT */
static int __timer_cap_enable (void *p_drv, int chan)
{
    amdr_timer_cap_dev_t    *p_dev      = (amdr_timer_cap_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer = p_dev->p_devinfo->p_hw_timer;
    amdr_timer_cap_ioinfo_t *p_ioinfo   = p_dev->p_devinfo->p_ioinfo;
    
    /* The valid channel num is 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }
    
    am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].func);
    
    amhw_timer_cap_int_enable(p_hw_timer, chan);
    
    /* The timer not enable*/
    if ((p_hw_timer->tcr & 0x01) != 0x01) {
        amhw_timer_enable(p_hw_timer);
    }
    
    am_int_connect(p_dev->p_devinfo->inum, __timer_cap_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    
    return AM_OK;
}

/** \brief Disable the PWM OUTPUT */
static int __timer_cap_disable (void *p_drv, int chan)
{
    amdr_timer_cap_dev_t    *p_dev      = (amdr_timer_cap_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer = p_dev->p_devinfo->p_hw_timer;
    amdr_timer_cap_ioinfo_t *p_ioinfo   = p_dev->p_devinfo->p_ioinfo;
 
    /* The valid channel number is 0 ~ (channels_num - 1) */
    if (chan >= p_dev->p_devinfo->channels_num) {
        return -AM_EINVAL;
    }

    am_gpio_pin_cfg(p_ioinfo[chan].gpio, p_ioinfo[chan].dfunc);
  
    amhw_timer_cap_int_disable(p_hw_timer, chan);
    
    /** if all channels disabled the capture,disable the timer */
    if ((p_hw_timer->ccr & ((1 << 2) | (1 << 5) | (1 << 8) | (1 << 11))) == 0) {
        
        amhw_timer_disable(p_hw_timer);
    }
    
    return AM_OK;
}

/** \brief Disable the capture channel  */
static int __timer_cap_reset (void *p_drv, int chan)
{
    amdr_timer_cap_dev_t *p_dev      = (amdr_timer_cap_dev_t *)p_drv;
    amhw_timer_t         *p_hw_timer = p_dev->p_devinfo->p_hw_timer;
    
    amhw_timer_reset(p_hw_timer);
    
    return AM_OK;
}

static int __timer_cap_count_to_time (void         *p_drv,
                                      int           chan,
                                      unsigned int  count1,
                                      unsigned int  count2,
                                      unsigned int *p_time_ns)
{
    amdr_timer_cap_dev_t *p_dev      = (amdr_timer_cap_dev_t *)p_drv;
    amhw_timer_t         *p_hw_timer = p_dev->p_devinfo->p_hw_timer;
    uint32_t              clkfreq    = amhw_clock_periph_freq_get(p_hw_timer);
    uint32_t              count_err;
    
    count_err = count2 - count1;

    /* convert the count err value to time  */
    *p_time_ns = (uint64_t)1000000000 * (uint64_t)count_err / clkfreq ;
    
    return AM_OK;
}

static void __timer_cap_irq_handler (void *p_arg)
{
    amdr_timer_cap_dev_t *p_dev      = (amdr_timer_cap_dev_t *)p_arg;
    amhw_timer_t         *p_hw_timer = p_dev->p_devinfo->p_hw_timer;
    uint8_t               chans_num  = p_dev->p_devinfo->channels_num;
    uint8_t               i;
    am_cap_callback_t     callback_func;
    uint32_t              value;
    
    for (i = 0; i < chans_num; i++) {
        if (amhw_timer_cap_pending_get(p_hw_timer, i) == TRUE) {
            callback_func = p_dev->callback_info[i].callback_func;
            value    = amhw_timer_cap_val_get(p_hw_timer, i);
            
            if (callback_func != NULL) {
                callback_func(p_dev->callback_info[i].p_arg, value);
            }
            
            /* clear the match 0 interrupt flag */
            amhw_timer_cap_pending_clr(p_hw_timer,i);
        }        
    }
}

am_cap_handle_t amdr_timer_cap_init (amdr_timer_cap_dev_t           *p_dev,
                                     const amdr_timer_cap_devinfo_t *p_devinfo)
{
    amhw_timer_t  *p_hw_timer;
    uint8_t        i;
    
    if (p_dev == NULL || p_devinfo == NULL) {
        return NULL;
    }
    
    /* The timer support channels number is 4 */
    if (p_devinfo->channels_num > 4) {
        return NULL;
    }
    
    p_hw_timer              = p_devinfo->p_hw_timer;
    p_dev->p_devinfo        = p_devinfo;
    p_dev->cap_serv.p_funcs = (struct am_cap_drv_funcs *)&__g_timer_cap_drv_funcs;
    p_dev->cap_serv.p_drv   = p_dev;
    
    for (i = 0; i < p_devinfo->channels_num; i++) {
        p_dev->callback_info[i].callback_func = NULL;
    }
    
    /* Reset the timer counter and pre-scale counts to 0 */
    amhw_timer_reset(p_hw_timer);
    
    /* Set the timer pre-scale counts to 0   */
    amhw_timer_prescale_set(p_hw_timer, 0);
    
    amhw_timer_disable(p_hw_timer);
     
    return &(p_dev->cap_serv);
}

void amdr_timer_cap_deinit (amdr_timer_cap_dev_t *p_dev)
{
    amhw_timer_t *p_hw_timer  = p_dev->p_devinfo->p_hw_timer;
 
    amhw_timer_disable(p_hw_timer);
    am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */

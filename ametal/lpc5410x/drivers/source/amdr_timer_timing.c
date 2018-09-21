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
 * \brief Timing driver implementation for standard timer
 *
 * 1. The standard timer can provide 3 service as follows,This driver implement 
 *    the timing function.
 *     - Timing
 *     - PWM
 *     - CAP
 * 2. In the driver,The four match register used as follows:
 *     - The match register 0 to generate period timing interrupt
 *     - The match register 1 not use
 *     - The match register 2 not use
 *     - The match register 3 not use
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-05  tee, first implementation.
 * \endinternal
 */

#include "amdr_timer_timing.h"
#include "amhw_clock.h"
#include "am_int.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/* lpc5410x timer for timing drv functions declaration */
static int __timer_timing_info_get(void *p_drv, am_timer_info_t *p_info);

static int __timer_timing_count_get(void     *p_drv,
                                    uint8_t   chan,
                                    uint32_t *p_count);

static int __timer_timing_rollover_get (void     *p_drv,
                                        uint8_t   chan,
                                        uint32_t *p_rollover);
                                     
static int __timer_timing_disable(void *p_drv, uint8_t chan);

static int __timer_timing_enable(void    *p_drv, 
                                 uint8_t  chan,
                                 uint32_t max_timer_count);
    
static int __timer_timing_callback_set(void    *p_drv,
                                       uint8_t  chan,
                                       void   (*pfn_callback)(void *),
                                       void    *p_arg);
                                    
static int  __timer_timing_connect(void *p_drv);

static void __timer_irq_handler(void *p_arg);
    
/** \brief timer for timing driver functions */
static const struct am_timer_drv_funcs __g_timer_timing_drv_funcs = {
    __timer_timing_info_get,
    __timer_timing_count_get,
    __timer_timing_rollover_get,
    __timer_timing_disable,
    __timer_timing_enable,
    __timer_timing_callback_set,
    NULL,
    NULL,
    NULL,
    __timer_timing_connect,
};

/******************************************************************************/

int __timer_timing_connect (void *p_drv)
{
    amdr_timer_timing_dev_t *p_dev = (amdr_timer_timing_dev_t *)p_drv;
    
    am_int_connect(p_dev->p_devinfo->inum, __timer_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    
    return AM_OK;
}

void __timer_irq_handler (void *p_arg)
{
    amdr_timer_timing_dev_t *p_dev      = (amdr_timer_timing_dev_t *)p_arg;
    amhw_timer_t            *p_hw_timer =  p_dev->p_devinfo->p_hw_timer;

    /* 
     * Because use the match 0 to generate interrupt
     * So,Check if the match 0 interrupt 
     */
    if (amhw_timer_mat_pending_get(p_hw_timer, 0) == TRUE) {
        
        if (p_dev->callback_info[0].pfn_callback != NULL) {
            p_dev->callback_info[0].pfn_callback(p_dev->callback_info[0].p_arg);
        }
        
        /* clear the match 0 interrupt flag */
        amhw_timer_mat_pending_clr(p_hw_timer, 0);
    }
}

/** \brief Get the timer information */
static int __timer_timing_info_get (void *p_drv, am_timer_info_t *p_info)
{
    amdr_timer_timing_dev_t *p_dev      = (amdr_timer_timing_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer =  p_dev->p_devinfo->p_hw_timer;
    
    /* Get the input frequency */
    p_info->clk_frequency = amhw_clock_periph_freq_get(p_hw_timer);
    p_info->min_frequency = 1;                        /* The min freq is 1Hz     */
    p_info->max_frequency = p_info->clk_frequency;
    
    p_info->features = AM_TIMER_SIZE(32)           | /* 32-bit timer             */
                       AM_TIMER_CHAN_NUM(1)        | /* support 1 channels       */
                       AM_TIMER_CAN_INTERRUPT      | /* Can generate interrupt   */
                       AM_TIMER_INTERMEDIATE_COUNT | /* can read now count       */
                       AM_TIMER_AUTO_RELOAD;         /* Auto reload              */
    
    return AM_OK;
}

/** \brief Get the timer Now counter value */ 
static int __timer_timing_count_get (void     *p_drv,
                                     uint8_t   chan,
                                     uint32_t *p_count)
{
    amdr_timer_timing_dev_t *p_dev      = (amdr_timer_timing_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer =  p_dev->p_devinfo->p_hw_timer;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    *p_count = amhw_timer_count_get(p_hw_timer);

    return AM_OK;
}

/** \brief The timer roll over value get */
static int __timer_timing_rollover_get (void     *p_drv,
                                        uint8_t   chan,
                                        uint32_t *p_rollover)
{
    amdr_timer_timing_dev_t *p_dev      = (amdr_timer_timing_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer =  p_dev->p_devinfo->p_hw_timer;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    *p_rollover = 0xFFFFFFFF / amhw_clock_periph_freq_get(p_hw_timer);
    
    return AM_OK;
}

/** \brief The timer disable */
static int __timer_timing_disable (void *p_drv, uint8_t chan)
{
    amdr_timer_timing_dev_t *p_dev      = (amdr_timer_timing_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer =  p_dev->p_devinfo->p_hw_timer;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    amhw_timer_disable(p_hw_timer);
    
    amhw_timer_count_set(p_hw_timer, 0);
    
    /* clear the match 0 interrupt flag */
    amhw_timer_mat_pending_clr(p_hw_timer, 0);
    amhw_timer_mat_int_disable(p_hw_timer, 0);

    return AM_OK;
}

/** \brief The timer enable and set the maximum count value */
static int __timer_timing_enable (void    *p_drv, 
                                  uint8_t  chan,
                                  uint32_t max_timer_count)
{
    amdr_timer_timing_dev_t *p_dev      = (amdr_timer_timing_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer =  p_dev->p_devinfo->p_hw_timer;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    amhw_timer_mat_val_set(p_hw_timer, 0, max_timer_count - 1);
    amhw_timer_prescale_set(p_hw_timer, 0);
    
    amhw_timer_count_set(p_hw_timer, 0);
    
    /* clear the match 0 interrupt flag */
    amhw_timer_mat_pending_clr(p_hw_timer, 0);
    
    /* Enable the match 0 reset the timer counter */
    amhw_timer_mat_reset_enable(p_hw_timer, 0);

    if (p_dev->callback_info[0].pfn_callback == NULL) {
        amhw_timer_mat_int_disable(p_hw_timer, 0);
    } else {
        amhw_timer_mat_int_enable(p_hw_timer, 0);
    }
 
    amhw_timer_enable(p_hw_timer);
    
    return AM_OK;
}

/** \brief set the function to be called on every interrupt */
static int __timer_timing_callback_set (void    *p_drv,
                                        uint8_t  chan,
                                        void   (*pfn_callback)(void *),
                                        void    *p_arg)
{
    amdr_timer_timing_dev_t *p_dev      = (amdr_timer_timing_dev_t *)p_drv;
    amhw_timer_t            *p_hw_timer =  p_dev->p_devinfo->p_hw_timer;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    /* needn't interrupt, close the match 0 interrupt */
    if (pfn_callback == NULL) {
        amhw_timer_mat_int_disable(p_hw_timer, 0);
        
    } else {
        p_dev->callback_info[0].pfn_callback = pfn_callback;
        p_dev->callback_info[0].p_arg        = p_arg;
        
        amhw_timer_mat_int_enable(p_hw_timer, 0);
    }

    return AM_OK;
}

am_timer_handle_t amdr_timer_timing_init (amdr_timer_timing_dev_t           *p_dev,
                                          const amdr_timer_timing_devinfo_t *p_devinfo)
{
    amhw_timer_t *p_hw_timer;

    if (p_devinfo == NULL || p_devinfo->p_hw_timer == NULL) {
        return NULL;
    }
    
    p_hw_timer                 = p_devinfo->p_hw_timer;
    p_dev->p_devinfo           = p_devinfo;
    p_dev->timer_serv.p_funcs  = (struct am_timer_drv_funcs *)&__g_timer_timing_drv_funcs;
    p_dev->timer_serv.p_drv    = p_dev; 
    
    p_dev->callback_info[0].pfn_callback = NULL;
    p_dev->callback_info[0].p_arg        = NULL;

    amhw_timer_reset(p_hw_timer);     
     
    return &(p_dev->timer_serv);
}
                                     

void amdr_timer_timing_deinit (amdr_timer_timing_dev_t *p_dev)
{
    amhw_timer_t *p_hw_timer  = p_dev->p_devinfo->p_hw_timer;
 
    amhw_timer_disable(p_hw_timer);
    am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */

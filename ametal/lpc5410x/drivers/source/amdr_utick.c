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
 * \brief UTICK drivers implementation for Standard Timer interface
 *
 * The UTICK clock source is wdt osc.
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-17  tee, first implementation.
 * \endinternal
 */

#include "amdr_utick.h"
#include "amhw_clock.h"
#include "am_int.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/* lpc5410x timer for timing drv functions declaration */
static int __utick_info_get(void *p_drv, am_timer_info_t *p_info);

static int __utick_count_get(void     *p_drv,
                             uint8_t   chan,
                             uint32_t *p_count);

static int __utick_rollover_get(void     *p_drv,
                                uint8_t   chan,
                                uint32_t *p_rollover);
                                     
static int __utick_disable(void *p_drv, uint8_t chan);

static int __utick_enable(void     *p_drv, 
                          uint8_t   chan,
                          uint32_t  max_timer_count);
    
static int __utick_callback_set(void    *p_drv,
                                uint8_t  chan,
                                void   (*pfn_callback)(void *),
                                void    *p_arg);
                                    
static int  __utick_connect(void *p_drv);

static void __utick_irq_handler(void *p_arg);
    
/** \brief timer for timing driver functions */
static const struct am_timer_drv_funcs __g_utick_drv_funcs = {
    __utick_info_get,
    __utick_count_get,
    __utick_rollover_get,
    __utick_disable,
    __utick_enable,
    __utick_callback_set,
    NULL,
    NULL,
    NULL,
    __utick_connect,
};

/******************************************************************************/

int __utick_connect (void *p_drv)
{
    amdr_utick_dev_t *p_dev = (amdr_utick_dev_t *)p_drv;
    
    am_int_connect(p_dev->p_devinfo->inum, __utick_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    
    return AM_OK;
}

void __utick_irq_handler (void *p_arg)
{
    amdr_utick_dev_t *p_dev      = (amdr_utick_dev_t *)p_arg;
    amhw_utick_t     *p_hw_utick =  p_dev->p_devinfo->p_hw_utick;

    /* 
     * Because use the match 0 to generate interrupt
     * So,Check if the match 0 interrupt 
     */
    if (amhw_utick_int_flag_check(p_hw_utick) == TRUE) {
        if (p_dev->callback_info[0].pfn_callback != NULL) {
            p_dev->callback_info[0].pfn_callback(p_dev->callback_info[0].p_arg);
        }
        
        /* clear the match 0 interrupt flag */
        amhw_utick_int_flag_clr(p_hw_utick);
    }
}

/** \brief Get the timer information */
static int __utick_info_get (void *p_drv, am_timer_info_t *p_info)
{
    amdr_utick_dev_t *p_dev      = (amdr_utick_dev_t *)p_drv;
    amhw_utick_t     *p_hw_utick =  p_dev->p_devinfo->p_hw_utick;
    
    /* Get the input frequency */
    p_info->clk_frequency = amhw_clock_periph_freq_get(p_hw_utick);
    p_info->min_frequency = 1;                         /* The minimum freq is 1Hz  */
    p_info->max_frequency = p_info->clk_frequency / 2; /* 0 stop,1 for delay 2     */
    
    p_info->features = AM_TIMER_SIZE(31)           |  /* 31-bit timer             */
                       AM_TIMER_CHAN_NUM(1)        |  /* support 1 channels       */
                       AM_TIMER_CAN_INTERRUPT      |  /* Can generate interrupt   */
                       AM_TIMER_INTERMEDIATE_COUNT |  /* can read now count       */
                       AM_TIMER_AUTO_RELOAD;          /* Auto reload              */
    
    return AM_OK;
}

/** \brief Get the timer Now counter value */ 
static int __utick_count_get (void     *p_drv,
                              uint8_t   chan,
                              uint32_t *p_count)
{
    amdr_utick_dev_t *p_dev      = (amdr_utick_dev_t *)p_drv;
    amhw_utick_t     *p_hw_utick =  p_dev->p_devinfo->p_hw_utick;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    *p_count = amhw_utick_tick_get(p_hw_utick);

    return AM_OK;
}

/** \brief The timer roll over value get */
static int __utick_rollover_get (void     *p_drv,
                                 uint8_t   chan,
                                 uint32_t *p_rollover)
{
    amdr_utick_dev_t *p_dev      = (amdr_utick_dev_t *)p_drv;
    amhw_utick_t     *p_hw_utick =  p_dev->p_devinfo->p_hw_utick;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    *p_rollover = 0x7FFFFFFF / amhw_clock_periph_freq_get(p_hw_utick);
    
    return AM_OK;
}

/** \brief The timer disable */
static int __utick_disable (void *p_drv, uint8_t chan)
{
    amdr_utick_dev_t *p_dev      = (amdr_utick_dev_t *)p_drv;
    amhw_utick_t     *p_hw_utick =  p_dev->p_devinfo->p_hw_utick;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    amhw_utick_disable(p_hw_utick);
    
    amhw_utick_int_flag_clr(p_hw_utick);

    return AM_OK;
}

/** \brief The timer enable and set the maximum count value */
static int __utick_enable (void    *p_drv, 
                           uint8_t  chan,
                           uint32_t max_timer_count)
{
    amdr_utick_dev_t *p_dev      = (amdr_utick_dev_t *)p_drv;
    amhw_utick_t     *p_hw_utick =  p_dev->p_devinfo->p_hw_utick;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    amhw_utick_tick_set(p_hw_utick, max_timer_count, TRUE);
    
    return AM_OK;
}

/** \brief set the function to be called on every interrupt */
static int __utick_callback_set (void     *p_drv,
                                 uint8_t   chan,
                                 void    (*pfn_callback)(void *),
                                 void     *p_arg)
{
    amdr_utick_dev_t *p_dev = (amdr_utick_dev_t *)p_drv;

    if (chan != 0) {
        return -AM_EINVAL;
    }

    p_dev->callback_info[0].pfn_callback = pfn_callback;
    p_dev->callback_info[0].p_arg   = p_arg;

    return AM_OK;
}

am_timer_handle_t amdr_utick_init (amdr_utick_dev_t           *p_dev,
                                   const amdr_utick_devinfo_t *p_devinfo)
{
    amhw_utick_t *p_hw_utick;

    if (p_devinfo == NULL || p_devinfo->p_hw_utick == NULL) {
        return NULL;
    }
    
    p_hw_utick                 = p_devinfo->p_hw_utick;
    p_dev->p_devinfo           = p_devinfo;
    p_dev->timer_serv.p_funcs  = (struct am_timer_drv_funcs *)&__g_utick_drv_funcs;
    p_dev->timer_serv.p_drv    = p_dev; 
                               
    p_dev->callback_info[0].pfn_callback = NULL;
    p_dev->callback_info[0].p_arg        = NULL;

    amhw_utick_disable(p_hw_utick);
    
    return &(p_dev->timer_serv);
}

void amdr_utick_deinit (amdr_utick_dev_t *p_dev)
{
    amhw_utick_t     *p_hw_utick =  p_dev->p_devinfo->p_hw_utick;
    
    amhw_utick_disable(p_hw_utick);
    
    amhw_utick_int_flag_clr(p_hw_utick);
    
    am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */

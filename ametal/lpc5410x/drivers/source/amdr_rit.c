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
 * \brief RIT implementation for Standard Timer interface 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-17  tee, first implementation.
 * \endinternal
 */

#include "amdr_rit.h"
#include "amhw_clock.h"
#include "am_int.h"


/*******************************************************************************
* Functions declaration
*******************************************************************************/

/* lpc5410x RIT for timing drv functions declaration */
static int __rit_info_get(void *p_drv, am_timer_info_t *p_info);

static int __rit_count_get64(void     *p_drv,
                               uint8_t   chan,
                               uint64_t *p_count);

static int __rit_rollover_get64(void     *p_drv,
                                  uint8_t   chan,
                                  uint64_t *p_rollover);
                                     
static int __rit_disable(void *p_drv, uint8_t chan);

static int __rit_enable64(void     *p_drv, 
                            uint8_t   chan,
                            uint64_t  max_timer_count);
    
static int __rit_callback_set(void    *p_drv,
                           uint8_t  chan,
                           void   (*pfn_callback)(void *),
                           void    *p_arg);
                                    
static int  __rit_connect(void *p_drv);

static void __timer_irq_handler(void *p_arg);
    
/** \brief timer for timing driver functions */
static const struct am_timer_drv_funcs __g_rit_drv_funcs = {
    __rit_info_get,
    NULL,
    NULL,
    __rit_disable,
    NULL,
    __rit_callback_set,
    __rit_count_get64,
    __rit_rollover_get64,
    __rit_enable64,
    __rit_connect,
};

/******************************************************************************/

int __rit_connect (void *p_drv)
{
    amdr_rit_dev_t *p_dev = (amdr_rit_dev_t *)p_drv;
    
    am_int_connect(p_dev->p_devinfo->inum, __timer_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    
    return AM_OK;
}

void __timer_irq_handler (void *p_arg)
{
    amdr_rit_dev_t *p_dev    = (amdr_rit_dev_t *)p_arg;
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;

    /* 
     * Because use the match 0 to generate interrupt
     * So,Check if the match 0 interrupt 
     */
    if (amhw_rit_int_flag_check(p_hw_rit) == TRUE) {
        
        if (p_dev->callback_info[0].pfn_callback != NULL) {
            p_dev->callback_info[0].pfn_callback(p_dev->callback_info[0].p_arg);
        }
        
        /* clear the match 0 interrupt flag */
        amhw_rit_int_flag_clr(p_hw_rit);
    }
}

/** \brief Get the timer information */
static int __rit_info_get (void *p_drv, am_timer_info_t *p_info)
{
    amdr_rit_dev_t *p_dev    = (amdr_rit_dev_t *)p_drv;
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;
    
    /* Get the input frequency */
    p_info->clk_frequency = amhw_clock_periph_freq_get(p_hw_rit);
    p_info->min_frequency = 1;                        /* The minimum freq is 1Hz     */
    p_info->max_frequency = p_info->clk_frequency;
    
    p_info->features  = AM_TIMER_SIZE(48)           | /* 32-bit timer             */
                        AM_TIMER_CHAN_NUM(1)        | /* support 1 channels       */
                        AM_TIMER_CAN_INTERRUPT      | /* Can generate interrupt   */
                        AM_TIMER_INTERMEDIATE_COUNT | /* can read now count       */
                        AM_TIMER_AUTO_RELOAD;         /* Auto reload              */
    
    return AM_OK;
}

/** \brief Get the timer Now counter value */ 
static int __rit_count_get64 (void     *p_drv,
                                uint8_t   chan,
                                uint64_t *p_count)
{
    amdr_rit_dev_t *p_dev    = (amdr_rit_dev_t *)p_drv;
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    *p_count = amhw_rit_count_get(p_hw_rit);

    return AM_OK;
}

/** \brief The timer roll over value get */
static int __rit_rollover_get64 (void     *p_drv,
                                   uint8_t   chan,
                                   uint64_t *p_rollover)
{
    amdr_rit_dev_t *p_dev    = (amdr_rit_dev_t *)p_drv;
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    *p_rollover = 0xFFFFFFFFFFFFull / amhw_clock_periph_freq_get(p_hw_rit);
    
    return AM_OK;
}

/** \brief The timer disable */
static int __rit_disable (void *p_drv, uint8_t chan)
{
    amdr_rit_dev_t *p_dev    = (amdr_rit_dev_t *)p_drv;
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    amhw_rit_disable(p_hw_rit);
    
    amhw_rit_count_set(p_hw_rit, 0);
    
    /* clear the RIT interrupt flag */
    amhw_rit_int_flag_clr(p_hw_rit);

    return AM_OK;
}

/** \brief The timer enable and set the maximum count value */
static int __rit_enable64 (void     *p_drv, 
                           uint8_t   chan,
                           uint64_t  max_timer_count)
{
    amdr_rit_dev_t *p_dev    = (amdr_rit_dev_t *)p_drv;
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    amhw_rit_mask_set(p_hw_rit, 0);     /* No mask */
    amhw_rit_count_set(p_hw_rit, 0);
    amhw_rit_compval_set(p_hw_rit, max_timer_count - 1);
    amhw_rit_clear_enable(p_hw_rit);

    amhw_rit_enable(p_hw_rit);
    
    return AM_OK;
}

/** \brief set the function to be called on every interrupt */
static int __rit_callback_set (void   *p_drv,
                               uint8_t chan,
                               void  (*pfn_callback)(void *),
                               void   *p_arg)
{
    amdr_rit_dev_t *p_dev    = (amdr_rit_dev_t *)p_drv;
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;
    
    if (chan != 0) {
        return -AM_EINVAL;
    }
    
    p_dev->callback_info[0].pfn_callback = pfn_callback;
    p_dev->callback_info[0].p_arg   = p_arg;

    /* clear the RIT interrupt flag */
    amhw_rit_int_flag_clr(p_hw_rit);
 
    return AM_OK;
   
}

am_timer_handle_t amdr_rit_init (amdr_rit_dev_t           *p_dev,
                                 const amdr_rit_devinfo_t *p_devinfo)
{
    amhw_rit_t *p_hw_rit;

    if (p_devinfo == NULL || p_devinfo->p_hw_rit == NULL) {
        return NULL;
    }
    
    p_hw_rit                   = p_devinfo->p_hw_rit;
    p_dev->p_devinfo           = p_devinfo;
    p_dev->timer_serv.p_funcs  = (struct am_timer_drv_funcs *)&__g_rit_drv_funcs;
    p_dev->timer_serv.p_drv    = p_dev; 
    
    p_dev->callback_info[0].pfn_callback = NULL;
    p_dev->callback_info[0].p_arg        = NULL;

    /* disable the RIT,default(after reset) is enable */
    amhw_rit_disable(p_hw_rit);
    
    amhw_rit_clear_enable(p_hw_rit);
    
    /* 
     * Enable for debug,The timer is halted when the processor is halted for debugging 
     */
    amhw_rit_debug_enable(p_hw_rit);
    
    return &(p_dev->timer_serv);
}
                                     

void amdr_rit_deinit (amdr_rit_dev_t *p_dev)
{
    amhw_rit_t     *p_hw_rit =  p_dev->p_devinfo->p_hw_rit;
    
    p_dev->timer_serv.p_funcs  = NULL;
    p_dev->timer_serv.p_drv    = NULL; 
    
    /* disable the RIT */
    amhw_rit_disable(p_hw_rit);
    
    am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */

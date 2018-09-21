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
 * \brief Timing driver implementation for SCT
 *
 * 1. The SCT can provide 3 service as follows,This driver implement 
 *    the timing function.
 *     - Timing
 *     - PWM
 *     - CAP
 * 2. In the driver,The SCT resource used as follows:
 *    - The match 0 to save the period time,associate with event 0 to generate 
 *      interrupt.
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-14  tee, first implementation.
 * \endinternal
 */

#include "amdr_sct_timing.h"
#include "am_int.h"
#include "amhw_clock.h"

/*******************************************************************************
  Functions declaration
*******************************************************************************/

/* lpc5410x SCT for timing drv functions declaration */
static int __sct_timing_info_get(void *p_drv, am_timer_info_t *p_info);

static int __sct_timing_count_get(void     *p_drv,
                                  uint8_t   chan,
                                  uint32_t *p_count);

static int __sct_timing_rollover_get(void     *p_drv,
                                     uint8_t   chan,
                                     uint32_t *p_rollover);
                                     
static int __sct_timing_disable(void *p_drv, uint8_t chan);

static int __sct_timing_enable(void     *p_drv, 
                               uint8_t   chan,
                               uint32_t  max_sct_count);
    
static int __sct_timing_callback_set(void    *p_drv,
                                     uint8_t  chan,
                                     void   (*pfn_callback)(void *),
                                     void    *p_arg);
                                    
static int  __sct_timing_connect(void *p_drv);

static void __sct_irq_handler(void *p_arg);
    
/** \brief SCT for timing driver functions */
static const struct am_timer_drv_funcs __g_sct_timing_drv_funcs = {
    __sct_timing_info_get,
    __sct_timing_count_get,
    __sct_timing_rollover_get,
    __sct_timing_disable,
    __sct_timing_enable,
    __sct_timing_callback_set,
    NULL,
    NULL,
    NULL,
    __sct_timing_connect,
};

/******************************************************************************/

/**
 * \brief Calculate 16 bits timer prescale(8-bit) and match value(16-bit) for a given count
 *
 * \param[in]  count   : number of clocks the 16bits timer count 
 * \param[out] p_match : pointer to hold the timer match value
 *
 * \return the 8-bit prescale value calculated
 */
uint32_t __prescale_and_match_cal (uint32_t count, uint32_t *p_match)
{
    uint32_t match, min_remainder, prescale;
    uint32_t result_quot, result_rem;
 
    min_remainder = count;
    prescale      = 1;
   *p_match       = 65536;

    /* 
     * the count is less than 65536, 
     * the prescale set to 1, and the match equal to count   
     */
    if (count <= 65536) {        
        prescale = 1;
       *p_match  = count;  
        return prescale;        
    }    
    
    /* check match value one by one until find a best one */
    for (match = 65536; match > 0; match--) {
        result_quot = count / match;
        result_rem  = count % match;
        
        /* 
         * because the width of prescale value is 8-bits, the result_quot maximum
         * value is 256, if beyond 256,the count is can't be reached.
         */
        if (result_quot <= 256) {       
            if (result_rem == 0) {   
            
                /* find a best prescale and match value */
                prescale = result_quot;
                *p_match = match;
                break;
                
            } else if (result_rem < min_remainder) {
            
                /* find a better prescale and match value */
                min_remainder = result_rem;
                prescale      = result_quot;
               *p_match       = match;
            }
        }
    }

    return prescale;
}

int __sct_timing_connect (void *p_drv)
{
    amdr_sct_timing_dev_t *p_dev = (amdr_sct_timing_dev_t *)p_drv;
    
    am_int_connect(p_dev->p_devinfo->inum, __sct_irq_handler, (void *)p_dev);
    am_int_enable(p_dev->p_devinfo->inum);
    
    return AM_OK;
}

void __sct_irq_handler (void *p_arg)
{
    amdr_sct_timing_dev_t *p_dev    = (amdr_sct_timing_dev_t *)p_arg;
    amhw_sct_t            *p_hw_sct =  p_dev->p_devinfo->p_hw_sct;

    /* 
     * Because use the event 0 to generate interrupt
     * So,Check if the event 0 interrupt 
     */
    if (amhw_sct_event_flag_chk(p_hw_sct, AMHW_SCT_EVT(0)) == TRUE ) {
        
        if (p_dev->callback_info[0].pfn_callback != NULL) {
            p_dev->callback_info[0].pfn_callback(p_dev->callback_info[0].p_arg);
        }
        
        /* Clear the event 0 flag */
        amhw_sct_event_flag_clr(p_hw_sct, AMHW_SCT_EVT(0));  
    }
    
    if (amhw_sct_event_flag_chk(p_hw_sct, AMHW_SCT_EVT(1)) == TRUE ) {
        
        if (p_dev->callback_info[1].pfn_callback != NULL) {
            p_dev->callback_info[1].pfn_callback(p_dev->callback_info[1].p_arg);
        }
        
        /* Clear the event 0 flag */
        amhw_sct_event_flag_clr(p_hw_sct, AMHW_SCT_EVT(1));  
    }
}

/** \brief Get the SCT information */
static int __sct_timing_info_get (void *p_drv, am_timer_info_t *p_info)
{
    amdr_sct_timing_dev_t *p_dev    = (amdr_sct_timing_dev_t *)p_drv;
    amhw_sct_t            *p_hw_sct =  p_dev->p_devinfo->p_hw_sct;
    
    /* Get the input frequency */
    p_info->clk_frequency = amhw_clock_periph_freq_get(p_hw_sct);
    p_info->max_frequency = p_info->clk_frequency;
    
    if (p_dev->p_devinfo->flag == AMDR_SCT_TIMING_1_32BIT) {
        p_info->min_frequency = 1;                        /* The minimum freq is 1Hz */
        
        p_info->features  = AM_TIMER_SIZE(32)           | /* 32-bit SCT              */
                            AM_TIMER_CHAN_NUM(1)        | /* support 1 channels      */
                            AM_TIMER_CAN_INTERRUPT      | /* Can generate interrupt  */
                            AM_TIMER_INTERMEDIATE_COUNT | /* can read now count      */
                            AM_TIMER_AUTO_RELOAD;         /* Auto reload             */
        
    } else {
        
        /* 8-bit pre-scale,16-bit timer */
        if (p_info->clk_frequency <= 0xFFFFFF) {
            p_info->min_frequency = 1;
        } else {
            p_info->min_frequency = p_info->clk_frequency / 0xFFFFFF;
            
            if (p_info->min_frequency * 0xFFFFFF < p_info->clk_frequency) {
                p_info->min_frequency += 1;
            }
        }
            
        p_info->features  = AM_TIMER_SIZE(16)           | /* 16-bit SCT               */
                            AM_TIMER_CHAN_NUM(2)        | /* support 2 channels       */
                            AM_TIMER_CAN_INTERRUPT      | /* Can generate interrupt   */
                            AM_TIMER_INTERMEDIATE_COUNT | /* can read now count       */
                            AM_TIMER_AUTO_RELOAD;         /* Auto reload              */        
    
    }
    
    return AM_OK;
}

/** \brief Get the SCT Now counter value */ 
static int __sct_timing_count_get (void     *p_drv,
                                   uint8_t   chan,
                                   uint32_t *p_count)
{
    amdr_sct_timing_dev_t *p_dev   = (amdr_sct_timing_dev_t *)p_drv;
    amhw_sct_t           *p_hw_sct =  p_dev->p_devinfo->p_hw_sct;
    
    if (p_dev->p_devinfo->flag == AMDR_SCT_TIMING_1_32BIT) {
        if (chan != 0) {
            return -AM_EINVAL;
        }

        *p_count = amhw_sct_count_get(p_hw_sct, AMHW_SCT_MODE_UNIFY);
        
    } else {
        if (chan == 0) {
            *p_count = amhw_sct_count_get(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L);
        } else if (chan == 1) {
            *p_count = amhw_sct_count_get(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H);
        }
        
        return -AM_EINVAL;
    }
    return AM_OK;
}

/** \brief The SCT roll over value get */
static int __sct_timing_rollover_get (void     *p_drv,
                                      uint8_t   chan,
                                      uint32_t *p_rollover)
{
    amdr_sct_timing_dev_t *p_dev    = (amdr_sct_timing_dev_t *)p_drv;
    amhw_sct_t            *p_hw_sct =  p_dev->p_devinfo->p_hw_sct;
    
    if (p_dev->p_devinfo->flag == AMDR_SCT_TIMING_1_32BIT) {
        if (chan != 0) {
            return -AM_EINVAL;
        }

        *p_rollover = 0xFFFFFFFF / amhw_clock_periph_freq_get(p_hw_sct);
        
    } else {
        if (chan >= 2) {
            return -AM_EINVAL;
        }
        
        *p_rollover = 0xFFFFFF / amhw_clock_periph_freq_get(p_hw_sct);
    }
    
    return AM_OK;
}

/** \brief The SCT disable */
static int __sct_timing_disable (void *p_drv, uint8_t chan)
{
    amdr_sct_timing_dev_t *p_dev    = (amdr_sct_timing_dev_t *)p_drv;
    amhw_sct_t            *p_hw_sct =  p_dev->p_devinfo->p_hw_sct;
    
    if (p_dev->p_devinfo->flag == AMDR_SCT_TIMING_1_32BIT) {
        if (chan != 0) {
            return -AM_EINVAL;
        }
        /* Set the halt and stop bits,the SCT L counter is stop */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
        amhw_sct_count_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
        
    } else {
        if (chan == 0) {
            
            /* Set the halt and stop bits,the SCT L counter is stop */
            amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
            amhw_sct_count_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L, 0);
            
        } else if (chan == 1) {
            
            /* Set the halt and stop bits,the SCT L counter is stop */
            amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
            amhw_sct_count_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H, 0);
            
        }
        
        return -AM_EINVAL;
    }

    return AM_OK;
}

/** \brief The SCT enable and set the max count value */
static int __sct_timing_enable (void     *p_drv, 
                                uint8_t   chan,
                                uint32_t  max_sct_count)
{
    amdr_sct_timing_dev_t *p_dev    = (amdr_sct_timing_dev_t *)p_drv;
    amhw_sct_t            *p_hw_sct =  p_dev->p_devinfo->p_hw_sct;
    
    if (p_dev->p_devinfo->flag == AMDR_SCT_TIMING_1_32BIT) {
        if (chan != 0) {
            return -AM_EINVAL;
        }

        /* Before change the count value, halt the counter */
        amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
        amhw_sct_count_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
        
        amhw_sct_mat_val_set(p_hw_sct, 
                             AMHW_SCT_MODE_UNIFY, 
                             AMHW_SCT_MAT(0), 
                             max_sct_count);
        amhw_sct_mat_reload_val_set(p_hw_sct, 
                                    AMHW_SCT_MODE_UNIFY, 
                                    AMHW_SCT_MAT(0), 
                                    max_sct_count);
        
        if (p_dev->callback_info[0].pfn_callback == NULL) {
            amhw_sct_event_int_disable(p_hw_sct, AMHW_SCT_EVT(0));
        } else {
            amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
        }
        
        /* start counting */
        amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
        
    } else {
        
        uint8_t  prescale;
        uint32_t match;
        
        /* 16bit timer + 8bit prescale support timing 0xFFFFFF counts*/
        if (max_sct_count > 0xFFFFFF || chan >= 2) {
            return -AM_EINVAL;
        }
        
        prescale = __prescale_and_match_cal(max_sct_count, &match);
        
        if (chan == 0) {
            
            /* Before change the count value, halt the counter */
            amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
            amhw_sct_count_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L, 0);
            
            amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L, prescale);
            
            amhw_sct_mat_val_set(p_hw_sct, 
                                 AMHW_SCT_MODE_SEPARATE_L, 
                                 AMHW_SCT_MAT(0), 
                                 match);
            amhw_sct_mat_reload_val_set(p_hw_sct, 
                                        AMHW_SCT_MODE_SEPARATE_L,
                                        AMHW_SCT_MAT(0),
                                        match);
            
            if (p_dev->callback_info[0].pfn_callback == NULL) {
                amhw_sct_event_int_disable(p_hw_sct, AMHW_SCT_EVT(0));
            } else {
                amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
            }
            
            /* start counting */
            amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
            
        } else if (chan == 1) {
            
            /* Before change the count value, halt the counter */
            amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_H | AMHW_SCT_CTRL_HALT_H);
            amhw_sct_count_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H, 0);
            
            amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H, prescale);
            
            amhw_sct_mat_val_set(p_hw_sct, 
                                 AMHW_SCT_MODE_SEPARATE_H, 
                                 AMHW_SCT_MAT(0), 
                                 match);
            amhw_sct_mat_reload_val_set(p_hw_sct, 
                                        AMHW_SCT_MODE_SEPARATE_H,
                                        AMHW_SCT_MAT(0),
                                        match);
            
            if (p_dev->callback_info[1].pfn_callback == NULL) {
                amhw_sct_event_int_disable(p_hw_sct, AMHW_SCT_EVT(1));
            } else {
                amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(1));
            }
            
            /* start counting */
            amhw_sct_ctrl_clr(p_hw_sct, AMHW_SCT_CTRL_STOP_H | AMHW_SCT_CTRL_HALT_H);
        }
    }

    return AM_OK;
}

/** \brief set the function to be called on every interrupt */
static int __sct_timing_callback_set (void     *p_drv,
                                      uint8_t   chan,
                                      void    (*pfn_callback)(void *),
                                      void     *p_arg)
{
    amdr_sct_timing_dev_t *p_dev    = (amdr_sct_timing_dev_t *)p_drv;
    amhw_sct_t            *p_hw_sct =  p_dev->p_devinfo->p_hw_sct;
    
    if (p_dev->p_devinfo->flag == AMDR_SCT_TIMING_1_32BIT) {
        if (chan != 0) {
            return -AM_EINVAL;
        }
        
        /* needn't interrupt, disable the event 0 interrupt */
        if (pfn_callback == NULL) {
            amhw_sct_event_int_disable(p_hw_sct, AMHW_SCT_EVT(0));
            
        } else {
            p_dev->callback_info[0].pfn_callback = pfn_callback;
            p_dev->callback_info[0].p_arg   = p_arg;
            
            amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
        }
    } else {
        if (chan >= 2) {
            return -AM_EINVAL;
        }
        
        /* needn't interrupt, disable the event 0 interrupt */
        if (pfn_callback == NULL) {
            amhw_sct_event_int_disable(p_hw_sct, AMHW_SCT_EVT(chan));
            
        } else {
            
            p_dev->callback_info[chan].pfn_callback = pfn_callback;
            p_dev->callback_info[chan].p_arg   = p_arg;
            
            amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(chan));
        }
    }
    
    return AM_OK;
}

static void __sct_timing_1_32bit_init (amhw_sct_t *p_hw_sct)
{
    amhw_sct_config(p_hw_sct,
                    AMHW_SCT_CONFIG_32BIT_COUNTER  | /* the timer is operate as 1 32-bit timer */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* the SCT clock is system clock          */
    
    /* Configure the match/capture reg 0 operate as match register */
    amhw_sct_regmode_config(p_hw_sct,
                            AMHW_SCT_MODE_UNIFY,    /* the SCT mode is UNIFY(1 32-bit counter)  */
                            0,                      /* select the match/capture  0 to configure */
                            AMHW_SCT_MATCAP_MATCH); /* operate as match register                */
    
    /* CLear the match 0 and match reload value */
    amhw_sct_mat_val_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), 0);
    amhw_sct_mat_reload_val_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_MAT(0), 0);
    
    /* set the event 0 control */
    amhw_sct_event_ctrl(p_hw_sct,
                        AMHW_SCT_EVT(0),                  /* event 0 */
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* the event associated with the match 0 */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* Uses the specified match only.        */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV value is added into STATE     */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* ADD 0,the state will not change       */
                   
    /* set the now state value is 0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
    
    /* enable the event 0 happen in state 0 */
    amhw_sct_event_state_enable(p_hw_sct, AMHW_SCT_EVT(0), AMHW_SCT_STATE(0));
    
    /* enable the event 0 as the counter limit */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_UNIFY, AMHW_SCT_EVT(0));
    
    /* enable the event 0 generate interrupt */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));

    /* Set the CLRCTR bit to clear the counter to 0 */
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
    
    /* Set the prescaler value to 0. use the system clock,not prescale */
    amhw_sct_prescale_set(p_hw_sct, AMHW_SCT_MODE_UNIFY, 0);
}


/* 
 * The event0 associated with match0 _L 16bits, _L 16bits timer
 * The event1 associated with match0 _H 16bits, _H 16bits timer
 */
static void __sct_timing_2_16bit_init(amhw_sct_t *p_hw_sct)
{
    amhw_sct_config(p_hw_sct,
                    AMHW_SCT_CONFIG_16BIT_COUNTER  | /* the timer is operate as 2 16-bit timer */
                    AMHW_SCT_CONFIG_CLKMODE_SYSCLK); /* the SCT clock is system clock */    

    /* configure the match/capture reg 0 _L / or _H 16bits operate as match register */
    amhw_sct_regmode_config(p_hw_sct, 
                            AMHW_SCT_MODE_SEPARATE_L, 
                            AMHW_SCT_MAT(0),
                            AMHW_SCT_MATCAP_MATCH);
    
    amhw_sct_regmode_config(p_hw_sct, 
                            AMHW_SCT_MODE_SEPARATE_H, 
                            AMHW_SCT_MAT(0),
                            AMHW_SCT_MATCAP_MATCH);
    
    /* The L timer use the event 0, set the event 1 control */
    amhw_sct_event_ctrl(p_hw_sct,
                        AMHW_SCT_EVT(0),
                        AMHW_SCT_EV_CTRL_HEVENT_L       |
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* the event associated with the match 0 */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* Uses the specified match only.        */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV value is added into STATE     */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* ADD 0,the state will not change       */    

    /* The H timer use the event 1, set the event 1 control */
    amhw_sct_event_ctrl(p_hw_sct,
                        AMHW_SCT_EVT(1),
                        AMHW_SCT_EV_CTRL_HEVENT_H       |  
                        AMHW_SCT_EV_CTRL_MATCHSEL(0)    | /* the event associated with the match 0 */
                        AMHW_SCT_EV_CTRL_COMBMODE_MATCH | /* Uses the specified match only.        */
                        AMHW_SCT_EV_CTRL_STATELD_ADD    | /*  STATEV value is added into STATE     */ 
                        AMHW_SCT_EV_CTRL_STATEV(0));      /* ADD 0,the state will not change       */    

    /* set the now state value is 0 */
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L, AMHW_SCT_STATE(0));
    amhw_sct_state_set(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H, AMHW_SCT_STATE(0));
    
    /* enable the event happen in state 0 */
    amhw_sct_event_state_enable(p_hw_sct, AMHW_SCT_EVT(0), AMHW_SCT_STATE(0));
    amhw_sct_event_state_enable(p_hw_sct, AMHW_SCT_EVT(1), AMHW_SCT_STATE(0));

    /* enable the event as the counter limit */
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_SEPARATE_L, AMHW_SCT_EVT(0));
    amhw_sct_event_limit_enable(p_hw_sct, AMHW_SCT_MODE_SEPARATE_H, AMHW_SCT_EVT(1));
    
    /* enable the event generate interrupt */
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(0));
    amhw_sct_event_int_enable(p_hw_sct, AMHW_SCT_EVT(1));

    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_H);
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_CLRCTR_L);
}

am_timer_handle_t amdr_sct_timing_init (amdr_sct_timing_dev_t           *p_dev,
                                        const amdr_sct_timing_devinfo_t *p_devinfo)
{
    amhw_sct_t *p_hw_sct;

    if (p_devinfo == NULL || p_devinfo->p_hw_sct == NULL) {
        return NULL;
    }
    
    p_hw_sct                  = p_devinfo->p_hw_sct;
    p_dev->p_devinfo          = p_devinfo;
    p_dev->timer_serv.p_funcs = (struct am_timer_drv_funcs *)&__g_sct_timing_drv_funcs;
    p_dev->timer_serv.p_drv   = p_dev; 

    /* Operate as one 32-bit timer */
    if (p_devinfo->flag == AMDR_SCT_TIMING_1_32BIT) {
        __sct_timing_1_32bit_init(p_hw_sct);
        
        p_dev->callback_info[0].pfn_callback = NULL;
        p_dev->callback_info[0].p_arg        = NULL;
    } else {
        __sct_timing_2_16bit_init(p_hw_sct);
        
        p_dev->callback_info[0].pfn_callback = NULL;
        p_dev->callback_info[0].p_arg        = NULL;
    
        p_dev->callback_info[1].pfn_callback = NULL;
        p_dev->callback_info[1].p_arg        = NULL;
    }
    
    return &(p_dev->timer_serv);
}

void amdr_sct_timing_deinit (amdr_sct_timing_dev_t *p_dev)
{
    amhw_sct_t *p_hw_sct = p_dev->p_devinfo->p_hw_sct;
 
    amhw_sct_ctrl_set(p_hw_sct, AMHW_SCT_CTRL_STOP_L | AMHW_SCT_CTRL_HALT_L);
    
    am_int_disable(p_dev->p_devinfo->inum);
}

/* end of file */

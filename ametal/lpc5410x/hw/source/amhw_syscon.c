/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief LPC5410x System configuration (SYSCON) implementation for operating hardware.
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */
 
#include "amhw_syscon.h"

/******************************************************************************
* Public functions
*******************************************************************************/

/**
 * \brief Set source for non-maskable interrupt (NMI) 
 */
void amhw_syscon_nmisrc_set (uint32_t intsrc)
{
    uint32_t reg;

    reg    =  AMHW_SYSCON->nmisrc;
#if defined(CORE_M4)
    reg   &= ~AMHW_SYSCON_NMISRC_M4_ENABLE;
#else
    reg   &= ~AMHW_SYSCON_NMISRC_M0_ENABLE;
    intsrc = (intsrc << 8);
#endif

    /* First write without NMI bit, and then write source */
    AMHW_SYSCON->nmisrc = reg;
    AMHW_SYSCON->nmisrc = reg | intsrc;
}

/** 
 * \brief Enable interrupt used for NMI source 
 */
void amhw_syscon_nmisrc_enable (void)
{
#if defined(CORE_M4)
    AMHW_SYSCON->nmisrc |= AMHW_SYSCON_NMISRC_M4_ENABLE;
#else
    AMHW_SYSCON->nmisrc |= AMHW_SYSCON_NMISRC_M0_ENABLE;
#endif
}

/** 
 * \brief Disable interrupt used for NMI source 
 */
void amhw_syscon_nmisrc_disable (void)
{
#if defined(CORE_M4)
    AMHW_SYSCON->nmisrc &= ~AMHW_SYSCON_NMISRC_M4_ENABLE;
#else
    AMHW_SYSCON->nmisrc &= ~AMHW_SYSCON_NMISRC_M0_ENABLE;
#endif
}

/** 
 * \brief Resets a peripheral 
 */
void amhw_syscon_periph_reset (amhw_syscon_periph_reset_t periph)
{
    uint32_t pid = (uint32_t)periph;

    if (pid >= 128) {
        
        /* Async resets mapped to 128 and above, offset for peripheral bit index */
        pid = 1 << (((uint32_t)periph) - 128);
        
        AMHW_ASYNCSYSCON->asyncpresetctrlset = pid;
        AMHW_ASYNCSYSCON->asyncpresetctrlclr = pid;
    } else if (periph >= 32) {
        pid = 1 << (((uint32_t)periph) - 32);
        
        AMHW_SYSCON->presetctrlset1 = pid;
        AMHW_SYSCON->presetctrlclr1 = pid;
    } else {
        pid = 1 << ((uint32_t)periph);
        
        AMHW_SYSCON->presetctrlset0 = pid;
        AMHW_SYSCON->presetctrlclr0 = pid;
    }
}

/** 
 * \brief Returns the computed value for a frequency measurement cycle 
 */
uint32_t amhw_syscon_freqmeas_targfreq_get (uint32_t ref_clkrate)
{
    uint32_t capval;
    uint64_t clkrate = 0;

    /* Get raw capture value */
    capval = amhw_syscon_freqmeas_capval_get();

    /* LIMIT CAPVAL check */
    if (capval > 2) {
        clkrate = (((uint64_t)capval - 2) * (uint64_t)ref_clkrate) / 0x4000;
    }

    return (uint32_t)clkrate;
}

void amhw_syscon_powerup (uint32_t powerupmask)
{
    /*
     * If turning the PLL back on, perform the following sequence to 
     * accelerate PLL lock.
     */
    if (powerupmask & AMHW_SYSCON_PD_SYS_PLL) {
        
        volatile uint32_t delay_x;
        
        uint32_t max_cco    = (1 << 18) | 0x3fff;
        uint32_t cur_ssctrl = AMHW_SYSCON->syspllssctrl0;

        /* If NOT using spread spectrum mode */
        if (cur_ssctrl & (1 << 18)) {

            /* Turn on PLL */
            AMHW_SYSCON->pdruncfgclr = AMHW_SYSCON_PD_SYS_PLL;
            
            /* 
             * this sequence accelerate the PLL lock time.
             */
            AMHW_SYSCON->syspllssctrl0 = max_cco | (1 << 17); /* Set mreq to activate */
            
            /* clear mreq to prepare for restoring mreq */
            AMHW_SYSCON->syspllssctrl0 = max_cco;

            /* Delay for 20 uSec @ 12Mhz*/
            for (delay_x = 0; delay_x < 48; ++delay_x) {}

            /* set original value back with mreq */
            AMHW_SYSCON->syspllssctrl0 = cur_ssctrl | (1 << 17);
        }
    }

    /* Enable peripheral states by setting low */
    AMHW_SYSCON->pdruncfgclr = powerupmask;
}

void amhw_syscon_setupflashclocks (uint32_t freq)
{
    if (freq < 20000000) {
        amhw_syscon_flashaccess_set(AMHW_SYSCON_FLASH_1CYCLE);
    } else if (freq < 48000000) {
        amhw_syscon_flashaccess_set(AMHW_SYSCON_FLASH_2CYCLE);
    } else if (freq < 72000000) {
        amhw_syscon_flashaccess_set(AMHW_SYSCON_FLASH_3CYCLE);
    } else {
        amhw_syscon_flashaccess_set(AMHW_SYSCON_FLASH_4CYCLE);
    }
}

/**
 * \brief Set AHB priority 
 */
void amhw_syscon_ahb_priority_set (am_ahb_bus_type_t bus, uint8_t priority)
{
    uint32_t temp;
    
    priority &= 0x03;                           /* Valid 0 ~ 3 */
    
    temp      = AMHW_SYSCON->ahbmatprio;
    temp     &= ~(0x03 << ((uint32_t)bus));     /* Clear       */
    
    /* Set priority */
    AMHW_SYSCON->ahbmatprio = temp | (priority << ((uint32_t)bus));  
}

/** 
 * \brief The function reserve for the lib_power.lib 
 */
void Chip_SYSCON_PowerUp (uint32_t powerupmask)
{
    /* 
     * If turning the PLL back on, perform the following sequence to 
     * accelerate PLL lock.
     */
    if (powerupmask & AMHW_SYSCON_PD_SYS_PLL) {
        volatile uint32_t delay_x;
        
        uint32_t max_cco    = (1 << 18) | 0x3fff;
        uint32_t cur_ssctrl = AMHW_SYSCON->syspllssctrl0;

        /* If NOT using spread spectrum mode */
        if (cur_ssctrl & (1 << 18)) {

            /* Turn on PLL */
            AMHW_SYSCON->pdruncfgclr = AMHW_SYSCON_PD_SYS_PLL;
            
            /* 
             * this sequence accelerate the PLL lock time 
             */
            AMHW_SYSCON->syspllssctrl0 = max_cco | (1 << 17); /* Set mreq to activate */
            
            /* clear mreq to prepare for restoring mreq */
            AMHW_SYSCON->syspllssctrl0 = max_cco; 

            /* Delay for 20 uSec @ 12Mhz*/
            for (delay_x = 0; delay_x < 48; ++delay_x) {}

            /* set original value back with mreq */
            AMHW_SYSCON->syspllssctrl0 = cur_ssctrl | (1 << 17);
        }
    }

    /* Enable peripheral states by setting low */
    AMHW_SYSCON->pdruncfgclr = powerupmask;
}

/* end of file */

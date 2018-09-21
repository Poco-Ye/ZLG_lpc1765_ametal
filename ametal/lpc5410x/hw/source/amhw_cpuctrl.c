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
 * \brief CPU control implementation for operating hardware.
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-08  jon, first implementation.
 * \endinternal
 */

#include "amhw_cpuctrl.h"
#include "amhw_syscon.h" 

/**
 * \brief Determine which MCU this code is running on
 */
bool_t amhw_cpu_is_m4core (void) 
{
    
    /* M4 core is designated by values 0xC24 on bits 15..4 */
    if (((SCB->CPUID >> 4) & 0xFFF) == 0xC24) {
        return TRUE;
    }

    return FALSE;
}

/**
 * \brief Determine if this core is a slave or master
 */
bool_t amhw_cpu_is_master_core (void)
{
    if ((AMHW_SYSCON->cpuctrl & 0x01) != 0) {
        return TRUE;
    }
    
    return FALSE;
}

/**
 * \brief Set up M0+ boot and reset M0+ core
 */
static void __cpu_m0p_boot (uint32_t *p_entry, uint32_t *p_stack)
{
    uint32_t temp;

    /* Set up M0+ stack and M0+ boot location */
    AMHW_SYSCON->cpstack = (uint32_t)p_stack;
    AMHW_SYSCON->cpboot  = (uint32_t)p_entry;

    temp = AMHW_SYSCON->cpuctrl | 0xc0c40000 | AMHW_CM0_CLK_ENABLE; 

    /* Enable M0+ clocking with reset asserted */
    AMHW_SYSCON->cpuctrl = temp | AMHW_CM0_RESET_ENABLE;

    /* De-assert reset on M0+ */
    AMHW_SYSCON->cpuctrl = temp;
}

/**
 * \brief Use for the cortex-m4 start up the cortex-m0+
 */
void amhw_cpu_boot_m0p (uint32_t m0p_entryaddr)
{
    uint32_t *p_jumpdddr, *p_stackaddr;

    /* 
     * Boot M0 core, using reset vector and stack pointer from the CM0+
     * image in FLASH. 
     */
    p_stackaddr = (uint32_t *)(*(uint32_t *) m0p_entryaddr);
    p_jumpdddr  = (uint32_t *)(*(uint32_t *)(m0p_entryaddr + 4));
    
    __cpu_m0p_boot(p_jumpdddr, p_stackaddr);
}

/* end of file */


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
 * \brief LPC5410X memory allocation for Cortex-M0+ and Cortex-M4
 *
 * \note LPC5410X memory Memory mapping:
 *           - FLASH: 0x0000 0000  ~  0x0008 0000  (total 512KB)
 *           - SRAM0: 0x0200 0000  ~  0x0201 0000  (total 64KB )
 *           - SRAM1: 0x0201 0000  ~  0x0201 8000  (total 32KB )
 *           - SRAM2: 0x0340 0000  ~  0x0340 2000  (total 8KB  )
 * \internal
 * \par History
 * - 1.00 14-12-11  tee, first implementation.
 * \endinternal
 */

#ifndef __LPC5410X_CONFIG_MEMORY_H
#define __LPC5410X_CONFIG_MEMORY_H

/**
 * \name The macro defines for memory size (KB)
 *
 * The user can change according to actual condition
 */
#define LPC5410X_CFG_MEM_FLASH_CM4_SIZE    128  /**< \breif FLASH for M4 ,128KB    */
#define LPC5410X_CFG_MEM_FLASH_CM0_SIZE    128  /**< \breif FLASH for M0+,128KB    */

#define LPC5410X_CFG_MEM_SRAM_CM4_SIZE      64  /**< \breif SRAM for M4 , 64KB     */
#define LPC5410X_CFG_MEM_SRAM_CM0_SIZE      32  /**< \breif SRAM for M0+ ,32KB     */

/** @} */

/**
 * \name The macro defines for memory distribution 
 *
 * The user shouldn't change
 * @{
 */
#define  LPC5410X_CFG_MEM_FLASH_CM4_START    0x00000000
#define  LPC5410X_CFG_MEM_FLASH_CM4_LEN     (LPC5410X_CFG_MEM_FLASH_CM4_SIZE * 1024)

#define  LPC5410X_CFG_MEM_FLASH_CM0_START   \
            (LPC5410X_CFG_MEM_FLASH_CM4_START + LPC5410X_CFG_MEM_FLASH_CM4_LEN)
            
#define  LPC5410X_CFG_MEM_FLASH_CM0_LEN     (LPC5410X_CFG_MEM_FLASH_CM0_SIZE * 1024)    

#define  LPC5410X_CFG_MEM_SRAM_CM4_START     0x02000000
#define  LPC5410X_CFG_MEM_SRAM_CM4_LEN      (LPC5410X_CFG_MEM_SRAM_CM4_SIZE * 1024)

#define  LPC5410X_CFG_MEM_SRAM_CM0_START    \
            (LPC5410X_CFG_MEM_SRAM_CM4_START + LPC5410X_CFG_MEM_SRAM_CM4_LEN)
            
#define  LPC5410X_CFG_MEM_SRAM_CM0_LEN      (LPC5410X_CFG_MEM_SRAM_CM0_SIZE * 1024)

/** @} */
  
#endif  /* __LPC5410X_CONFIG_MEMORY_H */

/* end of file */

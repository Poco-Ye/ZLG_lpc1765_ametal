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
 * \brief In-Application programming (IAP) implementation for operating hardware.
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */
 
#include "amhw_iap.h"

/*******************************************************************************
  Public functions
*******************************************************************************/

/**
 * \brief Prepare sector for write operation
 */
amhw_iap_stat_t amhw_iap_prepare (uint32_t start_sec, uint32_t end_sec)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_PREPARE;
    command[1] = start_sec;
    command[2] = end_sec;
    
    amhw_iap_entry(command, result);

    return (amhw_iap_stat_t)result[0];
}

/**
 * \brief Copy RAM to flash
 */
amhw_iap_stat_t amhw_iap_copy (uint32_t dst_addr, 
                               uint32_t src_addr, 
                               uint32_t nbytes,
                               uint32_t clkfreq)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_COPY_RAM_TO_FLASH;
    command[1] = dst_addr;
    command[2] = (uint32_t)src_addr;
    command[3] = nbytes;
    command[4] = clkfreq / 1000;
    
    amhw_iap_entry(command, result);

    return (amhw_iap_stat_t)result[0];
}

/**
 * \brief Erase sector
 */
amhw_iap_stat_t amhw_iap_erase_sector (uint32_t start_sec, 
                                       uint32_t end_sec, 
                                       uint32_t clkfreq)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_ERASE_SECTOR;
    command[1] = start_sec;
    command[2] = end_sec;
    command[3] = clkfreq / 1000;
    
    amhw_iap_entry(command, result);

    return (amhw_iap_stat_t)result[0];
}

/**
 * \brief Erase page
 */
amhw_iap_stat_t amhw_iap_erase_page (uint32_t start_page, 
                                     uint32_t end_page, 
                                     uint32_t clkfreq)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_ERASE_PAGE;
    command[1] = start_page;
    command[2] = end_page;
    command[3] = clkfreq / 1000;
    
    amhw_iap_entry(command, result);

    return (amhw_iap_stat_t)result[0];
}

/**
 * \brief Blank check sector
 */
uint8_t amhw_iap_blank_check (uint32_t start_sec, uint32_t end_sec)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_BLANK_CHECK;
    command[1] = start_sec;
    command[2] = end_sec;
    
    amhw_iap_entry(command, result);

    return result[0];
}

/**
 * \brief Read part identification number
 */
uint32_t amhw_iap_part_id_read (void)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_PARTID_READ;
    
    amhw_iap_entry(command, result);

    return result[1];
}

/**
 * \brief Read boot code version number 
 */
uint16_t amhw_iap_boot_ver_read (void)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_BOOT_VER_READ;
    
    amhw_iap_entry(command, result);

    return result[1];
}

/**
 * \brief IAP compare
 */
uint8_t amhw_iap_compare (uint32_t dst_addr, uint32_t src_addr, uint32_t nbytes)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_COMPARE;
    command[1] = dst_addr;
    command[2] = src_addr;
    command[3] = nbytes;
    
    amhw_iap_entry(command, result);

    return result[0];
}

/**
 * \brief Reinvoke ISP
 */
void amhw_iap_reinvoke_isp (void)
{
    uint32_t command[5], result[4];

    command[0] = AMHW_IAP_CMD_REINVOKE_ISP;
    
    amhw_iap_entry(command, result);
}

/**
 * \brief Read the unique ID
 */
amhw_iap_stat_t amhw_iap_unique_id_read (uint32_t uid[4])
{
    uint32_t command[5], result[5];

    command[0] = AMHW_IAP_CMD_READ_UID;
    
    amhw_iap_entry(command, result);
    
    uid[0] = result[1];
    uid[1] = result[2];
    uid[2] = result[3];
    uid[3] = result[4];

    return (amhw_iap_stat_t)result[0];
}

/**
 * \brief Read the Read Signature
 */
uint32_t amhw_iap_signature_read (void)
{
    uint32_t command[5], result[5];

    command[0] = AMHW_IAP_CMD_SIGNATURE_READ;
    
    amhw_iap_entry(command, result);
    
    return result[1];
}

/* end of file */

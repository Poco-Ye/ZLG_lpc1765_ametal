/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief CRC例程，通过HW层的接口实现
 *
 * - 实验现象：
 *   1. 串口输出CRC计算结果；
 *   2. LED以0.5s的时间间隔闪烁。
 * 
 * \par 源代码
 * \snippet demo_hw_crc.c src_hw_crc 
 * 
 * \internal
 * \par Modification History
 * - 1.00 14-12-09  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_hw_crc
 * \copydoc demo_hw_crc.c
 */
 
/** [src_hw_crc] */
#include "ametal.h"
#include "am_board.h"


/** \brief CRC测试数据 */
char data_test[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

/** \brief CRC测试数据的长度 */
uint32_t length_test = sizeof(data_test) / sizeof(data_test[0]);

/**
 * \brief CRC-CCITT 计算
 * \param[in] p_data  : 指向CRC计算数据缓冲区的指针。
 * \param[in] nbytes  : 计算数据的长度。
 * \return  CRC-CCITT计算的结果。
 */
uint16_t crc_ccitt (const uint8_t *p_data, uint32_t nbytes)
{
    /* 没有标志需要置位，标志值为0 */
    amhw_crc_mode_set(AMHW_CRC, AMHW_CRC_POLY_CCITT, 0);    
    
    amhw_crc_seed_set(AMHW_CRC, 0xFFFF);
    
    amhw_crc_data8_write(AMHW_CRC, p_data, nbytes);
    
    return amhw_crc_sum_get(AMHW_CRC);
}

/**
 * \brief CRC-16 计算
 * \param[in] p_data  : 指向CRC计算数据缓冲区的指针。
 * \param[in] nbytes  : 计算数据的长度。
 * \return  CRC-16计算的结果。
 */
uint16_t crc_16 (const uint8_t *p_data, uint32_t nbytes)
{
   
    amhw_crc_mode_set(AMHW_CRC, 
                      AMHW_CRC_POLY_CRC16, 
                      AMHW_CRC_MODE_WRDATA_BIT_RVS | 
                      AMHW_CRC_MODE_SUM_BIT_RVS);    
    
    amhw_crc_seed_set(AMHW_CRC, 0x0000);
    
    amhw_crc_data8_write(AMHW_CRC, p_data, nbytes);
    
    return amhw_crc_sum_get(AMHW_CRC);
}

/**
 * \brief  CRC-32计算
 * \param[in] p_data  : 指向CRC计算数据缓冲区的指针。
 * \param[in] nbytes  : 计算数据的长度。
 * \return  CRC-32计算的结果。
 */
uint32_t crc_32 (const uint8_t *p_data, uint32_t nbytes)
{
   
    amhw_crc_mode_set(AMHW_CRC, 
                      AMHW_CRC_POLY_CRC32, 
                      AMHW_CRC_MODE_WRDATA_BIT_RVS | 
                      AMHW_CRC_MODE_SUM_BIT_RVS    |
                      AMHW_CRC_MODE_SUM_CMPL);    
    
    amhw_crc_seed_set(AMHW_CRC, 0xFFFFFFFF);
    
    amhw_crc_data8_write(AMHW_CRC, p_data, nbytes);
    
    return amhw_crc_sum_get(AMHW_CRC);
}

/**
 * \brief 主函数入口
 */
int main (void)
{   
    uint16_t result_crc16;
    uint16_t result_crc_ccitt;
    uint32_t result_crc32;
    
    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_crc_init();
    
    /* 计算结果应为：0xbb3d     */
    result_crc16 = crc_16((const uint8_t *)data_test, length_test);
    AM_DBG_INFO("CRC-16 result is     : 0x%x \r\n", result_crc16);
 
    /* 计算结果应为：0x29b1     */
    result_crc_ccitt = crc_ccitt((const uint8_t *)data_test, length_test);
    AM_DBG_INFO("CRC-CCITT result is  : 0x%x \r\n", result_crc_ccitt);
    
    /* 计算结果应为：0xcbf43926 */
    result_crc32 = crc_32((const uint8_t *)data_test, length_test);
    AM_DBG_INFO("CRC-32 result is     : 0x%x \r\n", result_crc32);
    
    while (1) {     
        
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}

/** [src_hw_crc] */

/* end of file */

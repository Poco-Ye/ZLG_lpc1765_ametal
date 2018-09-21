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
 * \brief CRC例程，通过标准接口实现
 *
 * - 实验现象：
 *   1. 串口输出CRC计算结果；
 *   2. LED以0.5s的时间间隔闪烁。
 * 
 * \par 源代码
 * \snippet demo_std_crc.c src_std_crc 
 * 
 * \internal
 * \par Modification History
 * - 1.00 15-01-19  tee, first implementation.
 * \endinternal
 */ 

/**
 * \addtogroup demo_if_std_crc
 * \copydoc demo_std_crc.c
 */

/** [src_std_crc] */
#include "ametal.h"
#include "am_board.h"

/** \brief CRC测试数据 */
const uint8_t data_test[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

/** \brief CRC测试数据的长度 */
uint32_t length_test = sizeof(data_test) / sizeof(data_test[0]);

/**
 * \brief 主函数入口
 */
int main (void)
{  
    am_crc_handle_t crc_handle;
    uint32_t        crc_result;
    
    /* 定义CRC-16模型 */
    am_crc_pattern_t crc_pattern = {
        16,          /* CRC宽度(如：CRC5 的宽度为 5)           */
        0x8005,      /* CRC生成多项式                          */
        0x0000,      /* CRC初始值                              */
        TRUE,        /* 如果输入数据需要位反转，则该值为TRUE   */
        TRUE,        /* 如果输出结果值需要位反转，则该值为TRUE */
        0x0000,      /* 输出异或值                             */
    };

    /* 板级初始化 */
    am_board_init();

    /* 平台初始化 */
    amhw_plfm_crc_init();
    
    crc_handle = amdr_crc_init(&g_crc_dev, 
                               &g_crc_devinfo);
    
    /* 初始化CRC为CRC-16模型 */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-16 init failed\r\n");
    } else {
        am_crc_cal(crc_handle, data_test, length_test);
        am_crc_final(crc_handle, &crc_result);
        
        /* 计算结果应为：0xbb3d     */
        AM_DBG_INFO("CRC-16 result is        : 0x%x \r\n", crc_result);
    }
    
    /* 改变模型为CRC-CCITT模型 */
    
    crc_pattern.width     = 16;
    crc_pattern.poly      = 0x1021;
    crc_pattern.initvalue = 0xFFFF;
    crc_pattern.refin     = FALSE;
    crc_pattern.refout    = FALSE;
    crc_pattern.xorout    = 0x0000;
    
    /* 初始化CRC为CRC-CCITT模型 */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-ccitt init failed\r\n");
    
    } else {
        am_crc_cal(crc_handle, data_test, length_test);
        am_crc_final(crc_handle, &crc_result);
        
        /* 计算结果应为：0x29b1     */
        AM_DBG_INFO("CRC-CCITT result is     : 0x%x \r\n", crc_result);
    }
    
    /* 改变模型为CRC-32模型 */
    crc_pattern.width     = 32;
    crc_pattern.poly      = 0x04C11DB7;
    crc_pattern.initvalue = 0xFFFFFFFF;
    crc_pattern.refin     = TRUE;
    crc_pattern.refout    = TRUE;
    crc_pattern.xorout    = 0xFFFFFFFF;

    /* 初始化CRC为CRC-32模型 */
    if (am_crc_init(crc_handle, &crc_pattern) != AM_OK) {
        AM_DBG_INFO("The crc-32 init failed\r\n");
    
    } else {
        am_crc_cal(crc_handle, data_test, length_test);
        am_crc_final(crc_handle, &crc_result);
        
        /* 计算结果应为：0xcbf43926     */
        AM_DBG_INFO("CRC-32 result is        : 0x%x \r\n", crc_result);
    }
    
    while (1) {
        am_led_toggle(LED0);
        am_mdelay(500);
    }
}

/** [src_std_crc] */

/* end of file */

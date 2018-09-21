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
 * \brief CRC驱动，服务CRC标准接口
 *
 * 本CRC驱动支持3种CRC模型：
 * 
 * 1. width     = 16; \n
 *    poly      = 0x1021; \n
 *    initvalue = 可以是任意值; \n
 *    refin     = TRUE 或者 FALSE; \n
 *    refout    = TRUE 或者 FALSE; \n
 *    xorout    = 0x0000 或者 0xFFFF; \n
 * 2. width     = 16; \n
 *    poly      = 0x8005; \n
 *    initvalue = 可以是任意值; \n
 *    refin     = TRUE 或者 FALSE; \n
 *    refout    = TRUE 或者 FALSE; \n
 *    xorout    = 0x0000 或者 0xFFFF; \n
 * 3. width     = 32; \n
 *    poly      = 0x04C11DB7; \n
 *    initvalue = 可以是任意值; \n
 *    refin     = TRUE 或者 FALSE; \n
 *    refout    = TRUE 或者 FALSE; \n
 *    xorout    = 0x00000000 或者 0xFFFFFFFF; \n
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-19  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_CRC_H
#define __AMDR_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_crc.h"
#include "amhw_crc.h"

/**
 * \addtogroup amdr_if_crc
 * \copydoc amdr_crc.h
 * @{
 */

/**
 * \brief CRC设备信息结构体
 */
typedef struct amdr_crc_devinfo {
    amhw_crc_t   *p_hw_crc;               /**< \brief 指向CRC寄存器块的指针   */
} amdr_crc_devinfo_t;
    
/**
 * \brief CRC设备结构体
 */
typedef struct amdr_crc_dev {

    am_crc_serv_t              crc_serv;  /**< \brief 标准CRC服务               */
    am_crc_pattern_t          *p_patern;  /**< \brief 指向CRC模型的指针         */
    const amdr_crc_devinfo_t  *p_devinfo; /**< \brief 指向CRC设备信息常量的指针 */

} amdr_crc_dev_t;

/**
 * \brief 初始化CRC
 *
 * \param[in] p_dev     : 指向CRC设备的指针
 * \param[in] p_devinfo : 指向CRC设备信息常量的指针
 *
 * \return CRC标准服务操作句柄，值为NULL时表明初始化失败
 */
am_crc_handle_t amdr_crc_init(amdr_crc_dev_t            *p_dev,
                              const amdr_crc_devinfo_t  *p_devinfo);

/**
 * \brief 不使用CRC时，解初始化CRC，释放相关资源
 * \param[in] p_dev : 指向CRC设备的指针
 * \return 无
 */
void amdr_crc_deinit(amdr_crc_dev_t *p_dev);

/** 
 * @}  
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_CRC_H */

/* end of file */

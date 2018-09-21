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
 * \brief IAP(In-Application programming)操作接口
 *
 * IAP通过调用ROM中的函数实现,包括了扇区擦除、FLASH读写等操作.
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_IAP_H
#define __AMHW_IAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_lpc5410x.h"

/**
 * \addtogroup amhw_if_iap
 * \copydoc amhw_iap.h
 * @{
 */

/** IAP 的ROM API函数类型定义 */
typedef void (*amhw_iap_entry_t)(unsigned int[], unsigned int[]);

/**
 * \name IAP指令宏定义
 * @{
 */

#define AMHW_IAP_CMD_PREPARE             50  /**< \brief 扇区准备指令         */
#define AMHW_IAP_CMD_COPY_RAM_TO_FLASH   51  /**< \brief 从RAM复制内容至FLASH */
#define AMHW_IAP_CMD_ERASE_SECTOR        52  /**< \brief 扇区擦除指令         */
#define AMHW_IAP_CMD_BLANK_CHECK         53  /**< \brief 扇区查空指令         */
#define AMHW_IAP_CMD_PARTID_READ         54  /**< \brief 读 PartID 指令       */
#define AMHW_IAP_CMD_BOOT_VER_READ       55  /**< \brief 读 Boot code 版本号  */
#define AMHW_IAP_CMD_COMPARE             56  /**< \brief 数据比较指令         */
#define AMHW_IAP_CMD_REINVOKE_ISP        57  /**< \brief 重新进入ISP模式      */
#define AMHW_IAP_CMD_READ_UID            58  /**< \brief 读UID指令            */
#define AMHW_IAP_CMD_ERASE_PAGE          59  /**< \brief 页擦除指令           */
#define AMHW_IAP_CMD_SIGNATURE_READ      70  /**< \brief 读Signature 指令     */

/** @} */

/**
 * \brief IAP操作状态定义
 */
typedef enum amhw_iap_stat {
    AMHW_IAP_STAT_SUCCESS      = 0,    /**< \brief 指令执行成功               */
    AMHW_IAP_STAT_INVALID_CMD,         /**< \brief 非法指令                   */
    AMHW_IAP_STAT_SRC_ADDR_ERROR,      /**< \brief 源地址不是按字对齐         */
    AMHW_IAP_STAT_DST_ADDR_ERROR,      /**< \brief 目标地址没有正确的地址对齐 */
    AMHW_IAP_STAT_SRC_ADDR_NOT_MAPPED, /**< \brief 源地址不在内存映射中       */
    AMHW_IAP_STAT_DST_ADDR_NOT_MAPPED, /**< \brief 目标地址不在内存映射中     */
    AMHW_IAP_STAT_COUNT_ERROR,         /**< \brief 字节个数值错误             */
    AMHW_IAP_STAT_INVALID_SECTOR,      /**< \brief 扇区值错误                 */
    AMHW_IAP_STAT_SECTOR_NOT_BLANK,    /**< \brief 扇区非空                   */
    AMHW_IAP_STAT_SECTOR_NOT_PREPARED, /**< \brief 扇区准备指令没有执行       */
    AMHW_IAP_STAT_COMPARE_ERROR,       /**< \brief 源地址和目标地址数据不同   */
    AMHW_IAP_STAT_BUSY,                /**< \brief FLASH编程接口忙            */
} amhw_iap_stat_t;


/**
 * \brief 该函数用于直接调用ROM API函数
 *
 * \param[in]  cmd_param     : 指令相关数据
 * \param[out] status_result : 指令执行结果的相关数据
 *
 * \return 无
 */
am_static_inline
void amhw_iap_entry (unsigned int cmd_param[], unsigned int status_result[])
{
    ((amhw_iap_entry_t) AMHW_IAP_ENTRY_LOCATION)(cmd_param, status_result);
}

/**
 * \brief 写操作前的扇区准备函数
 *
 * \param[in] start_sec : 起始扇区号
 * \param[in] end_sec   : 结束扇区号
 *
 * \return IAP指令执行的状态
 *
 * \note 结束扇区号必须大于或等于起始扇区号
 *
 */
amhw_iap_stat_t amhw_iap_prepare(uint32_t start_sec, uint32_t end_sec);

/**
 * \brief 复制RAM中数据至FLASH中，相当于FLASH写操作
 *
 * \param[in] dst_addr : 目标FLASH地址，应该以 256 字节对齐
 * \param[in] src_addr : 数据源RAM的地址，应该以字对齐
 * \param[in] nbytes   : 复制的数据个数, 应该是 256、512 、1024 或者 4096
 * \param[in] clkfreq  : 系统时钟频率(单位：Hz)
 *
 * \return IAP指令执行的状态
 *
 * \note 该函数操作到的FLASH扇区必须在调用该函数前调用amhw_iap_prepare()函数进行
 *       写入准备操作
 */
amhw_iap_stat_t amhw_iap_copy(uint32_t dst_addr,
                              uint32_t src_addr,
                              uint32_t nbytes,
                              uint32_t clkfreq);

/**
 * \brief 扇区擦除
 *
 * \param[in] start_sec : 起始扇区号
 * \param[in] end_sec   : 结束扇区号
 * \param[in] clkfreq   : 系统时钟频率(单位：Hz)
 *
 * \return IAP指令执行的状态
 *
 * \note 结束扇区号必须大于或等于起始扇区号，该函数操作到的FLASH扇区必须在调用该
 *       函数前调用amhw_iap_prepare()函数进行准备操作
 */
amhw_iap_stat_t amhw_iap_erase_sector(uint32_t start_sec,
                                      uint32_t end_sec,
                                      uint32_t clkfreq);

/**
 * \brief 页擦除，单页或多页擦除
 *
 * \param[in] start_page : 起始页号
 * \param[in] end_page   : 结束页号
 * \param[in] clkfreq    : 系统时钟频率(单位：Hz)
 *
 * \return IAP指令执行的状态
 *
 * \note 结束页号必须大于或等于起始页号，该函数操作到的FLASH扇区必须在调用该
 *       函数前调用amhw_iap_prepare()函数进行准备操作
 */
amhw_iap_stat_t amhw_iap_erase_page(uint32_t start_page,
                                    uint32_t end_page,
                                    uint32_t clkfreq);

/**
 * \brief 单个扇区或多个扇区查空
 *
 * \param[in] start_sec : 起始扇区号
 * \param[in] end_sec   : 结束扇区号
 *
 * \return IAP指令执行的状态，执行如果成功(AMHW_IAP_STAT_SUCCESS)表明扇区为空。
 *
 * \note 结束扇区号必须大于或等于起始扇区号
 */
amhw_iap_stat_t amhw_iap_blank_check(uint32_t start_sec, uint32_t end_sec);

/**
 * \brief 读Part ID值
 * \return Part ID值
 */
uint32_t amhw_iap_part_id_read(void);

/**
 * \brief 读boot code版本号
 * \return boot code版本号, 版本号格式：<字节1(主版本号)>.<字节0(次版本号)>
 */
uint16_t amhw_iap_boot_ver_read(void);

/**
 * \brief 比较两处内存中的数据
 *
 * \param[in] dst_addr : 数据比较的数据目标地址，可以是FLASH地址或者RAM地址
 * \param[in] src_addr : 数据比较的数据源地址，可以是FLASH地址或者RAM地址
 * \param[in] nbytes   : 数据比较的个数
 *
 * \return IAP指令执行的状态
 *
 * \note 地址应该以字对齐，字节个数应该是4的整数倍
 */
amhw_iap_stat_t amhw_iap_compare(uint32_t dst_addr,
                                 uint32_t src_addr,
                                 uint32_t nbytes);

/**
 * \brief 通过IAP将 boot loader重新切换到ISP模式
 * \return 无
 */
void amhw_iap_reinvoke_isp(void);

/**
 * \brief 读器件的UID(共128位)
 * \param[out] uid :
 *              - uid[0] : 第一个32位数据 (最低地址，最低位0~31）
 *              - uid[1] : 第二个32位数据
 *              - uid[2] : 第三个32位数据
 *              - uid[3] : 第四个32位数据
 * \return IAP指令执行的状态
 */
amhw_iap_stat_t amhw_iap_unique_id_read(uint32_t uid[4]);

/**
 * \brief 读 signature(FLASH 签名) 值
 * \return 32位signature值
 */
uint32_t amhw_iap_signature_read(void);

/**
 * @} amhw_if_iap
 */

#ifdef __cplusplus
}
#endif

#endif

/* end of files */

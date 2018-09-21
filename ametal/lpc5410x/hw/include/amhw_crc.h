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
 * \brief 循环冗余校验(CRC) 操作接口
 *
 * 1. 支持3种CRC生成多项式： CRC-CCITT, CRC-16, and CRC-32
 *    - CRC-CCITT : x16 + x12 + x5 + 1   (0x1021);
 *    - CRC-16    : x16 + x15 + x2 + 1   (0x8005);
 *    - CRC-32    : x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 +
 *                   x5 + x4 + x2+ x + 1  (0x04C11DB7);
 * 2. 支持输入数据和CRC校验和的位反序和1's补码;
 * 3. 可编程种子数据设置;
 * 4. 支持 PIO back-to-back 传输方式;
 * 5. 支持三种数据宽度的输入数据: 8位、16位和32位
 *    - 8 位数据写入: 运行1个周期;
 *    - 16位数据写入: 运行2个周期;
 *    - 32位数据写入: 运行4个周期。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_CRC_H
#define __AMHW_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_crc
 * \copydoc amhw_crc.h
 * @{
 */

/*
 * \brief 匿名结构体段的开始
 */
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/**
 * \brief CRC 寄存器块结构体
 */
typedef struct amhw_crc {
    __IO    uint32_t    mode;           /**< \brief CRC 模式寄存器            */
    __IO    uint32_t    seed;           /**< \brief CRC 种子寄存器            */
    union {
        __I     uint32_t    sum;        /**< \brief CRC 校验寄存器            */
        __O     uint32_t    wrdata32;   /**< \brief CRC 写数据寄存器（32位写）*/
        __O     uint16_t    wrdata16;   /**< \brief CRC 写数据寄存器（16位写）*/
        __O     uint8_t     wrdata8;    /**< \brief CRC 写数据寄存器（8位写） */
    };
} amhw_crc_t;


/**
 * \name CRC模式定义
 * @{
 */

#define AMHW_CRC_MODE_WRDATA_BIT_RVS (1 << 2)  /**< \brief 输入数据位反序             */
#define AMHW_CRC_MODE_WRDATA_CMPL    (1 << 3)  /**< \brief 输入数据进行1's补码运算    */
#define AMHW_CRC_MODE_SUM_BIT_RVS    (1 << 4)  /**< \brief 输出CRC值位反序            */
#define AMHW_CRC_MODE_SUM_CMPL       (1 << 5)  /**< \brief 输出CRC值时进行1's补码运算 */

/** @} */

/**
 * \brief CRC生成多项式定义
 */
typedef enum amhw_crc_poly {
    AMHW_CRC_POLY_CCITT = 0,              /**< \brief CRC-CCIT 多项式   */
    AMHW_CRC_POLY_CRC16 = 1,              /**< \brief CRC-16   多项式   */
    AMHW_CRC_POLY_CRC32 = 2,              /**< \brief CRC-32   多项式   */
} amhw_crc_poly_t;


/**
 * \brief 设置CRC模式和生成多项式
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] poly     : CRC的生成多项式
 * \param[in] flags    : AMHW_CRC_MODE_*宏值或多个AMHW_CRC_MODE_*宏的或值
 *                        - #AMHW_CRC_MODE_WRDATA_BIT_RVS
 *                        - #AMHW_CRC_MODE_WRDATA_CMPL
 *                        - #AMHW_CRC_MODE_SUM_BIT_RVS
 *                        - #AMHW_CRC_MODE_SUM_CMPL
 *                       如果没有标志设置，则该值为0.
 *
 * \return 无
 */
am_static_inline
void amhw_crc_mode_set (amhw_crc_t     *p_hw_crc,
                        amhw_crc_poly_t poly,
                        uint32_t        flags)
{
    p_hw_crc->mode = (uint32_t)poly | flags;
}

/**
 * \brief 获取CRC模式寄存器值
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \return 当前CRC模式寄存器值
 */
am_static_inline
uint32_t amhw_crc_mode_get (amhw_crc_t *p_hw_crc)
{
    return p_hw_crc->mode;
}

/**
 * \brief 设置CRC种子值
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] seed     : CRC种子值
 *
 * \return 无
 */
am_static_inline
void amhw_crc_seed_set (amhw_crc_t *p_hw_crc, uint32_t seed)
{
    p_hw_crc->seed = seed;
}


/**
 * \brief 获取CRC种子值
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \return CRC种子值
 */
am_static_inline
uint32_t amhw_crc_seed_get (amhw_crc_t *p_hw_crc)
{
    return p_hw_crc->seed;
}

/**
 * \brief 写入1个8位数据至CRC引擎进行CRC计算
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] data     : 写入的8位数据
 *
 * \return 无
 */
am_static_inline
void amhw_crc_wrdata8 (amhw_crc_t *p_hw_crc, uint8_t data)
{
    p_hw_crc->wrdata8 = data;
}

/**
 * \brief 写入1个16位数据至CRC引擎进行CRC计算
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] data     : 写入的16位数据
 *
 * \return 无
 */
am_static_inline
void amhw_crc_wrdata16 (amhw_crc_t *p_hw_crc, uint16_t data)
{
    p_hw_crc->wrdata16 = data;
}

/**
 * \brief 写入1个32位数据至CRC引擎进行CRC计算
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] data     : 写入的32位数据
 *
 * \return 无
 */
am_static_inline
void amhw_crc_wrdata32 (amhw_crc_t *p_hw_crc, uint32_t data)
{
    p_hw_crc->wrdata32 = data;
}

/**
 * \brief 写入n个8位数据至CRC引擎进行CRC计算
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] p_data   : 指向待进行CRC计算的输入数据缓冲区(8位数据缓冲区)
 * \param[in] nbytes   : 8位数据的个数
 *
 * \return 无
 */
void amhw_crc_data8_write(amhw_crc_t    *p_hw_crc,
                          const uint8_t *p_data,
                          uint32_t       nbytes);

/**
 * \brief 写入n个16位数据至CRC引擎进行CRC计算
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] p_data   : 指向待进行CRC计算的输入数据缓冲区(16位数据缓冲区)
 * \param[in] nhwords  : 16位数据的个数
 *
 * \return 无
 */
void amhw_crc_data16_write(amhw_crc_t     *p_hw_crc,
                           const uint16_t *p_data,
                           uint32_t        nhwords);


/**
 * \brief 写入n个32位数据至CRC引擎进行CRC计算
 *
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \param[in] p_data   : 指向待进行CRC计算的输入数据缓冲区(32位数据缓冲区)
 * \param[in] nwords   : 32位数据的个数
 *
 * \return 无
 */
void amhw_crc_data32_write(amhw_crc_t     *p_hw_crc,
                           const uint32_t *p_data,
                           uint32_t        nwords);

/**
 * \brief 获取CRC计算结果值
 * \param[in] p_hw_crc : 指向CRC寄存器块的指针
 * \return CRC计算结果值
 */
am_static_inline
uint32_t amhw_crc_sum_get (amhw_crc_t *p_hw_crc)
{
    return p_hw_crc->sum;
}

/*
 * \brief 匿名结构体段的结束
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
#elif defined(__GNUC__)
#elif defined(__TMS470__)
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_CRC_H */

/* end of file */

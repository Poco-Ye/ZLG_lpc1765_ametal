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
* e-mail:      apollo.support\zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief I/O 引脚配置 (IOCON) 硬件操作接口
 * 
 * 以下为对标准端口引脚有关电学特性的配置：
 *  - 上拉/下拉；
 *  - 开漏模式；
 *  - 翻转功能；
 *  - 引脚 PIO0_23 到 PIO0_28 是开漏引脚，可配置为不同的I2C总线速度。
 * 
 * \internal
 * \par Modification History
 * - 1.01 14-12-06  hbt, amend.
 * - 1.00 14-11-03  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_IOCON_H
#define __AMHW_IOCON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
    
 /** 
 * \addtogroup amhw_if_iocon
 * \copydoc amhw_iocon.h
 * @{
 */


/**
  * \brief LPC5410x IOCON 寄存器块结构体
 */
typedef struct amhw_iocon {
    __IO uint32_t  pio[2][32];       /**< \brief 数字 I/O 控制寄存器 */
} amhw_iocon_t;


/**
 * \brief I/O 功能和模式配置
 *
 * \param[in] p_hw_iocon : 指向IOCON寄存器块的指针
 * \param[in] pin        : 引脚编号，值为 PIO* (#PIO0_0).
 * \param[in] flags      : 配置参数
 *
 * \return    无
 */
am_local am_inline 
void amhw_iocon_cfg (amhw_iocon_t *p_hw_iocon, int pin, uint32_t flags)
{
    p_hw_iocon->pio[pin >> 5][(pin & 0x1F)] = flags;
}


/**
 * @} amhw_if_iocon
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_IOCON_H */

/* end of file */

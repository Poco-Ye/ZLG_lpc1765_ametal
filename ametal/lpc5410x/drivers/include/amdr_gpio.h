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
 * \brief GPIO驱动，服务GPIO标准接口
 *
 * \internal
 * \par Modification history
 * - 1.10 14-12-15  hbt, modified interfaces.
 * - 1.00 14-12-02  tee, first implementation.
 * \endinternal
 */

#ifndef __AMDR_GPIO_H
#define __AMDR_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"  
#include "am_bitops.h"

#include "lpc5410x_pin.h"
#include "amhw_gpio.h"
#include "amhw_iocon.h"
#include "amhw_inmux.h"
#include "amhw_pint.h"

/** 
 * \addtogroup amdr_if_gpio
 * \copydoc amdr_gpio.h
 * @{
 */

/**
 * \brief 引脚的触发信息 
 */
struct amdr_gpio_trigger_info {

    /** \brief 触发回调函数 */
    am_pfnvoid_t  pfn_callback;

    /** \brief 回调函数的参数 */
    void *p_arg;
};

/**
 * \brief GPIO 设备信息
 */
typedef struct amdr_gpio_devinfo {
    
    /** \brief 指向GPIO寄存器块的指针 */
    amhw_gpio_t  *p_hw_gpio;
    
    /** \brief 指向IOCON寄存器块的指针 */
    amhw_iocon_t *p_hw_iocon;

    /** \brief 指向引脚中断寄存器块的指针 */
    amhw_pint_t  *p_hw_pint;

    /** \brief 指向输入复用寄存器块的指针 */
    amhw_inmux_t *p_hw_inmux;

    /** \brief GPIO引脚中断号列表 */
    const int8_t inum_pin[PIN_INT_MAX];

    /** \brief GPIO支持的引脚中断号数量 */
    size_t       pint_count;

    /** \brief 触发信息映射 */
    uint8_t     *p_infomap;

    /** \brief 指向引脚触发信息的指针 */
    struct amdr_gpio_trigger_info *p_triginfo;
    
} amdr_gpio_devinfo_t;

/**
 * \brief GPIO设备实例 
 */
typedef struct amdr_gpio_dev {
    
    /** \brief 指向GPIO设备信息的指针 */
    const amdr_gpio_devinfo_t *p_devinfo;
    
    /** \brief 参数有效标志 */
    bool_t                     valid_flg;
    
} amdr_gpio_dev_t;

/**
 * \brief GPIO初始化 
 *
 * \param[in] p_dev     : 指向GPIO设备的指针 
 * \param[in] p_devinfo : 指向GPIO设备信息的指针 
 *
 * \retval AM_OK : 操作成功 
 */
int amdr_gpio_init(amdr_gpio_dev_t           *p_dev, 
                   const amdr_gpio_devinfo_t *p_devinfo);

/**
 * \brief GPIO去初始化
 *
 * \param[in] p_dev : 指向GPIO设备的指针 
 *
 * \return 无 
 */
void amdr_gpio_deinit(amdr_gpio_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMDR_GPIO_H */

/* end of file */

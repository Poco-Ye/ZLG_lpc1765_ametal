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
 * \brief GPIO 硬件操作接口
 * 
 * 1. GPIO 引脚能够通过软件配置为输入输出；
 * 2. 所有GPIO 引脚默认为输入，在复位时中断禁能；
 * 3. 引脚寄存器允许引脚单独配置或多个同时配置。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-24  hbt, first implementation.
 * \endinternal
 */

#ifndef __AMHW_GPIO_H
#define __AMHW_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h" 

/** 
 * \addtogroup amhw_if_gpio 
 * \copydoc amhw_gpio.h
 * @{
 */

/** 
 * \name GPIO 端口编号
 * @{
 */

#define AMHW_GPIO_PORT_0        0        /**< \brief 端口 0  */ 
#define AMHW_GPIO_PORT_1        1        /**< \brief 端口 1  */

/** @} */

/**
 * \name GPIO 引脚电平
 * @{
 */
 
#define AMHW_GPIO_LEVEL_LOW     0        /**< \brief 低电平 */
#define AMHW_GPIO_LEVEL_HIGH    1        /**< \brief 高电平 */

/** @} */
    
/**
 * \brief GPIO 寄存器块结构体
 */
typedef struct amhw_gpio {
    __IO uint8_t  b[128][32];       /**< \brief 引脚字节寄存器       */
    __IO uint32_t w[32][32];        /**< \brief 引脚字寄存器         */
    __IO uint32_t dir[32];          /**< \brief 方向寄存器           */
    __IO uint32_t mask[32];         /**< \brief 掩码寄存             */
    __IO uint32_t pin[32];          /**< \brief 端口引脚寄存器       */
    __IO uint32_t mpin[32];         /**< \brief 端口掩码寄存器       */
    __IO uint32_t set[32];          /**< \brief 输出的读或置位寄存器 */
    __O  uint32_t clr[32];          /**< \brief 端口清除寄存器       */
    __O  uint32_t toggle[32];       /**< \brief 端口翻转寄存器       */
} amhw_gpio_t;


/**
 * \brief 设置GPIO引脚方向为输出
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return    无
 */
am_static_inline 
void amhw_gpio_pin_dir_output (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->dir[pin >> 5] |= (1UL << (pin & 0x1F));
}

/**
 * \brief 设置GPIO引脚方向为输入
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return    无
 */
am_static_inline 
void amhw_gpio_pin_dir_input (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->dir[pin >> 5] &= ~(1UL << (pin & 0x1F));
}

/**
 * \brief 获取指定引脚的方向
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \retval  0  : 输入
 * \retval  1  : 输出
 */
am_static_inline
int amhw_gpio_pin_dir_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return (((p_hw_gpio->dir[pin >> 5] & 
             (1UL << (pin & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief 设置GPIO端口的掩码值，用于端口的读和写
 *
 *  该值影响对端口的读和写.写0时，使能读和写；写1时，禁止写入该位，读时始终为0.
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] port      : 端口编号，值为 AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 * \param[in] value     : 掩码值，可用于读和写
 * 
 * \return    无
 */
am_static_inline 
void amhw_gpio_mask_set (amhw_gpio_t *p_hw_gpio, 
                         int          port, 
                         uint32_t     value)
{
    p_hw_gpio->mask[port] = value;
}

/**
 * \brief 获取GPIO指定端口的掩码值
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] port      : 端口编号，值为 AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return    端口的掩码值
 */
am_static_inline 
uint32_t amhw_gpio_mask_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->mask[port];
}

/**
 * \brief 获取引脚的电平状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \retval  0  : 低电平
 * \retval  1  : 高电平
 */
am_static_inline 
int amhw_gpio_pin_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return (((p_hw_gpio->pin[pin >> 5] & 
             (1UL << (pin & 0x1F))) != 0) ? 1 : 0);
}

/**
 * \brief 设置指定端口的所有GPIO引脚的状态（与掩码无关）
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] port      : 端口编号，值为 AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 * \param[in] value     : GPIO引脚状态
 *
 * \return    无
 */
am_static_inline 
void amhw_gpio_port_set (amhw_gpio_t *p_hw_gpio, int port, uint32_t value)
{
    p_hw_gpio->pin[port] = value;
}

/**
 * \brief 获取指定端口的所有GPIO引脚的状态（与掩码无关）
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] port      : 端口编号，值为 AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return   端口的引脚状态
 */
am_static_inline 
uint32_t amhw_gpio_port_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->pin[port];
}

/**
 * \brief 通过 MASKP0 寄存器的掩码设置GPIO端口的引脚状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] port      : 端口编号，值为 AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 。
 * \param[in] value     : 所有GPIO端口引脚的状态
 *
 * \return    无
 *
 * \note 如果某一位对应的MASK寄存器值为1，该输出为将不受影响
 */
am_static_inline 
void amhw_gpio_port_masked_set (amhw_gpio_t *p_hw_gpio, 
                                int          port, 
                                uint32_t     value)
{
    p_hw_gpio->mpin[port] = value;
}

/**
 * \brief 通过 MASKP0 寄存器的掩码获取GPIO端口的引脚状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] port      : 端口编号，值为 AMHW_GPIO_PORT_* (#AMHW_GPIO_PORT_0) 
 *
 * \return掩码后的GPIO端口引脚状态
 */
am_static_inline 
uint32_t amhw_gpio_port_masked_get (amhw_gpio_t *p_hw_gpio, int port)
{
    return p_hw_gpio->mpin[port];
}

/**
 * \brief 设置GPIO引脚输出高电平
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return    无.
 *
 * \note 该功能仅限于已设置为输出的引脚
 */
am_static_inline 
void amhw_gpio_pin_out_high (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->set[pin >> 5] = (1UL << (pin & 0x1F));
}

/**
 * \brief 设置GPIO引脚输出低电平
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return    无
 *
 * \note 该功能仅限于已设置为输出的引脚
 */
am_static_inline 
void amhw_gpio_pin_out_low (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->clr[pin >> 5] = (1UL << (pin & 0x1F));
}

/**
 * \brief 翻转GPIO输出引脚的电平状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return 无
 *
 * \note 该功能仅限于已设置为输出的引脚
 */
am_static_inline 
void amhw_gpio_pin_toggle (amhw_gpio_t *p_hw_gpio, int pin)
{
    p_hw_gpio->toggle[pin >> 5] = (1UL << (pin & 0x1F));
}

/**
 * \brief通过字节设置GPIO的引脚状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 * \param[in] byte      : 0为低，1为高
 *
 * \return    无
 */         
am_static_inline 
void amhw_gpio_pin_byte_set (amhw_gpio_t *p_hw_gpio, int pin, uint8_t byte)
{
    p_hw_gpio->b[pin >> 5][(pin & 0x1F)] = byte;
}

/**
 * \brief 获取一个字节表示的GPIO引脚状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return    以字节表示的引脚状态
 *
 * \note 当当前引脚设置为模拟输入时，读到的值始终为0
 */
am_static_inline 
uint8_t amhw_gpio_pin_byte_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return p_hw_gpio->b[pin >> 5][(pin & 0x1F)];
}

/**
 * \brief 通过字设置GPIO的引脚状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 * \param[in] word      : 0为低电平，其余均为高电平
 *
 * \return    无
 */        
am_static_inline 
void amhw_gpio_pin_word_set (amhw_gpio_t *p_hw_gpio, int pin, uint32_t word)
{
    p_hw_gpio->w[pin >> 5][(pin & 0x1F)] = word;
}

/**
 * \brief 获取一个字表示的GPIO引脚状态
 *
 * \param[in] p_hw_gpio : 指向GPIO寄存器块的指针
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return    以字表示的引脚状态
 */
am_static_inline 
uint32_t amhw_gpio_pin_word_get (amhw_gpio_t *p_hw_gpio, int pin)
{
    return p_hw_gpio->w[pin >> 5][(pin & 0x1F)];
}


/**
 * @} amhw_if_gpio
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_GPIO_H */

/* end of file */

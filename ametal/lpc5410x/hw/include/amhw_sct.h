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
 * \brief 状态可编程定时器(State Configurable Timer) 操作接口
 *
 * 1. SCT定时器具有多种功能, including:
 *       - 输出PWM波形；
 *       - 输入捕获；
 *       - 匹配输出；
 * 2. 32位计数器可以工作在2个16位计数器模式或者一个32位计数器模式；
 * 3. 计数器的计数时钟可以是系统时钟，也可以是选择的外部管脚输入信号；
 * 4. 计数器可以工作在向上计数模式，也可以工作在向上-向下计数模式；
 * 5. 下列情况可以定义为一个事件:
 *     - 计数器匹配状态；
 *     - 指定的输入 （或者输出）管脚的电平（或边沿）状态；
 *     - 计数器匹配状态和输入/输出状态的结合（与/或）；
 * 6. 事件控制着状态变化、输出、中断和DMA请求
 *     - 匹配寄存器0可以用作自动边界限制，作为计数器的计数边界；
 *     - 在双向模式中, 事件可以根据计数方向触发；
 *     - 匹配事件可以保持直到另外一个指定的事件发生；
 * 7. 事件可以限制（limit）、终止（halt）, 启动（start）, 停止（stop）计数器；
 * 8. 支持:
 *       - 8 路输入；
 *       - 8 路输出；
 *       - 13 个匹配/捕获寄存器；
 *       - 13 个事件；
 *       - 13 个状态；
 * 9.  8 路输入连接至预先定义好的管脚或信号；
 * 10. 8 路输出
 *       - 输出0 至 输出7可以连接至外部管脚；
 *       - 输出7 可以连接至ADC的触发输入复用矩阵。
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_SCT_H
#define __AMHW_SCT_H


#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/**
 * \addtogroup amhw_if_sct
 * \copydoc amhw_sct.h
 * @{
 */

/**
 * \name SCT模块配置
 * @{
 */

#define AMHW_SCT_EVENT_NUM         (13)  /**< \brief 支持的事件个数           */
#define AMHW_SCT_MATCAP_REG_NUM    (13)  /**< \brief 匹配/捕获寄存器个数      */
#define AMHW_SCT_STATE_NUM         (13)  /**< \brief 支持的状态个数           */
#define AMHW_SCT_OUTPUT_NUM        (8)   /**< \brief 支持的输出路数           */
#define AMHW_SCT_INPUT_NUM         (8)   /**< \brief 支持的输入路数           */
#define AMHW_SCT_DMA_REQUEST_NUM   (2)   /**< \brief 支持的DMA请求数          */

/** @} */

/* 使用无名结构体和联合体区域的开始 */
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
 * \brief 状态可编程定时器寄存器块结构体
 */
typedef struct amhw_sct {
    __IO uint32_t config;          /**< \brief 配置寄存器                     */
                                                                              
    union {                                                                   
        __IO uint32_t ctrl_u;      /**< \brief 控制寄存器                     */
        struct {                                                              
            __IO uint16_t ctrl_l;  /**< \brief 控制寄存器低16位               */
            __IO uint16_t ctrl_h;  /**< \brief 控制寄存器高16位               */
        };                                                                    
    };                                                                        
                                                                              
    __IO uint16_t limit_l;         /**< \brief 限制寄存器低16位               */
    __IO uint16_t limit_h;         /**< \brief 限制寄存器高16位               */
    __IO uint16_t halt_l;          /**< \brief 终止寄存器低16位               */
    __IO uint16_t halt_h;          /**< \brief 终止寄存器高16位               */
    __IO uint16_t stop_l;          /**< \brief 停止寄存器低16位               */
    __IO uint16_t stop_h;          /**< \brief 停止寄存器高16位               */
    __IO uint16_t start_l;         /**< \brief 启动寄存器低16位               */
    __IO uint16_t start_h;         /**< \brief 启动寄存器高16位               */
                                                                              
    uint32_t reserved1[10];        /**< \brief 保留，不应使用                 */
                                                                              
    union {                                                                   
        __IO uint32_t count_u;     /**< \brief 计数器寄存器                   */
        struct {                                                              
            __IO uint16_t count_l; /**< \brief 计数器寄存器低16位             */
            __IO uint16_t count_h; /**< \brief 计数器寄存器高16位             */
        };                                                                    
    };                                                                        
                                                                              
    __IO uint16_t state_l;         /**< \brief 状态寄存器低16位               */
    __IO uint16_t state_h;         /**< \brief 状态寄存器高16位               */
    __I  uint32_t input;           /**< \brief 输入寄存器,只读                */
                                   
    __IO uint16_t regmode_l;       /**< \brief 匹配/捕获模式选择寄存器低16位  */
    __IO uint16_t regmode_h;       /**< \brief 匹配/捕获模式选择寄存器高16位  */
    __IO uint32_t output;          /**< \brief 输出寄存器                     */
    __IO uint32_t outputdirctrl;   /**< \brief 输出方向控制寄存器             */
                                   
    __IO uint32_t res;             /**< \brief 冲突解决寄存器                 */

    union {

        __IO uint32_t dmarequest[2];   /**< \brief DMA请求寄存器组            */
        struct {
            __IO uint32_t dma0request; /**< \brief DMA0 请求寄存器            */
            __IO uint32_t dma1request; /**< \brief DMA1 请求寄存器            */
        };
    };

         uint32_t reserved2[35];   /**< \brief 保留，不应使用                 */

    __IO uint32_t even;            /**< \brief 事件使能寄存器                 */
    __IO uint32_t evflag;          /**< \brief 事件标志寄存器                 */
    __IO uint32_t conen;           /**< \brief "无变化冲突事件"中断使能寄存器 */
    __IO uint32_t conflag;         /**< \brief "无变化冲突事件"状态寄存器     */

    union {

        __IO union {               /**< \brief 匹配寄存器                     */
            __IO uint32_t u;       /**< \brief 匹配寄存器联合状态32位         */
            struct {
                __IO uint16_t l;   /**< \brief 匹配寄存器低16位               */
                __IO uint16_t h;   /**< \brief 匹配寄存器高16位               */
            };

        } match[AMHW_SCT_MATCAP_REG_NUM];

        __I union {                /**< \brief 捕获寄存器                     */
            __IO uint32_t u;       /**< \brief 捕获寄存器联合状态32位         */
            struct {               
                __IO uint16_t l;   /**< \brief 捕获寄存器低16位               */
                __IO uint16_t h;   /**< \brief 捕获寄存器高16位               */
            };
        } cap[AMHW_SCT_MATCAP_REG_NUM];
    };

    uint32_t reserved3[48 + (16 - AMHW_SCT_MATCAP_REG_NUM)]; /**< \brief 保留 */

    union {

        __IO union {              /**< \brief 匹配重转载寄存器                */
            __IO uint32_t u;      /**< \brief 匹配重转载寄存器联合状态32位    */

            struct {
                __IO uint16_t l;  /**< \brief 匹配重转载寄存器低16位          */
                __IO uint16_t h;  /**< \brief 匹配重转载寄存器高16位          */
            };

        } matchrel[AMHW_SCT_MATCAP_REG_NUM];

        __IO union {              /**< \brief 捕获控制寄存器                  */
            __IO uint32_t u;      /**< \brief 捕获控制寄存器联合状态32位      */

            struct {
                __IO uint16_t l;  /**< \brief 捕获控制寄存器低16位            */
                __IO uint16_t h;  /**< \brief 捕获控制寄存器高16位            */
            };
        } capctrl[AMHW_SCT_MATCAP_REG_NUM];

    };

    uint32_t reserved6[48 + (16 - AMHW_SCT_MATCAP_REG_NUM)]; /**< \brief 保留 */

    __IO struct {
        __IO uint32_t state;      /**< \brief 事件状态寄存器                  */
        __IO uint32_t ctrl;       /**< \brief 事件控制寄存器                  */
    } event[AMHW_SCT_EVENT_NUM];  /**< \brief 事件状态、控制寄存器组          */

    uint32_t reserved9[128 - 2 * AMHW_SCT_EVENT_NUM]; /**< \brief 保留        */

    __IO struct {
        __IO uint32_t set;        /**< \brief 输出置位寄存器                  */
        __IO uint32_t clr;        /**< \brief 输出清零寄存器                  */
    } out[AMHW_SCT_OUTPUT_NUM];   /**< \brief 输出置位、清零寄存器组          */

} amhw_sct_t;


/** \brief 用于定义事件号,n的有效区间是：0 ~ AMHW_SCT_EVENT_NUM - 1           */
#define AMHW_SCT_EVT(n)       (n)

/** \brief 用于定义状态号,n的有效区间是：0 ~ AMHW_SCT_STATE_NUM - 1           */
#define AMHW_SCT_STATE(n)     (n)

/** \brief 定义使用的捕获寄存器号，n的有效区间是：0 ~ AMHW_SCT_MATCAP_REG_NUM - 1 */
#define AMHW_SCT_CAP(n)       (n)

/** \brief 定义使用的匹配寄存器号，n的有效区间是：0 ~ AMHW_SCT_MATCAP_REG_NUM - 1 */
#define AMHW_SCT_MAT(n)       (n)

/** \brief 定义输出通道号,n的有效区间是：0 ~ AMHW_SCT_OUTPUT_NUM - 1          */
#define AMHW_SCT_OUT(n)       (n)

/** \brief 定义输入通道号,n的有效区间是：0 ~ AMHW_SCT_INPUT_NUM - 1           */
#define AMHW_SCT_INPUT(n)     (n)

/**
 * \name 用于SCT配置的宏
 * @{
 */

/** \brief 定时器计数器运行在2个16位定时器的模式下 */
#define AMHW_SCT_CONFIG_16BIT_COUNTER                   0x00000000

/** \brief 定时器计数器运行在1个32位定时器的模式下 */
#define AMHW_SCT_CONFIG_32BIT_COUNTER                   0x00000001

/**
  * \brief 阻止匹配寄存器的高16位和低16位从指定的重转载寄存器中重转载
  *        仅仅当计数器运行在1个32位定时器的模式下使用。
  */
#define AMHW_SCT_CONFIG_NORELOAD_U                      (0x1 << 7)

/**
  * \brief 阻止匹配寄存器的低16位从指定的重转载寄存器中重转载
  *        仅仅当计数器运行在2个16位定时器的模式下使用。
  */
#define AMHW_SCT_CONFIG_NORELOAD_L                      (0x1 << 7)

/**
  * \brief 阻止匹配寄存器的高16位从指定的重转载寄存器中重转载
  *        仅仅当计数器运行在2个16位定时器的模式下使用。
  */
#define AMHW_SCT_CONFIG_NORELOAD_H                      (0x1 << 8)

/** \brief 系统时钟作为SCT计数时钟（时钟模式0）                               */
#define AMHW_SCT_CONFIG_CLKMODE_SYSCLK                  (0x0 << 1)

/** \brief 预分频的系统时钟作为SCT计数时钟 （时钟模式1）                      */
#define AMHW_SCT_CONFIG_CLKMODE_PRESCALED_SYSCLK        (0x1 << 1)

/** \brief SCT输入（由CKSEL选择的输入）作为SCT计数时钟（时钟模式2）           */
#define AMHW_SCT_CONFIG_CLKMODE_SCT_INPUT               (0x2 << 1)

/** \brief 预分频的SCT输入（由CKSEL选择的输入）作为SCT计数时钟（时钟模式3）   */
#define AMHW_SCT_CONFIG_CLKMODE_PRESCALED_SCT_INPUT     (0x3 << 1)

/**
 * @}
 */

/**
 * \name 为时钟模式2和时钟模式3选择时钟输入
 * @{
 */

#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_0    (0x0UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_0   (0x1UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_1    (0x2UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_1   (0x3UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_2    (0x4UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_2   (0x5UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_3    (0x6UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_3   (0x7UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_4    (0x8UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_4   (0x9UL << 3)
#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_5    (0xAUL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_5   (0xBUL << 3)
#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_6    (0xCUL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_6   (0xDUL << 3)
#define AMHW_SCT_CONFIG_CKSEL_RISING_IN_7    (0xEUL << 3)
#define AMHW_SCT_CONFIG_CKSEL_FALLING_IN_7   (0xFUL << 3)

/** @} */


/**
 * \name 同步输入，在输入用作事件产生信号之前将输入与SCT时钟同步
 *
 * 在时钟模式2和时钟模式3下，该设置未被使用。
 * @{
 */

#define AMHW_SCT_CONFIG_INSYNC_0     (0x1 <<  9) /**< \brief 同步输入0        */
#define AMHW_SCT_CONFIG_INSYNC_1     (0x1 << 10) /**< \brief 同步输入1        */
#define AMHW_SCT_CONFIG_INSYNC_2     (0x1 << 11) /**< \brief 同步输入2        */
#define AMHW_SCT_CONFIG_INSYNC_3     (0x1 << 12) /**< \brief 同步输入3        */
#define AMHW_SCT_CONFIG_INSYNC_4     (0x1 << 12) /**< \brief 同步输入4        */
#define AMHW_SCT_CONFIG_INSYNC_5     (0x1 << 14) /**< \brief 同步输入5        */

#define AMHW_SCT_CONFIG_INSYNC_ALL   (0x3F << 9) /**< \brief 同步所有输入     */

/** @} */

/**
 * \name 匹配寄存器0上的匹配状态作为定时器计数器的自动限制状态
 * @{
 */
#define AMHW_SCT_CONFIG_AUTOLIMIT_U  (0x1UL << 17)
#define AMHW_SCT_CONFIG_AUTOLIMIT_L  (0x1UL << 17)
#define AMHW_SCT_CONFIG_AUTOLIMIT_H  (0x1UL << 18)

/** @} */

/**
 * \name 用于SCT控制的宏定义
 * @{
 */

#define AMHW_SCT_CTRL_STOP_L    (1 << 1) /**< \brief 停止低16位定时器或联合状态32位定时器 */
#define AMHW_SCT_CTRL_HALT_L    (1 << 2) /**< \brief 终止低16位定时器或联合状态32位定时器 */
#define AMHW_SCT_CTRL_CLRCTR_L  (1 << 3) /**< \brief 清零低16位计数器或联合状态32位计数器 */

/**
 * \brief 低16位定时器或联合状态32位定时器向上计数至其限制状态，然后清零
 */
#define AMHW_SCT_CTRL_BIDIR_L_COUNT_UP       (0 << 4)

/**
 * \brief 低16位定时器或联合状态32位定时器向上计数至其限制状态，然后向下计数至0
 */
#define AMHW_SCT_CTRL_BIDIR_L_COUNT_UP_DOWN  (1 << 4)

/** \brief 低16位定时器或联合状态32位定时器的时钟预分频值 */
#define AMHW_SCT_CTRL_PRE_L(x)               (((x) & 0xFF) << 5)

#define AMHW_SCT_CTRL_STOP_H     (1 << 17)    /**< \brief 停止高16位定时器    */
#define AMHW_SCT_CTRL_HALT_H     (1 << 18)    /**< \brief 终止高16位定时器    */
#define AMHW_SCT_CTRL_CLRCTR_H   (1 << 19)    /**< \brief 清零高16位计数器    */

/**
 * \brief 高16位定时器向上计数至其限制状态，然后清零
 */
#define AMHW_SCT_CTRL_BIDIR_H_COUNT_UP       (0 << 20)

/**
 * \brief 高16位定时器向上计数至其限制状态，向下计数至0
 */
#define AMHW_SCT_CTRL_BIDIR_H_COUNT_UP_DOWN  (1 << 20)

/** \brief 高16位定时器的时钟预分频值  */
#define AMHW_SCT_CTRL_PRE_H(x)               (((x) & 0xFF) << 21)

/**
 * @}
 */

/**
 * \name 用于事件控制寄存器的宏定义
 * @{
 */

/** \brief 选择连接到该事件的匹配寄存器 */
#define AMHW_SCT_EV_CTRL_MATCHSEL(reg)   (reg << 0)

/** \brief 指定该事件属于L组，使用状态寄存器的低16位和匹配寄存器低16位 */
#define AMHW_SCT_EV_CTRL_HEVENT_L        (0UL << 4)

/** \brief 指定该事件属于H组，使用状态寄存器的高16位和匹配寄存器高16位 */
#define AMHW_SCT_EV_CTRL_HEVENT_H        (1UL << 4)

/** \brief IO事件为IOSEL选择的输入信号     */
#define AMHW_SCT_EV_CTRL_OUTSEL_INPUT    (0UL << 5)

/** \brief IO事件为IOSEL选择的输出信号     */
#define AMHW_SCT_EV_CTRL_OUTSEL_OUTPUT   (1UL << 5)

/** \brief 选择与该事件相关联的IO信号      */
#define AMHW_SCT_EV_CTRL_IOSEL(signal)   (signal << 6)

/** \brief 该事件通过加运算（加上STATEV值）改变状态值  */
#define AMHW_SCT_EV_CTRL_STATELD_ADD      (0x0UL << 14)

/** \brief 该事件通过直接转载STATEV值改变状态值        */
#define AMHW_SCT_EV_CTRL_STATELD_LOAD     (0x1UL << 14)

/**
 * \brief 定义 STATEV 值
 *
 *  仅当该事件是当前状态下允许发生的事件中事件号最高时，才可以通过该值改变状态值
 *  如果 STATELD 和 STATEV 值都为0, 则状态不会发生改变
 */
#define AMHW_SCT_EV_CTRL_STATEV(x)        (((x) &(0x1F)) << 15)

/**
 * \name 控制事件的激活状态
 * @{
 */

/**
 * \brief 如果使用了该标志，并且事件触发源中包含有匹配事件触发，则当计数器向上时，
 *        只要计数值大于或等于相应匹配寄存器值，则匹配事件激活为有效态。或当计数器
 *        向下计数时，计数值小于或等于相应匹配寄存器值，匹配事件激活为有效态。
 */
#define AMHW_SCT_EV_CTRL_MATCHMEM_1                (0x1UL << 20)

/**
 * \brief 如果使用了该标志，并且事件触发源中包含有匹配事件触发. 则当且仅当计数值
 *        等于相应匹配寄存器值时，匹配事件才被认为是有效态。
 */
#define AMHW_SCT_EV_CTRL_MATCHMEM_0                (0x0UL << 20)

/** @} */

/** \brief 事件触发将忽略定时器的计数方向 */
#define AMHW_SCT_EV_CTRL_DIRECTION_INDEPENDENT     (0x0UL << 21)

/** \brief 在双向计数模式中，仅当向上计数时，该事件才会被触发  */
#define AMHW_SCT_EV_CTRL_DIRECTION_UP              (0x1UL << 21)

/** \brief 在双向计数模式中，仅当向下计数时，该事件才会被触发  */
#define AMHW_SCT_EV_CTRL_DIRECTION_DOWN            (0x2UL << 21)

/**
 * @}
 */

/**
 * \name 为事件选择IO触发状态
 * @{
 */

#define AMHW_SCT_EV_CTRL_IOCOND_LOW    (0x0UL << 10)  /**< \brief 低电平触发  */
#define AMHW_SCT_EV_CTRL_IOCOND_RISE   (0x1UL << 10)  /**< \brief 上升沿触发  */
#define AMHW_SCT_EV_CTRL_IOCOND_FALL   (0x2UL << 10)  /**< \brief 下降沿触发  */
#define AMHW_SCT_EV_CTRL_IOCOND_HIGH   (0x3UL << 10)  /**< \brief 高电平触发  */

/** @} */

/**
 * \name 指定匹配状态和IO状态触发事件的组合方式
 * @{
 */
 
/** brief 或方式，仅有一种状态发生即触发事件 */
#define AMHW_SCT_EV_CTRL_COMBMODE_OR      (0x0UL << 12)

/** brief 仅匹配状态产生才触发事件           */
#define AMHW_SCT_EV_CTRL_COMBMODE_MATCH   (0x1UL << 12)

/** brief 仅IO状态产生才触发事件             */
#define AMHW_SCT_EV_CTRL_COMBMODE_IO      (0x2UL << 12)

/** brief 匹配状态和IO状态均产生才触发事件   */
#define AMHW_SCT_EV_CTRL_COMBMODE_AND     (0x3UL << 12)

/** @} */

/**
 * \name SCT冲突解决宏定义
 * @{
 */
#define AMHW_SCT_RES_NOCHANGE                (0) /**< \brief 冲突时无变化     */
#define AMHW_SCT_RES_SET_OUTPUT              (1) /**< \brief 冲突时置位输出   */
#define AMHW_SCT_RES_CLEAR_OUTPUT            (2) /**< \brief 冲突时清零输出   */
#define AMHW_SCT_RES_TOGGLE_OUTPUT           (3) /**< \brief 冲突时翻转输出   */

/**
 * @}
 */

/**
 * \name SCT双向计数时，输出控制
 * @{
 */

/** \brief 置位和清零忽略定时器的计数方向                                     */
#define AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT   (0)

/** \brief 置位和清零是颠倒的，当低16位定时器或联合状态32位定时器向下计数时   */
#define AMHW_SCT_OUTPUTDIRCTRL_L_REVERSED    (1)

/** \brief 置位和清零是颠倒的，当高16位定时器向下计数时                       */
#define AMHW_SCT_OUTPUTDIRCTRL_H_REVERSED    (2)

/** @} */

/**
 * \brief SCT 模式标志
 *
 * 该标志用于配置某些寄存器时，指明当前配置的SCT何种模式，当SCT工作在1个32位定时
 * 器模式下时，模式标志恒为:AMHW_SCT_MODE_UNIFY，当SCT工作在2个16位定时器模式下
 * 时，则配置寄存器时，就要指明操作的是低16位(AMHW_SCT_MODE_SEPARATE_L)还是高
 * 16位(AMHW_SCT_MODE_SEPARATE_H)
 */
typedef enum amhw_sct_mode {
    AMHW_SCT_MODE_UNIFY      = 0,    /**< \brief 联合模式                     */
    AMHW_SCT_MODE_SEPARATE_L,        /**< \brief 2个16位定时器模式时，低16位  */
    AMHW_SCT_MODE_SEPARATE_H         /**< \brief 2个16位定时器模式时，高16位  */
} amhw_sct_mode_t;

/**
 * \brief 匹配/捕获 模式
 *
 *  用于设置某些寄存器的模式，指定其工作在匹配状态还是捕获状态
 */
typedef enum amhw_sct_matcap_mode {
    AMHW_SCT_MATCAP_MATCH  = 0,     /**< \brief 寄存器工作在匹配状态 */
    AMHW_SCT_MATCAP_CAPTURE,        /**< \brief 寄存器工作在捕获状态 */
} amhw_sct_matcap_mode_t;


/**
 * \brief 配置SCT
 *
 * \param[in] p_hw_sct  : 指向SCT寄存器块的指针
 * \param[in] cfg_flags : AMHW_SCT_CONFIG_* 宏值或多个 AMHW_SCT_CONFIG_*宏的或
 *                        (OR)值(#AMHW_SCT_CONFIG_32BIT_COUNTER)
 * \return 无
 */
am_static_inline
void amhw_sct_config (amhw_sct_t *p_hw_sct, uint32_t cfg_flags)
{
    p_hw_sct->config = cfg_flags;
}

/**
 * \brief 控制SCT
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] ctrl_flags :AMHW_SCT_CTRL_* 宏值或多个 AMHW_SCT_CTRL_*宏的或
 *                        (OR)值(#AMHW_SCT_CTRL_HALT_L)
 * \return 无
 *
 * \note 当SCT停止或终止时，所有位都可以进行写操作。但当SCT运行时，只有STOP和HALT位
 *       可以操作，如需操作其他位，需要先将HALT位置1.
 */
am_static_inline
void amhw_sct_ctrl (amhw_sct_t *p_hw_sct, uint32_t ctrl_flags)
{
    p_hw_sct->ctrl_u = ctrl_flags;
}

/**
 * \brief 检查SCT是否处于终止(HALT)状态
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 *
 * \retval  TRUE  : 处于终止(HALT)状态
 * \retval  FALSE : 没有处于终止(HALT)状态
 */
am_static_inline
bool_t amhw_sct_halt_check (amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        return (bool_t)((p_hw_sct->ctrl_u & AMHW_SCT_CTRL_HALT_H) != 0);
    } else {
        return (bool_t)((p_hw_sct->ctrl_u & AMHW_SCT_CTRL_HALT_L) != 0);
    }
}

/**
 * \brief 检查SCT是否处于停止(STOP)状态
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 *
 * \retval  TRUE  : 处于停止(STOP)状态
 * \retval  FALSE : 没有处于停止(STOP)状态
 */
am_static_inline
bool_t amhw_sct_stop_check (amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        return (bool_t)((p_hw_sct->ctrl_u & AMHW_SCT_CTRL_STOP_H) != 0);
    } else {
        return (bool_t)((p_hw_sct->ctrl_u & AMHW_SCT_CTRL_STOP_L) != 0);
    }
}

/**
 * \brief 设置控制寄存器的相应位为1
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] value    : 如果该值的位n为1，则会将控制寄存器的相应位置1。0无影响
 *
 * \return 无
 */
am_static_inline
void amhw_sct_ctrl_set (amhw_sct_t *p_hw_sct, uint32_t value)
{
    p_hw_sct->ctrl_u |= value;
}

/**
 * \brief 清零控制寄存器的相应位
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] value    : 如果该值的位n为1，则会将控制寄存器的相应位清零。0无影响
 *
 * \return 无
 */
am_static_inline
void amhw_sct_ctrl_clr (amhw_sct_t *p_hw_sct, uint32_t value)
{
    p_hw_sct->ctrl_u &= (~value);
}

/**
 * \brief 将SCT从终止(HALT)态切换到停止(STOP)态(并不会处于运行态)
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 *
 * \return 无
 */
void amhw_sct_ctrl_halt_to_stop(amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode);

/**
 * \brief 设置SCT的预分频值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] prescale : 计数器的时钟频率是SCT时钟频率除以(prescale + 1)
 *
 * \return 无
 */
void amhw_sct_prescale_set(amhw_sct_t     *p_hw_sct,
                           amhw_sct_mode_t mode,
                           uint8_t         prescale);

/**
 * \brief 获取SCT的预分频值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 *
 * \return SCT的预分频值
 */
uint8_t amhw_sct_prescale_get(amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode);

/**
 * \brief 配置SCT的一个事件
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] flags    : AMHW_SCT_EV_CTRL_*宏值或多个AMHW_SCT_EV_CTRL_*宏的或(OR)
 *                       值。(#AMHW_SCT_EV_CTRL_COMBMODE_MATCH)
 *                       
 * \return 无
 */
am_static_inline
void amhw_sct_event_ctrl (amhw_sct_t *p_hw_sct, uint32_t evt_num, uint32_t flags)
{
    p_hw_sct->event[evt_num].ctrl = flags;
}

/**
 * \brief 使能一个事件在指定状态中发生
 *
 * \param[in] p_hw_sct  : 指向SCT寄存器块的指针
 * \param[in] evt_num   : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] state_num : 状态号，0 ~ AMHW_SCT_STATE_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_state_enable (amhw_sct_t *p_hw_sct,
                                  uint32_t    evt_num,
                                  uint32_t    state_num)
{
    p_hw_sct->event[evt_num].state |= (1 << state_num);
}

/**
 * \brief 禁能一个事件在指定状态中发生
 *
 * \param[in] p_hw_sct  : 指向SCT寄存器块的指针
 * \param[in] evt_num   : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] state_num : 状态号，0 ~ AMHW_SCT_STATE_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_state_disable (amhw_sct_t *p_hw_sct,
                                   uint32_t    evt_num,
                                   uint32_t    state_num)
{
    p_hw_sct->event[evt_num].state &= ~(1 << state_num);
}

/**
 * \brief 使能一个事件作为计数器的限制状态
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_limit_enable (amhw_sct_t     *p_hw_sct,
                                  amhw_sct_mode_t mode,
                                  uint32_t        evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->limit_h |= 1 << evt_num;
    } else {
        p_hw_sct->limit_l |= 1 << evt_num;
    }
}

/**
 * \brief 禁能一个事件作为计数器的限制状态
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_limit_disable (amhw_sct_t     *p_hw_sct,
                                   amhw_sct_mode_t mode,
                                   uint32_t        evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->limit_h &= ~(1 << evt_num);
    } else {
        p_hw_sct->limit_l &= ~(1 << evt_num);
    }
}

/**
 * \brief 使能一个事件发生时终止定时器
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_halt_enable (amhw_sct_t      *p_hw_sct,
                                 amhw_sct_mode_t  mode,
                                 uint32_t         evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->halt_h |= 1 << evt_num;
    } else {
        p_hw_sct->halt_l |= 1 << evt_num;
    }
}

/**
 * \brief 禁能一个事件发生时终止定时器
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_halt_disable (amhw_sct_t      *p_hw_sct,
                                  amhw_sct_mode_t  mode,
                                  uint32_t         evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->halt_h &= ~(1 << evt_num);
    } else {
        p_hw_sct->halt_l &= ~(1 << evt_num);
    }
}

/**
 * \brief 使能一个事件发生时停止定时器
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_stop_enable (amhw_sct_t      *p_hw_sct,
                                 amhw_sct_mode_t  mode,
                                 uint32_t         evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->stop_h |= 1 << evt_num;
    } else {
        p_hw_sct->stop_l |= 1 << evt_num;
    }
}

/**
 * \brief 禁能一个事件发生时停止定时器
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_stop_disable (amhw_sct_t      *p_hw_sct,
                                  amhw_sct_mode_t  mode,
                                  uint32_t         evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->stop_h &= ~(1 << evt_num);
    } else {
        p_hw_sct->stop_l &= ~(1 << evt_num);
    }
}

/**
 * \brief 使能一个事件发生时启动定时器
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_start_enable (amhw_sct_t      *p_hw_sct,
                                  amhw_sct_mode_t  mode,
                                  uint32_t         evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->start_h |= 1 << evt_num;
    } else {
        p_hw_sct->start_l |= 1 << evt_num;
    }
}

/**
 * \brief 禁能一个事件发生时启动定时器
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_event_start_disable (amhw_sct_t      *p_hw_sct,
                                   amhw_sct_mode_t  mode,
                                   uint32_t         evt_num)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->start_h &= ~(1 << evt_num);
    } else {
        p_hw_sct->start_l &= ~(1 << evt_num);
    }
}

/**
 * \brief 设置SCT的计数(count)值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式.
 * \param[in] value    : 计数(count)值
 *
 * \note 设置计数值时，必须确保相应的计数器处于HALT状态，如果SCT模式是
 *       #AMHW_SCT_MODE_SEPARATE_L 或者 #AMHW_SCT_MODE_SEPARATE_H 
 *       计数(count)值仅仅低16位有效
 */
void amhw_sct_count_set(amhw_sct_t     *p_hw_sct,
                        amhw_sct_mode_t mode,
                        uint32_t        value);

/**
 * \brief 获取定时器的当前计数值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 *
 * \return 定时器的当前计数值，如果SCT模式是#AMHW_SCT_MODE_SEPARATE_L 
 *         或者 #AMHW_SCT_MODE_SEPARATE_H， 计数(count)值仅仅低16位有效     
 */
uint32_t amhw_sct_count_get(amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode);

/**
 * \brief 获取当前的状态值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 *
 * \return 当前的状态值
 */
am_static_inline
uint16_t amhw_sct_state_get (amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        return p_hw_sct->state_h;
    } else {
        return p_hw_sct->state_l;
    }
}

/**
 * \brief 设置状态值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] value    : 状态值
 *
 * \note 设置状态值是，必须确保相应的计数器处于终止(HALT)状态
 */
am_static_inline
void amhw_sct_state_set (amhw_sct_t      *p_hw_sct,
                         amhw_sct_mode_t  mode,
                         uint16_t         value)
{
    if (mode == AMHW_SCT_MODE_SEPARATE_H) {
        p_hw_sct->state_h = value;
    } else {
        p_hw_sct->state_l = value;
    }
}

/**
 * \brief 获取SCT的输入状态
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 *
 * \return 输入状态。 位0  ~ 位7 : AIN0 ~ AIN7(直接读取的输入状态)
 *                    位16 ~ 位23: SIN0 ~ SIN7(输入状态)
 *
 * \note SIN0 ~ SIN7:
 *        - 如果设置寄存器中，INSYNC 位为1，则相应的输入状态SIN是同步后的输入状态。
 *          利用3个SCT时钟同步，因此会得到一个比原信号延迟3个SCT时钟的稳定信号。
 *        - 如果设置寄存器中，INSYNC 位为0，则相应的输入状态SIN与直接读取的输入
 *          状态AIN相同。
 */
am_static_inline
uint32_t amhw_sct_input_state_get (amhw_sct_t *p_hw_sct)
{
     return p_hw_sct->input;
}

/**
 * \brief 获取SCT的输出状态
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 *
 * \return 输出状态. 位0 ~ 位7: 输出0 ~ 输出7
 *           - 如果输出状态为高电平，则相应位为1
 *           - 如果输出状态为低电平，则相应位为0
 */
am_static_inline
uint32_t amhw_sct_output_state_get (amhw_sct_t *p_hw_sct)
{
     return p_hw_sct->output;
}

/**
 * \brief 设置SCT的输出状态
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] state    : 位 n 为1，则输出通道n输出高电平
 *                       位 n 为0，则输出通道n输出低电平
 *
 * \return 无
 *
 * \note 写SCT输出寄存器必须确保所有的计数器处于终止(HALT)状态
 */
am_static_inline
void amhw_sct_output_state_config (amhw_sct_t *p_hw_sct, uint8_t state)
{
     p_hw_sct->output = state;
}

/**
 * \brief 设置指定的输出通道输出高电平
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  无
 *
 * \note 写SCT输出寄存器必须确保所有的计数器处于终止(HALT)状态
 */
am_static_inline
void amhw_sct_output_state_set (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
     p_hw_sct->output |= (1 << output_num);
}

/**
 * \brief 设置指定的输出通道输出低电平
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  无
 *
 * \note 写SCT输出寄存器必须确保所有的计数器处于终止(HALT)状态
 */
am_static_inline
void amhw_sct_output_state_clr (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
     p_hw_sct->output &= ~(1 << output_num);
}

/**
 * \brief SCT双向计数时的输出控制
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 * \param[in] value      : 控制值：
 *                         - #AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT
 *                         - #AMHW_SCT_OUTPUTDIRCTRL_L_REVERSED
 *                         - #AMHW_SCT_OUTPUTDIRCTRL_R_REVERSED
 *
 * \return  无
 */
void amhw_sct_output_dir_ctrl(amhw_sct_t *p_hw_sct,
                              uint8_t     output_num,
                              uint8_t     value);

/**
 * \brief 配置输出冲突解决
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 * \param[in] value      : 冲突解决方式：
 *                          - #AMHW_SCT_RES_NOCHANGE       : 输出无变化
 *                          - #AMHW_SCT_RES_SET_OUTPUT     : 输出高电平
 *                          - #AMHW_SCT_RES_CLEAR_OUTPUT   : 输出低电平
 *                          - #AMHW_SCT_RES_TOGGLE_OUTPUT  : 翻转输出电平
 * \return 无
 */
void amhw_sct_conflict_res_config(amhw_sct_t *p_hw_sct,
                                  uint8_t     output_num,
                                  uint8_t     value);


/**
 * \brief 使能事件的DMA请求
 *
 * \param[in] p_hw_sct    : 指向SCT寄存器块的指针
 * \param[in] request_num : DMA请求号,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 * \param[in] evt_num     : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_dma_request_event_enable (amhw_sct_t *p_hw_sct,
                                        uint8_t     request_num,
                                        uint32_t     evt_num)
{
    p_hw_sct->dmarequest[request_num] |= (1 << evt_num);
}

/**
 * \brief 禁能事件的DMA请求
 *
 * \param[in] p_hw_sct    : 指向SCT寄存器块的指针
 * \param[in] request_num : DMA请求号,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 * \param[in] evt_num     : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_dma_request_event_disable (amhw_sct_t *p_hw_sct,
                                         uint8_t     request_num,
                                         uint32_t    evt_num)
{
    p_hw_sct->dmarequest[request_num] &= ~(1 << evt_num);
}

/**
 * \brief 当匹配寄存器值从相应的重装载寄存器中重转载时，产生DMA请求
 *
 * \param[in] p_hw_sct    : 指向SCT寄存器块的指针
 * \param[in] request_num : DMA请求号,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_dma_request_reload_enable (amhw_sct_t *p_hw_sct,
                                         uint8_t     request_num)
{
    p_hw_sct->dmarequest[request_num] |= (1 << 30);
}

/**
 * \brief 当匹配寄存器值从相应的重装载寄存器中重转载时，不产生DMA请求
 *
 * \param[in] p_hw_sct    : 指向SCT寄存器块的指针
 * \param[in] request_num : DMA请求号,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_dma_request_reload_disable (amhw_sct_t *p_hw_sct,
                                          uint8_t     request_num)
{
    p_hw_sct->dmarequest[request_num] &= ~(1 << 30);
}

/**
 * \brief 检测DMA请求标志是否置位
 *
 * \param[in] p_hw_sct    : 指向SCT寄存器块的指针
 * \param[in] request_num : DMA请求号,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 *
 * \retval  TRUE  : DMA请求标志置位
 * \retval  FALSE : DMA请求标志未置位
 */
am_static_inline
bool_t amhw_sct_dma_request_check (amhw_sct_t *p_hw_sct, uint8_t request_num)
{
    return (bool_t)((p_hw_sct->dmarequest[request_num] & (1ul << 31)) != 0);
}

/**
 * \brief 使能指定事件的中断请求
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_event_int_enable (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    p_hw_sct->even |= (1 << evt_num);
}

/**
 * \brief 禁能指定事件的中断请求
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_event_int_disable (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    p_hw_sct->even &= ~(1 << evt_num);
}

/**
 * \brief 获取事件标志寄存器值
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \return 事件标志寄存器值，相应位为1，表明相应事件发生
 */
am_static_inline
uint32_t amhw_sct_event_flag_get (amhw_sct_t *p_hw_sct)
{
    return p_hw_sct->evflag;
}

/**
 * \brief 检测指定事件是否发生
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \retval  TRUE  : 事件发生
 * \retval  FALSE : 事件未发生
 */
am_static_inline
bool_t amhw_sct_event_flag_chk (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    return (bool_t)((p_hw_sct->evflag & (1 << evt_num)) != 0);
}

/**
 * \brief 清除指定事件的发生标志
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] evt_num  : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_event_flag_clr (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    p_hw_sct->evflag = (1 << evt_num);
}

/**
 * \brief 使能输出冲突时产生中断
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_conflict_int_enable (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
    p_hw_sct->conen |= (1 << output_num);
}

/**
 * \brief 禁能输出冲突时产生中断
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  无
 */
am_static_inline
void amhw_sct_conflict_int_disable (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
    p_hw_sct->conen &= ~(1 << output_num);
}

/**
 * \brief 获取冲突标志
 * \param[in] p_hw_sct  : 指向SCT寄存器块的指针
 * \return 冲突标志. 如果在输出n上有无变化冲突事件发生(即该输出的冲突解决设置为
           无变化)，位 n (0 ~ 7) 为1
 *
 * \note  位30为特殊位，如果有总线错误（当低16位计数器或联合状态下的32位计数器未
 *        处于HALT状态时,对不应该写入操作的寄存器，如STATE,MATCH，进行了写入操作），
 *        则该位为1。
 *        位31为特殊位，如果有总线错误（当高16位计数器未处于HALT状态时,对不应该
 *        写入操作的寄存器，如STATE,MATCH，进行了写入操作），则该位为1。
 */
am_static_inline
uint32_t amhw_sct_conflict_flag_get (amhw_sct_t *p_hw_sct)
{
    return p_hw_sct->conflag;
}

/**
 * \brief 清除冲突标志
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] flags    : 位n为1，则清除该位上的相应标志
 *
 * \return 无
 */
am_static_inline
void amhw_sct_conflict_flag_clr (amhw_sct_t  *p_hw_sct, uint32_t flags)
{
    p_hw_sct->conflag = (1 << flags);
}

/**
 * \brief SCT匹配/捕获寄存器模式配置
 *
 * \param[in] p_hw_sct    : 指向SCT寄存器块的指针
 * \param[in] sct_mode    : SCT模式
 * \param[in] matcap_num  : 匹配/捕获寄存器号，0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] matcap_mode : 设置的模式：
 *                           - AMHW_SCT_MATCAP_MATCH, 设置为匹配模式
 *                           - AMHW_SCT_MATCAP_CAPTURE, 设置为捕获模式
 * \return  无
 */
void amhw_sct_regmode_config(amhw_sct_t            *p_hw_sct,
                             amhw_sct_mode_t        sct_mode,
                             uint32_t               matcap_num,
                             amhw_sct_matcap_mode_t matcap_mode);


/**
 * \brief 设置匹配寄存器值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] mat_num  : 匹配寄存器号， 0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] value    : 设置的值
 *
 * \return  无
 *
 * \note 设置值之前，必须确保该模式下相应计数器处于HALT状态，如果SCT模式为
 *       AMHW_SCT_MODE_SEPARATE_L 或者AMHW_SCT_MODE_SEPARATE_H
 *       value值仅低16为有效
 */
void amhw_sct_mat_val_set(amhw_sct_t     *p_hw_sct,
                          amhw_sct_mode_t mode,
                          uint32_t        mat_num,
                          uint32_t        value);

/**
 * \brief 设置匹配重转载寄存器的值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] mode     : SCT模式
 * \param[in] num      : 匹配重转载寄存器号， 0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] value    : 设置的值
 *
 * \return 无
 *
 * \note 设置值之前，无需确保该模式下相应计数器处于HALT状态，如果SCT模式为
 *       AMHW_SCT_MODE_SEPARATE_L 或者AMHW_SCT_MODE_SEPARATE_H
 *       value值仅低16为有效
 */
void amhw_sct_mat_reload_val_set(amhw_sct_t     *p_hw_sct,
                                 amhw_sct_mode_t mode,
                                 uint32_t        num,
                                 uint32_t        value);
/**
 * \brief 配置捕获，使能或禁能事件触发捕获寄存器值被捕获值装载
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] sct_mode : SCT模式
 * \param[in] cap_num  : 捕获寄存器号，0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] evt_num  : 触发捕获的事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \param[in] active   : TRUE: 使能事件触发捕获
 *                       FALSE: 禁能事件触发捕获
 * \return  无
 */
void amhw_sct_cap_ctrl(amhw_sct_t      *p_hw_sct,
                       amhw_sct_mode_t  sct_mode,
                       uint32_t         cap_num,
                       uint32_t         evt_num,
                       bool_t           active);

/**
 * \brief 获取捕获值
 *
 * \param[in] p_hw_sct : 指向SCT寄存器块的指针
 * \param[in] sct_mode : SCT模式
 * \param[in] cap_num  : 捕获寄存器号，0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 *
 * \return 捕获值
 *         如果SCT模式是 AMHW_SCT_MODE_SEPARATE_L 或者 AMHW_SCT_MODE_SEPARATE_H
 *         则返回值仅仅低16位有效
 */
uint32_t amhw_sct_cap_val_get(amhw_sct_t      *p_hw_sct,
                              amhw_sct_mode_t  sct_mode,
                              uint32_t         cap_num);

/**
 * \brief 使能指定事件将指定输出通道置为高电平
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] evt_num    : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_out_set_enable (amhw_sct_t  *p_hw_sct,
                              uint8_t      output_num,
                              uint32_t     evt_num)
{
    p_hw_sct->out[output_num].set |= (1 << evt_num);
}

/**
 * \brief 禁能指定事件将指定输出通道置为高电平
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] evt_num    : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_out_set_disable (amhw_sct_t *p_hw_sct,
                               uint8_t     output_num,
                               uint32_t    evt_num)
{
    p_hw_sct->out[output_num].set &= ~(1 << evt_num);
}

/**
 * \brief 使能指定事件将指定输出通道置为低电平
 *
 * \param[in] p_hw_sct   : 指向SCT寄存器块的指针
 * \param[in] evt_num    : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_out_clr_enable (amhw_sct_t  *p_hw_sct,
                              uint8_t      output_num,
                              uint32_t     evt_num)
{
    p_hw_sct->out[output_num].clr |= (1 << evt_num);
}

/**
 * \brief 禁能指定事件将指定输出通道置为低电平
 *
 * \param[in] p_hw_sct    : 指向SCT寄存器块的指针
 * \param[in] evt_num     : 事件号，0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num  : 输出通道号，0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return 无
 */
am_static_inline
void amhw_sct_out_clr_disable (amhw_sct_t *p_hw_sct,
                               uint8_t     output_num,
                               uint32_t    evt_num)
{
    p_hw_sct->out[output_num].clr &= ~(1 << evt_num);
}

/* 使用无名结构体和联合体区域的结束 */
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
 * @} amhw_if_sct
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AMHW_SCT_H */

/* end of file */



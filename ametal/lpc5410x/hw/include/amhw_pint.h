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
 * \brief PINT 硬件操作接口
 *
 * 引脚中断：
 * – 从GPIO的端口0到端口1，高达8个可选择引脚作为引脚中断，支持边沿或电平敏感
 *   中断请求。每一个中断请求均可在NVIC中建立独立的中断；
 * – 边沿敏感中断可配置为上升沿、下降沿或双边沿；
 * – 电平敏感中断可配置为高电平或低电平。
 *
 * \internal
 * \par Modification History
 * - 1.10 15-01-01  hbt, modified.
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */
#ifndef __AMHW_PINT_H
#define __AMHW_PINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_pint
 * \copydoc amhw_pint.h
 * @{
 */

/**
 * \brief LPC5410X 引脚中断寄存器块结构体
 */
typedef struct amhw_pint {
    __IO uint32_t isel;   /**< \brief 引脚中断模式寄存器               */
    __IO uint32_t ienr;   /**< \brief 上升沿或电平中断使能寄存器       */
    __IO uint32_t sienr;  /**< \brief 上升沿或电平中断设置寄存器       */
    __IO uint32_t cienr;  /**< \brief 上升沿或电平中断清除使能寄存器   */
    __IO uint32_t ienf;   /**< \brief 下降沿或高电平中断使能寄存器     */
    __IO uint32_t sienf;  /**< \brief 下降沿或高电平中断设置寄存器     */
    __IO uint32_t cienf;  /**< \brief 下降沿或高电平中断清除使能寄存器 */
    __IO uint32_t rise;   /**< \brief 上升沿寄存器                     */
    __IO uint32_t fall;   /**< \brief 下降沿寄存器                     */
    __IO uint32_t ist;    /**< \brief 引脚中断状态寄存器               */
    __IO uint32_t pmctrl; /**< \brief 模式匹配中断控制寄存器           */
    __IO uint32_t pmsrc;  /**< \brief 模式匹配中断位寄存器             */
    __IO uint32_t pmcfg;  /**< \brief 模式匹配中断位控制寄存器         */
} amhw_pint_t;

/**
 * \name LPC5410X 引脚中断和模式匹配引擎寄存器位域和宏定义
 * @{
 */
 
/** \brief 引脚中断模式掩码 */
#define AMHW_PINT_ISEL_PMODE_MASK      ((uint32_t)0x00FF)

/** \brief 模式匹配控制掩码 */
#define AMHW_PINT_PMCTRL_MASK          ((uint32_t)0xFF000003)

/** 
 * \brief 模式匹配指定8个引脚中断控制。
 */
#define AMHW_PINT_PMCTRL_PMATCH_SEL    (1 << 0)

/**
 * \brief 当指定布尔表达式的值为真，使能“接收事件”输出到CPU和（或）GPIO输出。
 */
#define AMHW_PINT_PMCTRL_RXEV_ENA      (1 << 1)

/** \brief 输入源起始位 */
#define AMHW_PINT_SRC_BITSOURCE_START  8

/** \brief 输入源掩码 */
#define AMHW_PINT_SRC_BITSOURCE_MASK   7

/** \brief 配置起始位 */
#define AMHW_PINT_SRC_BITCFG_START     8

/** \brief 配置掩码 */
#define AMHW_PINT_SRC_BITCFG_MASK      7

/** @} */

/**
 * \name LPC5410X 引脚中断通道编号
 * \anchor grp_amhw_pint_chan
 * @{
 */
 
#define AMHW_PINT_CHAN_0      (1 << 0)     /**< \brief 引脚中断通道 0  */
#define AMHW_PINT_CHAN_1      (1 << 1)     /**< \brief 引脚中断通道 1  */
#define AMHW_PINT_CHAN_2      (1 << 2)     /**< \brief 引脚中断通道 2  */
#define AMHW_PINT_CHAN_3      (1 << 3)     /**< \brief 引脚中断通道 3  */
#define AMHW_PINT_CHAN_4      (1 << 4)     /**< \brief 引脚中断通道 4  */
#define AMHW_PINT_CHAN_5      (1 << 5)     /**< \brief 引脚中断通道 5  */
#define AMHW_PINT_CHAN_6      (1 << 6)     /**< \brief 引脚中断通道 6  */
#define AMHW_PINT_CHAN_7      (1 << 7)     /**< \brief 引脚中断通道 7  */
#define AMHW_PINT_CHAN_(ch)   (1 << (ch))  /**< \brief 引脚中断通道 ch */

/** @} */

/**
 * \brief 配置引脚为边沿敏感
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_edge_set (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->isel = (p_hw_pint->isel & AMHW_PINT_ISEL_PMODE_MASK) & ~chan;
}

/**
 * \brief 配置引脚为电平敏感
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_level_set (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->isel = (p_hw_pint->isel & AMHW_PINT_ISEL_PMODE_MASK) | chan;
}

/**
 * \brief 获取引脚中断敏感状态
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 *
 * \retval  0 : 边沿敏感
 * \retval  1 : 电平敏感
 */
am_static_inline 
uint32_t amhw_pint_mode_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->isel & AMHW_PINT_ISEL_PMODE_MASK;
}

/**
 * \brief 获取上升沿或电平敏感的使能状态
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 *
 * \retval  0 : 禁能
 * \retval  1 : 使能
 */
am_static_inline 
uint32_t amhw_pint_high_enabled_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->ienr;
}

/**
 * \brief 使能上升沿或电平敏感中断
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_high_enable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->sienr = chan;
}

/**
 * \brief 禁能上升沿或电平敏感中断
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_high_disable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->cienr = chan;
}

/**
 * \brief 获取下降沿中断状态或有效电平中断状态
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \retval  0 : 下降沿中断禁能或低电平中断
 * \retval  1 : 下降沿中断使能或高电平中断
 */
am_static_inline 
uint32_t amhw_pint_low_enabled_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->ienf;
}

/**
 * \brief 选择高电平或下降沿中断
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_low_enable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->sienf = chan;
}

/**
 * \brief 禁能低电平或下降沿中断
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
*/
am_static_inline 
void amhw_pint_low_disable (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->cienf = chan;
}

/**
 * \brief 获取上升沿监测的状态或最后写入的状态
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    状态
 */
am_static_inline 
uint32_t amhw_pint_rise_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->rise;
}

/**
 * \brief 清除对应引脚的上升沿监测
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_rise_clr (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->rise = chan;
}

/**
 * \brief 获取下降沿监测的状态或最后写入的状态
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    状态。
 */
am_static_inline 
uint32_t amhw_pint_fall_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->fall;
}

/**
 * \brief 清除对应引脚的下降沿监测
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_fall_clr (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->fall = chan;
}

/**
 * \brief 获取中断状态
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    中断状态 (PININTn 的 bit n = 1，意味着中断pending).
 */
am_static_inline 
uint32_t amhw_pint_status_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->ist;
}

/**
 * \brief 清除通道对应引脚的边沿触发功能
 *
 * 中断模式选择边沿敏感时，清除边沿触发功能；
 * 中断模式选择电平触发时，切换触发电平。
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号，参见 
 *                        \ref grp_amhw_pint_chan
 *
 * \return    无
 */
am_static_inline 
void amhw_pint_status_clr (amhw_pint_t *p_hw_pint, uint32_t chan)
{
    p_hw_pint->ist = chan;
}

/**
 * \brief 使能模式匹配中断
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_pint_match_enable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           | AMHW_PINT_PMCTRL_PMATCH_SEL;
}

/**
 * \brief 禁能模式匹配中断
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_pint_match_disable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           & ~AMHW_PINT_PMCTRL_PMATCH_SEL;
}

/**
 * \brief 使能引脚中断的“接收事件”输出
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_pint_match_rxev_enable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           | AMHW_PINT_PMCTRL_RXEV_ENA;
}

/**
 * \brief 禁能引脚中断的“接收事件”输出
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    无
 */
am_static_inline 
void amhw_pint_match_rxev_disable (amhw_pint_t *p_hw_pint)
{
    p_hw_pint->pmctrl = (p_hw_pint->pmctrl & AMHW_PINT_PMCTRL_MASK) 
                                           & ~AMHW_PINT_PMCTRL_RXEV_ENA;
}

/**
 * \brief 获取模式匹配状态
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \return    8 bit 的模式匹配状态，当某一位为1时，其对应的 product term 匹配
 */
am_static_inline 
uint32_t amhw_pint_match_get (amhw_pint_t *p_hw_pint)
{
    return p_hw_pint->pmctrl >> 24;
}
   
/**
 * \brief 引脚中断通道定义
 */
typedef enum amhw_pint_select {
    AMHW_PINT_SELECT0 = 0,       /**< \brief 引脚中断选择通道0 */
    AMHW_PINT_SELECT1 = 1,       /**< \brief 引脚中断选择通道1 */
    AMHW_PINT_SELECT2 = 2,       /**< \brief 引脚中断选择通道2 */
    AMHW_PINT_SELECT3 = 3,       /**< \brief 引脚中断选择通道3 */
    AMHW_PINT_SELECT4 = 4,       /**< \brief 引脚中断选择通道4 */
    AMHW_PINT_SELECT5 = 5,       /**< \brief 引脚中断选择通道5 */
    AMHW_PINT_SELECT6 = 6,       /**< \brief 引脚中断选择通道6 */
    AMHW_PINT_SELECT7 = 7        /**< \brief 引脚中断选择通道7 */
} amhw_pint_select_t;


/**
 * \brief 触发方式定义
 */
typedef enum amhw_pint_trigger_mode { 
    AMHW_PINT_TRIGGER_HIGH       = 0x0,   /**< \brief 高电平触发 */
    AMHW_PINT_TRIGGER_LOW        = 0x1,   /**< \brief 低电平触发 */
    AMHW_PINT_TRIGGER_RISE       = 0x2,   /**< \brief 上升沿触发 */
    AMHW_PINT_TRIGGER_FALL       = 0x3,   /**< \brief 下降沿触发 */
    AMHW_PINT_TRIGGER_BOTH_EDGES = 0x4    /**< \brief 双边沿触发 */
} amhw_pint_trigger_mode_t;

/**
 * \brief 触发形式选择
 *
 * \param[in] p_hw_pint    : 指向引脚中断寄存器块的指针
 * \param[in] chan         : 引脚中断通道号，参见
 *                           \ref grp_amhw_pint_chan
 * \param[in] trigger_type : 形式选择：
 *                           - AMHW_PINT_TRIGGER_HIGH       : 高电平触发
 *                           - AMHW_PINT_TRIGGER_LOW        : 低电平触发
 *                           - AMHW_PINT_TRIGGER_RISE       : 上升沿触发
 *                           - AMHW_PINT_TRIGGER_FALL       : 下降沿触发
 *                           - AMHW_PINT_TRIGGER_BOTH_EDGES : 双边沿触发
 *
 * \return    无
 */
void amhw_pint_trigger_select(amhw_pint_t              *p_hw_pint, 
                              uint8_t                   chan,
                              amhw_pint_trigger_mode_t  trigger_type);

/**
 * \brief 引脚中断位片编号
 */
typedef enum amhw_pint_bitslice {
    AMHW_PINT_BITSLICE0 = 0,            /**< \brief 位片0编号  */
    AMHW_PINT_BITSLICE1,                /**< \brief 位片1编号  */
    AMHW_PINT_BITSLICE2,                /**< \brief 位片2编号  */
    AMHW_PINT_BITSLICE3,                /**< \brief 位片3编号  */
    AMHW_PINT_BITSLICE4,                /**< \brief 位片4编号  */
    AMHW_PINT_BITSLICE5,                /**< \brief 位片5编号  */
    AMHW_PINT_BITSLICE6,                /**< \brief 位片6编号  */
    AMHW_PINT_BITSLICE7                 /**< \brief 位片7编号  */
} amhw_pint_bitslice_t;

/**
 * \brief 设置引脚中断模式匹配的源
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] chan      : 引脚中断通道号
 * \param[in] slicenum  : 位片编号
 *
 * \return    无
 */
void amhw_pint_match_src_set(amhw_pint_t          *p_hw_pint, 
                             amhw_pint_select_t    chan, 
                             amhw_pint_bitslice_t  slicenum);

/**
 * \brief 引脚匹配中断位片配置值
 */
typedef enum amhw_pint_bitslice_cfg {
    AMHW_PINT_PATTERNCONST1          = 0x0, /**< \brief 标准1，        */ 
    AMHW_PINT_PATTERNRISING          = 0x1, /**< \brief 上升沿         */ 
    AMHW_PINT_PATTERNFALLING         = 0x2, /**< \brief 下降沿         */ 
    AMHW_PINT_PATTERNRISINGORFALLING = 0x3, /**< \brief 上升沿或下降沿 */ 
    AMHW_PINT_PATTERNHIGH            = 0x4, /**< \brief 高电平         */ 
    AMHW_PINT_PATTERNLOW             = 0x5, /**< \brief 低电平         */ 
    AMHW_PINT_PATTERNCONST0          = 0x6, /**< \brief 标准0          */ 
    AMHW_PINT_PATTERNEVENT           = 0x7  /**< \brief 事件           */ 
} amhw_pint_bitslice_cfg_t;

/**
 * \brief 在引脚中断中配置模式匹配
 *
 * \param[in] p_hw_pint : 指向引脚中断寄存器块的指针
 * \param[in] slice_num : 位片编号
 * \param[in] slice_cfg : 位片配置参数
 * \param[in] end_point : 如果该值为TURE，当前位片即为最终构成
 *
 * \return    无
 */
void amhw_pint_match_config(amhw_pint_t              *p_hw_pint, 
                            amhw_pint_bitslice_t      slice_num, 
                            amhw_pint_bitslice_cfg_t  slice_cfg, 
                            bool_t                    end_point);

/**
 * @}
 */
 
#ifdef __cplusplus
}
#endif

#endif /* __AMHW_PINT_H */

/* end of file */

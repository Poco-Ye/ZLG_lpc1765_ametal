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
 * \brief 输入复用 (INMUX) 硬件操作接口
 *
 * 1. 将输入配置为引脚中断块和部分匹配引擎;
 * 2. 将输入配置为DMA触信号;
 * 3. 将输入配置为频率测量功能。该功能受SYSCON中FREQMECTRL寄存器的影响。
 *
 * \internal
 * \par Modification History
 * - 1.10 15-01-01  hbt, modified.
 * - 1.00 14-12-05  asd, first implementation.
 * \endinternal
 */
 
#ifndef __AMHW_INMUX_H
#define __AMHW_INMUX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

 /** 
 * \addtogroup amhw_if_inmux
 * \copydoc amhw_inmux.h
 * @{
 */
 
/**
 * \brief  输入复用寄存器块结构体
 */
typedef struct amhw_inmux {
    __IO uint32_t reserved0[6];         /**< \brief 保留                     */
    __I  uint32_t reserved1[42];        /**< \brief 保留                     */
    __IO uint32_t pintsel[8];           /**< \brief 引脚中断选择寄存器       */
    __IO uint32_t dma_itrig_inmux[22];  /**< \brief DMA 触发源输入复用寄存器 */
    __I  uint32_t reserved2[2];         /**< \brief 保留                     */  
    __IO uint32_t dma_otrig_inmux[4];   /**< \brief DMA 输出触发反馈寄存器   */
    __I  uint32_t reserved3[4];         /**< \brief 保留                     */
    __IO uint32_t freqmeas_ref;         /**< \brief 频率测量参考时钟选择     */ 
    __IO uint32_t freqmeas_target;      /**< \brief 频率测量目标时钟选择     */
} amhw_inmux_t;


/**
 * \name LPC5410X 引脚中断选择
 * \anchor grp_amhw_inmux_chan
 * @{
 */
 
#define AMHW_INMUX_CHAN_0         0    /**< \brief 引脚中断通道 0 */
#define AMHW_INMUX_CHAN_1         1    /**< \brief 引脚中断通道 1 */
#define AMHW_INMUX_CHAN_2         2    /**< \brief 引脚中断通道 2 */
#define AMHW_INMUX_CHAN_3         3    /**< \brief 引脚中断通道 3 */
#define AMHW_INMUX_CHAN_4         4    /**< \brief 引脚中断通道 4 */
#define AMHW_INMUX_CHAN_5         5    /**< \brief 引脚中断通道 5 */
#define AMHW_INMUX_CHAN_6         6    /**< \brief 引脚中断通道 6 */
#define AMHW_INMUX_CHAN_7         7    /**< \brief 引脚中断通道 7 */

/** @} */

/**
 * \brief 引脚中断通道选择引脚
 *
 * \param[in] p_hw_inmux : 指向输入复用寄存器块的指针
 * \param[in] pint_sel   : GPIO 引脚中断通道号，参见
 *                         \ref grp_amhw_inmux_chan
 * \param[in] pin       : 引脚编号，值为 PIO* (#PIO0_0)
 *
 * \return  无
 */
am_static_inline 
void amhw_inmux_pint_sel (amhw_inmux_t *p_hw_inmux,
                          int           pint_sel,
                          int           pin)
{
    p_hw_inmux->pintsel[pint_sel] = pin;
}


/** \brief DMA 触发信号源 */
typedef enum amhw_inmux_dma_trigsrc {
    AMHW_INMUX_DMATRIG_ADC0_SEQA_IRQ = 0, /**< \brief ADC0 序列A中断     */
    AMHW_INMUX_DMATRIG_ADC0_SEQB_IRQ,     /**< \brief ADC0 序列B中断     */
    AMHW_INMUX_DMATRIG_SCT0_DMA0,         /**< \brief SCT 0 DMA 0 请求   */
    AMHW_INMUX_DMATRIG_SCT0_DMA1,         /**< \brief SCT 1 DMA 1 请求   */
    AMHW_INMUX_DMATRIG_TIMER0_MATCH0,     /**< \brief Timer 0 匹配 0     */
    AMHW_INMUX_DMATRIG_TIMER0_MATCH1,     /**< \brief Timer 0 匹配 1     */
    AMHW_INMUX_DMATRIG_TIMER1_MATCH0,     /**< \brief Timer 1 匹配 0     */
    AMHW_INMUX_DMATRIG_TIMER2_MATCH0,     /**< \brief Timer 2 匹配 0     */
    AMHW_INMUX_DMATRIG_TIMER2_MATCH1,     /**< \brief Timer 2 匹配 1     */
    AMHW_INMUX_DMATRIG_TIMER3_MATCH0,     /**< \brief Timer 3 匹配 0     */
    AMHW_INMUX_DMATRIG_TIMER4_MATCH0,     /**< \brief Timer 4 匹配 0     */
    AMHW_INMUX_DMATRIG_TIMER4_MATCH1,     /**< \brief Timer 4 匹配 1     */
    AMHW_INMUX_DMATRIG_PININT0,           /**< \brief 引脚中断 0         */
    AMHW_INMUX_DMATRIG_PININT1,           /**< \brief 引脚中断 1         */
    AMHW_INMUX_DMATRIG_PININT2,           /**< \brief 引脚中断 2         */
    AMHW_INMUX_DMATRIG_PININT3,           /**< \brief 引脚中断 3         */
    AMHW_INMUX_DMATRIG_OUTMUX0,           /**< \brief DMA 输出触发复用 0 */
    AMHW_INMUX_DMATRIG_OUTMUX1,           /**< \brief DMA 输出触发复用 1 */
    AMHW_INMUX_DMATRIG_OUTMUX2,           /**< \brief DMA 输出触发复用 2 */
    AMHW_INMUX_DMATRIG_OUTMUX3            /**< \brief DMA 输出触发复用 3 */
} amhw_inmux_dma_trigsrc_t;

/**
 * \brief 为指定DMA通道选择触发源
 *
 * \param[in] p_hw_inmux : 指向输入复用寄存器块的指针
 * \param[in] chan       : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                         (#DMA_CHAN_USART0_RX_REQ)
* \param[in] trig        : 触发源
 *
 * \return 无
 */
am_static_inline 
void amhw_inmux_dma_trig_set (amhw_inmux_t            *p_hw_inmux,
                              int                      chan, 
                              amhw_inmux_dma_trigsrc_t trig)
{
    p_hw_inmux->dma_itrig_inmux[chan] = (uint32_t)trig;
}

/** 
 * \brief DMA通道选择做输出触发源
 */
typedef enum amhw_inmux_dma_otrig {
    AMHW_INMUX_DMATRIG_OUT0 = 0,  /**< \brief DMA 输出触发源 0 */
    AMHW_INMUX_DMATRIG_OUT1,      /**< \brief DMA 输出触发源 1 */
    AMHW_INMUX_DMATRIG_OUT2,      /**< \brief DMA 输出触发源 2 */
    AMHW_INMUX_DMATRIG_OUT3       /**< \brief DMA 输出触发源 3 */
} amhw_inmux_dma_otrig_t;

/**
 * \brief 选择DMA通道作输出触发源
 *
 * \param[in] p_hw_inmux : 指向输入复用寄存器块的指针
 * \param[in] index      : 选择输出通道 (#AMHW_INMUX_DMATRIG_OUT0).
 * \param[in] chan       : DMA通道，值为 DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                         (#DMA_CHAN_USART0_RX_REQ). 只能是 DMA_CHAN_0 到 DMA_CHAN_19.
 *
 * \return 无
 */
am_static_inline 
void amhw_inmux_dma_outmux_set (amhw_inmux_t           *p_hw_inmux, 
                                amhw_inmux_dma_otrig_t  index, 
                                int                     chan)
{
    p_hw_inmux->dma_otrig_inmux[index] = (uint32_t)chan;
}

/**
 * \brief 频率测量的参考时钟和目标时钟源
 */
typedef enum amhw_inmux_freqmsr_src {
    AMHW_INMUX_FREQMSR_SRC_CLKIN = 0, /**< \brief 时钟输入           */
    AMHW_INMUX_FREQMSR_SRC_IRC,       /**< \brief IRC 振荡器         */
    AMHW_INMUX_FREQMSR_SRC_WDTOSC,    /**< \brief 看门狗时钟振荡器   */
    AMHW_INMUX_FREQMSR_SRC_32KHZOSC,  /**< \brief 32KHz (RTC) 振荡器 */
    AMHW_INMUX_FREQMSR_SRC_MAINCLK,   /**< \brief 主时钟             */
    AMHW_INMUX_FREQMSR_SRC_PIO0_4,    /**< \brief 外部引脚 PIO0_4    */
    AMHW_INMUX_FREQMSR_SRC_PIO0_20,   /**< \brief 外部引脚 PIO0_20   */
    AMHW_INMUX_FREQMSR_SRC_PIO0_24,   /**< \brief 外部引脚 PIO0_24   */
    AMHW_INMUX_FREQMSR_SRC_PIO1_4     /**< \brief 外部引脚 PIO1_4    */
} amhw_inmux_freqmsr_src_t;

/**
 * \brief 选择参考时钟实现频率测量
 *
 * \param[in] p_hw_inmux : 指向输入复用寄存器块的指针
 * \param[in] ref_src    : 参考时钟
 *
 * \return 无
 */
am_static_inline 
void amhw_inmux_freqmsr_refclk_set (amhw_inmux_t            *p_hw_inmux, 
                                    amhw_inmux_freqmsr_src_t ref_src)
{
    p_hw_inmux->freqmeas_ref = (uint32_t)ref_src;
}

/**
 * \brief 选择目标时钟实现频率测量
 *
 * \param[in] p_hw_inmux : 指向输入复用寄存器块的指针
 * \param[in] targ_src   : 目标时钟
 *
 * \return 无
 */
am_static_inline 
void amhw_inmux_freqmsr_targclk_set (amhw_inmux_t             *p_hw_inmux, 
                                     amhw_inmux_freqmsr_src_t  targ_src)
{
    p_hw_inmux->freqmeas_target = (uint32_t)targ_src;
}

/**
 * @} 
 */


#ifdef __cplusplus
}
#endif

#endif /* __AMHW_INMUX_H */

/* end of file */

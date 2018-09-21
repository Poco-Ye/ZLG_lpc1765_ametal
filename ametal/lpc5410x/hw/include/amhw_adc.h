/*******************************************************************************
*                                Apollo
*                      ----------------------------
*                      innovating embedded platform
*
*Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
*All rights reserved.
*
*Contact information:
*web site:    http://www.zlg.cn/
*e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC 硬件操作接口
 *
 * 1. 12位逐次逼近型数模转换器；
 * 2. 模拟输入引脚多达12个；
 * 3. 2个独立触发的转换序列；
 * 4. 可选择高/低阈值比较和“零点穿越”监测；
 * 5. 电压测量范围从 Vrefn 到 Vrefp (典型值为 3V; 不可超出 VDD 的电压值)；
 * 6. 12位的转换速率高达 4.8 MHz. 可减小转换精度来实现更高的转换速率；
 * 7. 突发转换模式支持单通道或多通道输入；
 * 8. 同步或异步操作. 在 ADC 的时钟频率内，异步操作可灵活适应. 同步模式可减少
 *    潜在的触发干扰、消除不确定触发和因抖动引起的触发响应等。
 *
 * \internal
 * \par Modification history
 * - 1.10 14-12-01  hbt, modified.
 * - 1.00 14-12-01  tee, first implementation.
 * \endinternal
 */
#ifndef  __AMHW_ADC_H
#define  __AMHW_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
#include "am_types.h"

/**
 * \addtogroup amhw_if_adc 
 * \copydoc amhw_adc.h
 * @{
 */

/**
 * \brief 使用匿名联合体段开始
 * @{
 */
 
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
    
  /* 默认使能匿名联合体 */
#elif defined(__TMS470__)

  /* 默认使能匿名联合体 */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */


/**
 * \brief ADC 寄存器块结构体
 */
typedef struct amhw_adc {
    volatile uint32_t ctrl;                      /**< \brief ADC 控制寄存器          */
    volatile uint32_t inputsel;                  /**< \brief ADC 输入控制寄存器      */
    union {
        volatile uint32_t seq_ctrl[2];
        struct {
            volatile uint32_t seqa_ctrl;         /**< \brief ADC 序列A控制寄存器     */
            volatile uint32_t seqb_ctrl;         /**< \brief ADC 序列B控制寄存器     */
        };
    };
    union {
        const volatile uint32_t seq_gdat[2];
        struct {
            const volatile uint32_t seqa_gdat;   /**< \brief ADC 序列A全局数据寄存器 */
            const volatile uint32_t seqb_gdat;   /**< \brief ADC 序列B全局数据寄存器 */
        };
    };
    uint32_t reserved[2];                        /**< \brief 保留                    */
    union {
        const volatile uint32_t dat[12];         /**< \brief ADC 通道数据寄存器      */
        struct {
            const volatile uint32_t dat0;        /**< \brief ADC 通道0数据寄存器     */
            const volatile uint32_t dat1;        /**< \brief ADC 通道1数据寄存器     */
            const volatile uint32_t dat2;        /**< \brief ADC 通道2数据寄存器     */
            const volatile uint32_t dat3;        /**< \brief ADC 通道3数据寄存器     */
            const volatile uint32_t dat4;        /**< \brief ADC 通道4数据寄存器     */
            const volatile uint32_t dat5;        /**< \brief ADC 通道5数据寄存器     */
            const volatile uint32_t dat6;        /**< \brief ADC 通道6数据寄存器     */
            const volatile uint32_t dat7;        /**< \brief ADC 通道7数据寄存器     */
            const volatile uint32_t dat8;        /**< \brief ADC 通道8数据寄存器     */
            const volatile uint32_t dat9;        /**< \brief ADC 通道9数据a寄存器    */
            const volatile uint32_t dat10;       /**< \brief ADC 通道10数据寄存器    */
            const volatile uint32_t dat11;       /**< \brief ADC 通道11数据寄存器    */
        };
    };
    union {
        volatile uint32_t thr_low[2];
        struct {
            volatile uint32_t thr0_low;          /**< \brief ADC 低阈值寄存器 0      */
            volatile uint32_t thr1_low;          /**< \brief ADC 低阈值寄存器 1      */
        };
    };
    union {
        volatile uint32_t thr_high[2];
        struct {
            volatile uint32_t thr0_high;         /**< \brief ADC 高阈值寄存器 0      */
            volatile uint32_t thr1_high;         /**< \brief ADC 高阈值寄存器 1      */
        };
    };
    volatile uint32_t chan_thrsel;       /**< \brief ADC 通道阈值选择寄存器          */
    volatile uint32_t inten;             /**< \brief ADC 中断使能寄存器              */
    volatile uint32_t flags;             /**< \brief ADC 中断请求标志寄存器          */
    volatile uint32_t startup;           /**< \brief ADC 启动寄存器                  */
    volatile uint32_t calibr;            /**< \brief ADC 校验寄存器                  */
} amhw_adc_t;


/**
 * \name ADC 通道编号
 * \anchor grp_amhw_adc_chan
 * @{
 */

#define AMHW_ADC0_CHAN_0          0          /**< \brief ADC 通道 0   */
#define AMHW_ADC0_CHAN_1          1          /**< \brief ADC 通道 1   */
#define AMHW_ADC0_CHAN_2          2          /**< \brief ADC 通道 2   */
#define AMHW_ADC0_CHAN_3          3          /**< \brief ADC 通道 3   */
#define AMHW_ADC0_CHAN_4          4          /**< \brief ADC 通道 4   */
#define AMHW_ADC0_CHAN_5          5          /**< \brief ADC 通道 5   */
#define AMHW_ADC0_CHAN_6          6          /**< \brief ADC 通道 6   */
#define AMHW_ADC0_CHAN_7          7          /**< \brief ADC 通道 7   */
#define AMHW_ADC0_CHAN_8          8          /**< \brief ADC 通道 8   */
#define AMHW_ADC0_CHAN_9          9          /**< \brief ADC 通道 9   */
#define AMHW_ADC0_CHAN_10         10         /**< \brief ADC 通道 10  */
#define AMHW_ADC0_CHAN_11         11         /**< \brief ADC 通道 11  */

/** @} */

#define AMHW_ADC_CHAN_CNT         12         /**< \brief ADC 通道数量 */

/**
 * \brief ADC 序列寄存器索引
 */
typedef enum amhw_adc_seq_index {
    AMHW_ADC_SEQ_A = 0,                      /**< \brief 序列A索引    */
    AMHW_ADC_SEQ_B,                          /**< \brief 序列B索引    */
} amhw_adc_seq_index_t;


/**
 * \brief ADC 阈值比较索引
 */
typedef enum amhw_adc_comp_thre_index {
    AMHW_ADC_COMP_THRE_0,                    /**< \brief 阈值比较0索引 */
    AMHW_ADC_COMP_THRE_1,                    /**< \brief 阈值比较1索引 */
} amhw_adc_comp_thre_index_t;


/**
 * \name ADC 控制寄存器位域定义
 * \anchor grp_amhw_adc_ctrl
 * @{
 */
 
#define AMHW_ADC_CTRL_CLK_DIV(x)     ((x) & 0xFF)         /**< \brief 设置时钟分频值 @a x   */

#define AMHW_ADC_CTRL_MODE_SYNC      (0UL << 8)           /**< \brief 设置同步模式          */
#define AMHW_ADC_CTRL_MODE_ASYNC     (1UL << 8)           /**< \brief 设置异步模式          */

#define AMHW_ADC_CTRL_RESOL_6BIT     (0UL << 9)           /**< \brief 设置ADC精度为 6 bits  */
#define AMHW_ADC_CTRL_RESOL_8BIT     (1UL << 9)           /**< \brief 设置ADC精度为 8 bits  */
#define AMHW_ADC_CTRL_RESOL_10BIT    (2UL << 9)           /**< \brief 设置ADC精度为 10 bits */
#define AMHW_ADC_CTRL_RESOL_12BIT    (3UL << 9)           /**< \brief 设置ADC精度为 12 bits */
#define AMHW_ADC_CTRL_RESOL_NBIT(n)  (((n / 2) - 3) << 9) /**< \brief 设置ADC精度为 n bits  */

#define AMHW_ADC_CTRL_BYPASS_CALIB   (1UL << 11)          /**< \brief 忽略校验              */
#define AMHW_ADC_CTRL_CALIB          (0UL << 11)          /**< \brief 使能检验              */

#define AMHW_ADC_CTRL_SAMPLE_TIME(x) (((x) & 7) << 12)    /**< \brief 设置采样时间 @a x     */

/** @} */

/**
 * \brief 启动ADC
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 *
 * \retval  AM_OK      : 启动成功
 * \retval -AM_ETIME   : 超时
 */
int amhw_adc_startup(amhw_adc_t *p_hw_adc);

/**
 * \brief ADC 校验
 *
 * \param[in] p_hw_adc    : 指向ADC寄存器块的指针
 * \param[in] sysclk_freq : 主时钟频率
 *
 * \return  无
 */
void amhw_adc_calibrate(amhw_adc_t *p_hw_adc, uint32_t sysclk_freq);

/**
 * \brief ADC 控制配置
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] flags    : 功能配置参数，参见
 *                       \ref grp_amhw_adc_ctrl
 *
 * \return    无
 */
am_static_inline
void amhw_adc_config (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->ctrl = flags;
}

/**
 * \brief 获取 ADC 控制寄存器状态 
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \return 控制寄存器状态 
 */
am_static_inline
uint32_t amhw_adc_ctrl_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->ctrl;
}


/**
 * \name ADC 序列控制寄存器位域定义 
 * \anchor grp_amhw_adc_seq_ctrl
 * @{
 */

#define AMHW_ADC_SEQ_CTRL_TRIG_SOFT      (0UL << 12)     /**< \brief 软件触发                 */
#define AMHW_ADC_SEQ_CTRL_TRIG_PININT0   (0UL << 12)     /**< \brief 使用 pinint0 做硬件触发  */
#define AMHW_ADC_SEQ_CTRL_TRIG_PININT1   (1UL << 12)     /**< \brief 使用 pinint1 做硬件触发  */
#define AMHW_ADC_SEQ_CTRL_TRIG_ARMTXEV   (5UL << 12)     /**< \brief 使用 arm_txev 做硬件触发 */
#define AMHW_ADC_SEQ_CTRL_TRIG_POL_NEG   (0UL << 18)     /**< \brief 阴极触发                 */
#define AMHW_ADC_SEQ_CTRL_TRIG_POL_POS   (1UL << 18)     /**< \brief 阳极触发                 */

#define AMHW_ADC_SEQ_CTRL_BYPASS_SYNC    (1UL << 19)     /**< \brief 忽略同步触发             */

/** \brief 使能突发转换模式 */
#define AMHW_ADC_SEQ_CTRL_MODE_BURST     ((1UL << 27) | (0UL << 26))
                                             
#define AMHW_ADC_SEQ_CTRL_MODE_SINGLE    (1UL << 28)     /**< \brief 使能单次转换模式         */

#define AMHW_ADC_SEQ_CTRL_SEQA_PIRO_HIGH (1UL << 29)     /**< \brief 序列A高优先级            */

#define AMHW_ADC_SEQ_CTRL_MODE_EOC       (0UL << 30)     /**< \brief 转换完成产生事件         */
#define AMHW_ADC_SEQ_CTRL_MODE_EOS       (1UL << 30)     /**< \brief 序列转换完成产生事件     */

#define AMHW_ADC_SEQ_CTRL_ENABLE_CH(ch)  (1UL << (ch))   /**< \brief 使能ADC通道              */

/** @} */


/**
 * \brief ADC 转换序列配置
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 * \param[in] flags    : 功能配置参数，参见
 *                       \ref grp_amhw_adc_seq_ctrl
 *
 * \return  无
 */
am_static_inline
void amhw_adc_seq_config (amhw_adc_t          *p_hw_adc,
                          amhw_adc_seq_index_t index, 
                          uint32_t             flags)
{
    p_hw_adc->seq_ctrl[index] = flags;
}

/**
 * \brief 获取 ADC 序列转换配置状态
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 *
 * \return  ADC 序列转换配置状态
 */
am_static_inline
uint32_t amhw_adc_seq_ctrl_get (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    return p_hw_adc->seq_ctrl[index];
}

/**
 * \brief 启动ADC序列转换
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 *
 * \return  无
 */
am_static_inline
void amhw_adc_seq_start (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] |= (1UL << 26);
}

/**
 * \brief 使能ADC转换序列
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 *
 * \return  无
 */
am_static_inline
void amhw_adc_seq_enable (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] |= (1UL << 31);
}

/**
 * \brief 禁能ADC转换序列
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 *
 * \return  无
 */
am_static_inline
void amhw_adc_seq_disable (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] &= ~(1UL << 31);
}

/**
 * \brief ADC转换序列使能和启动
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 *
 * \return  无
 */
am_static_inline  
void amhw_adc_seq_start_and_enable (amhw_adc_t          *p_hw_adc, 
                                    amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] |= (1UL << 31) | (1UL << 26);
}

/**
 * \brief 使能ADC转换序列的通道
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针。
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 * \param[in] chan     : ADC 通道, 参见
 *                       \ref grp_amhw_adc_chan
 * \return  无
 */
am_static_inline  
void amhw_adc_seq_chan_set (amhw_adc_t          *p_hw_adc, 
                            amhw_adc_seq_index_t index, 
                            int                  chan)
{
    p_hw_adc->seq_ctrl[index] &= ~(1UL << 31);
    p_hw_adc->seq_ctrl[index] |= ((1UL << chan) | (1UL << 31 ));
}

/**
 * \name 数据寄存器位域定义
 * \anchor grp_amhw_adc_data_reg
 * @{
 */

#define AMHW_ADC_DR_RESULT(n)     (((n) >> 4) & 0xFFF) /**< \brief 获取ADC转换值    */

#define AMHW_ADC_DR_THCMPRANGE(n) (((n) >> 16) & 0x3)  /**< \brief 阈值穿越比较结果 */
#define AMHW_ADC_DR_THCMPCROSS(n) (((n) >> 18) & 0x3)  /**< \brief 阈值范围比较结果 */

#define AMHW_ADC_DR_CHANNEL(n)    (((n) >> 26) & 0xF)  /**< \brief 当前转换的通道号 */

#define AMHW_ADC_DR_OVERRUN       (1UL << 30)          /**< \brief 溢出标志位       */
#define AMHW_ADC_DR_DATAVALID     (1UL << 31)          /**< \brief 数据有效位       */

/** @} */

/**
 * \brief 从通道数据寄存器获取ADC转换值
 *
 * 返回值是 \ref grp_amhw_adc_data_reg 中的 'n' 
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] chan     : ADC 通道, 参见
 *                       \ref grp_amhw_adc_chan
 *
 * \return  ADC转换值
 */
am_static_inline
uint32_t amhw_adc_chan_data_get (amhw_adc_t *p_hw_adc, int chan)
{
    return (p_hw_adc->dat[chan]);
}

/**
 * \brief 从全局数据寄存器获取ADC转换值
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC转换序列，
 *                       (#AMHW_ADC_SEQ_A) 或 (#AMHW_ADC_SEQ_B)
 *
 * \return  ADC转换值
 */
am_static_inline
uint32_t amhw_adc_glo_data_get (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    return (p_hw_adc->seq_gdat[index]);
}

/**
 * \brief 设置ADC低比较阈值
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC阈值比较，
 *                       (#AMHW_ADC_COMP_THRE_0) 或 (#AMHW_ADC_COMP_THRE_1)
 * \param[in] value    : 设置的低阈值
 *
 * \return  无
 */
am_static_inline 
void amhw_adc_thr_low_set (amhw_adc_t                 *p_hw_adc,
                           amhw_adc_comp_thre_index_t  index,
                           uint32_t                    value)
{
    p_hw_adc->thr_low[index] |= (value << 4); 
}

/**
 * \brief 设置ADC高比较阈值
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] index    : 选择ADC阈值比较，
 *                       (#AMHW_ADC_COMP_THRE_0) 或 (#AMHW_ADC_COMP_THRE_1)
 * \param[in] value    : 设置的高阈值
 *
 * \return  无
 */
am_static_inline 
void amhw_adc_thr_high_set (amhw_adc_t                 *p_hw_adc,
                            amhw_adc_comp_thre_index_t  index,
                            uint32_t                    value)
{
    p_hw_adc->thr_high[index] |= (value << 4);
}

/**
 * \brief 阈值比较0选择通道号
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] chan     : ADC 通道, 参见
 *                       \ref grp_amhw_adc_chan
 *
 * \return  无
 */
am_static_inline 
void amdr_adc_thr0_sel (amhw_adc_t *p_hw_adc, int chan)
{
    p_hw_adc->chan_thrsel &= ~(1UL << chan); 
}

/**
 * \brief 阈值比较1选择通道号
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] chan     : ADC 通道, 参见
 *                       \ref grp_amhw_adc_chan
 *
 * \return  无
 */
am_static_inline 
void amdr_adc_thr1_sel (amhw_adc_t *p_hw_adc, int chan)
{
    p_hw_adc->chan_thrsel |= (1UL << chan);
}

/**
 * \name ADC中断使能寄存器位域定义
 * \anchor grp_amhw_adc_inten
 * @{
 */
 
#define AMHW_ADC_INTEN_SEQA_ENABLE       (1UL << 0)                /**< \brief 序列A中断使能位      */
#define AMHW_ADC_INTEN_SEQB_ENABLE       (1UL << 1)                /**< \brief 序列B中断使能位      */
#define AMHW_ADC_INTEN_OVRRUN_ENABLE     (1UL << 2)                /**< \brief 溢出中断使能位       */

#define AMHW_ADC_INTEN_CMP_DISBALE(ch)   (0x0UL << (2 * (ch) + 3)) /**< \brief 禁能阈值比较中断     */
#define AMHW_ADC_INTEN_CMP_OUTSIDETH(ch) (0x1UL << (2 * (ch) + 3)) /**< \brief 使能外部阈值比较中断 */
#define AMHW_ADC_INTEN_CMP_CROSSTH(ch)   (0x2UL << (2 * (ch) + 3)) /**< \brief 使能穿越阈值比较中断 */

/** @} */

/**
 * \brief ADC 中断使能
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] flag     : 中断配置参数，参见
 *                       \ref grp_amhw_adc_inten
 * \return  无
 */
am_static_inline 
void amhw_adc_int_enable (amhw_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->inten = flag;
}

/**
 * \name ADC 标志寄存器位域定义
 * \anchor grp_amhw_adc_flags
 * @{
 */
 
#define AMHW_ADC_FLAGS_THCMP_MASK(ch)   (1UL << (ch))         /**< \brief 通道阈值比较标志 */
#define AMHW_ADC_FLAGS_OVRRUN_MASK(ch)  (1UL << (12 + (ch)))  /**< \brief 通道溢出标志     */
#define AMHW_ADC_FLAGS_SEQA_OVRRUN_MASK (1UL << 24)           /**< \brief 序列A溢出标志    */
#define AMHW_ADC_FLAGS_SEQB_OVRRUN_MASK (1UL << 25)           /**< \brief 序列B溢出标志    */
#define AMHW_ADC_FLAGS_SEQA_INT_MASK    (1UL << 28)           /**< \brief 序列A中断标志    */
#define AMHW_ADC_FLAGS_SEQB_INT_MASK    (1UL << 29)           /**< \brief 序列B中断标志    */
#define AMHW_ADC_FLAGS_THCMP_INT_MASK   (1UL << 30)           /**< \brief 阈值比较中断标志 */
#define AMHW_ADC_FLAGS_OVRRUN_INT_MASK  (1UL << 31)           /**< \brief 溢出中断标志     */

/** @} */

/**
 * \brief 获取中断标志
 * 
 * 和 \ref grp_amhw_adc_flags 的参数进行与操作获取具体状态
 *
 * \par 示例
 * \code 
 * if (amhw_adc_flags_get(p_hw_adc) & AMHW_ADC_FLAGS_SEQA_INT_MASK) (
 * // do something.
 * )
 * \endcode
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针。
 * \return  中断标志.
 */
am_static_inline 
uint32_t amhw_adc_flags_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->flags;
}

/**
 * \brief 清除中断标志
 * 
 * 和 \ref grp_amhw_adc_flags 的参数进行与操作获取具体状态
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针。
 * \param[in] flags    : 中断标志参数, 参见 \ref grp_amhw_adc_flags 
 * 
 * \return  无
 */
am_static_inline 
void amhw_adc_flags_clr (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->flags = flags;
}

/**
 * \name 启动设置参数
 * \anchor grp_amhw_adc_startup
 * @{
 */

#define AMHW_ADC_STARTUP_ENA      (1UL << 0)    /**< \brief 使能ADC   */
#define AMHW_ADC_STARTUP_INIT     (1UL << 1)    /**< \brief 初始化ADC */

/** @} */

/**
 * \brief 设置ADC启动
 *
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \param[in] flags    : 启动参数，参见 \ref grp_amhw_adc_startup 
 * 
 * \return  无
 */
am_static_inline
void amhw_adc_startup_set (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->startup = flags;
}

/**
 * \brief 获取ADC启动状态
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针。
 * \return  启动状态
 */
am_static_inline
uint32_t amhw_adc_startup_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->startup;
}

/**
 * \brief 使能ADC校验请求
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \return  无
 */
am_static_inline
void amhw_adc_calib_enable (amhw_adc_t *p_hw_adc)
{
    p_hw_adc->calibr |= (1UL << 0);
}

/**
 * \brief 获取ADC检验执行状态
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \return  无
 */
am_static_inline
bool_t amhw_adc_calib_get (amhw_adc_t *p_hw_adc)
{
    return (bool_t)((p_hw_adc->calibr & 0x1) ? 0 : 1);
}

/**
 * \brief 查看ADC检验执行状态
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 *
 * \retval  TRUE  : ADC校验请求执行
 * \retval  FALSE : ADC校验请求未执行
 */
am_static_inline
bool_t amhw_adc_calib_isrun (amhw_adc_t *p_hw_adc)
{
    return (bool_t)((p_hw_adc->calibr >> 1) & 0x01);
}

/**
 * \brief 获取ADC校验值
 * \param[in] p_hw_adc : 指向ADC寄存器块的指针
 * \return ADC校验值
 */
am_static_inline
uint32_t amhw_adc_calib_value_get (amhw_adc_t *p_hw_adc)
{
    return (p_hw_adc->calibr >> 2);
}

/**
 * \brief 使用匿名联合体段结束
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
 
  /* 允许匿名联合体使能 */
#elif defined(__GNUC__)

  /* 默认使用匿名联合体 */
#elif defined(__TMS470__)

  /* 默认使用匿名联合体 */
#elif defined(__TASKING__)
  #pragma warning restore
#else
  #warning Not supported compiler t
#endif

/** @} */


/**
 *@} 
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMHW_ADC_H */

/* end of file */

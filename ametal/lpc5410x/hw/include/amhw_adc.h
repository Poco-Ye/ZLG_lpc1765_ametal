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
 * \brief ADC Ӳ�������ӿ�
 *
 * 1. 12λ��αƽ�����ģת������
 * 2. ģ���������Ŷ��12����
 * 3. 2������������ת�����У�
 * 4. ��ѡ���/����ֵ�ȽϺ͡���㴩Խ����⣻
 * 5. ��ѹ������Χ�� Vrefn �� Vrefp (����ֵΪ 3V; ���ɳ��� VDD �ĵ�ѹֵ)��
 * 6. 12λ��ת�����ʸߴ� 4.8 MHz. �ɼ�Сת��������ʵ�ָ��ߵ�ת�����ʣ�
 * 7. ͻ��ת��ģʽ֧�ֵ�ͨ�����ͨ�����룻
 * 8. ͬ�����첽����. �� ADC ��ʱ��Ƶ���ڣ��첽�����������Ӧ. ͬ��ģʽ�ɼ���
 *    Ǳ�ڵĴ������š�������ȷ���������򶶶�����Ĵ�����Ӧ�ȡ�
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
 * \brief ʹ������������ο�ʼ
 * @{
 */
 
#if defined(__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined(__ICCARM__)
  #pragma language=extended
#elif defined(__GNUC__)
    
  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
#elif defined(__TASKING__)
  #pragma warning 586
#else
  #warning Not supported compiler t
#endif

/** @} */


/**
 * \brief ADC �Ĵ�����ṹ��
 */
typedef struct amhw_adc {
    volatile uint32_t ctrl;                      /**< \brief ADC ���ƼĴ���          */
    volatile uint32_t inputsel;                  /**< \brief ADC ������ƼĴ���      */
    union {
        volatile uint32_t seq_ctrl[2];
        struct {
            volatile uint32_t seqa_ctrl;         /**< \brief ADC ����A���ƼĴ���     */
            volatile uint32_t seqb_ctrl;         /**< \brief ADC ����B���ƼĴ���     */
        };
    };
    union {
        const volatile uint32_t seq_gdat[2];
        struct {
            const volatile uint32_t seqa_gdat;   /**< \brief ADC ����Aȫ�����ݼĴ��� */
            const volatile uint32_t seqb_gdat;   /**< \brief ADC ����Bȫ�����ݼĴ��� */
        };
    };
    uint32_t reserved[2];                        /**< \brief ����                    */
    union {
        const volatile uint32_t dat[12];         /**< \brief ADC ͨ�����ݼĴ���      */
        struct {
            const volatile uint32_t dat0;        /**< \brief ADC ͨ��0���ݼĴ���     */
            const volatile uint32_t dat1;        /**< \brief ADC ͨ��1���ݼĴ���     */
            const volatile uint32_t dat2;        /**< \brief ADC ͨ��2���ݼĴ���     */
            const volatile uint32_t dat3;        /**< \brief ADC ͨ��3���ݼĴ���     */
            const volatile uint32_t dat4;        /**< \brief ADC ͨ��4���ݼĴ���     */
            const volatile uint32_t dat5;        /**< \brief ADC ͨ��5���ݼĴ���     */
            const volatile uint32_t dat6;        /**< \brief ADC ͨ��6���ݼĴ���     */
            const volatile uint32_t dat7;        /**< \brief ADC ͨ��7���ݼĴ���     */
            const volatile uint32_t dat8;        /**< \brief ADC ͨ��8���ݼĴ���     */
            const volatile uint32_t dat9;        /**< \brief ADC ͨ��9����a�Ĵ���    */
            const volatile uint32_t dat10;       /**< \brief ADC ͨ��10���ݼĴ���    */
            const volatile uint32_t dat11;       /**< \brief ADC ͨ��11���ݼĴ���    */
        };
    };
    union {
        volatile uint32_t thr_low[2];
        struct {
            volatile uint32_t thr0_low;          /**< \brief ADC ����ֵ�Ĵ��� 0      */
            volatile uint32_t thr1_low;          /**< \brief ADC ����ֵ�Ĵ��� 1      */
        };
    };
    union {
        volatile uint32_t thr_high[2];
        struct {
            volatile uint32_t thr0_high;         /**< \brief ADC ����ֵ�Ĵ��� 0      */
            volatile uint32_t thr1_high;         /**< \brief ADC ����ֵ�Ĵ��� 1      */
        };
    };
    volatile uint32_t chan_thrsel;       /**< \brief ADC ͨ����ֵѡ��Ĵ���          */
    volatile uint32_t inten;             /**< \brief ADC �ж�ʹ�ܼĴ���              */
    volatile uint32_t flags;             /**< \brief ADC �ж������־�Ĵ���          */
    volatile uint32_t startup;           /**< \brief ADC �����Ĵ���                  */
    volatile uint32_t calibr;            /**< \brief ADC У��Ĵ���                  */
} amhw_adc_t;


/**
 * \name ADC ͨ�����
 * \anchor grp_amhw_adc_chan
 * @{
 */

#define AMHW_ADC0_CHAN_0          0          /**< \brief ADC ͨ�� 0   */
#define AMHW_ADC0_CHAN_1          1          /**< \brief ADC ͨ�� 1   */
#define AMHW_ADC0_CHAN_2          2          /**< \brief ADC ͨ�� 2   */
#define AMHW_ADC0_CHAN_3          3          /**< \brief ADC ͨ�� 3   */
#define AMHW_ADC0_CHAN_4          4          /**< \brief ADC ͨ�� 4   */
#define AMHW_ADC0_CHAN_5          5          /**< \brief ADC ͨ�� 5   */
#define AMHW_ADC0_CHAN_6          6          /**< \brief ADC ͨ�� 6   */
#define AMHW_ADC0_CHAN_7          7          /**< \brief ADC ͨ�� 7   */
#define AMHW_ADC0_CHAN_8          8          /**< \brief ADC ͨ�� 8   */
#define AMHW_ADC0_CHAN_9          9          /**< \brief ADC ͨ�� 9   */
#define AMHW_ADC0_CHAN_10         10         /**< \brief ADC ͨ�� 10  */
#define AMHW_ADC0_CHAN_11         11         /**< \brief ADC ͨ�� 11  */

/** @} */

#define AMHW_ADC_CHAN_CNT         12         /**< \brief ADC ͨ������ */

/**
 * \brief ADC ���мĴ�������
 */
typedef enum amhw_adc_seq_index {
    AMHW_ADC_SEQ_A = 0,                      /**< \brief ����A����    */
    AMHW_ADC_SEQ_B,                          /**< \brief ����B����    */
} amhw_adc_seq_index_t;


/**
 * \brief ADC ��ֵ�Ƚ�����
 */
typedef enum amhw_adc_comp_thre_index {
    AMHW_ADC_COMP_THRE_0,                    /**< \brief ��ֵ�Ƚ�0���� */
    AMHW_ADC_COMP_THRE_1,                    /**< \brief ��ֵ�Ƚ�1���� */
} amhw_adc_comp_thre_index_t;


/**
 * \name ADC ���ƼĴ���λ����
 * \anchor grp_amhw_adc_ctrl
 * @{
 */
 
#define AMHW_ADC_CTRL_CLK_DIV(x)     ((x) & 0xFF)         /**< \brief ����ʱ�ӷ�Ƶֵ @a x   */

#define AMHW_ADC_CTRL_MODE_SYNC      (0UL << 8)           /**< \brief ����ͬ��ģʽ          */
#define AMHW_ADC_CTRL_MODE_ASYNC     (1UL << 8)           /**< \brief �����첽ģʽ          */

#define AMHW_ADC_CTRL_RESOL_6BIT     (0UL << 9)           /**< \brief ����ADC����Ϊ 6 bits  */
#define AMHW_ADC_CTRL_RESOL_8BIT     (1UL << 9)           /**< \brief ����ADC����Ϊ 8 bits  */
#define AMHW_ADC_CTRL_RESOL_10BIT    (2UL << 9)           /**< \brief ����ADC����Ϊ 10 bits */
#define AMHW_ADC_CTRL_RESOL_12BIT    (3UL << 9)           /**< \brief ����ADC����Ϊ 12 bits */
#define AMHW_ADC_CTRL_RESOL_NBIT(n)  (((n / 2) - 3) << 9) /**< \brief ����ADC����Ϊ n bits  */

#define AMHW_ADC_CTRL_BYPASS_CALIB   (1UL << 11)          /**< \brief ����У��              */
#define AMHW_ADC_CTRL_CALIB          (0UL << 11)          /**< \brief ʹ�ܼ���              */

#define AMHW_ADC_CTRL_SAMPLE_TIME(x) (((x) & 7) << 12)    /**< \brief ���ò���ʱ�� @a x     */

/** @} */

/**
 * \brief ����ADC
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 *
 * \retval  AM_OK      : �����ɹ�
 * \retval -AM_ETIME   : ��ʱ
 */
int amhw_adc_startup(amhw_adc_t *p_hw_adc);

/**
 * \brief ADC У��
 *
 * \param[in] p_hw_adc    : ָ��ADC�Ĵ������ָ��
 * \param[in] sysclk_freq : ��ʱ��Ƶ��
 *
 * \return  ��
 */
void amhw_adc_calibrate(amhw_adc_t *p_hw_adc, uint32_t sysclk_freq);

/**
 * \brief ADC ��������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flags    : �������ò������μ�
 *                       \ref grp_amhw_adc_ctrl
 *
 * \return    ��
 */
am_static_inline
void amhw_adc_config (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->ctrl = flags;
}

/**
 * \brief ��ȡ ADC ���ƼĴ���״̬ 
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ���ƼĴ���״̬ 
 */
am_static_inline
uint32_t amhw_adc_ctrl_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->ctrl;
}


/**
 * \name ADC ���п��ƼĴ���λ���� 
 * \anchor grp_amhw_adc_seq_ctrl
 * @{
 */

#define AMHW_ADC_SEQ_CTRL_TRIG_SOFT      (0UL << 12)     /**< \brief �������                 */
#define AMHW_ADC_SEQ_CTRL_TRIG_PININT0   (0UL << 12)     /**< \brief ʹ�� pinint0 ��Ӳ������  */
#define AMHW_ADC_SEQ_CTRL_TRIG_PININT1   (1UL << 12)     /**< \brief ʹ�� pinint1 ��Ӳ������  */
#define AMHW_ADC_SEQ_CTRL_TRIG_ARMTXEV   (5UL << 12)     /**< \brief ʹ�� arm_txev ��Ӳ������ */
#define AMHW_ADC_SEQ_CTRL_TRIG_POL_NEG   (0UL << 18)     /**< \brief ��������                 */
#define AMHW_ADC_SEQ_CTRL_TRIG_POL_POS   (1UL << 18)     /**< \brief ��������                 */

#define AMHW_ADC_SEQ_CTRL_BYPASS_SYNC    (1UL << 19)     /**< \brief ����ͬ������             */

/** \brief ʹ��ͻ��ת��ģʽ */
#define AMHW_ADC_SEQ_CTRL_MODE_BURST     ((1UL << 27) | (0UL << 26))
                                             
#define AMHW_ADC_SEQ_CTRL_MODE_SINGLE    (1UL << 28)     /**< \brief ʹ�ܵ���ת��ģʽ         */

#define AMHW_ADC_SEQ_CTRL_SEQA_PIRO_HIGH (1UL << 29)     /**< \brief ����A�����ȼ�            */

#define AMHW_ADC_SEQ_CTRL_MODE_EOC       (0UL << 30)     /**< \brief ת����ɲ����¼�         */
#define AMHW_ADC_SEQ_CTRL_MODE_EOS       (1UL << 30)     /**< \brief ����ת����ɲ����¼�     */

#define AMHW_ADC_SEQ_CTRL_ENABLE_CH(ch)  (1UL << (ch))   /**< \brief ʹ��ADCͨ��              */

/** @} */


/**
 * \brief ADC ת����������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 * \param[in] flags    : �������ò������μ�
 *                       \ref grp_amhw_adc_seq_ctrl
 *
 * \return  ��
 */
am_static_inline
void amhw_adc_seq_config (amhw_adc_t          *p_hw_adc,
                          amhw_adc_seq_index_t index, 
                          uint32_t             flags)
{
    p_hw_adc->seq_ctrl[index] = flags;
}

/**
 * \brief ��ȡ ADC ����ת������״̬
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 *
 * \return  ADC ����ת������״̬
 */
am_static_inline
uint32_t amhw_adc_seq_ctrl_get (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    return p_hw_adc->seq_ctrl[index];
}

/**
 * \brief ����ADC����ת��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 *
 * \return  ��
 */
am_static_inline
void amhw_adc_seq_start (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] |= (1UL << 26);
}

/**
 * \brief ʹ��ADCת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 *
 * \return  ��
 */
am_static_inline
void amhw_adc_seq_enable (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] |= (1UL << 31);
}

/**
 * \brief ����ADCת������
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 *
 * \return  ��
 */
am_static_inline
void amhw_adc_seq_disable (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] &= ~(1UL << 31);
}

/**
 * \brief ADCת������ʹ�ܺ�����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 *
 * \return  ��
 */
am_static_inline  
void amhw_adc_seq_start_and_enable (amhw_adc_t          *p_hw_adc, 
                                    amhw_adc_seq_index_t index)
{
    p_hw_adc->seq_ctrl[index] |= (1UL << 31) | (1UL << 26);
}

/**
 * \brief ʹ��ADCת�����е�ͨ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ�롣
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_adc_chan
 * \return  ��
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
 * \name ���ݼĴ���λ����
 * \anchor grp_amhw_adc_data_reg
 * @{
 */

#define AMHW_ADC_DR_RESULT(n)     (((n) >> 4) & 0xFFF) /**< \brief ��ȡADCת��ֵ    */

#define AMHW_ADC_DR_THCMPRANGE(n) (((n) >> 16) & 0x3)  /**< \brief ��ֵ��Խ�ȽϽ�� */
#define AMHW_ADC_DR_THCMPCROSS(n) (((n) >> 18) & 0x3)  /**< \brief ��ֵ��Χ�ȽϽ�� */

#define AMHW_ADC_DR_CHANNEL(n)    (((n) >> 26) & 0xF)  /**< \brief ��ǰת����ͨ���� */

#define AMHW_ADC_DR_OVERRUN       (1UL << 30)          /**< \brief �����־λ       */
#define AMHW_ADC_DR_DATAVALID     (1UL << 31)          /**< \brief ������Чλ       */

/** @} */

/**
 * \brief ��ͨ�����ݼĴ�����ȡADCת��ֵ
 *
 * ����ֵ�� \ref grp_amhw_adc_data_reg �е� 'n' 
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_adc_chan
 *
 * \return  ADCת��ֵ
 */
am_static_inline
uint32_t amhw_adc_chan_data_get (amhw_adc_t *p_hw_adc, int chan)
{
    return (p_hw_adc->dat[chan]);
}

/**
 * \brief ��ȫ�����ݼĴ�����ȡADCת��ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADCת�����У�
 *                       (#AMHW_ADC_SEQ_A) �� (#AMHW_ADC_SEQ_B)
 *
 * \return  ADCת��ֵ
 */
am_static_inline
uint32_t amhw_adc_glo_data_get (amhw_adc_t *p_hw_adc, amhw_adc_seq_index_t index)
{
    return (p_hw_adc->seq_gdat[index]);
}

/**
 * \brief ����ADC�ͱȽ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADC��ֵ�Ƚϣ�
 *                       (#AMHW_ADC_COMP_THRE_0) �� (#AMHW_ADC_COMP_THRE_1)
 * \param[in] value    : ���õĵ���ֵ
 *
 * \return  ��
 */
am_static_inline 
void amhw_adc_thr_low_set (amhw_adc_t                 *p_hw_adc,
                           amhw_adc_comp_thre_index_t  index,
                           uint32_t                    value)
{
    p_hw_adc->thr_low[index] |= (value << 4); 
}

/**
 * \brief ����ADC�߱Ƚ���ֵ
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] index    : ѡ��ADC��ֵ�Ƚϣ�
 *                       (#AMHW_ADC_COMP_THRE_0) �� (#AMHW_ADC_COMP_THRE_1)
 * \param[in] value    : ���õĸ���ֵ
 *
 * \return  ��
 */
am_static_inline 
void amhw_adc_thr_high_set (amhw_adc_t                 *p_hw_adc,
                            amhw_adc_comp_thre_index_t  index,
                            uint32_t                    value)
{
    p_hw_adc->thr_high[index] |= (value << 4);
}

/**
 * \brief ��ֵ�Ƚ�0ѡ��ͨ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_adc_chan
 *
 * \return  ��
 */
am_static_inline 
void amdr_adc_thr0_sel (amhw_adc_t *p_hw_adc, int chan)
{
    p_hw_adc->chan_thrsel &= ~(1UL << chan); 
}

/**
 * \brief ��ֵ�Ƚ�1ѡ��ͨ����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] chan     : ADC ͨ��, �μ�
 *                       \ref grp_amhw_adc_chan
 *
 * \return  ��
 */
am_static_inline 
void amdr_adc_thr1_sel (amhw_adc_t *p_hw_adc, int chan)
{
    p_hw_adc->chan_thrsel |= (1UL << chan);
}

/**
 * \name ADC�ж�ʹ�ܼĴ���λ����
 * \anchor grp_amhw_adc_inten
 * @{
 */
 
#define AMHW_ADC_INTEN_SEQA_ENABLE       (1UL << 0)                /**< \brief ����A�ж�ʹ��λ      */
#define AMHW_ADC_INTEN_SEQB_ENABLE       (1UL << 1)                /**< \brief ����B�ж�ʹ��λ      */
#define AMHW_ADC_INTEN_OVRRUN_ENABLE     (1UL << 2)                /**< \brief ����ж�ʹ��λ       */

#define AMHW_ADC_INTEN_CMP_DISBALE(ch)   (0x0UL << (2 * (ch) + 3)) /**< \brief ������ֵ�Ƚ��ж�     */
#define AMHW_ADC_INTEN_CMP_OUTSIDETH(ch) (0x1UL << (2 * (ch) + 3)) /**< \brief ʹ���ⲿ��ֵ�Ƚ��ж� */
#define AMHW_ADC_INTEN_CMP_CROSSTH(ch)   (0x2UL << (2 * (ch) + 3)) /**< \brief ʹ�ܴ�Խ��ֵ�Ƚ��ж� */

/** @} */

/**
 * \brief ADC �ж�ʹ��
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flag     : �ж����ò������μ�
 *                       \ref grp_amhw_adc_inten
 * \return  ��
 */
am_static_inline 
void amhw_adc_int_enable (amhw_adc_t *p_hw_adc, uint32_t flag)
{
    p_hw_adc->inten = flag;
}

/**
 * \name ADC ��־�Ĵ���λ����
 * \anchor grp_amhw_adc_flags
 * @{
 */
 
#define AMHW_ADC_FLAGS_THCMP_MASK(ch)   (1UL << (ch))         /**< \brief ͨ����ֵ�Ƚϱ�־ */
#define AMHW_ADC_FLAGS_OVRRUN_MASK(ch)  (1UL << (12 + (ch)))  /**< \brief ͨ�������־     */
#define AMHW_ADC_FLAGS_SEQA_OVRRUN_MASK (1UL << 24)           /**< \brief ����A�����־    */
#define AMHW_ADC_FLAGS_SEQB_OVRRUN_MASK (1UL << 25)           /**< \brief ����B�����־    */
#define AMHW_ADC_FLAGS_SEQA_INT_MASK    (1UL << 28)           /**< \brief ����A�жϱ�־    */
#define AMHW_ADC_FLAGS_SEQB_INT_MASK    (1UL << 29)           /**< \brief ����B�жϱ�־    */
#define AMHW_ADC_FLAGS_THCMP_INT_MASK   (1UL << 30)           /**< \brief ��ֵ�Ƚ��жϱ�־ */
#define AMHW_ADC_FLAGS_OVRRUN_INT_MASK  (1UL << 31)           /**< \brief ����жϱ�־     */

/** @} */

/**
 * \brief ��ȡ�жϱ�־
 * 
 * �� \ref grp_amhw_adc_flags �Ĳ��������������ȡ����״̬
 *
 * \par ʾ��
 * \code 
 * if (amhw_adc_flags_get(p_hw_adc) & AMHW_ADC_FLAGS_SEQA_INT_MASK) (
 * // do something.
 * )
 * \endcode
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ�롣
 * \return  �жϱ�־.
 */
am_static_inline 
uint32_t amhw_adc_flags_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->flags;
}

/**
 * \brief ����жϱ�־
 * 
 * �� \ref grp_amhw_adc_flags �Ĳ��������������ȡ����״̬
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ�롣
 * \param[in] flags    : �жϱ�־����, �μ� \ref grp_amhw_adc_flags 
 * 
 * \return  ��
 */
am_static_inline 
void amhw_adc_flags_clr (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->flags = flags;
}

/**
 * \name �������ò���
 * \anchor grp_amhw_adc_startup
 * @{
 */

#define AMHW_ADC_STARTUP_ENA      (1UL << 0)    /**< \brief ʹ��ADC   */
#define AMHW_ADC_STARTUP_INIT     (1UL << 1)    /**< \brief ��ʼ��ADC */

/** @} */

/**
 * \brief ����ADC����
 *
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \param[in] flags    : �����������μ� \ref grp_amhw_adc_startup 
 * 
 * \return  ��
 */
am_static_inline
void amhw_adc_startup_set (amhw_adc_t *p_hw_adc, uint32_t flags)
{
    p_hw_adc->startup = flags;
}

/**
 * \brief ��ȡADC����״̬
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ�롣
 * \return  ����״̬
 */
am_static_inline
uint32_t amhw_adc_startup_get (amhw_adc_t *p_hw_adc)
{
    return p_hw_adc->startup;
}

/**
 * \brief ʹ��ADCУ������
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return  ��
 */
am_static_inline
void amhw_adc_calib_enable (amhw_adc_t *p_hw_adc)
{
    p_hw_adc->calibr |= (1UL << 0);
}

/**
 * \brief ��ȡADC����ִ��״̬
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return  ��
 */
am_static_inline
bool_t amhw_adc_calib_get (amhw_adc_t *p_hw_adc)
{
    return (bool_t)((p_hw_adc->calibr & 0x1) ? 0 : 1);
}

/**
 * \brief �鿴ADC����ִ��״̬
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 *
 * \retval  TRUE  : ADCУ������ִ��
 * \retval  FALSE : ADCУ������δִ��
 */
am_static_inline
bool_t amhw_adc_calib_isrun (amhw_adc_t *p_hw_adc)
{
    return (bool_t)((p_hw_adc->calibr >> 1) & 0x01);
}

/**
 * \brief ��ȡADCУ��ֵ
 * \param[in] p_hw_adc : ָ��ADC�Ĵ������ָ��
 * \return ADCУ��ֵ
 */
am_static_inline
uint32_t amhw_adc_calib_value_get (amhw_adc_t *p_hw_adc)
{
    return (p_hw_adc->calibr >> 2);
}

/**
 * \brief ʹ������������ν���
 * @{
 */

#if defined(__CC_ARM)
  #pragma pop
#elif defined(__ICCARM__)
 
  /* ��������������ʹ�� */
#elif defined(__GNUC__)

  /* Ĭ��ʹ������������ */
#elif defined(__TMS470__)

  /* Ĭ��ʹ������������ */
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

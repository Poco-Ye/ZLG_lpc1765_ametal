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
 * \brief ��׼��ʱ��(Standard counter/timers)�����ӿ�
 *
 * 1. 32λ������/��ʱ����ÿ��������һ��32λ�ɱ��Ԥ��Ƶ����
 * 2. ����ģʽ�Ͷ�ʱģʽ��
 * 3. 4��32λ����ͨ����������ָ�������źŵı��ز���ʱ��ֵ�������¼�ͬʱ������ѡ��
 *   �Ƿ�����ж�����
 * 4. ��ʱ����Ԥ��Ƶ����������Ϊ��ָ���Ĳ����¼����㣬�����Կ��������򵥵�����Ƶ��
 *   ��������ָ���ı������㶨ʱ����Ԥ��Ƶ����������ʱ��ֱֵ����һ�����أ�
 * 5. 4��32λƥ��Ĵ�������:
 *    - ƥ��ʱ�����жϣ�
 *    - ֹͣ��ʱ������ѡ���Ƿ�����жϣ���
 *    - ��λ��ʱ������ѡ���Ƿ�����жϣ���
 * 6. 4���ⲿ����ܽ�����Ӧ��ƥ��Ĵ������������¹��ܣ� 
 *    - ƥ��ʱ�������Ϊ�͵�ƽ��
 *    - ƥ��ʱ�������Ϊ�ߵ�ƽ��
 *    - ƥ��ʱ��ת�����ƽ��
 *    - ƥ��ʱ�ܽ�״̬�ޱ仯��
 * 7. ����ÿ����ʱ������߿ɴ�3·�����ؿ��Ƶ�PWM�����
 *
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  tee, first implementation.
 * \endinternal
 */

#ifndef __AMHW_TIMER_H
#define __AMHW_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"

/** 
 * \addtogroup amhw_if_timer  
 * \copydoc amhw_timer.h
 * @{
 */
    
/**
 * \brief Standard Timer �Ĵ�����ṹ��
 */
typedef struct amhw_timer { 
    __IO uint32_t ir;             /**< \brief �ж�״̬�Ĵ���         */
    __IO uint32_t tcr;            /**< \brief ��ʱ�����ƼĴ���       */
    __IO uint32_t tc;             /**< \brief ��ʱ�������Ĵ���       */
    __IO uint32_t pr;             /**< \brief Ԥ��Ƶ�Ĵ���           */
    __IO uint32_t pc;             /**< \brief Ԥ��Ƶ�����Ĵ���       */
    __IO uint32_t mcr;            /**< \brief ƥ����ƼĴ���         */
    __IO uint32_t mr[4];          /**< \brief ƥ��Ĵ���             */
    __IO uint32_t ccr;            /**< \brief ������ƼĴ���         */
    __IO uint32_t cr[4];          /**< \brief ����Ĵ���             */
    __IO uint32_t emr;            /**< \brief �ⲿƥ��ܽżĴ���     */
    __I  uint32_t reserved0[12];  /**< \brief ��������Ӧʹ��         */
    __IO uint32_t ctcr;           /**< \brief �������ƼĴ���         */
    __IO uint32_t pwmc;           /**< \brief PWM���ƼĴ���          */
} amhw_timer_t;

/**
 * \brief ���һ��ƥ��ͨ���Ƿ�����ж�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ������ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \retval  TRUE  : �жϲ���
 * \retval  FALSE : �ж�δ����
 *
 */
am_static_inline 
bool_t amhw_timer_mat_pending_get (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    return (bool_t)((p_hw_timer->ir & (1 << ch)) != 0);
}

/**
 * \brief ���һ������ͨ���Ƿ�����ж�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : �����Ĳ���ͨ������Чֵ 0 ~ 3
 *
 * \retval  TRUE  : �жϲ���
 * \retval  FALSE : �ж�δ����
 */
am_static_inline  
bool_t amhw_timer_cap_pending_get (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    return (bool_t)((p_hw_timer->ir & (1 << (ch + 4))) != 0);
}

/**
 * \brief ���ƥ���жϱ�־
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ������жϱ�־��ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline
void amhw_timer_mat_pending_clr (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ir = (1 << ch);
}

/**
 * \brief ��������жϱ�־
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ������жϱ�־�Ĳ���ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_cap_pending_clr (amhw_timer_t *p_hw_timer, int8_t ch)
{
    p_hw_timer->ir = (0x10 << ch);
}

/**
 * \brief ʹ�ܶ�ʱ�� (��ʼ����)
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \return ��
 */
am_static_inline 
void amhw_timer_enable (amhw_timer_t *p_hw_timer)
{
    p_hw_timer->tcr = (p_hw_timer->tcr & 0x03) | (1 << 0);
}

/**
 * \brief ���ܶ�ʱ��(ֹͣ����)
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \return ��
 */
am_static_inline 
void amhw_timer_disable (amhw_timer_t *p_hw_timer)
{
    p_hw_timer->tcr = (p_hw_timer->tcr & 0x03) & ~(1 << 0);
}

/**
 * \brief �õ���ǰ��ʱ���ļ���ֵ
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \return ��ǰ��ʱ���ļ���ֵ
 */
am_static_inline 
uint32_t amhw_timer_count_get (amhw_timer_t *p_hw_timer)
{
    return p_hw_timer->tc;
}

/**
 * \brief ���õ�ǰ��ʱ���ļ���ֵ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] value      : ���õĶ�ʱ���ļ���ֵ
 * \return ��
 */
am_static_inline 
void amhw_timer_count_set (amhw_timer_t *p_hw_timer, uint32_t value)
{
    p_hw_timer->tc = value;
}

/**
 * \brief �õ�Ԥ��Ƶ����ֵ
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \return ��ǰ��Ԥ��Ƶ������ֵ
 */
am_static_inline 
uint32_t amhw_timer_prescale_get (amhw_timer_t *p_hw_timer)
{
    return p_hw_timer->pr;
}

/**
 * \brief ����Ԥ��Ƶ����ֵ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] prescale   : Ԥ��Ƶֵ
 *
 * \return ��
 */
am_static_inline  
void amhw_timer_prescale_set (amhw_timer_t *p_hw_timer, uint32_t prescale)
{
    p_hw_timer->pr = prescale;
}

/**
 * \brief �õ�Ԥ��Ƶ�������ĵ�ǰֵ
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \return Ԥ��Ƶ�������ĵ�ǰֵ
 */
am_static_inline 
uint32_t amhw_timer_prescale_count_get (amhw_timer_t *p_hw_timer)
{
    return p_hw_timer->pc;
}

/**
 * \brief ����һ��ƥ��ͨ����ƥ��ֵ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ƥ��ͨ������Чֵ 0 ~ 3
 * \param[in] val        : ƥ��ֵ
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_mat_val_set (amhw_timer_t *p_hw_timer, uint8_t ch, uint32_t val)
{
    p_hw_timer->mr[ch] = val;
}

/**
 * \brief ��һ������ͨ����ȡ����ֵ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ����ͨ������Чֵ 0 ~ 3
 *
 * \return ָ������ͨ���Ĳ���ֵ
 */
am_static_inline  
uint32_t amhw_timer_cap_val_get (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    return p_hw_timer->cr[ch];
}

/**
 * \brief  ��λ��ʱ������ֵ��Ԥ��Ƶ������ֵΪ0
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \return ��
 */
void amhw_timer_reset (amhw_timer_t *p_hw_timer);

/**
 * \brief ʹ��ƥ���жϣ�����ʱ������ֵ��ƥ��ͨ����ֵ���ʱ��
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_mat_int_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (1 << (ch * 3));
}

/**
 * \brief ����ƥ���ж�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_mat_int_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) & (~(1 << (ch * 3)));
}

/**
 * \brief ʹ��ƥ���¼���λ��ʱ������ֵ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \return   ��
 */
am_static_inline  
void amhw_timer_mat_reset_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (1 << ((ch * 3) + 1));
}

/**
 * \brief ����ƥ���¼���λ��ʱ������ֵ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline  
void amhw_timer_mat_reset_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) & (~(1 << ((ch * 3) + 1)));
}

/**
 * \brief ʹ��ƥ���¼�ֹͣ��ʱ������
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_mat_stop_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (1 << (((ch * 3) + 2)));
}

/**
 * \brief ����ƥ���¼�ֹͣ��ʱ������
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ƥ��ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_mat_stop_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->mcr = (p_hw_timer->mcr & (0x0FFF)) | (~(1 << (((ch * 3) + 2))));
}

/**
 * \brief ʹ�������ش��������¼�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ����ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 *
 * \note ͬʱʹ�������ز�����½��ز��񽫻���˫���ؾ����������¼�
 */
am_static_inline 
void amhw_timer_cap_rising_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (1 << (ch * 3));
}

/**
 * \brief ���������ش��������¼�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ����ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_cap_rising_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) & (~(1 << (ch * 3)));
}


/**
 * \brief ʹ���½��ش��������¼�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ����ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 *
 * \note ͬʱʹ�������ز�����½��ز��񽫻���˫���ؾ����������¼�
 */
am_static_inline  
void amhw_timer_cap_falling_enable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (1 << (ch * 3 + 1));
}

/**
 * \brief �����½��ش��������¼�
 * 
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ����ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline  
void amhw_timer_cap_falling_disable (amhw_timer_t *p_hw_timer, int8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (~(1 << (ch * 3 + 1)));
}

/**
 * \brief ʹ�ܲ����ж�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ����ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline  
void amhw_timer_cap_int_enable (amhw_timer_t *p_hw_timer, int8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) | (1 << (ch * 3 + 2));
}

/**
 * \brief ���ܲ����ж�
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch         : ����ͨ������Чֵ 0 ~ 3
 *
 * \return ��
 */
am_static_inline  
void amhw_timer_cap_int_disable (amhw_timer_t *p_hw_timer, uint8_t ch)
{
    p_hw_timer->ccr = (p_hw_timer->ccr & 0x0FFF) & (~(1 << (ch * 3 + 2)));
}

/**
 * \brief Standard timer ƥ��ܽű仯״̬����
 */
typedef enum  amhw_timer_mat_pin_state {
    AMHW_TIMER_MAT_PIN_DO_NOTHING = 0, /**< \brief ƥ��ʱ�����κα仯    */
    AMHW_TIMER_MAT_PIN_CLR        = 1, /**< \brief ƥ��ʱ����͵�ƽ      */
    AMHW_TIMER_MAT_PIN_SET        = 2, /**< \brief ƥ��ʱ����ߵ�ƽ      */
    AMHW_TIMER_MAT_PIN_TOGGLE     = 3  /**< \brief ƥ��ʱ��ת�����ƽ    */
} amhw_timer_mat_pin_state_t;

/**
 * \brief ����ƥ��ͨ����Ӧ���ⲿ�ܽ�
 *
 * \param[in] p_hw_timer    : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] ch            : ƥ��ͨ������Чֵ 0 ~ 3
 * \param[in] initial_state : �ⲿ�ܽŵĳ�ʼ״̬, 1���ߵ�ƽ, 0 ���͵�ƽ
 * \param[in] match_state   : ѡ��ùܽŵ�ƥ���¼�����״̬
 *
 * \return ��
 */
void amhw_timer_mat_pin_ctrl (amhw_timer_t              *p_hw_timer,
                              uint8_t                    ch,
                              uint8_t                    initial_state,
                              amhw_timer_mat_pin_state_t match_state);

/**
 * \brief Standard timer �ļ���ʱ��Դ�ͱ���ѡ��
 */
typedef enum amhw_timer_src {
    AMHW_TIMER_SRC_RISING_PCLK  = 0, /**< \brief Ĭ�ϣ�PCLK��������     */
    AMHW_TIMER_SRC_RISING_CAP   = 1, /**< \brief ���������������       */
    AMHW_TIMER_SRC_FALLING_CAP  = 2, /**< \brief ����������½���       */
    AMHW_TIMER_SRC_BOTH_CAP     = 3  /**< \brief ���������˫����       */
} amhw_timer_src_t;

/**
 * \brief ���ö�ʱ������ʱ��Դ��ʱ�ӱ���
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] timer_src  : ��ʱ������ʱ��Դ��ʱ�ӱ���
 * \param[in] cap_num    : ���ʱ��ԴΪ�������룬������ָ������ͨ���ţ���Чֵ0~3
 *
 * \return ��
 */
am_static_inline  
void amhw_timer_src_set (amhw_timer_t     *p_hw_timer, 
                         amhw_timer_src_t  timer_src, 
                         uint8_t           cap_num)
{
    p_hw_timer->ctcr = (p_hw_timer->ctcr &  0xF0ul)  |
                       ((uint32_t)timer_src)         |
                       ((uint32_t)cap_num << 2);
}

/**
 * \brief ѡ��ʱ����Ԥ��Ƶ������������Դ
 */
typedef enum  amhw_timer_cap_clrsrc {
    AMHW_TIMER_CAP_CLRSRC_CH0_RISING  = 0, /**< \brief ����ͨ��0������   */
    AMHW_TIMER_CAP_CLRSRC_CH0_FALLING = 1, /**< \brief ����ͨ��0�½���   */
    AMHW_TIMER_CAP_CLRSRC_CH1_RISING  = 2, /**< \brief ����ͨ��1������   */
    AMHW_TIMER_CAP_CLRSRC_CH1_FALLING = 3, /**< \brief ����ͨ��1�½���   */
    AMHW_TIMER_CAP_CLRSRC_CH2_RISING  = 4, /**< \brief ����ͨ��2������   */
    AMHW_TIMER_CAP_CLRSRC_CH2_FALLING = 5, /**< \brief ����ͨ��2�½���   */ 
} amhw_timer_cap_clrsrc_t;

/**
 * \brief ʹ�����벶��ʱ��Դ���㶨ʱ����Ԥ��Ƶ������ֵ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] clr_src    : �������������Դ
 *
 * \return ��
 */
am_static_inline
void amhw_timer_cap_clr_enable (amhw_timer_t            *p_hw_timer,
                                amhw_timer_cap_clrsrc_t  clr_src)
{
    p_hw_timer->ctcr = (p_hw_timer->ctcr & 0x1F) | (clr_src << 5) | (1 <<  4);
}

/**
 * \brief �������벶��ʱ��Դ���㶨ʱ����Ԥ��Ƶ������ֵ
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \return ��
 */
am_static_inline 
void amhw_timer_cap_clr_disable (amhw_timer_t *p_hw_timer)
{
    p_hw_timer->ctcr &= ~((uint32_t)(1 << 4));
}

/**
 * \brief ʹ��ƥ��ͨ����PWMģʽ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] mat_num    : ƥ��ͨ������Чֵ��0 ~ 3
 *
 * \return ��
 * 
 * \note ��ʹ����ƥ��ͨ����PWMģʽ���򵱶�ʱ������ֵС��ƥ��Ĵ���ֵʱ�������
 *       ��ƽ��������͵�ƽ��
 */
am_static_inline 
void amhw_timer_mat_pwm_enable (amhw_timer_t *p_hw_timer, uint8_t mat_num)
{
    p_hw_timer->pwmc |=  (1 << mat_num);
}

/**
 * \brief ����ƥ��ͨ����PWMģʽ
 *
 * \param[in] p_hw_timer : ָ��Standard Timer�Ĵ������ָ��
 * \param[in] mat_num    : ƥ��ͨ������Чֵ��0 ~ 3
 *
 * \return ��
 */
am_static_inline 
void amhw_timer_mat_pwm_disable (amhw_timer_t *p_hw_timer, uint8_t mat_num)
{
    p_hw_timer->pwmc &=  ~(1 << mat_num);
}

/**
 * @} amhw_if_timer
 */

#ifdef __cplusplus
}
#endif


#endif /* __AMHW_TIMER_H */

/* end of file */

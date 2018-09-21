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
 * \brief ״̬�ɱ�̶�ʱ��(State Configurable Timer) �����ӿ�
 *
 * 1. SCT��ʱ�����ж��ֹ���, including:
 *       - ���PWM���Σ�
 *       - ���벶��
 *       - ƥ�������
 * 2. 32λ���������Թ�����2��16λ������ģʽ����һ��32λ������ģʽ��
 * 3. �������ļ���ʱ�ӿ�����ϵͳʱ�ӣ�Ҳ������ѡ����ⲿ�ܽ������źţ�
 * 4. ���������Թ��������ϼ���ģʽ��Ҳ���Թ���������-���¼���ģʽ��
 * 5. ����������Զ���Ϊһ���¼�:
 *     - ������ƥ��״̬��
 *     - ָ�������� ������������ܽŵĵ�ƽ������أ�״̬��
 *     - ������ƥ��״̬������/���״̬�Ľ�ϣ���/�򣩣�
 * 6. �¼�������״̬�仯��������жϺ�DMA����
 *     - ƥ��Ĵ���0���������Զ��߽����ƣ���Ϊ�������ļ����߽磻
 *     - ��˫��ģʽ��, �¼����Ը��ݼ������򴥷���
 *     - ƥ���¼����Ա���ֱ������һ��ָ�����¼�������
 * 7. �¼��������ƣ�limit������ֹ��halt��, ������start��, ֹͣ��stop����������
 * 8. ֧��:
 *       - 8 ·���룻
 *       - 8 ·�����
 *       - 13 ��ƥ��/����Ĵ�����
 *       - 13 ���¼���
 *       - 13 ��״̬��
 * 9.  8 ·����������Ԥ�ȶ���õĹܽŻ��źţ�
 * 10. 8 ·���
 *       - ���0 �� ���7�����������ⲿ�ܽţ�
 *       - ���7 ����������ADC�Ĵ������븴�þ���
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
 * \name SCTģ������
 * @{
 */

#define AMHW_SCT_EVENT_NUM         (13)  /**< \brief ֧�ֵ��¼�����           */
#define AMHW_SCT_MATCAP_REG_NUM    (13)  /**< \brief ƥ��/����Ĵ�������      */
#define AMHW_SCT_STATE_NUM         (13)  /**< \brief ֧�ֵ�״̬����           */
#define AMHW_SCT_OUTPUT_NUM        (8)   /**< \brief ֧�ֵ����·��           */
#define AMHW_SCT_INPUT_NUM         (8)   /**< \brief ֧�ֵ�����·��           */
#define AMHW_SCT_DMA_REQUEST_NUM   (2)   /**< \brief ֧�ֵ�DMA������          */

/** @} */

/* ʹ�������ṹ�������������Ŀ�ʼ */
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
 * \brief ״̬�ɱ�̶�ʱ���Ĵ�����ṹ��
 */
typedef struct amhw_sct {
    __IO uint32_t config;          /**< \brief ���üĴ���                     */
                                                                              
    union {                                                                   
        __IO uint32_t ctrl_u;      /**< \brief ���ƼĴ���                     */
        struct {                                                              
            __IO uint16_t ctrl_l;  /**< \brief ���ƼĴ�����16λ               */
            __IO uint16_t ctrl_h;  /**< \brief ���ƼĴ�����16λ               */
        };                                                                    
    };                                                                        
                                                                              
    __IO uint16_t limit_l;         /**< \brief ���ƼĴ�����16λ               */
    __IO uint16_t limit_h;         /**< \brief ���ƼĴ�����16λ               */
    __IO uint16_t halt_l;          /**< \brief ��ֹ�Ĵ�����16λ               */
    __IO uint16_t halt_h;          /**< \brief ��ֹ�Ĵ�����16λ               */
    __IO uint16_t stop_l;          /**< \brief ֹͣ�Ĵ�����16λ               */
    __IO uint16_t stop_h;          /**< \brief ֹͣ�Ĵ�����16λ               */
    __IO uint16_t start_l;         /**< \brief �����Ĵ�����16λ               */
    __IO uint16_t start_h;         /**< \brief �����Ĵ�����16λ               */
                                                                              
    uint32_t reserved1[10];        /**< \brief ��������Ӧʹ��                 */
                                                                              
    union {                                                                   
        __IO uint32_t count_u;     /**< \brief �������Ĵ���                   */
        struct {                                                              
            __IO uint16_t count_l; /**< \brief �������Ĵ�����16λ             */
            __IO uint16_t count_h; /**< \brief �������Ĵ�����16λ             */
        };                                                                    
    };                                                                        
                                                                              
    __IO uint16_t state_l;         /**< \brief ״̬�Ĵ�����16λ               */
    __IO uint16_t state_h;         /**< \brief ״̬�Ĵ�����16λ               */
    __I  uint32_t input;           /**< \brief ����Ĵ���,ֻ��                */
                                   
    __IO uint16_t regmode_l;       /**< \brief ƥ��/����ģʽѡ��Ĵ�����16λ  */
    __IO uint16_t regmode_h;       /**< \brief ƥ��/����ģʽѡ��Ĵ�����16λ  */
    __IO uint32_t output;          /**< \brief ����Ĵ���                     */
    __IO uint32_t outputdirctrl;   /**< \brief ���������ƼĴ���             */
                                   
    __IO uint32_t res;             /**< \brief ��ͻ����Ĵ���                 */

    union {

        __IO uint32_t dmarequest[2];   /**< \brief DMA����Ĵ�����            */
        struct {
            __IO uint32_t dma0request; /**< \brief DMA0 ����Ĵ���            */
            __IO uint32_t dma1request; /**< \brief DMA1 ����Ĵ���            */
        };
    };

         uint32_t reserved2[35];   /**< \brief ��������Ӧʹ��                 */

    __IO uint32_t even;            /**< \brief �¼�ʹ�ܼĴ���                 */
    __IO uint32_t evflag;          /**< \brief �¼���־�Ĵ���                 */
    __IO uint32_t conen;           /**< \brief "�ޱ仯��ͻ�¼�"�ж�ʹ�ܼĴ��� */
    __IO uint32_t conflag;         /**< \brief "�ޱ仯��ͻ�¼�"״̬�Ĵ���     */

    union {

        __IO union {               /**< \brief ƥ��Ĵ���                     */
            __IO uint32_t u;       /**< \brief ƥ��Ĵ�������״̬32λ         */
            struct {
                __IO uint16_t l;   /**< \brief ƥ��Ĵ�����16λ               */
                __IO uint16_t h;   /**< \brief ƥ��Ĵ�����16λ               */
            };

        } match[AMHW_SCT_MATCAP_REG_NUM];

        __I union {                /**< \brief ����Ĵ���                     */
            __IO uint32_t u;       /**< \brief ����Ĵ�������״̬32λ         */
            struct {               
                __IO uint16_t l;   /**< \brief ����Ĵ�����16λ               */
                __IO uint16_t h;   /**< \brief ����Ĵ�����16λ               */
            };
        } cap[AMHW_SCT_MATCAP_REG_NUM];
    };

    uint32_t reserved3[48 + (16 - AMHW_SCT_MATCAP_REG_NUM)]; /**< \brief ���� */

    union {

        __IO union {              /**< \brief ƥ����ת�ؼĴ���                */
            __IO uint32_t u;      /**< \brief ƥ����ת�ؼĴ�������״̬32λ    */

            struct {
                __IO uint16_t l;  /**< \brief ƥ����ת�ؼĴ�����16λ          */
                __IO uint16_t h;  /**< \brief ƥ����ת�ؼĴ�����16λ          */
            };

        } matchrel[AMHW_SCT_MATCAP_REG_NUM];

        __IO union {              /**< \brief ������ƼĴ���                  */
            __IO uint32_t u;      /**< \brief ������ƼĴ�������״̬32λ      */

            struct {
                __IO uint16_t l;  /**< \brief ������ƼĴ�����16λ            */
                __IO uint16_t h;  /**< \brief ������ƼĴ�����16λ            */
            };
        } capctrl[AMHW_SCT_MATCAP_REG_NUM];

    };

    uint32_t reserved6[48 + (16 - AMHW_SCT_MATCAP_REG_NUM)]; /**< \brief ���� */

    __IO struct {
        __IO uint32_t state;      /**< \brief �¼�״̬�Ĵ���                  */
        __IO uint32_t ctrl;       /**< \brief �¼����ƼĴ���                  */
    } event[AMHW_SCT_EVENT_NUM];  /**< \brief �¼�״̬�����ƼĴ�����          */

    uint32_t reserved9[128 - 2 * AMHW_SCT_EVENT_NUM]; /**< \brief ����        */

    __IO struct {
        __IO uint32_t set;        /**< \brief �����λ�Ĵ���                  */
        __IO uint32_t clr;        /**< \brief �������Ĵ���                  */
    } out[AMHW_SCT_OUTPUT_NUM];   /**< \brief �����λ������Ĵ�����          */

} amhw_sct_t;


/** \brief ���ڶ����¼���,n����Ч�����ǣ�0 ~ AMHW_SCT_EVENT_NUM - 1           */
#define AMHW_SCT_EVT(n)       (n)

/** \brief ���ڶ���״̬��,n����Ч�����ǣ�0 ~ AMHW_SCT_STATE_NUM - 1           */
#define AMHW_SCT_STATE(n)     (n)

/** \brief ����ʹ�õĲ���Ĵ����ţ�n����Ч�����ǣ�0 ~ AMHW_SCT_MATCAP_REG_NUM - 1 */
#define AMHW_SCT_CAP(n)       (n)

/** \brief ����ʹ�õ�ƥ��Ĵ����ţ�n����Ч�����ǣ�0 ~ AMHW_SCT_MATCAP_REG_NUM - 1 */
#define AMHW_SCT_MAT(n)       (n)

/** \brief �������ͨ����,n����Ч�����ǣ�0 ~ AMHW_SCT_OUTPUT_NUM - 1          */
#define AMHW_SCT_OUT(n)       (n)

/** \brief ��������ͨ����,n����Ч�����ǣ�0 ~ AMHW_SCT_INPUT_NUM - 1           */
#define AMHW_SCT_INPUT(n)     (n)

/**
 * \name ����SCT���õĺ�
 * @{
 */

/** \brief ��ʱ��������������2��16λ��ʱ����ģʽ�� */
#define AMHW_SCT_CONFIG_16BIT_COUNTER                   0x00000000

/** \brief ��ʱ��������������1��32λ��ʱ����ģʽ�� */
#define AMHW_SCT_CONFIG_32BIT_COUNTER                   0x00000001

/**
  * \brief ��ֹƥ��Ĵ����ĸ�16λ�͵�16λ��ָ������ת�ؼĴ�������ת��
  *        ������������������1��32λ��ʱ����ģʽ��ʹ�á�
  */
#define AMHW_SCT_CONFIG_NORELOAD_U                      (0x1 << 7)

/**
  * \brief ��ֹƥ��Ĵ����ĵ�16λ��ָ������ת�ؼĴ�������ת��
  *        ������������������2��16λ��ʱ����ģʽ��ʹ�á�
  */
#define AMHW_SCT_CONFIG_NORELOAD_L                      (0x1 << 7)

/**
  * \brief ��ֹƥ��Ĵ����ĸ�16λ��ָ������ת�ؼĴ�������ת��
  *        ������������������2��16λ��ʱ����ģʽ��ʹ�á�
  */
#define AMHW_SCT_CONFIG_NORELOAD_H                      (0x1 << 8)

/** \brief ϵͳʱ����ΪSCT����ʱ�ӣ�ʱ��ģʽ0��                               */
#define AMHW_SCT_CONFIG_CLKMODE_SYSCLK                  (0x0 << 1)

/** \brief Ԥ��Ƶ��ϵͳʱ����ΪSCT����ʱ�� ��ʱ��ģʽ1��                      */
#define AMHW_SCT_CONFIG_CLKMODE_PRESCALED_SYSCLK        (0x1 << 1)

/** \brief SCT���루��CKSELѡ������룩��ΪSCT����ʱ�ӣ�ʱ��ģʽ2��           */
#define AMHW_SCT_CONFIG_CLKMODE_SCT_INPUT               (0x2 << 1)

/** \brief Ԥ��Ƶ��SCT���루��CKSELѡ������룩��ΪSCT����ʱ�ӣ�ʱ��ģʽ3��   */
#define AMHW_SCT_CONFIG_CLKMODE_PRESCALED_SCT_INPUT     (0x3 << 1)

/**
 * @}
 */

/**
 * \name Ϊʱ��ģʽ2��ʱ��ģʽ3ѡ��ʱ������
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
 * \name ͬ�����룬�����������¼������ź�֮ǰ��������SCTʱ��ͬ��
 *
 * ��ʱ��ģʽ2��ʱ��ģʽ3�£�������δ��ʹ�á�
 * @{
 */

#define AMHW_SCT_CONFIG_INSYNC_0     (0x1 <<  9) /**< \brief ͬ������0        */
#define AMHW_SCT_CONFIG_INSYNC_1     (0x1 << 10) /**< \brief ͬ������1        */
#define AMHW_SCT_CONFIG_INSYNC_2     (0x1 << 11) /**< \brief ͬ������2        */
#define AMHW_SCT_CONFIG_INSYNC_3     (0x1 << 12) /**< \brief ͬ������3        */
#define AMHW_SCT_CONFIG_INSYNC_4     (0x1 << 12) /**< \brief ͬ������4        */
#define AMHW_SCT_CONFIG_INSYNC_5     (0x1 << 14) /**< \brief ͬ������5        */

#define AMHW_SCT_CONFIG_INSYNC_ALL   (0x3F << 9) /**< \brief ͬ����������     */

/** @} */

/**
 * \name ƥ��Ĵ���0�ϵ�ƥ��״̬��Ϊ��ʱ�����������Զ�����״̬
 * @{
 */
#define AMHW_SCT_CONFIG_AUTOLIMIT_U  (0x1UL << 17)
#define AMHW_SCT_CONFIG_AUTOLIMIT_L  (0x1UL << 17)
#define AMHW_SCT_CONFIG_AUTOLIMIT_H  (0x1UL << 18)

/** @} */

/**
 * \name ����SCT���Ƶĺ궨��
 * @{
 */

#define AMHW_SCT_CTRL_STOP_L    (1 << 1) /**< \brief ֹͣ��16λ��ʱ��������״̬32λ��ʱ�� */
#define AMHW_SCT_CTRL_HALT_L    (1 << 2) /**< \brief ��ֹ��16λ��ʱ��������״̬32λ��ʱ�� */
#define AMHW_SCT_CTRL_CLRCTR_L  (1 << 3) /**< \brief �����16λ������������״̬32λ������ */

/**
 * \brief ��16λ��ʱ��������״̬32λ��ʱ�����ϼ�����������״̬��Ȼ������
 */
#define AMHW_SCT_CTRL_BIDIR_L_COUNT_UP       (0 << 4)

/**
 * \brief ��16λ��ʱ��������״̬32λ��ʱ�����ϼ�����������״̬��Ȼ�����¼�����0
 */
#define AMHW_SCT_CTRL_BIDIR_L_COUNT_UP_DOWN  (1 << 4)

/** \brief ��16λ��ʱ��������״̬32λ��ʱ����ʱ��Ԥ��Ƶֵ */
#define AMHW_SCT_CTRL_PRE_L(x)               (((x) & 0xFF) << 5)

#define AMHW_SCT_CTRL_STOP_H     (1 << 17)    /**< \brief ֹͣ��16λ��ʱ��    */
#define AMHW_SCT_CTRL_HALT_H     (1 << 18)    /**< \brief ��ֹ��16λ��ʱ��    */
#define AMHW_SCT_CTRL_CLRCTR_H   (1 << 19)    /**< \brief �����16λ������    */

/**
 * \brief ��16λ��ʱ�����ϼ�����������״̬��Ȼ������
 */
#define AMHW_SCT_CTRL_BIDIR_H_COUNT_UP       (0 << 20)

/**
 * \brief ��16λ��ʱ�����ϼ�����������״̬�����¼�����0
 */
#define AMHW_SCT_CTRL_BIDIR_H_COUNT_UP_DOWN  (1 << 20)

/** \brief ��16λ��ʱ����ʱ��Ԥ��Ƶֵ  */
#define AMHW_SCT_CTRL_PRE_H(x)               (((x) & 0xFF) << 21)

/**
 * @}
 */

/**
 * \name �����¼����ƼĴ����ĺ궨��
 * @{
 */

/** \brief ѡ�����ӵ����¼���ƥ��Ĵ��� */
#define AMHW_SCT_EV_CTRL_MATCHSEL(reg)   (reg << 0)

/** \brief ָ�����¼�����L�飬ʹ��״̬�Ĵ����ĵ�16λ��ƥ��Ĵ�����16λ */
#define AMHW_SCT_EV_CTRL_HEVENT_L        (0UL << 4)

/** \brief ָ�����¼�����H�飬ʹ��״̬�Ĵ����ĸ�16λ��ƥ��Ĵ�����16λ */
#define AMHW_SCT_EV_CTRL_HEVENT_H        (1UL << 4)

/** \brief IO�¼�ΪIOSELѡ��������ź�     */
#define AMHW_SCT_EV_CTRL_OUTSEL_INPUT    (0UL << 5)

/** \brief IO�¼�ΪIOSELѡ�������ź�     */
#define AMHW_SCT_EV_CTRL_OUTSEL_OUTPUT   (1UL << 5)

/** \brief ѡ������¼��������IO�ź�      */
#define AMHW_SCT_EV_CTRL_IOSEL(signal)   (signal << 6)

/** \brief ���¼�ͨ�������㣨����STATEVֵ���ı�״ֵ̬  */
#define AMHW_SCT_EV_CTRL_STATELD_ADD      (0x0UL << 14)

/** \brief ���¼�ͨ��ֱ��ת��STATEVֵ�ı�״ֵ̬        */
#define AMHW_SCT_EV_CTRL_STATELD_LOAD     (0x1UL << 14)

/**
 * \brief ���� STATEV ֵ
 *
 *  �������¼��ǵ�ǰ״̬�����������¼����¼������ʱ���ſ���ͨ����ֵ�ı�״ֵ̬
 *  ��� STATELD �� STATEV ֵ��Ϊ0, ��״̬���ᷢ���ı�
 */
#define AMHW_SCT_EV_CTRL_STATEV(x)        (((x) &(0x1F)) << 15)

/**
 * \name �����¼��ļ���״̬
 * @{
 */

/**
 * \brief ���ʹ���˸ñ�־�������¼�����Դ�а�����ƥ���¼��������򵱼���������ʱ��
 *        ֻҪ����ֵ���ڻ������Ӧƥ��Ĵ���ֵ����ƥ���¼�����Ϊ��Ч̬���򵱼�����
 *        ���¼���ʱ������ֵС�ڻ������Ӧƥ��Ĵ���ֵ��ƥ���¼�����Ϊ��Ч̬��
 */
#define AMHW_SCT_EV_CTRL_MATCHMEM_1                (0x1UL << 20)

/**
 * \brief ���ʹ���˸ñ�־�������¼�����Դ�а�����ƥ���¼�����. ���ҽ�������ֵ
 *        ������Ӧƥ��Ĵ���ֵʱ��ƥ���¼��ű���Ϊ����Ч̬��
 */
#define AMHW_SCT_EV_CTRL_MATCHMEM_0                (0x0UL << 20)

/** @} */

/** \brief �¼����������Զ�ʱ���ļ������� */
#define AMHW_SCT_EV_CTRL_DIRECTION_INDEPENDENT     (0x0UL << 21)

/** \brief ��˫�����ģʽ�У��������ϼ���ʱ�����¼��Żᱻ����  */
#define AMHW_SCT_EV_CTRL_DIRECTION_UP              (0x1UL << 21)

/** \brief ��˫�����ģʽ�У��������¼���ʱ�����¼��Żᱻ����  */
#define AMHW_SCT_EV_CTRL_DIRECTION_DOWN            (0x2UL << 21)

/**
 * @}
 */

/**
 * \name Ϊ�¼�ѡ��IO����״̬
 * @{
 */

#define AMHW_SCT_EV_CTRL_IOCOND_LOW    (0x0UL << 10)  /**< \brief �͵�ƽ����  */
#define AMHW_SCT_EV_CTRL_IOCOND_RISE   (0x1UL << 10)  /**< \brief �����ش���  */
#define AMHW_SCT_EV_CTRL_IOCOND_FALL   (0x2UL << 10)  /**< \brief �½��ش���  */
#define AMHW_SCT_EV_CTRL_IOCOND_HIGH   (0x3UL << 10)  /**< \brief �ߵ�ƽ����  */

/** @} */

/**
 * \name ָ��ƥ��״̬��IO״̬�����¼�����Ϸ�ʽ
 * @{
 */
 
/** brief ��ʽ������һ��״̬�����������¼� */
#define AMHW_SCT_EV_CTRL_COMBMODE_OR      (0x0UL << 12)

/** brief ��ƥ��״̬�����Ŵ����¼�           */
#define AMHW_SCT_EV_CTRL_COMBMODE_MATCH   (0x1UL << 12)

/** brief ��IO״̬�����Ŵ����¼�             */
#define AMHW_SCT_EV_CTRL_COMBMODE_IO      (0x2UL << 12)

/** brief ƥ��״̬��IO״̬�������Ŵ����¼�   */
#define AMHW_SCT_EV_CTRL_COMBMODE_AND     (0x3UL << 12)

/** @} */

/**
 * \name SCT��ͻ����궨��
 * @{
 */
#define AMHW_SCT_RES_NOCHANGE                (0) /**< \brief ��ͻʱ�ޱ仯     */
#define AMHW_SCT_RES_SET_OUTPUT              (1) /**< \brief ��ͻʱ��λ���   */
#define AMHW_SCT_RES_CLEAR_OUTPUT            (2) /**< \brief ��ͻʱ�������   */
#define AMHW_SCT_RES_TOGGLE_OUTPUT           (3) /**< \brief ��ͻʱ��ת���   */

/**
 * @}
 */

/**
 * \name SCT˫�����ʱ���������
 * @{
 */

/** \brief ��λ��������Զ�ʱ���ļ�������                                     */
#define AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT   (0)

/** \brief ��λ�������ǵߵ��ģ�����16λ��ʱ��������״̬32λ��ʱ�����¼���ʱ   */
#define AMHW_SCT_OUTPUTDIRCTRL_L_REVERSED    (1)

/** \brief ��λ�������ǵߵ��ģ�����16λ��ʱ�����¼���ʱ                       */
#define AMHW_SCT_OUTPUTDIRCTRL_H_REVERSED    (2)

/** @} */

/**
 * \brief SCT ģʽ��־
 *
 * �ñ�־��������ĳЩ�Ĵ���ʱ��ָ����ǰ���õ�SCT����ģʽ����SCT������1��32λ��ʱ
 * ��ģʽ��ʱ��ģʽ��־��Ϊ:AMHW_SCT_MODE_UNIFY����SCT������2��16λ��ʱ��ģʽ��
 * ʱ�������üĴ���ʱ����Ҫָ���������ǵ�16λ(AMHW_SCT_MODE_SEPARATE_L)���Ǹ�
 * 16λ(AMHW_SCT_MODE_SEPARATE_H)
 */
typedef enum amhw_sct_mode {
    AMHW_SCT_MODE_UNIFY      = 0,    /**< \brief ����ģʽ                     */
    AMHW_SCT_MODE_SEPARATE_L,        /**< \brief 2��16λ��ʱ��ģʽʱ����16λ  */
    AMHW_SCT_MODE_SEPARATE_H         /**< \brief 2��16λ��ʱ��ģʽʱ����16λ  */
} amhw_sct_mode_t;

/**
 * \brief ƥ��/���� ģʽ
 *
 *  ��������ĳЩ�Ĵ�����ģʽ��ָ���乤����ƥ��״̬���ǲ���״̬
 */
typedef enum amhw_sct_matcap_mode {
    AMHW_SCT_MATCAP_MATCH  = 0,     /**< \brief �Ĵ���������ƥ��״̬ */
    AMHW_SCT_MATCAP_CAPTURE,        /**< \brief �Ĵ��������ڲ���״̬ */
} amhw_sct_matcap_mode_t;


/**
 * \brief ����SCT
 *
 * \param[in] p_hw_sct  : ָ��SCT�Ĵ������ָ��
 * \param[in] cfg_flags : AMHW_SCT_CONFIG_* ��ֵ���� AMHW_SCT_CONFIG_*��Ļ�
 *                        (OR)ֵ(#AMHW_SCT_CONFIG_32BIT_COUNTER)
 * \return ��
 */
am_static_inline
void amhw_sct_config (amhw_sct_t *p_hw_sct, uint32_t cfg_flags)
{
    p_hw_sct->config = cfg_flags;
}

/**
 * \brief ����SCT
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] ctrl_flags :AMHW_SCT_CTRL_* ��ֵ���� AMHW_SCT_CTRL_*��Ļ�
 *                        (OR)ֵ(#AMHW_SCT_CTRL_HALT_L)
 * \return ��
 *
 * \note ��SCTֹͣ����ֹʱ������λ�����Խ���д����������SCT����ʱ��ֻ��STOP��HALTλ
 *       ���Բ����������������λ����Ҫ�Ƚ�HALTλ��1.
 */
am_static_inline
void amhw_sct_ctrl (amhw_sct_t *p_hw_sct, uint32_t ctrl_flags)
{
    p_hw_sct->ctrl_u = ctrl_flags;
}

/**
 * \brief ���SCT�Ƿ�����ֹ(HALT)״̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 *
 * \retval  TRUE  : ������ֹ(HALT)״̬
 * \retval  FALSE : û�д�����ֹ(HALT)״̬
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
 * \brief ���SCT�Ƿ���ֹͣ(STOP)״̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 *
 * \retval  TRUE  : ����ֹͣ(STOP)״̬
 * \retval  FALSE : û�д���ֹͣ(STOP)״̬
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
 * \brief ���ÿ��ƼĴ�������ӦλΪ1
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] value    : �����ֵ��λnΪ1����Ὣ���ƼĴ�������Ӧλ��1��0��Ӱ��
 *
 * \return ��
 */
am_static_inline
void amhw_sct_ctrl_set (amhw_sct_t *p_hw_sct, uint32_t value)
{
    p_hw_sct->ctrl_u |= value;
}

/**
 * \brief ������ƼĴ�������Ӧλ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] value    : �����ֵ��λnΪ1����Ὣ���ƼĴ�������Ӧλ���㡣0��Ӱ��
 *
 * \return ��
 */
am_static_inline
void amhw_sct_ctrl_clr (amhw_sct_t *p_hw_sct, uint32_t value)
{
    p_hw_sct->ctrl_u &= (~value);
}

/**
 * \brief ��SCT����ֹ(HALT)̬�л���ֹͣ(STOP)̬(�����ᴦ������̬)
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 *
 * \return ��
 */
void amhw_sct_ctrl_halt_to_stop(amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode);

/**
 * \brief ����SCT��Ԥ��Ƶֵ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] prescale : ��������ʱ��Ƶ����SCTʱ��Ƶ�ʳ���(prescale + 1)
 *
 * \return ��
 */
void amhw_sct_prescale_set(amhw_sct_t     *p_hw_sct,
                           amhw_sct_mode_t mode,
                           uint8_t         prescale);

/**
 * \brief ��ȡSCT��Ԥ��Ƶֵ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 *
 * \return SCT��Ԥ��Ƶֵ
 */
uint8_t amhw_sct_prescale_get(amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode);

/**
 * \brief ����SCT��һ���¼�
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] flags    : AMHW_SCT_EV_CTRL_*��ֵ����AMHW_SCT_EV_CTRL_*��Ļ�(OR)
 *                       ֵ��(#AMHW_SCT_EV_CTRL_COMBMODE_MATCH)
 *                       
 * \return ��
 */
am_static_inline
void amhw_sct_event_ctrl (amhw_sct_t *p_hw_sct, uint32_t evt_num, uint32_t flags)
{
    p_hw_sct->event[evt_num].ctrl = flags;
}

/**
 * \brief ʹ��һ���¼���ָ��״̬�з���
 *
 * \param[in] p_hw_sct  : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num   : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] state_num : ״̬�ţ�0 ~ AMHW_SCT_STATE_NUM - 1
 *
 * \return ��
 */
am_static_inline
void amhw_sct_event_state_enable (amhw_sct_t *p_hw_sct,
                                  uint32_t    evt_num,
                                  uint32_t    state_num)
{
    p_hw_sct->event[evt_num].state |= (1 << state_num);
}

/**
 * \brief ����һ���¼���ָ��״̬�з���
 *
 * \param[in] p_hw_sct  : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num   : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] state_num : ״̬�ţ�0 ~ AMHW_SCT_STATE_NUM - 1
 *
 * \return ��
 */
am_static_inline
void amhw_sct_event_state_disable (amhw_sct_t *p_hw_sct,
                                   uint32_t    evt_num,
                                   uint32_t    state_num)
{
    p_hw_sct->event[evt_num].state &= ~(1 << state_num);
}

/**
 * \brief ʹ��һ���¼���Ϊ������������״̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ����һ���¼���Ϊ������������״̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ʹ��һ���¼�����ʱ��ֹ��ʱ��
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ����һ���¼�����ʱ��ֹ��ʱ��
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ʹ��һ���¼�����ʱֹͣ��ʱ��
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ����һ���¼�����ʱֹͣ��ʱ��
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ʹ��һ���¼�����ʱ������ʱ��
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ����һ���¼�����ʱ������ʱ��
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return ��
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
 * \brief ����SCT�ļ���(count)ֵ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ.
 * \param[in] value    : ����(count)ֵ
 *
 * \note ���ü���ֵʱ������ȷ����Ӧ�ļ���������HALT״̬�����SCTģʽ��
 *       #AMHW_SCT_MODE_SEPARATE_L ���� #AMHW_SCT_MODE_SEPARATE_H 
 *       ����(count)ֵ������16λ��Ч
 */
void amhw_sct_count_set(amhw_sct_t     *p_hw_sct,
                        amhw_sct_mode_t mode,
                        uint32_t        value);

/**
 * \brief ��ȡ��ʱ���ĵ�ǰ����ֵ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 *
 * \return ��ʱ���ĵ�ǰ����ֵ�����SCTģʽ��#AMHW_SCT_MODE_SEPARATE_L 
 *         ���� #AMHW_SCT_MODE_SEPARATE_H�� ����(count)ֵ������16λ��Ч     
 */
uint32_t amhw_sct_count_get(amhw_sct_t *p_hw_sct, amhw_sct_mode_t mode);

/**
 * \brief ��ȡ��ǰ��״ֵ̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 *
 * \return ��ǰ��״ֵ̬
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
 * \brief ����״ֵ̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] value    : ״ֵ̬
 *
 * \note ����״ֵ̬�ǣ�����ȷ����Ӧ�ļ�����������ֹ(HALT)״̬
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
 * \brief ��ȡSCT������״̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 *
 * \return ����״̬�� λ0  ~ λ7 : AIN0 ~ AIN7(ֱ�Ӷ�ȡ������״̬)
 *                    λ16 ~ λ23: SIN0 ~ SIN7(����״̬)
 *
 * \note SIN0 ~ SIN7:
 *        - ������üĴ����У�INSYNC λΪ1������Ӧ������״̬SIN��ͬ���������״̬��
 *          ����3��SCTʱ��ͬ������˻�õ�һ����ԭ�ź��ӳ�3��SCTʱ�ӵ��ȶ��źš�
 *        - ������üĴ����У�INSYNC λΪ0������Ӧ������״̬SIN��ֱ�Ӷ�ȡ������
 *          ״̬AIN��ͬ��
 */
am_static_inline
uint32_t amhw_sct_input_state_get (amhw_sct_t *p_hw_sct)
{
     return p_hw_sct->input;
}

/**
 * \brief ��ȡSCT�����״̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 *
 * \return ���״̬. λ0 ~ λ7: ���0 ~ ���7
 *           - ������״̬Ϊ�ߵ�ƽ������ӦλΪ1
 *           - ������״̬Ϊ�͵�ƽ������ӦλΪ0
 */
am_static_inline
uint32_t amhw_sct_output_state_get (amhw_sct_t *p_hw_sct)
{
     return p_hw_sct->output;
}

/**
 * \brief ����SCT�����״̬
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] state    : λ n Ϊ1�������ͨ��n����ߵ�ƽ
 *                       λ n Ϊ0�������ͨ��n����͵�ƽ
 *
 * \return ��
 *
 * \note дSCT����Ĵ�������ȷ�����еļ�����������ֹ(HALT)״̬
 */
am_static_inline
void amhw_sct_output_state_config (amhw_sct_t *p_hw_sct, uint8_t state)
{
     p_hw_sct->output = state;
}

/**
 * \brief ����ָ�������ͨ������ߵ�ƽ
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  ��
 *
 * \note дSCT����Ĵ�������ȷ�����еļ�����������ֹ(HALT)״̬
 */
am_static_inline
void amhw_sct_output_state_set (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
     p_hw_sct->output |= (1 << output_num);
}

/**
 * \brief ����ָ�������ͨ������͵�ƽ
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  ��
 *
 * \note дSCT����Ĵ�������ȷ�����еļ�����������ֹ(HALT)״̬
 */
am_static_inline
void amhw_sct_output_state_clr (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
     p_hw_sct->output &= ~(1 << output_num);
}

/**
 * \brief SCT˫�����ʱ���������
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 * \param[in] value      : ����ֵ��
 *                         - #AMHW_SCT_OUTPUTDIRCTRL_INDEPENDENT
 *                         - #AMHW_SCT_OUTPUTDIRCTRL_L_REVERSED
 *                         - #AMHW_SCT_OUTPUTDIRCTRL_R_REVERSED
 *
 * \return  ��
 */
void amhw_sct_output_dir_ctrl(amhw_sct_t *p_hw_sct,
                              uint8_t     output_num,
                              uint8_t     value);

/**
 * \brief ���������ͻ���
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 * \param[in] value      : ��ͻ�����ʽ��
 *                          - #AMHW_SCT_RES_NOCHANGE       : ����ޱ仯
 *                          - #AMHW_SCT_RES_SET_OUTPUT     : ����ߵ�ƽ
 *                          - #AMHW_SCT_RES_CLEAR_OUTPUT   : ����͵�ƽ
 *                          - #AMHW_SCT_RES_TOGGLE_OUTPUT  : ��ת�����ƽ
 * \return ��
 */
void amhw_sct_conflict_res_config(amhw_sct_t *p_hw_sct,
                                  uint8_t     output_num,
                                  uint8_t     value);


/**
 * \brief ʹ���¼���DMA����
 *
 * \param[in] p_hw_sct    : ָ��SCT�Ĵ������ָ��
 * \param[in] request_num : DMA�����,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 * \param[in] evt_num     : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_dma_request_event_enable (amhw_sct_t *p_hw_sct,
                                        uint8_t     request_num,
                                        uint32_t     evt_num)
{
    p_hw_sct->dmarequest[request_num] |= (1 << evt_num);
}

/**
 * \brief �����¼���DMA����
 *
 * \param[in] p_hw_sct    : ָ��SCT�Ĵ������ָ��
 * \param[in] request_num : DMA�����,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 * \param[in] evt_num     : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_dma_request_event_disable (amhw_sct_t *p_hw_sct,
                                         uint8_t     request_num,
                                         uint32_t    evt_num)
{
    p_hw_sct->dmarequest[request_num] &= ~(1 << evt_num);
}

/**
 * \brief ��ƥ��Ĵ���ֵ����Ӧ����װ�ؼĴ�������ת��ʱ������DMA����
 *
 * \param[in] p_hw_sct    : ָ��SCT�Ĵ������ָ��
 * \param[in] request_num : DMA�����,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_dma_request_reload_enable (amhw_sct_t *p_hw_sct,
                                         uint8_t     request_num)
{
    p_hw_sct->dmarequest[request_num] |= (1 << 30);
}

/**
 * \brief ��ƥ��Ĵ���ֵ����Ӧ����װ�ؼĴ�������ת��ʱ��������DMA����
 *
 * \param[in] p_hw_sct    : ָ��SCT�Ĵ������ָ��
 * \param[in] request_num : DMA�����,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_dma_request_reload_disable (amhw_sct_t *p_hw_sct,
                                          uint8_t     request_num)
{
    p_hw_sct->dmarequest[request_num] &= ~(1 << 30);
}

/**
 * \brief ���DMA�����־�Ƿ���λ
 *
 * \param[in] p_hw_sct    : ָ��SCT�Ĵ������ָ��
 * \param[in] request_num : DMA�����,0 ~ AMHW_SCT_DMA_REQUEST_NUM - 1
 *
 * \retval  TRUE  : DMA�����־��λ
 * \retval  FALSE : DMA�����־δ��λ
 */
am_static_inline
bool_t amhw_sct_dma_request_check (amhw_sct_t *p_hw_sct, uint8_t request_num)
{
    return (bool_t)((p_hw_sct->dmarequest[request_num] & (1ul << 31)) != 0);
}

/**
 * \brief ʹ��ָ���¼����ж�����
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_event_int_enable (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    p_hw_sct->even |= (1 << evt_num);
}

/**
 * \brief ����ָ���¼����ж�����
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_event_int_disable (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    p_hw_sct->even &= ~(1 << evt_num);
}

/**
 * \brief ��ȡ�¼���־�Ĵ���ֵ
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \return �¼���־�Ĵ���ֵ����ӦλΪ1��������Ӧ�¼�����
 */
am_static_inline
uint32_t amhw_sct_event_flag_get (amhw_sct_t *p_hw_sct)
{
    return p_hw_sct->evflag;
}

/**
 * \brief ���ָ���¼��Ƿ���
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \retval  TRUE  : �¼�����
 * \retval  FALSE : �¼�δ����
 */
am_static_inline
bool_t amhw_sct_event_flag_chk (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    return (bool_t)((p_hw_sct->evflag & (1 << evt_num)) != 0);
}

/**
 * \brief ���ָ���¼��ķ�����־
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num  : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_event_flag_clr (amhw_sct_t *p_hw_sct, uint32_t evt_num)
{
    p_hw_sct->evflag = (1 << evt_num);
}

/**
 * \brief ʹ�������ͻʱ�����ж�
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_conflict_int_enable (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
    p_hw_sct->conen |= (1 << output_num);
}

/**
 * \brief ���������ͻʱ�����ж�
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return  ��
 */
am_static_inline
void amhw_sct_conflict_int_disable (amhw_sct_t *p_hw_sct, uint8_t output_num)
{
    p_hw_sct->conen &= ~(1 << output_num);
}

/**
 * \brief ��ȡ��ͻ��־
 * \param[in] p_hw_sct  : ָ��SCT�Ĵ������ָ��
 * \return ��ͻ��־. ��������n�����ޱ仯��ͻ�¼�����(��������ĳ�ͻ�������Ϊ
           �ޱ仯)��λ n (0 ~ 7) Ϊ1
 *
 * \note  λ30Ϊ����λ����������ߴ��󣨵���16λ������������״̬�µ�32λ������δ
 *        ����HALT״̬ʱ,�Բ�Ӧ��д������ļĴ�������STATE,MATCH��������д���������
 *        ���λΪ1��
 *        λ31Ϊ����λ����������ߴ��󣨵���16λ������δ����HALT״̬ʱ,�Բ�Ӧ��
 *        д������ļĴ�������STATE,MATCH��������д������������λΪ1��
 */
am_static_inline
uint32_t amhw_sct_conflict_flag_get (amhw_sct_t *p_hw_sct)
{
    return p_hw_sct->conflag;
}

/**
 * \brief �����ͻ��־
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] flags    : λnΪ1���������λ�ϵ���Ӧ��־
 *
 * \return ��
 */
am_static_inline
void amhw_sct_conflict_flag_clr (amhw_sct_t  *p_hw_sct, uint32_t flags)
{
    p_hw_sct->conflag = (1 << flags);
}

/**
 * \brief SCTƥ��/����Ĵ���ģʽ����
 *
 * \param[in] p_hw_sct    : ָ��SCT�Ĵ������ָ��
 * \param[in] sct_mode    : SCTģʽ
 * \param[in] matcap_num  : ƥ��/����Ĵ����ţ�0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] matcap_mode : ���õ�ģʽ��
 *                           - AMHW_SCT_MATCAP_MATCH, ����Ϊƥ��ģʽ
 *                           - AMHW_SCT_MATCAP_CAPTURE, ����Ϊ����ģʽ
 * \return  ��
 */
void amhw_sct_regmode_config(amhw_sct_t            *p_hw_sct,
                             amhw_sct_mode_t        sct_mode,
                             uint32_t               matcap_num,
                             amhw_sct_matcap_mode_t matcap_mode);


/**
 * \brief ����ƥ��Ĵ���ֵ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] mat_num  : ƥ��Ĵ����ţ� 0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] value    : ���õ�ֵ
 *
 * \return  ��
 *
 * \note ����ֵ֮ǰ������ȷ����ģʽ����Ӧ����������HALT״̬�����SCTģʽΪ
 *       AMHW_SCT_MODE_SEPARATE_L ����AMHW_SCT_MODE_SEPARATE_H
 *       valueֵ����16Ϊ��Ч
 */
void amhw_sct_mat_val_set(amhw_sct_t     *p_hw_sct,
                          amhw_sct_mode_t mode,
                          uint32_t        mat_num,
                          uint32_t        value);

/**
 * \brief ����ƥ����ת�ؼĴ�����ֵ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] mode     : SCTģʽ
 * \param[in] num      : ƥ����ת�ؼĴ����ţ� 0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] value    : ���õ�ֵ
 *
 * \return ��
 *
 * \note ����ֵ֮ǰ������ȷ����ģʽ����Ӧ����������HALT״̬�����SCTģʽΪ
 *       AMHW_SCT_MODE_SEPARATE_L ����AMHW_SCT_MODE_SEPARATE_H
 *       valueֵ����16Ϊ��Ч
 */
void amhw_sct_mat_reload_val_set(amhw_sct_t     *p_hw_sct,
                                 amhw_sct_mode_t mode,
                                 uint32_t        num,
                                 uint32_t        value);
/**
 * \brief ���ò���ʹ�ܻ�����¼���������Ĵ���ֵ������ֵװ��
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] sct_mode : SCTģʽ
 * \param[in] cap_num  : ����Ĵ����ţ�0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 * \param[in] evt_num  : ����������¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 *
 * \param[in] active   : TRUE: ʹ���¼���������
 *                       FALSE: �����¼���������
 * \return  ��
 */
void amhw_sct_cap_ctrl(amhw_sct_t      *p_hw_sct,
                       amhw_sct_mode_t  sct_mode,
                       uint32_t         cap_num,
                       uint32_t         evt_num,
                       bool_t           active);

/**
 * \brief ��ȡ����ֵ
 *
 * \param[in] p_hw_sct : ָ��SCT�Ĵ������ָ��
 * \param[in] sct_mode : SCTģʽ
 * \param[in] cap_num  : ����Ĵ����ţ�0 ~ AMHW_SCT_MATCAP_REG_NUM - 1
 *
 * \return ����ֵ
 *         ���SCTģʽ�� AMHW_SCT_MODE_SEPARATE_L ���� AMHW_SCT_MODE_SEPARATE_H
 *         �򷵻�ֵ������16λ��Ч
 */
uint32_t amhw_sct_cap_val_get(amhw_sct_t      *p_hw_sct,
                              amhw_sct_mode_t  sct_mode,
                              uint32_t         cap_num);

/**
 * \brief ʹ��ָ���¼���ָ�����ͨ����Ϊ�ߵ�ƽ
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num    : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return ��
 */
am_static_inline
void amhw_sct_out_set_enable (amhw_sct_t  *p_hw_sct,
                              uint8_t      output_num,
                              uint32_t     evt_num)
{
    p_hw_sct->out[output_num].set |= (1 << evt_num);
}

/**
 * \brief ����ָ���¼���ָ�����ͨ����Ϊ�ߵ�ƽ
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num    : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return ��
 */
am_static_inline
void amhw_sct_out_set_disable (amhw_sct_t *p_hw_sct,
                               uint8_t     output_num,
                               uint32_t    evt_num)
{
    p_hw_sct->out[output_num].set &= ~(1 << evt_num);
}

/**
 * \brief ʹ��ָ���¼���ָ�����ͨ����Ϊ�͵�ƽ
 *
 * \param[in] p_hw_sct   : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num    : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return ��
 */
am_static_inline
void amhw_sct_out_clr_enable (amhw_sct_t  *p_hw_sct,
                              uint8_t      output_num,
                              uint32_t     evt_num)
{
    p_hw_sct->out[output_num].clr |= (1 << evt_num);
}

/**
 * \brief ����ָ���¼���ָ�����ͨ����Ϊ�͵�ƽ
 *
 * \param[in] p_hw_sct    : ָ��SCT�Ĵ������ָ��
 * \param[in] evt_num     : �¼��ţ�0 ~ AMHW_SCT_EVENT_NUM - 1
 * \param[in] output_num  : ���ͨ���ţ�0 ~ AMHW_SCT_OUTPUT_NUM - 1
 *
 * \return ��
 */
am_static_inline
void amhw_sct_out_clr_disable (amhw_sct_t *p_hw_sct,
                               uint8_t     output_num,
                               uint32_t    evt_num)
{
    p_hw_sct->out[output_num].clr &= ~(1 << evt_num);
}

/* ʹ�������ṹ�������������Ľ��� */
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



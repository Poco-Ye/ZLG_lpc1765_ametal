/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief ���������ļ�������ϵͳ���弶��Ӳ������
 * \sa am_prj_config.h
 * \internal
 * \par Modification history
 * - 1.00 14-12-23  tee, first implementation.
 * \endinternal
 */
 
#ifndef __AM_PRJ_CONFIG_H
#define __AM_PRJ_CONFIG_H

#include "ametal.h"

/**
 * \addtogroup am_if_prj_config
 * \copydoc am_prj_config.h
 * @{
 */

/**
 * \name ϵͳ����
 * @{
 */

/** \brief ������ʱ��Դ */
#define AM_CFG_MAIN_CLK_SRC          AMHW_CLOCK_MAIN_SRC_PLLOUT

/** \brief �����첽ʱ��Դ */
#define AM_CFG_ASYNC_CLK_SRC         AMHW_CLOCK_ASYNC_SRC_IRC

/** \brief ����ϵͳʱ�ӷ�Ƶ��ϵͳʱ�� = ��ʱ��/ϵͳʱ�ӷ�Ƶ�� */
#define AM_CFG_SYSTEM_CLK_DIV        1

/** \brief �����첽ʱ�ӷ�Ƶ  */
#define AM_CFG_ASYNC_CLK_DIV         1

/** \brief ����PLLʱ��Դ */
#define AM_CFG_PLL_CLK_SRC           AMHW_PLL_CLKSRC_IRC

/** \brief ����PLLʱ�������ʱ��Ƶ�� */
#define AM_CFG_PLLOUT_FREQ           100000000

/** \brief �Ƿ�ʹ��PLL�߾��������0-��ʹ�ã�1-ʹ�� */
#define AM_CFG_PLL_USEPRECISE        0

/** @} */

/**
 * \name �弶��ʼ������
 * �����ʹ���κεİ�����Դ�����Խ����к궨���ֵ����Ϊ0
 * @{
 */

/** \brief ���Ϊ1�����ʼ����ʱ��������ʼ�������ʹ��am_mdelay() �� am_udelay()��ʱ���� */
#define AM_CFG_DELAY_ENABLE          1

/** \brief ���Ϊ1������ʼ���ж�ϵͳ����ʼ�������ʹ��am_int_connect()���жϱ�׼�ӿں��� */
#define AM_CFG_INT_ENABLE            1

/** \brief ���Ϊ1�����ʼ�����ڵ���                */
#define AM_CFG_DEBUG_ENABLE          1

/** \brief ���Դ���ѡ��0 - USART0, 1 - USART1...  */
#define AM_CFG_DEBUG_USART           0

/** \brief ���Դ��ڲ���������                */
#define AM_CFG_DEBUG_BAUDRATE       (115200)     

/** \brief ���Ϊ1�����ʼ��led����ع���    */
#define AM_CFG_LED_ENABLE            1

/** \brief ���Ϊ1�����ʼ������������ع��� */
#define AM_CFG_BUZZER_ENABLE         1

/** \brief ��������PWMƵ��              */
#define AM_CFG_BUZZER_PWM_FREQ       2500
    
/** \brief PWM��ռ�ձȣ�50����50%       */
#define AM_CFG_BUZZER_PWM_DUTY       50

/** @} */

#include "amdr_hwconfig_adc.h"
#include "amdr_hwconfig_crc.h"
#include "amdr_hwconfig_dma.h"
#include "amdr_hwconfig_fifo.h"
#include "amdr_hwconfig_gpio.h"
#include "amdr_hwconfig_i2c.h"   
#include "amdr_hwconfig_int.h"
#include "amdr_hwconfig_mrt.h"
#include "amdr_hwconfig_rit.h"
#include "amdr_hwconfig_rtc.h"
#include "amdr_hwconfig_sct_cap.h"
#include "amdr_hwconfig_sct_pwm.h"
#include "amdr_hwconfig_sct_timing.h"
#include "amdr_hwconfig_spi.h"
#include "amdr_hwconfig_timer_cap.h"
#include "amdr_hwconfig_timer_pwm.h"
#include "amdr_hwconfig_timer_timing.h"
#include "amdr_hwconfig_usart.h"
#include "amdr_hwconfig_wwdt.h"
#include "amdr_hwconfig_utick.h"

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  /* __AM_PRJ_CONFIG_H */

/* end of file */

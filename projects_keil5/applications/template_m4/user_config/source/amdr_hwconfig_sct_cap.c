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
 * \brief LPC5410X SCT0 ���ڲ����ܵ��û������ļ�
 * \sa amdr_hwconfig_sct_cap.c
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-04  tee, first implementation.
 * \endinternal
 */

#include "amdr_hwconfig_sct_cap.h"

/**
 * \addtogroup amdr_if_hwconfig_src_sct_cap
 * \copydoc amdr_hwconfig_sct_cap.c
 * @{
 */
 
/** \brief SCT0���ڲ����ܵ�����������Ϣ�б� */
amdr_sct_cap_ioinfo_t __g_sct0_cap_ioinfo_list[] = {
    {PIO0_23, PIO0_23_GPIO | PIO0_23_INPUT , PIO0_23_GPIO | PIO0_23_INPUT}, /**< \brief ͨ�� 0 */
    {PIO0_24, PIO0_24_GPIO | PIO0_24_INPUT , PIO0_24_GPIO | PIO0_24_INPUT}, /**< \brief ͨ�� 1 */
    {PIO0_25, PIO0_25_GPIO | PIO0_25_INPUT | PIO0_25_DRIVEDISABLE | 
              PIO0_25_FILTERENABLE, PIO0_25_GPIO | PIO0_25_INPUT},          /**< \brief ͨ�� 2 */
    {PIO0_26, PIO0_26_GPIO | PIO0_26_INPUT , PIO0_26_GPIO | PIO0_26_INPUT}, /**< \brief ͨ�� 3 */
    {PIO0_27, PIO0_27_GPIO | PIO0_27_INPUT , PIO0_27_GPIO | PIO0_27_INPUT}, /**< \brief ͨ�� 4 */
    {PIO0_28, PIO0_28_GPIO | PIO0_28_INPUT , PIO0_28_GPIO | PIO0_28_INPUT}, /**< \brief ͨ�� 5 */
    {0,0,0},/**< \brief ͨ��6��ADC0��ֵ�жϣ�������ΪSCT�Ĳ���ͨ��6���źţ�����IO���� */
    {0,0,0},/**< \brief ͨ��7�ǵ���ֹͣ�źţ�������ΪSCT�Ĳ���ͨ��7���źţ�����IO���� */
};

/** \brief SCT0���ڲ����ܵ��豸��Ϣ */
const amdr_sct_cap_devinfo_t  g_sct0_cap_devinfo = {
    AMHW_SCT0,                 /**< \brief ָ��SCT0�Ĵ������ָ�� */
    INUM_SCT0,                 /**< \brief SCT0�жϱ��           */
    8,                         /**< \brief 8������ͨ��            */
    &__g_sct0_cap_ioinfo_list[0],
};

/** \brief SCT0���ڲ����ܵ��豸���� */
amdr_sct_cap_dev_t  g_sct0_cap_dev;

/** \brief SCT0���ڲ����ܵ�ƽ̨��ʼ�� */
void amhw_plfm_sct0_cap_init (void)
{
    amhw_clock_periph_enable(AMHW_CLOCK_SCT0);
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
}

/** \brief  ���SCT0ƽ̨��ʼ�� */
void amhw_plfm_sct0_cap_deinit (void)
{
    amhw_syscon_periph_reset(AMHW_RESET_SCT0);
    amhw_clock_periph_disable(AMHW_CLOCK_SCT0);
}

/**
 * @}
 */

/* end of file */

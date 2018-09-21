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
 * \brief �����ж�Ӳ���ӿ�ʵ�֡�
 * 
 * \internal
 * \par Modification History
 * - 1.10 15-01-01  hbt, modified.
 * - 1.00 14-12-06  asd, first implementation.
 * \endinternal
 */

#include "amhw_pint.h"

/******************************************************************************
* ��������
*******************************************************************************/

/**
 * \brief ������ʽѡ��
 */
void amhw_pint_trigger_select (amhw_pint_t              *p_hw_pint, 
                               uint8_t                   chan,
                               amhw_pint_trigger_mode_t  trigger_type)
{
    switch (trigger_type) {
    case 0:                                      /* �ߵ�ƽ���� */
        amhw_pint_level_set(p_hw_pint, chan);
        amhw_pint_high_enable(p_hw_pint, chan);
        amhw_pint_low_disable(p_hw_pint, chan);
        break;
    
    case 1:                                      /* �͵�ƽ���� */
        amhw_pint_level_set(p_hw_pint, chan);
        amhw_pint_high_disable(p_hw_pint, chan);
        amhw_pint_low_enable(p_hw_pint, chan);
        break;
    
    case 2:                                      /* �����ش��� */
        amhw_pint_edge_set(p_hw_pint, chan);
        amhw_pint_high_enable(p_hw_pint, chan);
        amhw_pint_low_disable(p_hw_pint, chan);
        break;
    
    case 3:                                      /* �½��ش��� */
        amhw_pint_edge_set(p_hw_pint, chan);
        amhw_pint_high_disable(p_hw_pint, chan);
        amhw_pint_low_enable(p_hw_pint, chan);
        break;
    
    case 4:                                      /* ˫���ش��� */
        amhw_pint_edge_set(p_hw_pint, chan);
        amhw_pint_high_enable(p_hw_pint, chan);
        amhw_pint_low_enable(p_hw_pint, chan);
        break;
    
    default:
        break;
    }
}

/**
 * \brief ѡ��ģʽƥ����������Դ��
 */
void amhw_pint_match_src_set (amhw_pint_t         *p_hw_pint, 
                              amhw_pint_select_t   chan, 
                              amhw_pint_bitslice_t slicenum)
{
    uint32_t pmsrc_reg;

    /* ģʽƥ��Դ */
    pmsrc_reg = p_hw_pint->pmsrc & ~(AMHW_PINT_SRC_BITSOURCE_MASK 
                                 << (AMHW_PINT_SRC_BITSOURCE_START 
                                  + (slicenum * 3)));
    p_hw_pint->pmsrc = pmsrc_reg | (chan << (AMHW_PINT_SRC_BITSOURCE_START
                                          + (slicenum * 3)));
}

/**
 * \brief ����ģʽƥ�����档
 */
void amhw_pint_match_config (amhw_pint_t             *p_hw_pint, 
                             amhw_pint_bitslice_t     slicenum, 
                             amhw_pint_bitslice_cfg_t slice_cfg, 
                             bool_t                   end_point)
{
    uint32_t pmcfg_reg;

    /* ����λƬ */
    pmcfg_reg = p_hw_pint->pmcfg & ~(AMHW_PINT_SRC_BITCFG_MASK 
                                 << (AMHW_PINT_SRC_BITCFG_START 
                                  + (slicenum * 3)));
    p_hw_pint->pmcfg = pmcfg_reg | (slice_cfg << (AMHW_PINT_SRC_BITCFG_START 
                                               + (slicenum * 3)));

    /* ��ĩ��Ϊ�棬ʹ�ܸ�λƬ */
    if (end_point == TRUE) {
        
        /* Ĭ��λƬ7Ϊ������� */
        if (slicenum != AMHW_PINT_BITSLICE7) {
            p_hw_pint->pmcfg |= (0x1 << slicenum);
        }
    }
}

/* end of file */

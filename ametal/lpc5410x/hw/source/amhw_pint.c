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
 * \brief 引脚中断硬件接口实现。
 * 
 * \internal
 * \par Modification History
 * - 1.10 15-01-01  hbt, modified.
 * - 1.00 14-12-06  asd, first implementation.
 * \endinternal
 */

#include "amhw_pint.h"

/******************************************************************************
* 公共函数
*******************************************************************************/

/**
 * \brief 触发形式选择
 */
void amhw_pint_trigger_select (amhw_pint_t              *p_hw_pint, 
                               uint8_t                   chan,
                               amhw_pint_trigger_mode_t  trigger_type)
{
    switch (trigger_type) {
    case 0:                                      /* 高电平触发 */
        amhw_pint_level_set(p_hw_pint, chan);
        amhw_pint_high_enable(p_hw_pint, chan);
        amhw_pint_low_disable(p_hw_pint, chan);
        break;
    
    case 1:                                      /* 低电平触发 */
        amhw_pint_level_set(p_hw_pint, chan);
        amhw_pint_high_disable(p_hw_pint, chan);
        amhw_pint_low_enable(p_hw_pint, chan);
        break;
    
    case 2:                                      /* 上升沿触发 */
        amhw_pint_edge_set(p_hw_pint, chan);
        amhw_pint_high_enable(p_hw_pint, chan);
        amhw_pint_low_disable(p_hw_pint, chan);
        break;
    
    case 3:                                      /* 下降沿触发 */
        amhw_pint_edge_set(p_hw_pint, chan);
        amhw_pint_high_disable(p_hw_pint, chan);
        amhw_pint_low_enable(p_hw_pint, chan);
        break;
    
    case 4:                                      /* 双边沿触发 */
        amhw_pint_edge_set(p_hw_pint, chan);
        amhw_pint_high_enable(p_hw_pint, chan);
        amhw_pint_low_enable(p_hw_pint, chan);
        break;
    
    default:
        break;
    }
}

/**
 * \brief 选择模式匹配引擎输入源。
 */
void amhw_pint_match_src_set (amhw_pint_t         *p_hw_pint, 
                              amhw_pint_select_t   chan, 
                              amhw_pint_bitslice_t slicenum)
{
    uint32_t pmsrc_reg;

    /* 模式匹配源 */
    pmsrc_reg = p_hw_pint->pmsrc & ~(AMHW_PINT_SRC_BITSOURCE_MASK 
                                 << (AMHW_PINT_SRC_BITSOURCE_START 
                                  + (slicenum * 3)));
    p_hw_pint->pmsrc = pmsrc_reg | (chan << (AMHW_PINT_SRC_BITSOURCE_START
                                          + (slicenum * 3)));
}

/**
 * \brief 配置模式匹配引擎。
 */
void amhw_pint_match_config (amhw_pint_t             *p_hw_pint, 
                             amhw_pint_bitslice_t     slicenum, 
                             amhw_pint_bitslice_cfg_t slice_cfg, 
                             bool_t                   end_point)
{
    uint32_t pmcfg_reg;

    /* 配置位片 */
    pmcfg_reg = p_hw_pint->pmcfg & ~(AMHW_PINT_SRC_BITCFG_MASK 
                                 << (AMHW_PINT_SRC_BITCFG_START 
                                  + (slicenum * 3)));
    p_hw_pint->pmcfg = pmcfg_reg | (slice_cfg << (AMHW_PINT_SRC_BITCFG_START 
                                               + (slicenum * 3)));

    /* 如末端为真，使能该位片 */
    if (end_point == TRUE) {
        
        /* 默认位片7为最终组成 */
        if (slicenum != AMHW_PINT_BITSLICE7) {
            p_hw_pint->pmcfg |= (0x1 << slicenum);
        }
    }
}

/* end of file */

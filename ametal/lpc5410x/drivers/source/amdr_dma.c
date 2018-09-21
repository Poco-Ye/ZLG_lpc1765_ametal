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
 * \brief DMA 驱动实现
 *
 * \internal
 * \par Modification history
 * - 1.10 15-01-09  hbt, modified.
 * - 1.00 14-12-02  zen, first implementation.
 * \endinternal
 */

#include "amdr_dma.h"
#include "am_int.h"
#include "amhw_clock.h"
#include "lpc5410x_inum.h"   


/*******************************************************************************
  私有定义
*******************************************************************************/

/** \brief 中断未连接标识 */
#define __INT_NOT_CONNECTED      0xFF

/** \brief 定义指向DMA设备信息的指针 */
#define __DMA_DEVINFO_DECL(p_dma_devinfo, p_dev)  \
        const amdr_dma_devinfo_t *p_dma_devinfo = p_dev->p_devinfo


/*******************************************************************************
  全局变量
*******************************************************************************/

/** \brief 指向DMA设备的指针 */
amdr_dma_dev_t *__gp_dma_dev;

/** \brief DMA中断回调函数信息数组 */
static struct amdr_dma_int_info __dma_int_info[AMHW_DMA_CHAN_CNT];

/** \brief DMA中断回调函数信息映射 */
static uint8_t __dma_int_map[AMHW_DMA_CHAN_CNT];

/*******************************************************************************
  公共函数
*******************************************************************************/

/* 启动通道传输 */ 
int amdr_dma_chan_setup (int chan, uint32_t flags)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    
    amhw_dma_chan_cfg_set(p_dma_devinfo->p_hw_dma, chan, flags);
    
    return AM_OK;
}

/* 开始通道传输 */ 
int amdr_dma_chan_start (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    
    amhw_dma_chan_int_enable(p_dma_devinfo->p_hw_dma, chan);
    amhw_dma_chan_enable(p_dma_devinfo->p_hw_dma, chan);
    
    return AM_OK;
}

/* 停止通道传输 */
int amdr_dma_chan_stop (int chan)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    
    amhw_dma_t *p_hw_dma = p_dma_devinfo->p_hw_dma;
    
    amhw_dma_chan_int_disable(p_hw_dma, chan);
    amhw_dma_chan_disable(p_hw_dma, chan);

    /* 等待通道传输unbusy */
    while (amhw_dma_chan_busy(p_hw_dma, chan));

    /* 冻结通道传输 */
    amhw_dma_chan_abort(p_hw_dma, chan);
    
    /* 清中断标志 */
    amhw_dma_chan_inta_clear(p_hw_dma, chan);
    amhw_dma_chan_intb_clear(p_hw_dma, chan);
    amhw_dma_chan_errint_clear(p_hw_dma, chan); 
    
    return AM_OK;
}

/* 开始DMA传输 */ 
int amdr_dma_chan_xfer_startup (int chan, amhw_dma_xfer_desc_t *p_desc)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_dma_xfer_desc_t *p_desc_tmp = NULL;
    
    p_desc_tmp = (amhw_dma_xfer_desc_t *)amhw_dma_chan_desc_addr_get(p_dma_devinfo->p_hw_dma, chan);
    
    p_desc_tmp->xfercfg      = p_desc->xfercfg;
    p_desc_tmp->src_end_addr = p_desc->src_end_addr;
    p_desc_tmp->dst_end_addr = p_desc->dst_end_addr;
    p_desc_tmp->link         = p_desc->link;
    
    amhw_dma_chan_xfercfg_set(p_dma_devinfo->p_hw_dma, chan, p_desc_tmp->xfercfg);

    return AM_OK;
}

/* 建立传输描述符 */
int amdr_dma_xfer_desc_build (amhw_dma_xfer_desc_t *p_desc,
                              uint32_t              src_addr,
                              uint32_t              dst_addr,
                              uint32_t              nbytes,
                              uint32_t              flags)
{
    uint32_t xfer_cnt;
    uint32_t width_byte = (1 << AM_BITS_GET(flags, 8, 2));
    uint32_t src_inc    = AM_BITS_GET(flags, 12, 2);
    uint32_t dst_inc    = AM_BITS_GET(flags, 14, 2);
    
    if (!AM_ALIGNED(src_addr, width_byte) ||
        !AM_ALIGNED(dst_addr, width_byte) ||
        !AM_ALIGNED(nbytes,   width_byte)) {
        return AM_ERROR;
    }

    xfer_cnt = nbytes / width_byte - 1;
    AM_BITS_SET(flags, 16, 10, xfer_cnt);

    p_desc->xfercfg = flags;
    
    if (src_inc != 0) {
        p_desc->src_end_addr = src_addr + nbytes - width_byte;
    } else {
        p_desc->src_end_addr = src_addr;
    }
    
    if (dst_inc != 0) {
        p_desc->dst_end_addr = dst_addr + nbytes - width_byte;
    } else {
        p_desc->dst_end_addr = dst_addr;
    }
    
    p_desc->link = 0;

    return AM_OK;
}

/* 连接两个传输描述符 */
int amdr_dma_xfer_desc_link (amhw_dma_xfer_desc_t *p_desc, 
                             amhw_dma_xfer_desc_t *p_next)
{
    p_desc->link = (uint32_t)p_next;
    return AM_OK;
}

/* DMA中断处理函数 */
static void __dma_int_handler (void *p_arg)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, __gp_dma_dev);
    amhw_dma_t *p_hw_dma = p_dma_devinfo->p_hw_dma;
    
    int      i;
    int      chan = 0xFF;
    int      flag = 0xFF;
    uint32_t inta, intb, errint;
    
    amdr_pfn_dma_isr_t  pfn_isr;
    void               *p_isr_arg;
    
    inta   = amhw_dma_inta_status(p_hw_dma);
    intb   = amhw_dma_intb_status(p_hw_dma); 
    errint = amhw_dma_errint_status(p_hw_dma);
    
    if ((inta & 0x3FFFFF) != 0) {
        for (i = 0; i < 22; i++) {
            if (inta & (1UL << i)) {
                chan = i;
                flag = AMDR_DMA_INTA;
                break;
            }
        }
        amhw_dma_inta_clear(p_hw_dma, inta);
        
    } else if ((intb & 0x3FFFFF) != 0) {
        for (i = 0; i < 22; i++) {
            if (intb & (1UL << i)) {
                chan = i;
                flag = AMDR_DMA_INTB;
                break;
            }
        }
        amhw_dma_intb_clear(p_hw_dma, intb);
        
    } else if ((errint & 0x3FFFFF) != 0) {
        for (i = 0; i < 22; i++) {
            if (intb & (1UL << i)) {
                chan = i;
                flag = AMDR_DMA_INTERR;
                break;
            }
        }
        amhw_dma_errint_clear(p_hw_dma, errint);
    }
    
    pfn_isr   = __dma_int_info[chan].pfn_isr;
    p_isr_arg = __dma_int_info[chan].p_arg;
    
    if (pfn_isr) {
        pfn_isr(p_isr_arg, (void *)flag);
    }
}

/* 连接DMA中断服务函数 */
int amdr_dma_isr_connect (int                 chan, 
                          amdr_pfn_dma_isr_t  pfn_isr,
                          void               *p_arg)
{
    int key; 
    
    /* 关CPU中断 */
    key = am_int_cpu_lock();
    
    if (__dma_int_map[chan] == __INT_NOT_CONNECTED) {
        __dma_int_info[chan].pfn_isr = pfn_isr;
        __dma_int_info[chan].p_arg   = p_arg;
        __dma_int_map[chan]          = chan;
    } else {
        
        /* 开CPU中断 */ 
        am_int_cpu_unlock(key);
        
        return -AM_EPERM;
    }
    
    /* 开CPU中断 */ 
    am_int_cpu_unlock(key);
    
     return AM_OK;
}

/* 删除DMA中断服务函数连接 */
int amdr_dma_isr_disconnect (int                 chan, 
                             amdr_pfn_dma_isr_t  pfn_isr, 
                             void               *p_arg)
{
    if (__dma_int_map[chan] == chan) {
        __dma_int_info[chan].pfn_isr = NULL;
        __dma_int_map[chan]          = __INT_NOT_CONNECTED;
    } else {
        return -AM_EINVAL;
    }
    
    return AM_OK;
}

/* DMA初始化 */
int amdr_dma_init (amdr_dma_dev_t *p_dev, const amdr_dma_devinfo_t *p_devinfo)
{
    int i;

    p_dev->p_devinfo = p_devinfo;
    __gp_dma_dev     = p_dev;
    
    amhw_dma_enable(p_devinfo->p_hw_dma);
    amhw_dma_sram_addr_set(p_devinfo->p_hw_dma, (uint32_t)p_devinfo->p_sram_base);
    
    for (i = 0; i < AMHW_DMA_CHAN_CNT; i++) {
        __dma_int_info[i].pfn_isr = NULL;
        __dma_int_map[i]          = __INT_NOT_CONNECTED;
    }
    
    am_int_connect(p_devinfo->inum, __dma_int_handler, (void *)0);
    am_int_enable(p_devinfo->inum);
    
    return AM_OK;
}

/* DMA去初始化 */
void amdr_dma_deinit (amdr_dma_dev_t *p_dev)
{
    __DMA_DEVINFO_DECL(p_dma_devinfo, p_dev);
    int i;
    
    for (i = 0; i < AMHW_DMA_CHAN_CNT; i++) {
        __dma_int_info[i].pfn_isr = NULL;
        __dma_int_map[i]          = 0;
    }
    
    am_int_disable(p_dma_devinfo->inum);
    amhw_dma_disable(p_dma_devinfo->p_hw_dma);
}

/* end of file */

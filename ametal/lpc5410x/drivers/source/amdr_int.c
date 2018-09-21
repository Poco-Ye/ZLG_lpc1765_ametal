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
 * \brief NVIC实现
 *
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  hbt, first implementation.
 * \endinternal
 */

#include "amdr_int.h"
#include "lpc5410x_inum.h"


/*******************************************************************************
* 私有定义
*******************************************************************************/

/** \brief 中断未连接标识 */
#define __INT_NOT_CONNECTED      0xFF

/** \brief 定义指向中断信息的指针 */
#define __INT_DEVINFO_DECL(p_int_devinfo, p_dev)  \
        const amdr_int_devinfo_t *p_int_devinfo = p_dev->p_devinfo
        
/*******************************************************************************
  全局变量
*******************************************************************************/

/** \brief 指向中断设备的指针 */
amdr_int_dev_t *__gp_int_dev;

/******************************************************************************
  公共函数
*******************************************************************************/

/* 中断初始化 */
int amdr_int_init (amdr_int_dev_t *p_dev, const amdr_int_devinfo_t *p_devinfo)
{
    int i;

    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }
    
    p_dev->p_devinfo = p_devinfo;
    __gp_int_dev     = p_dev;
    p_dev->valid_flg = TRUE;

    if ((p_devinfo->p_isrmap == NULL) || (p_devinfo->p_isrinfo == NULL)) {
        p_dev->valid_flg = FALSE;
    }
    
    if (p_dev->valid_flg) {
        for (i = 0; i < p_devinfo->input_cnt; i++) {
            p_devinfo->p_isrmap[i] = __INT_NOT_CONNECTED;
        }
        
        for (i = 0; i < p_devinfo->isrinfo_cnt; i++) {
            p_devinfo->p_isrinfo[i].pfn_isr = NULL;
        }
    }
    
    return AM_OK;
}

/* 中断去初始化 */
void amdr_int_deinit (amdr_int_dev_t *p_dev)
{
    __INT_DEVINFO_DECL(p_int_devinfo, p_dev);
    int i;
    
    if (p_dev->valid_flg) {
        for (i = 0; i < p_int_devinfo->input_cnt; i++) {
            p_int_devinfo->p_isrmap[i] = __INT_NOT_CONNECTED;
        }
        
        for (i = 0; i < p_int_devinfo->isrinfo_cnt; i++) {
            p_int_devinfo->p_isrinfo[i].pfn_isr = NULL;
        }
    }
    
    for (i = 0; i < p_int_devinfo->input_cnt; i++) {
        amhw_int_disable(p_int_devinfo->p_hw_int, 
                         p_int_devinfo->int_servinfo.inum_start + i);
    }
}

/* 中断处理函数 */
void am_exc_eint_handler (void)
{ 
    __INT_DEVINFO_DECL(p_int_devinfo, __gp_int_dev);
    int           inum = 0;
    int           slot;
    am_pfnvoid_t  pfn_isr;
    void         *p_arg;
    
    inum = amhw_inum_get(p_int_devinfo->p_hw_int);
    
    if (!((inum >= p_int_devinfo->int_servinfo.inum_start) && 
          (inum <= p_int_devinfo->int_servinfo.inum_end))) {
        return;
    }
    
    slot = p_int_devinfo->p_isrmap[inum];
    if (slot == __INT_NOT_CONNECTED) {
        return;
    }
    
    pfn_isr = p_int_devinfo->p_isrinfo[slot].pfn_isr;
    p_arg   = p_int_devinfo->p_isrinfo[slot].p_arg;
    
    if (pfn_isr != NULL) {
        pfn_isr(p_arg);
    }
}

/* 连接中断回调函数 */
int am_int_connect (int inum, am_pfnvoid_t pfn_isr, void *p_arg)
{
    __INT_DEVINFO_DECL(p_int_devinfo, __gp_int_dev);
    int slot = 0;
    int i;
    
    if (!((inum >= p_int_devinfo->int_servinfo.inum_start) && 
          (inum <= p_int_devinfo->int_servinfo.inum_end))) {
        return -AM_EINVAL;
    }
    
    if (pfn_isr == NULL) {
        return -AM_EINVAL;
    }
    
    slot =  p_int_devinfo->p_isrmap[inum];
    if (slot == __INT_NOT_CONNECTED) {
        for (i = 0; i < p_int_devinfo->input_cnt; i++) {
            if (p_int_devinfo->p_isrinfo[i].pfn_isr == NULL) {
                slot = i;
                break;
            }
        }
    } else {
        slot = __INT_NOT_CONNECTED;
    }
    
    if (slot != __INT_NOT_CONNECTED) {
        p_int_devinfo->p_isrmap[inum]          = slot;
        p_int_devinfo->p_isrinfo[slot].pfn_isr = pfn_isr;
        p_int_devinfo->p_isrinfo[slot].p_arg   = p_arg;
    }

    if (slot == __INT_NOT_CONNECTED) {
        return -AM_EPERM;                           /* 没有空的内存映射 */
    }
    
    return AM_OK;
}

/* 删除中断回调函数连接 */
int am_int_disconnect (int inum, am_pfnvoid_t pfn_isr, void *p_arg)
{
    __INT_DEVINFO_DECL(p_int_devinfo, __gp_int_dev);
    int slot = 0;
    
    if (!((inum >= p_int_devinfo->int_servinfo.inum_start) && 
          (inum <= p_int_devinfo->int_servinfo.inum_end))) {
        return -AM_EINVAL;
    }
    
    if (pfn_isr == NULL) {
        return -AM_EINVAL;
    }
    
    slot =  p_int_devinfo->p_isrmap[inum];
    if (slot == __INT_NOT_CONNECTED) {
        return -AM_EPERM;
    }
    
    p_int_devinfo->p_isrmap[inum]          = __INT_NOT_CONNECTED;
    p_int_devinfo->p_isrinfo[slot].pfn_isr = NULL;
    
    return AM_OK;
}

/* 使能中断 */
int am_int_enable (int inum)
{
    __INT_DEVINFO_DECL(p_int_devinfo, __gp_int_dev);
    
    amhw_int_enable(p_int_devinfo->p_hw_int, inum);
    
    return AM_OK;
}

/* 禁能中断 */
int am_int_disable (int inum)
{
    __INT_DEVINFO_DECL(p_int_devinfo, __gp_int_dev);
    
    amhw_int_disable(p_int_devinfo->p_hw_int, inum);
    
    return AM_OK;
}

__asm uint32_t am_int_cpu_lock (void)
{
    MRS     r0, PRIMASK
    CPSID   I
    BX      LR
}

__asm void am_int_cpu_unlock (uint32_t key)
{
    MSR     PRIMASK, r0
    BX      LR
}

/* end of file */

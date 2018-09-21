/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/   http://www.zlgmcu.com/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief  NVIC驱动，服务中断标准接口
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-29  hbt, first implementation.
 * \endinternal
 */

#ifndef __AMDR_INT_H
#define __AMDR_INT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_int.h"

/**
 * \addtogroup amdr_if_int
 * \copydoc amdr_int.h
 * @{
 */
    

/**
 * \brief 中断服务信息
 */
struct awdr_int_servinfo {

    /** \brief 起始中断号 */
    int inum_start;

    /** \brief 末尾中断号 */
    int inum_end;
};

/** \brief 中断服务例行信息 */
struct amdr_int_isr_info {

    /** \brief 触发回调函数 */
    am_pfnvoid_t  pfn_isr;

    /** \brief 回调函数的参数 */
    void         *p_arg;
};


/** \brief 中断设备信息 */
typedef struct amdr_int_devinfo {
    
    /** \brief 中断服务信息实例 */
    const struct awdr_int_servinfo int_servinfo;
    
    /** \brief 指向中断控制器寄存器块的指针 */
    amhw_int_t *p_hw_int;
    
    /** \brief 总中断数量 */
    int input_cnt;

    /** \brief ISR 信息映射(大小与 input_cnt 一致) */
    uint8_t *p_isrmap;

    /** \brief ISR 信息数量 */
    int isrinfo_cnt;

    /** \brief ISR 信息映射内存(大小与 isrinfo_cnt 一致) */
    struct amdr_int_isr_info *p_isrinfo;
    
} amdr_int_devinfo_t;

/**
 * \brief 中断设备实例 
 */
typedef struct amdr_int_dev {
    
    /** \brief 指向中断设备信息的指针 */
    const amdr_int_devinfo_t *p_devinfo;
    
    /** \brief 参数有效标志 */
    bool_t                     valid_flg;
    
} amdr_int_dev_t;



/**
 * \brief 中断初始化 
 *
 * \param[in] p_dev     : 指向中断设备的指针 
 * \param[in] p_devinfo : 指向中断设备信息的指针 
 *
 * \retval  AM_OK       : 操作成功 
 * \retval -AM_EINVAL   : 无效参数 
 */
int amdr_int_init(amdr_int_dev_t *p_dev, const amdr_int_devinfo_t *p_devinfo);

/**
 * \brief 中断去初始化 
 *
 * \param[in] p_dev : 指向中断设备的指针 
 *
 * \return  无 
 */
void amdr_int_deinit(amdr_int_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AMDR_INT_H */

/* end of file */

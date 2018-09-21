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
 * \brief DMA驱动，服务DMA接口
 *
 * \internal
 * \par Modification History
 * - 1.10 14-12-11  hbt, add device and device information.
 * - 1.00 14-12-01  zen, first implementation.
 * \endinternal
 */

#ifndef __AMDR_DMA_H
#define __AMDR_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "am_types.h"
#include "amhw_dma.h"

/**
 * \addtogroup amdr_if_dma
 * \copydoc amdr_dma.h
 * @{
 */


/**
 * \name 通道传输中断标志 
 * \anchor amdr_dma_chan_cfg_flags
 * @{
 */

#define AMDR_DMA_INTA         0     /**< \brief 中断A标志     */
#define AMDR_DMA_INTB         1     /**< \brief 中断B标志     */
#define AMDR_DMA_INTERR       2     /**< \brief 错误中断标志  */

/** @} */


/** \brief DMA中断回调函数类型 */
typedef void (*amdr_pfn_dma_isr_t)(void *p_arg, void *p_flg);

/** \brief DMA中断回调函数信息 */
struct amdr_dma_int_info {
    
    /** \brief DMA触发回调函数 */
    amdr_pfn_dma_isr_t  pfn_isr;

    /** \brief 回调函数的第一个入口参数 */
    void               *p_arg;
};

/** \brief DMA设备信息 */
typedef struct amdr_dma_devinfo {
    
    /** \brief 指向DMA寄存器块的指针 */
    amhw_dma_t *p_hw_dma;
    
    /** \brief SRAM 基地址，必须是512字节对齐 */
    void       *p_sram_base;
    
    /** \brief DMA中断号 */
    uint8_t     inum;
    
} amdr_dma_devinfo_t;

/**
 * \brief DMA设备实例
 */
typedef struct amdr_dma_dev {
    
    /** \brief 指向DMA设备信息的指针 */
    const amdr_dma_devinfo_t *p_devinfo;
    
} amdr_dma_dev_t;


/**
 * \brief 启动通道传输 
 *
 * \param[in] chan  : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                   (#DMA_CHAN_USART0_RX_REQ)
 * \param[in] flags : 配置参数，参见
 *                    \ref grp_amhw_dma_chan_cfg_flags "Channel Configuration Flags".
 * 
 * \retval AM_OK    : 启动成功 
 */
int amdr_dma_chan_setup(int chan, uint32_t flags);

/**
 * \brief 开始通道传输 
 * \param[in] chan : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                  (#DMA_CHAN_USART0_RX_REQ).
 * \retval AM_OK   : 操作成功 
 */
int amdr_dma_chan_start(int chan);

/**
 * \brief 停止通道传输 
 * \param[in] chan : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                  (#DMA_CHAN_USART0_RX_REQ).
 * \retval AM_OK   : 操作成功 
 */
int amdr_dma_chan_stop(int chan);

/**
 * \brief 建立传输描述符 
 *
 * \attention 如使用乒乓传输，重载描述符的地址必须是16字节对齐  
 * 
 * \param[in] p_desc   : 指向DMA传输描述符的指针 
 * \param[in] src_addr : 源端首地址 
 * \param[in] dst_addr : 目标端首地址 
 * \param[in] nbytes   : 传输字节数，注意要与“flags”的宽度对应 
 * \param[in] flags    : 配置参数，参见
 *                       \ref grp_amhw_dma_chan_xfercfg_flags "Transfer Configuration Flags"
 *
 * \retval  AM_OK      : 建立成功 
 * \retval -AM_EINVAL  : 无效参数 
 */
int amdr_dma_xfer_desc_build(amhw_dma_xfer_desc_t *p_desc,
                             uint32_t              src_addr,
                             uint32_t              dst_addr,
                             uint32_t              nbytes,
                             uint32_t              flags);

/**
 * \brief 启动传输 
 *
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                     (#DMA_CHAN_USART0_RX_REQ) 
 * \param[in] p_desc  : 指向DMA传输描述符的指针 
 *
 * \retval  AM_OK     : 操作成功 
 * \retval -AM_EINVAL : 参数无效 
 */
int amdr_dma_chan_xfer_startup(int chan, amhw_dma_xfer_desc_t *p_desc);

/**
 * \brief 连接DMA回调函数 
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTA)，(#AMDR_DMA_INTB) 或 (#AMDR_DMA_INTERR) 
 *
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                     (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] pfn_isr : 回调函数指针 
 * \param[in] p_arg   : 回调函数的第一个入口参数 
 *
 * \retval  AM_OK     : 连接成功 
 * \retval -AM_EPERM  : 参数错误 
 */
int amdr_dma_isr_connect(int                 chan,
                         amdr_pfn_dma_isr_t  pfn_isr, 
                         void               *p_arg);

/**
 * \brief 删除DMA回调函数的连接 
 *
 * \attention 该回调函数的第二个参数可从驱动获得，该参数的取值范围是 AMDR_DMA_INT* 
 *            (#AMDR_DMA_INTA)，(#AMDR_DMA_INTB) 或 (#AMDR_DMA_INTERR) 
 *
 * \param[in] chan    : DMA 通道号，值为：DMA_CHAN_* (#DMA_CHAN_0) 或 
 *                     (#DMA_CHAN_USART0_RX_REQ).
 * \param[in] pfn_isr : 回调函数指针 
 * \param[in] p_arg   : 回调函数的第一个入口参数 
 *
 * \retval  AM_OK     : 删除成功 
 * \retval -AM_EPERM  : 参数错误 
 */
int amdr_dma_isr_disconnect(int                 chan,
                            amdr_pfn_dma_isr_t  pfn_isr, 
                            void               *p_arg);

/**
 * \brief 连接两个传输描述符 
 *
 * \attention 传输描述符的地址必须都是16字节对齐 
 *
 * \param[in] p_desc : 指向当前传输描述符的指针，必须16字节对齐 
 * \param[in] p_next : 指向下一个传输描述符的指针，必须16字节对齐 
 *
 * \retval  AM_OK    : 连接成功 
 */
int amdr_dma_xfer_desc_link(amhw_dma_xfer_desc_t *p_desc, 
                            amhw_dma_xfer_desc_t *p_next);

/**
 * \brief DMA初始化
 *
 * \param[in] p_dev     : 指向DMA设备的指针 
 * \param[in] p_devinfo : 指向DMA设备信息的指针 
 *
 * \retval  AM_OK       : 初始化成功 
 */
int amdr_dma_init(amdr_dma_dev_t *p_dev, const amdr_dma_devinfo_t *p_devinfo);


/**
 * \brief DMA去初始化 
 *
 * \param[in] p_dev : 指向DMA设备的指针 
 *
 * \return  无
 */
void amdr_dma_deinit (amdr_dma_dev_t *p_dev);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif


#endif /* __AMDR_DMA_H */

/* end of file */

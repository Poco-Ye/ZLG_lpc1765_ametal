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
 * \brief 环形缓存区标准接口
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-03  jon, first implementation.
 * \endinternal
 */
#ifndef __AM_RINGBUF_H
#define __AM_RINGBUF_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
    
/**
 * \addtogroup am_if_ringbuf
 * \copydoc am_ringbuf.h
 * @{
 */
 
/**
 * \brief 环形缓存区信息结构体
 */
typedef struct am_ringbuf {
    void    *p_data_buf;          /**< \brief 指向数据缓存的指针 */
    uint32_t count;               /**< \brief 环形缓存区的大小     */
    uint32_t item_sz;             /**< \brief 数据类型的长度 */
    uint32_t head;                /**< \brief 环形缓存区的头 */
    uint32_t tail;                /**< \brief 环形缓存区的尾 */
} am_ringbuf_t;

/** \brief 获取环形缓存区的头 */
#define AM_RB_VHEAD(rb)    (*(volatile uint32_t *) &(rb)->head) 

/** \brief 获取环形缓存区的头 */
#define AM_RB_VTAIL(rb)    (*(volatile uint32_t *) &(rb)->tail) 

#ifndef AM_MIN

/** \brief 获取两数的最小值 */
#define AM_MIN(a, b)       (((a) < (b)) ? (a) : (b))
#endif

/**
 * \brief 初始化环形缓存区
 *
 * \param[in] p_rb       : 指向环形缓存区的指针
 * \param[in] p_data_buf : 指向环形缓存的数据缓存指针
 * \param[in] item_size  : 环形缓存区数据单元的长度
 * \param[in] count      : 环形缓存区的大小
 *
 * \retval  AM_OK        : 初始化完成
 * \retval -AM_EINVAL    : 初始化失败，参数无效
 */
int am_ringbuf_init(am_ringbuf_t *p_rb, 
                    void         *p_data_buf, 
                    uint32_t      item_size, 
                    uint32_t      count);

/**
 * \brief 清空唤醒缓存区
 * \param[in] p_rb : 指向环形缓存区的指针
 * \return  无
 */
am_static_inline
void am_ringbuf_flush (am_ringbuf_t *p_rb)
{
    p_rb->head = p_rb->tail = 0;
}

/**
 * \brief 获取环形缓存区的数据缓存长度
 * \param[in] p_rb : 指向环形缓存的指针
 * \retval    环形缓存区的大小（字节数）
 */
am_static_inline 
uint32_t am_ringbuf_size_get (am_ringbuf_t *p_rb)
{
    return (p_rb->count);
}

/**
 * \brief 获取环形缓存区的长度
 * \param[in] p_rb : 指向环形缓存的指针
 * \retval    环形缓存区的数目（以定义的数据类型位单元）
 */
am_static_inline 
uint32_t am_ringbuf_size_used_get (am_ringbuf_t *p_rb)
{
    return AM_RB_VHEAD(p_rb) - AM_RB_VTAIL(p_rb);
}

/**
 * \brief 获取环形缓存区剩余的数目
 * \param[in] p_rb : 指向环形缓存区的指针
 * \retval    环形缓存区剩余的单元数目
 */
am_static_inline 
uint32_t am_ringbuf_size_free_get (am_ringbuf_t *p_rb)
{
    return p_rb->count - am_ringbuf_size_used_get(p_rb);
}

/**
 * \brief 检测环形缓存区是否为满
 *
 * \param[in] p_rb : 指向环形缓存区的指针
 *
 * \retval TRUE    : 环形缓存区为满
 * \retval FALSE   : 环形缓存区不满
 */
am_static_inline 
bool_t am_ringbuf_isfull (am_ringbuf_t *p_rb)
{
    return (bool_t)(am_ringbuf_size_used_get(p_rb) >= p_rb->count);
}

/**
 * \brief 检测唤醒缓存区是否为空
 *
 * \param[in] p_rb : 指向环形缓存区的指针
 * 
 * \retval TRUE    : 环形缓存区为空
 * \retval FALSE   : 环形缓存区非空
 */
am_static_inline 
bool_t am_ringbuf_isempty (am_ringbuf_t *p_rb)
{
    return (bool_t)(AM_RB_VHEAD(p_rb) == AM_RB_VTAIL(p_rb));
}

/**
 * \brief 在环形缓存区中插入一个单元数据
 *
 * \param[in] p_rb   : 指向环形缓存区的指针
 * \param[in] p_data : 指向要插入的数据
 *
 * \retval  1 : 插入数据成功
 * \retval  0 : 环形缓存区为满，插入不成功
 */
uint32_t am_ringbuf_insert(am_ringbuf_t *p_rb, const void *p_data);

/**
 * \brief 在环形缓存区中插入一组数据
 *
 * \param[in] p_rb    : 指向环形缓存区的指针
 * \param[in] p_buf   : 指向要插入的数据
 * \param[in] length  : 插入数据的长度
 *
 * \return  成功插入的数目
 */
uint32_t am_ringbuf_insert_mult(am_ringbuf_t *p_rb, 
                                const void   *p_buf, 
                                uint32_t      length);

/**
 * \brief 从环形缓存区中推出一单元数据
 *
 * \param[in] p_rb   : 指向环形缓存区的指针
 * \param[in] p_data : 指向要推出的数据单元
 *
 * \retval  1 : 推出数据成功
 * \retval  0 : 环形缓存区为空，操作失败
 */
uint32_t am_ringbuf_pop(am_ringbuf_t *p_rb, void *p_data);

/**
 * \brief 从环形缓存区中推出一组数据
 *
 * \param[in] p_rb   : 指向环形缓存区的指针
 * \param[in] p_buf  : 指向要推出的数据缓存
 * \param[in] length : 环形缓存区要推出的数据长度
 *
 * \return   成功推出的数据数目
 */
uint32_t am_ringbuf_pop_mult(am_ringbuf_t *p_rb, 
                             void         *p_buf, 
                             uint32_t      length);


/**
 * @} 
 */

#ifdef __cplusplus
}
#endif
 
#endif /* __AM_RINGBUF_H */

/* end of file */

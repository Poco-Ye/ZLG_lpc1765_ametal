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
 * \brief ring buffer interfaces
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-03  jon, first implementation.
 * \endinternal
 */
 
#include "string.h"
#include "am_ringbuf.h"

/*******************************************************************************
  Private defines
*******************************************************************************/ 

#define __RB_INDH(rb)                ((rb)->head & ((rb)->count - 1))
#define __RB_INDT(rb)                ((rb)->tail & ((rb)->count - 1))

/*******************************************************************************
  Public functions
*******************************************************************************/ 

/**
 * \brief Ring buffer initialization
 */
int am_ringbuf_init (am_ringbuf_t *p_rb, 
                     void         *p_data_buf, 
                     uint32_t      item_size, 
                     uint32_t      count)
{
    if ((p_rb       == NULL) || 
        (p_data_buf == NULL) || 
        (item_size  == 0)) {
             
        return -AM_EINVAL;
    }
    
    p_rb->p_data_buf = p_data_buf;
    p_rb->count      = count;
    p_rb->item_sz    = item_size;
    p_rb->head       = p_rb->tail = 0;
    
    return AM_OK;
}

/**
 * \brief Insert a single item into ring buffer
 */
uint32_t am_ringbuf_insert (am_ringbuf_t *p_rb, const void *p_data)
{
    uint8_t *ptr = p_rb->p_data_buf;

    /* Cannot insert when ring buffer is full */
    if (am_ringbuf_isfull(p_rb) == TRUE) {
        return 0;
    }
    
    ptr += __RB_INDH(p_rb) * p_rb->item_sz;
    
    memcpy(ptr, p_data, p_rb->item_sz);
    
    p_rb->head++;
    
    return 1;
}

/**
 * \brief Insert an array of items into ring buffer
 */
uint32_t am_ringbuf_insert_mult (am_ringbuf_t  *p_rb, 
                                 const void    *p_buf, 
                                 uint32_t       length)
{
    uint8_t *ptr = p_rb->p_data_buf;
    int      cnt1, cnt2;

    /* Cannot insert when ring buffer is full */
    if (am_ringbuf_isfull(p_rb) == TRUE) {
        return 0;                     
    }

    /* Calculate the segment lengths */
    cnt1 = cnt2 = am_ringbuf_size_free_get(p_rb);
    
    if (__RB_INDH(p_rb) + cnt1 >= p_rb->count) {
        cnt1 = p_rb->count - __RB_INDH(p_rb);
    }
    cnt2   -= cnt1;

    cnt1    = AM_MIN(cnt1, length);
    length -= cnt1;

    cnt2    = AM_MIN(cnt2, length);
    length -= cnt2;

    /* Write segment 1 */
    ptr += __RB_INDH(p_rb) * p_rb->item_sz;
    memcpy(ptr, p_buf, cnt1 * p_rb->item_sz);
    
    p_rb->head += cnt1;

    /* Write segment 2 */
    ptr   = (uint8_t *)p_rb->p_data_buf + __RB_INDH(p_rb) * p_rb->item_sz;
    p_buf = (const uint8_t *)p_buf + cnt1 * p_rb->item_sz;
    
    memcpy(ptr, p_buf, cnt2 * p_rb->item_sz);
    p_rb->head += cnt2;

    return cnt1 + cnt2;
}

/**
 * \brief Pop an item from the ring buffer
 */
uint32_t am_ringbuf_pop (am_ringbuf_t *p_rb, void *p_data)
{
    uint8_t *ptr = p_rb->p_data_buf;

    /* Cannot pop when ring buffer is empty */
    if (am_ringbuf_isempty(p_rb) == TRUE) {
        return 0;
    }
        
    ptr += __RB_INDT(p_rb) * p_rb->item_sz;
    memcpy(p_data, ptr, p_rb->item_sz);
    p_rb->tail++;

    return 1;
}

/**
 * \brief Pop an array of items from the ring buffer
 */
uint32_t am_ringbuf_pop_mult (am_ringbuf_t *p_rb, 
                              void         *p_buf, 
                              uint32_t      length)
{
    uint8_t *ptr = p_rb->p_data_buf;
    int      cnt1, cnt2;

    /* Cannot pop when ring buffer is empty */
    if (am_ringbuf_isempty(p_rb) == TRUE) {
        return 0;
    }

    /* Calculate the segment lengths */
    cnt1 = cnt2 = am_ringbuf_size_used_get(p_rb);
    
    if (__RB_INDT(p_rb) + cnt1 >= p_rb->count) {
        cnt1 = p_rb->count - __RB_INDT(p_rb);
    }
    cnt2   -= cnt1;

    cnt1    = AM_MIN(cnt1, length);
    length -= cnt1;

    cnt2    = AM_MIN(cnt2, length);
    length -= cnt2;

    /* Write segment 1 */
    ptr += __RB_INDT(p_rb) * p_rb->item_sz;
    memcpy(p_buf, ptr, cnt1 * p_rb->item_sz);
    p_rb->tail += cnt1;

    /* Write segment 2 */  
    ptr   = (uint8_t *)p_rb->p_data_buf + __RB_INDT(p_rb) * p_rb->item_sz;
    p_buf = (uint8_t *)p_buf + cnt1 * p_rb->item_sz;
    
    memcpy(p_buf, ptr, cnt2 * p_rb->item_sz);
    p_rb->tail += cnt2;

    return cnt1 + cnt2;
}

/* end of file */

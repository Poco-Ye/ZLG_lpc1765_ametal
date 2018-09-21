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
 * \brief I2C drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-01-10  jon, first implementation.
 * \endinternal
 */

#include "amdr_i2c.h"
#include "amhw_clock.h"

#define __I2C_STATE_IDLE    0x01     /* 空闲状态     */
#define __I2C_STATE_READ    0x02     /* 发送数据状态 */
#define __I2C_STATE_WRITE   0x04     /* 接收数据状态 */


/*******************************************************************************
  Functions declaration
*******************************************************************************/

/* I2C hardware related configure function */
static int __i2c_speed_set(amdr_i2c_dev_t *p_dev, uint32_t speed);
static int __i2c_hard_init(amdr_i2c_dev_t *p_dev);

static int __i2c_send_data(void *p_drv);
static int __i2c_recv_data(void *p_drv);

/* I2C interrupt related functions */
static void __i2c_irq_handler(void *p_arg);
static int __i2c_mst_sm_event(void *p_arg, uint32_t status);

/* I2C driver function implementation */
static int __i2c_transfer(void *p_drv, am_i2c_transfer_t *p_trans);
static int __i2c_connect(void *p_drv);


/**
 * \brief I2C driver functions definition 
 */
static am_const struct am_i2c_drv_funcs __g_i2c_drv_funcs = {
    __i2c_transfer,
    __i2c_connect,
};

/******************************************************************************/

static void __i2c_end_with_error (amdr_i2c_dev_t *p_dev, int error)
{
    amhw_i2c_t        *p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;
    am_i2c_transfer_t *p_trans  = p_dev->p_trans; 
    
    amhw_i2c_mst_stop(p_hw_i2c);
    
    /* 恢复空闲状态 */
    p_dev->state = __I2C_STATE_IDLE;
    p_dev->busy  = FALSE;

    amhw_i2c_int_disable(p_hw_i2c, 
                         AMHW_I2C_INTENCLR_MSTPEND    |
                         AMHW_I2C_INTENCLR_MSTARBLOSS |
                         AMHW_I2C_INTENCLR_MSTSSERR);
    
    if(p_trans->pfn_callback != NULL) {
        p_trans->pfn_callback(p_trans->p_arg,error);
    }
}

/**
 * \brief I2C send device address and start transfer
 */
static int __i2c_transfer (void *p_drv, am_i2c_transfer_t *p_trans)
{
    amdr_i2c_dev_t *p_dev    = (amdr_i2c_dev_t *)p_drv;
    amhw_i2c_t     *p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;
    
    /* get device address */
    uint16_t dev_addr = (p_trans->addr) << 1;
    
    if(p_dev == NULL) {
        return -AM_EINVAL;
    }
    
    if (p_dev->busy == TRUE) {
        return -AM_EBUSY;            /* 设备忙 */
    }
    
    /* 不支持10bit 模式 */
    if (p_trans->flags & AM_I2C_ADDR_10BIT) {
        return -AM_ENOTSUP;          /* 不支持 */
    }   
 
    p_dev->busy     = TRUE;
    p_dev->p_trans  = p_trans;       /* 保存当前的transfer */
    p_dev->data_ptr = 0;             /* 数据指针清0        */
 
    /* Strat I2C controller  */
    if(!(p_trans->flags & AM_I2C_M_NOSTART)) {
        
        /* is_send start signal in this operate */
        if (p_trans->flags & AM_I2C_M_RD) {
            dev_addr |= 0x1;            /* set bit0 to 1 to indicate read operate */
        } else {
            dev_addr |= 0x0;            /* set bit0 to 0 to indicate write operate */
        }
        
        /* send device address */
        amhw_i2c_mstdat_write(p_hw_i2c, dev_addr);
        amhw_i2c_mst_start(p_hw_i2c);   /* I2C  controller send start signal */
    }
    
    if (p_trans->flags & AM_I2C_M_RD) {
        p_dev->state = __I2C_STATE_READ;
    } else {
        p_dev->state = __I2C_STATE_WRITE;
    }

    /* enable interrupt bits */
    amhw_i2c_int_enable(p_hw_i2c, 
                        AMHW_I2C_INTENSET_MSTPEND    |  /* master pending interrupt enable   */
                        AMHW_I2C_INTENSET_MSTARBLOSS |  /* master arbitration loss interrupt */
                        AMHW_I2C_INTENSET_MSTSSERR);    /* master start/stop error interrupt */

    return AM_OK;
}

/**
 * \brief I2C interrupt connect function
 */
static int __i2c_connect (void *p_drv)
{
    amdr_i2c_dev_t *p_dev = (amdr_i2c_dev_t *)p_drv;
    
    am_int_connect(p_dev->p_devinfo->inum, __i2c_irq_handler, (void *)p_drv);
    am_int_enable(p_dev->p_devinfo->inum);

    return AM_OK;
}


/**
 * \brief I2C transmit data 
 */
static int __i2c_send_data (void *p_drv)
{
    amdr_i2c_dev_t    *p_dev   = (amdr_i2c_dev_t *)p_drv;
    amhw_i2c_t        *p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;
    am_i2c_transfer_t *p_trans  = p_dev->p_trans;
    
    /* 静态变量导致不可重入，多个I2C总线调用时将会出现严重问题 */
    
    if (p_dev == NULL) {
        return -AM_EINVAL;
    }
    
    if(p_dev->data_ptr < p_trans->length) {
        amhw_i2c_mstdat_write(p_hw_i2c, ((uint8_t *)(p_trans->p_buf))[p_dev->data_ptr++]);
        amhw_i2c_mst_continue(p_hw_i2c);
    } else {
        p_dev->data_ptr = 0;
        p_dev->busy     = FALSE;     
        
        amhw_i2c_int_disable(p_hw_i2c, 
                             AMHW_I2C_INTENCLR_MSTPEND    |  
                             AMHW_I2C_INTENCLR_MSTARBLOSS |  
                             AMHW_I2C_INTENCLR_MSTSSERR);
        if(p_trans->flags & AM_I2C_M_STOP) {
            amhw_i2c_mst_stop(p_hw_i2c);
        }

        p_dev->state = __I2C_STATE_IDLE;
        
        /* current transfer send complete, callback pfunc_i2c_tx_complete */
        if(p_trans->pfn_callback != NULL) {
            p_trans->pfn_callback(p_trans->p_arg,AM_OK);     /* maybe start up transfor in callback function */
        }
    }
    return AM_OK;
}

/**
 * \brief I2C transmit data 
 */
static int __i2c_recv_data (void *p_drv)
{
    amdr_i2c_dev_t    *p_dev    = (amdr_i2c_dev_t *)p_drv;
    amhw_i2c_t        *p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;
    am_i2c_transfer_t *p_trans  = p_dev->p_trans;

    ((uint8_t *)(p_trans->p_buf))[p_dev->data_ptr++] = amhw_i2c_mstdat_read(p_hw_i2c);
    
    if(p_dev->data_ptr < p_trans->length) { 
        amhw_i2c_mst_continue(p_hw_i2c);
        
    } else {
        p_dev->data_ptr = 0;
        p_dev->busy     = FALSE;    
        amhw_i2c_int_disable(p_hw_i2c, 
                             AMHW_I2C_INTENCLR_MSTPEND    |
                             AMHW_I2C_INTENCLR_MSTARBLOSS |
                             AMHW_I2C_INTENCLR_MSTSSERR);
        
        if(p_trans->flags & AM_I2C_M_STOP) {
            amhw_i2c_mst_stop(p_hw_i2c);
        }

        p_dev->state = __I2C_STATE_IDLE;
        
        if(p_trans->pfn_callback != NULL) {
            p_trans->pfn_callback(p_trans->p_arg,AM_OK);
        }
    }
    return AM_OK;
}


/**
 * \brief set I2C master speed 
 */
static int __i2c_speed_set (amdr_i2c_dev_t *p_dev, uint32_t bus_speed)
{
    amhw_i2c_t *p_hw_i2c  = p_dev->p_devinfo->p_hw_i2c;
 
    uint32_t    scl,div,div_top;
    uint32_t    scl_h, scl_l;
    uint32_t    sum_div,cur_div;
    uint32_t    f_scl,f_div;       /* find scl and div */

    uint32_t    err,min_err;
    
    if (bus_speed > 1000000) {
        return -AM_EINVAL;        /* 支持的最大频率为1MHz */
    }
    
    /* I2C时钟的高电平和低电平均在2 ~ 9之间，即分频后，应该使到4 ~ 18个时钟组成的时钟可以得到需要的频率 */
    sum_div = amhw_clock_periph_freq_get(p_hw_i2c) / bus_speed;
    
    div_top = sum_div / 4 + 1;           /* 因为SCL最小值为4，所以分频值最大只需要为：总分频值 / 4 */
    
    /* 总的分频小于 65536 */
    if (div_top >= 65536) {
        div_top = 65536;                 /* 分频器的分频值最大为65536 */
    }
    
    min_err = 0xFFFFFFFF;
 
    //scan for the best divide value( 1 ~ 65536)
    for (div = 1; div <= div_top; div++) {
        for (scl = 4; scl <= 18; scl += 2) {
            
            cur_div = div * scl;
            
            if (cur_div > sum_div) {
                err = cur_div - sum_div;
            } else {
                err = sum_div - cur_div;
            }
            
            /* 找到了最佳分频值  */
            if (err == 0) {
                f_scl = scl;
                f_div = div;
                break;
            }
            
            if (err < min_err) {     /* 本次误差小于上次误差 */
                f_scl   = scl;
                f_div   = div;                
                min_err = err;
            }
        }
        
        /* 找到了最佳分频值  */
        if (err == 0) {
            break;
        }
    }
    
    amhw_i2c_clkdiv_set(p_hw_i2c,f_div);
    
    scl_h = f_scl >> 1;               /* 占空比设置默认为50% */
    scl_l = (f_scl - scl_h);
    
    if (scl_h < 2) {
        scl_h = 2;
    } else if (scl_h > 9) {
        scl_h = 9;
    }
    
    if (scl_l < 2) {
        scl_l = 2;
    } else if (scl_l > 9) {
        scl_l = 9;
    }
    amhw_i2c_msttime_set(p_hw_i2c, ((scl_l-2) << 0) | ((scl_h-2) << 4));
    
    return AM_OK;
}

/**
 * \brief I2C hardware configure 
 */ 
static int __i2c_hard_init (amdr_i2c_dev_t *p_dev)
{
    amhw_i2c_t *p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;
   
    
    if (p_hw_i2c == NULL) {
        return -AM_EINVAL;
    }
    
     /* close I2C controller,configure I2C master parameter */
    amhw_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);

    /* setting I2C SCL speed */
    __i2c_speed_set(p_dev, p_dev->p_devinfo->bus_speed);

    /* master parameter configured, and enable I2C controller */
    amhw_i2c_mode_enable(p_hw_i2c, AM_I2C_MASTER_MODE);

    return AM_OK;
}


/**
 * \brief the I2C initialization
 */
am_i2c_handle_t amdr_i2c_init (amdr_i2c_dev_t           *p_dev,
                               const amdr_i2c_devinfo_t *p_devinfo)
                               
{
    p_dev->i2c_serv.p_drv_funcs = (struct am_i2c_drv_funcs *)&__g_i2c_drv_funcs;
    p_dev->i2c_serv.p_drv       = p_dev; 
  
    p_dev->p_devinfo = p_devinfo;
    
    p_dev->busy     = FALSE;
    p_dev->p_trans  = NULL;
    p_dev->data_ptr = 0;
    p_dev->state    = __I2C_STATE_IDLE;    /* 初始化为空闲状态 */
    
    __i2c_hard_init(p_dev);
    
    return &(p_dev->i2c_serv);
}


/**
 * \brief the I2C de-initialization
 */
void amdr_i2c_deinit (amdr_i2c_dev_t *p_dev)
{
    amhw_i2c_t *p_hw_i2c  = p_dev->p_devinfo->p_hw_i2c;
    p_dev->i2c_serv.p_drv_funcs = NULL;
    p_dev->i2c_serv.p_drv       = NULL; 
    
    amhw_i2c_mode_disable(p_hw_i2c, AM_I2C_MASTER_MODE);
    am_int_disable(p_dev->p_devinfo->inum);
}

/**
 * \brief I2C status machine  
 * status = 0,1,2,3,4
 */
static int __i2c_mst_sm_event (void *p_arg, uint32_t status)
{   
    amdr_i2c_dev_t  *p_dev  = (amdr_i2c_dev_t *)p_arg;

    /* 以设备的状态为基准进行状态的设置 */
    switch(p_dev->state) {
        
    /* 当前没有数据请求     */
    case __I2C_STATE_IDLE:
        break;
    
    /* 当前处于接收数据状态 */
    case __I2C_STATE_READ:
        if ((status == AMHW_I2C_STAT_MSTIDLE) || 
            (status == AMHW_I2C_STAT_MSTRX)) {
                
            __i2c_recv_data(p_dev);
                
        } else if (status == AMHW_I2C_STAT_MSTNACKADDR){
            if(p_dev->p_trans->flags & AM_I2C_IGNORE_NAK) {  
                __i2c_recv_data(p_dev);
            } else {
                __i2c_end_with_error(p_dev,-AM_ENXIO);
            }
        }
        break;
    
    case __I2C_STATE_WRITE:
        if ((status == AMHW_I2C_STAT_MSTIDLE)   || 
            (status == AMHW_I2C_STAT_MSTTX)) {
                
            __i2c_send_data(p_dev);
                
        } else if (status == AMHW_I2C_STAT_MSTNACKADDR ||
                   status == AMHW_I2C_STAT_MSTNACKTX) {  /* 发送地址/数据后无应答 */
                       
            if(p_dev->p_trans->flags & AM_I2C_IGNORE_NAK) {  
                __i2c_recv_data(p_dev);
            } else {
                __i2c_end_with_error(p_dev,-AM_ENXIO);
            }
        } 
        break;
     
    default: 
        break;
    }
 
    return AM_OK;
}

/**
 * \breif I2C IRQ handler 
 */
void __i2c_irq_handler (void *p_arg)
{
    amdr_i2c_dev_t    *p_dev    = (amdr_i2c_dev_t *)p_arg;
    amhw_i2c_t        *p_hw_i2c = p_dev->p_devinfo->p_hw_i2c;

    uint32_t        i2c_status  = amhw_i2c_intstat_get(p_hw_i2c);
    uint32_t        i2c_mst_stat;
    
    if (i2c_status == 0) {
        return;
    }
    
    if ((i2c_status & AMHW_I2C_STAT_MSTARBLOSS)||            /* 总线仲裁丢失      */
        (i2c_status & AMHW_I2C_STAT_MSTSSERR)) {             /* Start/Stop error */
        
        amhw_i2c_stat_set(p_hw_i2c,                          /* clear status     */
                          AMHW_I2C_STAT_MSTARBLOSS |
                          AMHW_I2C_STAT_MSTSSERR);
            
        __i2c_end_with_error(p_dev,-AM_EIO);
    }    

    if (i2c_status & AMHW_I2C_STAT_MSTPEND) {                /* master pending status   */
        i2c_mst_stat = (amhw_i2c_stat_get(p_hw_i2c) & 
                        AMHW_I2C_MASTER_STATE_MASK);
        
        __i2c_mst_sm_event(p_dev,i2c_mst_stat);
    }
}

/* end of file */

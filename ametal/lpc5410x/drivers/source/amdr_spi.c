/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2015 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief SPI drivers implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */


#include "amdr_spi.h"
#include "amhw_clock.h"

/*******************************************************************************
* Functions declaration
*******************************************************************************/

/* SPI drive function implementation */
static int __spi_config(void *p_drv, am_spi_cfg_info_t *p_cfg_info);
static int __spi_transfer(void *p_drv, am_spi_transfer_t *p_trans);
static int __spi_connect(void *p_drv);

/* SPI interrupt related functions */
static int __spi_hard_init(amdr_spi_dev_t *p_dev);

static void __spi_irq_handler(void *p_arg);

static void __spi_mst_ctrl(amdr_spi_dev_t *p_dev);
static void __spi_write_data(amdr_spi_dev_t *p_dev);
static void __spi_read_data(amdr_spi_dev_t *p_dev);
static int  __spi_sm_send_event(amdr_spi_dev_t *p_dev, uint32_t event);


/*******************************************************************************
  SSP State and Event define
*******************************************************************************/

/*
 * SSP Controller State
 */

#define __SPI_ST_IDLE               0       /* idle state          */
#define __SPI_ST_TRANS_START        1       /* transfer start      */
#define __SPI_ST_M_SEND_DATA        2       /* master send data    */
#define __SPI_ST_M_RECV_DATA        3       /* master receive data */

/*
 * SSP Controller Event
 *
 * Event has 32-bits, bit[15:0] event number, bit[31:16] event parameter
 */

#define __SPI_EVT_NUM_GET(event)    ((event) & 0xFFFF)
#define __SPI_EVT_PAR_GET(event)    ((event >> 16) & 0xFFFF)

#define __SPI_EVT(evt_num, evt_par) (((evt_num) & 0xFFFF) | ((evt_par) << 16))

/* no event */
#define __SPI_EVT_NONE              __SPI_EVT(0, 0)

/* launch transfers */
#define __SPI_EVT_TRANS_LAUNCH      __SPI_EVT(1, 0)

/* receive data */
#define __SPI_EVT_M_SEND_DATA       __SPI_EVT(2, 0)

/* receive data */
#define __SPI_EVT_M_RECV_DATA       __SPI_EVT(3, 0)

/* udelay */
#define __SPI_EVT_UDELAY_DONE       __SPI_EVT(4, 0)

/**
 * \brief SPI driver functions definition 
 */
static am_const struct am_spi_drv_funcs __g_spi_drv_funcs = {
    __spi_config, 
    __spi_transfer,
    __spi_connect
};

/* SPI传输出现错误 */
void __spi_error_happen (amdr_spi_dev_t *p_dev)
{
    amhw_spi_t *p_hw_spi  = p_dev->p_devinfo->p_hw_spi;
    
    p_dev->state = __SPI_ST_IDLE;
    
    amhw_spi_int_disable(p_hw_spi, AMHW_SPI_INTENCLR_MSTIDLE     |
                                   AMHW_SPI_INTENCLR_RXRDY       |
                                   AMHW_SPI_INTENCLR_TXRDY       |
                                   AMHW_SPI_INTENCLR_RXOVERRUN   |
                                   AMHW_SPI_INTENCLR_TXUNDERRUN  |
                                   AMHW_SPI_INTENCLR_SELNASSERT  |
                                   AMHW_SPI_INTENCLR_SELNDEASSERT);
    
    /* 调用回调函数，声明出现错误 */
    if (p_dev->p_trans->pfn_callback) {
        p_dev->p_trans->pfn_callback(p_dev->p_trans->p_arg,AM_ERROR);
    }
}

/**
 * \brief SPI hardware initialize
 */ 
int __spi_config (void *p_arg, am_spi_cfg_info_t *p_info)
{
    amdr_spi_dev_t   *p_dev     = (amdr_spi_dev_t *)p_arg;
    amhw_spi_t       *p_hw_spi  = p_dev->p_devinfo->p_hw_spi;
    
    if (p_hw_spi == NULL) {
        return -AM_EINVAL;
    }
    
    /* 速率配置 */
    if (p_dev->cur_speed != p_info->speed) {
        
        uint32_t  max_speed,min_speed;
        
        /* close SPI controller,configure SPI master parameter */
        amhw_spi_disable(p_hw_spi);        
        
        /* 最大频率与PCLK相等 */
        max_speed = amhw_clock_periph_freq_get(p_hw_spi);
        min_speed = max_speed / 65536;
        
        if (min_speed == 0) {
            min_speed = 1;
        }
        
        if (p_info->speed > max_speed) {
            p_info->speed = max_speed;           /* 将最高频率信息返回 */
            return -AM_EHIGH;                    /* 需求的速率过高     */
        } else if (p_info->speed < min_speed) {
             p_info->speed = min_speed;          /* 将最低频率信息返回 */
            return -AM_ELOW;                     /* 需求的速率过低     */ 
        }
        
        /* SPI speed setting */
        p_hw_spi->div = (amhw_clock_periph_freq_get(p_hw_spi) / p_info->speed) - 1;
        
        p_dev->cur_speed = amhw_clock_periph_freq_get(p_hw_spi) / 
                           (p_hw_spi->div & 0xFFFF + 1);  
        
        amhw_spi_enable(p_hw_spi);
    }

    if (p_info->cfg_flags != p_dev->cur_flags) {
        
        uint32_t  cfg_flg = p_hw_spi->cfg;
        
        if(p_info->cfg_flags & AM_SPI_CFG_LSB_FIRST) {
            cfg_flg |= (1 << 3);
        } else {
            cfg_flg &= ~(1 << 3);
        }
        
        if (p_info->cfg_flags & AM_SPI_CFG_CPHA) {
            cfg_flg |= (1 << 4);
        } else {
            cfg_flg &= ~(1 << 4);
        }
        
        if (p_info->cfg_flags & AM_SPI_CFG_CPOL) {
            cfg_flg |= (1 << 5);
        } else {
            cfg_flg &= ~(1 << 5);
        }
        
        if (p_info->cfg_flags & AM_SPI_CFG_LOOP) {
            cfg_flg |= (1 << 7);
        } else {
            cfg_flg &= ~(1 << 7);
        }
        
        p_dev->cur_flags = p_info->cfg_flags;
        
        amhw_spi_disable(p_hw_spi); 
        
        /* SPI Configuration */
        p_hw_spi->cfg = cfg_flg;
        
        /* enable SPI controller */
        amhw_spi_enable(p_hw_spi);
    }
 
    /* 设置与当前设置不匹配时才进行配置 */
    if (p_info->bpw != p_dev->cur_bpw) {
        
        if (p_info->bpw > 16) {
            return -AM_ENOTSUP;                /* 不支持的位宽或模式      */
        } else {
            p_dev->cur_bpw = p_info->bpw;      /* 保存位宽，发送数据时设置 */
        }
    }
    
    return AM_OK;
}

/**
 * \brief SPI interrupt connect function
 */
int __spi_connect (void *p_drv)
{
    amdr_spi_dev_t *p_dev = (amdr_spi_dev_t *)p_drv;

    am_int_connect(p_dev->p_devinfo->inum, __spi_irq_handler, (void *)p_drv);
    am_int_enable(p_dev->p_devinfo->inum);
    
    return AM_OK;
}

/**
 * \brief SPI master frame control configure
 */
void __spi_mst_ctrl (amdr_spi_dev_t *p_dev) 
{
    amhw_spi_t        *p_hw_spi = p_dev->p_devinfo->p_hw_spi;
    am_spi_transfer_t *p_trans  = p_dev->p_trans; 
    
    if (p_dev == NULL) {
        return ;
    }
    
    /* 位宽为 1 ~ 8位 */
    if (p_dev->cur_bpw <= 8) {
        
        /* 最后一个字的传输 */
        if ( (p_dev->data_ptr == (p_trans->nbytes - 1)) &&
             (p_dev->p_trans->flags & AM_SPI_TRANS_EOT)) {
                 
            amhw_spi_end_trans_enable(p_hw_spi);
        } else {
            amhw_spi_end_trans_disable(p_hw_spi);
        }
        
    } else {
         /* 最后一个字的传输 */
        if ( (p_dev->data_ptr == (p_trans->nbytes - 2)) &&
             (p_dev->p_trans->flags & AM_SPI_TRANS_EOT)) {
                 
            amhw_spi_end_trans_enable(p_hw_spi);
        } else {
            amhw_spi_end_trans_disable(p_hw_spi);
        }
    }
    
    /* 不需要接收数据 */
    if (p_trans->p_rxbuf == NULL) {
        amhw_spi_ignore_recv_enable(p_hw_spi);
    } else {
        amhw_spi_ignore_recv_disable(p_hw_spi);
    }
}

void __spi_write_data (amdr_spi_dev_t *p_dev)
{
    amhw_spi_t                 *p_hw_spi = p_dev->p_devinfo->p_hw_spi;
    am_spi_transfer_t          *p_trans  = p_dev->p_trans; 
    
    if (p_dev == NULL) {
        return ;
    }
    
    /* tx_buf valid */
    if (p_trans->p_txbuf != NULL) {
        if ((p_dev->cur_bpw) <= 8) {
            uint8_t *ptr = (uint8_t *)(p_trans->p_txbuf) + p_dev->data_ptr;
            amhw_spi_txdat_write(p_hw_spi, *ptr);
        } else {
            uint16_t *ptr = (uint16_t *)((uint8_t *)(p_trans->p_txbuf) + p_dev->data_ptr);
            amhw_spi_txdat_write(p_hw_spi, *ptr);
        }
        
    /* tx_buf invalid */
    } else {
        amhw_spi_txdat_write(p_hw_spi, 0x0000);
    }
 
    /* nbytes data to receive */
    p_dev->nbytes_to_recv = p_dev->cur_bpw < 9 ? 1 : 2;
    
}

void __spi_read_data (amdr_spi_dev_t *p_dev)
{
    amhw_spi_t                 *p_hw_spi = p_dev->p_devinfo->p_hw_spi;
    am_spi_transfer_t          *p_trans  = p_dev->p_trans; 
 
    uint8_t *p_buf8  = (uint8_t *)p_trans->p_rxbuf + p_dev->data_ptr;
 
    if(p_dev == NULL) {
        return ;
    }
    
    /*  rx_buf valid */
    if (p_trans->p_rxbuf != NULL && p_dev->nbytes_to_recv) {
        if ((p_dev->cur_bpw) <= 8) {
             *p_buf8 = amhw_spi_rxdata_8bit_read(p_hw_spi); 
        
        } else {   
             *(uint16_t *)(p_buf8) = amhw_spi_rxdata_16bit_read(p_hw_spi);
        }
        
    /* rx_buf invalid or no need to recieve data */
    } else { 
        if ((p_dev->cur_bpw) <= 8) {
            (void)amhw_spi_rxdata_8bit_read(p_hw_spi); 
        
        } else {
            (void)amhw_spi_rxdata_16bit_read(p_hw_spi);
        }
    }
    
    /* nbytes data already sent and received */
    p_dev->data_ptr += p_dev->nbytes_to_recv;
    
    p_dev->nbytes_to_recv = 0;
}

/** 
 * \brief SPI interrupt handle function
 */
void __spi_irq_handler (void *p_arg)
{
    amdr_spi_dev_t  *p_dev      = (amdr_spi_dev_t *)p_arg;
    amhw_spi_t      *p_hw_spi   = p_dev->p_devinfo->p_hw_spi;
    uint32_t         spi_status = amhw_spi_intstat_read(p_hw_spi); /* get int_status info */       

    if ((spi_status & AMHW_SPI_STAT_SELNASSERT)  ||
        (spi_status & AMHW_SPI_STAT_SELNDEASSERT)) {
            
        amhw_spi_stat_clear(p_hw_spi, AMHW_SPI_STAT_SELNASSERT |
                                      AMHW_SPI_STAT_SELNDEASSERT);
    }
    
    if ((spi_status & AMHW_SPI_STAT_RXOVERRUN)  ||
        (spi_status & AMHW_SPI_STAT_TXUNDERRUN)) {
            
        amhw_spi_stat_clear(p_hw_spi, AMHW_SPI_STAT_RXOVERRUN  | 
                                      AMHW_SPI_STAT_TXUNDERRUN | 
                                      AMHW_SPI_STAT_SELNASSERT |
                                      AMHW_SPI_STAT_SELNDEASSERT);
        __spi_error_happen(p_dev);
    
    }

    /* 发送数据 */
    if (spi_status & AMHW_SPI_STAT_TXRDY) {
        /* run the state machine */
        __spi_sm_send_event(p_dev, __SPI_EVT_M_SEND_DATA);
    }
    
    if (spi_status & AMHW_SPI_STAT_RXRDY) {
        __spi_sm_send_event(p_dev, __SPI_EVT_M_RECV_DATA);
    }
}

int __spi_hard_init (amdr_spi_dev_t *p_dev)
{
    const amdr_spi_devinfo_t *p_devinfo = p_dev->p_devinfo;
    amhw_spi_t               *p_hw_spi  = p_devinfo->p_hw_spi;
    amhw_spi_mst_delay_t      delay_config;
    am_spi_cfg_info_t         cfg_info;

    if (p_hw_spi == NULL) {
        return -AM_EINVAL;
    }

     /* close SPI controller,configure SPI master parameter */
    amhw_spi_disable(p_hw_spi);

    /* transfer delay configure */
    delay_config.predelay      = 0x0; 
    delay_config.postdelay     = 0x0;
    delay_config.framedelay    = 0x0;
    delay_config.transferdelay = 0x0;
    
    amhw_spi_master_dly(p_hw_spi, &delay_config);

    /* SPI Configuration */
    p_hw_spi->cfg = AMHW_SPI_CFG_MASTER;               /* configure master/slave mode  */
    
    /* 复位状态下的标识 */
    p_dev->cur_bpw    = 8;                             /* 默认位宽，8位                 */
    p_dev->cur_flags  = AM_SPI_CFG_MODE_0;
    p_dev->cur_speed  = amhw_clock_periph_freq_get(p_hw_spi);
    
    cfg_info.bpw       = p_devinfo->bits_per_word;
    cfg_info.cfg_flags = p_devinfo->flags;
    cfg_info.speed     = p_devinfo->speed;
    
    if (p_devinfo->speed > amhw_clock_periph_freq_get(p_hw_spi)) {
        cfg_info.speed = amhw_clock_periph_freq_get(p_hw_spi);
    }
    
    if (p_devinfo->speed < amhw_clock_periph_freq_get(p_hw_spi) / 65536 ) {
        cfg_info.speed = amhw_clock_periph_freq_get(p_hw_spi) / 65536;
    }
    
    /* 配置SPI */
    __spi_config(p_dev,&cfg_info);
    
    /* master parameter configured, and enable SPI controller */
    amhw_spi_enable(p_hw_spi);

    return AM_OK;
}

/**
 * \brief SPI initialize
 */
am_spi_handle_t amdr_spi_init (amdr_spi_dev_t           *p_dev,
                               const amdr_spi_devinfo_t *p_devinfo)
{
    p_dev->spi_serve.p_drv_funcs = (struct am_spi_drv_funcs *)&__g_spi_drv_funcs;
    p_dev->spi_serve.p_drv       = p_dev; 
  
    p_dev->p_devinfo = p_devinfo;
    
    __spi_hard_init(p_dev);
    
    p_dev->data_ptr        = 0;
    p_dev->nbytes_to_recv  = 0;
    p_dev->state           = __SPI_ST_IDLE;
    
    return &(p_dev->spi_serve);
}
/**
 * \brief SPI De_initialize
 */
void amdr_spi_deinit(amdr_spi_dev_t *p_dev)
{
    amhw_spi_t *p_hw_spi  = p_dev->p_devinfo->p_hw_spi;
    
    p_dev->spi_serve.p_drv_funcs = NULL;
    p_dev->spi_serve.p_drv       = NULL; 
    
    amhw_spi_disable(p_hw_spi);

    am_int_disable(p_dev->p_devinfo->inum);
    am_int_disconnect(p_dev->p_devinfo->inum,__spi_irq_handler, (void *)p_dev);
}


/**
 * \brief SPI transfer data function 
 */
int __spi_transfer (void *p_drv, am_spi_transfer_t *p_trans)
{
    amdr_spi_dev_t             *p_dev    = (amdr_spi_dev_t *)p_drv;
    amhw_spi_t                 *p_hw_spi = p_dev->p_devinfo->p_hw_spi;
    uint32_t                    txctl_tmp;
    
    if(p_dev == NULL) {
        return -AM_EINVAL;
    }
    
    p_dev->nbytes_to_recv = 0;
    p_dev->data_ptr       = 0;
 
    p_dev->p_trans        = p_trans;
   
    
    txctl_tmp  = p_hw_spi->txctl;
    
    /* 设置位宽 */
    txctl_tmp &= ~(0xFFul << 24);
    txctl_tmp |= AMHW_SPI_TXDATCTL_FSIZE(p_dev->cur_bpw - 1);
    
    //AMHW_SPI_TXDATCTL_SSELN(p_param->slave),是否需要选择SPI片选管脚
    
    p_hw_spi->txctl = txctl_tmp;
    
    
    /* launch the state machine */
    return __spi_sm_send_event(p_dev, __SPI_EVT_TRANS_LAUNCH);
}


/*  translate to next sate */
#define __spi_next_state(s, e) \
    do { \
        p_dev->state = (s); \
        new_event = (e); \
    } while(0)

/**
 * \brief send event to SPI controller state machine
 */
static int __spi_sm_send_event (amdr_spi_dev_t *p_dev, uint32_t event)
{
    amhw_spi_t  *p_hw_spi = p_dev->p_devinfo->p_hw_spi;

    volatile uint32_t new_event = __SPI_EVT_NONE;

    while (1) {

        /* check if new event is sent from internal */
        if (new_event != __SPI_EVT_NONE) {
            event     = new_event;
            new_event = __SPI_EVT_NONE;
        }

        switch (p_dev->state) {

        /*
         * The controller is in idle state, waiting for someone lauch
         * the message transfer.
         */

        case __SPI_ST_IDLE:
        {
            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;                /* 空闲状态等待的消息必须是启动传输 */
            }
        }

        /*
         * Transfer start, get a transfer from current processing message,
         * and start transfer.
         */
        case __SPI_ST_TRANS_START:
        {
            
            if (event != __SPI_EVT_TRANS_LAUNCH) {
                return -AM_EINVAL;                /* 空闲状态等待的消息必须是启动传输 */
            }

            /* reset current data pointer */
            p_dev->data_ptr       = 0;
            p_dev->nbytes_to_recv = 0;

            /* next op. is send data */
            __spi_next_state(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);
            
            break;
        }

        /*
         * Send data bytes
         */

        case __SPI_ST_M_SEND_DATA:
        {
            if (event != __SPI_EVT_M_SEND_DATA) {
                return -AM_EINVAL;                /* 空闲状态等待的消息必须是启动传输 */
            }
            
            /* no more data to transfer */
            if (p_dev->data_ptr >= p_dev->p_trans->nbytes) {

                 /* NO data to transform */
                 amhw_spi_int_disable(p_hw_spi,AMHW_SPI_INTENSET_TXRDY);
                 
                 /* back to IDLE state */
                 __spi_next_state(__SPI_ST_IDLE, __SPI_EVT_NONE);
                
                 if (p_dev->p_trans->pfn_callback) {
                     p_dev->p_trans->pfn_callback(p_dev->p_trans->p_arg,AM_OK);
                 }

                 break;
                 
            } else {
                
                if ((amhw_spi_stat_read(p_hw_spi) & AMHW_SPI_STAT_TXRDY) != 0) {
                
                     /* transfer control configure */
                    __spi_mst_ctrl(p_dev);
                    
                    /* write data to slave device */
                    __spi_write_data(p_dev);

                    /* disable TX interrupt */
                    amhw_spi_int_disable(p_hw_spi,AMHW_SPI_INTENSET_TXRDY);
                    
                    /* 忽略了接收 */
                    if (p_dev->p_trans->p_rxbuf == NULL) {
                        
                        p_dev->nbytes_to_recv = 0;
                        
                        p_dev->data_ptr += (p_dev->cur_bpw < 9 ? 1 : 2);
                        
                        /* 忽略了接收，下一状态还是发送状态 */
                        __spi_next_state(__SPI_ST_M_SEND_DATA, __SPI_EVT_NONE);
                        
                        amhw_spi_int_disable(p_hw_spi,AMHW_SPI_INTENSET_RXRDY);
                        
                        /* 开启发送中断，通过发送完成切换到下一个状态 */
                        amhw_spi_int_enable(p_hw_spi,AMHW_SPI_INTENSET_TXRDY);

                    } else {
                        
                        /* 未忽略接收，下一状态是接收状态 */
                        __spi_next_state(__SPI_ST_M_RECV_DATA, __SPI_EVT_NONE);                        
                        
                        /* Enable RX interrupt */
                        amhw_spi_int_enable(p_dev->p_devinfo->p_hw_spi, AMHW_SPI_INTENSET_RXRDY      |
                                                                        AMHW_SPI_INTENSET_RXOVERRUN  |
                                                                        AMHW_SPI_INTENSET_TXUNDERRUN);

                    }
                } else {                                            /* 打开中断等待发送就绪 */
                    /* Enable TX interrupt */
                    amhw_spi_int_enable(p_hw_spi,AMHW_SPI_INTENSET_TXRDY);
                }
            }
            break;
        }

        /*
         * Receive data bytes
         */
        case __SPI_ST_M_RECV_DATA:
        {
            
            if (event != __SPI_EVT_M_RECV_DATA) {
                return -AM_EINVAL;                /* 空闲状态等待的消息必须是启动传输 */
            }
            
            __spi_read_data(p_dev);

            /* no more data to receive */
            if (p_dev->nbytes_to_recv == 0) {

                /* transfer the remain data */
                __spi_next_state(__SPI_ST_M_SEND_DATA, __SPI_EVT_M_SEND_DATA);

                /* disable TX and RX interrupt */
                amhw_spi_int_disable(p_hw_spi,AMHW_SPI_INTENSET_RXRDY      |
                                              AMHW_SPI_INTENSET_TXRDY      |
                                              AMHW_SPI_INTENSET_RXOVERRUN  |
                                              AMHW_SPI_INTENSET_TXUNDERRUN |
                                              AMHW_SPI_INTENSET_SELNASSERT |
                                              AMHW_SPI_INTENSET_SELNDEASSERT);
            /* more data to receive */
            } else {
                /* do nothing here */
            }
            break;
        }

        /*
         * should never run to here
         */
        default:
            break;
        }

        /* no new event sent from internal, break out */
        if (new_event == __SPI_EVT_NONE) {
            break;
        }
    }

    return AM_OK;
}

/* end of file */

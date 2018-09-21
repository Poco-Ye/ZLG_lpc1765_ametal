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
 * \brief GPIO implementation
 * 
 * - GPIO pins can be configured as input or output by software.
 * - All GPIO pins default to inputs with interrupt disabled at reset.
 * - Pin registers allow pins to be sensed and set individually.
 *
 * \internal
 * \par Modification history
 * - 1.00 15-01-01  hbt, first implementation.
 * \endinternal
 */


#include "amdr_gpio.h"
#include "amdr_gpio_util.h"   
#include "am_gpio_util.h"
#include "am_int.h"
#include "amhw_clock.h"


/*******************************************************************************
* ˽�ж���
*******************************************************************************/

/** \brief �ж�δ���ӱ�ʶ */
#define AMDR_GPIO_INVALID_PIN_MAP    0xFF

/** \brief ����ָ��GPIO�豸��Ϣ��ָ�� */
#define __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev)  \
        const amdr_gpio_devinfo_t *p_gpio_devinfo = p_dev->p_devinfo

/******************************************************************************
  ȫ�ֱ���
******************************************************************************/

/** \bruef ָ��GPIO�豸��ָ�� */
amdr_gpio_dev_t *__gp_gpio_dev;

/*******************************************************************************
  ��������
*******************************************************************************/ 

/* ���Ź������� */
int am_gpio_pin_cfg (int pin, uint32_t flags)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    
    uint32_t func, mode;
    uint32_t iocon_cfg;
    
    amhw_gpio_t  *p_hw_gpio  = p_gpio_devinfo->p_hw_gpio; 
    amhw_iocon_t *p_hw_iocon = p_gpio_devinfo->p_hw_iocon;

    iocon_cfg = (p_hw_iocon->pio[pin >> 5][(pin & 0x1F)]);
    
    func      = AM_GPIO_COM_FUNC_GET(flags);
    mode      = AM_GPIO_COM_MODE_GET(flags);
    
    /*
     * ���й�������
     */
    if (func != 0x00) {
        flags &= ~AMDR_GPIO_DIREN_BIT;                /* ��������Ҫ�����÷��� */
        
        switch (func) {
        case 1:
            amhw_gpio_pin_dir_input(p_hw_gpio, pin);
            break;
        case 2:
            amhw_gpio_pin_dir_output(p_hw_gpio, pin);
            break;
        case 3:
            amhw_gpio_pin_dir_output(p_hw_gpio, pin);
            amhw_gpio_pin_out_high(p_hw_gpio, pin);
            break;
        case 4:
            amhw_gpio_pin_dir_output(p_hw_gpio, pin);
            amhw_gpio_pin_out_low(p_hw_gpio, pin);
            break;
        default:
            break;
        }
    }
    
    if (mode != 0x00) {
        
        if (mode < AM_GPIO_OPEN_DRAIN_VAL) {
            flags &= ~AMDR_GPIO_CON_BIT3;                /* ��������Ҫ������ģʽ */
            
            iocon_cfg &= ~(AM_SBF((0x3), 3));            /* ��0 */  
            iocon_cfg |= (((~mode) & 0x3) << 3);
            
        } else if (mode == AM_GPIO_OPEN_DRAIN_VAL) {     /* ��������Ҫ������bit10��ODλ */
            flags &= ~AMDR_GPIO_CON_BIT10;
            
            iocon_cfg &= ~(AM_SBF((1), 10));              /* ��0 */  
            iocon_cfg |=  (AMDR_GPIO_ODBIT_GET(flags) << 10);
            
        } else if (mode > AM_GPIO_OPEN_DRAIN_VAL) {
            return -AM_ENOTSUP;
        }
    }

    /*
     * ƽ̨��������
     */
    if ((flags & AMDR_GPIO_CON_BIT0) != 0) {              /* ��Ҫ���ù����� */
        iocon_cfg &= ~(AM_SBF((0x7), 0));                 /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_FUNC_GET(flags) << 0);   
    }

    if ((flags & AMDR_GPIO_DIREN_BIT) != 0) {             /* ��Ҫ���÷����� */
        if (AMDR_GPIO_DIR_GET(flags) == 0) {
            amhw_gpio_pin_dir_input(p_hw_gpio, pin);
        } else {
            amhw_gpio_pin_dir_output(p_hw_gpio, pin);
        }
    }
    
    if ((flags & AMDR_GPIO_I2CEN_BIT) != 0) {
        iocon_cfg &= ~(AM_SBF((0x3F), 5));            /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_I2C_FUNC_GET(flags) << 5);
    }

    if ((flags & AMDR_GPIO_ADCEN_BIT) != 0) {
        iocon_cfg &= ~(AM_SBF((0x3), 3));            /* ����ģʽ��������/������ */  
        iocon_cfg &= ~(AM_SBF((1), 7));              /* ģ������ģʽ */
    }
    
    if ((flags & AMDR_GPIO_CON_BIT3) != 0) {
        iocon_cfg &= ~(AM_SBF((0x3), 3));            /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_MODE_GET(flags) << 3);
    }
    
    if ((flags & AMDR_GPIO_CON_BIT5) != 0) {
        iocon_cfg &= ~(AM_SBF((1), 5));              /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_I2CSLEWBIT_GET(flags) << 5);
    }
    
    if ((flags & AMDR_GPIO_CON_BIT6) != 0) {
        iocon_cfg &= ~(AM_SBF((1), 6));              /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_INVERTBIT_GET(flags) << 6);
    }
    
    if ((flags & AMDR_GPIO_CON_BIT8) != 0) {
        iocon_cfg &= ~(AM_SBF((1), 8));              /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_FILTEROFFBIT_GET(flags) << 8);
    }
    
    if ((flags & AMDR_GPIO_CON_BIT9) != 0) {
        iocon_cfg &= ~(AM_SBF((1), 9));              /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_SLEWBIT_GET(flags) << 9);
    }
    
    if ((flags & AMDR_GPIO_CON_BIT10) != 0) {
        iocon_cfg &= ~(AM_SBF((1), 10));              /* ��0 */  
        iocon_cfg |=  (AMDR_GPIO_ODBIT_GET(flags) << 10);
    }
    
    amhw_iocon_cfg(p_hw_iocon, pin, iocon_cfg);
    
    return AM_OK;
}


/* ��ȡ����״̬ */
int am_gpio_get (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    
    return (int)amhw_gpio_pin_get(p_gpio_devinfo->p_hw_gpio, pin);
}

/* �����������״̬ */
int am_gpio_set (int pin, int value)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    
    if (value == 0) {
        amhw_gpio_pin_out_low(p_gpio_devinfo->p_hw_gpio, pin);
    } else {
        amhw_gpio_pin_out_high(p_gpio_devinfo->p_hw_gpio, pin);
    }
    
    return AM_OK;
}

/* �������״̬��ת */
int am_gpio_toggle (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    
    amhw_gpio_pin_toggle(p_gpio_devinfo->p_hw_gpio, pin);
    
    return AM_OK;
}

/**
 * \brief ���Ŵ�����ʽѡ��
 */
int am_gpio_trigger_cfg (int pin, uint32_t flag)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    
    int i;
    int slot = -1;
    
    amhw_pint_t *p_hw_pint = p_gpio_devinfo->p_hw_pint; 

    for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
        if ((p_gpio_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        return -AM_ENXIO;
    }

    slot = (1UL << slot);
    amhw_pint_status_clr(p_hw_pint, slot);
    
    switch (flag) {
    case 0:       /* �رմ��� */
        amhw_pint_high_disable(p_hw_pint, slot);
        amhw_pint_low_disable(p_hw_pint, slot);
        break;
    
    case 1:       /* �ߵ�ƽ���� */
        amhw_pint_level_set(p_hw_pint, slot);
        amhw_pint_high_enable(p_hw_pint, slot);
        amhw_pint_low_disable(p_hw_pint, slot);
        break;
    
    case 2:        /* �͵�ƽ���� */
        amhw_pint_level_set(p_hw_pint, slot);
        amhw_pint_high_disable(p_hw_pint, slot);
        amhw_pint_low_enable(p_hw_pint, slot);
        break;
    
    case 3:        /* �����ش��� */
        amhw_pint_edge_set(p_hw_pint, slot);
        amhw_pint_high_enable(p_hw_pint, slot);
        amhw_pint_low_disable(p_hw_pint, slot);
        break;
    
    case 4:        /* �½��ش��� */
        amhw_pint_edge_set(p_hw_pint, slot);
        amhw_pint_high_disable(p_hw_pint, slot);
        amhw_pint_low_enable(p_hw_pint, slot);
        break;
    
    case 5:        /* ˫���ش��� */
        amhw_pint_edge_set(p_hw_pint, slot);
        amhw_pint_high_enable(p_hw_pint, slot);
        amhw_pint_low_enable(p_hw_pint, slot);
        break;
    
    default:
        break;
    }
    
    return AM_OK;
}

/**
 * \brief GPIO �жϷ�����Ӧ������
 * \param[in] p_arg : ��ǰ�ж�ӳ���š�
 */
static void __gpio_eint_isr (void *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    int          slot      = (int)p_arg;
    am_pfnvoid_t pfn_isr   = NULL;
    void        *p_arg_tmp = NULL;
    amhw_pint_t *p_hw_pint = p_gpio_devinfo->p_hw_pint;
    
    /* ����Ǳ������д�����������ؼ�⹦�� */
    if (!(p_hw_pint->isel & (1UL << slot))) {
        p_hw_pint->ist = (1 << slot); 
    }
    
    /* ��ȡ�йػص����������� */
    pfn_isr = p_gpio_devinfo->p_triginfo[slot].pfn_callback;
    p_arg   = p_gpio_devinfo->p_triginfo[slot].p_arg;
    
    if (pfn_isr != NULL) {
        pfn_isr(p_arg_tmp);
    }
}

/**
 * \brief ���������жϻص�����
 */
int am_gpio_trigger_connect (int           pin,
                             am_pfnvoid_t  pfn_callback,
                             void         *p_arg)
{ 
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    int          key;
    int          i;
    int          slot      = -1;
    int          err       = AM_OK;
    bool_t       already   = FALSE;
    amhw_gpio_t *p_hw_gpio = p_gpio_devinfo->p_hw_gpio;
    
    amhw_gpio_pin_dir_input(p_hw_gpio, pin);

    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();
    
    for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
        if ((p_gpio_devinfo->p_infomap)[i] == AMDR_GPIO_INVALID_PIN_MAP) {
            slot = i;
            break;
        }
        if (p_gpio_devinfo->p_infomap[i] == pin) {
            already = TRUE;
            break;
        }
    }
    
    if (already) {  
        
        /* ��CPU�ж� */
        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }
    
    if (-1 != slot) {
        err = am_int_connect((p_gpio_devinfo->inum_pin)[slot],
                             (am_pfnvoid_t)__gpio_eint_isr,
                             (void *)slot);
        
        /*  ���津�����ż��ص����� */
        if (AM_OK == err) {
            (p_gpio_devinfo->p_infomap)[slot]               = pin;
            (p_gpio_devinfo->p_triginfo)[slot].pfn_callback = pfn_callback;
            (p_gpio_devinfo->p_triginfo)[slot].p_arg        = p_arg;
        }
        
        amhw_inmux_pint_sel(p_gpio_devinfo->p_hw_inmux, slot, pin);
        
        /* ���ж� */
        am_int_cpu_unlock(key);
        
    }
     return AM_OK;
}


/**
 * \brief ɾ�������жϻص���������
 */
int am_gpio_trigger_disconnect (int           pin,
                                am_pfnvoid_t  pfn_callback,
                                void         *p_arg)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    int key;
    int i;
    int slot = -1;
    
    /* �ر�CPU�ж� */  
    key = am_int_cpu_lock();
    
    for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
        if ((p_gpio_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {

        /* ��CPU�ж� */ 
        am_int_cpu_unlock(key);
        return -AM_EINVAL;
    }
    
    am_int_disconnect((p_gpio_devinfo->inum_pin)[slot],
                      (am_pfnvoid_t)__gpio_eint_isr,
                      (void *)slot);
    
    (p_gpio_devinfo->p_infomap)[slot]               = AMDR_GPIO_INVALID_PIN_MAP;
    (p_gpio_devinfo->p_triginfo)[slot].pfn_callback = NULL;
 
    /* ��CPU�ж� */ 
    am_int_cpu_unlock(key);
    
    return AM_OK;
}

/**
 * \brief ʹ�������жϡ�
 */
int am_gpio_trigger_on (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    int key;
    int i;
    int slot = -1;
    
    /* �ر�CPU�ж� */
    key = am_int_cpu_lock();
    
    for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
        if ((p_gpio_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }
    
    /* ��CPU�ж�t */ 
    am_int_cpu_unlock(key);
    
    if (slot == -1) {
        return -AM_ENXIO;
    }
    
    return am_int_enable((p_gpio_devinfo->inum_pin)[slot]);
}

/**
 * \brief ���������жϡ�
 */
int am_gpio_trigger_off (int pin)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, __gp_gpio_dev);
    int key;
    int i;
    int slot = -1;
    
    /* �ر�CPU�ж� */ 
    key = am_int_cpu_lock();
    
    for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
        if ((p_gpio_devinfo->p_infomap)[i] == pin) {
            slot = i;
            break;
        }
    }
    
    /* ��CPU�ж� */
    am_int_cpu_unlock(key);
    
    if (slot == -1) {
        return -AM_ENXIO;
    }
    
    return am_int_disable((p_gpio_devinfo->inum_pin)[slot]);
}

/**
 * \brief GPIO��ʼ��
 */
int amdr_gpio_init (amdr_gpio_dev_t           *p_dev, 
                    const amdr_gpio_devinfo_t *p_devinfo)
{
    int i;

    if (p_dev == NULL || p_devinfo == NULL) {
        return -AM_EINVAL;
    }
    
    p_dev->p_devinfo  = p_devinfo;
    __gp_gpio_dev     = p_dev;
    p_dev->valid_flg  = TRUE;
        
    if ((p_devinfo->p_triginfo == NULL) ||
        (p_devinfo->p_infomap == NULL)) {
        p_dev->valid_flg = FALSE;
    }

    if (p_dev->valid_flg) {
        for (i = 0; i < p_devinfo->pint_count; i++) {
            (p_devinfo->p_infomap)[i]               = AMDR_GPIO_INVALID_PIN_MAP;
            (p_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }
    
    return AM_OK;
}

/**
 * \brief GPIOȥ��ʼ��
 */
void amdr_gpio_deinit (amdr_gpio_dev_t *p_dev)
{
    __GPIO_DEVINFO_DECL(p_gpio_devinfo, p_dev);
    int i;
    
    if (p_dev->valid_flg) {
        for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
            (p_gpio_devinfo->p_infomap)[i]               = 0;
            (p_gpio_devinfo->p_triginfo)[i].pfn_callback = NULL;
        }
    }
    
    for (i = 0; i < p_gpio_devinfo->pint_count; i++) {
        am_int_disable((p_gpio_devinfo->inum_pin)[i]);
    }
}


/* end of file */

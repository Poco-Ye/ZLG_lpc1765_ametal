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
 * \brief I2C Ӳ�������ӿ�
 * 
 * 1. ���ж����������ӻ��ͼ�صȹ��ܣ�
 * 2. �����ٶ�:
 *    - ��׼ģʽ��, �ɸߴ�100k bits/s��
 *    - ����ģʽ��, �ɸߴ�400k bits/s��
 *    - ����ģʽplus��, �ɸߴ�1M bits/s��
 *    - ����ģʽ��, �ڴӻ�ģʽ�ɸߴ�3.4M bits/s��
 * 3. ֧�ֶ�������;��дӻ��Ķ�������
 * 4. ��Ӳ����֧�ֶ���ӻ���ַ��
 * 5. ͨ��������ã���֧��10bits��ַ���豸��
 * 6. ֧��ϵͳ�������ߣ�
 * 7. Ϊ�˽�������DMA�ɶ�������I2C���������ӻ��ͼ�أ�
 * 8. ����Ƭ��ʱ������ʱ�������ݺʹӻ���ַƥ�䣬���Խ��豸�ӵ���ģʽ�л��ѣ� 
 * 9. ���������ӻ�ģʽ��֧�ֿ���ģʽplus (FM+, �������ʿɸߴ� 1 MHz) 
 *    ����ģʽ���豸Ϊ�ӻ�ʱ֧�֣��������ʿɸߴ� 3.4 MHz����
 *   
 *
 * \internal
 * \par Modification History
 * - 1.00 14-11-01  jon, first implementation.
 * \endinternal
 */

#ifndef __AMHW_I2C_H
#define __AMHW_I2C_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
/**
 * @addtogroup amhw_if_i2c
 * @copydoc amhw_i2c.h
 * @{
 */
    
/**
 * \brief I2C �Ĵ�����ṹ��
 */
typedef struct amhw_i2c {
    __IO uint32_t  cfg;           /**< \brief I2C ���üĴ���              */
    __IO uint32_t  stat;          /**< \brief I2C ״̬�Ĵ���              */
    __IO uint32_t  intenset;      /**< \brief I2C �ж�λʹ�ܻ��ȡ�Ĵ���  */
    __O  uint32_t  intenclr;      /**< \brief I2C �ж�λ���ܼĴ���        */
    __IO uint32_t  timeout;       /**< \brief I2C ��ʱʱ���趨�Ĵ���      */
    __IO uint32_t  clkdiv;        /**< \brief I2C ʱ�ӷ�Ƶ��ֵ�趨�Ĵ���  */
    __I  uint32_t  intstat;       /**< \brief I2C �ж�״̬                */
    __I  uint32_t  reserved;      /**< \brief ����λ                      */
    __IO uint32_t  mstctl;        /**< \brief I2C �������ƼĴ���          */
    __IO uint32_t  msttime;       /**< \brief I2C ����SCL�ߵ�ƽ�͵͵�ƽʱ���趨�Ĵ��� */
    __IO uint32_t  mstdat;        /**< \brief I2C �������ݼĴ���          */
    __I  uint32_t  reserved1[5];  /**< \brief ����λ                      */
    __IO uint32_t  slvctl;        /**< \brief I2C �ӻ����ƼĴ���          */
    __IO uint32_t  slvdat;        /**< \brief I2C �ӻ����ݼĴ���          */
    __IO uint32_t  slvadr0;       /**< \brief �ӻ���ַ0                   */
    __IO uint32_t  slvadr1;       /**< \brief �ӻ���ַ1                   */
    __IO uint32_t  slvadr2;       /**< \brief �ӻ���ַ2                   */
    __IO uint32_t  slvadr3;       /**< \brief �ӻ���ַ3                   */
    __IO uint32_t  slvqual0;      /**< \brief �ӻ���ַ�޶��Ĵ���          */
    __I  uint32_t  reserved2[9];  /**< \brief ����λ                      */
    __I  uint32_t  monrxdat;      /**< \brief ���ģʽ���ݼĴ���          */
} amhw_i2c_t;



/**
 * \name I2C ״̬�Ĵ�������λ��ϸ����
 * @{
 */

#define AMHW_I2C_STAT_MSTPEND          (0x1 << 0)  /**< \brief I2C ��������״̬ */
#define AMHW_I2C_MASTER_STATE_MASK     (0x7 << 1)  /**< \brief I2C ����״̬���� */
#define AMHW_I2C_STAT_MSTIDLE          (0x0 << 1)  /**< \brief I2C ��������״̬ */
#define AMHW_I2C_STAT_MSTRX            (0x1 << 1)  /**< \brief I2C �������վ���״̬  */
#define AMHW_I2C_STAT_MSTTX            (0x2 << 1)  /**< \brief I2C �������;���״̬  */
#define AMHW_I2C_STAT_MSTNACKADDR      (0x3 << 1)  /**< \brief I2C ������ַ����Ӧ    */
#define AMHW_I2C_STAT_MSTNACKTX        (0x4 << 1)  /**< \brief I2C ������������Ӧ    */
#define AMHW_I2C_STAT_MSTARBLOSS       (0x1 << 4)  /**< \brief I2C �����ٲ�ʧ��      */
#define AMHW_I2C_STAT_MSTSSERR         (0x1 << 6)  /**< \brief I2C ��������/ֹͣ���� */
                                       
#define AMHW_I2C_STAT_SLVPEND          (0x1 << 8)  /**< \brief I2C �ӻ�����״̬ */
#define AMHW_I2C_SLAVE_STATE_MASK      (0x3 << 9)  /**< \brief I2C �ӻ�״̬���� */
#define AMHW_I2C_STAT_SLVADDR          (0x0 << 9)  /**< \brief I2C �ӻ���ַ     */
#define AMHW_I2C_STAT_SLVRX            (0x1 << 9)  /**< \brief I2C �ӻ����վ���״̬ */
#define AMHW_I2C_STAT_SLVTX            (0x2 << 9)  /**< \brief I2C �ӻ����;���״̬ */
#define AMHW_I2C_STAT_SLVNOTSTR        (0x1 << 11) /**< \brief I2C �ӻ�������I2C����ʱ�� */
#define AMHW_I2C_STAT_SLVSEL           (0x1 << 14) /**< \brief I2C �ӻ�ѡ��     */
#define AMHW_I2C_STAT_SLVDESEL         (0x1 << 15) /**< \brief I2C �ӻ���ѡ��   */
                                       
#define AMHW_I2C_STAT_EVTIMEOUT        (0x1 << 24) /**< \brief I2C �¼���ʱ    */
#define AMHW_I2C_STAT_SCLTIMEOUT       (0x1 << 25) /**< \brief I2C ʱ�ӳ�ʱ    */

/** @} */


/**
 * \name I2C �ж�ʹ�ܼĴ�������λ��ϸ����
 * @{
 */

#define AMHW_I2C_INTENSET_MSTPEND      (0x1 << 0)  /**< \brief I2C ���������ж�ʹ��          */
#define AMHW_I2C_INTENSET_MSTARBLOSS   (0x1 << 4)  /**< \brief I2C �����ٲ�ʧ���ж�ʹ��      */
#define AMHW_I2C_INTENSET_MSTSSERR     (0x1 << 6)  /**< \brief I2C ��������/ֹͣ�����ж�ʹ�� */
                                       
#define AMHW_I2C_INTENSET_SLVPEND      (0x1 << 8)  /**< \brief I2C �ӻ������ж�ʹ��       */
#define AMHW_I2C_INTENSET_SLVNOTSTR    (0x1 << 11) /**< \brief I2C �ӻ�����������ʱ��ʹ�� */
#define AMHW_I2C_INTENSET_SLVDESEL     (0x1 << 15) /**< \brief I2C �ӻ���ѡ���ж�ʹ��     */
                                       
#define AMHW_I2C_INTENSET_MONRX        (0x1 << 8)  /**< \brief I2C ���ģʽ���վ����ж�ʹ�� */
#define AMHW_I2C_INTENSET_MONOVEN      (0x1 << 11) /**< \brief I2C ��س����ж�ʹ��         */
#define AMHW_I2C_INTENSET_MONIDLE      (0x1 << 15) /**< \brief I2C ���ģʽ�����ж�ʹ��     */
                                       
#define AMHW_I2C_INTENSET_EVTIMEOUT    (0x1 << 24) /**< \brief I2C �¼���ʱ�ж�ʹ�� */
#define AMHW_I2C_INTENSET_SCLTIMEOUT   (0x1 << 25) /**< \brief I2C ʱ�ӳ�ʱ�ж�ʹ�� */

/** @} */


/**
 * \name I2C �жϽ��ܼĴ�������λ��ϸ����
 * @{
 */

#define AMHW_I2C_INTENCLR_MSTPEND      (0x1 << 0)  /**< \brief I2C ���������жϽ���          */
#define AMHW_I2C_INTENCLR_MSTARBLOSS   (0x1 << 4)  /**< \brief I2C �����ٲ�ʧ���жϽ���      */
#define AMHW_I2C_INTENCLR_MSTSSERR     (0x1 << 6)  /**< \brief I2C ��������/ֹͣ�����жϽ��� */
                                                   
#define AMHW_I2C_INTENCLR_SLVPEND      (0x1 << 8)  /**< \brief I2C �ӻ������жϽ���       */
#define AMHW_I2C_INTENCLR_SLVNOTSTR    (0x1 << 11) /**< \brief I2C �ӻ�����������ʱ�ӽ��� */
#define AMHW_I2C_INTENCLR_SLVDESEL     (0x1 << 15) /**< \brief I2C �ӻ���ѡ���жϽ���     */
                                                   
#define AMHW_I2C_INTENCLR_MONRX        (0x1 << 8)  /**< \brief I2C ���ģʽ���վ����жϽ��� */
#define AMHW_I2C_INTENCLR_MONOVEN      (0x1 << 11) /**< \brief I2C ��س����жϽ���         */
#define AMHW_I2C_INTENCLR_MONIDLE      (0x1 << 15) /**< \brief I2C ���ģʽ�����жϽ���     */
                                                   
#define AMHW_I2C_INTENCLR_EVTIMEOUT    (0x1 << 24) /**< \brief I2C �¼���ʱ�жϽ��� */
#define AMHW_I2C_INTENCLR_SCLTIMEOUT   (0x1 << 25) /**< \brief I2C ʱ�ӳ�ʱ�жϽ��� */

/** @} */


/**
 * \name I2C �������ƼĴ���λ����
 * @{
 */
 
#define AMHW_I2C_CTL_MSTCONTINUE       (1 << 0)  /**< \brief I2C ������������Ӧ������λ */ 
#define AMHW_I2C_CTL_MSTSTART          (1 << 1)  /**< \brief I2C ������������λ */
#define AMHW_I2C_CTL_MSTSTOP           (1 << 2)  /**< \brief I2C ����ֹͣ����λ */
#define AMHW_I2C_CTL_MSTDMA            (1 << 3)  /**< \brief I2C ����DMA����λ  */

/** @} */


/**
 * \name I2C �ӻ����ƼĴ���λ����
 * @{
 */ 

#define AMHW_I2C_CTL_SLVCONTINUE       (1 << 0)  /**< \brief I2C �ӻ���������Ӧ������λ */
#define AMHW_I2C_CTL_SLVNACK           (1 << 1)  /**< \brief I2C �ӻ�����Ӧ����λ */
#define AMHW_I2C_CTL_SLVDMA            (1 << 3)  /**< \brief I2C �ӻ�DMA����λ    */

/** @} */

/**
 * \anchor I2C_mode
 * \brief I2Cģʽ���壨�ο�I2C CFG�Ĵ����� 
 */
typedef enum amhw_i2c_mode {
    AM_I2C_MASTER_MODE    = (1 << 0),  /**< \brief ����ģʽʹ��  */
    AM_I2C_SLAVE_MODE     = (1 << 1),  /**< \brief �ӻ�ģʽʹ�� */
    AM_I2C_MONITOR_MODE   = (1 << 2),  /**< \brief ���ģʽʹ�� */
    AM_I2C_TIMEOUT_MODE   = (1 << 3),  /**< \brief ��ʱʹ�� */
    AM_I2C_MONCLKSTR_MODE = (1 << 4),  /**< \brief ���ģʽʱ������ʹ�� */
} amhw_i2c_mode_t;

/**
 * \brief I2C д���ݵ��������ݼĴ���
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] value    : д���������ݼĴ���������
 *
 * \return  ��
 */
am_static_inline 
void amhw_i2c_mstdat_write (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->mstdat = value;  
}

/**
 * \brief I2C ��ȡ���ݴ��������ݼĴ���
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  �������ݼĴ�����ֵ
 */
am_static_inline 
uint32_t amhw_i2c_mstdat_read (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->mstdat);  
}

/**
 * \brief д���ݵ��ӻ����ݼĴ���
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] value    : д��ӻ����ݼĴ���������
 *
 * \return  ��
 */
am_static_inline 
void amhw_i2c_slvdat_write (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->slvdat =  value;  
}

/**
 * \brief I2C ��ȡ���ݴӴӻ����ݼĴ���
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  �ӻ����ݼĴ�����ֵ
 */
am_static_inline 
uint32_t amhw_i2c_slvdat_read (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->slvdat);  
}

/**
 * \brief ��ȡʱ�ӷ�Ƶ�Ĵ���
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  ʱ�ӷ�Ƶ�Ĵ�����ֵ
 */
am_static_inline 
uint32_t amhw_i2c_clkdiv_get (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->clkdiv);
}

/**
 * \brief �趨ʱ�ӷ�Ƶ����
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] div      : ʱ�ӷ�Ƶ����
 *
 * \return  ��
 */
am_static_inline 
void amhw_i2c_clkdiv_set (amhw_i2c_t *p_hw_i2c, uint32_t div)
{
    uint32_t clkdiv;
    
    if((div >= 1) && (div <= 65535)) {
        clkdiv = div - 1;
    } else {
        clkdiv = 0;
    }
    
    p_hw_i2c->clkdiv = clkdiv;
}


/**
 * \brief �趨MSTTIME��SCL�ߵ�ƽ��SCL�ĵ�ƽʱ�䣩
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] value    : �趨ʱ�����
 *
 * \return  ��
 */
am_static_inline 
void amhw_i2c_msttime_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->msttime = value;
}

/**
 * \brief ��ȡ��ǰ�ж�״̬�ĺ���
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  �ж�״̬�Ĵ�����ֵ 
 */
am_static_inline 
uint32_t amhw_i2c_intstat_get (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->intstat);
}

/**
 * \brief ��ȡ��ǰI2C״̬�ĺ���
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  ״̬�Ĵ�����ֵ
 */
am_static_inline 
uint32_t amhw_i2c_stat_get (amhw_i2c_t *p_hw_i2c)
{
    return (p_hw_i2c->stat);
}
/**
 * \brief �趨I2C״̬�ĺ���
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] value    : �趨��״̬λAMHW_I2C_STAT_* ��ֵ���� 
 *                       AMHW_I2C_STAT_*��� ��OR��ֵ(#AMHW_I2C_STAT_MSTPEND)
 *
 * \return  ��
 */
am_static_inline 
void amhw_i2c_stat_set (amhw_i2c_t *p_hw_i2c, uint32_t value)
{
    p_hw_i2c->stat = value;
}
/**
 * \brief I2C �ж�ʹ��
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2C_INTENSET_* ��ֵ���� 
 *                       AMHW_I2C_INTENSET_*��� ��OR��ֵ(#AMHW_I2C_INTENSET_MSTPEND) 
 *
 * \return  None
 */
am_static_inline 
void amhw_i2c_int_enable (amhw_i2c_t *p_hw_i2c, uint32_t flags)
{
    p_hw_i2c->intenset = flags;
}

/**
 * \brief I2C �жϽ���
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] flags    : AMHW_I2C_INTENCLR_*��ֵ���� 
 *                       AMHW_I2C_INTENCLR_*��� ��OR��ֵ(#AMHW_I2C_INTENCLR_MSTPEND) 
 *
 * \return  None
 */
am_static_inline 
void amhw_i2c_int_disable (amhw_i2c_t *p_hw_i2c, uint32_t flags)
{
    p_hw_i2c->intenclr = flags;
}
/**
 * \brief I2C �����������ƺ���
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  ��
 */
am_static_inline 
void amhw_i2c_mst_start (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->mstctl = AMHW_I2C_CTL_MSTSTART;  
}

/**
 * \brief I2C ��������������������ӦACK��
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return    ��
 */
am_static_inline 
void amhw_i2c_mst_continue (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->mstctl = AMHW_I2C_CTL_MSTCONTINUE;  
}
/**
 * \brief  I2C ����ֹͣ���ƺ���
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  ��
 */
am_static_inline 
void amhw_i2c_mst_stop (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->mstctl = AMHW_I2C_CTL_MSTSTOP;
}

/**
 * \brief I2C �ӻ�������������ӦACK��
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \return  ��
 */
am_static_inline 
void amhw_i2c_slv_continue (amhw_i2c_t *p_hw_i2c)
{
    p_hw_i2c->slvctl = AMHW_I2C_CTL_SLVCONTINUE;
}

/**
 * \brief  ʹ���趨��I2Cģʽ
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] mode     : ��Ҫʹ�ܵ�I2C ģʽ,�ο� \ref I2C_mode "I2C ģʽ����"
 *
 * \return    ��
 */
am_static_inline 
void amhw_i2c_mode_enable (amhw_i2c_t *p_hw_i2c, uint32_t mode)
{
    p_hw_i2c->cfg |= mode;
}


/**
 * \brief  �����趨��I2Cģʽ
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] mode     : ��Ҫ���ܵ�I2C ģʽ,�ο� \ref I2C_mode "I2C ģʽ����"
 *
 * \return    ��
 */
am_static_inline 
void amhw_i2c_mode_disable (amhw_i2c_t *p_hw_i2c, uint32_t mode)
{
    p_hw_i2c->cfg &= ~mode;
}


/**
 * \brief �趨�ӻ���ַ0
 *
 * \param[in] p_hw_i2c : ָ��I2C�Ĵ������ָ��
 * \param[in] sla_addr : �ӻ���ַ
 *
 * \return    ��
 */
am_static_inline 
void amhw_i2c_slvadr0_set (amhw_i2c_t *p_hw_i2c, uint32_t sla_addr)
{
    p_hw_i2c->slvadr0 = sla_addr;
}


/** 
 * @} amhw_if_i2c 
 */

#ifdef __cplusplus
}
#endif

#endif /* __AMHW_I2C_H */


/* end of file */

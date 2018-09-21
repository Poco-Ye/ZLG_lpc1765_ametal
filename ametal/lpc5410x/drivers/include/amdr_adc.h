/*******************************************************************************
*                                Apollo
*                      ----------------------------
*                      innovating embedded platform
*
*Copyright (c) 2001-2014 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
*All rights reserved.
*
*Contact information:
*web site:    http://www.zlg.cn/
*e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief ADC����������ADC��׼�ӿ�
 *
 * \internal
 * \par Modification History
 * - 1.01 15-01-15  hbt, delete device name in amh_adc_dev.
 * - 1.00 15-01-10  asd, first implementation.
 * \endinternal
 */
 
#ifndef  __AMDR_ADC_H
#define  __AMDR_ADC_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include "am_types.h"
#include "am_adc.h"
#include "amhw_adc.h"

/**
 * \addtogroup amdr_if_adc
 * \copydoc amdr_adc.h
 * @{
 */


/**
 * \brief ADC �豸��Ϣ 
 */
typedef struct amdr_adc_devinfo {
    
    /** \brief ָ��ADC�Ĵ������ָ�� */
    amhw_adc_t *p_hw_adc;
    
    /** \brief ADC�жϺ����� */
    uint8_t    *intnums;

    /** \brief ADC�жϺ����� */
    uint8_t     intcnts;

    /** \brief ADC�������� */
    uint8_t     bits;

    /** 
     * \brief ADC�ο���ѹ����λ��mV 
     *
     * ���� LPC5410x, �ο���ѹ Vref = (Vrefp - Vrefn)  Ϊ��������������ʱ
     * �ȶ�����ADC��ȷ����VREFP = VDDA Vrefn ����ֵΪ�� Vss �� Vssa ��
     * 
     * \note �òο���ѹ�ɾ���ĵ�·���� 
     *
     */
    uint32_t    vref;
    
    /** \brief ADC����ʱ�ӷ�Ƶ */
    uint32_t    clk_div;

} amdr_adc_devinfo_t;

/**
 * \brief ADC�豸ʵ�� 
 */
typedef struct amdr_adc_dev {
    
    /** \brief ADC��׼���� */
    am_adc_serv_t             adc_serve;

    /** \brief ָ��ADC�豸��Ϣ��ָ�� */
    const amdr_adc_devinfo_t *p_devinfo;
    
    /** \brief ����û�����ת����Ļص����� */
    void (*pfn_convert_cb) (void *p_arg, uint32_t actual_cnt);
        
    /** \brief �û������ص������Ļص��������� */
    void                    *p_arg;
    
    /** \brief ��ǰת��ͨ���Ļ�����          */
    uint32_t                *p_val;
    
    /** \brief ��ǰת����ͨ�� */
    uint32_t                 chan;
    
} amdr_adc_dev_t;

/**
 * \brief ADC��ʼ�� 
 *
 * Ĭ�ϳ�ʼ������A 
 *
 * \param[in] p_dev     : ָ��ADC�豸��ָ�� 
 * \param[in] p_devinfo : ָ��ADC�豸��Ϣ��ָ�� 
 *
 * \return ADC��׼���������� ���Ϊ NULL��������ʼ��ʧ�� 
 */
am_adc_handle_t amdr_adc_init(amdr_adc_dev_t           *p_dev, 
                              const amdr_adc_devinfo_t *p_devinfo);

/**
 * \brief ADCȥ��ʼ�� 
 *
 * Ĭ��ȥ��ʼ������A 
 *
 * \param[in] p_dev : ָ��ADC�豸��ָ�� 
 *
 * \return �� 
 */
void amdr_adc_deinit(amdr_adc_dev_t *p_dev);                              
                              
/**
 * @} 
 */

#ifdef __cplusplus
}
#endif

#endif /*__AMDR_ADC_H  */

/* end of file */

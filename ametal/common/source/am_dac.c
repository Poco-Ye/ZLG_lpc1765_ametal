/*******************************************************************************
*                                 Apollo
*                       ----------------------------
*                       innovating embedded platform
*
* Copyright (c) 2001-2012 Guangzhou ZHIYUAN Electronics Stock Co., Ltd.
* All rights reserved.
*
* Contact information:
* web site:    http://www.zlg.cn/
* e-mail:      apollo.support@zlg.cn
*******************************************************************************/

/**
 * \file
 * \brief UART implementation
 * 
 * \internal
 * \par Modification history
 * - 1.00 15-04-27  tee, first implementation.
 * \endinternal
 */
#include "am_dac.h"


/*******************************************************************************
  public functions
*******************************************************************************/

/**
 * \brief ����DACͨ���ĵ�ѹֵ����λ��mV��
 *
 * \param[in] handle : DAC��׼����������
 * \param[in] chan   : DACͨ����
 *
 * \retval   AW_OK      �����ɹ�
 * \retval  -AW_ENXIO   DACͨ���Ų�����
 */
int am_dac_mv_set (am_dac_handle_t handle, int chan, uint32_t mv)
{
    uint32_t bits = am_dac_bits_get(handle);
    uint32_t vref = am_dac_vref_get(handle);
    
    
    return am_dac_val_set(handle,chan, mv * (1 << bits) / vref);
}

/* end of file */

/*******************************************************************************
*                                 Apollo
*                       ---------------------------
*                       innovating embedded systems
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
 * \brief RTC��ʾ���̣�ͨ����׼�ӿ�ʵ��
 *
 * - ʵ������:
 *  1. ���ڴ�ӡ��ǰʱ����Ϣ, ���磺 "Thu Jan 22 14:18:58 2015"
 *
 * \par Դ����
 * \snippet demo_std_rtc.c src_std_rtc 
 * 
 * \internal
 * \par Modification history
 * - 1.00 14-12-04  tee, first implementation.
 * \endinternal
 */ 
 
/**
 * \addtogroup demo_if_std_rtc
 * \copydoc demo_std_rtc.c
 */

/** [src_std_rtc] */
#include "ametal.h"
#include "am_board.h"
#include <time.h>

/* ��ǰ��ʱ��������ã����� : 2015/1/22 14:17:23 */
struct am_tm now_time = {
    23,           /*  23�� */
    17,           /*  17�� */
    14,           /*  14ʱ */
    22,           /*  22�� */
    1 - 1,        /*   1�� */
    2015 - 1900,  /*2015�� */
};

/**
 * \brief ������
 */
int main(void)
{
    uint32_t          time_sec = 0;
    am_rtc_handle_t   handle   = NULL;
    char time_str[30];

    /* �༶��ʼ��  */
    am_board_init();
    
    AM_DBG_INFO("The demo RTC for standard service\r\n");
    
    /* RTC ƽ̨��ʼ��*/
    amhw_plfm_rtc_init();
    
    handle = amdr_rtc_init(&g_rtc_dev, &g_rtc_devinfo);

    /* �趨��ǰʱ�� */
    am_rtc_time_set(handle, &now_time);
 
    /* Sleep and do all the work in the RTC interrupt handler */
    while (1) {

        /* ͨ��RTC����ȡ��ǰʱ����Ϣ����λ���� */
        am_rtc_time_get(handle, &now_time);
 
        /* ���������ʱ����Ϣת�����ַ�����ʽ */
        asctime_r((struct tm*)&now_time, time_str);
        
        AM_DBG_INFO("%s", time_str);
        am_mdelay(1000);
    }
}

/** [src_std_rtc] */

/* end of file */

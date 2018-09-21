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
 * \brief LPC5410X DMA 通道编号定义 
 *
 * \internal
 * \par Modification History
 * - 1.00 15-01-06  hbt, first implementation.
 * \endinternal
 */

#ifndef __LPC5410X_DMA_CHAN_H
#define __LPC5410X_DMA_CHAN_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \addtogroup amhw_if_dma_chan
 * \copydoc lpc5410x_dma_chan.h
 * @{
 */

    
/**
 * \name LPC5410X DMA 通道编号
 * @{
 */

#define DMA_CHAN_0                0               /**< \brief DMA通道0  */
#define DMA_CHAN_1                1               /**< \brief DMA通道1  */
#define DMA_CHAN_2                2               /**< \brief DMA通道2  */
#define DMA_CHAN_3                3               /**< \brief DMA通道3  */
#define DMA_CHAN_4                4               /**< \brief DMA通道4  */
#define DMA_CHAN_5                5               /**< \brief DMA通道5  */
#define DMA_CHAN_6                6               /**< \brief DMA通道6  */
#define DMA_CHAN_7                7               /**< \brief DMA通道7  */
#define DMA_CHAN_8                8               /**< \brief DMA通道8  */
#define DMA_CHAN_9                9               /**< \brief DMA通道9  */
#define DMA_CHAN_10               10              /**< \brief DMA通道10 */
#define DMA_CHAN_11               11              /**< \brief DMA通道11 */
#define DMA_CHAN_12               12              /**< \brief DMA通道12 */
#define DMA_CHAN_13               13              /**< \brief DMA通道13 */
#define DMA_CHAN_14               14              /**< \brief DMA通道14 */
#define DMA_CHAN_15               15              /**< \brief DMA通道15 */
#define DMA_CHAN_16               16              /**< \brief DMA通道16 */
#define DMA_CHAN_17               17              /**< \brief DMA通道17 */
#define DMA_CHAN_18               18              /**< \brief DMA通道18 */
#define DMA_CHAN_19               19              /**< \brief DMA通道19 */
#define DMA_CHAN_20               20              /**< \brief DMA通道20 */
#define DMA_CHAN_21               21              /**< \brief DMA通道21 */

/** @} */


/**
 * \name 外设的DMA请求对应的DMA通道
 * @{
 */

#define DMA_CHAN_USART0_RX_REQ    DMA_CHAN_0      /**< \brief UART0 RX 请求   */
#define DMA_CHAN_USART0_TX_REQ    DMA_CHAN_1      /**< \brief UART0 TX 请求   */
#define DMA_CHAN_USART1_RX_REQ    DMA_CHAN_2      /**< \brief UART1 RX 请求   */
#define DMA_CHAN_USART1_TX_REQ    DMA_CHAN_3      /**< \brief UART1 TX 请求   */
#define DMA_CHAN_USART2_RX_REQ    DMA_CHAN_4      /**< \brief UART2 RX 请求   */
#define DMA_CHAN_USART2_TX_REQ    DMA_CHAN_5      /**< \brief UART2 TX 请求   */
#define DMA_CHAN_USART3_RX_REQ    DMA_CHAN_6      /**< \brief UART3 RX 请求   */
#define DMA_CHAN_USART3_TX_REQ    DMA_CHAN_7      /**< \brief UART3 TX 请求   */
#define DMA_CHAN_SPI0_RX_REQ      DMA_CHAN_8      /**< \brief SPI0 RX 请求    */
#define DMA_CHAN_SPI0_TX_REQ      DMA_CHAN_9      /**< \brief SPI0 TX 请求    */
#define DMA_CHAN_SPI1_RX_REQ      DMA_CHAN_10     /**< \brief SPI1 RX 请求    */
#define DMA_CHAN_SPI1_TX_REQ      DMA_CHAN_11     /**< \brief SPI1 TX 请求    */
#define DMA_CHAN_I2C0_SLV_REQ     DMA_CHAN_12     /**< \brief I2C0 从机请求   */
#define DMA_CHAN_I2C0_MST_REQ     DMA_CHAN_13     /**< \brief I2C0 主机请求   */
#define DMA_CHAN_I2C1_SLV_REQ     DMA_CHAN_14     /**< \brief I2C1 从机请求   */
#define DMA_CHAN_I2C1_MST_REQ     DMA_CHAN_15     /**< \brief I2C1 主机请求   */
#define DMA_CHAN_I2C2_SLV_REQ     DMA_CHAN_16     /**< \brief I2C2 从机请求   */
#define DMA_CHAN_I2C2_MST_REQ     DMA_CHAN_17     /**< \brief I2C2 主机请求   */
#define DMA_CHAN_I2C0_MNT_REQ     DMA_CHAN_18     /**< \brief I2C0 监控器请求 */
#define DMA_CHAN_I2C1_MNT_REQ     DMA_CHAN_19     /**< \brief I2C1 监控器求   */
#define DMA_CHAN_I2C2_MNT_REQ     DMA_CHAN_20     /**< \brief I2C2 监控器请求 */
#define DMA_CHAN_NO_REQ           DMA_CHAN_21     /**< \brief 无DMA请求       */

/** @} */


/**
 * @} amhw_if_dma_chan
 */

#ifdef __cplusplus
}
#endif


#endif /* __LPC5410X_DMA_CHAN_H */

/* end of file */

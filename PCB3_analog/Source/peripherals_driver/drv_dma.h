/*
 * drv_dma.h
 *
 *  Created on: Aug 18, 2023
 *      Author: icepe
 */

#ifndef DRV_DMA_H_
#define DRV_DMA_H_

#include "stdint.h"
#include "stm32g030xx.h"

#ifndef DMA_PERIPH_TO_MEMORY
#define DMA_PERIPH_TO_MEMORY         0x00000000U    /*!< Peripheral to memory direction */
#endif

#ifndef DMA_MEMORY_TO_PERIPH
#define DMA_MEMORY_TO_PERIPH         DMA_CCR_DIR  /*!< Memory to peripheral direction */
#endif

#ifndef DMA_MEMORY_TO_MEMORY
#define DMA_MEMORY_TO_MEMORY         DMA_CCR_MEM2MEM  /*!< Memory to memory direction     */
#endif

#ifndef DMA_PDATAALIGN_BYTE
#define DMA_PDATAALIGN_BYTE          0x00000000U             /*!< Peripheral data alignment : Byte     */
#endif

#ifndef	DMA_PDATAALIGN_HALFWORD
#define DMA_PDATAALIGN_HALFWORD      DMA_CCR_PSIZE_0         /*!< Peripheral data alignment : HalfWord */
#endif

#ifndef	DMA_PDATAALIGN_WORD
#define DMA_PDATAALIGN_WORD          DMA_CCR_PSIZE_1             /*!< Peripheral data alignment : Word     */
#endif


#ifndef DMA_MDATAALIGN_BYTE
#define DMA_MDATAALIGN_BYTE          0x00000000U             /*!< Peripheral data alignment : Byte     */
#endif

#ifndef	DMA_MDATAALIGN_HALFWORD
#define DMA_MDATAALIGN_HALFWORD      DMA_CCR_MSIZE_0         /*!< Peripheral data alignment : HalfWord */
#endif

#ifndef	DMA_MDATAALIGN_WORD
#define DMA_MDATAALIGN_WORD          DMA_CCR_MSIZE_1             /*!< Peripheral data alignment : Word     */
#endif





void dma_init(DMA_Channel_TypeDef *DMA_channelx,DMAMUX_Channel_TypeDef *DMAMUX_channelx,uint32_t Direction , uint32_t PeriphDataAlignment,
									uint32_t MemDataAlignment, uint32_t dmamux);
void dma_config(DMA_Channel_TypeDef *DMA_channelx, uint32_t Direction,uint32_t srcAdd, uint32_t destAdd, uint16_t datasize);
#endif /* DRV_DMA_H_ */

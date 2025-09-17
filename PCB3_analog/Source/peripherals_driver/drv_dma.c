/*
 * drv_dma.c
 *
 *  Created on: Aug 18, 2023
 *      Author: icepe
 */

#include "drv_dma.h"
#include "stm32g030xx.h"

void dma_init(DMA_Channel_TypeDef *DMA_channelx, DMAMUX_Channel_TypeDef *DMAMUX_channelx, uint32_t Direction, uint32_t PeriphDataAlignment,
		uint32_t MemDataAlignment, uint32_t dmamux) {
	//Enable clock
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	//enable interrupt
	DMA_channelx->CCR |= (DMA_CCR_TCIE | DMA_CCR_TEIE);
	//set data direction
	//read form peripheral
	DMA_channelx->CCR &= ~DMA_CCR_DIR;
	DMA_channelx->CCR |= Direction;
	//enable CIRC mode
	DMA_channelx->CCR &= ~DMA_CCR_CIRC;
	//enable memory increment
	DMA_channelx->CCR |= DMA_CCR_MINC;
	//DMA_channelx->CCR &= ~DMA_CCR_MINC;
	//set peripheral data size //8bit
	DMA_channelx->CCR &= ~DMA_CCR_PSIZE;	//00
	DMA_channelx->CCR |= PeriphDataAlignment;
	//set peripheral memmory size //8bit
	DMA_channelx->CCR &= ~DMA_CCR_MSIZE;	//00
	DMA_channelx->CCR |= MemDataAlignment;
	//Set the Priority Level LOW
	DMA_channelx->CCR &= ~DMA_CCR_PL; // 00

	//DMAMUX1_Channel0->CCR &= ~DMAMUX_CxCR_DMAREQ_ID;
	DMAMUX_channelx->CCR |= dmamux;

}

void dma_deInit(DMA_Channel_TypeDef *DMA_channelx) {

}

void dma_config(DMA_Channel_TypeDef *DMA_channelx, uint32_t Direction,uint32_t srcAdd, uint32_t destAdd, uint16_t datasize) {
	//Set the data size in CNDTR Register
	DMA_channelx->CNDTR = datasize;

	if (DMA_MEMORY_TO_PERIPH == Direction) {
		//Set the  peripheral address in PAR Register
		DMA_channelx->CPAR = destAdd;
		//Set the  Memory address in MAR Register
		DMA_channelx->CMAR = srcAdd;
	}
	/* Peripheral to Memory */
	else{
		//Set the  peripheral address in PAR Register
		DMA_channelx->CPAR = srcAdd;
		//Set the  Memory address in MAR Register
		DMA_channelx->CMAR = destAdd;
	}

	//enable DMA
	DMA_channelx->CCR |= DMA_CCR_EN;
}

void dma_stop(DMA_Channel_TypeDef *DMA_channelx) {
}
/*

void DMA_Channel1_IRQHandler(void) {
	//half tran
	if (((DMA1->ISR) & DMA_ISR_HTIF1) == DMA_ISR_HTIF1) {
		DMA1->IFCR |= DMA_IFCR_CHTIF1;
	}
	//full
	if (((DMA1->ISR) & DMA_ISR_TCIF1) == DMA_ISR_TCIF1) {
		DMA1->IFCR |= DMA_IFCR_CGIF1;
	}
}
*/




/*
 * drv_spi.c
 *
 *  Created on: Apr 3, 2023
 *      Author: icepe
 */
#include "drv_spi.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_spi.h"
#include "stm32g0xx_ll_gpio.h"



void SPI1_init()
{
  LL_SPI_InitTypeDef SPI_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
  LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
  /**SPI1 GPIO Configuration
  PA5   ------> SPI1_SCK
  PA6   ------> SPI1_MISO
  PA7   ------> SPI1_MOSI
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* SPI1 interrupt Init */
#if 0
  NVIC_SetPriority(SPI1_IRQn, 1);
  NVIC_EnableIRQ(SPI1_IRQn);
#endif

  /* SPI1 parameter configuration*/
  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;//LL_SPI_POLARITY_HIGH;
  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;//LL_SPI_PHASE_2EDGE;
  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV8;
  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
  SPI_InitStruct.CRCPoly = 7;
  LL_SPI_Init(SPI1, &SPI_InitStruct);
 // LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
  //LL_SPI_DisableNSSPulseMgt(SPI1);
//active SPI
  LL_SPI_Enable(SPI1);

}

uint8_t SPI1_readWrite(uint8_t TxData){
	uint8_t ret  = 0;
	while(!(SPI1->SR & SPI_SR_TXE));
	*((__IO uint8_t *)&SPI1->DR) = TxData;
	while(!((SPI1->SR) & SPI_SR_RXNE));
	ret =  (uint8_t)SPI1->DR;
	return ret;
}

#if 0
void SPI1_WriteByte(uint8_t TxData) {
	LL_SPI_TransmitData8(SPI1, TxData);
	LL_SPI_ReceiveData8(SPI1);
}

uint8_t SPI1_ReadByte() {
	LL_SPI_TransmitData8(SPI1, 0xff);
	return LL_SPI_ReceiveData8(SPI1);
}
#else
void SPI1_WriteByte(uint8_t TxData) {
	SPI1_readWrite(TxData);
}

uint8_t SPI1_ReadByte() {
	return SPI1_readWrite(0xff);
}
#endif

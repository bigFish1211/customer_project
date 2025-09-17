/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    Examples_LL/SPI/SPI_TwoBoards_FullDuplex_IT_Master_Init/Src/stm32g0xx_it.c
  * @author  MCD Application Team
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2019-2020 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_it.h"
#include "uart.h"
#include <stdint.h>

extern volatile uint32_t u32MiliCount;
extern volatile uint32_t u32SecCount;

static uint32_t u32tickCount = 0;;
void NMI_Handler(void)
{
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{

  while (1)
  {
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void) {
	u32tickCount++;
	u32MiliCount++;
	if (u32tickCount >= 1000) {
		u32tickCount = 0;
		u32SecCount++;
	}
}

void USART1_IRQHandler(void) {
	USART1_callback();
}

void USART2_IRQHandler(void) {
	USART2_callback();
}

void LPUART1_IRQHandler(void) {
	LPUART1_callback();
}

void DMA1_Channel1_IRQHandler(void) {
}
void DMA1_Channel2_3_IRQHandler(void) {

}

void DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5_IRQHandler(void) {
	USART1_TX_callback();
	USART2_TX_callback();
	LPUART1_TX_callback();
}


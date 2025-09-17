/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    Examples_LL/SPI/SPI_TwoBoards_FullDuplex_IT_Master_Init/Inc/stm32g0xx_it.h
  * @author  MCD Application Team
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32G0xx_IT_H
#define __STM32G0xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void EXTI4_15_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_USART4_USART5_USART6_LPUART1_IRQHandler(void);
void LPUART1_IRQHandler(void);
void DMA1_Channel1_IRQHandler(void);
void DMA1_Channel2_3_IRQHandler(void);
void DMA1_Channel4_5_6_7_DMAMUX_DMA2_Channel1_2_3_4_5_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32G0xx_IT_H */

/*
 * platform.c
 *
 *  Created on: Mar 6, 2025
 *      Author: thangnq
 */

#include "platform.h"
#include <stdint.h>

uint8_t log_buf[1024] ={0};

#define INIT_RELAY(n)                         \
do {                                          \
    GPIO_InitStruct.Pin = RELAY##n##_pin;     \
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT; \
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW; \
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL; \
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;   \
    LL_GPIO_Init(RELAY##n##_GPIO_port, &GPIO_InitStruct); \
} while(0)


void pin_init() {

	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);

#ifdef LED_MCU_pin
	GPIO_InitStruct.Pin = LED_MCU_pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(LED_MCU_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RS485_DIR_pin
	GPIO_InitStruct.Pin = RS485_DIR_pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(RS485_DIR_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef SW01_pin
	  GPIO_InitStruct.Pin = SW01_pin;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(SW01_pin_GPIO_port, &GPIO_InitStruct);
#endif
	RS485_RE();
}


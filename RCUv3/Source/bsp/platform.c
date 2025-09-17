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
} while(0);

#define ON_RELAY(n)                         \
do {                                          \
	RELAY##n##_ON();\
} while(0);


void pin_init() {

	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOC);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOD);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOF);
#if 0
	//INIT_RELAY(1);
	for (int i = 1; i < 16; i++) {
		INIT_RELAY(i);
	}
#else

#ifdef RELAY1_pin
    GPIO_InitStruct.Pin = RELAY1_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY1_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY2_pin
    GPIO_InitStruct.Pin = RELAY2_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY2_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY3_pin
    GPIO_InitStruct.Pin = RELAY3_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY3_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY4_pin
    GPIO_InitStruct.Pin = RELAY4_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY4_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY5_pin
    GPIO_InitStruct.Pin = RELAY5_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY5_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY6_pin
    GPIO_InitStruct.Pin = RELAY6_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY6_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY7_pin
    GPIO_InitStruct.Pin = RELAY7_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY7_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY8_pin
    GPIO_InitStruct.Pin = RELAY8_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY8_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY9_pin
    GPIO_InitStruct.Pin = RELAY9_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY9_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY10_pin
    GPIO_InitStruct.Pin = RELAY10_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY10_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY11_pin
    GPIO_InitStruct.Pin = RELAY11_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY11_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY12_pin
    GPIO_InitStruct.Pin = RELAY12_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY12_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY13_pin
    GPIO_InitStruct.Pin = RELAY13_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY13_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY14_pin
    GPIO_InitStruct.Pin = RELAY14_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY14_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef RELAY15_pin
    GPIO_InitStruct.Pin = RELAY15_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(RELAY15_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef W5500_SPI_CS_pin
    GPIO_InitStruct.Pin = W5500_SPI_CS_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(W5500_SPI_CS_GPIO_port, &GPIO_InitStruct);
#endif

#ifdef W5500_RESET_pin
    GPIO_InitStruct.Pin = W5500_RESET_pin;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(W5500_RESET_GPIO_port, &GPIO_InitStruct);
#endif

#endif
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
	RS485_RE();
	//RS485_DE();
//	for(int i =1;i<16;i++){
//		ON_RELAY(1);
//	}
#if 0
	RELAY1_ON();
	RELAY2_ON();
	RELAY3_ON();
	RELAY4_ON();
	RELAY5_ON();
	RELAY6_ON();
	RELAY7_ON();
	RELAY8_ON();
	RELAY9_ON();
	RELAY10_ON();
	RELAY11_ON();
	RELAY12_ON();
	RELAY13_ON();
	RELAY14_ON();
	RELAY15_ON();
#else
	RELAY1_OFF();
	RELAY2_OFF();
	RELAY3_OFF();
	RELAY4_OFF();
	RELAY5_OFF();
	RELAY6_OFF();
	RELAY7_OFF();
	RELAY8_OFF();
	RELAY9_OFF();
	RELAY10_OFF();
	RELAY11_OFF();
	RELAY12_OFF();
	RELAY13_OFF();
	RELAY14_OFF();
	RELAY15_OFF();
#endif
	W5500_RESET_OFF();
}


/*
 * platform.h
 *
 *  Created on: Mar 6, 2025
 *      Author: thangnq
 */

#ifndef USER_LIB_PLATFORM_H_
#define USER_LIB_PLATFORM_H_

#include <string.h>
#include "LL_API.h"
#include "uart.h"
#include "drv_spi.h"
#include "drv_i2c.h"


#define LED_MCU_pin 				LL_GPIO_PIN_8
#define LED_MCU_GPIO_port 			GPIOA

#define RS485_DIR_pin 				LL_GPIO_PIN_6
#define RS485_DIR_GPIO_port 		GPIOC

#define SW01_pin 					LL_GPIO_PIN_8
#define SW01_pin_GPIO_port 			GPIOB

#ifdef LED_MCU_pin
#define LED_MCU_ON()					LL_GPIO_ResetOutputPin(LED_MCU_GPIO_port, LED_MCU_pin)
#define LED_MCU_OFF()					LL_GPIO_SetOutputPin(LED_MCU_GPIO_port, LED_MCU_pin)
#else
#define LED_MCU_ON()
#define LED_MCU_OFF()
#endif

#ifdef RS485_DIR_pin
#define RS485_DE()						LL_GPIO_SetOutputPin(RS485_DIR_GPIO_port, RS485_DIR_pin)
#define RS485_RE()						LL_GPIO_ResetOutputPin(RS485_DIR_GPIO_port, RS485_DIR_pin)
#else
#define RS485_DE()
#define RS485_RE()
#endif


#ifdef SW01_pin
#define SW01_STT()						!LL_GPIO_IsInputPinSet(SW01_pin_GPIO_port, SW01_pin)
#else
#define SW01_pin()
#endif

#define COM_TRANS_TIMEOUT				1000//ms


#define COM_DEBUG_init(baudrate) 			USART2_setup(baudrate)
#define COM_DEBUG_putchar(c) 				USART2_putchar(c)
#define COM_DEBUG_trans(str,len)			USART2_TX_transmit(str,len,COM_TRANS_TIMEOUT)

#define COM_RS485_init(baudrate) 			USART1_setup(baudrate)
#define COM_RS485_putchar(c) 				USART1_putchar(c)
#define COM_RS485_trans(str,len)			USART1_TX_transmit(str,len,COM_TRANS_TIMEOUT)

#define  MCP4278_i2c_init()					I2C2_Init()
#define  ADS1115_i2c_init()					I2C2_Init()

#define COM_LOG							COM_DEBUG_trans
#define ENABLE_CONSOLE_LOG				1

extern uint8_t log_buf[1024];

#if ENABLE_CONSOLE_LOG
#define PRINTF(...) do\
                       {\
                            sprintf(log_buf,##__VA_ARGS__);\
                            COM_LOG(log_buf,strlen(log_buf));\
                        }\
                    while(0);
#define LOG  PRINTF

#define LOG_LINE()  PRINTF("%s\t%d\r\n",__func__,__LINE__)

#else
#define LOG  PRINTF
#define LOG(...) (void)0
#define LOG_LINE()
#endif

void pin_init();
char NMEAChecksum(char *data, int len) ;
void write_config(void);
void load_config(void);


#endif /* USER_LIB_PLATFORM_H_ */

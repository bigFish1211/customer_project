/*
 * platform.h
 *
 *  Created on: Mar 6, 2025
 *      Author: thangnq
 */

#ifndef USER_LIB_PLATFORM_H_
#define USER_LIB_PLATFORM_H_

#include <string.h>
#include "config.h"
#include "LL_API.h"
#include "uart.h"
#include "drv_spi.h"
#include "drv_i2c.h"


#if 1
#define RELAY1_pin 				LL_GPIO_PIN_15
#define RELAY1_GPIO_port 			GPIOA

#define RELAY2_pin 				LL_GPIO_PIN_6
#define RELAY2_GPIO_port 			GPIOD

#define RELAY3_pin 				LL_GPIO_PIN_3
#define RELAY3_GPIO_port 			GPIOB

#define RELAY4_pin 				LL_GPIO_PIN_4
#define RELAY4_GPIO_port 			GPIOB

#define RELAY5_pin 				LL_GPIO_PIN_5
#define RELAY5_GPIO_port 			GPIOB

#define RELAY6_pin 				LL_GPIO_PIN_8
#define RELAY6_GPIO_port 			GPIOB

#define RELAY7_pin 				LL_GPIO_PIN_9
#define RELAY7_GPIO_port 			GPIOB

#define RELAY8_pin 				LL_GPIO_PIN_10
#define RELAY8_GPIO_port 			GPIOC

#define RELAY9_pin 				LL_GPIO_PIN_5
#define RELAY9_GPIO_port 			GPIOD

#define RELAY10_pin 				LL_GPIO_PIN_4
#define RELAY10_GPIO_port 			GPIOD

#define RELAY11_pin 				LL_GPIO_PIN_3
#define RELAY11_GPIO_port 			GPIOD

#define RELAY12_pin 				LL_GPIO_PIN_2
#define RELAY12_GPIO_port 			GPIOD

#define RELAY13_pin 				LL_GPIO_PIN_1
#define RELAY13_GPIO_port 			GPIOD

#define RELAY14_pin 				LL_GPIO_PIN_0
#define RELAY14_GPIO_port 			GPIOD

#define RELAY15_pin 				LL_GPIO_PIN_9
#define RELAY15_GPIO_port 			GPIOC

#define LED_MCU_pin 				LL_GPIO_PIN_4
#define LED_MCU_GPIO_port 			GPIOA

#endif

#define W5500_SPI_CS_pin 			LL_GPIO_PIN_4
#define W5500_SPI_CS_GPIO_port 		GPIOA

#define W5500_RESET_pin 			LL_GPIO_PIN_2
#define W5500_RESET_GPIO_port 		GPIOA

#define RS485_DIR_pin 				LL_GPIO_PIN_9
#define RS485_DIR_GPIO_port 		GPIOD


#ifdef RELAY1_pin
#define RELAY1_ON()					LL_GPIO_ResetOutputPin(RELAY1_GPIO_port, RELAY1_pin)
#define RELAY1_OFF()				LL_GPIO_SetOutputPin(RELAY1_GPIO_port, RELAY1_pin)
#else
#define RELAY1_ON()
#define RELAY1_OFF()
#endif

#ifdef RELAY2_pin
#define RELAY2_ON()					LL_GPIO_ResetOutputPin(RELAY2_GPIO_port, RELAY2_pin)
#define RELAY2_OFF()					LL_GPIO_SetOutputPin(RELAY2_GPIO_port, RELAY2_pin)
#else
#define RELAY2_ON()
#define RELAY2_OFF()
#endif

#ifdef RELAY3_pin
#define RELAY3_ON()					LL_GPIO_ResetOutputPin(RELAY3_GPIO_port, RELAY3_pin)
#define RELAY3_OFF()					LL_GPIO_SetOutputPin(RELAY3_GPIO_port, RELAY3_pin)
#else
#define RELAY3_ON()
#define RELAY3_OFF()
#endif

#ifdef RELAY4_pin
#define RELAY4_ON()					LL_GPIO_ResetOutputPin(RELAY4_GPIO_port, RELAY4_pin)
#define RELAY4_OFF()					LL_GPIO_SetOutputPin(RELAY4_GPIO_port, RELAY4_pin)
#else
#define RELAY4_ON()
#define RELAY4_OFF()
#endif

#ifdef RELAY5_pin
#define RELAY5_ON()					LL_GPIO_ResetOutputPin(RELAY5_GPIO_port, RELAY5_pin)
#define RELAY5_OFF()					LL_GPIO_SetOutputPin(RELAY5_GPIO_port, RELAY5_pin)
#else
#define RELAY5_ON()
#define RELAY5_OFF()
#endif

#ifdef RELAY6_pin
#define RELAY6_ON()					LL_GPIO_ResetOutputPin(RELAY6_GPIO_port, RELAY6_pin)
#define RELAY6_OFF()					LL_GPIO_SetOutputPin(RELAY6_GPIO_port, RELAY6_pin)
#else
#define RELAY6_ON()
#define RELAY6_OFF()
#endif

#ifdef RELAY7_pin
#define RELAY7_ON()					LL_GPIO_ResetOutputPin(RELAY7_GPIO_port, RELAY7_pin)
#define RELAY7_OFF()					LL_GPIO_SetOutputPin(RELAY7_GPIO_port, RELAY7_pin)
#else
#define RELAY7_ON()
#define RELAY7_OFF()
#endif

#ifdef RELAY8_pin
#define RELAY8_ON()					LL_GPIO_ResetOutputPin(RELAY8_GPIO_port, RELAY8_pin)
#define RELAY8_OFF()					LL_GPIO_SetOutputPin(RELAY8_GPIO_port, RELAY8_pin)
#else
#define RELAY8_ON()
#define RELAY8_OFF()
#endif

#ifdef RELAY9_pin
#define RELAY9_ON()					LL_GPIO_ResetOutputPin(RELAY9_GPIO_port, RELAY9_pin)
#define RELAY9_OFF()					LL_GPIO_SetOutputPin(RELAY9_GPIO_port, RELAY9_pin)
#else
#define RELAY9_ON()
#define RELAY9_OFF()
#endif


#ifdef RELAY10_pin
#define RELAY10_ON()					LL_GPIO_ResetOutputPin(RELAY10_GPIO_port, RELAY10_pin)
#define RELAY10_OFF()					LL_GPIO_SetOutputPin(RELAY10_GPIO_port, RELAY10_pin)
#else
#define RELAY10_ON()
#define RELAY10_OFF()
#endif

#ifdef RELAY11_pin
#define RELAY11_ON()					LL_GPIO_ResetOutputPin(RELAY11_GPIO_port, RELAY11_pin)
#define RELAY11_OFF()					LL_GPIO_SetOutputPin(RELAY11_GPIO_port, RELAY11_pin)
#else
#define RELAY11_ON()
#define RELAY11_OFF()
#endif

#ifdef RELAY12_pin
#define RELAY12_ON()					LL_GPIO_ResetOutputPin(RELAY12_GPIO_port, RELAY12_pin)
#define RELAY12_OFF()					LL_GPIO_SetOutputPin(RELAY12_GPIO_port, RELAY12_pin)
#else
#define RELAY12_ON()
#define RELAY12_OFF()
#endif

#ifdef RELAY13_pin
#define RELAY13_ON()					LL_GPIO_ResetOutputPin(RELAY13_GPIO_port, RELAY13_pin)
#define RELAY13_OFF()					LL_GPIO_SetOutputPin(RELAY13_GPIO_port, RELAY13_pin)
#else
#define RELAY13_ON()
#define RELAY13_OFF()
#endif

#ifdef RELAY14_pin
#define RELAY14_ON()					LL_GPIO_ResetOutputPin(RELAY14_GPIO_port, RELAY14_pin)
#define RELAY14_OFF()					LL_GPIO_SetOutputPin(RELAY14_GPIO_port, RELAY14_pin)
#else
#define RELAY14_ON()
#define RELAY14_OFF()
#endif

#ifdef RELAY15_pin
#define RELAY15_ON()					LL_GPIO_ResetOutputPin(RELAY15_GPIO_port, RELAY15_pin)
#define RELAY15_OFF()					LL_GPIO_SetOutputPin(RELAY15_GPIO_port, RELAY15_pin)
#else
#define RELAY15_ON()
#define RELAY15_OFF()
#endif

#ifdef LED_MCU_pin
#define LED_MCU_ON()					LL_GPIO_ResetOutputPin(LED_MCU_GPIO_port, LED_MCU_pin)
#define LED_MCU_OFF()					LL_GPIO_SetOutputPin(LED_MCU_GPIO_port, LED_MCU_pin)
#else
#define LED_MCU_ON()
#define LED_MCU_OFF()
#endif




#ifdef W5500_SPI_CS_pin
#define W5500_SPI_CS_SELECT()					LL_GPIO_ResetOutputPin(W5500_SPI_CS_GPIO_port, W5500_SPI_CS_pin)
#define W5500_SPI_CS_DESELECT()					LL_GPIO_SetOutputPin(W5500_SPI_CS_GPIO_port, W5500_SPI_CS_pin)
#else
#define W5500_SPI_CS_SELECT()
#define W5500_SPI_CS_DESELECT()
#endif

#ifdef W5500_RESET_pin
#define W5500_RESET_ON()						LL_GPIO_SetOutputPin(W5500_RESET_GPIO_port, W5500_RESET_pin)
#define W5500_RESET_OFF()						LL_GPIO_ResetOutputPin(W5500_RESET_GPIO_port, W5500_RESET_pin)
#else
#define W5500_RESET_ON()
#define W5500_RESET_OFF()
#endif

#ifdef RS485_DIR_pin
#define RS485_DE()								LL_GPIO_SetOutputPin(RS485_DIR_GPIO_port, RS485_DIR_pin)
#define RS485_RE()								LL_GPIO_ResetOutputPin(RS485_DIR_GPIO_port, RS485_DIR_pin)
#else
#define RS485_DE()
#define RS485_RE()
#endif

#define COM_TRANS_TIMEOUT				1000//ms

#if 0
#define COMX0_init(baudrate) 			USART1_setup(baudrate)
#define COM_BLE_init(baudrate) 			USART2_setup(baudrate)

#define COMX0_putchar(c) 				USART1_putchar(c)
#define COM_BLE_putchar(c) 				USART2_putchar(c)
#define COM_RFID_putchar(c) 			LPUART1_putchar(c)

#define COMX0_trans(str,len)			USART1_TX_transmit(str,len,COM_TRANS_TIMEOUT)
#define COM_BLE_trans(str,len)			USART2_TX_transmit(str,len,COM_TRANS_TIMEOUT)
#endif

#define COM_DEBUG_init(baudrate) 			USART3_setup(baudrate)
#define COM_DEBUG_putchar(c) 				USART3_putchar(c)
#define COM_DEBUG_trans(str,len)			USART3_TX_transmit(str,len,COM_TRANS_TIMEOUT)

#define COM_RS485_init(baudrate) 			USART1_setup(baudrate)
#define COM_RS485_putchar(c) 				USART1_putchar(c)
#define COM_RS485_trans(str,len)			USART1_TX_transmit(str,len,COM_TRANS_TIMEOUT)

#define W5500_SPI_int()						SPI1_init()
#define W5500_SPI_ReadByte					SPI1_ReadByte
#define W5500_SPI_WriteByte					SPI1_WriteByte

#define  PCA9555_i2c_init()					I2C1_Init()

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

#define PRINT_AUTHOR_INFO()  do\
								{\
	PRINTF("\r\n=== Firmware Info ===\r\n");\
	PRINTF("Author   : %s\r\n", AUTHOR);\
	PRINTF("Email    : %s\r\n", EMAIL);\
	PRINTF("Version  : %s\r\n", VERSION);\
	PRINTF("Build    : %s %s\r\n", BUILD_DATE, BUILD_TIME);\
	PRINTF("======================\r\n");\
								}\
							while(0);


void pin_init();
char NMEAChecksum(char *data, int len) ;
void write_config(void);
void load_config(void);


#endif /* USER_LIB_PLATFORM_H_ */

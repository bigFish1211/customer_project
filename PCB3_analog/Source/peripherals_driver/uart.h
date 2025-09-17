/*
 * uart.h
 *
 *  Created on: Mar 5, 2025
 *      Author: thangnq
 */

#ifndef USER_LIB_UART_H_
#define USER_LIB_UART_H_
#include <stdint.h>
void USART1_setup(uint32_t baudrate);
void USART3_setup(uint32_t baudrate);

void USART1_putchar(uint8_t c);
void USART3_putchar(uint8_t c);

void USART11_TX_transmit(uint8_t *str, uint16_t len, uint32_t timeout);
void USART3_TX_transmit(uint8_t *str, uint16_t len, uint32_t timeout);

void USART1_TX_callback(void);
void USART3_TX_callback(void);

void USART1_callback(void);
void USART3_callback(void);



#endif /* USER_LIB_UART_H_ */

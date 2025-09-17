/*
 * uart.c
 *
 *  Created on: Mar 5, 2025
 *      Author: thangnq
 */
#include "uart.h"
#include <string.h>
#include "LL_API.h"
#include "config.h"
//#include "handlerIOTask.h"

#define USART1_ENABLE_RX_DMA 		   	1
#define USART1_ENABLE_TX_DMA			0

#define USART3_ENABLE_RX_DMA 		    1
#define USART3_ENABLE_TX_DMA			0//1

#define LPUART1_ENABLE_RX_DMA 		   	0
#define LPUART1_ENABLE_TX_DMA			0


#define USE_TIMEOUT						1
//usart 1

#define USART1_TX_Pin 					LL_GPIO_PIN_9
#define USART1_TX_GPIO_Port 			GPIOA
#define USART1_TX_GPIO_AF 				LL_GPIO_AF_1
#define USART1_TX_GPIO_CLK    			LL_IOP_GRP1_PERIPH_GPIOA

#define USART1_RX_Pin 					LL_GPIO_PIN_10
#define USART1_RX_GPIO_Port 			GPIOA
#define USART1_RX_GPIO_AF 				LL_GPIO_AF_1
#define USART1_RX_GPIO_CLK    			LL_IOP_GRP1_PERIPH_GPIOA

#define USART1_CLK_ENABLE()				LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)
#define USART1_CLK_DISABLE()			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1)

#define USART1_IRQ						USART1_IRQn

#if	USART1_ENABLE_RX_DMA
#define USART1_RX_DMA    				DMA1
#define USART1_RX_DMA_CHANEL			LL_DMA_CHANNEL_1
#define USART1_RX_DMA_DMAMUX_REQ		LL_DMAMUX_REQ_USART1_RX
#endif
#if USART1_ENABLE_TX_DMA
#define USART1_TX_DMA    				DMA1
#define USART1_TX_DMA_CHANEL			LL_DMA_CHANNEL_4
#define USART1_TX_DMA_DMAMUX_REQ		LL_DMAMUX_REQ_USART1_TX
#endif

//usart 2

#define USART3_TX_Pin 					LL_GPIO_PIN_4
#define USART3_TX_GPIO_Port 			GPIOC
#define USART3_TX_GPIO_AF 				LL_GPIO_AF_0
#define USART3_TX_GPIO_CLK    			LL_IOP_GRP1_PERIPH_GPIOC

#define USART3_RX_Pin 					LL_GPIO_PIN_5
#define USART3_RX_GPIO_Port 			GPIOC
#define USART3_RX_GPIO_AF 				LL_GPIO_AF_0
#define USART3_RX_GPIO_CLK    			LL_IOP_GRP1_PERIPH_GPIOC

#define USART3_IRQ						USART3_IRQn

#define USART3_CLK_ENABLE()				LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3)
#define USART3_CLK_DISABLE()			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3)

#if	USART3_ENABLE_RX_DMA
#define USART3_RX_DMA    				DMA1
#define USART3_RX_DMA_CHANEL			LL_DMA_CHANNEL_2
#define USART3_RX_DMA_DMAMUX_REQ		LL_DMAMUX_REQ_USART3_RX
#endif

#if USART3_ENABLE_TX_DMA
#define USART3_TX_DMA    				DMA1
#define USART3_TX_DMA_CHANEL			LL_DMA_CHANNEL_5
#define USART3_TX_DMA_DMAMUX_REQ		LL_DMAMUX_REQ_USART3_TX
#endif

//lpuart
#define LPUART1_TX_Pin 					LL_GPIO_PIN_10
#define LPUART1_TX_GPIO_Port 			GPIOB
#define LPUART1_TX_GPIO_AF 				LL_GPIO_AF_1
#define LPUART1_TX_GPIO_CLK    			LL_IOP_GRP1_PERIPH_GPIOB

#define LPUART1_RX_Pin 					LL_GPIO_PIN_11
#define LPUART1_RX_GPIO_Port 			GPIOB
#define LPUART1_RX_GPIO_AF 				LL_GPIO_AF_1
#define LPUART1_RX_GPIO_CLK    			LL_IOP_GRP1_PERIPH_GPIOB


#define LPUART1_IRQ						LPUART1_IRQn

#define LPUART1_CLK_ENABLE()			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_LPUART1)
#define LPUART1_CLK_DISABLE()			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_LPUART1)

#if LPUART1_ENABLE_RX_DMA
#define LPUART1_RX_DMA    				DMA1
#define LPUART1_RX_DMA_CHANEL			LL_DMA_CHANNEL_3
#define LPUART1_RX_DMA_DMAMUX_REQ		LL_DMAMUX_REQ_LPUART1_RX
#endif

#if LPUART1_ENABLE_TX_DMA
#define LPUART1_TX_DMA    				DMA1
#define LPUART1_TX_DMA_CHANEL			LL_DMA_CHANNEL_6
#define LPUART1_TX_DMA_DMAMUX_REQ		LL_DMAMUX_REQ_LPUART1_TX
#endif

#if USART1_ENABLE_RX_DMA

#define USART1_RX_BUFFER_SIZE 			1024
uint8_t usart1_rxBuffer[USART1_RX_BUFFER_SIZE] = {0};

#endif

#if USART1_ENABLE_TX_DMA

#define USART1_TX_BUFFER_SIZE 			1024
uint8_t usart1_txBuffer[USART1_TX_BUFFER_SIZE] = {0};
static uint8_t usart1_transmit_busy = 0;
#endif

#if USART3_ENABLE_RX_DMA
#define USART3_RX_BUFFER_SIZE 			1024
uint8_t usart3_rxBuffer[USART3_RX_BUFFER_SIZE] = {0};
#endif

#if USART3_ENABLE_TX_DMA
#define USART3_TX_BUFFER_SIZE 			1024
uint8_t USART3_txBuffer[USART3_TX_BUFFER_SIZE] = {0};
static uint8_t USART3_transmit_busy = 0;
#endif

#if LPUART1_ENABLE_RX_DMA

#define LPUART1_RX_BUFFER_SIZE 					1024
uint8_t lpuart1_rxBuffer[LPUART1_RX_BUFFER_SIZE] = {0};

#endif

#if LPUART1_ENABLE_TX_DMA
#define LPUART1_TX_BUFFER_SIZE 					1024
uint8_t lpuart1_txBuffer[LPUART1_TX_BUFFER_SIZE] = {0};
static uint8_t lpuart1_transmit_busy = 0;
#endif


extern volatile uint32_t u32MiliCount;
extern volatile uint32_t u32SecCount;


extern char rfid_buff[256];
extern int buff_idx;
extern int rfid_idx;

extern int putcomdata(uint8_t *data, uint16_t len, uint8_t source);

static void USART1_deinit();
static void USART3_deinit();


static void USART1_GPIO_Init();
static void USART3_GPIO_Init();

static void DMA1_Channelx_DeInit(uint32_t Channel);

static void USARTx_Init(USART_TypeDef *USARTx,uint32_t baudrate);
static void USARTx_DMA_RX_Init(USART_TypeDef *USARTx,const DMA_TypeDef *DMAx, uint32_t Channel,  uint32_t Request,uint8_t* rx_bufer,uint16_t rx_bufer_size );
static void USARTx_DMA_TX_Init(USART_TypeDef *USARTx,const DMA_TypeDef *DMAx, uint32_t Channel,  uint32_t Request,uint8_t* tx_bufer,uint16_t tx_bufer_size );


void USART1_setup(uint32_t baudrate) {
	USART1_deinit();

	USART1_GPIO_Init();
	USART1_CLK_ENABLE();
	USARTx_Init(USART1, baudrate);

#if USART1_ENABLE_RX_DMA
	LL_USART_EnableIT_IDLE(USART1);
#else
	LL_USART_EnableIT_RXNE_RXFNE(USART1);
#endif
	LL_USART_EnableIT_ERROR(USART1); // Bật ngắt lỗi
	NVIC_SetPriority(USART1_IRQn, 1);
	NVIC_EnableIRQ(USART1_IRQn);

#if USART1_ENABLE_RX_DMA
	DMA1_Channelx_DeInit(USART1_RX_DMA_CHANEL);
	USARTx_DMA_RX_Init(USART1, USART1_RX_DMA, USART1_RX_DMA_CHANEL, USART1_RX_DMA_DMAMUX_REQ, usart1_rxBuffer, USART1_RX_BUFFER_SIZE);
#endif
#if USART1_ENABLE_TX_DMA
	DMA1_Channelx_DeInit(USART1_TX_DMA_CHANEL);
	NVIC_SetPriority(DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn, 1);
	NVIC_EnableIRQ(DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn);
	USARTx_DMA_TX_Init(USART1, USART1_TX_DMA, USART1_TX_DMA_CHANEL, USART1_TX_DMA_DMAMUX_REQ, usart1_txBuffer, USART1_TX_BUFFER_SIZE);
#endif

}

void USART3_setup(uint32_t baudrate) {
	USART3_deinit();

	USART3_GPIO_Init();
	USART3_CLK_ENABLE();
	USARTx_Init(USART3, baudrate);
#if USART3_ENABLE_RX_DMA
	LL_USART_EnableIT_IDLE(USART3);
#else
	LL_USART_EnableIT_RXNE_RXFNE(USART3);
#endif
	LL_USART_EnableIT_ERROR(USART3);
	NVIC_SetPriority(USART3_4_5_6_IRQn, 1);
	NVIC_EnableIRQ(USART3_4_5_6_IRQn);
#if USART3_ENABLE_RX_DMA
	DMA1_Channelx_DeInit(USART3_RX_DMA_CHANEL);
	USARTx_DMA_RX_Init(USART3, USART3_RX_DMA, USART3_RX_DMA_CHANEL, USART3_RX_DMA_DMAMUX_REQ, usart3_rxBuffer, USART3_RX_BUFFER_SIZE);
#endif
#if USART3_ENABLE_TX_DMA
	DMA1_Channelx_DeInit(USART3_TX_DMA_CHANEL);
	NVIC_SetPriority(DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn, 1);
	NVIC_EnableIRQ(DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQn);
	USARTx_DMA_TX_Init(USART3, USART3_TX_DMA, USART3_TX_DMA_CHANEL, USART3_TX_DMA_DMAMUX_REQ, USART3_txBuffer, USART3_TX_BUFFER_SIZE);
#endif
}

void USART1_deinit() {
	LL_USART_Disable(USART1);
	NVIC_DisableIRQ(USART1_IRQn);

	LL_APB2_GRP1_ForceReset(LL_APB2_GRP1_PERIPH_USART1);
	LL_APB2_GRP1_ReleaseReset(LL_APB2_GRP1_PERIPH_USART1);
	LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);

	LL_GPIO_ResetOutputPin(USART1_TX_GPIO_Port, USART1_TX_Pin); // TX
	LL_GPIO_ResetOutputPin(USART1_RX_GPIO_Port, USART1_RX_Pin); // RX
}
void USART3_deinit() {
	LL_USART_Disable(USART3);
	NVIC_DisableIRQ(USART3_4_5_6_IRQn);

	LL_APB1_GRP1_ForceReset(LL_APB1_GRP1_PERIPH_USART3);
	LL_APB1_GRP1_ReleaseReset(LL_APB1_GRP1_PERIPH_USART3);
	LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);

	LL_GPIO_ResetOutputPin(USART3_TX_GPIO_Port, USART3_TX_Pin); // TX
	LL_GPIO_ResetOutputPin(USART3_RX_GPIO_Port, USART3_RX_Pin); // RX
}


void USART1_putchar(uint8_t c){
	while ((USART1->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF);
	USART1->TDR = c;
}

void USART3_putchar(uint8_t c){
	while ((USART3->ISR & USART_ISR_TXE_TXFNF) != USART_ISR_TXE_TXFNF);
	USART3->TDR = c;
}


void USART1_TX_transmit(uint8_t *str, uint16_t len, uint32_t timeout) {

#if USART1_ENABLE_TX_DMA
#if USE_TIMEOUT
	uint32_t usart1_transmit_timestamp = u32MiliCount;
	while ((usart1_transmit_busy) && ((uint32_t) (u32MiliCount - usart1_transmit_timestamp) <= timeout)){

	}
#else
	while (usart1_transmit_busy);
#endif

		//if (!usart1_transmit_busy) {
		if ((!usart1_transmit_busy) ||((uint32_t)(u32MiliCount - usart1_transmit_busy) >= 1000)){
		uint16_t data_len = len > USART1_TX_BUFFER_SIZE ? USART1_TX_BUFFER_SIZE : len;
		memcpy(usart1_txBuffer, str, data_len);
		LL_DMA_DisableChannel(USART1_TX_DMA, USART1_TX_DMA_CHANEL);
		LL_DMA_SetMemoryAddress(USART1_TX_DMA, USART1_TX_DMA_CHANEL, (uint32_t) usart1_txBuffer);
		LL_DMA_SetDataLength(USART1_TX_DMA, USART1_TX_DMA_CHANEL, data_len);
		LL_USART_ClearFlag_TC(USART1);
		LL_DMA_EnableChannel(USART1_TX_DMA, USART1_TX_DMA_CHANEL);
		usart1_transmit_busy = u32MiliCount;
	}
#else
	for(int i =0;i< len;i++){
		USART1_putchar(*str);
				str++;
	}
#endif
}


void USART3_TX_transmit(uint8_t *str, uint16_t len, uint32_t timeout) {

#if USART3_ENABLE_TX_DMA
#if USE_TIMEOUT
	uint32_t USART3_transmit_timestamp = u32MiliCount;
	while ((USART3_transmit_busy) && ((uint32_t) (u32MiliCount - USART3_transmit_timestamp) <= timeout)) {
	}
#else
	while (USART3_transmit_busy);
#endif
	//if (!USART3_transmit_busy) {
	if ((!USART3_transmit_busy) ||((uint32_t)(u32MiliCount - USART3_transmit_busy) >= 1000)){
		uint16_t data_len = len > USART3_TX_BUFFER_SIZE ? USART3_TX_BUFFER_SIZE : len;
		memcpy(USART3_txBuffer, str, data_len);
		LL_DMA_DisableChannel(USART3_TX_DMA, USART3_TX_DMA_CHANEL);
		LL_DMA_SetMemoryAddress(USART3_TX_DMA, USART3_TX_DMA_CHANEL, (uint32_t) USART3_txBuffer);
		LL_DMA_SetDataLength(USART3_TX_DMA, USART3_TX_DMA_CHANEL, data_len);
		LL_USART_ClearFlag_TC(USART3);
		LL_DMA_EnableChannel(USART3_TX_DMA, USART3_TX_DMA_CHANEL);
		USART3_transmit_busy = 1;
	}
#else
	for(int i =0;i< len;i++){
		USART3_putchar(*str);
				str++;
	}
#endif
}


void LPUART1_TX_transmit(uint8_t *str, uint16_t len, uint32_t timeout) {
#if LPUART1_ENABLE_TX_DMA
#if USE_TIMEOUT
	uint32_t USART3_transmit_timestamp = u32MiliCount;
	while ((lpuart1_transmit_busy) && ((uint32_t) (u32MiliCount - lpuart1_transmit_timestamp) <= timeout)) {
	}
#else
	while (lpuart1_transmit_busy);
#endif
	if (!lpuart1_transmit_busy) {
		uint16_t data_len = len > LPUART1_TX_BUFFER_SIZE ? LPUART1_TX_BUFFER_SIZE : len;
		memcpy(lpuart1_txBuffer, str, data_len);
		LL_DMA_DisableChannel(USART3_TX_DMA, LPUART1_TX_DMA_CHANEL);
		LL_DMA_SetMemoryAddress(LPUART1_TX_DMA, LPUART1_TX_DMA_CHANEL, (uint32_t) lpuart1_txBuffer);
		LL_DMA_SetDataLength(LPUART1_TX_DMA, LPUART1_TX_DMA_CHANEL, data_len);
		LL_DMA_EnableChannel(LPUART1_TX_DMA, LPUART1_TX_DMA_CHANEL);
		lpuart1_transmit_busy = 1;
	}
#else
	for(int i =0;i< len;i++){
		LPUART1_putchar(*str);
				str++;
	}
#endif
}



void USART1_TX_callback(void) {
#if USART1_ENABLE_TX_DMA
	if (LL_DMA_IsActiveFlag_TC4(USART1_TX_DMA)) {
		LL_DMA_ClearFlag_TC4(USART1_TX_DMA);
		LL_DMA_DisableChannel(USART1_TX_DMA, USART1_TX_DMA_CHANEL);
		usart1_transmit_busy = 0;
	}
#endif
}

void USART3_TX_callback(void) {
#if USART3_ENABLE_TX_DMA
	if (LL_DMA_IsActiveFlag_TC5(USART3_TX_DMA)) {
		LL_DMA_ClearFlag_TC5(USART3_TX_DMA);
		LL_DMA_DisableChannel(USART3_TX_DMA, USART3_TX_DMA_CHANEL);
		USART3_transmit_busy = 0;
	}
#endif
}


void LPUART1_TX_callback(void) {
#if LPUART1_ENABLE_TX_DMA
	if (LL_DMA_IsActiveFlag_TC6(LPUART1_TX_DMA)) {
		LL_DMA_ClearFlag_TC6(LPUART1_TX_DMA);
		LL_DMA_DisableChannel(LPUART1_TX_DMA, LPUART1_TX_DMA_CHANEL);
		lpuart1_transmit_busy = 0;
	}
#endif
}

void USART1_callback(void) {
	uint8_t cChar = 0;
	if (LL_USART_IsActiveFlag_IDLE(USART1)) {

#if USART1_ENABLE_RX_DMA
		/* Disable and Re-enable DMA to reset the buffer */
		LL_DMA_DisableChannel(USART1_RX_DMA, USART1_RX_DMA_CHANEL);
		uint16_t remainingBytes = LL_DMA_GetDataLength(USART1_RX_DMA, USART1_RX_DMA_CHANEL);
		uint16_t receivedLength = USART1_RX_BUFFER_SIZE - remainingBytes;

		if (receivedLength > 0) {
			putcomdata(usart1_rxBuffer, receivedLength, source_485);
		}

		/* Process received data */
		/* Restart DMA */
		LL_DMA_SetDataLength(USART1_RX_DMA, USART1_RX_DMA_CHANEL, USART1_RX_BUFFER_SIZE);
		LL_DMA_EnableChannel(USART1_RX_DMA, USART1_RX_DMA_CHANEL);
#endif
		LL_USART_ClearFlag_IDLE(USART1);  // Clear flag
	}
	if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART1)) {
		cChar = USART1->RDR;
		USART1->ICR |= USART_RQR_RXFRQ;

	}
	//(ORE)
	if (LL_USART_IsActiveFlag_ORE(USART1)) {
		LL_USART_ClearFlag_ORE(USART1);
		cChar = LL_USART_ReceiveData8(USART1);
	}

	//Framing (FE)
	if (LL_USART_IsActiveFlag_FE(USART1)) {
		LL_USART_ClearFlag_FE(USART1);
		cChar = LL_USART_ReceiveData8(USART1);
	}

	//(NE)
	if (LL_USART_IsActiveFlag_NE(USART1)) {
		LL_USART_ClearFlag_NE(USART1);
		cChar = LL_USART_ReceiveData8(USART1);
	}

	//(PE)
	if (LL_USART_IsActiveFlag_PE(USART1)) {
		LL_USART_ClearFlag_PE(USART1);
		cChar = LL_USART_ReceiveData8(USART1);
	}

	if (LL_USART_IsActiveFlag_TXE(USART1)) {
		LL_USART_ClearFlag_TXFE(USART1);
	}
}

char ble_buf[256] ={0};
int ble_idx =0;

void USART3_callback(void) {
	uint8_t cChar = 0;
	if (LL_USART_IsActiveFlag_IDLE(USART3)) {

#if USART3_ENABLE_RX_DMA
		/* Disable and Re-enable DMA to reset the buffer */
		LL_DMA_DisableChannel(USART3_RX_DMA, USART3_RX_DMA_CHANEL);
		uint16_t remainingBytes = LL_DMA_GetDataLength(USART3_RX_DMA, USART3_RX_DMA_CHANEL);
		uint16_t receivedLength = USART3_RX_BUFFER_SIZE - remainingBytes;

		if (receivedLength > 0) {
			putcomdata(usart3_rxBuffer, receivedLength, source_debug);
		}

		LL_DMA_SetMemoryAddress(USART3_RX_DMA, USART3_RX_DMA_CHANEL, (uint32_t) usart3_rxBuffer);
		LL_DMA_SetDataLength(USART3_RX_DMA, USART3_RX_DMA_CHANEL, USART3_RX_BUFFER_SIZE);
		LL_DMA_EnableChannel(USART3_RX_DMA, USART3_RX_DMA_CHANEL);
#endif
		LL_USART_ClearFlag_IDLE(USART3);  // Clear flag
	}
	if (LL_USART_IsActiveFlag_RXNE_RXFNE(USART3)) {
		cChar = USART3->RDR;
		USART3->ICR |= USART_RQR_RXFRQ;
	}

	//(ORE)
	if (LL_USART_IsActiveFlag_ORE(USART3)) {
		LL_USART_ClearFlag_ORE(USART3);
		cChar = LL_USART_ReceiveData8(USART3);
	}

	//Framing (FE)
	if (LL_USART_IsActiveFlag_FE(USART3)) {
		LL_USART_ClearFlag_FE(USART3);
		cChar = LL_USART_ReceiveData8(USART3);
	}

	//(NE)
	if (LL_USART_IsActiveFlag_NE(USART3)) {
		LL_USART_ClearFlag_NE(USART3);
		cChar = LL_USART_ReceiveData8(USART3);
	}

	//(PE)
	if (LL_USART_IsActiveFlag_PE(USART3)) {
		LL_USART_ClearFlag_PE(USART3);
		cChar = LL_USART_ReceiveData8(USART3);
	}

	if (LL_USART_IsActiveFlag_TXE(USART3)) {
		LL_USART_ClearFlag_TXFE(USART3);

	}
}

static void USART1_GPIO_DeInit() {
	LL_GPIO_ResetOutputPin(USART1_TX_GPIO_Port, USART1_TX_Pin); // TX
	LL_GPIO_ResetOutputPin(USART1_RX_GPIO_Port, USART1_RX_Pin); // RX
}

static void USART3_GPIO_DeInit() {
	LL_GPIO_ResetOutputPin(USART3_TX_GPIO_Port, USART3_TX_Pin); // TX
	LL_GPIO_ResetOutputPin(USART3_RX_GPIO_Port, USART3_RX_Pin); // RX
}


static void USART1_GPIO_Init() {
	LL_IOP_GRP1_EnableClock(USART1_TX_GPIO_CLK);
	LL_IOP_GRP1_EnableClock(USART1_RX_GPIO_CLK);
	/*TX*/
	LL_GPIO_SetPinMode(USART1_TX_GPIO_Port, USART1_TX_Pin, LL_GPIO_MODE_ALTERNATE);
	if (USART1_TX_Pin < LL_GPIO_PIN_8)
		LL_GPIO_SetAFPin_0_7(USART1_TX_GPIO_Port, USART1_TX_Pin, USART1_TX_GPIO_AF);
	else
		LL_GPIO_SetAFPin_8_15(USART1_TX_GPIO_Port, USART1_TX_Pin, USART1_TX_GPIO_AF);
	LL_GPIO_SetPinSpeed(USART1_TX_GPIO_Port, USART1_TX_Pin, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(USART1_TX_GPIO_Port, USART1_TX_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(USART1_TX_GPIO_Port, USART1_TX_Pin, LL_GPIO_PULL_UP);
	/*RX*/
	LL_GPIO_SetPinMode(USART1_RX_GPIO_Port, USART1_RX_Pin, LL_GPIO_MODE_ALTERNATE);
	if (USART1_RX_Pin < LL_GPIO_PIN_8)
		LL_GPIO_SetAFPin_0_7(USART1_RX_GPIO_Port, USART1_RX_Pin, USART1_RX_GPIO_AF);
	else
		LL_GPIO_SetAFPin_8_15(USART1_RX_GPIO_Port, USART1_RX_Pin, USART1_RX_GPIO_AF);
	LL_GPIO_SetPinSpeed(USART1_RX_GPIO_Port, USART1_RX_Pin, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinPull(USART1_RX_GPIO_Port, USART1_RX_Pin, LL_GPIO_PULL_UP);

}



static void USART3_GPIO_Init() {
	LL_IOP_GRP1_EnableClock(USART3_TX_GPIO_CLK);
	LL_IOP_GRP1_EnableClock(USART3_RX_GPIO_CLK);
	/*TX*/
	LL_GPIO_SetPinMode(USART3_TX_GPIO_Port, USART3_TX_Pin, LL_GPIO_MODE_ALTERNATE);
	if (USART3_TX_Pin < LL_GPIO_PIN_8)
		LL_GPIO_SetAFPin_0_7(USART3_TX_GPIO_Port, USART3_TX_Pin, USART3_TX_GPIO_AF);
	else
		LL_GPIO_SetAFPin_8_15(USART3_TX_GPIO_Port, USART3_TX_Pin, USART3_TX_GPIO_AF);

	LL_GPIO_SetPinSpeed(USART3_TX_GPIO_Port, USART3_TX_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinOutputType(USART3_TX_GPIO_Port, USART3_TX_Pin, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(USART3_TX_GPIO_Port, USART3_TX_Pin, LL_GPIO_PULL_UP);
	/*RX*/
	LL_GPIO_SetPinMode(USART3_RX_GPIO_Port, USART3_RX_Pin, LL_GPIO_MODE_ALTERNATE);
	if (USART3_RX_Pin < LL_GPIO_PIN_8)
		LL_GPIO_SetAFPin_0_7(USART3_RX_GPIO_Port, USART3_RX_Pin, USART3_RX_GPIO_AF);
	else
		LL_GPIO_SetAFPin_8_15(USART3_RX_GPIO_Port, USART3_RX_Pin, USART3_RX_GPIO_AF);

	LL_GPIO_SetPinSpeed(USART3_RX_GPIO_Port, USART3_RX_Pin, LL_GPIO_SPEED_FREQ_LOW);
	LL_GPIO_SetPinPull(USART3_RX_GPIO_Port, USART3_RX_Pin, LL_GPIO_PULL_UP);
}


static void USARTx_Init(USART_TypeDef *USARTx,uint32_t baudrate) {
    LL_USART_SetBaudRate(USARTx, SystemCoreClock, LL_USART_PRESCALER_DIV1, LL_USART_OVERSAMPLING_16, baudrate);
    LL_USART_SetDataWidth(USARTx, LL_USART_DATAWIDTH_8B);
    LL_USART_SetStopBitsLength(USARTx, LL_USART_STOPBITS_1);
    LL_USART_SetParity(USARTx, LL_USART_PARITY_NONE);
    LL_USART_SetTransferDirection(USARTx, LL_USART_DIRECTION_TX_RX);
    LL_USART_SetHWFlowCtrl(USARTx, LL_USART_HWCONTROL_NONE);

	//LL_LPUART_DisableFIFO(USARTx);
    /* Enable USART */
    LL_USART_Enable(USARTx);
    while((!(LL_USART_IsActiveFlag_TEACK(USARTx))) || (!(LL_USART_IsActiveFlag_REACK(USARTx))))
     {
     }

}

static void USARTx_DMA_RX_Init(USART_TypeDef *USARTx,const DMA_TypeDef *DMAx, uint32_t Channel,  uint32_t Request,uint8_t* rx_bufer,uint16_t rx_bufer_size ) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

#if defined(DMA2)
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
#endif

    /* Configure DMA for USART3_RX */
    LL_DMA_ConfigTransfer(DMAx, Channel,
                          LL_DMA_DIRECTION_PERIPH_TO_MEMORY |
                          LL_DMA_MODE_CIRCULAR |
                          LL_DMA_PERIPH_NOINCREMENT |
                          LL_DMA_MEMORY_INCREMENT |
                          LL_DMA_PDATAALIGN_BYTE |
                          LL_DMA_MDATAALIGN_BYTE |
                          LL_DMA_PRIORITY_HIGH);

    /* Set Peripheral Address */
    LL_DMA_SetPeriphAddress(DMAx, Channel, (uint32_t)&USARTx->RDR);
    /* Set Memory Address */
    LL_DMA_SetMemoryAddress(DMAx, Channel, (uint32_t)rx_bufer);
    /* Set Number of Data to Transfer */
    LL_DMA_SetDataLength(DMAx, Channel, rx_bufer_size);
    LL_DMA_SetPeriphRequest(DMAx, Channel, Request);
	/* Enable USART DMA Reception */
	LL_USART_EnableDMAReq_RX(USARTx);
	/* Enable DMA Channel */
	LL_DMA_EnableChannel(DMAx, Channel);

}


static void USARTx_DMA_TX_Init(USART_TypeDef *USARTx,const DMA_TypeDef *DMAx, uint32_t Channel,  uint32_t Request,uint8_t* tx_bufer,uint16_t tx_bufer_size ) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

#if defined(DMA2)
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
#endif

    /* Configure DMA for USART3_RX */
    LL_DMA_ConfigTransfer(DMAx, Channel,
                          LL_DMA_DIRECTION_MEMORY_TO_PERIPH |
                          LL_DMA_MODE_NORMAL |
                          LL_DMA_PERIPH_NOINCREMENT |
                          LL_DMA_MEMORY_INCREMENT |
                          LL_DMA_PDATAALIGN_BYTE |
                          LL_DMA_MDATAALIGN_BYTE |
                          LL_DMA_PRIORITY_HIGH);

    /* Set Peripheral Address */
    LL_DMA_SetPeriphAddress(DMAx, Channel, (uint32_t)&USARTx->TDR);
    /* Set Memory Address */
    LL_DMA_SetMemoryAddress(DMAx, Channel, (uint32_t)tx_bufer);
    /* Set Number of Data to Transfer */
    LL_DMA_SetDataLength(DMAx, Channel, tx_bufer_size);
    LL_DMA_SetPeriphRequest(DMAx, Channel, Request);
	/* Enable USART DMA Reception */
	LL_USART_EnableDMAReq_TX(USARTx);
	 //Enable DMA Transfer Complete Interrupt (Optional)
	LL_DMA_EnableIT_TC(DMAx, Channel);
	/* Enable DMA Channel */
	LL_DMA_EnableChannel(DMAx, Channel);

}

static void DMA1_Channelx_DeInit(uint32_t Channel) {
	LL_DMA_DisableChannel(DMA1, Channel);
}

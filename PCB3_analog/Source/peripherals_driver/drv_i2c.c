/*
 * drv_i2c.c
 *
 *  Created on: Apr 11, 2025
 *      Author: thangnq
 */

#include "drv_i2c.h"
#include "platform.h"

#include "stm32g0xx_ll_i2c.h"
#include "stm32g0xx_ll_rcc.h"
#include "stm32g0xx_ll_bus.h"
#include "stm32g0xx_ll_system.h"
#include "stm32g0xx_ll_exti.h"
#include "stm32g0xx_ll_cortex.h"
#include "stm32g0xx_ll_utils.h"
#include "stm32g0xx_ll_pwr.h"
#include "stm32g0xx_ll_dma.h"
#include "stm32g0xx_ll_gpio.h"

#define  I2C2_INTERRUPT_en			0

#define  I2C2_SDA_pin				LL_GPIO_PIN_12
#define  I2C2_SDA_GPIO_port			GPIOA
#define  I2C2_SDA_AF				LL_GPIO_AF_6
#define  I2C2_SDA_CLK_en()			LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA)

#define  I2C2_SCL_pin				LL_GPIO_PIN_11
#define  I2C2_SCL_GPIO_port			GPIOA
#define  I2C2_SCL_AF				LL_GPIO_AF_6
#define  I2C2_SCL_CLK_en()			LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA)

void I2C2_Init()
{
  LL_I2C_InitTypeDef I2C_InitStruct = {0};
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
  //LL_RCC_SetI2CClockSource(LL_RCC_I2C2_CLKSOURCE_PCLK1);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C2);
  I2C2_SDA_CLK_en();
  I2C2_SCL_CLK_en();

  GPIO_InitStruct.Pin = I2C2_SDA_pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = I2C2_SDA_AF;
  LL_GPIO_Init(I2C2_SDA_GPIO_port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = I2C2_SCL_pin;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
  GPIO_InitStruct.Alternate = I2C2_SCL_AF;
  LL_GPIO_Init(I2C2_SCL_GPIO_port, &GPIO_InitStruct);

  I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
  I2C_InitStruct.Timing = 0x00F02B86;//0x00303D5B;
  I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_DISABLE;
  I2C_InitStruct.DigitalFilter = 0;
  I2C_InitStruct.OwnAddress1 = 0;
  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
  I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
  LL_I2C_Init(I2C2, &I2C_InitStruct);
  LL_I2C_EnableAutoEndMode(I2C2);
  LL_I2C_SetOwnAddress2(I2C2, 0, LL_I2C_OWNADDRESS2_NOMASK);
  LL_I2C_DisableOwnAddress2(I2C2);
  LL_I2C_DisableGeneralCall(I2C2);
  LL_I2C_EnableClockStretching(I2C2);

#if I2C2_INTERRUPT_en
  NVIC_SetPriority(I2C2_IRQn, 0);
  NVIC_EnableIRQ(I2C2_IRQn);

  LL_I2C_EnableIT_ADDR(I2C2);
  LL_I2C_EnableIT_NACK(I2C2);
  LL_I2C_EnableIT_ERR(I2C2);
  LL_I2C_EnableIT_STOP(I2C2);
#endif

}

void I2C2_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
	// Bắt đầu
	LL_I2C_HandleTransfer(I2C2, devAddr, LL_I2C_ADDRSLAVE_7BIT, 2, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

	while (!LL_I2C_IsActiveFlag_TXIS(I2C2))
		;  // Đợi gửi địa chỉ
	LL_I2C_TransmitData8(I2C2, regAddr);

	while (!LL_I2C_IsActiveFlag_TXIS(I2C2))
		;  // Đợi gửi data
	LL_I2C_TransmitData8(I2C2, data);

	while (!LL_I2C_IsActiveFlag_STOP(I2C2))
		;
	LL_I2C_ClearFlag_STOP(I2C2);
}

uint8_t I2C2_ReadByte(uint8_t devAddr, uint8_t regAddr) {
	uint8_t data;

	// Gửi địa chỉ để yêu cầu đọc
	LL_I2C_HandleTransfer(I2C2, devAddr, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);
	while (!LL_I2C_IsActiveFlag_TXIS(I2C2))
		;
	LL_I2C_TransmitData8(I2C2, regAddr);
	while (!LL_I2C_IsActiveFlag_TC(I2C2))
		;

	// Đọc lại dữ liệu
	LL_I2C_HandleTransfer(I2C2, devAddr, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);
	while (!LL_I2C_IsActiveFlag_RXNE(I2C2))
		;
	data = LL_I2C_ReceiveData8(I2C2);

	while (!LL_I2C_IsActiveFlag_STOP(I2C2))
		;
	LL_I2C_ClearFlag_STOP(I2C2);

	return data;
}


#if 0
void I2C2_WriteBuf(uint8_t devAddr, uint8_t *buffer,uint8_t size) {

    LL_I2C_HandleTransfer(I2C2, devAddr, LL_I2C_ADDRSLAVE_7BIT,
                          size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);

    for (uint8_t i = 0; i < size; i++) {
        while (!LL_I2C_IsActiveFlag_TXIS(I2C2));
        LL_I2C_TransmitData8(I2C2, buffer[i]);
    }

    while (!LL_I2C_IsActiveFlag_STOP(I2C2));
    LL_I2C_ClearFlag_STOP(I2C2);
}

#endif

void I2C2_WriteBuf(uint8_t devAddr, uint8_t *buffer,uint8_t size){
  LL_I2C_HandleTransfer(I2C2, devAddr, LL_I2C_ADDRSLAVE_7BIT, size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
  int i = size;
	while (!LL_I2C_IsActiveFlag_STOP(I2C2)&&i) {
			if (LL_I2C_IsActiveFlag_TXIS(I2C2)) {
				LL_I2C_TransmitData8(I2C2, *(buffer++));
				i--;
		}
	}
	  while (!LL_I2C_IsActiveFlag_STOP(I2C2));
  LL_I2C_ClearFlag_STOP(I2C2);
}


void I2C2_readBuf(uint8_t devAddr,uint8_t regAddr,uint8_t *buffer,uint8_t size){
	LL_I2C_HandleTransfer(I2C2, devAddr, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);
	while (!LL_I2C_IsActiveFlag_TXIS(I2C2));
	LL_I2C_TransmitData8(I2C2, regAddr);
	while (!LL_I2C_IsActiveFlag_TC(I2C2));

	// Đọc lại dữ liệu
	LL_I2C_HandleTransfer(I2C2, devAddr, LL_I2C_ADDRSLAVE_7BIT, size, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);
	while (!LL_I2C_IsActiveFlag_RXNE(I2C2));
	for (int i = 0; i < 2; i++) {
	        while (!LL_I2C_IsActiveFlag_RXNE(I2C1));
	        buffer[i] = LL_I2C_ReceiveData8(I2C1);
	    }
	while (!LL_I2C_IsActiveFlag_STOP(I2C2))
		;
	LL_I2C_ClearFlag_STOP(I2C2);
}

void I2C2_Scan() {
	uint8_t address;
	for (address = 1; address < 127; address++) {
		// Start + 7-bit address in write mode
		LL_I2C_HandleTransfer(I2C2, (address << 1),
		LL_I2C_ADDRESSING_MODE_7BIT, 1, // Transfer 1 byte (dummy)
				LL_I2C_MODE_SOFTEND,
				LL_I2C_GENERATE_START_WRITE);

		uint32_t timeout = 10000;
//		while (!LL_I2C_IsActiveFlag_STOP(I2C2)
//				&& !LL_I2C_IsActiveFlag_NACK(I2C2) && timeout--)
//			;
		while (!LL_I2C_IsActiveFlag_STOP(I2C2) && --timeout);
		if (LL_I2C_IsActiveFlag_NACK(I2C2)) {
			LL_I2C_ClearFlag_NACK(I2C2);
		} else {
			// Device found
			LOG("Found device at 0x%02X\r\n", address)
			;
		}

		// Wait for STOP and clear it
		if (LL_I2C_IsActiveFlag_STOP(I2C2)) {
			LL_I2C_ClearFlag_STOP(I2C2);
		}

		LL_mDelay(1); // Small delay between probes
	}
}

uint8_t I2C2_IsDeviceReady(uint8_t devAddr) {
    // Gửi start chỉ với địa chỉ (không gửi dữ liệu)
    LL_I2C_HandleTransfer(I2C2, devAddr << 1, LL_I2C_ADDRSLAVE_7BIT,
                          0, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);
    uint32_t timeout = 100;
    while (!LL_I2C_IsActiveFlag_STOP(I2C2)) {
        if (LL_I2C_IsActiveFlag_NACK(I2C2)) {
            LL_I2C_ClearFlag_NACK(I2C2);
            LL_I2C_GenerateStopCondition(I2C2);
            return 0;  // thiết bị không sẵn sàng
        }
        if (--timeout == 0) return 0;
    }

    LL_I2C_ClearFlag_STOP(I2C2);
    return 1;  // thiết bị sẵn sàng (ACK OK)
}


/*
 * drv_spi.h
 *
 *  Created on: Apr 3, 2023
 *      Author: icepe
 */

#ifndef INC_DRV_SPI_H_
#define INC_DRV_SPI_H_

#include <stdint.h>
#include "stm32g0xx.h"

void SPI1_init();
void SPI1_WriteByte(uint8_t TxData);
uint8_t SPI1_ReadByte();
#endif /* INC_DRV_SPI_H_ */

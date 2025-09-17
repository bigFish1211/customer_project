/*
 * drv_i2c.h
 *
 *  Created on: Apr 11, 2025
 *      Author: thangnq
 */

#ifndef USER_DRIVER_DRV_I2C_H_
#define USER_DRIVER_DRV_I2C_H_
#include <stdint.h>

void I2C1_Init();
void I2C1_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C1_ReadByte(uint8_t devAddr, uint8_t regAddr);
void I2C1_Scan();
void I2C1_Scan1();
void I2C1_WriteBuf(uint8_t devAddr, uint8_t *buffer,uint8_t size);
uint8_t I2C1_IsDeviceReady(uint8_t devAddr);

#endif /* USER_DRIVER_DRV_I2C_H_ */

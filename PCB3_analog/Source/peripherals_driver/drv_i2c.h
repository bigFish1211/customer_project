/*
 * drv_i2c.h
 *
 *  Created on: Apr 11, 2025
 *      Author: thangnq
 */

#ifndef USER_DRIVER_DRV_I2C_H_
#define USER_DRIVER_DRV_I2C_H_
#include <stdint.h>

void I2C2_Init();
void I2C2_WriteByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
uint8_t I2C_ReadByte(uint8_t devAddr, uint8_t regAddr);
void I2C2_Scan();
void I2C2_Scan1();
void I2C2_WriteBuf(uint8_t devAddr, uint8_t *buffer,uint8_t size);
void I2C2_readBuf(uint8_t devAddr,uint8_t regAddr, uint8_t *buffer,uint8_t size);
uint8_t I2C2_IsDeviceReady(uint8_t devAddr);

#endif /* USER_DRIVER_DRV_I2C_H_ */

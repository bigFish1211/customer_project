/*
 * ads1115.c
 *
 *  Created on: Sep 16, 2025
 *      Author: thannq
 */

#include "ads1115.h"
#include "drv_i2c.h"


#define ADS1115_I2C_ADDR   (0x48 << 1)  // Địa chỉ mặc định
#define ADS1115_REG_CONV   0x00
#define ADS1115_REG_CONFIG 0x01

void ADS1115_WriteReg(uint8_t reg, uint16_t value) {
	uint8_t data[3];
	data[0] = reg;
	data[1] = (value >> 8) & 0xFF;
	data[2] = value & 0xFF;
	I2C2_WriteBuf(ADS1115_I2C_ADDR, data, 3);
}

uint16_t ADS1115_ReadReg(uint8_t reg) {
	uint8_t data[2];
	uint16_t value;
	I2C2_readBuf(ADS1115_I2C_ADDR, reg, data, 2);
	value = (data[0] << 8) | data[1];
	return value;
}

int16_t ADS1115_ReadChannel(uint8_t channel)
{
    uint16_t config = 0x8000; // OS=1 (start single conversion)
    // MUX: chọn kênh
    switch (channel) {
        case 0: config |= 0x4000; break; // AIN0 vs GND
        case 1: config |= 0x5000; break; // AIN1 vs GND
        case 2: config |= 0x6000; break; // AIN2 vs GND
        case 3: config |= 0x7000; break; // AIN3 vs GND
    }
    config |= 0x0200; // PGA = ±4.096V (1 LSB = 125uV)
    config |= 0x0100; // Mode = single-shot
    config |= 0x0080; // Data rate = 128 SPS
    ADS1115_WriteReg(ADS1115_REG_CONFIG, config);
    // Đợi conversion (max 8ms ở 128SPS)
    LL_mDelay(10);
    return (int16_t)ADS1115_ReadReg(ADS1115_REG_CONV);
}

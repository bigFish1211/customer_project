/*
 * PCA9555.c
 *
 *  Created on: Sep 15, 2025
 *      Author: thannq
 */


#include "drv_i2c.h"
#include "stdint.h"
#include "PCA9555.h"
#include "platform.h"

#define PAC9555_IN_PORT0_REGISTER				0x00
#define PAC9555_IN_PORT1_REGISTER				0x01

#define PAC9555_OUT_PORT0_REGISTER				0x02
#define PAC9555_OUT_PORT1_REGISTER				0x03

#define PAC9555_POLARITY_PORT0_REGISTER			0x04
#define PAC9555_POLARITY_PORT1_REGISTER			0x05

#define PAC9555_CONFIG_PORT0_REGISTER			0x06
#define PAC9555_CONFIG_PORT1_REGISTER			0x07

void PCA9555_Write(uint8_t addr,uint8_t reg, uint8_t data)
{
    uint8_t buf[2] = {reg, data};
    I2C1_WriteBuf(addr, buf, 2);
}

uint8_t PCA9555_Read(uint8_t addr,uint8_t reg)
{
    uint8_t data;
    data = I2C1_ReadByte(addr,reg);
    return data;
}

void PCA9555_Init(uint8_t addr,uint8_t port0_dir,uint8_t port1_dir)
{
    PCA9555_Write(addr,PAC9555_CONFIG_PORT0_REGISTER, port0_dir);
    PCA9555_Write(addr,PAC9555_CONFIG_PORT1_REGISTER, port1_dir);
    //LOG("PCA9555 addr %x\r\n",addr);
    //LOG("PAC9555_CONFIG_PORT0_REGISTER :%x\r\n",PCA9555_Read(addr,PAC9555_CONFIG_PORT0_REGISTER));
    //LOG("PAC9555_CONFIG_PORT1_REGISTER :%x\r\n",PCA9555_Read(addr,PAC9555_CONFIG_PORT1_REGISTER));
}

void PCA9555_Init16(uint8_t addr,uint16_t port_dir)
{
    PCA9555_Write(addr,PAC9555_CONFIG_PORT0_REGISTER, (uint8_t)port_dir);
    PCA9555_Write(addr,PAC9555_CONFIG_PORT1_REGISTER, (uint8_t)(port_dir>>8));
   // LOG("PCA9555 addr %x\r\n",addr);
   // LOG("PAC9555_CONFIG_PORT0_REGISTER :%x\r\n",PCA9555_Read(addr,PAC9555_CONFIG_PORT0_REGISTER));
   // LOG("PAC9555_CONFIG_PORT1_REGISTER :%x\r\n",PCA9555_Read(addr,PAC9555_CONFIG_PORT1_REGISTER));
}
void PCA9555_WritePort0(uint8_t addr,uint8_t value)
{
    PCA9555_Write(addr,PAC9555_OUT_PORT0_REGISTER, value);
}

void PCA9555_WritePort1(uint8_t addr ,uint8_t value)
{
    PCA9555_Write(addr,PAC9555_OUT_PORT1_REGISTER, value);
}

void PCA9555_Write16(uint8_t addr ,uint16_t value)
{
    PCA9555_Write(addr,PAC9555_OUT_PORT0_REGISTER, (uint8_t)value);
    PCA9555_Write(addr,PAC9555_OUT_PORT1_REGISTER, (uint8_t)(value>>8));
}

uint8_t PCA9555_ReadPort0(uint8_t addr)
{
    return PCA9555_Read(addr,PAC9555_IN_PORT0_REGISTER);
}

uint8_t PCA9555_ReadPort1(uint8_t addr)
{
    return PCA9555_Read(addr,PAC9555_IN_PORT1_REGISTER);
}

uint16_t PCA9555_Read16(uint8_t addr){
	uint8_t data[2]={0};
	data[0] = PCA9555_Read(addr,PAC9555_IN_PORT0_REGISTER);
	data[1] =  PCA9555_Read(addr,PAC9555_IN_PORT1_REGISTER);
	uint16_t value = (data[0]|(uint16_t)data[1]<<8);
	return value;
}


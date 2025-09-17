/*
 * mcp4728.c
 *
 *  Created on: Sep 16, 2025
 *      Author: thannq
 */

#include "mcp4728.h"
#include "drv_i2c.h"

#define MCP4728_I2C_ADDR   (0x60 << 1)

#define MCP4728_MULTI_IR_CMD                                                   \
  0x40 ///< Command to write to the input register only
#define MCP4728_MULTI_EEPROM_CMD                                               \
  0x50 ///< Command to write to the input register and EEPROM
#define MCP4728_FAST_WRITE_CMD                                                 \
  0xC0 ///< Command to write all channels at once with

typedef enum pd_mode {
  MCP4728_PD_MODE_NORMAL, ///< Normal; the channel outputs the given value as
                          ///< normal.
  MCP4728_PD_MODE_GND_1K, ///< VOUT is loaded with 1 kΩ resistor to ground. Most
                          ///< of the channel circuits are powered off.
  MCP4728_PD_MODE_GND_100K, ///< VOUT is loaded with 100 kΩ resistor to ground.
                            ///< Most of the channel circuits are powered off.
  MCP4728_PD_MODE_GND_500K, ///< VOUT is loaded with 500 kΩ resistor to ground.
                            ///< Most of the channel circuits are powered off.
} MCP4728_pd_mode_t;

typedef enum gain {
  MCP4728_GAIN_1X,
  MCP4728_GAIN_2X,
} MCP4728_gain_t;

typedef enum vref {
  MCP4728_VREF_VDD,
  MCP4728_VREF_INTERNAL,
} MCP4728_vref_t;

#if 0
void MCP4728_WriteChannel(uint8_t channel, uint16_t value){
	uint8_t data[2];
	//uint32_t timeout;
    data[0] = (channel & 0x03) << 1 | ((value >> 8) & 0x0F); // CMD + D11..D8
    data[1] = value & 0xFF;                                  // D7..D0

	if (value > 4095) value = 4095;
	I2C2_WriteBuf(MCP4728_I2C_ADDR, data, 2);
}
#else
void MCP4728_WriteChannel(uint8_t channel, uint16_t value){
	uint8_t data[3];
	//uint32_t timeout;

	uint8_t sequential_write_cmd = MCP4728_MULTI_IR_CMD;
	sequential_write_cmd |= (channel << 1);
	data[0] = sequential_write_cmd;

	data[1] = value >> 8; // CMD + D11..D8
    data[2] = value & 0xFF;                                  // D7..D0

	if (value > 4095) value = 4095;
	I2C2_WriteBuf(MCP4728_I2C_ADDR, data, 3);
}
#endif

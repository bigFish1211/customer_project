/*
 * mcp4728.h
 *
 *  Created on: Sep 16, 2025
 *      Author: thannq
 */

#ifndef USER_LIB_MCP4728_H_
#define USER_LIB_MCP4728_H_
#include <stdint.h>

void MCP4728_WriteChannel(uint8_t channel, uint16_t value);
#endif /* USER_LIB_MCP4728_H_ */

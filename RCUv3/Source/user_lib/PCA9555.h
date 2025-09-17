/*
 * PCA9555.h
 *
 *  Created on: Sep 15, 2025
 *      Author: thannq
 */

#ifndef TASK_PCA9555_H_
#define TASK_PCA9555_H_
#include "stdint.h"

void PCA9555_Init16(uint8_t addr,uint16_t port_dir);
uint16_t PCA9555_Read16(uint8_t addr);
void PCA9555_Write16(uint8_t addr ,uint16_t value);

#endif /* TASK_PCA9555_H_ */

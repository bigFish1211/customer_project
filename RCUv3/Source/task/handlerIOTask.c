/*
 * handlerIOTask.c
 *
 *  Created on: Sep 16, 2025
 *      Author: thannq
 */

#include "handlerIOTask.h"
#include "config.h"
#include "queue.h"
#include "platform.h"
#include  "PCA9555.h"

const uint8_t PCA9555_addr[4]={0x40,0x42,0x4c,0x4e};
const uint16_t PCA9555_port_config[4] = { 0xa80e, 0x5555, 0x5555, 0x15 };

#define PCA9555_MAX_OUTPUT_PIN			27
#define PCA9555_MAX_INPUT_PIN			27
const uint8_t PCA9555_mask_out[32]={5,4,0,6,7,11,13,15,
								  17,19,21,23,25,27,29,31,
								  33,35,37,39,41,43,45,47,
								  49,51,53};

const uint8_t PCA9555_mask_int[32] ={1,2,3,10,9,8,12,14,
									16,18,20,22,24,26,28,30,
									32,34,36,38,40,42,44,46,
									48,50,52};

int putcomdata(uint8_t *data, uint16_t len, uint8_t source) {
	char *ptr = (char*) malloc(len);
	memcpy(ptr, data, len);
	RS232_DATA *msg = (RS232_DATA*) malloc(sizeof(RS232_DATA));
	msg->source = source;
	msg->len = len;
	msg->ptr_data = ptr;
	int result = queue_put(DP_RxQueue, msg);
	if (!result) {
		free(ptr);
		free(msg);
		return 0;
	}
	return 1;
}

int handler_comdata() {
	DataType_T ptr;
	RS232_DATA *comPtr;
	if (queue_get(DP_RxQueue, &ptr)) {
		comPtr = (RS232_DATA*) ptr;
		switch (comPtr->source) {
		case source_debug:
			COM_DEBUG_trans(comPtr->ptr_data, comPtr->len);
			break;
		case source_485:
			RS485_DE();
			COM_RS485_trans(comPtr->ptr_data, comPtr->len);
			RS485_RE();
			break;
		default:
			break;
		}

		free((char*) comPtr->ptr_data);
		free(comPtr);
	}
	return 1;
}

void RJ45_IO_setup(){

	for (int i = 0; i < 4; i++) {
		PCA9555_Init16(PCA9555_addr[i],PCA9555_port_config[i]);
	}
}

void RJ45_set_output(uint32_t value){
	uint16_t data[4] = { 0 };
	uint64_t u64data = 0;
	int i = 0;
	for (i = 0; i < PCA9555_MAX_OUTPUT_PIN; i++) {
		if ((value >> i) & 0x01) {
			u64data |= 1 << PCA9555_mask_out[i];
		}
	}

	data[0] = (uint16_t) (u64data);
	data[1] = (uint16_t) (u64data >> 16);
	data[2] = (uint16_t) (u64data >> 32);
	data[3] = (uint16_t) (u64data >> 48);

	for (i = 0; i < 4; i++) {
		 PCA9555_Write16(PCA9555_addr[i],data[i]);
	}
}


uint32_t RJ45_get_output(){
	uint32_t ret = 0;
	uint16_t data[4] = { 0 };
	int i=0;
	for (i = 0; i < 4; i++) {
		data[i] = PCA9555_Read16(PCA9555_addr[i]);
	}
	uint64_t value = data[0] | (data[1] << 16)| (data[2] << 32) | (data[3] << 48);
	for (i = 0; i < PCA9555_MAX_OUTPUT_PIN; i++) {
		if (value & PCA9555_mask_out[i]) {
			ret |= 1 << i;
		}
	}
	return ret;
}


uint32_t RJ45_get_input(){
	uint32_t ret = 0;
	uint16_t data[4] = { 0 };
	int i=0;
	for (i = 0; i < 4; i++) {
		data[i] = PCA9555_Read16(PCA9555_addr[i]);
	}
	uint64_t value = data[0] | data[1] << 16 | data[2] << 32 | data[3] << 48;
	for (i = 0; i < PCA9555_MAX_INPUT_PIN; i++) {
		if (value & PCA9555_mask_int[i]) {
			ret |= 1 << i;
		}
	}
	return ret;
}
static uint32_t u32IO_value =0,u32IO_lastValue = 0;
static uint32_t lastHandlerIO = 0;
void handler_IO(){
	if ((uint32_t) (u32MiliCount - lastHandlerIO) >= 200) {
		u32IO_value = RJ45_get_input();
		if (u32IO_value != u32IO_lastValue) {
			RJ45_set_output(u32IO_value);
		}
		u32IO_lastValue = u32IO_value;
	}

}

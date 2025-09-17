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


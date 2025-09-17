/*
 * config.h
 *
 *  Created on: Sep 13, 2025
 *      Author: thangnq
 */

#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_
#include <stdint.h>
#include "queue.h"



#define DP_RX_QUEUE_MAX_SIZE				20
#define DP_TX_QUEUE_MAX_SIZE				20

enum DATA_SOURCE {
	source_485 = 1,
	source_debug = 3,
};

// @formatter:on

typedef struct _RS232_DATA {
	uint8_t source;
	uint16_t len;
	uint32_t ptr_data;

} RS232_DATA;

#define AUTHOR      "ThangNguyen"
#define EMAIL		"thannq2706193@gmail.com"
#define VERSION     "1.0.0"
#define BUILD_DATE  __DATE__
#define BUILD_TIME  __TIME__


extern volatile uint32_t u32MiliCount;
extern volatile uint32_t u32SecCount;

extern queue_t *DP_RxQueue;
extern queue_t *DP_TxQueue;

#endif /* CONFIG_CONFIG_H_ */

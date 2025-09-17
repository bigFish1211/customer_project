/*
 * handlerIOTask.h
 *
 *  Created on: Sep 16, 2025
 *      Author: thannq
 */

#ifndef TASK_HANDLERIOTASK_H_
#define TASK_HANDLERIOTASK_H_

#include <stdint.h>
int putcomdata(uint8_t *data, uint16_t len, uint8_t source);
int handler_comdata();

#endif /* TASK_HANDLERIOTASK_H_ */

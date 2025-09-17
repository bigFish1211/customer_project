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
void RJ45_IO_setup();
void RJ45_set_output(uint32_t value);
void handler_IO();

#endif /* TASK_HANDLERIOTASK_H_ */

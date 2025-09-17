#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdint.h>

typedef unsigned long DataType_T;
struct queue {
	int size;
	int count;
	DataType_T *elements;
	DataType_T volatile * tail;
	DataType_T volatile * head;
};

typedef struct queue queue_t;

queue_t * queue_init(int size);
int queue_put(queue_t *queue, void * data);
int queue_get(queue_t *queue, DataType_T * dataptr);

#endif

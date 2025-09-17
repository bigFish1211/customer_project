#include <stdlib.h>
#include "queue.h"

queue_t * queue_init(int size) {
	queue_t * queue;
	int newSize = size + 1;
	queue = (queue_t *) malloc(sizeof(queue_t));
	queue->elements = (DataType_T *) malloc(newSize * sizeof(DataType_T));
	queue->tail = queue->head = &queue->elements[0];
	queue->size = newSize;
	return queue;
}

int queue_put(queue_t *queue, void * data) {
	DataType_T * nextTail;
	nextTail = queue->tail + 1;
	if (nextTail == &queue->elements[queue->size]) {
		/* Wrap around. */
		nextTail = &queue->elements[0];
	}

	if (nextTail == queue->head) {
		return 0;
	} else {
		*queue->tail = (DataType_T) data;
		queue->tail = nextTail;

		queue->count++;
		return 1;
	}
}

int queue_get(queue_t *queue, DataType_T *dataptr) {
	if (queue->tail == queue->head) {
		/* Queue is empty. */
		queue->count = 0;
		return 0;
	}
	DataType_T * tmp = (queue->head++); //lay data cua head, trong head co dia chi pointer tiep theo
	memcpy(dataptr, tmp, sizeof(DataType_T));

	if (queue->head == &queue->elements[queue->size]) {
		/* Wrap around. */
		queue->head = &queue->elements[0];
	}
	queue->count--;

	return 1;
}


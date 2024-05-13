#include <stdio.h>
#include <stdlib.h>
#include "my_bc.h"


Queue* create_queue(unsigned int capacity) {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	queue->front = 0;
	queue->size = 0;
	queue->rear = capacity - 1;
	queue->capacity = capacity;
	queue->array = (char**)malloc(queue->capacity * sizeof(char*));

	unsigned int index = 0;
	while (index < queue->capacity) {
		queue->array[index] = (char*)malloc(10 * sizeof(char));
		index++;
	}

	return queue;
}

void enqueue(Queue* queue, char* value) {
	unsigned int size = queue->size;
	if (size == queue->capacity) {
		printf("queue is full\n");
	}
	else {
		queue->rear = (queue->rear + 1) % queue->capacity;
		my_strcpy(queue->array[queue->rear], value);
		queue->size += 1;
	}
}

int dequeue(Queue* queue) {
	int index = queue->front;
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size -= 1;

	return index;
}

void print_queue(Queue* queue) {
	int index = queue->front;

	while (index != queue->rear + 1) {
		printf("%s", queue->array[index]);
		index ++;
	}
	printf("\n");
}

void free_queue(Queue* queue) {
	unsigned int index = 0;

	while (index < queue->capacity) {
		free(queue->array[index]);
		index ++;
	}
	free(queue->array);
	free(queue);
}

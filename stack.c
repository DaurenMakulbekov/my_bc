#include <stdio.h>
#include <stdlib.h>
#include "my_bc.h"


Stack* create_stack(unsigned int capacity) {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = -1;
	stack->capacity = capacity;
	stack->array = (char**)malloc(stack->capacity * sizeof(char*));

	unsigned int index = 0;
	while (index < stack->capacity) {
		stack->array[index] = (char*)malloc(10 * sizeof(char));
		index++;
	}

	return stack;
}

void push(Stack* stack, char* value) {
	unsigned int size = stack->top + 1;
	if (size == stack->capacity) {
		printf("stack is full\n");
	}
	else {
		my_strcpy(stack->array[++stack->top], value);
	}
}

int pop(Stack* stack) {
	int index = stack->top;
	stack->top -= 1;

	return index;
}

void print_stack(Stack* stack) {
	int index = 0;

	while (index < stack->top + 1) {
		printf("%s", stack->array[index]);
		index ++;
	}
	printf("\n");
}

void free_stack(Stack* stack) {
	unsigned int index = 0;

	while (index < stack->capacity) {
		free(stack->array[index]);
		index ++;
	}
	free(stack->array);
	free(stack);
}

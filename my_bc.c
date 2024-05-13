#include <stdio.h>
#include <stdlib.h>
#include "my_bc.h"
#include <unistd.h>


void copy_from_stack_to_queue(Stack* stack, Queue* queue) {
	while (stack->top != -1) {
		enqueue(queue, stack->array[stack->top]);
		stack->top --;
	}
}

void addition(Stack* stack, char* number, char* ptr_2, char* ptr_1) {
    int number_1 = my_atoi(ptr_1);
	int number_2 = my_atoi(ptr_2);
    my_itoa(number, number_2 + number_1);
	push(stack, number);
}

void subtraction(Stack* stack, char* number, char* ptr_2, char* ptr_1) {
    int number_1 = my_atoi(ptr_1);
	int number_2 = my_atoi(ptr_2);
    my_itoa(number, number_2 - number_1);
	push(stack, number);
}

void multiplication(Stack* stack, char* number, char* ptr_2, char* ptr_1) {
    int number_1 = my_atoi(ptr_1);
	int number_2 = my_atoi(ptr_2);
    my_itoa(number, number_2 * number_1);
	push(stack, number);
}

void division(Stack* stack, char* number, char* ptr_2, char* ptr_1) {
    int number_1 = my_atoi(ptr_1);
	int number_2 = my_atoi(ptr_2);

    if (number_1 == 0) {
        write(2, "divide by zero\n", 15);
    }
    else {
        my_itoa(number, number_2 / number_1);
	    push(stack, number);
    }
}

void mod(Stack* stack, char* number, char* ptr_2, char* ptr_1) {
    int number_1 = my_atoi(ptr_1);
	int number_2 = my_atoi(ptr_2);
    my_itoa(number, number_2 % number_1);
	push(stack, number);
}

void compute(Stack* stack, char* ptr_2, char* ptr_1, char* value) {
	char* number = NULL;
	number = (char*)malloc(10 * sizeof(char));

	if (value[0] == '+') {
        addition(stack, number, ptr_2, ptr_1);
	}
	else if (value[0] == '-') {
        subtraction(stack, number, ptr_2, ptr_1);
	}
	else if (value[0] == '*') {
        multiplication(stack, number, ptr_2, ptr_1);
	}
	else if (value[0] == '/') {
        division(stack, number, ptr_2, ptr_1);
	}
	else if (value[0] == '%') {
        mod(stack, number, ptr_2, ptr_1);
	}
	free(number);
}

void my_bc(Stack* stack, Queue* queue) {
	copy_from_stack_to_queue(stack, queue);
	int index_front = 0;
	int index_1, index_2;

	while (queue->size != 0) {
		index_front = dequeue(queue);
        if (queue->array[index_front][0] < '0' && queue->array[index_front][1] == '\0') {
            if (queue->array[index_front][0] == '+' || queue->array[index_front][0] == '-' || queue->array[index_front][0] == '*' || queue->array[index_front][0] == '/' || queue->array[index_front][0] == '%') {
                index_1 = pop(stack);
			    index_2 = pop(stack);
                
			    compute(stack, stack->array[index_2], stack->array[index_1], queue->array[index_front]);
		    }
        }
		else {
			push(stack, queue->array[index_front]);
		}
	}
}

void print_output(Stack* stack, Queue* queue) {
    if (queue->size == 1 && stack->top == -1) {
        print_queue(queue);
    }
    else if (queue->size > 1) {
		my_bc(stack, queue);
        if (stack->top != -1) {
		    print_stack(stack);
        }
    }
}

void free_stack_queue(Stack* stack, Queue* queue) {
    free_queue(queue);
	free_stack(stack);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        return 0;
    }
    else {
		int length = my_strlen(argv[1]);
		Stack* stack = create_stack(length);
		Queue* queue = create_queue(length);
        int ptr = 0;
        
        my_split(stack, queue, argv, &ptr);
        if (ptr == 0) {
            print_output(stack, queue);
            if (stack->top != -1) {
                free_stack_queue(stack, queue);
                return 0;
            }
            else {
                free_stack_queue(stack, queue);
                return 1;
            }
        }
        else {
            write(2, "parse error\n,", 12);
            free_stack_queue(stack, queue);
            return 1;
        }
    }
}

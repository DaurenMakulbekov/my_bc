#include <stdio.h>
#include <stdlib.h>
#include "my_bc.h"


int my_strlen(char* ptr) {
	int index = 0;

	while (ptr[index] != '\0') {
		index ++;
	}

	return index;
}

void my_strcpy(char* array, char* ptr) {
	int index = 0;

	while (ptr[index] != '\0') {
		array[index] = ptr[index];
		index ++;
	}
	array[index] = '\0';
}

void from_stack_to_queue(Stack* stack, Queue* queue, char* value) {
    int index = pop(stack);
	enqueue(queue, stack->array[index]);
	push(stack, value);
}

void value_addition(Stack* stack, Queue* queue, char* value) {
    if (stack->top != -1 && stack->array[stack->top][0] == '-') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '+') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '/') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '*') {
		from_stack_to_queue(stack, queue, value);
	}
    else {
		push(stack, value);
	}
}

void value_subtraction(Stack* stack, Queue* queue, char* value) {
    if (stack->top != -1 && stack->array[stack->top][0] == '+') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '-') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '/') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '*') {
		from_stack_to_queue(stack, queue, value);
	}
    else {
		push(stack, value);
	}
}

void value_multiplication(Stack* stack, char* value) {
    /*
    if (stack->top != -1 && stack->array[stack->top][0] == '/') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '*') {
		from_stack_to_queue(stack, queue, value);
	}
    */

    //else {
	push(stack, value);
	//}
}

void value_division(Stack* stack, char* value) {
    /*
    if (stack->top != -1 && stack->array[stack->top][0] == '*') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '/') {
		from_stack_to_queue(stack, queue, value);
	}
    */
    //else {
	push(stack, value);
	//}
}

void value_mod(Stack* stack, Queue* queue, char* value) {
    if (stack->top != -1 && stack->array[stack->top][0] == '*') {
		from_stack_to_queue(stack, queue, value);
	}
    else if (stack->top != -1 && stack->array[stack->top][0] == '/') {
		from_stack_to_queue(stack, queue, value);
	}
    else {
	    push(stack, value);
	}
}

void value_parentheses(Stack* stack, Queue* queue, char** argv, int index, char* value, int* ptr) {
    if (argv[1][index] == '(') {
        value[0] = argv[1][index];
        value[1] = '\0';
        push(stack, value);
    }
    else if (argv[1][index] == ')') {
        if (stack->array[stack->top][0] == '(') {
            *ptr = 1;
        }
        else {
            int index_stack = 0;
            while (stack->array[stack->top][0] != '(') {
                index_stack =  pop(stack);
                if (stack->array[index_stack][0] != '(') {
                    enqueue(queue, stack->array[index_stack]);
                }
            }
            pop(stack);
        }
    }
}

void fill_stack(Stack* stack, Queue* queue, char* value) {
    if (value[0] == '+') {
        value_addition(stack, queue, value);
	}
	else if (value[0] == '-') {
        value_subtraction(stack, queue, value);
	}
    else if (value[0] == '*') {
        value_multiplication(stack, value);
    }
    else if (value[0] == '/') {
        value_division(stack, value);
    }
    else if (value[0] == '%') {
        value_mod(stack, queue, value);
    }
}

void value_operators(Stack* stack, Queue* queue, char** argv, int* index, char* value, char* prev, int* ptr) {
    if (my_strlen(prev) == 1 && prev[0] < '0') {
        *ptr = 1;
    }
    else {
        value[0] = argv[1][*index];
	    value[1] = '\0';
	    fill_stack(stack, queue, value);
        
        prev[0] = argv[1][*index];
        prev[1] = '\0';
    }
}

void value_number(Queue* queue, char** argv, int index, char* value, int* index_value, char* prev) {
    int index_1 = *index_value;
    value[*index_value] = argv[1][index];
    prev[*index_value] = argv[1][index];
    index_1 ++;
	*index_value = index_1;
    
    if (argv[1][index + 1] < '0' || argv[1][index + 1] == '\0' || argv[1][index + 1] == ')') {
        value[*index_value] = '\0';
        prev[*index_value] = '\0';
	    enqueue(queue, value);    
        *index_value = 0;
    }
}

void my_split(Stack* stack, Queue* queue, char** argv, int* ptr) {
	char* value = (char*)malloc(10 * sizeof(char));
    char* prev = (char*)malloc(10 * sizeof(char));

	int index = 0;
	int index_value = 0;
	while (argv[1][index] != '\0') {
        if ((argv[1][index] >= '0' && argv[1][index] <= '9') || (argv[1][index + 1] == '\0' && argv[1][index] >= '0' && argv[1][index] <= '9')) {
            value_number(queue, argv, index, value, &index_value, prev);
	    }
        else if (argv[1][index] == '-' && prev[0] < '0' && prev[1] == '\0' && argv[1][index + 1] >= '0') {
            value_number(queue, argv, index, value, &index_value, prev);
        }
	    else if (argv[1][index] == '%' || argv[1][index] == '*' || argv[1][index] == '+' || argv[1][index] == '-' || argv[1][index] == '/') {
            value_operators(stack, queue, argv, &index, value, prev, ptr);
	    }
        else if (argv[1][index] == '(' || argv[1][index] == ')') {
            value_parentheses(stack, queue, argv, index, value, ptr);
        }
        else if (argv[1][index] > '9') {
            *ptr = 1;
        }
		index ++;
	}
	free(value);
    free(prev);
}

void get_array_int(char* ptr, int* array) {
	int number[10] = {0, 1, 2, 3, 4, 5, 6, 7 ,8 ,9};
	int index = 0;
	int count = 0;
	int index_ptr = 0;

	while (ptr[index_ptr] != '\0') {
		count = 0;
		for (int i = 48; i < 58; i++) {
			if (ptr[index_ptr] == i) {
				array[index] = number[count];
				index += 1;
				break;
			}
			count += 1;
		}
		index_ptr ++;
	}
}

int get_int(int* array_int, int length) {
	int array_numbers[10] = {1, 10, 100, 1000};
    int index_1 = length - 1;
    int number = 0;
	int index = 0;

	while (index < length) {
		number += array_int[index] * array_numbers[index_1];
		index += 1;
		index_1 -= 1;
	}

    return number;
}

int my_atoi(char* ptr) {
    int* array_int = NULL;
    int length = my_strlen(ptr);
	array_int = (int*)malloc(length * sizeof(int));
	get_array_int(ptr, array_int);

	int number = 0;
    if (ptr[0] == '-') {
        length -= 1;
    }
    number = get_int(array_int, length);
    if (ptr[0] == '-') {
        number = -number;
    }

	free(array_int);
	return number;
}

void reverse(char* ptr, char* ptr_1, int index) {
	int length = my_strlen(ptr_1);
	int index_1 = 0;

	while (index_1 < length) {
		ptr[index_1] = ptr_1[index - 1];
		index_1 ++;
		index --;
	}
	ptr[index_1] = '\0';
}

void my_itoa_1(char* ptr, int number) {
    number = -number;
    char ptr_1[10];
	int index = 0;

	 while (number > 0) {
		ptr_1[index] = (number % 10) + '0';
		number = number / 10;
		index ++;
	}
    ptr_1[index] = '-';
    index += 1;
	ptr_1[index] = '\0';

	reverse(ptr, ptr_1, index);
}

void my_itoa(char* ptr, int number) {
	if (number < 10 && number >= 0) {
		ptr[0] = (number % 10) + '0';
		ptr[1] = '\0';
	}
    else if (number < 0) {
        my_itoa_1(ptr, number);
    }
	else {
        char ptr_1[10];
		int index = 0;
        
		while (number > 0) {
		    ptr_1[index] = (number % 10) + '0';
		    number = number / 10;
		    index ++;
		}
		ptr_1[index] = '\0';

		reverse(ptr, ptr_1, index);
	}
}


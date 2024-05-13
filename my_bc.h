/* Struct */
typedef struct Stack {
	int top;
	unsigned int capacity;
	char** array;
} Stack;

typedef struct Queue {
	int front, rear, size;
	unsigned int capacity;
	char** array;
} Queue;

/* stack.c */
Stack* create_stack(unsigned int capacity);
void push(Stack* stack, char* value);
int pop(Stack* stack);
void print_stack(Stack* stack);
void free_stack(Stack* stack);

/* queue.c */
Queue* create_queue(unsigned int capacity);
void enqueue(Queue* queue, char* value);
int dequeue(Queue* queue);
void print_queue(Queue* queue);
void free_queue(Queue* queue);

/* functions.c */
int my_strlen(char* ptr);
void my_strcpy(char* array, char* ptr);
void value_addition(Stack* stack, Queue* queue, char* value);
void value_subtraction(Stack* stack, Queue* queue, char* value);
void value_multiplication(Stack* stack, char* value);
void value_division(Stack* stack, char* value);
void value_mod(Stack* stack, Queue* queue, char* value);
void fill_stack(Stack* stack, Queue* queue, char* value);
void value_parentheses(Stack* stack, Queue* queue, char** argv, int index, char* value, int* ptr);
void value_operators(Stack* stack, Queue* queue, char** argv, int* index, char* value, char* prev, int* ptr);
void value_number(Queue* queue, char** argv, int index, char* value, int* index_value, char* prev);
void my_split(Stack* stack, Queue* queue, char** argv, int* ptr);
void get_array_int(char* ptr, int* array);
int get_int(int* array_int, int length);
int my_atoi(char* ptr);
void my_itoa(char* ptr, int number);
void reverse(char* ptr, char* ptr_1, int index);
void my_itoa_1(char* ptr, int number);

CC=gcc
CFLAGS=-Wall -Wextra -Werror
TARGET=my_bc

all:
	$(CC) ${CFLAGS} my_bc.c stack.c queue.c functions.c -o ${TARGET}

clean:
	rm -rf my_bc

fclean: clean

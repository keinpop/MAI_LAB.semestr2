CC ?= gcc 
CFLAGS ?= -g -Werror -std=c99
all:
	$(CC) $(CFLAGS) deque.c main.c -o main

main: main.o deque.o
	${CC} -o main main.o deque.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: deque.c deque.o
	${CC} ${CFLAGS} -c deque.c

clean: 
	rm -rf *.o main
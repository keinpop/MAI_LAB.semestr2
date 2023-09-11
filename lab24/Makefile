CC = gcc
CFLAGS ?= -g -Wall -Wextra -std=c99 -w -lm

all:
	$(CC) $(CFLAGS) transform.c tree.c lexer.c main.c -o main

main: main.o  lexer.o  tree.o  transform.o
	${CC} -o main main.o  lexer.o tree.o transform.o

main.o: main.c 
	${CC} ${CFLAGS} -c main.c

functions.o: lexer.c lexer.o  tree.c tree.o transform.c transform.o
	${CC} ${CFLAGS} -c  lexer.c tree.c transform.c

clean: 
	rm -rf *.o main
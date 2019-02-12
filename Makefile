##
## Makefile
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -Wall -O3 -g

## Define targets

default: run
all: main.o debug.o chess.o micro.o drivers.o
run: main
	./main
	$(MAKE) clean

main: all
	$(CC) $(CFLAGS) main.o debug.o chess.o micro.o drivers.o -o main

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -rf *.o main

## rule to compile .c to .o

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

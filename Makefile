##
## Makefile
##

## Define compiler

CC	= gcc

## Define flags

CFLAGS	= -Wall -O3 -g

## Define targets

default: run
all: main
run: all
	./main
	$(MAKE) clean

main: main.o
	$(CC) $(CFLAGS) main.o -o main

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -rf *.o main

## rule to compile .c to .o

%.o:	%.c
	$(CC) $(CFLAGS) -c $<

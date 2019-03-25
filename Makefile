##
## Makefile
##

## Define Fake Targets
.PHONY: clean build run

## Define compiler

CC	= gcc

## Define Directories
ODIR = Build
SDIR = Src
IDIR = Inc
_OBJS = main.o debug.o chess.o drivers.o ai.o board.o book.o data.o eval.o search.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

## Define flags

CFLAGS	= -Wall -O3 -g -I $(IDIR)

## Define targets

default: run
all: main
objects: $(OBJS)

run: main
	./main

main: objects
	$(CC) $(CFLAGS) $(ODIR)/*.o -o "Build/main" && cp "Build/main" ./

## rule to clean up object files and executable so that you can rebuild

clean:
	rm -rf *.o main Build

## rule to compile .c to .o

$(ODIR)/%.o:	$(SDIR)/%.c
	mkdir -p Build
	$(CC) $(CFLAGS) -c -o "$@" "$<"

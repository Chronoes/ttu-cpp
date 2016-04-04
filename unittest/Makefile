SHELL := $(shell echo $$SHELL)
CC=clang++
CFLAGS=-Wall -std=c++11 -I include -O2

all: lib/unittest.o

lib/unittest.o:
	$(CC) $(CFLAGS) -o lib/unittest.o -c unittest.cpp

clean:
	rm lib/*.o

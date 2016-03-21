SHELL := $(shell echo $$SHELL)
CC=clang++
CFLAGS=-Wall -std=c++11 -I include -O2

all: unittest.o

unittest.o:
	$(CC) $(CFLAGS) -o lib/unittest.o -c unittest.cpp

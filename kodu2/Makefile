SHELL := $(shell echo $$SHELL)
CC=g++
CFLAGS=-Wall -std=c++11

all: test kodu2

kodu2:
	$(CC) $(CFLAGS) -o kodu2 kodu2.cpp

test:
	$(CC) $(CFLAGS) -D TESTING -o test kodu2.cpp test_functions.cpp test.cpp
	./test
	rm test

clean:
	rm -f kodu2 test

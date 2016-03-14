SHELL := $(shell echo $$SHELL)
CC=clang++
CFLAGS=-Wall -std=c++11

all: test
	$(CC) $(CFLAGS) -o kodu2 kodu2.cpp

test:
	$(CC) $(CFLAGS) -D TESTING -o test kodu2.cpp test.cpp
	./test

clean:
	rm -f kodu2 test

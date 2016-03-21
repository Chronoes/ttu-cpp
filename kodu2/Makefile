SHELL := $(shell echo $$SHELL)
CC=clang++
CFLAGS=-Wall -std=c++11

UNITTEST_PATH=$(shell realpath ../unittest)

all: runtest kodu2

kodu2:
	$(CC) $(CFLAGS) -o kodu2 kodu2.cpp

kodu2test.o:
	$(CC) $(CFLAGS) -D TESTING -o kodu2test.o -c kodu2.cpp

test: kodu2test.o
	$(CC) $(CFLAGS) -I $(UNITTEST_PATH)/include $(UNITTEST_PATH)/lib/unittest.o -D TESTING -o test kodu2test.o test.cpp

runtest: test
	./test

clean:
	rm -f kodu2 kodu2test.o test

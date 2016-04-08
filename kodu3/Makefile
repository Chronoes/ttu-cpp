SHELL := $(shell echo $$SHELL)
CC = clang++
CFLAGS = -Wall -std=c++11

UNITTEST_PATH = $(shell realpath ../unittest)
UNITTEST_INCLUDE = -I$(UNITTEST_PATH)/include
UNITTEST_LIB = $(UNITTEST_PATH)/lib/*.o

# Atom clang-linter
.clang_complete:
	echo $(UNITTEST_INCLUDE) > .clang_complete

all: bin bin/main

bin:
	mkdir -p bin

bin/Teenus.o: bin
	$(CC) $(CFLAGS) -o bin/Teenus.o -c Teenus.cpp

bin/main: bin/Teenus.o
	$(CC) $(CFLAGS) -o bin/main bin/*.o main.cpp

bin/test: bin/Teenus.o
	$(CC) $(CFLAGS) -DTESTING -o bin/test $(UNITTEST_INCLUDE) $(UNITTEST_LIB) bin/Teenus.o testTeenus.cpp

test: bin/test
	./bin/test

package:
	cat <(cat Teenus.hpp) <(sed 's/#include "Teenus.hpp"//' Teenus.cpp) > Teenus.h

clean:
	rm -rf bin Teenus.h

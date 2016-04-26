SHELL := $(shell echo $$SHELL)
CC = clang++
CFLAGS = -Wall -std=c++11

all: clean main

debug: CFLAGS += -DDEBUG
debug: main

kodu2.o:
	$(CC) $(CFLAGS) -DTESTING -c ../kodu2/kodu2.cpp

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main: Saade.o main.o kodu2.o
	$(CC) $(CFLAGS) -o main $^

clean:
	rm -rf *.o main test

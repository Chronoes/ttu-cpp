SHELL := $(shell echo $$SHELL)
CC = clang++
CFLAGS = -Wall -std=c++11

all: clean main

debug: CFLAGS += -DDEBUG
debug: main

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main: main.o
	$(CC) $(CFLAGS) -o main $^

clean:
	rm -rf *.o main test

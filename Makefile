CC = gcc

all: main server init

main: main.o
server: server.o
init: init.o

main.o: main.c malicious.h
server.o: server.c
init.o: init.c

.PHONY: clean
clean:
	rm -f *.o main server init
CC = gcc
CFLAGS = -c -Wall

all: build

build: main.o
	$(CC) main.o -o build

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o build

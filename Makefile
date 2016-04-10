CC = gcc
CFLAGS = -c -Wall

all: main

main: main.o build_index.o probe.o
	$(CC) main.o build_index.o probe.o -o main

main.o: main.c
	$(CC) $(CFLAGS) main.c

build_index.o: build_index.c
	$(CC) $(CFLAGS) build_index.c

probe.o: probe.c
	$(CC) $(CFLAGS) probe.c

clean:
	rm -rf *.o main

	

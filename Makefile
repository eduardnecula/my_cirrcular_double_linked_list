CC=gcc
CFLAGS=-Wall -Wextra -std=c99
DEBUG=-g -ggdb -march=native

build: main

main: Galaxi.o Circular.o
	$(CC) $(CFLAGS) $(DEBUG) Galaxi.o Circular.o -o main

src/Circular.o: Circular.h Circular.c
	$(CC) $(CFLAGS) $(DEBUG) Circular.c -c -o Circular.o

src/Galaxi.o: Galaxi.c
	$(CC) $(CFLAGS) $(DEBUG) Galaxi.c -c -o Galaxi.o

run:
	./main

clean:
	rm *.o
	rm main


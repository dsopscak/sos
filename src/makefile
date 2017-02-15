CFLAGS = -std=c99 -Wall
CC = gcc

sos: main.o sha256.o list.o quick_crypt.o
	gcc -o sos $^ 

clean:
	rm -f *.o sos

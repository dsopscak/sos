CFLAGS = -std=c99 -Wall
CC = gcc

qc: main.o sha256.o list.o quick_crypt.o
	gcc -o qc $^ 

clean:
	rm -f *.o qc

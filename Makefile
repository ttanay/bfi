.PHONY: all clean

CC = g++

all: bfi

bfi: bfi.o
	$(CC) -o bfi bfi.o

bfi.o: bfi.cpp
	$(CC) -c bfi.cpp

clean:
	rm *.o bfi
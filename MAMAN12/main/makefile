CC=gcc
CFLAGS= -g -ansi - pedantic -Wall

main: main.o my_bcmp.o
	$(CC) my_bcmp.o main.o -o main

main.o: main.c
	$(CC) -c main.c -o main.o

my_bcmp.o: my_bcmp.c
	$(CC) -c my_bcmp.c -o my_bcmp.o

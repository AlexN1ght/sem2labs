CC = gcc
LD = gcc
CCFLAGS = -Wall -pedantic  -std=c99
LDFLAGS =

main.out: main.o sort.o stack.o
	$(LD) $(LDFLAGS) -o main.out main.o sort.o stack.o
main.o: main.c stack.h sort.h
	$(CC) $(CCFLAGS) -c main.c
sort.o: sort.c sort.h
	$(CC) $(CCFLAGS) -c sort.c
stack.o: stack.c stack.h
	$(CC) $(CCFLAGS) -c stack.c
sort.o: stack.h

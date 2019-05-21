CC = gcc
LD = gcc
CCFLAGS = -Wall -pedantic  -std=c99
LDFLAGS =

main.out: main.o stack.o sort.o
	$(LD) $(LDFLAGS) -o main.out main.o stack.o sort.o
main.o: main.c stack.h sort.h sort.c stack.c
	$(CC) $(CCFLAGS) -c main.c
sort.o: sort.c sort.h
	$(CC) $(CCFLAGS) -c stack.c
stack.o: stack.c stack.h
	$(CC) $(CCFLAGS) -c stack.c
clean:
	rm *.o

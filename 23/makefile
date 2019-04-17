CC = gcc
LD = gcc
CCFLAGS = -Wall -pedantic  -std=c99
LDFLAGS =

main.out: main.o gtree.o
	$(LD) $(LDFLAGS) -o main.out main.o gtree.o
main.o: main.c GTree.h
	$(CC) $(CCFLAGS) -c main.c
gtree.o: gtree.c GTree.h
	$(CC) $(CCFLAGS) -c gtree.c
clean:
	rm *.o

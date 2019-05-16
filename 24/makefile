CC = gcc
LD = gcc
CCFLAGS = -Wall -pedantic  -std=c99
LDFLAGS =

main.out: main.o lin-2-list-barrier.o dayk.o bitree.o stack.o
	$(LD) $(LDFLAGS) -o main.out main.o lin-2-list-barrier.o dayk.o stack.o bitree.o 
main.o: main.c bitree.c Bitree.h lin-2-list-barrier.c Lin-2-list-barrier.h stack.c Stack.h Dayk.h dayk.c
	$(CC) $(CCFLAGS) -c main.c
dayk.o: Dayk.h dayk.c lin-2-list-barrier.c Lin-2-list-barrier.h
	$(CC) $(CCFLAGS) -c dayk.c
stack.o: stack.c Stack.h Bitree.h
	$(CC) $(CCFLAGS) -c stack.c
bitree.o: bitree.c Bitree.h
	$(CC) $(CCFLAGS) -c bitree.c
lin-2-list-barrier.o: lin-2-list-barrier.c Lin-2-list-barrier.h
	$(CC) $(CCFLAGS) -c lin-2-list-barrier.c
clean:
	rm *.o

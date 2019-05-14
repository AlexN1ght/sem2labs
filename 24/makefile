CC = gcc
LD = gcc
CCFLAGS = -Wall -pedantic  -std=c99
LDFLAGS =

main.out: main.o lin-2-list-barrier.o dayk.o
	$(LD) $(LDFLAGS) -o main.out main.o lin-2-list-barrier.o dayk.o
main.o: main.c Dayk.h dayk.c lin-2-list-barrier.c Lin-2-list-barrier.h
	$(CC) $(CCFLAGS) -c main.c
dayk.o: Dayk.h dayk.c lin-2-list-barrier.c Lin-2-list-barrier.h
	$(CC) $(CCFLAGS) -c dayk.c
lin-2-list-barrier.o: lin-2-list-barrier.c Lin-2-list-barrier.h
	$(CC) $(CCFLAGS) -c lin-2-list-barrier.c
clean:
	rm *.o

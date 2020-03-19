CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -c
LDFLAGS =

all: forests

.PHONY: all clean

bst.o: bst.c alloc.h bst.h
	$(CC) $(CFLAGS) $<

stringops.o: stringops.c alloc.h stringops.h
	$(CC) $(CFLAGS) $<

instruction.o: instruction.c alloc.h instruction.h stringops.h
	$(CC) $(CFLAGS) $<

forests.o: forests.c bst.h instruction.h
	$(CC) $(CFLAGS) $<

forests: forests.o bst.o instruction.o stringops.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o forests
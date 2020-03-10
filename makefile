CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2
LDFLAGS =

all: forests

forests: forests.o alloc.o bst.o instruction.o stringops.o
	$(CC) $(LDFLAGS) -o $@ $^

alloc.o: alloc.c alloc.h
	$(CC) $(CFLAGS) $<

bst.o: bst.c alloc.h bst.h
	$(CC) $(CFLAGS) $<

stringops.o: stringops.c alloc.h stringops.h
	$(CC) $(CFLAGS) $<

instruction.o: instruction.c alloc.h instruction.h stringops.h
	$(CC) $(CFLAGS) $<

forests.o: forests.c bst.h instruction.h
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o forests
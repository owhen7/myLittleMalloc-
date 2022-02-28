CC=gcc
CFLAGS=-I.
DEPS = mymalloc.h
OBJ = mymalloc.o memgrind.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mymalloc: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
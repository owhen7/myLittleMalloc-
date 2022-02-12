#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"



static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line)
{
    printf("Mymalloc was called from %s:%d\n", file, line);

    return NULL;
}

void myfree(void *p, char *file, int line)
{
    printf("free was called from %s:%d\n", file, line);

}
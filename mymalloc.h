#ifndef MALLOC_H
#define MALLOC_H
#include <stddef.h>

//Function Prototypes for malloc() and free() functions
void* mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

//Structure type declaration
typedef struct header{
        int length;
        int isFree;
        struct header* next;
    }header;



//Macro to replace the library functions free() and malloc() with our versions.
#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)

//Macro to define the size of our memory array
#define MEMSIZE 4096
#endif

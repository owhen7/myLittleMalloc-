#include <stddef.h>

//This code is from the Project1 Writeup. It must be included.
void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);
//void insertAfter(struct header*, size_t, int);

struct header{
        int length;
        int isFree;
        struct header *next;
    };

//Macro to replace the library functions free() and malloc() with our versions.
#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)
#define MEMSIZE 4096


//Does anything else go in this header? Or just these lines?

//This code is from the Project1 Writeup. It must be included.
void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);

//Macro to replace the library functions free() and malloc() with our versions.
#define malloc(s) mymalloc(s, __FILE__, __LINE__)
#define free(p) myfree(p, __FILE__, __LINE__)


//Does anything else go in this header? Or just these lines?
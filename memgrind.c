#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"


//This program is meant to test our malloc and free functions.
int main(int argc, char**argv)
{
  //The first 4 steps of this program are outlined in the project writeup.

    int *p = malloc(1024);
    free(p);
  
    return EXIT_SUCCESS;
}
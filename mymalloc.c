#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

void insertAfter(struct header *prev_node, size_t new_size, int old_size)
{
    /*1. check if the given prev_node is NULL */
    /*if (prev_node == NULL)
    {
    printf("the given previous node cannot be NULL");
    return;
    }*/

    /* 2. allocate new node */
    struct header* new_node =(struct header*) malloc(sizeof(struct header));

    /* 3. put in the data */
    new_node->length = (old_size-new_size)-sizeof(struct header);
    new_node->isFree = 1;

    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;

    return;

}

static char memory[MEMSIZE];

struct header* startPoint = (struct header*)memory;

startPoint->length = (sizeof(memory) - sizeof(struct header));
startPoint->isFree = 1;
startPoint->next = startPoint;

void *mymalloc(size_t size, char *file, int line)
{
    //start from the first chunk
   struct header *current = startPoint;

   //if the first chunk is free
   /*if(current.isFree) {
       if((&(current->next)) - (&(current)) >= size)
        return (&(startPoint) + sizeof(struct header));
   }*/

   //navigate through complete memory until a free block of required size is found
   while(!(current->isFree) && (current->length)>=size) {

      //if it is last chunk
      if(current->next == startPoint) {
         return "Not Enough Space";
      } else {
         //go to next link
         current = current->next;
      }
    }

   //if a valid free chunk is found


   //return the address of that chunk for client
   current->isFree = 0;
   if((current->length - size)>sizeof(struct header));
        insertAfter(current, size, (int)current->length);
   current->length = (int)size;
   return (&(current))+sizeof(struct header);

    printf("Mymalloc was called from %s:%d\n", file, line);

    return NULL;
}


void myfree(void *p, char *file, int line)
{
    printf("free was called from %s:%d\n", file, line);
}

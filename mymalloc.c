#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"


static char memory[MEMSIZE];

void* startPoint = (header *)(memory);
//*(header *)memory = (header){(int)(MEMSIZE - sizeof(struct header)), 1, NULL};
//*(header *)memory = (header){NULL, 0, NULL};
/*struct header *startPoint = (header*)memory;
(header*)startPoint->isFree = 1;
(header*)startPoint->length = (MEMSIZE - sizeof(struct header));
(header*)startPoint->next = startPoint;
*/
//insertAfter((sizeof(memory) - sizeof(struct header)),startPoint->length);
//startPoint = (struct header*)memory;

//((header*)startPoint)->length = (sizeof(memory) - sizeof(struct header));
//startPoint = insertAfter(startPoint,(sizeof(memory) - sizeof(struct header)),startPoint->length)
//startPoint = (header*){ (MEMSIZE - sizeof(struct header)), 1, startPoint};
/*->length = (MEMSIZE - sizeof(struct header));
startPoint.current->isFree = 1;
startPoint.current->next = current;*/
//startPoint = startPoint->next;

//header current;


void *mymalloc(size_t size, char *file, int line)
{
    //start from the first chunk
    header* current = startPoint;
   //if the first chunk is free i.e. current is NULL yet
   if((current)->next == NULL) {

        if(size<(MEMSIZE-sizeof(struct header))){
            (current)->isFree = 0;
            void* addressCurrent = current;

            struct header* new_node = (header*)(addressCurrent + (int)(sizeof(struct header) + size));

            if((MEMSIZE - size)>sizeof(struct header))
                {
                    /* 2. allocate new node */

                    /* 3. put in the data */
                    (new_node)->length = (MEMSIZE - size - sizeof(struct header)) - sizeof(struct header);
                    (new_node)->isFree = 1;

                    /* 4. Make next of new node as next of prev_node */
                    (new_node)->next = current;

                    /* 5. move the next of prev_node as new_node */
                    (current)->next = new_node;
                    //insertAfter(&current, &size, MEMSIZE);
                    (current)->length = size;
                }
            else{
                    (current)->next = current;
                    (current)->length = MEMSIZE-sizeof(struct header);
                }
            return (current+1);
        }
        else{
            printf("\nOut of Space: Cannot Allocate Memory at %s:%d\n", file, line);
            return NULL;
        }
   }
    //header** last;
   //navigate through complete memory until a free block of required size is found
   while(current && !(((current)->isFree) && ((current)->length)>=size)) {

      //if it is last chunk
        if((current)->next == startPoint){
        printf("\nOut of Space: Cannot Allocate Memory at %s:%d\n", file, line);
        return NULL;
        }
        //go to next link
        current = (current)->next;
      }

   //if a valid free chunk is found
   //return the address of that chunk for client
   (current)->isFree = 0;
   if((((current)->length) - size)>sizeof(struct header))
   {
       /* 2. allocate new node */
    char* addressCurrent = (char*)current;
    struct header* new_node =(struct header*)(addressCurrent + sizeof(struct header) + size);

    /* 3. put in the data */
    (new_node)->length = (((current)->length)-size)-sizeof(struct header);
    (new_node)->isFree = 1;

    /* 4. Make next of new node as next of prev_node */
    (new_node)->next = (current)->next;

    /* 5. move the next of prev_node as new_node */
    ((current)->next) = new_node;
        //insertAfter(&current, &size, (int)current->length);
    (current)->length = (int)size;
   }

   return (current+1);

    //printf("Mymalloc was called from %s:%d\n", file, line);
}


void myfree(void *p, char *file, int line)
{
    if(!p){
        printf("\nInvalid pointer %p at %s:%d\n", p, file, line);
        return;
    }

    header *prev_metablock = (header*)(p - (int)sizeof(struct header));

    if(!(prev_metablock->isFree))
        prev_metablock->isFree = 1;
    else
    {
        printf("\nInvalid pointer %p at %s:%d\n", p, file, line);
        return;
    }

        header* adjacent_metablock = prev_metablock->next;
        //header* adjacent_metablock = (header*)(addressPrevMetaBlock + (int)sizeof(struct header) + prev_metablock->length);
        if(adjacent_metablock->isFree && adjacent_metablock!=startPoint){
            prev_metablock->length += sizeof(struct header) + adjacent_metablock->length;
            prev_metablock->next = adjacent_metablock->next;
            adjacent_metablock = NULL;
        }

        header* current = startPoint;
        while(current && !(((current)->isFree) && ((current)->next)==prev_metablock && ((current)->next)!=startPoint)) {

        //if it is last chunk
        if((current)->next == startPoint){
        return;
        }
        //go to next link
        current = (current)->next;
        }

            current->length = current->length + sizeof(struct header) + prev_metablock->length;
            current->next = prev_metablock->next;
            prev_metablock = NULL;

      }


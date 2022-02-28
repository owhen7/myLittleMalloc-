#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

//creating static memory array that will act as our memory location to dynamically allocate data
static char memory[MEMSIZE];

//a void pointer that acts as a head pointer of our linked list
void* startPoint = (header *)(memory);

//starting mymalloc() method here
void *mymalloc(size_t size, char *file, int line)
{
    //start from the head pointer (start of memory)
    header* current = startPoint;
   //if the malloc() is being called the first time i.e. current is NULL yet
   if((current)->next == NULL) {

        //if the requested size is less than available memory space
        if(size<(MEMSIZE-sizeof(struct header))){

            //if a valid free chunk is found, set it to NOT FREE
            (current)->isFree = 0;

            void* addressCurrent = current;

            //check if meta-data node can be allocated
            if((MEMSIZE - size)>sizeof(struct header))
                {
                    //create new meta-data node to track the memory address and space availability
                    struct header* new_node = (header*)(addressCurrent + (int)(sizeof(struct header) + size));

                    /* put in the data */
                    (new_node)->length = (MEMSIZE - size - sizeof(struct header)) - sizeof(struct header);
                    (new_node)->isFree = 1;

                    /* Make next of new node as next of prev_node */
                    (new_node)->next = current;

                    /* move the next of prev_node as new_node */
                    (current)->next = new_node;

                    /* set the length of allocated meta-data node equal to the requested size */
                    (current)->length = size;
                }
                /* else return more than size requested as there is not enough space for us to make a new meta-data node */
            else{
                    (current)->next = current;
                    (current)->length = MEMSIZE-sizeof(struct header);
                }

            //return the address for client i.e. the payload address = address of block right after the end of meta-data node
            return (current+1);
        }

        /* else if the requested size is more than available memory space then return NULL */
        else{
            printf("\nOut of Space: Cannot Allocate Memory at %s:%d\n", file, line);
            return NULL;
        }
   }

    //if the linked list has already been initialized i.e. malloc() was previously called
    //navigate through complete memory until a free block of required size is found
   while(current && !(((current)->isFree) && ((current)->length)>=size)) {

        //if it is last chunk and no valid free chunk is found then return NULL
        if((current)->next == startPoint){
        printf("\nOut of Space: Cannot Allocate Memory at %s:%d\n", file, line);
        return NULL;
        }
        //go to next link
        current = (current)->next;
      }

   //if a valid free chunk is found, set it to NOT FREE
   (current)->isFree = 0;

   //check if meta-data node can be allocated
   if((((current)->length) - size)>sizeof(struct header))
   {
        //create new meta-data node to track the memory address and space availability
        char* addressCurrent = (char*)current;
        struct header* new_node =(struct header*)(addressCurrent + sizeof(struct header) + size);

        /* put in the data */
        (new_node)->length = (((current)->length)-size)-sizeof(struct header);
        (new_node)->isFree = 1;

        /* Make next of new node as next of prev_node */
        (new_node)->next = (current)->next;

        /* move the next of prev_node as new_node */
        ((current)->next) = new_node;

        /* set the length of allocated meta-data node equal to the requested size */
        (current)->length = (int)size;
   }

   //return the address for client i.e. the payload address = address of block right after the end of meta-data node
   return (current+1);
}


void myfree(void *p, char *file, int line)
{
    //Check if a valid pointer is passed, i.e. pointer address should not be more than the last address of our memory array
    if(!p || p>= (startPoint + MEMSIZE)){
        printf("\nInvalid pointer %p at %s:%d\n", p, file, line);
        return;
    }

    //get the previous meta-data block
    header *prev_metablock = (header*)(p - (int)sizeof(struct header));

    //check if pointer passed is valid i.e. it should not have been freed already
    if(!(prev_metablock->isFree))
        prev_metablock->isFree = 1;
    else
    {
        printf("\nInvalid pointer %p at %s:%d\n", p, file, line);
        return;
    }

        //get the meta-block right next to the previous meta-block
        header* adjacent_metablock = prev_metablock->next;

        //check if the adjacent right meta-block is free, if it is then coalesce
        if(adjacent_metablock->isFree && adjacent_metablock!=startPoint){
            prev_metablock->length += sizeof(struct header) + adjacent_metablock->length;
            prev_metablock->next = adjacent_metablock->next;
            adjacent_metablock = NULL;
        }

        //iterate through the entire linked list to find a meta-block that is adjacent left to the prev_metablock and is Free.
        header* current = startPoint;
        while(current && !(((current)->isFree) && ((current)->next)==prev_metablock && ((current)->next)!=startPoint)) {

        //if it is last chunk
        if((current)->next == startPoint){
        return;
        }
        //go to next link
        current = (current)->next;
        }


            //if a free block is found adjacent left to prev_metablock, then coalesce
            current->length = current->length + sizeof(struct header) + prev_metablock->length;
            current->next = prev_metablock->next;
            prev_metablock = NULL;

      }


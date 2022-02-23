#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include "mymalloc.h"

//#include "mymalloc.h" can be commented out to verift this testing program works (memgrind.c) independently of the other files.


//This program is meant to test our malloc and free functions.
int main(int argc, char**argv)
{

	//THIS FUNCTION WILL PERFORM EACH TASK 50 TIMES AND RECORD THE TIME IT TAKES FOR EACH TASK.
  	//NOTE - Error checking for free should happen in the free function itself.
  	//This program will have minimal output in the final version because it must do each task 50 times.
  	
  	
  	clock_t t; 
  	t = clock();
  	
  	
  	
  	//1. malloc and immediately free a 1 byte chunk 120 times.
  	for(int j = 0; j < 50; j++)
  	{
  		for(int i = 0; i < 120; i++)
		{
			int *p = malloc(1);
			free(p);
  		}
  	}
	
  	
  	t = clock()- t;
  	double time_passed = ((double)t)/CLOCKS_PER_SEC;
  	printf("Allocate then free 120 times x50 took %f seconds total.\n", time_passed);
  	
	t = clock();
  	//2. malloc() 120 1-byte chunks, store them to an array, and then free all of them afterwards.
  	for(int j = 0; j < 50; j++)
  	{
	  	int *ptr2[120];
	  	for(int i = 0; i < 120; i++)
		{
			ptr2[i] = malloc(1);
	  	}
		for(int i = 0; i < 120; i++)
		{
			free(ptr2[i]);
	  	}
  	}
  	
  	t = clock()- t;
	time_passed = ((double)t)/CLOCKS_PER_SEC;
  	printf("Allocate 120 times then free 120 times x50 took %f seconds total.\n", time_passed);
  	
  	
  	t = clock();
	//3. Randomly choose between allocating 1-byte chunk and deallocating a 1-byte chunk.
	srand((unsigned int)time(NULL)); //It's worth determining if this line goes inside the x50 loop.
	for(int j = 0; j < 50; j++)
  	{
	  	int *ptr3[120]; //This doesn't necessarily need to be 120 spaces long. We are only using a few at the front.
		int countMalloc = 0;
		int arrayIndex = 0;
		while(countMalloc < 120)
		{
			int r = rand() % 2; //Generate a random number that is either zero or one.
			
			//printf("array index is %d\n", arrayIndex);
			//use malloc to allocate a byte if the random number is 0
			if(r == 0)
			{
				ptr3[arrayIndex] = malloc(1);
				arrayIndex++;
				countMalloc++;
				
			}
			
			//free a byte our random number is 1 AND we have >0 bytes currently allocated.
			if(r == 1)
			{
				if(arrayIndex > 0) //If we have at least one byte available.
				{
					
					free(ptr3[arrayIndex-1]);
					arrayIndex--;
				}
			}
		}
		while(arrayIndex > 0) //Free any remaining allocated chunks.
		{
			free(ptr3[arrayIndex-1]);
			arrayIndex--;
		}
  	
  	}
  	
  	t = clock()- t;
	time_passed = ((double)t)/CLOCKS_PER_SEC;
	printf("Randomly allocate or free until 120 allocates x50 took %f seconds total.\n", time_passed);
	
	//todo: two more tests of our choice.
	
	return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "mymalloc.h"
//#define MEMSIZE 4096

//This program is meant to test our malloc and free functions.
int main(int argc, char**argv)
{
	
    // to store the execution time of code
    double time_spent[5][50] = {{0.0}};
    int count = 0;

    while(count!=50){
    clock_t begin = clock();

    //TASK-1 Starts Here
    //malloc() and immediately free() a 1-byte chunk, 120 times.
    for(int i=0;i<120;i++){
        char *p = malloc(1);
        free(p);
    }

    clock_t end = clock();

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent[0][count] += (double)(end - begin) / CLOCKS_PER_SEC;

    begin = clock();

    //TASK-2 Starts Here
    char *q[120];

    //getting 120 1-byte chunks, and storing the pointers in an array.
    for(int i=0;i<120;i++){
        q[i] = malloc(1);
    }

    //Now Deallocating the chunks
    for(int i=0;i<120;i++){
        free(q[i]);
    }

    end = clock();

    time_spent[1][count] += (double)(end - begin) / CLOCKS_PER_SEC;

    begin = clock();

    //TASK-3 Starts Here
    int mallocCount = 0;
    int arrayIndex = 0;
    char *r[120];
    while(mallocCount!=120){
    srand(time(NULL));
    bool randbool = rand() & 1; //Choose either a zero or a one.
        if(randbool){
            r[mallocCount] = malloc(1);
            arrayIndex++;
            mallocCount++;
        }
        else
        {
            if(mallocCount>0)
            free(r[mallocCount]);
        }
    }
    while(arrayIndex > 0){ //Go back and free all the extra allocations that are left over.
        free(r[arrayIndex-1]);
        arrayIndex--;
    }
    end = clock();

    time_spent[2][count] += (double)(end - begin) / CLOCKS_PER_SEC;

 	begin = clock();
	//TASK-4 Starts here.
	char *task4[120];
	
	for(int i = 0; i < 120; i++)
	{
	if(i%2 == 0) //Alternate between 1 sized and 2 sized memory.
		task4[i] = malloc(1);
	else
		task4[i] = malloc(2);
	}
	
	for(int i = 0; i < 120; i++) //Free all memory.
	{
		free(task4[i]);
	}
	end = clock();
	time_spent[3][count] += (double)(end - begin) / CLOCKS_PER_SEC;
	
	
	//TASK-5 Starts here.
	
	begin = clock();
	char *task5[120];
	for(int i = 0; i < 120; i++)
	{
		task5[i] = malloc(1); //Declare all 120 2-byte chunks.
	}
	for(int i = 0; i < 60; i++)
	{
		free(task5[i]); //Free chunk 0 through 59. This is half of the chunks we declared.
	}
	for(int i = 0; i < 60; i++)
	{
		task5[i] = malloc(2); //Declare the first 60 pointers again at size 2. (DOESNT WORK WITH SIZE 5)
	}
	for(int i = 0; i < 120; i++) //Free all memory.
	{
		free(task5[i]);
	}
	
	end = clock();
	time_spent[4][count] += (double)(end - begin) / CLOCKS_PER_SEC;
	
    count++;
}

	printf("\n\n%33s","Time (in seconds)");
	printf("\n--------------------------------------------------");
	printf("\n  %-11s|  %-12s|  %-12s|  %-12s |  %-12s |  %-12s","Trial #","Task#1","Task#2","Task#3","Task#4","Task#5");
	printf("\n--------------------------------------------------");
	
	for(int j=0;j<50;j++)
	{
		printf("\n  %-11d|  %-12.10f  |  %-12.10f  |  %-12.10f | %-12.10f | %-12.10f",j+1,time_spent[0][j],time_spent[1][j],time_spent[2][j], time_spent[3][j], time_spent[4][j]);
		printf("\n--------------------------------------------------");
	}

    double sumTaskTime[5]={0.0};
    double averageTaskTime[5];
    for(int i=0;i<5;i++){
        for(int j=1;j<50;j++){
            sumTaskTime[i] +=  time_spent[i][j];
        }
        averageTaskTime[i] = sumTaskTime[i]/50;
    }

    printf("\n  %-11s|  %-12.10f  |  %-12.10f  |  %-12.10f | %-12.10f | %-12.10f \n","AVERAGE",averageTaskTime[0],averageTaskTime[1],averageTaskTime[2], averageTaskTime[3], averageTaskTime[4]);

	/*

    	printf("MEMSIZE is currently %d.\n", MEMSIZE);
    	printf("The size of the metadata for each block of memory is currently %ld bytes.\n", sizeof(header));
	//Feb23 Lecture Mini-Task 1: Allocate all memory, then try to allocate more.
	printf("\nMini-task 1. Allocating all memory, then try to allocate more...\n");
	char *miniTask1[2];
	
	//Allocate the entire memory, minus space for the metadata.
	//This should work.
	miniTask1[0] = malloc(MEMSIZE-32);
	
	//Try to allocate more. This fails.
	miniTask1[1] = malloc(120);
	
	free(miniTask1[0]);
		
		
	//Feb23 Lecture Mini-Task 2: Allocate more memory than exists in total.
	//printf("Mini-task 2. Allocating more memory than exists in total...");
	//malloc(MEMSIZE + 1); //This fails.
	
	//Feb23 Lecture Mini-Task 3: Free an address outside of the range of our memory. 
	//
	
	//Feb23 Lecture Mini-Task 4: Free an address that isn't at the start of a chunk.
	//
	
	//Feb23 Lecture Mini-Task 5: Free every odd pointer, then try and allocate a chunk that is too large for the remaining space.
	// (CAN DELETE THIS)
*/
    return EXIT_SUCCESS;
}

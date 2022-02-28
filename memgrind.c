#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "mymalloc.h"

//This program is meant to test our malloc and free functions.
int main(int argc, char**argv)
{

    // to store the execution time of code
    double time_spent[5][50] = {{0.0}};
    int count = 0;

    while(count!=50){


    //TASK-1 Starts Here
     clock_t begin = clock();
    //malloc() and immediately free() a 1-byte chunk, 120 times.
    for(int i=0;i<120;i++){
        char *p = malloc(1);
        free(p);
    }

    clock_t end = clock();

    // calculate elapsed time by finding difference (end - begin) and
    // dividing the difference by CLOCKS_PER_SEC to convert to seconds
    time_spent[0][count] += (double)(end - begin) / CLOCKS_PER_SEC;

    begin = clock(); //timer starts

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

    end = clock(); //timer ends

    time_spent[1][count] += (double)(end - begin) / CLOCKS_PER_SEC;

    //TASK-3 Starts Here
    begin = clock();
    int mallocCount = 0;
    int arrayIndex = 0;
    char *r[120];
    while(mallocCount!=120){
    srand(time(NULL));
    bool randbool = rand() & 1; //Choose either a zero or a one.
        if(randbool){ //If it was a 1,
            r[mallocCount] = malloc(1);
            arrayIndex++;
            mallocCount++;
        }
        else //If it was a 0,
        {
            if(mallocCount>0)
            free(r[mallocCount]); //Free the latest chunk.
        }
    }
    while(arrayIndex > 0){ //Go back and free all of the extra allocations that are left over at the end.
        free(r[arrayIndex-1]);
        arrayIndex--;
    }

    end = clock();

    time_spent[2][count] += (double)(end - begin) / CLOCKS_PER_SEC;


	//TASK-4 Starts here.
	begin = clock();
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
		task5[i] = malloc(5); //Declare the first 60 pointers again at size 5.
	}
	for(int i = 0; i < 120; i++) //Free all memory.
	{
		free(task5[i]);
	}

	end = clock();
	time_spent[4][count] += (double)(end - begin) / CLOCKS_PER_SEC;

    count++; //After finishing and recording all 5 tasks, now we move to the next trial.
}
	//Output our elegant scoreboard
	printf("\n\n%58s","Time (in seconds)");
	printf("\n----------------------------------------------------------------------------------------------------");
	printf("\n  %-11s|  %-12s  |  %-12s  |  %-12s |  %-12s|  %-12s","Trial #","Task#1","Task#2","Task#3","Task#4","Task#5");
	printf("\n----------------------------------------------------------------------------------------------------");

	for(int j=0;j<50;j++)
	{
		printf("\n  %-11d|  %-12.10f  |  %-12.10f  |  %-12.10f | %-12.10f | %-12.10f",j+1,time_spent[0][j],time_spent[1][j],time_spent[2][j], time_spent[3][j], time_spent[4][j]);
		printf("\n----------------------------------------------------------------------------------------------------");
	}

    double sumTaskTime[5]={0.0};
    double averageTaskTime[5];
    for(int i=0;i<5;i++){
        for(int j=1;j<50;j++){
            sumTaskTime[i] +=  time_spent[i][j]; //Sum up the time from all fifty tasks,
        }
        averageTaskTime[i] = sumTaskTime[i]/50; // Now calculate all 5 averages.
    }
    //Display the averages here.
    printf("\n  %-11s|  %-12.10f  |  %-12.10f  |  %-12.10f | %-12.10f | %-12.10f \n","AVERAGE",averageTaskTime[0],averageTaskTime[1],averageTaskTime[2], averageTaskTime[3], averageTaskTime[4]);



    	printf("\n\nMEMSIZE is currently %d bytes.\n", MEMSIZE);
    	printf("\nThe size of the metadata for each block of memory is currently %ld bytes.\n", sizeof(header));

	//Feb23 Lecture Mini-Task 1: Allocate all memory, then try to allocate more.
	printf("\nMini-task 1. Allocating all memory, then trying to allocate more...\n");
	char *miniTask1[2];

	//Allocate the entire memory, minus space for the metadata. This works as intended.
	miniTask1[0] = malloc(MEMSIZE-sizeof(header));

	//Try to allocate more space, even though memory is full. This does not work, which is intended.
	miniTask1[1] = malloc(120);

	free(miniTask1[0]);


	//Feb23 Lecture Mini-Task 2: Allocate more memory than exists in total.
	printf("\nMini-task 2. Allocating more memory than exists in total...\n");
	malloc(MEMSIZE + 1); //This fails and produces an error message, as intended.

	//Feb23 Lecture Mini-Task 3: Free an address outside of the range of our memory.
	printf("\nMini-task 3. Freeing an address outside of the range of our memory...\n");
	char* miniTask3 = malloc(1);
	free(miniTask3 + MEMSIZE); //This command fails due to a check in myfree, which is intended.

	free(miniTask3);

	//Feb23 Lecture Mini-Task 4: Free an address that isn't at the start of a chunk.
	printf("\nMini-task 4. Freeing an address that isn't at the start of a chunk...\n");
	char* miniTask4 = malloc(100);

	free(miniTask4 + 2); //Freeing an address in the middle of a chunk does not work, as intended.

	free(miniTask4);

	//Feb23 Lecture Mini-Task 5: Freeing every odd pointer, then trying to allocate a chunk that is too large for the remaining space.
	printf("\nMini-task 5. Free every odd pointer, then try and allocate a chunk that is too large for the remaining space...\n");
	char *miniTask5[128];
	for(int i=0;i<128;i++)
        miniTask5[i] = malloc(16);
    for(int i=0;i<128;i++){
        if(i%2 == 1)
            free(miniTask5[i]);
    }

    //Now we allocate a chunk that is too large for the remaining space. It doesn't work, which is intended.
    char *p = malloc(17);

    //This print statement is included so the compiler doesn't think we declared char *p for no reason and give us an error.
    printf("\nThe value of p is %s\n",p);

    for(int i=0;i<128;i++){ //Now we can free the task 5 demonstration array.
        if(i%2 == 0)
            free(miniTask5[i]);
    }

    return EXIT_SUCCESS;
}

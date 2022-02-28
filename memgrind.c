#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "mymalloc.h"


//This program is meant to test our malloc and free functions.
int main(int argc, char**argv)
{
    // to store the execution time of code
    double time_spent[5][50] = {0.0};
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
    char *r[120];
    while(mallocCount!=120){
    srand(time(NULL));
    bool randbool = rand() & 1;
        if(randbool){
            r[mallocCount] = malloc(1);
            mallocCount++;
        }
        else
        {
            if(mallocCount>0)
            free(r[mallocCount]);
        }
    }
    for(int i=0;i<120;i++){
        free(r[i]);
    }
    end = clock();

    time_spent[2][count] += (double)(end - begin) / CLOCKS_PER_SEC;

    //Stress Tests Pending

    count++;
}

printf("\n\n%33s","Time (in seconds)");
printf("\n--------------------------------------------------");
printf("\n  %-11s|  %-12s|  %-12s|  %-12s","Trial #","Task#1","Task#2","Task#3");
printf("\n--------------------------------------------------");
    for(int j=0;j<50;j++){
            printf("\n  %-11d|  %-12.10f  |  %-12.10f  |  %-12.10f",j+1,time_spent[1][j],time_spent[2][j],time_spent[3][j]);
            printf("\n--------------------------------------------------");
    }

    double sumTaskTime[5]={0.0};
    double averageTaskTime[5];
    for(int i=1;i<3;i++){
        for(int j=1;j<50;j++){
            sumTaskTime[i] +=  time_spent[i][j];
        }
        averageTaskTime[i] = sumTaskTime[i]/50;
    }

    printf("\n  %-11s|  %-12.10f  |  %-12.10f  |  %-12.10f\n","AVERAGE",averageTaskTime[1],averageTaskTime[2],averageTaskTime[3]);

    return EXIT_SUCCESS;
}

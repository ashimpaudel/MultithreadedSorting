#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int sum; /* this data is shared by the thread(s) we create */
void *sorter(void *param); /* threads call this function */
void merge(int low, int high);

int sortArray[] = {99,9,97,23,45,32,904,5,66,60}; //our target array

typedef struct{
    int first;
    int last;
}fLIndices;

int main(int argc, char *argv[]){
    
    pthread_t th1, th2; //declaring two threads, later on we pass the index of two halves of array to each of them
    
    //threads are created by pthread_create function, we need to pass arguements tho this function of type void pointer
    //next step is to create two arguements to pass to each of thread
    
    fLIndices args1, args2;
    
    args1 -> first = 0
    //finding the middle point of the array
    middlePoint = (sizeof(sortArray)/sizeof(sortArray[0]))/2 
    args1 -> last = middlePoint

    args2 -> first = middlePoint + 1;
    args2 -> last = (sizeof(sortArray)/sizeof(sortArray[0])) - 1;
    
    //creating two threads 
    pthread_create(&th1, NULL, mergeSorter, &args1);
    pthread_create(&th2, NULL, mergeSorter, &args2);
    
    void pthread_join(th1, NULL);
    void pthread_join(th2, NULL);
    return 0;

}

void *mergeSorter(void *args){
    int first, last;
    first = ((fLIndices*)args) -> first;
    last = ((fLIndices*)args) -> last;
    mergeSort(arr, first, last);
}


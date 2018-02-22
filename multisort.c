#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *mergeSorter(void *args);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);

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
    int i,middlePoint;
    
    args1.first = 0;
    //finding the middle point of the array
    middlePoint = (sizeof(sortArray)/sizeof(sortArray[0]))/2;
    args1.last = middlePoint;

    args2.first = middlePoint + 1;
    args2.last = (sizeof(sortArray)/sizeof(sortArray[0])) - 1;
    
    //creating two threads 
    pthread_create(&th1, NULL, mergeSorter, &args1);
    pthread_create(&th2, NULL, mergeSorter, &args2);
    
    (void) pthread_join(th1, NULL);
    (void) pthread_join(th2, NULL);
    merge(sortArray,0, middlePoint, (sizeof(sortArray)/sizeof(sortArray[0])) - 1);
    for(i=0; i<10;i++)
        printf("%d,",sortArray[i]);
    return 0;

}

void *mergeSorter(void *args){
    int first, last;
    first = ((fLIndices*)args) -> first;
    last = ((fLIndices*)args) -> last;
    mergeSort(sortArray, first, last);
}

void mergeSort(int arr[], int l, int r){

    if(l<r){
        //same as 1+r/2, but it prevents the overflow when both munbers are large
        int m = l + (r-l)/2;
        //sorting first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        //merging the first and second halves of the array        
        merge(arr,l,m,r);    
    } 
}

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;
    
    //creating temporary arrays for two halves
    int L[n1], R[n2];

    //copying the data to temporary arrays
    for(i=0; i<n1; i++)
        L[i] = arr[l+i];
    for(j=0; j<n2; j++)
        R[j] = arr[m+1+j];

    //merging the temporary arrays back into our original array
    i = 0; //initial index of first temporary subarray
    j = 0; //initail index of second temporary subarray
    k = l; //initial index of merged subarray, using this to access original array

    while(i<n1 && j<n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;        
        }
        k++; //increasing the value of k in each while iteration
    }
    
    while(i<n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k] = R[j];
        j++;
        k++;
    }
  }


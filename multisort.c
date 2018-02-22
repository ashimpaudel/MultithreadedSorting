#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void *mergeSorter(void *args);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);


typedef struct{
    int first;
    int last;
    int* arrayPtr;
}fLIndices;



int main(int argc, char *argv[]){

    //reading the input from file line by line, Usage copied from geline man page: 
    //source: https://linux.die.net/man/3/getline
    int i;    
    FILE *fp;
    char *line = NULL;
    
    size_t len = 0;
    size_t read;

    fp = fopen(argv[1], "r");
    if (fp == NULL){
        printf("no data in input file");
        exit(EXIT_FAILURE);
    }
    while ((read = getline(&line, &len, fp)) != -1){
        //printf("Retrieved line of length %zu \n", read);
        printf("printing original array: \n");
        printf("%s", line);
        char *llc = malloc(strlen(line)+1);
        strcpy(llc, line);
        
        int arrCount = 0;
        char* pch;
        pch = strtok (line," ");

        //counting the number of integers
        while(pch != NULL){
        	arrCount ++;
        	pch = strtok (NULL, " ");
        }

        int sortArray[arrCount];

        pch = strtok (llc," ");
        arrCount = 0;
        while(pch != NULL){
        	sortArray[arrCount] = atoi(pch);
        	arrCount ++;
        	pch = strtok (NULL, " ");
        }

        //multithreaded merge sorting of sortArray
        pthread_t th1, th2; //declaring two threads, later on we pass the index of two halves of array to each of them
    
        //threads are created by pthread_create function, we need to pass arguements tho this function of type void pointer
        //next step is to create two arguements to pass to each of thread
        
        fLIndices args1, args2;
        int i,middlePoint;
        
        args1.first = 0;
        //finding the middle point of the array
        middlePoint = (sizeof(sortArray)/sizeof(sortArray[0]))/2;
        args1.last = middlePoint;
        args1.arrayPtr = sortArray;

        args2.first = middlePoint + 1;
        args2.last = (sizeof(sortArray)/sizeof(sortArray[0])) - 1;
        args2.arrayPtr = sortArray;
        

        //print the part1 of the array, to be sorted by thread1
        printf("part 1 of the array: \n");
        for(i=0; i<middlePoint;i++)
            printf("%d ",sortArray[i]);
        printf("\n");

                //print the part1 of the array, to be sorted by thread1
        printf("part 2 of the array: \n");
        for(i=middlePoint+1; i<(sizeof(sortArray)/sizeof(sortArray[0]));i++)
            printf("%d ",sortArray[i]);
        printf("\n");
        //creating two threads 
        pthread_create(&th1, NULL, mergeSorter, &args1);
        pthread_create(&th2, NULL, mergeSorter, &args2);
        
        (void) pthread_join(th1, NULL);
        (void) pthread_join(th2, NULL);

        merge(sortArray,0, middlePoint, (sizeof(sortArray)/sizeof(sortArray[0])) - 1);
        printf("sorted Array \n");
        for(i=0; i<(sizeof(sortArray)/sizeof(sortArray[0]));i++)
            printf("%d ",sortArray[i]);
        	printf("\n\n");
        
    
    
}
	free(line);
    fclose(fp);
    
    
    return 0;

}

void *mergeSorter(void *args){
    int first, last;
    int* sortArray;
    first = ((fLIndices*)args) -> first;
    last = ((fLIndices*)args) -> last;
    sortArray = ((fLIndices*)args) -> arrayPtr;
    
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


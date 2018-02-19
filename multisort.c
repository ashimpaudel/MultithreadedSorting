#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int sum; /* this data is shared by the thread(s) */
void *sorter(void *param); /* threads call this function */
void merge(int low, int high);

int array[] = {99,9,97,23,45,32,904,5,66,60}; //our target array


//structure to keep the index of array
typedef struct 
{
	int high;
	int low;
}Index;

int main(int argc, char *argv[])
{
	Index in;
	in.low = 0;
	in.high = 10;
    pthread_t thread; /* 3 thread identifier */
    pthread_create(&thread, NULL, sorter, &in); //For last argument pthread_create takes the address of any type
    pthread_join(thread,NULL);
    

    int i;
    for (i = 0; i < 10; i++) printf ("%d ", array[i]);
    return 0;
    
}
/* The thread will begin control in this function */
void *sorter(void *index_info)
{
	Index *ind = (Index *)index_info;
	int mid = (ind->low + ind->high)/2;

	Index nIndex[2];
	pthread_t threads[2];

	nIndex[0].low = ind->low;
	nIndex[0].high = mid;

	nIndex[1].low = mid+1;
	nIndex[1].high = ind->high;

	if (ind->low < ind->high){
		pthread_create(&threads[0], NULL, sorter, &nIndex[0]);
		pthread_create(&threads[1], NULL, sorter, &nIndex[1]);

		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL);

		merge(ind->high, ind->low);

    	pthread_exit(0);

	}

}

void merge(int low, int high){
	int mid = (low+high)/2;
	int left = low;
	int right = mid+1;

	int new_arr[high-low+1];
	int i;
	int curr = 0;

	while(left <= mid && right <= high){
		if (array[left] > array[right])
			new_arr[curr++] = array[right++];
		else
			new_arr[curr++] = array[right++];
	}

	while(left <= mid) 
		new_arr[curr++] = array[left++];
	while(right <= high) 
		new_arr[curr++] = array[left++];
	for (i = 0; i < (high-low+1); i++)
		 array[low+i] = new_arr[i];
		 //printf("%d\n",array[low+i] );




}

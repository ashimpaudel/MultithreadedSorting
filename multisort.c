#include <pthread.h>
#include <stdio.h>

int sum; /* this data is shared by the thread(s) */
void *sorter(void *param); /* threads call this function */

int array[] = {99,98,9,8,7,6,5,4,3,2}; //our target array
int firstlast[2];

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
    pthread_create(&thread, NULL, sorter, &in) //For last argument pthread_create takes the address of any type
    pthread_join(thread,NULL);
    

    /* wait for the thread to exit */
    //pthread_join(tid,NULL);
    printf("sum = %d\n",sum);

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
		pthread_create(&threads[0], NULL, mergesort, &nIndex[0]);
		pthread_create(&threads[1], NULL, mergesort, &nIndex[1]);

		pthread_join(threads[0], NULL);
		pthread_join(threads[1], NULL)

	}
	merge(ind->high, ind->low)

    pthread_exit(0);
}

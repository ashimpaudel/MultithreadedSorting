#include <pthread.h>
#include <stdio.h>

int sum; /* this data is shared by the thread(s) */
void *sorter(void *param); /* threads call this function */

int array[10] = {99,98,9,8,7,6,5,4,3,2};
int firstlast[2];

int main(int argc, char *argv[])
{
    pthread_t tid[3]; /* 3 thread identifier */
    pthread_attr_t attr; /* set of thread attributes */

    
    /* get the default attributes */
    pthread_attr_init(&attr);
    /* create the thread */
    firstlast[0]= 0;
    firstlast[1] = 4;
    pthread_create(&tid[0], &attr, sorter, firstlast);
    firstlast[0] = 5;
    firstlast[1] = 9;
    pthread_create(&tid[1], &attr, sorter, firstlast);

    /* wait for the thread to exit */
    pthread_join(tid,NULL);
    printf("sum = %d\n",sum);

}
/* The thread will begin control in this function */
void *sorter(int firstlast[])
{
	int i,j,temp,k;
	printf("printing the array before sorting\n");
	for (int i = firstlast[0]; i < firstlast[1]; ++i)
	{
		printf("%d",array[i] );
	}
	printf("\n");

    for(i=firstlast[0]; i< firstlast[1]; i++)
    {
        for(j= i+1; j<first1ast[1]; j++)
        {

            if(array[i] > array[j])
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;

            }
        }
    }
    printf("printing the array after sorting\n", );
	for (int i = firstlast[0]; i < firstlast[1]; ++i)
	{
		printf("%d",array[i] );
	}
	printf("\n");
    //code to sort a array

    pthread_exit(0);
}

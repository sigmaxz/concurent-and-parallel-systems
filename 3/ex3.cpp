#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 6

/*
* The bug was that where passing t and having a race conditon on it 
*/
void *PrintHello(void *threadid)
{
	long taskid = *(long*)threadid;
	free(threadid);
	sleep(1);
	printf("Hello from thread %ld\n", taskid);
	pthread_exit(NULL);
	
}

int main()
{
	pthread_t pthreads[NUM_THREADS];
	int rc;
	long t;

	for(t = 0; t < NUM_THREADS; t++)
	{
		printf("creating thread %ld\n",t);
		long* temp = (long*)malloc(sizeof(long));
		*temp = t;
		rc = pthread_create(&pthreads[t],NULL, PrintHello, (void *) temp);
		if(rc)
		{
			printf("err");
			exit(-1);
		}
	}

	pthread_exit(NULL);
}

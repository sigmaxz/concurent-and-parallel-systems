/*
 * hello world program
 *  arg: a number for threads
 *  output: each thread will print "hello world"
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *vargp)
{
	printf("hello world\n");
	return NULL;
}

int main()
{
	int nthreads ;
	
	printf("number of threads wanted? :");
	scanf("%d", &nthreads);
	
	pthread_t tid[nthreads];
	for(int i = 0; i < nthreads; i++)
	{
		pthread_create(&tid[i] , NULL, thread, NULL);
	}
	for( int j = 0 ; j < nthreads; j++)
	{
		pthread_join(tid[j],NULL);
	}
	
	return 0;
}

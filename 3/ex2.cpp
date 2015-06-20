/*
* what was happening was that the main was exiting before the thread woke up
* fix: waited for the thread created to finish before exiting main
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *thread(void *vargp);

int main()
{
	pthread_t tid;
	
	pthread_create(&tid, NULL, thread, NULL);
// 
	pthread_join(tid, NULL);
//
	exit(0);
}

void *thread(void *vargp)
{
	sleep(1);
	printf("Hello, world!\n");
	return NULL;
}


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

using namespace std;
const int arr1Col = 12;
const int arr1Row = 12;
const int arr2Col = 12;
const int arr2Row = 12;

// allows only one writer at a time
sem_t mutex;
sem_t read;
sem_t write;
int buf[2];



/* this is arr1  a 5x5
*	2 3 1 6 7 1
*	3 8 4 6 1 2
*	3 7 9 4 5 3
*	3 5 1 2 3 4	
*	1 7 4 8 3 5
*  4 6 3 7 2 8
*/
const int arr1[144] = { 2 , 3 , 1 , 6, 7,1, 3 , 8 , 4, 6 , 1,2, 3, 7, 9, 4, 5,3, 3, 5, 1, 2, 3, 4, 1, 7, 4, 8, 3,5 , 4, 6, 3, 7, 2, 8 ,2 , 3 , 1 , 6, 7,1, 3 , 8 , 4, 6 , 1,2, 3, 7, 9, 4, 5,3, 3, 5, 1, 2, 3, 4, 1, 7, 4, 8, 3,5 , 4, 6, 3, 7, 2, 8, 2 , 3 , 1 , 6, 7,1, 3 , 8 , 4, 6 , 1,2, 3, 7, 9, 4, 5,3, 3, 5, 1, 2, 3, 4, 1, 7, 4, 8, 3,5 , 4, 6, 3, 7, 2, 8, 2 , 3 , 1 , 6, 7,1, 3 , 8 , 4, 6 , 1,2, 3, 7, 9, 4, 5,3, 3, 5, 1, 2, 3, 4, 1, 7, 4, 8, 3,5 , 4, 6, 3, 7, 2, 8};

/* this is arr2 a 5x5 
*	3 4 2 7 5 2
*	2 5 1 7 5 4
*	3 9 5 9 7 6
*	4 5 2 5 6 7
*	0 1 2 7 0 3
*  3 4 5 6 7 8 
*/
const int arr2[144] = { 3, 4, 2, 7, 5,2, 2, 5, 1, 7, 5,4, 3, 9, 5, 9, 7,6,4, 5, 2, 5, 6,7,0, 1, 2, 7, 0,3,3, 4, 5, 6, 7, 8,3, 4, 2, 7, 5,2, 2, 5, 1, 7, 5,4, 3, 9, 5, 9, 7,6,4, 5, 2, 5, 6,7,0, 1, 2, 7, 0,3,3, 4, 5, 6, 7, 8 ,3, 4, 2, 7, 5,2, 2, 5, 1, 7, 5,4, 3, 9, 5, 9, 7,6,4, 5, 2, 5, 6,7,0, 1, 2, 7, 0,3,3, 4, 5, 6, 7, 8 ,3, 4, 2, 7, 5,2, 2, 5, 1, 7, 5,4, 3, 9, 5, 9, 7,6,4, 5, 2, 5, 6,7,0, 1, 2, 7, 0,3,3, 4, 5, 6, 7, 8   };

int ans[25];
// check dimensions of matrices to check for size validity 
int validmult()
{
	if( arr1Col == arr2Row) return 1;
	return 0;
}

/*
*	this function is the math behind finding one elem in the answer 
*/
void *calc(void *vargp)
{
  sem_wait(&read);
  int row= buf[0];
  int col= buf[1];
  sem_post(&write);
  int total = 0;
  for(int i = 1; i <= arr1Row ; i++)
  {
   total += arr1[(arr1Row *(row-1))+(i-1)] * arr2[(col-1)+(arr1Row*(i-1))];
  }
  sem_wait(&mutex);
  ans[((row-1)*arr1Row)+(col-1)] = total;
  sem_post(&mutex);
  return NULL;
}

void *serve(void *vargp)
{
int i;
int j;
for(i = 1 ; i<=arr1Row; i++)
	{
		for(j = 1; j<=arr1Row; j++)
		{
		  sem_wait(&write);
		  buf[0]=i;
		  buf[1]=j;
		  sem_post(&read);
		}
	}
return NULL;

}

/*
*	prints out matrix 
*/
void printar(const int* ans)
{
  for(int i = 1; i <= arr1Row* arr1Row; i++)
  {
    printf(" %d", ans[i-1]);
    if(i % arr1Row == 0) printf("\n");
  }
}

int main()
{

	int threads = arr1Row * arr1Row;
	pthread_t tid[threads];
	int i;
	int j;
	int q;
	int numt = 0;

	//init sema
	sem_init(&mutex, 0, 1);
   sem_init(&read,0,0);
	sem_init(&write,0,1);


	// check if this mult is allowable
	if( validmult()== 0 )
	{
		printf("not valid size matrices");
	}
	pthread_t ser;
	pthread_create(&ser,NULL,serve, NULL);
	for(i = 1, q= 0 ; i<=arr1Row; i++)
	{
		for(j = 1; j<=arr1Row; j++, numt++, q++)
		{
		  pthread_create(&tid[q],NULL,calc,NULL);
		}
	}
	for(int z = 0; z < threads; z++)
	{
		pthread_join(tid[z],NULL);
	}
	pthread_join(ser,NULL);
	printar(ans);

	exit(0);
}

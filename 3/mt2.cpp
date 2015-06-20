/* Name: Samuel Villarreal
 * Email: svill017@ucr.edu
 * Date: Feb 2014
 * Project: multithreaded matrix multilication
 * Description: case study of pthread on 1000x1000 matrices 
 * 
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

// contains pre-defined matrices to be multiplied
#include "mat.h"

using namespace std;
// matrix specifications 
const int arr1Col = 1000;
const int arr1Row = 1000;
const int arr2Col = 1000;
const int arr2Row = 1000;
const int td = 4; // the number of threads utilized 

// allows only one writer at a time
sem_t mutex;

float ans[1000000];


// check dimensions of matrices to check for size validity 
int validmult()
{
	if( arr1Col == arr2Row) return 1;
	return 0;
}

void calc(const int row,const int col)
{
  float total = 0;
  for(int i = 1; i <= arr1Row ; i++)
  {
   total += arr1[(arr1Row *(row-1))+(i-1)] * arr2[(col-1)+(arr1Row*(i-1))]; 
  }
  sem_wait(&mutex);
  ans[((row-1)*arr1Row)+(col-1)] = total;
  sem_post(&mutex);
}

/*
*	this function is the math behind finding one elem in the answer 
*/
void *split(void *vargp)
{
  int i= *((int*)vargp);
  int j= *((int*)(vargp)+1);
  free(vargp);
  
  for(; ( (i<=j)  || ( (i + (arr1Row/4) > arr1Row) && (i > (arr1Row -(arr1Row/4)))))&& (i <= arr1Row); i++)
	{
		int q= 1;
		for(; q<=arr1Row; q++)
		{
		  calc(i, q);
		}
	}
  return NULL;
}


/*
*	prints out matrix 
*/
void printar(const float* ans)
{
  for(int i = 1; i <= arr1Row* arr1Row; i++)
  {
    printf(" %f", ans[i-1]);
    if(i % arr1Row == 0) printf("\n");
  }
}

int main()
{
	pthread_t tid[td];
	int i;
	int q;

	//init sema
	sem_init(&mutex, 0, 1);

	// check if this mult is allowable
	if( validmult()== 0 )
	{
		printf("not valid size matrices");
	}
	for(i = 1, q= 0 ; i<= td; i++, q++)
	{
		  int *serv = (int *)malloc(sizeof(int) * 2);
		  *serv = 1 +((i-1)* (arr1Row/4)) ;
		  *(serv+1) = (i * (arr1Row/4));
		  pthread_create(&tid[q],NULL,split,serv);
	}
	for(int z = 0; z < td ; z++)
	{
		pthread_join(tid[z],NULL);
	}
	printar(ans);

	exit(0);
}

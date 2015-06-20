#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

using namespace std;
const int arr1Col = 1000;
const int arr1Row = 1000;
const int arr2Col = 1000;
const int arr2Row = 1000;
// check dimensions of matrices to check for size validity 
int validmult()
{
	if( arr1Col == arr2Row) return 1;
	return 0;
}

/*
*	this function is the math behind finding one elem in the answer 
*/
void calc(float* ans,const int row,const int col)
{
  float total = 0;
  for(int i = 1; i <= arr1Row ; i++)
  {
   total += arr1[(arr1Row *(row-1))+(i-1)] * arr2[(col-1)+(arr1Row*(i-1))]; 
  }
  ans[((row-1)*arr1Row)+(col-1)] = total;
}

/*
*	prints out matrix 
*/
void printar(const float* ans)
{
  for(int i = 1; i <= arr1Row*arr1Row; i++)
  {
    printf(" %f", ans[i-1]);
    if(i % arr1Row == 0) printf("\n");
  }
}

int main()
{

float Ans[arr1Row*arr1Row];

	if( validmult()== 0 )
	{
		printf("not valid size matrices");
	}
	int i;
	int j;
	for(i =1 ; i<=arr1Row; i++)
	{
		for(j = 1; j<=arr1Row; j++)
		{
		  calc(Ans, i, j);
		}
	}
	printar(Ans);

	exit(0);
}

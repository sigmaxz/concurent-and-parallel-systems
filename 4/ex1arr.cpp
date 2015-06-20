#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

using namespace std;

const static int space = 8;
const static int numT = 48;
const static long num_steps = 100000;
const static double step = 1.0/(double) num_steps;
static double arr[numT*numT] = {0};

void printa(double *arr)
{
  int i;
  for(i= 0; i < numT; i++)
  {
    printf("%f |", arr[i* space]);	
  }	
}

int main()
{
	omp_set_num_threads(numT);
	double pi = 0;
	double tstart, tend;
	tstart = omp_get_wtime();
	#pragma omp parallel
	{
	
	int id;
	int Nthreads;
	double istart;
	double iend;
	id = omp_get_thread_num();
	Nthreads = omp_get_num_threads();
	istart = (((double)id* (double)num_steps)/ (double)Nthreads);
	iend =   (((double)(id+1)*(double)num_steps) / (double)Nthreads);
	if( id == Nthreads-1){
		 iend = num_steps;
	}
	double x;
	int i;
	for(i = (int)istart; i < (int)iend; i++){
		x = ((double) i + 0.5)*step ;	
		arr[space*id] = arr[space*id] +  4.0/(1.0 + x* x);
	}
	}
	tend = omp_get_wtime();
	printf("time: %f\n",tend-tstart);
	int j;
	double sum;
	//printa(arr);
	for(j= 0; j < numT; j++)
	{
		sum = sum + arr[j*space]; 	
	}
	pi = (1.0/(double)num_steps) * sum;
	printf("(%f)\n", pi);	
	return 0;
}

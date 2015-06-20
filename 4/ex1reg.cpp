#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SPACE 8;
static long num_steps = 100000000;
const double step = 1.0/(double)num_steps;

int main()
{
	int i;
	double sum = 0, tstart, tend,pi;
	tstart = omp_get_wtime();
	#pragma omp parallel
	{
	int id = omp_get_thread_num();
	int Nthreads = omp_get_num_threads();
	double istart = (((double)id* (double)num_steps)/ (double)Nthreads);
	double iend =   (((double)(id+1)*(double)num_steps) / (double)Nthreads);
	if( id == Nthreads-1){
		 iend = num_steps;
	}
	int i;
	double x;
	double tsum = 0;
	for(i= (int)istart; i < (int)iend; i++){
		x = ( i + 0.5)*step ;
		tsum = tsum +  4.0/(1.0 + x* x);
	}
	#pragma omp critical 
	  sum += tsum;
	}
	tend = omp_get_wtime();
	printf( "time: %f\n", tend-tstart);
	int j;
	pi = step * sum;
	printf("(%f)\n", pi);	
	return 0;
}


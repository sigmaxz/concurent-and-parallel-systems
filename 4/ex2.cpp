#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

const static long num_steps = 100000000;
double step;

int main()
{
	int i;
	double x, pi, sum = 0.0 , tstart, tend;
	
	step = 1.0/ (double)num_steps;	

	tstart = omp_get_wtime();
	#pragma omp parallel for reduction(+:sum) 
	for(i= 0; i < num_steps; i++){
		x = ( i + 0.5)*step ;
		sum = sum +  4.0/(1.0 + x* x);
	}
	tend = omp_get_wtime();
	printf("time: %f \n",tend-tstart);

	pi = step * sum;
	printf("(%f)\n", pi);	
	return 0;
}


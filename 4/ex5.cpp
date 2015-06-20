#include "stdlib.h"
#include "stdio.h"
#include "omp.h"

int main()
{
	omp_set_num_threads(4);
	int a=1, b=2, c=3 , d=4;
//	#pragma omp parallel private(b) firstprivate(c) lastprivate(d)
	{
		printf( "%d %d %d %d %d\n", a,b,c,d, omp_get_thread_num());
	}
	
	return 0;
}

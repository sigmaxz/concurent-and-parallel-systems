/*
**  PROGRAM: Matrix Multiply
**
**  PURPOSE: This is a simple matrix multiply program. 
**           It will compute the product
**
**                C  = A * B
**
**           A and B are set to constant matrices so we
**           can make a quick test of the multiplication.
**
**  USAGE:   Right now, I hardwire the martix dimensions. 
**           later, I'll take them from the command line.
**
**  HISTORY: Written by Tim Mattson, Nov 1999.
*/
#include <malloc.h>
#include <stdio.h>
#include <omp.h>

#define ORDER 1000
#define AVAL 3.0
#define BVAL 5.0
#define TOL  0.001
double *A, *B, *C;

int main(int argc, char **argv)
{
	int Ndim, Pdim, Mdim;   /* A[N][P], B[P][M], C[N][M] */
	double cval, err, errsq;
	int i,j,k;
      double dN, mflops;
	double start_time, run_time;


	Ndim = ORDER;
	Pdim = ORDER;
	Mdim = ORDER;

   	A = (double *)malloc(Ndim*Pdim*sizeof(double));
      B = (double *)malloc(Pdim*Mdim*sizeof(double));
      C = (double *)malloc(Ndim*Mdim*sizeof(double));

	/* Initialize matrices */

	for (i=0; i<Ndim; i++)
		for (j=0; j<Pdim; j++)
			*(A+(i*Ndim+j)) = AVAL;

	for (i=0; i<Pdim; i++)
		for (j=0; j<Mdim; j++)
			*(B+(i*Pdim+j)) = BVAL;

	for (i=0; i<Ndim; i++)
		for (j=0; j<Mdim; j++)
			*(C+(i*Ndim+j)) = 0.0;

	/* Do the matrix product */
	start_time = omp_get_wtime();
	#pragma omp parallel
	{
	double tmp;
	int i2,j2,k2;
	int id = omp_get_thread_num();
	int Nthreads = omp_get_num_threads();
	int istart = id * Ndim/ Nthreads;
	int iend = (id+1)*Ndim/ Nthreads;
	if(id == Nthreads-1) iend = Ndim;
	for (i2=istart; i2< iend; i2++){
		for (j2=0; j2<Mdim; j2++){
			tmp = 0.0;
			for(k2=0;k2<Pdim;k2++){
				/* C(i,j) = sum(over k) A(i,k) * B(k,j) */
				tmp += *(A+(i2*Ndim+k2)) *  *(B+(k2*Pdim+j2));
			}
			*(C+(i2*Ndim+j2)) = tmp;
		}
	}
	}
	/* Check the answer */

	run_time = omp_get_wtime() - start_time;
 
	printf(" Order %d multiplication in %f seconds \n", ORDER, run_time);

      dN = (double)ORDER;
      mflops = 2.0 * dN * dN * dN/(1000000.0* run_time);
 
	printf(" Order %d multiplication at %f mflops\n", ORDER, mflops);

	cval = Pdim * AVAL * BVAL;
	errsq = 0.0;
	for (i=0; i<Ndim; i++){
		for (j=0; j<Mdim; j++){
			err = *(C+i*Ndim+j) - cval;
		    errsq += err * err;
		}
	}

	if (errsq > TOL) 
		printf("\n Errors in multiplication: %f",errsq);
	else
		printf("\n Hey, it worked");

	printf("\n all done \n");
}
#include "stdlib.h"
#include "stdio.h"
#include "omp.h"

int MAX = 100;
static int j;

int comp(int j)
{
 return j;
}

void Printa(int *a)
{
  int i;
  for(i=0; i < MAX; i++)
  {
	printf("%d ",a[i]);
	if(i % 10 == 0 && i != 0) printf("\n");
  }
}

int main()
{
  int i,*a;
  a = (int*)malloc(sizeof(int)*MAX);
  j=1;
  #pragma omp parallel for
  for (i=0; i<MAX; i++) {
    #pragma omp critical
    {
    j=j+2;
    
    a[i]=comp(j);
    }
  }
  Printa(a);
  return 0;
}

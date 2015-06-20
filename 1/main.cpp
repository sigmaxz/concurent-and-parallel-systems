#include <iostream>
#include <stdio.h>
#include <sys/wait.h> 

using namespace std;

void doit()
{
////	fork();
	if(fork() == 0){
		fork();
		printf("hello\n");
		return;
	}
	return;
}

	int counter = 1 ;

int main()
{
//	int i;
//	for(i = 0; i <2; i++)
//		fork();
//	doit();
////	if(fork() != 0)
///		printf("x=%d\n", ++x);

	if(fork() == 0){
		counter--;
		exit(0);
	}
	else{
		wait(NULL);
		printf("counter = %d\n", ++counter);
	}

////	printf("hello\n");
	exit(0);
}

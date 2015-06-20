#include <iostream>
#include <stdio.h>

using namespace std;

int count = 0;

void add1()
{
	count= count +1;
}


int main()
{
	fork(add1);
	return 0;
}


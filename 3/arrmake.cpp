#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

/* small program to generate 1000000 numbers for float array mult*/
int main()
{
	srand(time(NULL));
	 
	for( int i = 0; i < 1000000 -1; i++)
	{
		cout << rand() %9 << ",";
          if((i != 0) && (i% 1000 == 0)) cout << endl;
	}
	cout << rand()%9;
	return 0;
}

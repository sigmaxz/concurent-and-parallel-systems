#include <stdio.h>
#include <iostream>

using namespace std;

void foo(int n)
{
	int i;
	for(i = 0; i < n; i++)
		fork();
	printf("hello\n");
	exit(0);
}

int main()
{
	int n = 0;
	cout << "give an n:" << endl;
	cin >> n;
	foo(n);
	exit(0);
}

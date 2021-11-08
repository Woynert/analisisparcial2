//#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;


int
factorial (vector<int>* fact, int n)
{
	printf("Called\n");

	//resize storage
	if (fact->size () <= n)
		fact->resize (n+1);

	//check it exists
	if ((*fact)[n] != 0)
		return (*fact)[n];

	//calculate
	else
	{
		if (n <= 1)
			(*fact)[n] = 1;
		else
			(*fact)[n] = n * factorial(fact, n-1);

		return (*fact)[n];
	}
	return 0;
}

int
main()
{
	vector<int>* fact = new vector<int>();
	int n;

	printf ("Factorial number calculator. Type -1 to exit.\n\n");

	do
	{
		//input
		printf (">> ");
		scanf ("%i", &n);

		if (n < 0)
			break;

		//compute
		factorial(fact, n);

		printf ("%i : Storage size: %i \n\n", (*fact)[n], fact->size());
	}
	while (n >= 0);

	return 0;
}

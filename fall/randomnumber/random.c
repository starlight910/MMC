#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Random Numbers Generater Program

int lcg(int seed)
{
	int a;
	int c;
	int m;

	a = 5;
	c = 1;
	m = 19;

	seed = ( a * seed + c ) % m ;

	return seed;
}

int main(void)
{
	int i;
	int seed;
	int N;

	N = 20;     // Number of random numbers
	seed = 18;

	for( i = 0; i < N; i++ )
	{
		seed = lcg(seed);
		printf("%d ",seed);
	}

	printf("\n");

	return 0;
}


#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Random Numbers Generater Program + Input Numbers

int lcg(int seed, int a, int c, int m)
{
	seed = (a * seed + c ) %m ;

	return seed;
}

int main(int argc, char *argv[])
{
	int a;
	int c;
	int m;
	int i;
	int seed;
	int N;

	if(argc != 6)
	{
		printf("%s Input: A, C, M, N, Seed\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	a = atof(argv[1]);
	c = atof(argv[2]);
	m = atof(argv[3]);
	N = atof(argv[4]);
	seed = atof(argv[5]);

	for(i = 0; i < N; i++ )
	{
		seed = lcg(seed,a,c,m);
		printf("%d ",seed);
	}
	printf("\n");

	exit(EXIT_SUCCESS);

	return 0;
}


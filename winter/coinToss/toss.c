#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	int tpss;
	double val;

	srand(time(NULL));
	val = (double)rand()/RAND_MAX;
	printf("%f\n", val);

	if (val < 0.4)
	{
		printf("T\n");
	}
	else
	{
		printf("H\n");
	}
	return 0;
}


#include<stdio.h>
#include<randata.h>

float rdata[];

int main()
{
	double MAX;
	double MIN;
	int i;

	for(i = 0; i < MAX_NUMBERS; i++)
	{
	if(rdata[i] > MAX)
		MAX = rdata[i];
	if(rdata[i] < MIN)
		MIN = rdata[i];
	}


printf("Max %f Min%f\n", MAX, MIN);
}

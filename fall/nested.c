#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int i;
	int j;
	char *star = "*";
	int size = 0;

	if(argc == 2)
		size = atoi(argv[1]);

	for(i=3; i > size; i--)
	{
		for(j=0; j < i; j++)
		{
			printf("%s", star);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

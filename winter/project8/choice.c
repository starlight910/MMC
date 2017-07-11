#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main()
{
	srand ( time(NULL) ); //initialize the random seed

short sound[] = {1, 2, 3, 4, 5, 6, 7, 8};
int random = rand() % 8;
printf("%d\n", sound[random]);

	return 0 ;

}


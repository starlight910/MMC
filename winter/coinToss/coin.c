#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main(int argc, char *argv[])
{
	double value;
	char coinFace[5] ;

	if ( argc != 2 )
	{
		printf("%s: Coin tossed. Head or Tail?\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	strncpy(coinFace, argv[1], 4) ;

	srand(time(NULL));
	value = (double)rand()/RAND_MAX;
	printf("%f\n", value);

	if (value < 0.5) {
		if ( strncmp(coinFace, "head", 4) == 0 ) {
			fprintf(stderr,"Correct!!\n");
		}
	} else {
		if (strncmp(coinFace, "tail", 4) == 0 ) {
			fprintf(stderr,"Not lucky guy eh?\n");
		}
	}

	return 0 ;
}



#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char *argv[])
{
	int t;  //left bottle
	int bottle;
	int fall;
	char answer[128] ;

	/*
	if ( argc != 3)
	{
		printf("%s How many bottle on the wall? and How many fall?\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	*/

	fprintf(stderr,"How many bottles? ") ;
	fgets(answer, sizeof(answer), stdin) ;
	bottle = atof(answer) ;

	fprintf(stderr,"How many bottles will fall? ") ;
	fgets(answer, sizeof(answer), stdin) ;
	fall = atof(answer) ;

	fprintf(stderr,"%d Bottles of beer on the wall\n",bottle);
	fprintf(stderr,"%d Bottles of beer fall\n",fall);

	t = bottle - fall ;
	
	fprintf(stderr,"%d Bottles left one the wall\n",t);
	exit(EXIT_SUCCESS);
}



#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int plinko1(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;

	int i=0 ;

	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}
int plinko2(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;
}

int plinko3(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}
int plinko4(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}
int plinko5(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}
int plinko6(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}
int plinko7(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}
int plinko8(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}

int plinko9(int random) 
{
	double cdf[] = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 8.0, 1.0} ;
	srand(time(NULL)) ;
	double val = (double)rand()/RAND_MAX;

	int i=0 ;

	while (val > cdf[i]) {
		i++ ;
		random = i ;

	}

	return random ;

}

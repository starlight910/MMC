#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

//
//	RANDOM_SEED : the number that starts the pseudo-random sequence
//

static int RANDOM_SEED = 950208 ;			// my son's birthday

//
//	setRandomSeed(int newSeed)
//
//	sets 'newSeed' as the start of the pseudo-random sequence
//

void setRandomSeed(int newSeed)
{
	extern int RANDOM_SEED ;	// current seed
	RANDOM_SEED = newSeed ;		// set the current seed to the new seed
	return ;
}

//
//	irandom(void)
//	
//	this is the pseudo-random number generator, 
//	called by 'frandom()'
//
//	returns a pseudo random number between 0 and 2^31
//

int irandom(void)         // Linear Congruential Generator
{
	extern int RANDOM_SEED ;
    const int m = 2147483648 ;      // 2^31 (max length of sequence)
    const int a = 1103515245 ;		// the numbers for 'a' and 'c' are
    const int c = 12345 ;			// used by the UNIX/BSD OS
    
	RANDOM_SEED = ( a * RANDOM_SEED + c ) % m ;

	if ( RANDOM_SEED < 0 )			// make sure seed is positive
		RANDOM_SEED += m ;

    return RANDOM_SEED ;
}

//
//	frandom() : returns a pseudo-random floating point number between 0 and 1
//	it calls irandom() to generate a pseudo random integer.
//	it then divides the received integer by the maximum it
//	could be (2^31), and so creates a floating point number between 0
//	and 1.
//

double frandom(void)
{
	const double M = 2147483648.0 ;	// 2^31
	int I ;
	I = irandom() ;		// get a pseudo random integer
	return I / M ;		// divide by the maximum that integer could be
}



//
//	rescale(array[], N, ymax, ymin)
//
//	scales all the values in the array 'array' to be exactly beteen
//	ymin and ymax.
//
//

static void rescale(double array[], int N, double ymax, double ymin)
{
	double scale, xmax, xmin ;
	int i ;

	//	ymax, ymin = desired min/max values
	//	xmax, xmin = current min/max values

	xmax = xmin = array[0] ;		// find the current min/max values 
	for ( i = 1 ; i < N ; i++ ) {
		if ( array[i] > xmax ) 
			xmax = array[i] ;
		else if ( array[i] < xmin ) 
			xmin = array[i] ;
	}

	//
	//  function used:
	//	y(n) = (ymax-ymin)/(xmax-xmin) * (x(n) - xmin) + ymin ;
	//

	// set the scale factor
	scale = ( ymax - ymin ) / ( xmax - xmin ) ;

	// rescale all the values to have ymin and ymax as the limits
	for ( i = 0 ; i < N ; i++ )
		array[i] = scale * ( array[i] - xmin ) + ymin ;

	return ;
}


//
//	whiteNoise(sound[], dur, srate, dB)
//
//	generates white noise for 'dur' seconds, at 'dB' amplitude
//

void whiteNoise(short sound[], double dur, int sr, double dB)
{
	double Amax, Amin, *noise ;
	int samples, t ;

	samples = dur * sr ;	// translate seconds to samples
	noise = (double *)Malloc(samples * sizeof(double)) ;

	Amax = pow(10.0, dB/20.0) / 2 ;	// translate from dB to linear
	Amin = -Amax ;

	//	create a set of pseudo random numbers between Amax and Amin
	for ( t = 0 ; t < samples ; t++ ) 
		noise[t] = (Amax - Amin) * frandom() + Amin ;

	// 'stretch' the values to be exactly between Amax and Amin
	rescale(noise, samples, Amax, Amin) ;

	// copy to the short array
	for ( t = 0 ; t < samples ; t++ )
		sound[t] = noise[t] ;

	Free(noise) ;	// no longer needed.

	return ;
}

//
//	randomArray(max, min, N)
//
//	return an array of length 'N' with values between 'min' and 'max'
//

double *randomArray(
	double max, double min,		// limits for the data
	int N)						// the number of items
{
	int i, j, repeat ;
	double tmp, *array, R ;

	if ( max < min ) {		// swap values if needed
		tmp = max ;
		max = min ;
		min = tmp ;
	}

	// allocate memory for this array
	array = (double *)Malloc(N * sizeof(double)) ;

	// load the array with unique values between min and max
	for ( i = 0 ; i < N ; i++ ) {
		do {
			R = (max - min) * frandom() + min ;		// get test value
			repeat = 0 ;
			for ( j = 0 ; j < i ; j++ ) {	// check if value exists in array
				if ( R == array[j] ) {
					repeat = 1 ;				// value found! repeat
					break ;
				}
			}
		} while ( repeat == 1 ) ;
		array[i] = R ;
	}

	// scale the array to make limits EXACTLY at min and max
	rescale(array, N, max, min) ;			// scale the array

	return array ;
}

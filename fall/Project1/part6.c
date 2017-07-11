#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part6nTones = 12 ;			// number of tones in part 1
static double part6dur[] = {0.3, 0.2, 0.2, 0.3, 0.2, 0.2, 0.3, 0.2, 0.2, 0.3, 0.2, 0.2} ;    //duration of each tones


double getPart6Dur(void)
{
	double td = 0 ;
	int i ;

	for ( i = 0 ; i < part6nTones ; i++ )
		td += part6dur[i] ;

	return td ;
}

short *part6(int sr)
{
	//
	//	set the data for the partials
	//
	int nPartials = 7 ;		// total number of partials
	double partialF[] = {1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4} ;	// partial freq
	double partialA[] = {1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4} ;	// partial amp

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 5 ;
	double T[] = {0.0, 0.1, 0.25, 0.75, 1.0} ;
	double A[] = {0.0, 1.0, 0.80, 0.40, 0.0} ;
	int flag = 0 ;

	double F[] = {440, 415.30, 415.30, 415.30, 369.99, 369.99, 369.99, 329.63, 329.63, 329.63, 311.13, 311.13} ;		// fundamental frequency
	double dB = 70 ;		// starting amplitude

	short *sound,			// array for each individual tone
		  *output ;			// array for the sequence of tones
	double totalDuration,	// total duration of the tones
		   maxDur,			// max duration of an individual tone
		   st ;				// start time for each tone
	int i ;					// counter


	totalDuration = getPart6Dur() ;

	maxDur = 0 ; // initialize maxDur to zero
	for ( i = 0 ; i < part6nTones ; i++ ) {	
		if ( part6dur[i] > maxDur )			// find the maxDur
			maxDur = part6dur[i] ;
	}

	// allocate memory for the arrays
	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;


	st = 0 ;		// initialize start time to zero
	for ( i = 0 ; i < part6nTones ; i++ ) {		// loop to generate the tones

		addsyn(sound, part6dur[i], sr, F[i], dB, partialF, partialA, nPartials) ;
		adsr2(sound, part6dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part6dur[i], sr) ;

		st += part6dur[i] ;	// increment the start time

	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

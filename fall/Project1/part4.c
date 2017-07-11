#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part1nTones = 40 ;			// number of tones
static double part4dur[] = {1, 0.9, 0.5, 0.5, 1, 1, 0.9, 0.5, 0.5, 1, 1, 0.9, 0.5, 0.5, 1, 1, 0.9, 0.5, 0.5, 1, 1, 0.9, 0.5, 0.5, 1, 1, 0.9, 0.5, 0.5, 1, 1, 0.9, 0.5, 0.5, 1, 1, 0.9, 0.5, 0.5, 1} ;    //duration of each tones


double getPart4Dur(void)
{
	double td = 0 ;
	int i ;

	for ( i = 0 ; i < part1nTones ; i++ )
		td += part4dur[i] ;

	return td ;
}

short *part4(int sr)
{
	//
	//	set the data for the partials
	//
	int nPartials = 5 ;		// total number of partials
	double partialF[] = {1.0, 2.9, 0.8, 3.7, 0.6} ;	// partial freq
	double partialA[] = {1.0, 1.0, 1.0, 1.0, 1.0} ;	// partial amp

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 2 ;
	double T[] = {0.0, 1.0} ;
	double A[] = {0.0, 1.0} ;
	int flag = 0 ;

	double F[] = {138.59, 277.18, 138.59, 138.59, 277.18, 130.81, 277.18, 130.81, 130.81, 277.18, 123.47, 277.18, 123.47, 123.47, 277.81, 116.54, 233.08, 116.54, 116.54, 233.08, 110, 220, 110, 110, 220, 103.83, 207.65, 103.83, 103.83, 207.65, 98, 196, 98, 98, 196, 103.83, 207.65, 103.83, 103.83, 207.65} ;		// fundamental frequency
	double dB = 110 ;		// starting amplitude

	short *sound,			// array for each individual tone
		  *output ;			// array for the sequence of tones
	double totalDuration,	// total duration of the tones
		   maxDur,			// max duration of an individual tone
		   st ;				// start time for each tone
	int i ;					// counter


	totalDuration = getPart4Dur() ;

	maxDur = 0 ; // initialize maxDur to zero
	for ( i = 0 ; i < part1nTones ; i++ ) {	
		if ( part4dur[i] > maxDur )			// find the maxDur
			maxDur = part4dur[i] ;
	}

	// allocate memory for the arrays
	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;


	st = 0 ;		// initialize start time to zero
	for ( i = 0 ; i < part1nTones ; i++ ) {		// loop to generate the tones
		fprintf(stderr," i = %d ", i) ;

		addsyn(sound, part4dur[i], sr, F[i], dB, partialF, partialA, nPartials) ;
		adsr2(sound, part4dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part4dur[i], sr) ;

		st += part4dur[i] ;	// increment the start time

	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

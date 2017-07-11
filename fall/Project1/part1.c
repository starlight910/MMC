#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part1nTones = 4 ;			// number of tones in part 1
static double part1dur[] = {2, 2, 2, 2} ;    //duration of each tones


double getPart1Dur(void)
{
	double td = 0 ;
	int i ;

	for ( i = 0 ; i < part1nTones ; i++ )
		td += part1dur[i] ;

	return td ;
}

short *part1(int sr)
{
	//
	//	set the data for the partials
	//
	int nPartials = 6 ;		// total number of partials
	double partialF[] = {1.0, 0.9, 0.8, 0.7, 0.6, 0.5} ;	// partial freq
	double partialA[] = {1/1, 1/3, 1/1, 1/3, 1/1, 1/3} ;	// partial amp

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 5 ;
	double T[] = {0.0, 0.6, 0.7, 0.8, 1.0} ;
	double A[] = {0.0, 1.0, 0.80, 0.50, 0.0} ;
	int flag = 0 ;

	double F[] = {155.56, 164.81, 138.59, 130.81} ;		// fundamental frequency
	double dB = 110 ;		// starting amplitude

	short *sound,			// array for each individual tone
		  *output ;			// array for the sequence of tones
	double totalDuration,	// total duration of the tones
		   maxDur,			// max duration of an individual tone
		   st ;				// start time for each tone
	int i ;					// counter


	totalDuration = getPart1Dur() ;

	maxDur = 0 ; // initialize maxDur to zero
	for ( i = 0 ; i < part1nTones ; i++ ) {	
		if ( part1dur[i] > maxDur )			// find the maxDur
			maxDur = part1dur[i] ;
	}

	// allocate memory for the arrays
	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;


	st = 0 ;		// initialize start time to zero
	for ( i = 0 ; i < part1nTones ; i++ ) {		// loop to generate the tones
		fprintf(stderr," i = %d ", i) ;

		addsyn(sound, part1dur[i], sr, F[i], dB, partialF, partialA, nPartials) ;
		adsr2(sound, part1dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part1dur[i], sr) ;

		st += part1dur[i] ;	// increment the start time
		dB += 2 ;		// increment the amplitud
	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

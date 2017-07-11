#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part1nTones = 11 ;			// number of tones in part 1
static double part4dur[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.8, 0.8, 1} ;    //duration of each tones


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
	int nPartials = 8 ;		// total number of partials
	double partialF[] = {0.4, 0.8, 1.2, 1.6, 2, 2.4, 2.8, 3.2} ;	// partial freq
	double partialA[] = {1, 1/3, 1/5, 1/2, 1/4, 1/7, 1/5, 1} ;	// partial amp

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 2 ;
	double T[] = {0.0, 1.0} ;
	double A[] = {0.0, 1.0} ;
	int flag = 0 ;

	double F = 415.15;		// fundamental frequency
	double dB = 70 ;		// starting amplitude

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

		addsyn(sound, part4dur[i], sr, F, dB, partialF, partialA, nPartials) ;
		adsr2(sound, part4dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part4dur[i], sr) ;

		st += part4dur[i] ;	// increment the start time
		dB += 1 ;

		F = F ;
	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

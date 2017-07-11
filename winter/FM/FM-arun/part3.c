#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>
#include "random.h"

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB,
	double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, 
	double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part3nTones = 16 ;			// number of tones in part 1
static double part3dur[] = {			// duration of each tones
				0.5, 0.25, 0.75, 0.5,	
				0.4, 0.20, 0.60, 0.4, 
				0.3, 0.15, 0.45, 0.3,
				0.2, 0.1, 0.3, 0.2
} ;

double getPart3Dur(void)
{
	double td = 0 ;
	int i ;
	for ( i = 0 ; i < part3nTones ; i++ )
		td += part3dur[i] ;
	return td ;
}


short *part3(int sr)
{
	//
	//	set the data for the partials
	//
	int nPartials = 6 ;		// total number of partials
	double *partialF ;
	double *partialA ;

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 5 ;
	double T[] = {0.0, 0.1, 0.25, 0.75, 1.0} ;
	double A[] = {0.0, 1.0, 0.75, 0.50, 0.0} ;
	int flag = 0 ;

	double F = 440.0 ;		// fundamental frequency
	double dB = 60 ;		// starting amplitude

	short *sound,			// array for each individual tone
		  *output ;			// array for the sequence of tones
	double totalDuration,	// total duration of the tones
		   maxDur,			// max duration of an individual tone
		   st ;				// start time for each tone
	int i ;					// counter

	const double FREQ_MAX = 4.0, FREQ_MIN = 1.1 ;
	const int PARTIALS_MAX = 30, PARTIALS_MIN = 5 ;
	double fmax, fmin ;

	totalDuration = getPart3Dur() ;

	maxDur = 0 ; // initialize maxDur to zero
	for ( i = 0 ; i < part3nTones ; i++ ) {	
		if ( part3dur[i] > maxDur )			// find the maxDur
			maxDur = part3dur[i] ;
	}

	// allocate memory for the arrays
	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;

	st = 0 ;			// initialize start time to zero
	for ( i = 0 ; i < part3nTones ; i++ ) {		// loop to generate the tones

		// set the number of partials for this sound
		nPartials = (PARTIALS_MAX - PARTIALS_MIN) * frandom() + PARTIALS_MIN ;

		// set the frequency limits for the partials
		fmax = (FREQ_MAX - FREQ_MIN) * frandom() + FREQ_MIN ;
		fmin = (fmax - FREQ_MIN) * frandom() + FREQ_MIN ;

		// create randomaly filled arrays for partial freqs and amplitudes
		partialF = randomArray(fmax, fmin, nPartials) ;
		partialA = randomArray(1.0, 0.1, nPartials) ;

		addsyn(sound, part3dur[i], sr, F, dB, partialF, partialA, nPartials) ;

		Free(partialF) ;
		Free(partialA) ;

		

		adsr2(sound, part3dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part3dur[i], sr) ;

		st += part3dur[i] ;	// increment the start time
		if ( dB < 96 )
			dB += 3 ;		// increment the amplitude by 3dB

		if ( i % 2 == 0 )	// every other time, either raise of lower the freq
			F = F * pow(2.0, (i+1)/12.0) ;
		else 
			F = F / pow(2.0, (i+1)/12.0) ;
	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

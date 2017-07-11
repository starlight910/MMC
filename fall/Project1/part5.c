#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part5nTones = 5 ;			// number of tones in part 5
static double part5dur[] = {2, 1, 0.5, 1, 2} ;    //duration of each tones


double getPart5Dur(void)
{
	double td = 0 ;
	int i ;

	for ( i = 0 ; i < part5nTones ; i++ )
		td += part5dur[i] ;

	return td ;
}

short *part5(int sr)
{
	//
	//	set the data for the partials
	//
	int nPartials = 3 ;		// total number of partials
	double partialF[] = {1, 1.25, 2.0} ;	// partial freq
	double partialA[] = {1, 0.9, 0.91} ;	// partial amp

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 4 ;
	double T[] = {0.0, 0.1, 0.5, 1.0} ;
	double A[] = {0.0, 1.0, 0.5, 1.0} ;
	int flag = 0 ;

	double dB = 110 ;		// starting amplitude
	double F[] = {415.15, 550, 330, 440, 415.15};

	short *sound,			// array for each individual tone
		  *output ;			// array for the sequence of tones
	double totalDuration,	// total duration of the tones
		   maxDur,			// max duration of an individual tone
		   st ;				// start time for each tone
	int i ;					// counter


	totalDuration = getPart5Dur() ;

	maxDur = 0 ; // initialize maxDur to zero
	for ( i = 0 ; i < part5nTones ; i++ ) {	
		if ( part5dur[i] > maxDur )			// find the maxDur
			maxDur = part5dur[i] ;
	}

	// allocate memory for the arrays
	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;


	st = 0 ;		// initialize start time to zero
	for ( i = 0 ; i < part5nTones ; i++ ) {		// loop to generate the tones
		fprintf(stderr," i = %d ", i) ;

		addsyn(sound, part5dur[i], sr, F[i], dB, partialF, partialA, nPartials) ;
		adsr2(sound, part5dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part5dur[i], sr) ;

		st += part5dur[i] ;	// increment the start time
	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

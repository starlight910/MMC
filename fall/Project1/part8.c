#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part8nTones = 6 ;			// number of tones in part 5
static double part8dur[] = {1, 0.2, 0.5, 0.5, 1, 2} ;    //duration of each tones


double getPart8Dur(void)
{
	double td = 0 ;
	int i ;

	for ( i = 0 ; i < part8nTones ; i++ )
		td += part8dur[i] ;

	return td ;
}

short *part8(int sr)
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
	double F[] = {415.15, 550, 330, 440, 463.15, 550};

	short *sound,			// array for each individual tone
		  *output ;			// array for the sequence of tones
	double totalDuration,	// total duration of the tones
		   maxDur,			// max duration of an individual tone
		   st ;				// start time for each tone
	int i ;					// counter


	totalDuration = getPart8Dur() ;

	maxDur = 0 ; // initialize maxDur to zero
	for ( i = 0 ; i < part8nTones ; i++ ) {	
		if ( part8dur[i] > maxDur )			// find the maxDur
			maxDur = part8dur[i] ;
	}

	// allocate memory for the arrays
	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;


	st = 0 ;		// initialize start time to zero
	for ( i = 0 ; i < part8nTones ; i++ ) {		// loop to generate the tones
		fprintf(stderr," i = %d ", i) ;

		addsyn(sound, part8dur[i], sr, F[i], dB, partialF, partialA, nPartials) ;
		adsr2(sound, part8dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part8dur[i], sr) ;

		st += part8dur[i] ;	// increment the start time
		


	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

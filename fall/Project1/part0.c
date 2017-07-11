#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part0nTones = 6 ;			// number of tones in part 1
static double part0dur[] = {0.4, 0.4, 0.4, 0.4, 0.4, 0.4} ;    //duration of each tones


double getPart0Dur(void)
{
	double td = 0 ;
	int i ;

	for ( i = 0 ; i < part0nTones ; i++ )
		td += part0dur[i] ;

	return td ;
}

short *part0(int sr)
{
	//
	//	set the data for the partials
	//
	int nPartials = 6 ;		// total number of partials
	double partialF[] = {1.0, 0.98, 1.02, 0.96, 1.04, 0.94} ;	// partial freq
	double partialA[] = {1/1, 1/3, 1/1, 1/3, 1/1, 1/3} ;	// partial amp

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 3 ;
	double T[] = {0.0, 0.5, 1.0} ;
	double A[] = {0.0, 0.8, 1.0} ;
	int flag = 0 ;

	double F[] = {138.59, 164.81, 207.65, 220, 207.65, 164.81} ;		// fundamental frequency
	double dB = 110 ;		// starting amplitude

	short *sound,			// array for each individual tone
		  *output ;			// array for the sequence of tones
	double totalDuration,	// total duration of the tones
		   maxDur,			// max duration of an individual tone
		   st ;				// start time for each tone
	int i ;					// counter


	totalDuration = getPart0Dur() ;

	maxDur = 0 ; // initialize maxDur to zero
	for ( i = 0 ; i < part0nTones ; i++ ) {	
		if ( part0dur[i] > maxDur )			// find the maxDur
			maxDur = part0dur[i] ;
	}

	// allocate memory for the arrays
	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;


	st = 0 ;		// initialize start time to zero
	for ( i = 0 ; i < part0nTones ; i++ ) {		// loop to generate the tones
		fprintf(stderr," i = %d ", i) ;

		addsyn(sound, part0dur[i], sr, F[i], dB, partialF, partialA, nPartials) ;
		adsr2(sound, part0dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part0dur[i], sr) ;

		st += part0dur[i] ;	// increment the start time
		dB += 3 ;		// increment the amplitud
	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

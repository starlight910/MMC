#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB, double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part1nTones = 12 ;			// number of tones in part 1
static double part1dur[] = {0.5, 0.25, 0.75, 0.5, 0.4, 0.20, 0.60, 0.4,	0.3, 0.15, 0.45, 0.3} ; // duration of each tones

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
	double partialF[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0} ;	// partial frequency
	double partialA[] = {1.0, 1/2., 1/3., 1/4., 1/5., 1/6.} ;	// partial amplitude

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

		addsyn(sound, part1dur[i], sr, F, dB, partialF, partialA, nPartials) ;
		adsr2(sound, part1dur[i], sr, T, A, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part1dur[i], sr) ;

		st += part1dur[i] ;	// increment the start time
		dB += 3 ;		// increment the amplitude by 3dB

		if ( i % 2 == 0 )	// every other time, either raise of lower the freq
			F = F * pow(2.0, (i+1)/12.0) ;
		else 
			F = F / pow(2.0, (i+1)/12.0) ;
	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

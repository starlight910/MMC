#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void addsyn(short tone[], double dur, int sr, double F, double dB,
	double partialF[], double partialA[], int nPartials) ;
void adsr2(short sound[], double dur, int sr, 
	double T[], double A[], int N, int flag) ;
void concatenate(short output[], short input[], double st, double dur, int sr) ;

static int part1nTones = 20 ;			// number of tones in part 1
static double part1dur[20] ; 			// duration of each tones


short *part1(int sr)
{
	//
	//	set the data for the partials
	//
	int nPartials = 7 ;		// total number of partials
	double partialF[] = {1.0, 0.5, 1.5, 0.75, 1.2, 0.86, 0.3} ;	// partial freq
	double partialA[] = {1.0, 1/2., 1/4., 1/8., 1/16., 1/32., 1/33.} ;	// partial amp

	//
	//	set the data for the ADSR envelope
	//
	int nPoints = 5 ;
	double yp1[] = {0.0, 0.33, 0.66, 0.99, 0.0} ;
	double xp1[] = {0.0, 0.25, 0.5, 0.75, 1.0} ;
	int flag = 0 ;

	double F = 350.0 ;		// fundamental frequency
	double dB = 90 ;		// starting amplitude

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
		adsr2(sound, part1dur[i], sr, xp1, yp1, nPoints, flag) ;	// make envelope
		concatenate(output, sound, st, part1dur[i], sr) ;

		st += part1dur[i] ;	// increment the start time
	//	dB += 3 ;		// increment the amplitude by 3dB

		F = F + 5 ;

	/*	if ( i % 2 == 0 )	// every other time, either raise of lower the freq
			F = F * pow(2.0, (i+1)/12.0) ;
		else 
			F = F / pow(2.0, (i+1)/12.0) ;
*/	}

	Free(sound) ;	// no longer needed, so free this memory

	return output ;		// return the created sequence of tones
}

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

static int part2nTones = 4 ;			// number of tones in part 1
static double part2dur[] = {2, 2, 2, 2};  // duration of each tone

double getPart2Dur(void)
{
	double td = 0 ;
	int i ;

	for ( i = 0 ; i < part2nTones ; i++ )
		td += part2dur[i] ;

	return td ;
}

short *part2(int sr)
{
	int nPoints = 5 ;		// data for the envelope
	double T[] = {0.0, 0.3, 0.5, 0.9, 1.0} ;
	double A[] = {0.0, 1.0, 0.6, 0.3, 0.0} ;
	int flag = 0 ;

	int nPartials = 6 ;		// data for the partials
	double partialF[] = {1.0, 0.9, 0.8, 0.7, 0.6, 0.5} ;	
	double partialA[] = {1/1, 1/3, 1/1, 1/3, 1/1, 1/3} ;

//	int nPartials2 = 5 ;
//	double partialF2[] = {1, 0, 1/3, 0, 1/5} ;
//	double partialA2[] = {1.0, 1.0, 1.0, 1.0, 1.0} ;

	double F[] = {155.56, 164.81, 138.59, 185} ;		// initial frequency
	double dB = 110 ;		// initial amplitude

	short *sound, *output ;
	double totalDuration, maxDur, st ;
	int i ;

	totalDuration = getPart2Dur() ;

	maxDur = 0 ;	// initialize maxDur and totalDur
	for ( i = 0 ; i < part2nTones ; i++ ) {
		if ( part2dur[i] > maxDur )
			maxDur = part2dur[i] ;
	}

	sound = (short *)Malloc(maxDur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDuration * sr * sizeof(short)) ;

	st = 0 ;		// initialize start time
	for ( i = 0 ; i < part2nTones ; i++ ) {	// loop to create the tones

		// create the tone, apply an envelope to it, and concatenate it
		fprintf(stderr," i = %d ", i) ;

		addsyn(sound, part2dur[i], sr, F[i], dB, partialF, partialA, nPartials) ;
		adsr2(sound, part2dur[i], sr, T, A, nPoints, flag) ;	
		concatenate(output, sound, st, part2dur[i], sr) ;

		st += part2dur[i] ;		// increment the start time
		dB += 2 ;			// decrement the amplitude

	}

	Free(sound) ;

	return output ;
}

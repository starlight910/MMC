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

static int part2nTones = 16 ;			// number of tones in part 1
static double part2dur[] = {			// duration of each tone
				0.3, 0.15, 0.45, 0.3,
				0.4, 0.20, 0.60, 0.4, 
				0.5, 0.25, 0.75, 0.5, 
				0.3, 0.15, 0.45, 0.3
};

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
	double T[] = {0.0, 0.1, 0.25, 0.95, 1.0} ;
	double A[] = {0.0, 0.25, 0.50, 1.00, 0.0} ;
	int flag = 0 ;

	int nPartials = 6 ;		// data for the partials
	double partialF[] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0} ;	
	double partialA[] = {1.0, 1/3., 1/5., 1/7., 1/9., 1/11.} ;	

	double F = 660.0 ;		// initial frequency
	double dB = 96 ;		// initial amplitude

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
		addsyn(sound, part2dur[i], sr, F, dB, partialF, partialA, nPartials) ;
		adsr2(sound, part2dur[i], sr, T, A, nPoints, flag) ;	
		concatenate(output, sound, st, part2dur[i], sr) ;

		st += part2dur[i] ;		// increment the start time
		dB -= 3 ;			// decrement the amplitude

		if ( i % 2 == 0 )	// every other time, either raise or lower freq
			F = F / pow(2.0, (i+1)/12.0) ;
		else 
			F = F * pow(2.0, (i+1)/12.0) ;
	}

	Free(sound) ;

	return output ;
}

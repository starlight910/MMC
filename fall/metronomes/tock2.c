#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sf.h>
#include <sfmisc.h>
#include "random.h"

//
//	sort(array, N)
//	sort the array in ascending order [bubble sort]
//
static void sort(double array[], int N)
{
	int i, allDone ;
	double tmp ;

	do {
		allDone = 1 ;
		for ( i = 0 ; i < N - 1 ; i++ ) {
			if ( array[i] > array[i+1] ) {
				allDone = 0 ;
				tmp = array[i] ;
				array[i] = array[i+1] ;
				array[i+1] = tmp ;
			}
		}
	} while ( ! allDone ) ;

	return ;
}

//
//	sortReverse(array, N)
//	sort the array in descending order [bubble sort]
//

static void sortReverse(double array[], int N)
{
	int i, allDone ;
	double tmp ;

	do {
		allDone = 1 ;
		for ( i = 0 ; i < N - 1 ; i++ ) {
			if ( array[i] < array[i+1] ) {
				allDone = 0 ;
				tmp = array[i] ;
				array[i] = array[i+1] ;
				array[i+1] = tmp ;
			}
		}
	} while ( ! allDone ) ;

	return ;
}



//
//	envelopeRandom(sound, dur, sr) :
//	create a random envelope, and apply it to the sound
//

static void envelopeRandom(short *sound, double dur, int sr)
{
	extern void adsr2(short sound[], double dur, int sr, 
		double T[], double A[], int N, int flag) ;

	double *T, *A ;
	int nPoints, flag = 1 ;
	const int MAXPOINTS = 20, MINPOINTS = 4 ;
	static int counter ;

	// number of points in the envelope
	nPoints = (MAXPOINTS - MINPOINTS) * frandom() + MINPOINTS ;

	T = randomArray(1.0, 0.0, nPoints) ;
	A = randomArray(1.0, 0.1, nPoints) ;

	A[0] = 0.0 ;			// make sure the initial and final values
	A[nPoints-1] = 0.0 ;	// of the amplitude array are zeros

	sort(T, nPoints) ;	// make sure time points are in ascending order

	if ( counter++ % 2 == 0 )
		flag = 0 ;				// linear envelope
	else 
		flag = 1 ;				// exponential envelope

	adsr2(sound, dur, sr, T, A, nPoints, flag) ; // apply the envelope

	Free(T) ;
	Free(A) ;

	return ;
}



//
//	tock1(window, dur, sr)
//
//	make one 'tick' of the metronome.
//	create the sound using additive synthesis, with a random
//	fundamental and a random frequency spectrum.
//

void tock2(short *tickArray, double dur, int sr)
{
	extern void addsyn(short sData[], double dur, int sr, 
		double F, double dB, 
		double partialF[], double partialA[], int nPartials);
	extern void envelopeRandom(short data[], double dur, int sr) ;

	const int PMAX = 100, PMIN = 10 ;		// range of number of partials
	const int FMAX = 10, FMIN = 1.01 ;		// range of partial frequencies
	const double FQMAX = 1000, FQMIN = 500 ; // range of fundamental freq
	const double dB = 96 ;					// set amplitude
	const double amax = 1.0, amin = 0.01 ;	// range of amplitude values

	double tickDur = dur / 20.0 ;			// duration of the 'tick'

	int nPartials ;		
	double F, fmax, fmin ;
	double *partialF, *partialA ;

	memset(tickArray, 0, dur * sr * sizeof(short)) ;

	F = (FQMAX - FQMIN) * frandom() + FQMIN ;		// set fundamental

	nPartials = (PMAX - PMIN) * frandom() + PMIN ;	// set number of partials
	fmax = (FMAX - FMIN) * frandom() + FMIN ;		// set max partial freq
	fmin = (fmax - FMIN) * frandom() + FMIN ;		// set min partial freq

	partialF = randomArray(fmax, fmin, nPartials) ;	// set partial freqs
	partialA = randomArray(amax, amin, nPartials) ; // set partial amplitudes

	sort(partialF, nPartials) ;				// partial freqs ascending
	sortReverse(partialA, nPartials) ;		// partial amps descending

	// create the 'tick'
	addsyn(tickArray, tickDur, sr, F, dB, partialF, partialA, nPartials) ;

	Free(partialF) ;
	Free(partialA) ;

	envelopeRandom(tickArray, tickDur, sr) ;	// apply a 'random' envelope

	return ;
}



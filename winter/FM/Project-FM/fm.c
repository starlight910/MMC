#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

#include "env.h"

void fm(short sound[], double dur, int sr, double dB, double carrier, double modulator,	double peakDeviation)
{
	double cPhase, mPhase,		// carrier and modulator phase
		cInc, mInc,				// increments for the two
		amp ;					// linear amplitude
	int t, samples ;			// counter for time, and samples

	static int counter ;		// function counter

	// arrays for the envelope: T = time, A = amplitude
	double T[] = {0.0, 0.2, 0.5, 0.6, 0.8, 0.93, 0.95,  1.0} ;
	double A[] = {0.0, 0.01, 0.02, 0.03, 0.04, 0.9, 1.0,  2.2} ;
	int nPoints = 8 ;	// number of points in the envelope
	double *env ;		// array for the envelope

	// print out information to the screen
	fprintf(stderr,	"\tFM(%d): C = %g  M = %g  pd = %g  dur = %g  dB = %g\n",counter++, carrier, modulator,peakDeviation,dur, dB) ;

	samples = dur * sr ;			// translate seconds into samples
	amp = pow(10.0, dB/20.0) / 2 ;	// translate dB into linear

	cPhase = 0 ;		// initialize the phase for both
	mPhase = 0 ;		// carrier and modulator

	cInc = ( 2.0 * M_PI * carrier ) / sr ;	// increments for C & M
	mInc = ( 2.0 * M_PI * modulator ) / sr ;

	env = linearEnv(dur, sr, T, A, nPoints) ;	// make envelope

	for ( t = 0 ; t < samples ; t++ ) {		// FM loop
		sound[t] = amp * sin(cPhase 
				+ (peakDeviation * env[t]) * sin(mPhase)) ;
		cPhase += cInc ;		// increment cPhase & mPhase
		mPhase += mInc ;
	}

	Free(env) ;		// release memory

	return ;
}


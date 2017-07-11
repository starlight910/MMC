#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"
#include "cat.h"

int main(void)
{
	int nchan = 1,			// number of channels (1)
		sr = 44100 ;		// samples per second

	int i, nTones = 5 ;		// counter, total number of tones

	double dB = 90 ;		// amplitude of each tone

	double Carrier[] = {100, 200, 300, 400, 500} ;	// carrier freqs
	double Modulator[] = {200, 200, 200, 200, 200} ;// mod freqs
	double PD[] = {10, 20, 30, 40, 50} ;			// peak deviation

	double dur = 5,			// duration of each tone
		   startTime,		// start time for each tone
		   totalDur ;		// total duration of the tones

	short *tone, *output ;	// arrays for each tone, and the output

	totalDur = 0 ;			// compute the total duration of the tones
	for ( i = 0 ; i < nTones ; i++ )
		totalDur += dur ;

	// allocate memory for each tone, and for the output
	tone = (short *)Malloc(dur * sr * sizeof(short)) ;
	output = (short *)Malloc(totalDur * sr * sizeof(short)) ;

	// create the tones
	startTime = 0 ;
	for ( i = 0 ; i < nTones ; i++ ) {
		// create one FM tone
		fm(tone, dur, sr, dB, Carrier[i], Modulator[i], PD[i]) ;
		// concatenate the sequence
		concatenate(output, tone, startTime, dur, sr) ;
		// increment the start time
		startTime = startTime + dur ;
	}

	// save the set of tones
	sfsave("fmsounds.wav", output, totalDur, sr, nchan) ;

	Free(tone) ;	// release memory
	Free(output) ;

	exit(EXIT_SUCCESS) ;
}











#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

#include "env.h"

void fm(short sound[], double dur, int sr, double dB,
		double carrier,
		double modulator,
		double peakDeviation)
{
	double cPhase, mPhase,		// carrier and modulator phase
		cInc, mInc,				// increments for the two
		amp ;					// linear amplitude
	int t, samples ;			// counter for time, and samples

	static int counter ;		// function counter

	// arrays for the envelope: T = time, A = amplitude
	double T[] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0} ;
	double A[] = {0.0, 1.0, 0.75, 0.5, 1.0, 0.0} ;
	int nPoints = 6 ;	// number of points in the envelope
	double *env ;		// array for the envelope

	// print out information to the screen
	fprintf(stderr,
		"\tFM(%d): C = %g  M = %g  pd = %g  dur = %g  dB = %g\n",
			counter++, carrier, modulator, peakDeviation,
			dur, dB) ;

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


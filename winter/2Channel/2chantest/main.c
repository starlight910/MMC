#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"			// include declarations for fm()
#include "cat.h"		// declarations for concatenate()
#include "mix.h"		// declarations for the 'mix' functions
#include "env.h"		// declarations for 'adsr2()'

int main(void)
{
	int nchan = 2,			// number of channels of sound (2)
		sr = 44100 ;		// samples per second

	int Left = 0 ;			// identify left, right channels
	int Right = 1 ;

	int i, nTones = 6 ;		// counter, total number of tones

	double dB = 90 ;		// amplitude of each tone

	double Carrier[] = {440, 440, 440, 440, 440, 440} ;	// carrier freqs
	double Modulator[] = {1, 1, 1, 1, 1, 1} ;// mod freqs
	double PD[] = {2, 2, 2, 100, 100, 2} ;			// peak deviation
	int nFMTones = 6 ;

	double T[] = {0.0, 0.1, 0.25, 0.75, 1.0} ;	// envelope time values
	double A[] = {0.0, 0.01, 0.03, 0.2, 1.0} ;	// envelope amp values
	int nPoints = 5 ;		// number of 'points' in the envelope
	int envType = 0 ;		// linear envelope

	double dur[] = {2, 2, 2, 2, 2, 2};			// duration of each tone
	double startTime;		// start time for each tone
	double totalDur ;		// total duration of the tones

	short *tone, *output ;	// arrays for each tone, and the output

	totalDur = 0 ;			// compute the total duration of the tones
	for ( i = 0 ; i < nTones ; i++ )
		totalDur += dur[i] ;

	// allocate memory for each tone
	// tone = (short *)Malloc(dur[i] * sr * sizeof(short)) ;

	// setup the mix buffer for the output mix
	mixSetup(totalDur, sr, nchan) ;

	startTime = 0 ;
	for ( i = 0 ; i < nTones ; i++ ) 
	{		// create the tones
		tone = (short *)Malloc(dur[i] * sr * sizeof(short)) ;
		// create one FM tone, and apply an envelope
		fm(tone, dur, sr, dB,Carrier[i%nFMTones], Modulator[i%nFMTones], PD[i%nFMTones]) ;
		adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;

		// add the tone to the output mix buffer at 'startTime'
		if ( i % 2 == 0 ) 
			mixAdd(tone, startTime, dur[i], sr, Left) ;
		else 
			mixAdd(tone, startTime, dur[i], sr, Right) ;

		// increment the start time by a quarter of the duration
		// to ensure an overlap of the sounds
		startTime = startTime + (dur[i] * 0.25) ;
	}


	// convert the mix output from doubles to shorts
	output = mixConvertTo16Bits() ;

	// save the set of tones
	sfsave("fmsounds.wav", output, totalDur, sr, nchan) ;

	Free(tone) ;	// release memory
	Free(output) ;

	exit(EXIT_SUCCESS) ;
}

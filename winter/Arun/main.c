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

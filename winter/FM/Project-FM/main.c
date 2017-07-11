#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>
#include "fm.h"
#include "cat.h"

int main(void){	int nchan = 1,			// number of channels (1)
		sr = 44100 ;		// samples per second
         	int i, nTones = 33 ;		// counter, total number of tones
                double dB = 90 ;		// amplitude of each tone
                double Carrier[] = {440, 523.25, 329.63, 440, 523.25, 659.26, 440, 523.25, 329.63, 440, 523.25, 659.26, 220, 261.63, 164.81, 220, 261.63, 329.63, 220, 261.63, 164.81, 220, 261.63, 329.63, 880, 783.99, 698.46, 659.26, 622.25, 659.26, 440, 523.25, 622.25} ;	// carrier freqs
         	double Modulator[] = {111, 222, 333, 111, 222, 444, 111, 222, 333, 111, 222, 444, 666, 555, 444, 777, 555, 444, 666, 555, 444, 777, 555, 444, 111, 111, 111, 111, 222, 222, 555, 555, 555} ;// mod freqs
        	double PD[] = {200, 200, 0, 200, 200, 0, 200, 200, 0, 200, 200, 0, 200, 200, 0, 200, 200, 0, 200, 200, 0, 200, 200, 0, 300, 300, 300, 300, 100, 300, 200, 100, 0} ;			// peak deviation
        	double dur[] = {4, 4, 5, 4, 4, 5, 4, 4, 5, 4, 4, 5, 4, 4, 5, 4, 4, 5, 4, 4, 5, 4, 4, 5, 2, 2, 2, 4, 4, 4, 2, 2, 5};			// duration of each tone
        	double startTime;		// start time for each tone
        	double totalDur ;		// total duration of the tones
        	short *tone, *output ;	// arrays for each tone, and the output
        	totalDur = dur[i]  ;			// compute the total duration of the tones
        	for ( i = 0 ; i < nTones ; i++ )
        	totalDur += dur[i] ;

	// allocate memory for each tone, and for the output
	output = (short *)Malloc(totalDur * sr * sizeof(short)) ;

	// create the tones
	startTime = 0 ;
	for ( i = 0 ; i < nTones ; i++ ) 
	{
	 tone = (short *)Malloc(dur[i] * sr * sizeof(short)) ;
		// create one FM tone
		fm(tone, dur[i], sr, dB, Carrier[i], Modulator[i], PD[i]) ;
		// concatenate the sequence
    	concatenate(output, tone, startTime, dur[i], sr) ;
		// increment the start time
		startTime = startTime + dur[i] ;
	}

	fprintf(stderr, "\tTotal duration = %g\n",totalDur);
	// save the set of tones
	sfsave("fmsounds.wav", output, totalDur, sr, nchan) ;

	Free(tone) ;	// release memory
	Free(output) ;

	exit(EXIT_SUCCESS) ;
}

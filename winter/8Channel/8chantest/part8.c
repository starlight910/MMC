#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part8(int sr, double *tone, double *left, double *right, double *pan)
{
	double Left = 0 ;                  // left channel
	double Right = 1 ;                 // right channel
	
	int i, nTones = 12 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {440, 523.25, 493.88, 440, 523.25, 493.88, 440, 523.25, 493.88, 440, 523.25, 493.88} ;  // carrier freqs
	double Modulator[] = {10, 10, 10, 10, 10, 10, 40, 40, 40, 80, 80, 80} ;// mod freqs
    double PD[] = {3, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2} ;                    // peak deviation
	int nFMTones = 20 ;
	
	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.75, 1.0};
	double A[] = {0.5, 0.2, 0.0};
	
	double startTime[] = {90.0, 93.0, 94.0, 97.0, 98.0, 99.0, 102.0, 103.0, 104.0, 107.0, 108.0, 109.0};            // start time for each tone
    double dur[] = {5, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur[i] * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur[i], sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;

       // add the tone to the output mix buffer at 'startTime'
        if ( i % 2 == 0 )
       mixAdd(tone, startTime[i], dur[i], sr, Left) ;
        else
       mixAdd(tone, startTime[i], dur[i], sr, Right) ;


    free(tone);
        }
}



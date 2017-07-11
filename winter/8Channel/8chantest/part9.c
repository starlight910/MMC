#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part9(int sr, double *tone, double *left, double *right, double *pan)
{
	double Left = 0 ;                  // left channel
	double Right = 1 ;                 // right channel
	
	int i, nTones = 14 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {659.62, 440, 523.25, 587.33, 493.88, 659.62, 440, 523.25, 587.33, 493.88, 440, 440, 440, 440} ;  // carrier freqs
	double Modulator[] = {10, 10, 10, 10, 50, 20, 20, 20, 20, 100, 10, 10, 10, 10} ;// mod freqs
    double PD[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1} ;                    // peak deviation
	int nFMTones = 20 ;
	
	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.2, 0.75, 1.0};
	double A[] = {0.0, 1.0,  0.3, 0.0};
	
	double startTime[] = {111.0, 116.0, 121.0, 127.0, 130.0, 141.0, 146.0, 151.0, 157.0, 160.0, 163, 166, 168, 170};            // start time for each tone
    double dur[] = {27, 26, 22, 18, 12, 27, 26, 22, 18, 12, 10, 7, 7, 7};

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



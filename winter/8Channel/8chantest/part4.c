#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part4(int sr, double *tone, double *left, double *right, double *pan)
{
	double Left = 0 ;                  // left channel
	double Right = 1 ;                 // right channel
	
	int i, nTones = 6 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {329.63, 880, 783.99, 440, 392, 523.25} ;  // carrier freqs
	double Modulator[] = {200, 10, 10, 40, 40} ;// mod freqs
    double PD[] = {2, 1, 1, 3, 3, 3} ;                    // peak deviation
	int nFMTones = 15 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.1, 0.5, 0.8, 1.0};
	double A[] = {0.0, 0.5, 1.0, 0.5, 0.0};
	
	double startTime[] = {40.0, 43.0, 51.0, 52.0, 56.0, 59.0};            // start time for each tone
    double dur[] = {30, 10, 14, 5, 10, 10};

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



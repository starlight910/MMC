#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part6(int sr, double *tone, double *left, double *right, double *pan)
{
	double Left = 0 ;                  // left channel
	double Right = 1 ;                 // right channel
	
	int i, nTones = 12 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {82.41, 82.41, 82.41, 82.41, 82.41, 82.41, 82.41, 82.41, 164.81, 164.81, 164.81, 164.81} ;  // carrier freqs
	double Modulator[] = {10, 10, 10, 10, 10, 10, 10, 10, 200, 200, 200, 200} ;// mod freqs
    double PD[] = {5, 5, 5, 5, 5, 5, 5, 5, 3, 3, 3, 3} ;                    // peak deviation
	int nFMTones = 20 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.1, 0.5, 0.8, 1.0};
	double A[] = {0.0, 1.0, 0.5, 0.1, 0.0};
	
	double startTime[] = {63.0, 65.0, 67.0, 69.0, 71.0, 73.0, 75.0, 77.0, 79.0, 82.0, 85.0, 88.0 };            // start time for each tone
    double dur[] = {3, 3, 3, 3, 3, 3, 3, 3, 5, 5, 5, 5};

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



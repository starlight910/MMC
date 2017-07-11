#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part2(int sr, double *tone, double *left, double *right, double *pan)
{
	int Left = 0 ;                  // left channel
	int Right = 1 ;                 // right channel
	
	int i, nTones = 18 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {369.99, 369.99, 369.99, 830.61, 554.37, 830.61, 554.37, 369.99, 830.61, 739.99, 739.99, 830.61, 554.37, 739.99, 739.99, 739.99, 739.99, 739.99} ;  // carrier freqs
	double Modulator[] = {200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 } ;// mod freqs
    double PD[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2} ;                    // peak deviation
	int nFMTones = 10 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.25, 0.50, 0.75, 1.0};
	double A[] = {0.5, 0.4, 0.3, 0.2, 0.0};
	
	double startTime[] = {3.0, 6.0, 7.0, 8.0, 8.2, 11.0, 11.2, 11.4, 14.0, 16.0, 19.0, 20.8, 21.2, 22.0, 22.4, 24.2, 24.4, 25.2};            // start time for each tone
    double dur[] = {3, 2, 2, 5, 2, 4, 4, 2, 5, 4, 3, 2, 3, 2, 6, 3, 5, 4}; // Duration of each tone

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur[i] * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur[i], sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;

        if ( i % 2 == 0 )
       mixAdd(tone, startTime[i], dur[i], sr, Left) ;
        else
       mixAdd(tone, startTime[i], dur[i], sr, Right) ;
		

    free(tone);
        }
}



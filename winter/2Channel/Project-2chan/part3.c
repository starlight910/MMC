#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part3(int sr, double *tone, double *left, double *right, double *pan)
{
	int Left = 0 ;                  // left channel
	int Right = 1 ;                 // right channel
	
	int i, nTones = 20 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220, 220} ;  // carrier freqs
	double Modulator[] = {200, 200, 200, 200, 300, 300, 300, 300, 300, 300, 300, 440, 440, 440, 440, 440, 440, 440, 440, 440} ;// mod freqs
    double PD[] = {10, 10, 10, 10, 10, 10, 10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2} ;                    // peak deviation
	int nFMTones = 10 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.25, 0.50, 0.75, 1.0};
	double A[] = {0.0, 0.1, 1.0, 0.5, 0.0};
	
	double startTime[] = {30.0, 85.0, 90.0, 95.0, 100.0, 103.0, 106.0, 110.0, 118.0, 121.0, 123.0, 124.0, 130.0, 137.0, 142.0, 144.0, 151.0, 160.0, 170.0, 175.0};            // start time for each tone
    double dur[] = {4, 4, 4, 4, 4, 5, 10, 13, 21, 13, 21, 8, 5, 30, 15, 19, 21, 17, 9, 8}; //duration of each tone

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



#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part4(int sr, double *tone, double *left, double *right, double *pan)
{
	int Left = 0 ;                  // left channel
	int Right = 1 ;                 // right channel
	
	int i, nTones = 20 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {369.99, 369.99, 369.99, 369.99, 369.99, 369.99, 261.63, 440, 261.63, 440, 739.99, 369.99, 739.99, 369.99, 261.63, 220, 261.63, 440, 369.99, 220} ;  // carrier freqs
	double Modulator[] = {440, 440, 440, 440, 300, 300, 300, 300, 300, 300, 300, 440, 440, 440, 440, 440, 440, 440, 440, 440} ;// mod freqs
    double PD[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,  10, 10, 10} ;                    // peak deviation
	int nFMTones = 10 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.25, 0.50, 0.75, 1.0};
	double A[] = {1.0, 0.8, 0.7, 0.6, 0.0};
	
	double startTime[] = {100.0, 101.0, 103.0, 104.0, 107.0, 109.0, 111.0, 118.0, 121.0, 123.0, 129.0, 135.0, 138.0, 141.0, 146.0, 150.0, 156.0, 161.0, 164.0, 165.0};            // start time for each tone
    double dur[] = {2, 5, 2, 5, 2, 5, 10, 7, 3, 8, 6, 8, 5, 10, 9, 11, 5, 7, 9, 4};

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



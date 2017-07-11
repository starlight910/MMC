#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part11(int sr, double *tone, double *left, double *right, double *pan)
{
	double Left = 0 ;                  // left channel
	double Right = 1 ;                 // right channel
	
	int i, nTones = 30 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {440, 440, 220, 440, 440, 220, 440, 440, 220, 440, 440, 220, 440, 440, 220, 440, 440, 220, 440, 440, 220, 440, 440, 220, 440, 440, 220, 440, 440, 220} ;  // carrier freqs
	double Modulator[] = {10, 10, 300, 10, 10, 300, 10, 10, 300, 10, 10, 300, 10, 10, 300, 10, 10, 300, 10, 10, 300, 10, 10, 300, 10, 10, 300, 10, 10, 300} ;// mod freqs
    double PD[] = {2, 2, 500, 2, 2, 500, 2, 2, 500, 2, 2, 500, 2, 2, 500, 3, 3, 600, 3, 3, 700, 4, 4, 800, 5, 5, 900, 6, 6, 1000} ; // peak deviation

	int nFMTones = 40 ;

	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.5, 1.0};
	double A[] = {1.0, 0.5, 0.0};
 
	double startTime[] = {170.0, 170.6, 171.2, 174.0, 174.6, 175.2, 178.0, 178.6, 179.2, 182.0, 182.6, 183.2, 186.0, 186.6, 187.2, 190.0, 190.6, 191.2, 194.0, 194.6, 195.2, 198.0, 198.6, 199.2, 202.0, 202.6, 203.2, 206.0, 206.6, 207.2};            // start time for each tone
    double dur[] = {2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5, 2, 2, 5}; //duration of each tone

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



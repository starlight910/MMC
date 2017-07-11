#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part5(int sr, double *tone, double *left, double *right, double *pan)
{
	int Left = 0 ;                  // left channel
	int Right = 1 ;                 // right channel
	
	int i, nTones = 24 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {440, 440, 440, 369.99, 369.99, 369.99, 440, 440, 440, 369.99, 369.99, 369.99, 440, 440, 440, 369.99, 369.99, 369.99, 440, 440, 440, 369.99, 369.99, 369.99} ;  // carrier freqs
	double Modulator[] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400} ;// mod freqs
    double PD[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,       2, 2, 2, 2, 2, 2, 2} ;                    // peak deviation
	int nFMTones = 10 ;
	
	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.75, 1.0};
	double A[] = {0.5, 0.2, 0.0};
	
	double startTime[] = {20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 50.0, 50.5, 51.0, 51.5, 52.0, 52.5, 70.0, 70.5, 71.0, 71.5, 72.0, 72.5, 110.0, 110.5, 111.0, 111.5, 112.0, 112.5, 113.0};            // start time for each tone
    double dur[] = {2, 2, 2, 2, 2, 7, 2, 2, 2, 2, 2, 7, 2, 2, 2, 2, 2, 7, 2, 2, 2, 2, 2, 7};

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



#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part10(int sr, double *tone, double *left, double *right, double *pan)
{
	double Left = 0 ;                  // left channel
	double Right = 1 ;                 // right channel
	
	int i, nTones = 48 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440, 440} ;  // carrier freqs
	double Modulator[] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 } ;// mod freqs
    double PD[] = {2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1 } ;          // peak deviation
	int nFMTones = 100 ;
	
	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.75, 1.0};
	double A[] = {0.0, 0.7, 0.0};
	
	double startTime[] = {146.0, 146.3, 146.6, 146.9, 147.2, 147.5, 147.8, 148.1, 148.4, 148.7, 149.0, 149.3, 149.6, 149.9, 150.2, 150.5, 150.8, 151.1, 151.4, 151.7, 152.0, 152.3, 152.6, 152.9, 153.2, 153.5, 153.8, 154.1, 154.4, 154.7, 155.0, 155.3, 155.6, 155.9, 156.2, 156.5, 156.8, 156.1, 156.4, 156.7, 157.0, 157.3, 157.6, 157.9, 158.2, 158.5, 158.8, 159.1};            // start time for each tone
    double dur[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 }; //duration of each tone

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



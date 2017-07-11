#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part1(int sr, double *tone, double *left, double *right, double *pan)
{
	double Left = 0 ;                  // left channel
	double Right = 1 ;                 // right channel
	
	int i, nTones = 60 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {220, 220, 220, 196, 196, 196, 220, 220, 220, 196, 196, 196, 220, 220, 220, 196, 196, 196, 220, 220, 220, 196, 196, 196, 220, 220, 220, 196, 196, 196, 220, 220, 220, 196, 196, 196, 220, 220, 220, 196,  196, 196, 220, 220, 220, 196, 196, 196, 220, 220, 220, 196, 196, 196, 220,  220, 220, 196, 196, 196} ;  // carrier freqs
	double Modulator[] = {50, 50, 50, 50, 50, 50, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 40, 40, 40, 40, 40, 40, 50, 50, 50, 50, 50, 50, 40, 40, 40, 40, 40, 40 } ;// mod freqs
    double PD[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 ,1 ,1 ,1 ,1, 1, 1 } ; // peak deviation

	int nFMTones = 100 ;

	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.5, 1.0};
	double A[] = {1.0, 0.5, 0.0};
	
	double startTime[] = {2.0, 2.3, 2.6, 2.9, 3.2, 3.5, 6.0, 6.3, 6.6, 6.9, 7.2, 7.5, 10.0, 10.3, 10.6, 10.9, 11.2, 11.5, 14.0, 14.3, 14.6, 14.9, 15.2, 15.5, 18.0, 18.3, 18.6, 18.9, 19.2, 19.5, 22.0, 22.3, 22.6, 22.9, 23.2, 23.5, 26.0, 26.3, 26.6, 26.9, 27.2, 27.5, 30.0, 30.3, 30.6, 30.9, 31.2, 31.5, 34.0, 34.3, 34.6, 34.9, 35.2, 35.5, 38.0, 38.3, 38.6, 38.9, 39.2, 39.5};            // start time for each tone
    double dur[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}; //duration of each tone

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



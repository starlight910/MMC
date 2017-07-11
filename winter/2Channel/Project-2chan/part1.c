#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mix.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part1(int sr, double *tone, double *left, double *right, double *pan)
{
	int Left = 0 ;                  // left channel
	int Right = 1 ;                 // right channel
	
	int i, nTones = 8 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {440, 440, 440, 440, 440, 440, 440, 440} ;  // carrier freqs
	double Modulator[] = {200, 250, 300, 350, 400, 450, 500, 550} ;// mod freqs
    double PD[] = {2, 2, 2, 2, 2, 2, 2, 2} ;                    // peak deviation
	int nFMTones = 10 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.25, 0.50, 0.75, 1.0};
	double A[] = {0.25, 0.50, 1.0, 0.5, 0.0};
	
	double startTime[] = {2.0, 3.0, 5.0, 10.0, 13.0, 17.0, 21.0, 25.0};            // start time for each tone
    double dur[] = {6, 7, 9, 7, 6, 9, 7, 8}; //duration of each tone

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



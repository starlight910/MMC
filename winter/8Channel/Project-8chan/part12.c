#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part12(int sr, short *tone)
{
	
	int i, nTones = 8 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = {
		329.63, 880, 783.99, 440, 
		392, 523.25, 329.63, 164.81} ;  // carrier freqs

	double Modulator[] = {200, 10, 10, 40, 200, 40, 10} ;// mod freqs
    double PD[] = {2, 1, 1, 3, 3, 3, 2, 2} ;                    // peak deviation
	int nFMTones = 15 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.1, 0.5, 0.8, 1.0};
	double A[] = {0.1, 0.5, 1.0, 0.5, 0.0};
	
	double startTime[] = 
	{
		190.0, 192.0, 199.0, 207.0, 
		212.0, 220.0, 222.0, 230.0};            // start time for each tone
    double dur[] = {30, 10, 14, 5, 10, 10, 20, 14};

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur[i] * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur[i], sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;

	   if(i == 0 || i == 3 || i == 7)
	   {
		   mixAdd(tone, startTime[i], dur[i], 2) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
		}
		else if( i == 1 || i == 6)
		{
			mixAdd(tone, startTime[i], dur[i], 1) ;
			mixAdd(tone, startTime[i], dur[i], 2) ;
		}
		else if( i == 2 || i == 5)
		{
			mixAdd(tone, startTime[i], dur[i], 0) ;
			mixAdd(tone, startTime[i], dur[i], 3) ;
			mixAdd(tone, startTime[i], dur[i], 4) ;
		}
	   else if(i == 4)
	   {
		   mixAdd(tone, startTime[i], dur[i], 4) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
	   }


    free(tone);
        }
}



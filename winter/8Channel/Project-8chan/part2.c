#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part2(int sr, short *tone)
{
	
	int i, nTones = 8 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = 
	{
		440, 440, 415.30, 329.63, 
		440, 440, 415.30, 329.63} ;  // carrier freqs
	double Modulator[] = 
	{
		100, 70, 70, 10, 
		100, 70, 70, 10 } ;// mod freqs
    double PD[] = 
	{
		2, 1, 1, 2, 
		2, 1, 1, 2} ;                    // peak deviation
	int nFMTones = 10 ;
	
	double nPoints = 4;
	double envType = 1;
	
	double T[] = {0.0, 0.1, 0.75, 1.0};
	double A[] = {0.0, 1.0, 0.5, 0.0};
	
	double startTime[] = 
	{
		14.0, 18.0, 18.3, 22.0, 
		26.0, 30.0, 30.3, 34.0 };            // start time for each tone
    double dur[] = 
	{
		3, 2, 2, 5, 
		3, 2, 2, 5}; // Duration of each tone

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur[i] * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur[i], sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;

	   if ( i == 0 || i == 6)
	   {
		   mixAdd(tone, startTime[i], dur[i], 1) ;
		   mixAdd(tone, startTime[i], dur[i], 3) ;
	   }
	   else if ( i == 1 || i == 5)
	   {
		   mixAdd(tone, startTime[i], dur[i], 2) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
	   }
	   else if ( i == 2 || i == 4)
	   {
		   mixAdd(tone, startTime[i], dur[i], 3) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
	   }
	   else if ( i == 3)
	   {
		   mixAdd(tone, startTime[i], dur[i], 0) ;
		   mixAdd(tone, startTime[i], dur[i], 4) ;
		   mixAdd(tone, startTime[i], dur[i], 6) ;
	   }
	   else if ( i == 7)
	   {
		   mixAdd(tone, startTime[i], dur[i], 2) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
	   }

		

    free(tone);
        }
}



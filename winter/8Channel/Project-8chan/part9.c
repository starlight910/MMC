#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part9(int sr, short *tone)
{
	
	int i, nTones = 14 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = 
	{
		659.62, 440, 523.25, 587.33, 493.88, 659.62, 440, 
		523.25, 587.33, 493.88, 440, 440, 440, 440} ;  // carrier freqs
	double Modulator[] = 
	{
		10, 10, 10, 10, 50, 20, 20, 
		20, 20, 100, 10, 10, 10, 10} ;// mod freqs
    double PD[] = 
	{
		2, 2, 2, 2, 2, 2, 2, 
		2, 2, 2, 1, 1, 1, 1} ;    // peak deviation

	int nFMTones = 20 ;
	
	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.2, 0.75, 1.0};
	double A[] = {0.0, 1.0,  0.3, 0.0};
	
	double startTime[] = 
	{
		109.0, 116.0, 121.0, 127.0, 130.0, 139.0, 146.0, 
		151.0, 157.0, 160.0, 163, 166, 168, 170};            // start time for each tone
    double dur[] = 
	{
		30, 26, 23, 20, 15, 27, 23, 
		22, 18, 12, 10, 7, 7, 7};

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur[i] * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur[i], sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;


	   if(i == 0 || i == 5 || i == 12)
	   {
		   mixAdd(tone, startTime[i], dur[i], 0) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
	   }
	   else if(i == 1 || i == 6 || i == 10)
	   {
		   mixAdd(tone, startTime[i], dur[i], 1) ;
		   mixAdd(tone, startTime[i], dur[i], 3) ;
	   }
	   else if(i == 2 || i == 7 || i == 11 | i == 13)
	   {
		   mixAdd(tone, startTime[i], dur[i], 2) ;
		   mixAdd(tone, startTime[i], dur[i], 4) ;
		   mixAdd(tone, startTime[i], dur[i], 6) ;
	   }
	   else if( i == 3 || i == 8)
	   {
		   mixAdd(tone, startTime[i], dur[i], 1) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
	   }
	   else if( i == 4 || i == 9)
	   {
		   mixAdd(tone, startTime[i], dur[i], 2) ;
		   mixAdd(tone, startTime[i], dur[i], 3) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
	   }


    free(tone);
        }
}



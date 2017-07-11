#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part3(int sr, short *tone)
{
	
	int i, nTones = 48 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = 
	{
		440, 440, 440, 440, 440, 440, 
		440, 440, 440, 440, 440, 440, 
		440, 440, 440, 440, 440, 440, 
		440, 440, 440, 440, 440, 440, 
		440, 440, 440, 440, 440, 440, 
		440, 440, 440, 440, 440, 440, 
		440, 440, 440, 440, 440, 440, 
		440, 440, 440, 440, 440, 440} ;  // carrier freqs

	double Modulator[] = 
	{
		100, 100, 100, 100, 100, 100, 
		100, 100, 100, 100, 100, 100, 
		100, 100, 100, 100, 100, 100, 
		100, 100, 100, 100, 100, 100, 
		100, 100, 100, 100, 100, 100, 
		100, 100, 100, 100, 100, 100,
		100, 100, 100, 100, 100, 100, 
		100, 100, 100, 100, 100, 100 } ;// mod freqs

    double PD[] = 
	{
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1 } ;          // peak deviation
	int nFMTones = 100 ;
	
	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.75, 1.0};
	double A[] = {0.0, 0.7, 0.0};
	
	double startTime[] = 
	{
		41.0, 41.3, 41.6, 41.9, 42.2, 42.5, 
		42.8, 43.1, 43.4, 43.7, 44.0, 44.3, 
		44.6, 44.9, 45.2, 45.5, 45.8, 46.1, 
		46.4, 46.7, 47.0, 47.3, 47.6, 47.9, 
		48.2, 48.5, 48.8, 49.1, 49.4, 49.7, 
		50.0, 50.3, 50.6, 50.9, 51.2, 51.5, 
		51.8, 52.1, 52.4, 52.7, 53.0, 53.3, 
		53.6, 53.9, 54.2, 54.5, 54.8, 55.1};// start time for each tone
    
		double dur = 3 ;

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur, sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur, sr, T, A, nPoints, envType) ;

	   if(
			   i == 1 || i == 16 || i == 23 || 
			   i == 25 || i == 33 || i == 41)
	   {
		   mixAdd(tone, startTime[i], dur, 0) ;
	   }
	   else if(
			   i == 2 || i == 15 || i == 17 || 
			   i == 28 || i == 39 || i == 44)
	   {
		   mixAdd(tone, startTime[i], dur, 1) ;
	   }
	   else if(
			   i == 3 || i == 14 || i == 20 || 
			   i == 26 || i == 34 || i == 47)
	   {
		   mixAdd(tone, startTime[i], dur, 2) ;
	   }
	   else if(
			   i == 4 || i == 13 || i == 22 || 
			   i == 30 || i == 36 || i == 43)
	   {
		   mixAdd(tone, startTime[i], dur, 3) ;
	   }
	   else if(
			   i == 5 || i == 12 || i == 18 || 
			   i == 32 || i == 40 || i == 46)
	   {
		   mixAdd(tone, startTime[i], dur, 4) ;
	   }
	   else if(
			   i == 6 || i == 11 || i == 24 || 
			   i == 31 || i == 38 || i == 45)
	   {
		   mixAdd(tone, startTime[i], dur, 5) ;
	   }
	   else if(
			   i == 7 || i == 10 || i == 19 || 
			   i == 27 || i == 35 || i == 42)
	   {
		   mixAdd(tone, startTime[i], dur, 6) ;
	   }
	   else if(
			   i == 0 || i == 8 || i == 9 || 
			   i == 21 || i == 29 || i == 37)
	   {
		   mixAdd(tone, startTime[i], dur, 7) ;
	   }


    free(tone);
        }
}



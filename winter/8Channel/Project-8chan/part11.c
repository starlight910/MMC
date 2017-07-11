#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part11(int sr, short *tone)
{
	
	int i, nTones = 30 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = 
	{
		440, 440, 220, 440, 440, 220, 
		440, 440, 220, 440, 440, 220, 
		440, 440, 220, 440, 440, 220, 
		440, 440, 220, 440, 440, 220, 
		440, 440, 220, 440, 440, 220} ;  // carrier freqs

	double Modulator[] = 
	{
		10, 10, 300, 10, 10, 300, 
		10, 10, 300, 10, 10, 300, 
		10, 10, 300, 10, 10, 300, 
		10, 10, 300, 10, 10, 300, 
		10, 10, 300, 10, 10, 300} ;// mod freqs

    double PD[] = 
	{
		2, 2, 500, 2, 2, 500, 
		2, 2, 500, 2, 2, 500, 
		2, 2, 600, 3, 3, 900,
		3, 3, 1100, 4, 4, 1300, 
		5, 5, 1500, 6, 6, 2000} ; // peak deviation

	int nFMTones = 40 ;

	double nPoints = 4;
	double envType = 1;
	
	double T[] = {0.0, 0.1, 0.8, 1.0};
	double A[] = {0.0, 1.0, 0.7, 0.0};
 
	double startTime[] = {
		170.0, 170.6, 171.2, 174.0, 174.6, 175.2, 
		178.0, 178.6, 179.2, 182.0, 182.6, 183.2, 
		186.0, 186.6, 187.2, 190.0, 190.6, 191.2, 
		194.0, 194.6, 195.2, 198.0, 198.6, 199.2, 
		202.0, 202.6, 203.2, 206.0, 206.6, 207.2};// start time for each tone
	
    double dur[] = {
		2, 2, 5, 2, 2, 5, 
		2, 2, 5, 2, 2, 5, 
		2, 2, 5, 2, 2, 5, 
		2, 2, 5, 2, 2, 5, 
		2, 2, 5, 2, 2, 5}; //duration of each tone

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur[i] * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur[i], sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;

	   if( i == 2 || i == 8 || i == 14 || i == 20 || i == 26)
	   {
		   mixAdd(tone, startTime[i], dur[i], 0) ;
		   mixAdd(tone, startTime[i], dur[i], 2) ;
		   mixAdd(tone, startTime[i], dur[i], 4) ;
		   mixAdd(tone, startTime[i], dur[i], 6) ;
	   }
	   else if ( i == 5 || i == 11 || i == 17 || i == 23 || i == 29)
	   {
		   mixAdd(tone, startTime[i], dur[i], 1) ;
		   mixAdd(tone, startTime[i], dur[i], 3) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
	   }

	   else if(
			   i == 0 || i == 7 || 
			   i == 10 || i == 13 || 
			   i == 18 || i == 22 || i ==27)
	   {
		   mixAdd(tone, startTime[i], dur[i], 1) ;
		   mixAdd(tone, startTime[i], dur[i], 3) ;
	   }
	   else if(
			   i == 1 || i == 4 || 
			   i == 12 || i == 15 || 
			   i == 21 || i == 24 || i == 28 )
	   {
		   mixAdd(tone, startTime[i], dur[i], 4) ;
		   mixAdd(tone, startTime[i], dur[i], 6) ;
	   }
	   else if(
			   i == 3 || i == 6 || 
			   i == 9 || i == 16 || 
			   i == 19 || i == 25)
	   {
		   mixAdd(tone, startTime[i], dur[i], 1) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
	   }



    free(tone);
        }
}



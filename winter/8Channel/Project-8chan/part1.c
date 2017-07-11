#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part1(int sr, short *tone)
{

	int i, nTones = 60 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = 
	{
		220, 220, 220, 196, 196, 196,
		220, 220, 220, 196, 196, 196,
		220, 220, 220, 196, 196, 196, 
		220, 220, 220, 196, 196, 196, 
		220, 220, 220, 196, 196, 196, 
		220, 220, 220, 196, 196, 196, 
		220, 220, 220, 196, 196, 196, 
		220, 220, 220, 196, 196, 196, 
		220, 220, 220, 196, 196, 196, 
		220, 220, 220, 196, 196, 196} ;  // carrier freqs
	double Modulator[] = 
	{
		50, 50, 50, 50, 50, 50, 
		40, 40, 40, 40, 40, 40, 
		50, 50, 50, 50, 50, 50, 
		40, 40, 40, 40, 40, 40, 
		50, 50, 50, 50, 50, 50, 
		40, 40, 40, 40, 40, 40, 
		50, 50, 50, 50, 50, 50, 
		40, 40, 40, 40, 40, 40, 
		50, 50, 50, 50, 50, 50, 
		40, 40, 40, 40, 40, 40 } ;// mod freqs
    double PD[] = 
	{
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1, 1, 1, 1, 1, 1, 
		1 ,1 ,1 ,1, 1, 1 } ; // peak deviation

	int nFMTones = 60 ;

	double nPoints = 3;
	double envType = 1;
	
	double T[] = {0.0, 0.5, 1.0};
	double A[] = {1.0, 0.5, 0.0};
	
	double startTime[] = 
	{
		2.0, 2.3, 2.6, 2.9, 3.2, 3.5, 
		6.0, 6.3, 6.6, 6.9, 7.2, 7.5, 
		10.0, 10.3, 10.6, 10.9, 11.2, 11.5, 
		14.0, 14.3, 14.6, 14.9, 15.2, 15.5, 
		18.0, 18.3, 18.6, 18.9, 19.2, 19.5, 
		22.0, 22.3, 22.6, 22.9, 23.2, 23.5, 
		26.0, 26.3, 26.6, 26.9, 27.2, 27.5, 
		30.0, 30.3, 30.6, 30.9, 31.2, 31.5, 
		34.0, 34.3, 34.6, 34.9, 35.2, 35.5, 
		38.0, 38.3, 38.6, 38.9, 39.2, 39.5};            // start time for each tone

	double dur = 2 ; //duration of each tone

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur, sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur, sr, T, A, nPoints, envType) ;

	   if ( 
			   i == 1 || i == 7 || i == 13 || 
			   i == 19 || i == 25 || i == 31 || 
			   i == 37 || i == 43 || i == 49 || 
			   i == 55 )
	   {
			mixAdd(tone, startTime[i], dur, 0) ;
		    mixAdd(tone, startTime[i], dur, 1) ;
		    mixAdd(tone, startTime[i], dur, 5) ;
	   }
	   else if ( 
			   i == 2 || i ==  8 || i ==  14 || 
			   i == 20 || i == 26 || i == 32 || 
			   i == 38 || i == 44 || i == 50 ||
			   i == 56 )
	   {
		   mixAdd(tone, startTime[i], dur, 2) ;
		   mixAdd(tone, startTime[i], dur, 3) ;
		   mixAdd(tone, startTime[i], dur, 6) ;
	   }
	   else if (
			   i == 3 || i == 9 || i == 15 || 
			   i == 21 || i == 27 || i == 33 || 
			   i == 39 || i == 45 || i == 51 || 
			   i == 57 )
	   {
		   mixAdd(tone, startTime[i], dur, 4) ;
		   mixAdd(tone, startTime[i], dur, 5) ;
		   mixAdd(tone, startTime[i], dur, 7) ; 
	   }
	   else if(
			   i == 4 || i == 10 || i == 16 || 
			   i == 22 || i == 28 || i == 34 || 
			   i == 40 || i == 46 || i == 52 || 
			   i == 58 )
	   {
		   mixAdd(tone, startTime[i], dur, 7) ;
		   mixAdd(tone, startTime[i], dur, 6) ;
		   mixAdd(tone, startTime[i], dur, 2) ; 

	   }
	   else if(
			   i == 5 || i == 11 || i == 17 || 
			   i == 23 || i == 29 || i == 35 || 
			   i == 41 || i == 47 || i == 53 || 
			   i == 59 )
	   {
		   mixAdd(tone, startTime[i], dur, 5) ;
		   mixAdd(tone, startTime[i], dur, 4) ;
		   mixAdd(tone, startTime[i], dur, 1) ; 

	   }
	   else if(
			   i == 0 || i == 6 || i == 12 || 
			   i == 18 || i == 24 || i == 30 || 
			   i == 36 || i == 42 || i == 48 || 
			   i == 54 )
	   {
		   mixAdd(tone, startTime[i], dur, 3) ;
		   mixAdd(tone, startTime[i], dur, 2) ;
		   mixAdd(tone, startTime[i], dur, 0) ; 

	   }



    free(tone);
        }
}



#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part6(int sr, short *tone)
{
	
	int i, nTones = 12 ;            // counter, total number of tones
	double dB = 87 ;                // amplitude of each tone
	
	double Carrier[] = 
	{
		82.41, 82.41, 82.41, 82.41, 82.41, 82.41, 
		82.41, 82.41, 164.81, 164.81, 164.81, 164.81} ;  // carrier freqs
	double Modulator[] = 
	{
		10, 10, 10, 10, 10, 10, 
		10, 10, 200, 200, 200, 200} ;// mod freqs
    double PD[] = 
	{
		5, 5, 5, 5, 5, 5, 
		5, 5, 3, 3, 3, 3} ;    // peak deviation


	int nFMTones = 20 ;
	
	double nPoints = 5;
	double envType = 1;
	
	double T[] = {0.0, 0.1, 0.5, 0.8, 1.0};
	double A[] = {0.0, 1.0, 0.5, 0.1, 0.0};
	
	double startTime[] = 
	{
		63.0, 65.0, 67.0, 69.0, 71.0, 73.0, 
		75.0, 77.0, 79.0, 82.0, 85.0, 88.0 }; // start time for each tone

    double dur[] = 
	{
		3, 3, 3, 3, 3, 3, 
		3, 3, 5, 5, 5, 5};

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur[i] * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur[i], sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur[i], sr, T, A, nPoints, envType) ;


	   if( i == 0 || i == 4 || i == 8 || i == 10)
	   {
		   mixAdd(tone, startTime[i], dur[i], 0) ;
		   mixAdd(tone, startTime[i], dur[i], 3) ;
		   mixAdd(tone, startTime[i], dur[i], 6) ;
	   }
	   else if( i == 1 || i == 3 || i == 6 || i == 9)
	   {
		   mixAdd(tone, startTime[i], dur[i], 1) ;
		   mixAdd(tone, startTime[i], dur[i], 2) ;
		   mixAdd(tone, startTime[i], dur[i], 5) ;
	   }
	   else if ( i == 2 || i == 5 || i == 7 || i == 11)
	   {
		   mixAdd(tone, startTime[i], dur[i], 0) ;
		   mixAdd(tone, startTime[i], dur[i], 4) ;
		   mixAdd(tone, startTime[i], dur[i], 7) ;
	   }


    free(tone);
        }
}



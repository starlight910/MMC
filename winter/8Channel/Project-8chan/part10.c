#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"                 // include declarations for fm()
#include "mixtwo.h"                // declarations for the 'mix' functions
#include "env.h"                // declarations for 'adsr2()'


void *part10(int sr, short *tone)
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
		10, 10, 10, 10, 10, 10, 
		10, 10, 10, 10, 10, 10, 
		10, 10, 10, 10, 10, 10, 
		10, 10, 10, 10, 10, 10, 
		10, 10, 10, 10, 10, 10, 
		10, 10, 10, 10, 10, 10, 
		10, 10, 10, 10, 10, 10, 
		10, 10, 10, 10, 10, 10 } ;// mod freqs

    double PD[] = 
	{
		2, 1, 1, 2, 1, 1, 
		2, 1, 1, 2, 1, 1, 
		2, 1, 1, 2, 1, 1, 
		2, 1, 1, 2, 1, 1, 
		2, 1, 1, 2, 1, 1, 
		2, 1, 1, 2, 1, 1, 
		2, 1, 1, 2, 1, 1, 
		2, 1, 1, 2, 1, 1 } ;          // peak deviation
	int nFMTones = 100 ;
	
	double nPoints = 4;
	double envType = 1;
	
	double T[] = {0.0, 0.75, 1.0};
	double A[] = {0.0, 0.7, 0.0};
	
	double startTime[] = 
	{
		146.0, 146.3, 146.6, 146.9, 147.2, 147.5, 
		147.8, 148.1, 148.4, 148.7, 149.0, 149.3, 
		149.6, 149.9, 150.2, 150.5, 150.8, 151.1, 
		151.4, 151.7, 152.0, 152.3, 152.6, 152.9, 
		153.2, 153.5, 153.8, 154.1, 154.4, 154.7, 
		155.0, 155.3, 155.6, 155.9, 156.2, 156.5, 
		156.8, 156.1, 156.4, 156.7, 157.0, 157.3, 
		157.6, 157.9, 158.2, 158.5, 158.8, 159.1}; // start time for each tone
    double dur = 3; //duration of each tone

	short *output;  // arrays for each tone, and the output

        for ( i = 0 ; i < nTones ; i++ ) // create the tones 
		{
        tone = (short *)Malloc(dur * sr * sizeof(short));
        // create one FM tone, and apply an envelope
       fm(tone, dur, sr, dB,
       Carrier[i%nFMTones], Modulator[i%nFMTones],     PD[i%nFMTones]) ;
       adsr2(tone, dur, sr, T, A, nPoints, envType) ;

	   if ( 
			   i == 0 || i == 6 || i == 12 || i == 18 || 
			   i == 24 || i == 30 || i == 36 || i == 42 )
        {
             mixAdd(tone, startTime[i], dur, 0) ;
             mixAdd(tone, startTime[i], dur, 2) ;
             mixAdd(tone, startTime[i], dur, 4) ;
        }
        else if ( 
				i == 1 || i ==  7 || i ==  13 || i == 19 || 
				i == 25 || i == 31 || i == 37 || i == 43 )
        {
            mixAdd(tone, startTime[i], dur, 1) ;
            mixAdd(tone, startTime[i], dur, 3) ;
            mixAdd(tone, startTime[i], dur, 5) ;
        }
        else if (
				i == 2 || i == 8 || i == 14 || i == 20 || 
				i == 26 || i == 32 || i == 38 || i == 44)
        {
            mixAdd(tone, startTime[i], dur, 2) ;
            mixAdd(tone, startTime[i], dur, 4) ;
            mixAdd(tone, startTime[i], dur, 6) ;
        }
        else if(
				i == 3 || i == 9 || i == 15 || i == 21 || 
				i == 27 || i == 33 || i == 39 || i == 45 )
        {
            mixAdd(tone, startTime[i], dur, 7) ;
            mixAdd(tone, startTime[i], dur, 5) ;
            mixAdd(tone, startTime[i], dur, 3) ;
 
        }
        else if(
				i == 4 || i == 10 || i == 16 || i == 22 || 
				i == 28 || i == 34 || i == 40 || i == 46 )
        {
         mixAdd(tone, startTime[i], dur, 6) ;
         mixAdd(tone, startTime[i], dur, 4) ;
         mixAdd(tone, startTime[i], dur, 2) ;
 
        }
       else if(
			   i == 5 || i == 11 || i == 17 || i == 23 || 
			   i == 29 || i == 35 || i == 41 || i == 47 )
		{
		  mixAdd(tone, startTime[i], dur, 0) ;
		  mixAdd(tone, startTime[i], dur, 1) ;
		  mixAdd(tone, startTime[i], dur, 2) ;
	   }


    free(tone);
        }
}



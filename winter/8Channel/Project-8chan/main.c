#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"         // include declarations for fm()
#include "cat.h"        // declarations for concatenate()
#include "mixtwo.h"        // declarations for the 'mix' functions
#include "env.h"        // declarations for 'adsr2()'

int main(void)
{
	
    int nchan = 8,          // number of channels of sound (2)
    sr = 44100 ;            // samples per second

	
	double *channelNumber ;

    short *output;

    double *tone;
    double totalDur = 246 ; // total duration

	void *part1(int sr, double *tone);
	void *part2(int sr, double *tone);
	void *part3(int sr, double *tone);
	void *part4(int sr, double *tone);
	void *part5(int sr, double *tone);
	void *part6(int sr, double *tone);
	void *part7(int sr, double *tone);
	void *part8(int sr, double *tone);
	void *part9(int sr, double *tone);
	void *part10(int sr, double *tone);
	void *part11(int sr, double *tone);
	void *part12(int sr, double *tone);




	mixSetup(totalDur, sr, nchan);

    part1(sr, tone);
	part2(sr, tone);
	part3(sr, tone);
	part4(sr, tone);
	part5(sr, tone);
	part6(sr, tone);
	part7(sr, tone);
	part8(sr, tone);
	part9(sr, tone);
	part10(sr, tone);
	part11(sr, tone);
	part12(sr, tone);






	output = mixConvertTo16Bits() ;
	

	sfsave("8channel.wav", output, totalDur, sr, nchan) ;
	
	Free(output) ;

	exit(EXIT_SUCCESS) ;
}

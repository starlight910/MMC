#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

#include "fm.h"         // include declarations for fm()
#include "cat.h"        // declarations for concatenate()
#include "mix.h"        // declarations for the 'mix' functions
#include "env.h"        // declarations for 'adsr2()'

int main(void)
{
	
    int nchan = 2,          // number of channels of sound (2)
    sr = 44100 ;            // samples per second
    double *left ;             // identify left channel
	double *right ;            // identify right channel

    short *output;
    double *pan;
    double *tone;
    double totalDur = 246 ; // total duration

	void *part1(int sr, double *left, double *right, double *pan, double *tone);
    void *part2(int sr, double *left, double *right, double *pan, double *tone);
	void *part3(int sr, double *left, double *right, double *pan, double *tone);
	void *part4(int sr, double *left, double *right, double *pan, double *tone);
	void *part5(int sr, double *left, double *right, double *pan, double *tone);
    void *part6(int sr, double *left, double *right, double *pan, double *tone);
    void *part7(int sr, double *left, double *right, double *pan, double *tone);
	void *part8(int sr, double *left, double *right, double *pan, double *  tone);
	void *part9(int sr, double *left, double *right, double *pan, double *tone);
	void *part10(int sr, double *left, double *right, double *pan, double *tone);
	void *part11(int sr, double *left, double *right, double *pan, double *tone);
	void *part12(int sr, double *left, double *right, double *pan, double * tone);




	mixSetup(totalDur, sr, nchan);

    part1(sr, left, right, pan, tone);
	part2(sr, left, right, pan, tone);
	part3(sr, left, right, pan, tone);
	part4(sr, left, right, pan, tone);
	part5(sr, left, right, pan, tone);
    part6(sr, left, right, pan, tone);
    part7(sr, left, right, pan, tone);
	part8(sr, left, right, pan, tone);
	part9(sr, left, right, pan, tone);
	part10(sr, left, right, pan, tone);
	part11(sr, left, right, pan, tone);
	part12(sr, left, right, pan, tone);




	output = mixConvertTo16Bits() ;
	

	sfsave("8channel.wav", output, totalDur, sr, nchan) ;
	
	Free(output) ;

	exit(EXIT_SUCCESS) ;
}

#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void concatenate(short output[], short input[], double st, double dur, int sr) ;

int main(void)
{
	//
	//	variables for the final sound
	//
	int sr = 44100 ;		// sampling rate 
	int nchan = 1 ;			// number of channels of sound
	int samples ;			// number of samples of the sound
	short *final ;			// final output
	double finalDuration ;
	double startTime ;		// variable to store the start time of a tone

	//
	//	variables for part 1
	//	
	short *part1(int sr) ;	// function declaration
	short *part1sound ;				// array for sound
	double part1td ;				// total Duration of part 1

	//
	//	variables for part 2
	//
	short *part2(int sr) ;	// function declaration
	short *part2sound ;				// array for sound
	double part2td ;				// total duration of part 2

	double getPart1Dur(void) ;
	double getPart2Dur(void) ;

	//
	//	calculate the total duration of part 1 and part 2, then 
	//	find the finalDuration
	//

	part1td = getPart1Dur() ;
	part2td = getPart2Dur() ;


	finalDuration = part1td + part2td ;	// set the total duration
	samples = finalDuration * sr ;	// calculate and allocate memory
	final = (short *)Malloc(samples * sizeof(short)) ;


	startTime = 0 ;		// initialize start time

	//
	//	Create the first set of tones: part1()
	//

	part1sound = part1(sr) ;
	concatenate(final, part1sound, startTime, part1td, sr) ;
	Free(part1sound) ;
	startTime += part1td ;

	//
	//	Create the second set of tones: part2()
	//

	part2sound = part2(sr) ;
	concatenate(final, part2sound, startTime, part2td, sr) ;
	Free(part2sound) ;
	startTime += part2td ;

	sfsave("addsyn.wav", final, finalDuration, sr, nchan) ;

	exit(EXIT_SUCCESS) ;
}

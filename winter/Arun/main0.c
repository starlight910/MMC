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
	int nchan = 1, samples, sr = 44100 ;		
	short *final ;			// final output
	double startTime, finalDuration ;

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

	// 
	// variables for part 3
	//
	short *part3(int sr) ;
	short *part3sound ;
	double part3td ;

	// two function declarations
	double getPart1Dur(void) ;
	double getPart2Dur(void) ;
	double getPart3Dur(void) ;

	part1td = getPart1Dur() ;	//	get the durations of part 1 and part 2
	part2td = getPart2Dur() ;
	part3td = getPart3Dur() ;

	finalDuration = part1td + part2td + part3td ;	// set the total duration
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
	
	//
	//	Create the thir set of tones: part3()
	//

	part3sound = part3(sr) ;
	concatenate(final, part3sound, startTime, part3td, sr) ;
	Free(part3sound) ;
	startTime += part3td ;

	// playbuffer(final, finalDuration, sr, nchan, 1) ;

	sfsave("addsyn.wav", final, finalDuration, sr, nchan) ; // save the sounds

	Free(final) ;

	exit(EXIT_SUCCESS) ;
}

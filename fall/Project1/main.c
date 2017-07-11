#include <stdio.h>
#include <stdlib.h>
#include <sf.h>
#include <sfmisc.h>

// declarations for external functions
void concatenate(short output[], short input[], double st, double dur, int sr) ;

// short *mix(short *part1sound, double dur1, short *part2sound, double dur2, int sr) ;

int main(void)
{
	//
	//	variables for the final sound
	//
	int sr = 44100 ;		// sampling rate 
	int nchan = 1 ;			// number of channels of sound
	int samples ;			// number of samples of the sound
	short *final ;			// final output
	double finalDuration ;  // Total duration
	double startTime ;		// variable to store the start time of a tone

	//  variables for part 0
	short *part0(int sr) ;  // function declaration
	short *part0sound ;     // array for sound
	double part0td ;        // total Duration of part

	//  variables for part 01
	short *part01(int sr) ;
	short *part01sound ;
	double part01td ;

	//	variables for part 1	
	short *part1(int sr) ;	
	short *part1sound ;		
	double part1td ;		

	//	variables for part 2
	short *part2(int sr) ;	
	short *part2sound ;		
	double part2td ;		

	//  variables for part 4
	short *part4(int sr) ; 
	short *part4sound ;    
	double part4td ;       

	//  variables for part 5
	short *part5(int sr) ;
	short *part5sound ;
	double part5td ;

	//  variable for part 6
	short *part6(int sr) ;
	short *part6sound ;
	double part6td ;

	//  variable for part 7
	short *part7(int sr) ;
    short *part7sound ;
    double part7td ;

	//  variable for part 8
	short *part8(int sr) ;
	short *part8sound ;
	double part8td ;

	//  variable for part 9
	short *part9(int sr) ;
	short *part9sound ;
	double part9td ;


	double getPart0Dur(void) ;
	double getPart01Dur(void) ;
	double getPart1Dur(void) ;
	double getPart2Dur(void) ;
	double getPart4Dur(void) ;
	double getPart5Dur(void) ;
	double getPart6Dur(void) ;
	double getPart7Dur(void) ;
	double getPart8Dur(void) ;
	double getPart9Dur(void) ;


	// Calculate the total duration of all parts then find the finalDuration
	part0td = getPart0Dur() ;
	part01td = getPart01Dur() ;
	part1td = getPart1Dur() ;
	part2td = getPart2Dur() ;
	part4td = getPart4Dur() ;
	part5td = getPart5Dur() ;
	part6td = getPart6Dur() ;
	part7td = getPart7Dur() ;
	part8td = getPart8Dur() ;
	part9td = getPart9Dur() ;



	finalDuration = part1td + part2td + part1td + part2td + part0td + part0td + part01td + part01td + part0td + part0td + part01td + part01td +  part4td + part4td;	// set the total duration
	samples = finalDuration * sr ;	// calculate and allocate memory
	final = (short *)Malloc(samples * sizeof(short)) ;


	startTime = 0 ;		// initialize start time

	fprintf(stderr," < Verse 1 >\n") ;


	//	Create the first set of tones: part1()
	fprintf(stderr,"\tPart 1 ... ") ;
	part1sound = part1(sr) ;
	concatenate(final, part1sound, startTime, part1td, sr) ;
	Free(part1sound) ;
	startTime += part1td ;
	fprintf(stderr,"\tDone\n") ;

	//	Create the second set of tones: part2()
	fprintf(stderr,"\tPart 2 ... ") ;
	part2sound = part2(sr) ;
	concatenate(final, part2sound, startTime, part2td, sr) ;
	Free(part2sound) ;
	startTime += part2td ;
	fprintf(stderr,"\tDone\n") ;

	//  Create the third set of tones: part1()
     fprintf(stderr,"\tPart 1 ... ") ;
     part1sound = part1(sr) ;
     concatenate(final, part1sound, startTime, part1td, sr) ;
     Free(part1sound) ;
     startTime += part1td ;
     fprintf(stderr,"\tDone\n") ;
 
	//  Create the 4th set of tones: part2()
	fprintf(stderr,"\tPart 2 ... ") ;
	part2sound = part2(sr) ;
	concatenate(final, part2sound, startTime, part2td, sr) ;
	Free(part2sound) ;
	startTime += part2td ;
	fprintf(stderr,"\tDone\n") ;


	fprintf(stderr,"-------------------------------------\n\n") ;


	fprintf(stderr," < Chorus >\n") ;

	//  Create the 5th set of tones: part0()
	fprintf(stderr,"\tPart 0 ... ") ;
	part0sound = part0(sr) ;
	concatenate(final, part0sound, startTime, part0td, sr) ;
	Free(part0sound) ;
	startTime +=part0td ;
	fprintf(stderr,"\tDone\n") ;
	
	//  Create the 6th set of tones: part0()
	fprintf(stderr,"\tPart 0 ... ") ;
    part0sound = part0(sr) ;
    concatenate(final, part0sound, startTime, part0td, sr) ;
    Free(part0sound) ;
    startTime +=part0td ;
    fprintf(stderr,"\tDone\n") ;
	
	//  Create the 7th set of tones: part01()
    fprintf(stderr,"\tPart 01 ... ") ;
    part01sound = part01(sr) ;
    concatenate(final, part01sound, startTime, part01td, sr) ;
    Free(part01sound) ;
    startTime +=part01td ;
    fprintf(stderr,"\tDone\n") ;

	//  Create the 8th set of tones: part01()
    fprintf(stderr,"\tPart 01 ... ") ;
    part01sound = part01(sr) ;
    concatenate(final, part01sound, startTime, part01td, sr) ;
    Free(part01sound) ;
    startTime +=part01td ;
    fprintf(stderr,"\tDone\n") ;
 
	//  Create the 5th set of tones: part0()
    fprintf(stderr,"\tPart 0 ... ") ;
    part0sound = part0(sr) ;
    concatenate(final, part0sound, startTime, part0td, sr) ;
    Free(part0sound) ;
    startTime +=part0td ;
    fprintf(stderr,"\tDone\n") ;

    //  Create the 6th set of tones: part0()
    fprintf(stderr,"\tPart 0 ... ") ;
    part0sound = part0(sr) ;
    concatenate(final, part0sound, startTime, part0td, sr) ;
    Free(part0sound) ;
    startTime +=part0td ;
    fprintf(stderr,"\tDone\n") ;

    //  Create the 7th set of tones: part01()
    fprintf(stderr,"\tPart 01 ... ") ;
    part01sound = part01(sr) ;
    concatenate(final, part01sound, startTime, part01td, sr) ;
    Free(part01sound) ;
    startTime +=part01td ;
    fprintf(stderr,"\tDone\n") ;

    //  Create the 8th set of tones: part01()
    fprintf(stderr,"\tPart 01 ... ") ;
    part01sound = part01(sr) ;
    concatenate(final, part01sound, startTime, part01td, sr) ;
    Free(part01sound) ;
    startTime +=part01td ;
    fprintf(stderr,"\tDone\n") ;
	
	fprintf(stderr,"--------------------------------------\n\n") ;

	
	//  Create the 5th set of tones: part4()
    fprintf(stderr,"\tPart 4 ... ") ;
    part4sound = part4(sr) ;
    concatenate(final, part4sound, startTime, part4td, sr) ;
    Free(part4sound) ;
    startTime +=part4td ;
    fprintf(stderr,"\tDone\n") ;

    //  Create the 5th set of tones: part4()

    fprintf(stderr,"\tPart 4 ... ") ;
    part4sound = part4(sr) ;
    concatenate(final, part4sound, startTime, part4td, sr) ;
    Free(part4sound) ;
    startTime +=part4td ;
    fprintf(stderr,"\tDone\n") ;

	/*
	//  Create the 12th set of tones: part11()

    fprintf(stderr,"\tpart 7 ... ") ;
    part7sound = part7(sr) ;
    concatenate(final, part7sound, startTime, part7td, sr) ;
    Free(part7sound) ;
    startTime +=part7td ;
    fprintf(stderr,"\tDone\n") ;

	//  Create the first set of tones: part1()
	
    fprintf(stderr,"\tPart 6 ... ") ;
    part6sound = part6(sr) ;
    concatenate(final, part6sound, startTime, part6td, sr) ;
    Free(part6sound) ;
    startTime += part6td ;
    fprintf(stderr,"\tDone\n") ;
	
	//  Create the first set of tones: part1()

    fprintf(stderr,"\tPart 01 ... ") ;
    part01sound = part01(sr) ;
    concatenate(final, part01sound, startTime, part01td, sr) ;
    Free(part01sound) ;
    startTime += part01td ;
    fprintf(stderr,"\tDone\n") ;
	
	//  Create the first set of tones: part1()
	
    fprintf(stderr,"\tPart 01 ... ") ;
    part01sound = part01(sr) ;
    concatenate(final, part01sound, startTime, part01td, sr) ;
    Free(part01sound) ;
    startTime += part01td ;
    fprintf(stderr,"\tDone\n") ;

	//  Create the 8th set of tones: part7()

	fprintf(stderr,"\tPart 5 ... ") ;
	part5sound = part5(sr) ;
	concatenate(final, part5sound, startTime, part5td, sr) ;
	Free(part5sound) ;
	startTime +=part5td ;
	fprintf(stderr,"\tDone\n") ;

	//  Create the 9th set of tones: part8()
	
	fprintf(stderr,"\tpart 6 ... ") ;
	part6sound = part6(sr) ;
	concatenate(final, part6sound, startTime, part6td, sr) ;
	Free(part6sound) ;
	startTime +=part6td ;
	fprintf(stderr,"\tDone\n") ;
	 
	 //  Create the 11th set of tones: part10()

     fprintf(stderr,"\tpart 8 ... ") ;
     part8sound = part8(sr) ;
     concatenate(final, part8sound, startTime, part8td, sr) ;
     Free(part8sound) ;
     startTime +=part8td ;
     fprintf(stderr,"\tDone\n") ;
	 
	 //  Create the 12th set of tones: part11()

     fprintf(stderr,"\tpart 9 ... ") ;
     part9sound = part9(sr) ;
     concatenate(final, part9sound, startTime, part9td, sr) ;
     Free(part9sound) ;
     startTime +=part9td ;
     fprintf(stderr,"\tDone\n") ;
*/

	fprintf(stderr,"Before sfsave\n") ;
	
	//mix(part1sound, dur1, part2sound, dur2, sr) ;

	sfsave("Project1.wav", final, finalDuration, sr, nchan) ;

	exit(EXIT_SUCCESS) ;
}

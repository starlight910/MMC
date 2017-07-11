#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sf.h>
#include <sfmisc.h>

#include "random.h"

//
//	getMetronomeStartTime()
//
//	returns the tempo at which the 'metronome' starts its ticks
//	'tempo' is number of ticks per minute
//

int getMetronomeStartTempo(void)
{
	const int MM[] = {160, 168, 176, 184, 192, 200, 208};
	const int nItems = 7 ;		// number of MM marks in array
	int indx = nItems * frandom() ;
	return MM[indx] ;
}


//
//	setDegreeOfCurve()
//
//	returns the value for theta, which sets the intensity of the
//	logarithmic curve by which the duration of the gaps will be
//	determined
//

double setDegreeOfCurve(void)
{
	const double centerTheta = 5 ;
	const double maxTheta = centerTheta + 2 ;
	const double minTheta = centerTheta - 2 ;
	static int flag, N ;
	static double inc ;
	int indx ;

	if ( flag == 0 ) {
		flag = 1 ;
		N = ( maxTheta - minTheta ) * 10 ;	//set percision: 3.0, 3.1, 3.2, etc.
		inc = ( maxTheta - minTheta ) / N ;
	}

	indx = N * frandom() ;	// pick the index

	return indx * inc + minTheta ;
}


//
//	setTotalDuration()
//
//	returns a value for the total duration, which will be between 9:30
//	and 10:30
//

double setTotalDuration(void)
{
	const double duration = 10 * 60 ; //		10 minutes (600 seconds)
	const double maxDur = duration + 30 ;
	const double minDur = duration - 30 ;
	double totalDuration ;

	totalDuration = (maxDur - minDur) * frandom() + minDur ;

	return totalDuration ;
}

char *setSoundfileName(void)
{
	static int counter ;
	static char soundfile[128] ;

	memset(soundfile, 0, 128) ;

	sprintf(soundfile, "metro%d.wav", counter++) ;

	if ( access(soundfile, F_OK) == 0 ) 
		unlink(soundfile) ;

	return soundfile ;
}

int main(void)
{
	double duration ;				// total duration of the sound
	double maxGapDuration = 3.0 ;	// max duration between ticks
	double theta, *gapList ;
	char *soundfile ;
	int tempo, nGaps, i, nRuns = 1 ;

	extern double *makeGapList(int *nGaps, double duration, 
			double maxGapDuration, int temp, double theta) ;
	extern void tick(double gapList[], int nGaps, char *soundfile);

	setRandomSeed(time(NULL)) ;

	fprintf(stderr,"\ttick tock tick tock tick ... ") ;

	for ( i = 0 ; i < nRuns ; i++ ) {

		duration = setTotalDuration() ;		// length of run in seconds
		tempo = getMetronomeStartTempo() ;	// initial tempo
		theta = setDegreeOfCurve() ;		// intensity of exponential curve

		// create list of durations between ticks
		gapList = makeGapList(&nGaps, duration, maxGapDuration, tempo, theta) ;

		soundfile = setSoundfileName() ;	// output soundfile

		tick(gapList, nGaps, soundfile) ;	// create ticks, write soundfile
		Free(gapList) ;
	}

	fprintf(stderr,"tock\n") ;

	return 0 ;
}

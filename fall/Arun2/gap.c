#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

//
//	getGapSize(timeNow, timeTotal, minGap, maxGap, theta)
//
//	returns the 'gapSize' at 'timeNow'
//
//	minGap and maxGap are the inital and final gap sizes
//	theta is the degree of the curve
//	timeTotal is the total duration of the sound
//

double getGapSize(double timeNow, double timeTotal,
		double minGap, double maxGap, double theta)
{
	double t, y ;
	t = timeNow / timeTotal ;	// fractional value between 0-1
	y = minGap + (maxGap-minGap) * (1 - exp(t*theta)) / (1 - exp(theta)) ;
	return y ;
}


//
// makeGapList(*N, totalDuration, maxGap, MM, theta)
//
// returns a list of durations (distances between ticks)
//
// *N = length of the list
// totalDuration : totalDuration of the sound (eg, 10 minutes or 600 seconds)
// maxGap : max distance between ticks
// MM : initial tempo
// theta : intensity of the exponential curve
//

double *makeGapList(
		int *N,						// length of the darray
		double totalDuration,		// total duration of soundfile, eg: 600 sec
		double maxGap,				// eg: 2 sec
		int MM,						// initial tempo
		double theta)				// theta = degree of the curve
{
	double *gapList ;
	double currentTime = 0;
	double gap, minGap ;
	int i ;

	minGap = 60.0 / MM ;

	*N = 0 ;			// first find out the NUMBER of items in the list
	currentTime = 0 ;
	while ( currentTime < totalDuration ) {
		gap = getGapSize(currentTime, totalDuration, minGap, maxGap, theta) ;
		currentTime += gap ;
		*N += 1 ;
	}

	gapList = (double *)Malloc(*N * sizeof(double)) ;

	currentTime = 0 ;			// now fill up the list
	for ( i = 0 ; i < *N ; i++ ) {
		gap = getGapSize(currentTime, totalDuration, minGap, maxGap, theta) ;
		gapList[i] = gap ;
		currentTime += gap ;
	}

	return gapList ;
}



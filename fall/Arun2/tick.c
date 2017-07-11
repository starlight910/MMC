#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sf.h>
#include <sfmisc.h>
#include "random.h"

//
//	tick(gapList, N, soundfile)
//
//	create a list of ticks based on the 'gapList', and write it 
//	to a soundfile
//

void tick(double *gapList, int N, char *soundfile)
{
	extern void concatenate(short output[], short input[], 
			double st, double dur, int sr) ;
	extern void tock1(short *window, double dur, int sr) ;
	extern void tock2(short *window, double dur, int sr) ;

	double totalDuration, maxGap, st ;
	short *sequence, *oneTick ;
	int i, sr = 44100 ;

	totalDuration = 0 ;				// set the totalDuration by summing
	maxGap = gapList[0] ;			// up the values in 'gapList'
	for ( i = 0 ; i < N ; i++ ) {
		totalDuration += gapList[i] ;
		if ( gapList[i] > maxGap )	// 
			maxGap = gapList[i] ;
	}

	// allocate memory
	sequence = (short *)Malloc(totalDuration * sr * sizeof(short)) ;
	oneTick = (short *)Malloc(maxGap * sr * sizeof(short)) ;

	// create the sequence of ticks
	for ( i = 0, st = 0 ; i < N ; i++ ) {	

		if ( i % 2 == 0 )
			tock1(oneTick, gapList[i], sr) ;
		else
			tock2(oneTick, gapList[i], sr) ;

		concatenate(sequence, oneTick, st, gapList[i], sr) ;
		st += gapList[i] ;
	}

	sfsave(soundfile, sequence, totalDuration, sr, 1) ;

	Free(sequence) ;
	Free(oneTick) ;

	return ;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sf.h>
#include <sfmisc.h>

#include "random.h"

int main(void)
{
	double dur = 3 ;
	int sr = 44100 ;
	double db = 86 ;
	short *sound ;
	double T[] = {0.0, 0.25, 0.5, 0.75, 1.0} ;
	double A[] = {0.0, 1.0, 0.75, 0.5, 0.0} ;
	int nPoints = 5 ;
	int nchan = 1 ;

	extern void adsr2(short sound[], double dur, int sr, 
			double T[], double A[], int N, int flag) ;

	sound = (short *)Malloc(dur * sr * sizeof(short)) ;

	whiteNoise(sound, dur, sr, db) ;
	adsr2(sound, dur, sr, T, A, nPoints, 0) ;

	sfsave("wn.wav", sound, dur, sr, nchan) ;

	return 0 ;
}


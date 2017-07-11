#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sf.h>
#include <sfmisc.h>

#include "env.h"
#include "mixtwo.h"

static void mixPanTestValues(double *tList, int *cList, int N) 
{
	double *t ;
	int *c, err = 0 ;
	static int fCounter ;
	int mixChannelCount ;

	mixChannelCount = getMixChannelCount() ;

	fCounter++ ;

	for ( c = cList ; c < cList + N ; c++ ) {
		if ( *c >= mixChannelCount || *c < 0 ) {
			fprintf(stderr,
				"%s:%d mixPan[%d]: Bad value in channel list: %d\n", 
				__FILE__, __LINE__, fCounter, *c) ; 
			err++ ;
		}
	}

	for ( t = tList ; t < tList + N ; t++ ) {
		if ( *t < 0.0 || *t > 1 ) {
			fprintf(stderr,"%s:%d mixPan[%d]: Bad value in time list: %g\n",
				__FILE__, __LINE__, fCounter, *t) ; 
			err++ ;
		}
	}

	for ( t = tList ; t < tList + (N-1) ; t++ ) {
		if ( *t > *(t+1) ) {
			fprintf(stderr,"%s:%d mixPan[%d]: Time points out of sequence:",
					__FILE__, __LINE__, fCounter) ;
			fprintf(stderr, "%g -> %g\n", *t, *(t+1)) ;
			err++ ;
		}
	}

	if ( err ) {
		fprintf(stderr,"%s:%d mixPan[%d]: too many errors: %d\n", 
					__FILE__, __LINE__, fCounter, err) ;
		fprintf(stderr,"Exiting\n") ;
		exit(EXIT_FAILURE) ;
	}

	if ( tList[0] != 0 ) {
		fprintf(stderr,
		"%s:%d mixPan[%d]: Warning: TimePoint[0] is not zero: %g. Changing\n",
					__FILE__, __LINE__, fCounter, tList[0]) ;
		tList[0] = 0 ;
	}

	if ( tList[N-1] != 1.0 ) {
		fprintf(stderr,
		"%s:%d mixPan[%d]: Warning: TimePoint[N-1] is not 1.0: %g\n",
				__FILE__, __LINE__, fCounter, tList[N-1]) ;
		tList[N-1] = 1.0 ;
	}

	return ;
}

static void mixPanEqualPower(short *input, int samples, 
		short *out1, short *out2)
{
	double pan, panInc, L, R, B ;

	panInc = 1.0 / (samples - 1.0) ;
	for ( pan = 1.0 ; samples-- ; pan -= panInc ) {
		L = pan ; R = 1 - pan ;
		B = 1.0 / sqrt( L*L + R*R ) ;
		L *= B ; R *= B ;
		*out1++ = (short)(L * *input) ;
		*out2++ = (short)(R * *input++) ;
	}

	return ;
}

static int mixPanGetMaxTrans(int *sList, int N) 
{
	int *s, max = *sList ;

	for ( s = sList + 1 ; s < sList + (N-1) ; s++ )
		if ( *s > max )
			max = *s ;

	return max ;
}

static void mixPanAdjustRoundOffError(
		double td, int sr, double *tList, int N, int **sList)
{
	int *s, samples, sum ;
	double *t, seconds ;

	s = *sList = (int *)Malloc((N-1) * sizeof(int)) ;

	sum = 0 ;		// translate time values to samples
	for ( t = tList + 1 ; t < tList + N ; t++, s++ ) {
		seconds = (*t - *(t-1)) * td ;		// proportion to seconds
		*s = seconds * sr ;					// seconds to samples
		sum += *s ;
	}

	samples = td * sr ;		// total duration in samples
	if ( sum != samples )	// adjust for round off error
		*(s-1) += samples - sum ;

	return ;
}

void mixPan(short *input, double startTime, double totalDur, int sr, 
		double tList[], int cList[], int N)
{
	short *out1, *out2 ;
	int i, samples, *sList, st ;
	double mixTotalDuration ;

	mixTotalDuration = getMixTotalDuration() ;
	if ( startTime + totalDur >= mixTotalDuration ) {
		fprintf(stderr,
		"%s:%s:%d: Error: startTime + totalDur > mixBuffer size\n", 
			__FILE__, __FUNCTION__, __LINE__) ;
		fprintf(stderr,
			"\tstartTime = %f  totalDur = %f mixBuffer: %f\n",
				startTime, totalDur, mixTotalDuration) ;
		exit(EXIT_FAILURE) ;
	}

	mixPanTestValues(tList, cList, N) ;	// ensure values are decent

	// translate time values to samples, adjusting for round off error
	mixPanAdjustRoundOffError(totalDur, sr, tList, N, &sList) ;

	samples = mixPanGetMaxTrans(sList, N) ;
	out1 = (short *)Malloc(samples * sizeof(short)) ;
	out2 = (short *)Malloc(samples * sizeof(short)) ;

	st = startTime * sr ;	// start time in samples ;

	for ( i = 0 ; i < N - 1 ; i++ ) {

		samples = sList[i] ;	// transition duration in samples

		// pan 'input' to 'out1' and 'out2' over 'samples' duration
		mixPanEqualPower(input, samples, out1, out2) ;
		mixAddS(out1, st, samples, cList[i]) ;	// add the results to the mix
		mixAddS(out2, st, samples, cList[i+1]) ;

		st += samples ;		// increment output start time
		input += samples ;	// increment input pointer

	}

	Free(out1) ;
	Free(out2) ;
	Free(sList) ;

	return ;
}

